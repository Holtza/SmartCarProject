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

	
	double currentTraveledPath;
	int counter = 0;
	const int32_t WHEEL_ENCODER = 5;
	


SidewaysParker::SidewaysParker(const int32_t& argc,
        char** argv)
        : TimeTriggeredConferenceClientModule(argc, argv, "SidewaysParker"){}
    
SidewaysParker::~SidewaysParker(){}

// This method will be call automatically _before_ running body()
void SidewaysParker::setUp(){}

// This method will be call automatically _after_ return from body().
void SidewaysParker::tearDown(){}


// This method will do the main data processing job.
odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode
SidewaysParker::body(){

	ControlUnit unit;

	unit.stageMoving = ControlUnit::FORWARD;
	unit.stageMeasuring = ControlUnit::DETECT_OBSTACLE;
	
	while (getModuleStateAndWaitForRemainingTimeInTimeslice() == odcore::data::dmcp::ModuleStateMessage::RUNNING) {
	            
                unit = measureStage(unit);
                unit = movementStage(unit);

	}

	return odcore::data::dmcp::ModuleExitCodeMessage::OKAY;

}//end body

//Measuring state machine
ControlUnit SidewaysParker::measureStage(ControlUnit unit){

	cerr << "Measure stage: " << unit.stageMeasuring << endl;

	
        const int32_t IR_REAR_RIGHT = 2;
	const int32_t IR_REAR = 3;//????

	//Measurement variables go here:
	const double carSize = 1.5;
	const double minSpaceWidth = 25;
	const double minSpaceLength = carSize * 2;
	const int noiseAllowance = 2;
	const int backSafeDist = 3; //in cm (value from IR sensor)
	

	//Get most recent vehicle data:
            Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
            VehicleData vd = containerVehicleData.getData<VehicleData>();

	//Get most recent sensor board data:
            Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
            SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData>();

	//Set AbsTraveledPath data to latest wheel encoder data
	    vd.setAbsTraveledPath(sbd.getValueForKey_MapOfDistances(WHEEL_ENCODER));

	cerr << "WHEEL ENCODER DATA: " << sbd.getValueForKey_MapOfDistances(WHEEL_ENCODER) << endl;
	cerr << "ABS_TRAVELED_PATH: " << vd.getAbsTraveledPath() << endl;


	switch(unit.stageMeasuring) {

		//Controlling if there is an obstacle
		case ControlUnit::DETECT_OBSTACLE: {
			//If no obstacle is detected, start MEASURING stage
			if (sbd.getValueForKey_MapOfDistances(IR_REAR_RIGHT) < 0 || sbd.getValueForKey_MapOfDistances(IR_REAR_RIGHT) > minSpaceWidth) {
                    		unit.stageMeasuring = ControlUnit::MEASURING;
                    		currentTraveledPath = vd.getAbsTraveledPath();
			}
		}break;

		//Measure empty space
		case ControlUnit::MEASURING: {
			//If obstacle is encountered, go back to detecting obstacle state
			if ((sbd.getValueForKey_MapOfDistances(IR_REAR_RIGHT) > -1 && sbd.getValueForKey_MapOfDistances(IR_REAR_RIGHT) < minSpaceWidth)
			     && (counter > noiseAllowance)) {
                    		unit.stageMeasuring = ControlUnit::DETECT_OBSTACLE;
			//Account for noise
			}else if (sbd.getValueForKey_MapOfDistances(IR_REAR_RIGHT) > -1 && sbd.getValueForKey_MapOfDistances(IR_REAR_RIGHT) < minSpaceWidth){
				counter++;
			//If the space is big enough
                	}else if (vd.getAbsTraveledPath() - currentTraveledPath >= minSpaceLength) {
				unit.stageMeasuring = ControlUnit::DISABLE;
				unit.stageMoving = ControlUnit::PREP_REVERSE;
				counter = 0; //reset for next use
			}
                }break;

		case ControlUnit::MEASURE_BACK: {
			if (sbd.getValueForKey_MapOfDistances(IR_REAR) <= backSafeDist && sbd.getValueForKey_MapOfDistances(IR_REAR) > -1){
				unit.stageMoving = ControlUnit::ALIGNING;
				unit.stageMeasuring = ControlUnit::DISABLE;
			}
		}break;
		
		//Stop measuring
		case ControlUnit::DISABLE: {
			//Measuring disabled
		}

	}//end switch

	return unit;

}//end measureStage

//Moving state machine
ControlUnit SidewaysParker::movementStage(ControlUnit unit){

	cerr << "Movement stage: " << unit.stageMoving << endl;

	Container followerContainer = getKeyValueDataStore().get(automotive::miniature::SteeringData::ID());
        SteeringData sd = followerContainer.getData<SteeringData> ();
	
	//Get most recent vehicle data:
         Container containerVehicleData = getKeyValueDataStore().get(automotive::VehicleData::ID());
         VehicleData vd = containerVehicleData.getData<VehicleData>();

        // Create vehicle control data.
        VehicleControl vc;

	//Get most recent sensor board data:
        Container containerSensorBoardData = getKeyValueDataStore().get(automotive::miniature::SensorBoardData::ID());
        SensorBoardData sbd = containerSensorBoardData.getData<SensorBoardData>();

	//Set AbsTraveledPath data to latest wheel encoder data
	vd.setAbsTraveledPath(sbd.getValueForKey_MapOfDistances(WHEEL_ENCODER));
	cerr << "WHEEL ENCODER DATA: " << sbd.getValueForKey_MapOfDistances(WHEEL_ENCODER) << endl;
	cerr << "ABS_TRAVELED_PATH: " << vd.getAbsTraveledPath() << endl;

	//Distances moved during the stages
	const double reverseSpeed = -1;
	const double backRight = 4.0;
	const double reverse = 2.5;
	const double backLeft = 3.2;
	const double align = 1;


	switch(unit.stageMoving){

		//Go forward while looking for parking space
		case ControlUnit::FORWARD: {
			vc.setSpeed(1.5);
                	vc.setSteeringWheelAngle(0);
		}break;

		//Prepare for reverse movement (halt)
		case ControlUnit::PREP_REVERSE: {
			counter++;
                	vc.setSpeed(0);
			//If enough time has passed, enter next state
                	if (counter >= 30) {
                    		unit.stageMoving = ControlUnit::BACKWARDS_RIGHT;
				currentTraveledPath = vd.getAbsTraveledPath();
                	}
		}break;

		//Go back right
		case ControlUnit::BACKWARDS_RIGHT: {
			//Move until the vehicle has moved the desired distance
			if (vd.getAbsTraveledPath() - currentTraveledPath <= backRight) {
                    		vc.setSpeed(reverseSpeed);
                    		vc.setSteeringWheelAngle(25);
                	}else{
                    		vc.setSpeed(0);
                    		unit.stageMoving = ControlUnit::REVERSE;
				currentTraveledPath = vd.getAbsTraveledPath();
                	}
		}break;

		//Go straight back
		case ControlUnit::REVERSE: {
			//Move until the vehicle has moved the desired distance
			if (vd.getAbsTraveledPath() - currentTraveledPath <= reverse) {
				vc.setSpeed(reverseSpeed);
				vc.setSteeringWheelAngle(0);
			}else{
				vc.setSpeed(0);
				unit.stageMoving = ControlUnit::BACKWARDS_LEFT;
				currentTraveledPath = vd.getAbsTraveledPath();
			}
		}break;

		//Go back left
		case ControlUnit::BACKWARDS_LEFT: {
			//Move until the vehicle is close to the back obstacle
			unit.stageMeasuring = ControlUnit::MEASURE_BACK;
			//Or until the vehicle has moved the desired distance
                	if (vd.getAbsTraveledPath() - currentTraveledPath <= backLeft) {
				vc.setSpeed(reverseSpeed);
                		vc.setSteeringWheelAngle(-25);
			}else{
				unit.stageMoving = ControlUnit::ALIGNING;
				unit.stageMeasuring = ControlUnit::DISABLE;
				currentTraveledPath = vd.getAbsTraveledPath();
			}
		}break;

		//Go forward slightly
		case ControlUnit::ALIGNING: {

			//Move until the vehicle has moved the desired distance
			if (vd.getAbsTraveledPath() - currentTraveledPath <= align){
				vc.setSteeringWheelAngle(0);
				vc.setSpeed(0.5);
			}else{
				unit.stageMoving = ControlUnit::STOPPING;
				currentTraveledPath = vd.getAbsTraveledPath();
			}
				
		}break;

		//Stop
		case ControlUnit::STOPPING: {
			vc.setSpeed(0);
		}break;

	}//end switch

	Container c(vc);
        // Send container.
        getConference().send(c);

        return unit;

}//end movementStage
			

}//end miniature
}//end automotive
