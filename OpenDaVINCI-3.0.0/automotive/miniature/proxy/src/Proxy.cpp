
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


       string Proxy::readMiddleman(){
            char sensorValues[50];
            FILE *file;
            file = fopen("/root/lastPacket.txt", "r");
            fscanf(file, "%[^\n]", sensorValues);
            fprintf(file, "%s", sensorValues);
            fclose(file);
            return sensorValues;
 
        }


        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Proxy::body() {
            uint32_t captureCounter = 0;
            int US_FrontCenter;
            int US_FrontRight;
            int IR_FrontRight;
            int IR_RearRight;
            int IR_Rear;

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

               // Get most recent sensor board data
                Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
                SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();
                cerr << "Most recent sensor board data: '" << sbd.toString() << "'" << endl;
               // printf("%d\n", (int)(vc.getSteeringWheelAngle()*(180.0/3.14159)));
                
                // LEFT = -0.157080
                // SHORT_LEFT = -0.052360
                // SHARP_LEFT = -0.244346

              
                if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == 0)writeMiddleman(CAR_STRAIGHT);
                else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == -3)writeMiddleman(CAR_SHORT_TURN_LEFT);
                else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == -9)writeMiddleman(CAR_AVG_TURN_LEFT);
                else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == -14)writeMiddleman(CAR_SHARP_TURN_LEFT);
                else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == 3)writeMiddleman(CAR_SHORT_TURN_RIGHT);
                else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == 9)writeMiddleman(CAR_AVG_TURN_RIGHT);
                else if((int)(vc.getSteeringWheelAngle()*(180.0/3.14159)) == 14)writeMiddleman(CAR_SHARP_TURN_RIGHT);
                
                //testing reading sensor values from a file
                cout << "values: " << readMiddleman() <<endl;
                 // Get sensor data from IR/US.
                string sensorData = readMiddleman();
                int length = sensorData.length();

                // decode
                if(length == 0 || length < 20 || length > 20){ //Necessary? Length is already checked in SerialConnection!
                  cout << "error" <<endl;
 
                }else{
                   string sonarFrontCenter = sensorData.substr(0, 3);
                   US_FrontCenter = atoi(sonarFrontCenter.c_str());
                  // cout << "string US FrontCenter: " << sonarFrontCenter <<endl;
                   cout << "US_FrontCenter: " << US_FrontCenter <<endl;

                   string sonarFrontRight = sensorData.substr(3, 3);
                   US_FrontRight = atoi(sonarFrontRight.c_str());
                  // cout << "string US FrontRight: " << sonarFrontRight <<endl;
                   cout << "US_FrontRight: " << US_FrontRight <<endl;

                   string irRear = sensorData.substr(6, 3);
                   IR_Rear = atoi(irRear.c_str());
                  // cout <<"string IR Rear: " << irRear <<endl;
                   cout << "IR_Rear: " << IR_Rear <<endl;

                   string irRearRight = sensorData.substr(9, 3);
                   IR_RearRight = atoi(irRearRight.c_str());
                  // cout <<"string IR Rear Right: " << irRearRight <<endl;
                   cout << "IR_RearRight: " << IR_RearRight <<endl;

                   string irFrontRight = sensorData.substr(12, 3);
                   IR_FrontRight = atoi(irFrontRight.c_str());
                  // cout <<"string IR Front Right: " << irFrontRight <<endl;
                   cout << "IR_FrontRight: " << IR_FrontRight <<endl;
	  	   


                }

                // map 
                sbd.putTo_MapOfDistances(0, US_FrontCenter); 
                sbd.putTo_MapOfDistances(1, US_FrontRight);
                sbd.putTo_MapOfDistances(2, IR_Rear);
                sbd.putTo_MapOfDistances(3, IR_RearRight);
                sbd.putTo_MapOfDistances(4, IR_FrontRight); 

                Container container(sbd);
                getConference().send(container);

   
            }

            cout << "Proxy: Captured " << captureCounter << " frames." << endl;

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature
