/**
 * proxy - Sample application to encapsulate HW/SW interfacing with embedded systems.
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

#include <ctype.h>
#include <cstring>
#include <cmath>
#include <iostream>
#include <math.h>

#include "opendavinci/odcore/base/KeyValueConfiguration.h"
#include "opendavinci/odcore/data/Container.h"
#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "automotivedata/GeneratedHeaders_AutomotiveData.h"
#include "opendavinci/odcore/data/TimeStamp.h"

#include "OpenCVCamera.h"

#ifdef HAVE_UEYE
    #include "uEyeCamera.h"
#endif

#include "Proxy.h"

#define CAR_SHARP_TURN_RIGHT "s"
#define CAR_SHORT_TURN_RIGHT "c"
#define CAR_AVG_TURN_RIGHT "f"
#define CAR_SHARP_TURN_LEFT "A"
#define CAR_SHORT_TURN_LEFT "R"
#define CAR_AVG_TURN_LEFT "L"
#define CAR_STRAIGHT "Z"


namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odtools::recorder;

        Proxy::Proxy(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "proxy"),
            m_recorder(),
            m_camera()
        {}

        Proxy::~Proxy() {
        }

        void Proxy::setUp() {
            // This method will be call automatically _before_ running body().
            if (getFrequency() < 20) {
                cerr << endl << endl << "Proxy: WARNING! Running proxy with a LOW frequency (consequence: data updates are too seldom and will influence your algorithms in a negative manner!) --> suggestions: --freq=20 or higher! Current frequency: " << getFrequency() << " Hz." << endl << endl << endl;
            }

            // Get configuration data.
            KeyValueConfiguration kv = getKeyValueConfiguration();

            // Create built-in recorder.
            const bool useRecorder = kv.getValue<uint32_t>("proxy.useRecorder") == 1;
            if (useRecorder) {
                // URL for storing containers.
                stringstream recordingURL;
                recordingURL << "file://" << "proxy_" << TimeStamp().getYYYYMMDD_HHMMSS() << ".rec";
                // Size of memory segments.
                const uint32_t MEMORY_SEGMENT_SIZE = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.memorySegmentSize");
                // Number of memory segments.
                const uint32_t NUMBER_OF_SEGMENTS = getKeyValueConfiguration().getValue<uint32_t>("global.buffer.numberOfMemorySegments");
                // Run recorder in asynchronous mode to allow real-time recording in background.
                const bool THREADING = true;
                // Dump shared images and shared data?
                const bool DUMP_SHARED_DATA = getKeyValueConfiguration().getValue<uint32_t>("proxy.recorder.dumpshareddata") == 1;

                m_recorder = unique_ptr<Recorder>(new Recorder(recordingURL.str(), MEMORY_SEGMENT_SIZE, NUMBER_OF_SEGMENTS, THREADING, DUMP_SHARED_DATA));
            }

            // Create the camera grabber.
            const string NAME = getKeyValueConfiguration().getValue<string>("proxy.camera.name");
            string TYPE = getKeyValueConfiguration().getValue<string>("proxy.camera.type");
            std::transform(TYPE.begin(), TYPE.end(), TYPE.begin(), ::tolower);
            const uint32_t ID = getKeyValueConfiguration().getValue<uint32_t>("proxy.camera.id");
            const uint32_t WIDTH = getKeyValueConfiguration().getValue<uint32_t>("proxy.camera.width");
            const uint32_t HEIGHT = getKeyValueConfiguration().getValue<uint32_t>("proxy.camera.height");
            const uint32_t BPP = getKeyValueConfiguration().getValue<uint32_t>("proxy.camera.bpp");

            if (TYPE.compare("opencv") == 0) {
                m_camera = unique_ptr<Camera>(new OpenCVCamera(NAME, ID, WIDTH, HEIGHT, BPP));
            }
            if (TYPE.compare("ueye") == 0) {
#ifdef HAVE_UEYE
                m_camera = unique_ptr<Camera>(new uEyeCamera(NAME, ID, WIDTH, HEIGHT, BPP));
#endif
            }

            if (m_camera.get() == NULL) {
                cerr << "No valid camera type defined." << endl;
            }
        }

        void Proxy::tearDown() {
            // This method will be call automatically _after_ return from body().
        }

        void Proxy::distribute(Container c) {
            // Store data to recorder.
            if (m_recorder.get() != NULL) {
                // Time stamp data before storing.
                c.setReceivedTimeStamp(TimeStamp());
                m_recorder->store(c);
            }

            // Share data.
            getConference().send(c);
        }

        void Proxy::writeMiddleman(const char* turn){
            FILE *file;
            file = fopen("/root/middleman.txt", "w");
            fprintf(file, "%s", turn);
            fclose(file);
 
        }


        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Proxy::body() {
            uint32_t captureCounter = 0;
            //int wheelAngle = 0;
            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                // Capture frame.
                if (m_camera.get() != NULL) {
                    odcore::data::image::SharedImage si = m_camera->capture();

                    Container c(si);
                    distribute(c);
                    captureCounter++;
                }
                
                //Container containerVehicleData = getKeyValueDataStore().get(VehicleData::ID());
                //VehicleData vd = containerVehicleData.getData<VehicleData> ();
                Container c = getKeyValueDataStore().get(automotive::VehicleControl::ID());
                automotive::VehicleControl vc = c.getData<automotive::VehicleControl>();
                printf("%d\n", (int)(vc.getSteeringWheelAngle()*(180.0/3.14159)));


                if((int)vc.getSpeed() == 3){
                    char ch = (int)vc.getSteeringWheelAngle();
                    
                    const char* cchar = &ch;
                    
                    
                    writeMiddleman(cchar); 
                }


/*                
                if(vc.getSpeed() == 1 && ignoreFollower == 0){
                    ignoreFollower = 1;
                        
                    if(vc.getSteeringWheelAngle() == OVERTAKER_ANGLE_LEFT)writeMiddleman(OVERTAKER_ANGLE_LEFT);
                    else if(vc.getSteeringWheelAngle() == OVERTAKER_ANGLE_RIGHT)writeMiddleman(OVERTAKER_ANGLE_RIGHT);

                }
                if(vc.getSpeed() == 1.5 && ignoreFollower == 1){
                    ignoreFollower = 0;
                }


                // LEFT = -0.157080
                // SHORT_LEFT = -0.052360
                // SHARP_LEFT = -0.244346
                if(vc.getSpeed() == 2 && ignoreFollower == 0){
                    if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == 0)writeMiddleman(CAR_STRAIGHT);
                    else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == -3)writeMiddleman(CAR_SHORT_TURN_LEFT);
                    else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == -9)writeMiddleman(CAR_AVG_TURN_LEFT);
                    else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == -14)writeMiddleman(CAR_SHARP_TURN_LEFT);
                    else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == 3)writeMiddleman(CAR_SHORT_TURN_RIGHT);
                    else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == 9)writeMiddleman(CAR_AVG_TURN_RIGHT);
                    else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == 14)writeMiddleman(CAR_SHARP_TURN_RIGHT);

                // Get sensor data from IR/US.
                }*/
                
            
             }

            cout << "Proxy: Captured " << captureCounter << " frames." << endl;

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature

