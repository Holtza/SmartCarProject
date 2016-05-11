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

#ifndef ALTERNATIVEPARKER_H_
#define ALTERNATIVEPARKER_H_

#include "opendavinci/odcore/base/module/TimeTriggeredConferenceClientModule.h"

struct ControlUnit{

    enum StateMachineMoving { FORWARD, FRONT_ALIGN, FRONT_LEFT, PREP_REVERSE, REVERSE, BACKWARDS_LEFT, ADJUST, STOP };
    enum StateMachineMeasuring { DETECT_OBSTACLE, MEASURE_SIDE, MEASURE_BACK, DISABLE };

    StateMachineMoving stageMoving;
    StateMachineMeasuring stageMeasuring;

};

namespace automotive {
    namespace miniature {

        using namespace std;

        /**
         * This class is a skeleton to send driving commands to Hesperia-light's vehicle driving dynamics simulation.
         */
        class AlternativeParker : public odcore::base::module::TimeTriggeredConferenceClientModule {
            private:
                /**
                 * "Forbidden" copy constructor. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the copy constructor.
                 *
                 * @param obj Reference to an object of this class.
                 */
                AlternativeParker(const AlternativeParker &/*obj*/);

                /**
                 * "Forbidden" assignment operator. Goal: The compiler should warn
                 * already at compile time for unwanted bugs caused by any misuse
                 * of the assignment operator.
                 *
                 * @param obj Reference to an object of this class.
                 * @return Reference to this instance.
                 */
                AlternativeParker& operator=(const AlternativeParker &/*obj*/);

            public:
                /**
                 * Constructor.
                 *
                 * @param argc Number of command line arguments.
                 * @param argv Command line arguments.
                 */
                AlternativeParker(const int32_t &argc, char **argv);

                virtual ~AlternativeParker();

                odcore::data::dmcp::ModuleExitCodeMessage::ModuleExitCode body();

            private:

		ControlUnit measureStage(ControlUnit unit);
                ControlUnit movementStage(ControlUnit unit);

                virtual void setUp();

                virtual void tearDown();
        };

    }
} // automotive::miniature

#endif /*ALTERNATIVEPARKER_H_*/
