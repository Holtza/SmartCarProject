/**
 * lanedetector - Application skeleton for detecting lane markings.
 * Copyright (C) 2012 - 2015 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>
#include <memory>
#include <stdio.h>
#include <math.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>

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
#define IMAGE_SAMPLE 25
#define IMAGE_LINE_SPACING IMAGE_HEIGHT/(10/3)/IMAGE_SAMPLE
#define TURN_RATE 17
#define THRESHOLD 55

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::base::module;
        using namespace odcore::data;
        using namespace odcore::data::image;
        using namespace odtools::player;
        using namespace automotive;

        LaneDetector::LaneDetector(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "LaneDetector"),
            m_hasAttachedToSharedImageMemory(false),
            m_sharedImageMemory(),
            m_image(NULL),
            m_debug(false) {}

        LaneDetector::~LaneDetector() {}

        void LaneDetector::setUp() {
	        // This method will be called automatically _before_ running body().

            // If in debug mode, display the image from the camera feed.
	        if (m_debug) {
		        cvNamedWindow("Camera Feed Image", CV_WINDOW_AUTOSIZE);
		        cvMoveWindow("Camera Feed Image", 300, 100);
	        }
        }

        void LaneDetector::tearDown() {
	        // This method will be called automatically _after_ return from body().
	        if (m_image != NULL) {
		        cvReleaseImage(&m_image);
	        }

	        if (m_debug) {
		        cvDestroyWindow("Camera Feed Image");
	        }
        }

        bool LaneDetector::readSharedImage(Container &c) {
	        bool retVal = false;

	        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
		        SharedImage si = c.getData<SharedImage> ();

		        // Check if we have already attached to the shared memory containing the image from the virtual camera.
		        if (!m_hasAttachedToSharedImageMemory) {
			        m_sharedImageMemory = odcore::wrapper::SharedMemoryFactory::attachToSharedMemory(si.getName());
		        }

		        // Check if we could successfully attach to the shared memory.
		        if (m_sharedImageMemory->isValid()) {
			        // Lock the memory region to gain exclusive access using a scoped lock.
                    Lock l(m_sharedImageMemory);

			        if (m_image == NULL) {
				        m_image = cvCreateImage(cvSize(si.getWidth(), si.getHeight()), IPL_DEPTH_8U, si.getBytesPerPixel());
			        }

			        // Example: Simply copy the image into our process space.
			        if (m_image != NULL) {
				        memcpy(m_image->imageData, m_sharedImageMemory->getSharedMemory(), si.getWidth() * si.getHeight() * si.getBytesPerPixel());
			        }

			        // Mirror the image.
			        cvFlip(m_image, 0, -1);

			        retVal = true;
		        }
	        }
	        return retVal;
        }

        // This method is called to process an image described by the SharedImage data structure.
        void LaneDetector::processImage() {
	   int i,d,k,red,green,length;
           int sample, avgDirection; 
	   int avgLeft = 0;
	   int avgRight = 0;
	   int blue = 0;
	   double desiredSteeringWheelAngle;
       VehicleControl control;

           cv::Mat m = cv::cvarrToMat(m_image);
	   for(i=0;i<IMAGE_SAMPLE;i++){
	   	for(d=-1;d<=1;d+=2){
	   		int intensity = 255*sqrt(IMAGE_SAMPLE-i)/sqrt(IMAGE_SAMPLE);
		    if(d==1){
				green = intensity;
				blue = intensity;
				red = 0;
		    }else{
		    	green = intensity/4;
				blue = intensity;
				red= intensity/2;
		    }

	       	    for(k=0;k<IMAGE_WIDTH/2 - 3;k++){	   
			int x = (IMAGE_WIDTH/2)+k*d;
			int y = IMAGE_HEIGHT - (i*IMAGE_LINE_SPACING);
			
			sample = m.at<cv::Vec3b>(y,x)[0];
		        length = k;

			
		     //  cv::Vec3b colour = m.at<cv::Vec3b>(cvPoint(IMAGE_WIDTH/2+k*d, IMAGE_HEIGHT-(i*IMAGE_1LINE_SPACING)));
		       if(sample==255){
		           break;
	               }
	            }
	            if(d>0){
		        avgRight += length;
		    }else{
		        avgLeft += length;
		    }
		    CvPoint cvP1 = cvPoint(IMAGE_WIDTH / 2, IMAGE_HEIGHT - (i * IMAGE_LINE_SPACING));
	   	    CvPoint cvP2 = cvPoint(IMAGE_WIDTH / 2 + length * d, IMAGE_HEIGHT - (i*IMAGE_LINE_SPACING));
		    cv::line(m, cvP1, cvP2, CV_RGB(red,green,blue), 1, 8, 0);
	       }
           }
	   
	   avgDirection = avgLeft/IMAGE_SAMPLE - avgRight/IMAGE_SAMPLE;

	   control.setSpeed(2);

	   cerr << avgDirection <<  " - ";

       //left
	   if(avgDirection >= THRESHOLD){
	   	  	desiredSteeringWheelAngle = -TURN_RATE;
	        control.setSteeringWheelAngle(desiredSteeringWheelAngle* cartesian::Constants::DEG2RAD);
	        cerr << "Left" << endl;
	  }else if(avgDirection <= -THRESHOLD){
	        desiredSteeringWheelAngle = TURN_RATE;
	        control.setSteeringWheelAngle(desiredSteeringWheelAngle * cartesian::Constants::DEG2RAD);
	        cerr << "Right" << endl;

       //neutral
	   }else{
	       desiredSteeringWheelAngle = 0;
	       control.setSteeringWheelAngle(desiredSteeringWheelAngle * cartesian::Constants::DEG2RAD);
	       cerr << "Forward" << endl;
	   }
 	   

           cv::line(m, cvPoint(IMAGE_WIDTH/2,IMAGE_HEIGHT), cvPoint(IMAGE_WIDTH/2, 0), CV_RGB(255,255,255), 1,8,0);
           
            if (m_debug) {
                if (m_image != NULL) {
                    cvShowImage("Camera Feed Image", m_image);
                    cvWaitKey(10);
                }
            }


	   // uint32_t imgSize = m_image -> getSize();



            // 2. Calculate desired steering commands from the image features.



            // Here, you see an example of how to send the data structure SteeringData to the ContainerConference.
            // This data structure will be received by all running components. In our example, it will be processed
            // by a potential component to "drive" the car.
         //   SteeringData sd;
         //   sd.setExampleData(1234.56);

            Container v(control);
            getConference().send(v);

            // Create container for finally sending the data.
        //    Container c(sd);
            // Send container.
        //    getConference().send(c);
        }

        // This method will do the main data processing job.
        // Therefore, it tries to open the real camera first. If that fails, the virtual camera images from camgen are used.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode LaneDetector::body() {
	        // Get configuration data.
	        KeyValueConfiguration kv = getKeyValueConfiguration();
	        m_debug = kv.getValue<int32_t> ("lanedetector.debug") == 1;

            unique_ptr<Player> player;
/*
            // Lane-detector can also directly read the data from file. This might be interesting to inspect the algorithm step-wisely.
            odcore::io::URL url("file://recording.rec");

            // Size of the memory buffer.
            const uint32_t MEMORY_SEGMENT_SIZE = kv.getValue<uint32_t>("global.buffer.memorySegmentSize");

            // Number of memory segments.
            const uint32_t NUMBER_OF_SEGMENTS = kv.getValue<uint32_t>("global.buffer.numberOfMemorySegments");

            // If AUTO_REWIND is true, the file will be played endlessly.
            const bool AUTO_REWIND = true;

            // We do not want player to run in parallel but we want to process frame by frame sequentially.
            const bool THREADING = false;

            // Construct the player.
            player = unique_ptr<Player>(new Player(url, AUTO_REWIND, MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING));
*/

            // Main data processing loop.
	        while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
		        bool has_next_frame = false;

		        // Use the shared memory image.
                Container c;
                if (player.get() != NULL) {
		            // Read the next container from file.
                    c = player->getNextContainerToBeSent();
                }
                else {
		            // Get the most recent available container for a SHARED_IMAGE.
		            c = getKeyValueDataStore().get(odcore::data::image::SharedImage::ID());
                }

		        if (c.getDataType() == odcore::data::image::SharedImage::ID()) {
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

    } // miniature
} // automotive

