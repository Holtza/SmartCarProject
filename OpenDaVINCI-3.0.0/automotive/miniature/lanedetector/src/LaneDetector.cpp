/**
* lanedetector - Application skeleton for detecting lane markings.
* Copyright (C) 2012 - 2015 Christian Berger
*
* This program is free software;
you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation;
either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY;
without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program;
if not, write to the Free Software
* Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/
#include <iostream>
#include <memory>
#include <stdio.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <opencv2/imgproc/imgproc.hpp>
#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/base/Lock.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/wrapper/SharedMemoryFactory.h"
#include "opendavinci/odtools/player/Player.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "automotivedata/GeneratedHeaders_AutomotiveData.h"
#include "LaneDetector.h"
#define IMAGE_WIDTH 640
#define IMAGE_HEIGHT 480

#define CENTER_LINE_X (IMAGE_WIDTH/2 - 85)
#define MAX_WIDTH (IMAGE_WIDTH/2 + 85)
#define IMAGE_SAMPLE 25
#define IMAGE_LINE_SPACING IMAGE_HEIGHT/(10/3)/IMAGE_SAMPLE
#define TURN_RATE_SHARP 14
#define TURN_RATE_SHORT 3
#define TURN_RATE_AVG 9
#define THRESHOLD 120
#define THRESHOLD_AVG 80
#define THRESHOLD_LOW 70
#define CAR_SHARP_TURN_RIGHT "s"
#define CAR_SHORT_TURN_RIGHT "c"
#define CAR_AVG_TURN_RIGHT "f"
#define CAR_SHARP_TURN_LEFT "A"
#define CAR_SHORT_TURN_LEFT "R"
#define CAR_AVG_TURN_LEFT "L"
#define CAR_STRAIGHT "Z"

#define KERNEL_SIZE 3
#define CANNY_LOW_THRESHOLD 50
#define CANNY_HIGH_THRESHOLD 170
#define BLUR_RADIUS 5
#define LEFT_RED 1
#define LEFT_GREEN 0.4
#define LEFT_BLUE 0
#define RIGHT_RED 0
#define RIGHT_GREEN 0.6
#define RIGHT_BLUE 1

namespace  automotive {
    namespace  miniature {
        using namespace std;
        using namespace odcore::base;
        using namespace odcore::base::module;
        using namespace odcore::data;
        using namespace odcore::data::image;
        using namespace odtools::player;
        using namespace automotive;
        LaneDetector::LaneDetector(const int32_t & argc,
        char
        **argv):TimeTriggeredConferenceClientModule
        (argc, argv, "LaneDetector"),
        m_hasAttachedToSharedImageMemory(false),
        m_sharedImageMemory(),
        m_image(NULL),
        m_debug(false) {
        }
        LaneDetector::~LaneDetector() {
        }
        void  LaneDetector::setUp() {
            // This method will be called automatically _before_ running
            // body().
            // If in debug mode, display the image from the camera feed.
/*
			printf("Setting up Camera settings...");
			system("gnome-terminal -x sh -c 'v4l2-ctl -d /dev/video0 -c focus_absolute=0;v4l2-ctl -d /dev/video0 -c focus_auto=0'");
			system("gnome-terminal -x sh -c 'v4l2-ctl -d /dev/video1 -c focus_absolute=0;v4l2-ctl -d /dev/video1 -c focus_auto=0'");
			system("gnome-terminal -x sh -c 'v4l2-ctl -d /dev/video2 -c focus_absolute=0;v4l2-ctl -d /dev/video2 -c focus_auto=0'");
			printf("  Done!\n");
*/
            if (m_debug) {
                cvNamedWindow("Camera Feed Image", CV_WINDOW_AUTOSIZE);
                cvMoveWindow("Camera Feed Image", 300, 100);
            }
        }
        void LaneDetector::tearDown() {
            // This method will be called automatically _after_ return
            // from body().
            if (m_image != NULL) {
                cvReleaseImage(&m_image);
            }
            if (m_debug) {
                cvDestroyWindow("Camera Feed Image");
            }
        }
        bool LaneDetector::readSharedImage(Container & c) {
            bool retVal = false;
            if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
                SharedImage si = c.getData < SharedImage > ();
                // Check if we have already attached to the shared memory
                // containing the image from the virtual camera.
                if (!m_hasAttachedToSharedImageMemory) {
                    m_sharedImageMemory =
                    odcore::wrapper::SharedMemoryFactory::
                    attachToSharedMemory(si.getName());
                }
                // Check if we could successfully attach to the shared
                // memory.
                if (m_sharedImageMemory->isValid()) {
                    // Lock the memory region to gain exclusive access
                    // using a scoped lock.
                    Lock l(m_sharedImageMemory);
                    if (m_image == NULL) {
                        m_image =
                        cvCreateImage(cvSize
                        (si.getWidth(), si.getHeight()),
                        IPL_DEPTH_8U,
                        si.getBytesPerPixel());
                    }
                    // Example: Simply copy the image into our process
                    // space.
                    if (m_image != NULL) {
                        memcpy(m_image->imageData,
                        m_sharedImageMemory->getSharedMemory(),
                        si.getWidth() * si.getHeight() *
                        si.getBytesPerPixel());
                    }
                    // Mirror the image.
                   // cvFlip(m_image, 0, -1);
                    retVal = true;
                }
            }
            return retVal;
        }

        void LaneDetector::applyFilter(cv::Mat *img){
            // Mirror the image.
            cvFlip(m_image, 0, -1);
            blur(*img, *img, cv::Size(BLUR_RADIUS, BLUR_RADIUS));
            Canny(*img, *img, CANNY_LOW_THRESHOLD, CANNY_HIGH_THRESHOLD, KERNEL_SIZE);
            cv::cvtColor(*img, *img, CV_GRAY2BGR);
        }

        // This method is called to process an image described by the
        // SharedImage data structure.
        void LaneDetector::processImage() {
            int  i,d,k,red,green,length;
            int  avgDirection;
            int  avgLeft = 0;
            int  avgRight = 0;
            int  blue = 0;
            double  desiredSteeringWheelAngle;
            VehicleControl control;
            

            enum StateMachineMoving {LEFT, RIGHT, FORWARD, SHORT_LEFT, SHORT_RIGHT, LEFT_SHARP, RIGHT_SHARP};

            StateMachineMoving movingState;
    
            cv::Mat img;
            img = m_image;
            applyFilter(&img);
            IplImage  *image = new IplImage(img);
            cv::Mat m = cv::cvarrToMat(image);

            for (i = 0;i < IMAGE_SAMPLE;i++) {
                for (d = -1;d <= 1;d += 2) {
                    int  intensity = 255 * sqrt(IMAGE_SAMPLE - i) / sqrt(IMAGE_SAMPLE);
                    if (d == 1) {
                        green = (int)(intensity*LEFT_GREEN);
                        blue = (int)(intensity*LEFT_BLUE);
                        red = (int)(intensity*LEFT_RED);
                    }
                    else {
                        green = (int)(intensity*RIGHT_GREEN);
                        blue = (int)(intensity*RIGHT_BLUE);
                        red = (int)(intensity*RIGHT_RED);
                    }
                    for (k = 0;k < MAX_WIDTH; k++) {
                        int  x = CENTER_LINE_X + k * d;
                        int  y = IMAGE_HEIGHT - (i * IMAGE_LINE_SPACING);
                        int sample = m.at < cv::Vec3b > (y, x)[0];
                        length = k;
                        // cv::Vec3b colour =
                        // m.at<cv::Vec3b>(cvPoint(IMAGE_WIDTH/2+k*d,
                        // IMAGE_HEIGHT-(i*IMAGE_1LINE_SPACING)));
                        if (sample == 255) {
                            break;
                        }
                    }
                    if (d > 0) {
                        avgRight += length;
                    }
                    else {
                        avgLeft += length;
                    }

                    if(m_debug) {
                        CvPoint cvP1 = cvPoint(CENTER_LINE_X, IMAGE_HEIGHT - (i * IMAGE_LINE_SPACING));
                        CvPoint cvP2 = cvPoint(CENTER_LINE_X+ length * d, IMAGE_HEIGHT - (i * IMAGE_LINE_SPACING));
                        cv::line(m, cvP1, cvP2, CV_RGB(red, green, blue), 1, 8,0);
                    }
                }
            }
            avgDirection = avgLeft / IMAGE_SAMPLE - avgRight / IMAGE_SAMPLE;

              
            if (avgDirection >= THRESHOLD) {
                movingState = LEFT_SHARP;
            }
            else if(avgDirection >= THRESHOLD_AVG){
                movingState = LEFT;
            }
            else if(avgDirection >= THRESHOLD_LOW){
                movingState = SHORT_LEFT;
            }

            else if(avgDirection <= -THRESHOLD) {
                movingState = RIGHT_SHARP;
                
            }
            else if(avgDirection <= -THRESHOLD_AVG){
                movingState = RIGHT;
            }
            else if(avgDirection <= -THRESHOLD_LOW){
                movingState = SHORT_RIGHT;
            }
            else {
                movingState = FORWARD;
            }

            //cerr << avgDirection << " - ";

            if(movingState == FORWARD){
                control.setSpeed(2);
                desiredSteeringWheelAngle = 0;
                control.setSteeringWheelAngle(desiredSteeringWheelAngle *
                cartesian::Constants::DEG2RAD);
                //writeMiddleman(CAR_STRAIGHT);
                //cerr << "Forward" << endl;
            }
            else if(movingState == SHORT_LEFT){
                control.setSpeed(2);
                desiredSteeringWheelAngle = -TURN_RATE_SHORT;
                control.setSteeringWheelAngle(desiredSteeringWheelAngle *
                cartesian::Constants::DEG2RAD);
                //writeMiddleman(CAR_SHORT_TURN_LEFT);
                //cerr << "Left Short" << endl;
            }
            else if(movingState == SHORT_RIGHT){
                control.setSpeed(2);
                desiredSteeringWheelAngle = TURN_RATE_SHORT;
                control.setSteeringWheelAngle(desiredSteeringWheelAngle *
                cartesian::Constants::DEG2RAD);
                //writeMiddleman(CAR_SHORT_TURN_RIGHT);
                //cerr << "Right Short" << endl;
            }
            else if(movingState == LEFT){
                control.setSpeed(2);
                desiredSteeringWheelAngle = -TURN_RATE_AVG;
                control.setSteeringWheelAngle(desiredSteeringWheelAngle *
                cartesian::Constants::DEG2RAD);
                //writeMiddleman(CAR_AVG_TURN_LEFT);
                //cerr << "Left" << endl;
            }
            else if(movingState == RIGHT){
                control.setSpeed(2);
                desiredSteeringWheelAngle = TURN_RATE_AVG;
                control.setSteeringWheelAngle(desiredSteeringWheelAngle *
                cartesian::Constants::DEG2RAD);
                //writeMiddleman(CAR_AVG_TURN_RIGHT);
                //cerr << "Right" << endl;
            }
            else if(movingState == LEFT_SHARP){
                control.setSpeed(2);
                desiredSteeringWheelAngle = -TURN_RATE_SHARP;
                control.setSteeringWheelAngle(desiredSteeringWheelAngle *
                cartesian::Constants::DEG2RAD);
                //writeMiddleman(CAR_SHARP_TURN_LEFT);
                //cerr << "Left Sharp" << endl;
            }
            else if(movingState == RIGHT_SHARP){
                control.setSpeed(2);
                desiredSteeringWheelAngle = TURN_RATE_SHARP;
                control.setSteeringWheelAngle(desiredSteeringWheelAngle *
                cartesian::Constants::DEG2RAD);
                //writeMiddleman(CAR_SHARP_TURN_RIGHT);
                //cerr << "Right Sharp" << endl;
            }
            
            if (m_debug) {
                cv::line(m, cvPoint(CENTER_LINE_X, IMAGE_HEIGHT), cvPoint(CENTER_LINE_X, 0), CV_RGB(255, 255, 255), 1, 8, 0);
                if (image != NULL) {
                    cvShowImage("Camera Feed Image", image);
                    cvWaitKey(10);
                }
            }
            // uint32_t imgSize = m_image -> getSize();
            // 2. Calculate desired steering commands from the image
            // features.
            // Here, you see an example of how to send the data structure
            // SteeringData to the ContainerConference.
            // This data structure will be received by all running
            // components. In our example, it will be processed
            // by a potential component to "drive" the car.
            // SteeringData sd;
            // sd.setExampleData(1234.56);
            cout<<"Sending 2"<<endl;
            Container  v(control);
            getConference().send(v);
            // Create container for finally sending the data.
            // Container c(sd);
            // Send container.
            // getConference().send(c);
        }

        // This method will do the main data processing job.
        // Therefore, it tries to open the real camera first. If that
        // fails, the virtual camera images from camgen are used.
        odcore::data::dmcp::ModuleExitCodeMessage::
        ModuleExitCode LaneDetector::body() {
            // Get configuration data.
            KeyValueConfiguration kv = getKeyValueConfiguration();
            m_debug = kv.getValue < int32_t > ("lanedetector.debug") == 1;
            unique_ptr < Player > player;
            /*
            * // Lane-detector can also directly read the data from file.
            * This might be interesting to inspect the algorithm
            * step-wisely. odcore::io::URL url("file://recording.rec");
            *
            * // Size of the memory buffer. const uint32_t
            * MEMORY_SEGMENT_SIZE =
            * kv.getValue<uint32_t>("global.buffer.memorySegmentSize");
            *
            * // Number of memory segments. const uint32_t
            * NUMBER_OF_SEGMENTS =
            * kv.getValue<uint32_t>("global.buffer.numberOfMemorySegments");
            *
            * // If AUTO_REWIND is true, the file will be played
            * endlessly. const bool AUTO_REWIND = true;
            *
            * // We do not want player to run in parallel but we want to
            * process frame by frame sequentially. const bool THREADING =
            * false;
            *
            * // Construct the player. player = unique_ptr<Player>(new
            * Player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE,
            * NUMBER_OF_SEGMENTS, THREADING));
            */
            // Main data processing loop.
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() ==
            odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                bool has_next_frame = false;
                // Use the shared memory image.
                Container  c;
                if (player.get() != NULL) {
                    // Read the next container from file.
                    c = player->getNextContainerToBeSent();
                }
                else {
                    // Get the most recent available container for a
                    // SHARED_IMAGE.
                    c = getKeyValueDataStore().
                    get(odcore::data::image::SharedImage::ID());
                }
                if (c.getDataType() ==
                odcore::data::image::SharedImage::ID()) {
                    // Example for processing the received container.
                    has_next_frame = readSharedImage(c);
                }
                // Process the read image.
                if (true == has_next_frame) {
                    processImage();
                }
            }
            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }
    }
    // miniature
}
// automotive
