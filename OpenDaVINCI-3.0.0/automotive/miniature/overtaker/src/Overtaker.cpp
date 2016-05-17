/**
 * overtaker - Sample application for overtaking obstacles.
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

#include "Overtaker.h"

#define WHEELEANGLE 25
#define LEFT_WHEELANGLE -25
#define TURNSPEED 1
#define FOLLOWSPEED 1.5

double currentTraveledPath;
const int32_t WHEEL_ENCODER = 5;

namespace automotive {
    namespace miniature {

        using namespace std;
        using namespace odcore::base;
        using namespace odcore::data;
        using namespace automotive;
        using namespace automotive::miniature;

        Overtaker::Overtaker(const int32_t &argc, char **argv) :
            TimeTriggeredConferenceClientModule(argc, argv, "overtaker") {
        }

        Overtaker::~Overtaker() {}

        void Overtaker::setUp() {
            // This method will be call automatically _before_ running body().
        }

        void Overtaker::tearDown() {
            // This method will be call automatically _after_ return from body().
        }

        ControlUnit Overtaker::measureStage(ControlUnit unit){
            
            //set sensors
            const int32_t ULTRASONIC_FRONT_CENTER = 3;
            //const int32_t ULTRASONIC_FRONT_RIGHT = 4;
            const int32_t INFRARED_FRONT_RIGHT = 0;
            const int32_t INFRARED_REAR_RIGHT = 2;

            //measurement variables
            const double OVERTAKING_DISTANCE = 65;
            const double HEADING_PARALLEL = 5.0;
            const int val[] = {59, 58};

            // Get most recent sensor board data:
            Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
            SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData> ();

	    //Get most recent vehicle data:
         	Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
         	VehicleData vd = containerVehicleData.getData<VehicleData>();


		//Set AbsTraveledPath data to latest wheel encoder data
		vd.setAbsTraveledPath(sbd.getValueForKey_MapOfDistances(WHEEL_ENCODER));


            //cerr << "State is: " << unit.stageMeasuring << endl;

		switch(unit.stageMeasuring){

			case ControlUnit::FIND_OBJECT_INIT: {
				if(sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) > 1){
                    			unit.distanceToObstacleOld = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER);
               			}
                		unit.stageMeasuring = ControlUnit::FIND_OBJECT;

              			//  cerr << "State is FIND_OBJECT" << endl;
			}break;

			case ControlUnit::FIND_OBJECT: {
				if(sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) > 1){
                    			unit.distanceToObstacle = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER);
                		}
                		cerr << "Distance to obstacle old: " << unit.distanceToObstacleOld << endl;
                		cerr << "Distance to obstacle: " << unit.distanceToObstacle << endl;

                		// Approaching an obstacle (stationary or driving slower than us).
                		if ((unit.distanceToObstacleOld >= val[0]) && (unit.distanceToObstacle <= val[1])) {
                    			// Check if overtaking shall be started.
                    			unit.stageMeasuring = ControlUnit::FIND_OBJECT_PLAUSIBLE;

                    			cerr << "State is FIND_OBJECT_PLAUSIBLE THIS IS DIFFERENT" << endl;
                		}

                    		unit.distanceToObstacleOld = unit.distanceToObstacle;
			}break;

			case ControlUnit::FIND_OBJECT_PLAUSIBLE: {
				cout<<sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER)<<endl;
                    		if (sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_CENTER) < OVERTAKING_DISTANCE) {
                        
                        		unit.stageMoving = ControlUnit::TO_LEFT_LANE_LEFT_TURN;

                        		cerr << "State is DISABLE" << endl;
                        		// Disable measuring until requested from moving state machine again.
                        		unit.stageMeasuring = ControlUnit::DISABLE;
                    		}else{
                        		unit.stageMeasuring = ControlUnit::FIND_OBJECT;

                        		cerr << "State is FIND_OBJECT" << endl;
                    		}
			}break;

			case ControlUnit::HAVE_BOTH_IR: {
				cerr << "State is HAVE_BOTH_IR" << endl;

                    		// Remain in this stage until both IRs see something.
                    		if ( (sbd.getValueForKey_MapOfDistances(INFRARED_FRONT_RIGHT) < 15) && (sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT) < 20) && 
                                (sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT) > 0) && (sbd.getValueForKey_MapOfDistances(INFRARED_FRONT_RIGHT) > 0)) {
                        		// Turn to right.
                        		unit.stageMoving = ControlUnit::TO_LEFT_LANE_RIGHT_TURN;
                    		}
			}break;

			case ControlUnit::HAVE_BOTH_IR_SAME_DISTANCE: {
				// Remain in this stage until both IRs have the similar distance to obstacle (i.e. turn car)
                    		// and the driven parts of the turn are plausible.


                    		const double IR_FR = sbd.getValueForKey_MapOfDistances(INFRARED_FRONT_RIGHT);
                    		const double IR_RR = sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT);

                    		cerr << "vals: " << fabs(IR_FR - IR_RR) << endl;
                    		cerr << "Counter2: " << (unit.stageToRightLaneLeftTurn - unit.stageToRightLaneRightTurn) << endl;
                    		if ((fabs(IR_FR - IR_RR) < HEADING_PARALLEL) && ((unit.stageToRightLaneLeftTurn - unit.stageToRightLaneRightTurn) > -15)) {
                        		// Straight forward again.
                        		//unit.stageMoving = ControlUnit::CONTINUE_ON_LEFT_LANE;
                        		unit.stageMoving = ControlUnit::FORWARD;
                        		unit.stageMeasuring = ControlUnit::END_OF_OBJECT;
                    		}

			}break;

			case ControlUnit::END_OF_OBJECT: {
				 // Find end of object.
                    		unit.distanceToObstacle = sbd.getValueForKey_MapOfDistances(INFRARED_REAR_RIGHT);
                    		//unit.distanceToObstacleOld = sbd.getValueForKey_MapOfDistances(ULTRASONIC_FRONT_RIGHT);

                    		if (unit.distanceToObstacle < 0 || unit.distanceToObstacle > 25) {
                        		// Move to right lane again.
                        		unit.stageMoving = ControlUnit::TO_RIGHT_LANE_RIGHT_TURN;

					//Set current traveled path to total traveled path
					 currentTraveledPath = vd.getAbsTraveledPath();

                        		// Disable measuring until requested from moving state machine again.
                        		unit.stageMeasuring = ControlUnit::DISABLE;
                    		}

			}break;

			case ControlUnit::DISABLE: {
				//Measuring disabled
			}
		}


                return unit;
        }

        ControlUnit Overtaker::movementStage(ControlUnit unit){

		const double toRightLaneRightTurn = 4; 
		const double toRightLaneLeftTurn = 4;


                Container followerContainer = getKeyValueDataStore().get(automotive::miniature::SteeringData::ID());
                SteeringData sd = followerContainer.getData<SteeringData> ();
                // Create vehicle control data.
                VehicleControl vc;

		//Get most recent vehicle data:
         	Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
         	VehicleData vd = containerVehicleData.getData<VehicleData>();

		//Get most recent sensor board data:
        	Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
        	SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData>();

		//Set AbsTraveledPath data to latest wheel encoder data
		vd.setAbsTraveledPath(sbd.getValueForKey_MapOfDistances(WHEEL_ENCODER));

                // Moving state machine.

		switch(unit.stageMoving){

			case ControlUnit::FORWARD: {
				
				// Go forward.
                    		vc.setSpeed(2.0);
                    		vc.setSteeringWheelAngle(sd.getExampleData());
			}break;

			case ControlUnit::TO_LEFT_LANE_LEFT_TURN: {
				// Move to the left lane: Turn left part until both IRs see something.
                    		vc.setSpeed(1);
                    		vc.setSteeringWheelAngle(LEFT_WHEELANGLE);

                    		// State machine measuring: Both IRs need to see something before leaving this moving state.
                    		unit.stageMeasuring = ControlUnit::HAVE_BOTH_IR;

                    		unit.stageToRightLaneRightTurn++;
			}break;

			case ControlUnit::TO_LEFT_LANE_RIGHT_TURN: {
				// Move to the left lane: Turn right part until both IRs have the same distance to obstacle.
                    		vc.setSpeed(1);
                    		vc.setSteeringWheelAngle(WHEELEANGLE);

                    		// State machine measuring: Both IRs need to have the same distance before leaving this moving state.
                    		unit.stageMeasuring = ControlUnit::HAVE_BOTH_IR_SAME_DISTANCE;

                    		unit.stageToRightLaneLeftTurn++;
			}break;

			case ControlUnit::CONTINUE_ON_LEFT_LANE: {
				// Move to the left lane: Passing stage.
                    		vc.setSpeed(1.5);
                    		vc.setSteeringWheelAngle(sd.getExampleData());

                    		// Find end of object.
                    		unit.stageMeasuring = ControlUnit::END_OF_OBJECT;

			}break;

			case ControlUnit::TO_RIGHT_LANE_RIGHT_TURN: {
				// Move to the right lane: Turn right part.

				if (vd.getAbsTraveledPath() - currentTraveledPath <= toRightLaneRightTurn){
                    			vc.setSpeed(1);
                    			vc.setSteeringWheelAngle(WHEELEANGLE);
				}else{
					unit.stageMoving = ControlUnit::TO_RIGHT_LANE_LEFT_TURN;
					currentTraveledPath = vd.getAbsTraveledPath();
				}

                    		/*unit.stageToRightLaneRightTurn--;

                    		cerr << "Counter: " << unit.stageToRightLaneRightTurn << endl; 
                    		if (unit.stageToRightLaneRightTurn == 20) {
                        	unit.stageMoving = ControlUnit::TO_RIGHT_LANE_LEFT_TURN;*/

			}break;

			case ControlUnit::TO_RIGHT_LANE_LEFT_TURN: {
				// Move to the left lane: Turn left part.
				if (vd.getAbsTraveledPath() - currentTraveledPath <= toRightLaneLeftTurn){
                    			vc.setSpeed(1);
                    			vc.setSteeringWheelAngle(LEFT_WHEELANGLE);

				}else{
					unit.stageMoving = ControlUnit::FORWARD;
					unit.stageMeasuring = ControlUnit::FIND_OBJECT_INIT;
				
					unit.distanceToObstacle = 0;
					unit.distanceToObstacleOld = 0;
					unit.stageToRightLaneLeftTurn = 0;
                        		unit.stageToRightLaneRightTurn = 0;
				}
			}break;
		}
                

                // Create container for finally sending the data.
                
                
               
                    Container c(vc);
                    // Send container.
                    getConference().send(c);

                return unit;

        }

        // This method will do the main data processing job.
        odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode Overtaker::body() {

            ControlUnit unit;

            unit.stageMoving = ControlUnit::FORWARD;
            //unit.stageMeasuring = ControlUnit::DISABLE;
            unit.stageMeasuring = ControlUnit::FIND_OBJECT_INIT;

            cerr << "FIND_OBJECT_INIT" << endl;

            // State counter for dynamically moving back to right lane.
            unit.stageToRightLaneRightTurn = 0;
            unit.stageToRightLaneLeftTurn = 0;

            // Distance variables to ensure we are overtaking only stationary or slowly driving obstacles.
            unit.distanceToObstacle = 0;
            unit.distanceToObstacleOld = 0;

            while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
                
                unit = measureStage(unit);
                unit = movementStage(unit);
                cerr << "State is: " << unit.stageMeasuring << endl;
 

            }

            return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;
        }

    }
} // automotive::miniature
