/**
 * driver is an example application to demonstrate how to 
 *         generate driving commands from an application realized
 *         with OpenDaVINCI
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

#include <cstdio>
#include <cmath>
#include <iostream>

#include "opendavinci/odcore/io/conference/ContainerConference.h"
#include "opendavinci/odcore/data/Container.h"

#include "automotivedata/GeneratedHeaders_AutomotiveData.h"

#include "Driver.h"

#define CAR_SHARP_TURN_RIGHT 's'
#define CAR_SHORT_TURN_RIGHT 'c'
#define CAR_AVG_TURN_RIGHT 'f'
#define CAR_SHARP_TURN_LEFT 'A'
#define CAR_SHORT_TURN_LEFT 'R'
#define CAR_AVG_TURN_LEFT 'L'
#define CAR_STRAIGHT 'Z'
#define OVERTAKER_LEFT 'A'
#define OVERTAKER_RIGHT 's'


namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace odcore::data;
        using namespace automotive;
        using namespace automotive::miniature;

        Driver::Driver(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "Driver") {
        }

        Driver::~Driver() {}

        void Driver::setUp() {
            // This method will be call automatically _before_ running body().
        }

        void Driver::tearDown() {
            // This method will be call automatically _after_ return from body().
        }

        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Driver::body() {
 
            const int32_t ULTRASONIC_FRONT_CENTER = 3;
            const int32_t INFRARED_FRONT_RIGHT = 0;
            const int32_t INFRARED_REAR_RIGHT = 2;
            //int ignoreFollower = 0;

            int startedOvertaking = 0;

            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                // In the following, you find example for the various data sources that are available:

                // 1. Get most recent vehicle data:
                Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
                VehicleData vd = containerVehicleData.getData<VehicleData> ();
                cerr << "Most recent vehicle data: '" << vd.toString() << "'" << endl;

                // 2. Get most recent sensor board data:
                Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
                SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();
                cerr << "Most recent sensor board data: '" << sbd.toString() << "'" << endl;

                // 3. Get most recent user button data:
                Container containerUserButtonData = getKeyValueDataStore().get(automotive::miniature::UserButtonData::ID());
                UserButtonData ubd = containerUserButtonData.getData<UserButtonData> ();
                cerr << "Most recent user button data: '" << ubd.toString() << "'" << endl;

                // 4. Get most recent steering data as fill from lanedetector for example:
                Container containerSteeringData = getKeyValueDataStore().get(automotive::miniature::SteeringData::ID());
                SteeringData sd = containerSteeringData.getData<SteeringData> ();
                cerr << "Most recent steering data: '" << sd.toString() << "'" << endl;

                
                // Design your control algorithm here depending on the input data from above.
                
		
                Container c = getKeyValueDataStore().get(automotive::VehicleControl::ID());
                automotive::VehicleControl receivedVC = c.getData<automotive::VehicleControl>();



                // Create vehicle control data.
                VehicleControl vc;
                
                /*
                if((int)receivedVC.getSpeed() == 1 && ignoreFollower == 0){
                     ignoreFollower = 1;
 
                     if((int)receivedVC.getSteeringWheelAngle() == OVERTAKER_LEFT)vc.setSteeringWheelAngle(OVERTAKER_LEFT);
                     else if((int)receivedVC.getSteeringWheelAngle() == OVERTAKER_RIGHT)vc.setSteeringWheelAngle(OVERTAKER_RIGHT);
 
                }
                if(receivedVC.getSpeed() >= 1.45 && receivedVC.getSpeed() <= 1.55 && ignoreFollower == 1){
                     ignoreFollower = 0;
                 
 
                // LEFT = -0.157080
                // SHORT_LEFT = -0.052360
                // SHARP_LEFT = -0.244346
                if((int)receivedVC.getSpeed() == 2 && ignoreFollower == 0){
                     if((int)(receivedVC.getSteeringWheelAngle()*(180.0/3.14159)) == 0)vc.setSteeringWheelAngle(CAR_STRAIGHT);
                     else if((int)(receivedVC.getSteeringWheelAngle()*(180.0/3.14159)) == -3)vc.setSteeringWheelAngle(CAR_SHORT_TURN_LEFT);
                     else if((int)(receivedVC.getSteeringWheelAngle()*(180.0/3.14159)) == -9)vc.setSteeringWheelAngle(CAR_AVG_TURN_LEFT);
                     else if((int)(receivedVC.getSteeringWheelAngle()*(180.0/3.14159)) == -14)vc.setSteeringWheelAngle(CAR_SHARP_TURN_LEFT);
                     else if((int)(receivedVC.getSteeringWheelAngle()*(180.0/3.14159)) == 3)vc.setSteeringWheelAngle(CAR_SHORT_TURN_RIGHT);
                     else if((int)(receivedVC.getSteeringWheelAngle()*(180.0/3.14159)) == 9)vc.setSteeringWheelAngle(CAR_AVG_TURN_RIGHT);
                     else if((int)(receivedVC.getSteeringWheelAngle()*(180.0/3.14159)) == 14)vc.setSteeringWheelAngle(CAR_SHARP_TURN_RIGHT);
                }
                */

                //if((int)receivedVC.getSpeed() == 2 && ignoreFollower == 0){
                //      if((int)(sd.getExampleData()*(180.0/3.14159)) == 0)vc.setSteeringWheelAngle(CAR_STRAIGHT);
                //      else if((int)(sd.getExampleData()*(180.0/3.14159)) == -3)vc.setSteeringWheelAngle(CAR_SHORT_TURN_LEFT);
                //      else if((int)(sd.getExampleData()*(180.0/3.14159)) == -9)vc.setSteeringWheelAngle(CAR_AVG_TURN_LEFT);
                //      else if((int)(sd.getExampleData()*(180.0/3.14159)) == -14)vc.setSteeringWheelAngle(CAR_SHARP_TURN_LEFT);
                //      else if((int)(sd.getExampleData()*(180.0/3.14159)) == 3)vc.setSteeringWheelAngle(CAR_SHORT_TURN_RIGHT);
                //      else if((int)(sd.getExampleData()*(180.0/3.14159)) == 9)vc.setSteeringWheelAngle(CAR_AVG_TURN_RIGHT);
                //      else if((int)(sd.getExampleData()*(180.0/3.14159)) == 14)vc.setSteeringWheelAngle(CAR_SHARP_TURN_RIGHT);
                // //}


                

                cout<<sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER)<<endl;
                cout<<sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER)<<endl;
                cout<<sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER)<<endl;
                cout<<sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER)<<endl;
                cout<<sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER)<<endl;


                if(startedOvertaking < 50){
                    if(sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) > 15 || sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) < 0){
                        cout<<"i am following lane"<<endl;
                        cout<<"i am following lane"<<endl;
                        vc.setSteeringWheelAngle(sd.getExampleData());
                        vc.setSpeed(2);
                    }else{
                        cout<<"overtaking!!!"<<endl;
                        cout<<"overtaking!!!"<<endl;
                        vc.setSteeringWheelAngle(receivedVC.getSteeringWheelAngle());
                        vc.setSpeed(receivedVC.getSpeed());
                        startedOvertaking++;
                        cout<<startedOvertaking<<endl;
                        cout<<startedOvertaking<<endl;
                        cout<<startedOvertaking<<endl;

                    }
                }else if (startedOvertaking >= 50){
                    if(sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT) < 0 && sbd.getValueForKey_MapOfDistances(INFRARED_FRONT_RIGHT) < 0){
                        cout<<"i am following lane2"<<endl;
                        cout<<"i am following lane2"<<endl;
                        vc.setSteeringWheelAngle(sd.getExampleData());
                        vc.setSpeed(2);
                    }else{
                        cout<<"overtaker!!!2"<<endl;
                        cout<<"overtaker!!!2"<<endl;
                        vc.setSteeringWheelAngle(receivedVC.getSteeringWheelAngle());
                        vc.setSpeed(receivedVC.getSpeed());
                    }
                }
                // Design your control algorithm here depending on the input data from above.
		      


                // With setSteeringWheelAngle, you can steer in the range of -26 (left) .. 0 (straight) .. +25 (right)
   //             double desiredSteeringWheelAngle = 4; // 4 degree but SteeringWheelAngle expects the angle in radians!
   //             vc.setSteeringWheelAngle(desiredSteeringWheelAngle * cartesian::Constants::DEG2RAD);

               // double desiredSteeringWheelAngle = vd.getHeading();
               // vc.setSteeringWheelAngle(desiredSteeringWheelAngle * cartesian::Constants::DEG2RAD);

                // You can also turn on or off various lights:
                //vc.setBrakeLights(false);
                //vc.setFlashingLightsLeft(false);
                //vc.setFlashingLightsRight(true);

                // Create container for finally sending the data.
                Container cSend(vc);
                //Container exCont(sd);
                // Send container.
                getConference().send(cSend);
                //getConference().send(exCont);
            }

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature

