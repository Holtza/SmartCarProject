/**
 * sidewaysparker - Sample application for realizing a sideways parking car.
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

#include "opendavinci/GeneratedHeaders_OpenDaVINCI.h"
#include "automotivedata/GeneratedHeaders_AutomotiveData.h"

#include "SidewaysParker.h"


namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace automotive;
        using namespace automotive::miniature;
       


        SidewaysParker::SidewaysParker(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "SidewaysParker") {
        }

        SidewaysParker::~SidewaysParker() {}

        void SidewaysParker::setUp() {
            // This method will be call automatically _before_ running body().
        }

        void SidewaysParker::tearDown() {
            // This method will be call automatically _after_ return from body().
        }


        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode SidewaysParker::body() {
            /* sensors ids */
            const double IR_FRONT_RIGHT = 0;
            const double INFRARED_REAR = 1;
           //const double INFRARED_REAR_RIGHT = 2;
            const double ULTRASONIC_FRONT_CENTER = 3;
            const double ULTRASONIC_FRONT_RIGHT = 4;

            /* states for parking */
            const int DETECTING_OBSTACLE = 0;
            const int MEASURING = 1;
            const int REVERSING = 2;
            const int BACKWARDS_RIGHT = 3;
            const int BACKWARDS_LEFT = 4;
            const int STOP = 5;
            const int ALIGNING = 6;
          
           
            double carSize = 5.0;
            double currentTraveledPath; 
            int count;
            int count2;
            int state = DETECTING_OBSTACLE;


            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                // 1. Get most recent vehicle data:
                Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
                VehicleData vd = containerVehicleData.getData<VehicleData> ();
                cerr << "Most recent vehicle data: '" << vd.toString() << "'" << endl;

               // 2. Get most recent sensor board data:
               Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
               SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();
              



                // Create vehicle control data.
                VehicleControl vc;

       
                  
        
                      switch (state) {

                        case DETECTING_OBSTACLE: {
                        cout << "DETECTING_OBSTACLE" << endl;
                        vc.setSpeed(.8);
                        vc.setSteeringWheelAngle(0);
  
                          if(sbd.getValueForKey_MapOfDistances(IR_FRONT_RIGHT) < 0 && (sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_RIGHT) < 0 || sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_RIGHT) > carSize)){
                                state = MEASURING;
                                currentTraveledPath = vd.getAbsTraveledPath();
                        }
                     }
                        break;

                        case MEASURING:{
                        cout << "MEASURING" << endl;
                        cout << "Gap Space= " << vd.getAbsTraveledPath() - currentTraveledPath << endl;
                        vc.setSpeed(.8);
                        vc.setSteeringWheelAngle(0);
                    
                          if((sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_RIGHT) > -1 && vd.getAbsTraveledPath() - currentTraveledPath < carSize * 1.5)){
                                state = DETECTING_OBSTACLE;
                        }else if (vd.getAbsTraveledPath() - currentTraveledPath >= carSize * 2.2){
                                count = 0;
                                state = REVERSING;
                                currentTraveledPath = vd.getAbsTraveledPath();
                              
                             
                        }
                    }
                       break;

                        case REVERSING: {
                        cout << "REVERSING" << endl;
                        ++count;
                        vc.setSpeed(0);
                        if(count >= 30){
                                state = BACKWARDS_RIGHT;
                                currentTraveledPath = vd.getAbsTraveledPath();
                                count2 = 0;
                        }
                }

                        break;
                        
                        case BACKWARDS_RIGHT: {
          
                        cout << "BACKWARDS_RIGHT" << endl;
                        // cout << "IR_Rear= " << sbd.getValueForKey_MapOfDistances(INFRARED_REAR) << endl;
                
                        if(count2 <= 40){
                         vc.setSpeed(-1.6);
                         vc.setSteeringWheelAngle(25);
                        }
                       count2++;
                 
                          if(count2 > 40){
                               vc.setSpeed(0);
                               state = BACKWARDS_LEFT;
                        }

                     }
                        break;

                        case BACKWARDS_LEFT: {

                          cout << "BACKWARDS_LEFT" << endl;
                          vc.setSpeed(-.175);
                          vc.setSteeringWheelAngle(-25);
                          cout << "IR_Rear= " << sbd.getValueForKey_MapOfDistances(INFRARED_REAR ) << endl;
                 
                          if(sbd.getValueForKey_MapOfDistances(INFRARED_REAR) < carSize * 0.4 && sbd.getValueForKey_MapOfDistances(INFRARED_REAR) > 0){
                            state = ALIGNING;
                          }
                        }
                   
                        break;

                        case ALIGNING: {
                         cout << "ALIGNING" << endl;
                         vc.setSpeed(.4);
                         vc.setSteeringWheelAngle(25);
                         cout << "US_Front_Center= " << sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) << endl;
                    
                        if(sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) < carSize * 2 && sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) > 0){
                       
                                 vc.setSteeringWheelAngle(25);
                                 vc.setSpeed(.4);
                                 state = STOP;
                          
                        }
                   }
                        break;
                  
                        case STOP: {
                        cout << "Mode: STOP" << endl;
                        vc.setSpeed(0);
                   }
                        break;


                }
 
                 

                // Create container for finally sending the data.
                Container c(vc);
                // Send container.
                getConference().send(c);
            }

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }



   



    }
} // automotive::miniature

