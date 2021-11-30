#pragma once
// clang-format off

/*
    lucas_bjm.h
    2021 - Erik Morbach

    Grbl_ESP32 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Grbl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Grbl_ESP32.  If not, see <http://www.gnu.org/licenses/>.
*/


#define MACHINE_NAME            "MetalLogic, Bjm Machine"

#ifdef N_AXIS
        #undef N_AXIS
#endif
#define N_AXIS 5

#define DEFAULT_VELOCITY_SELECTOR true
#define USER_DIGITAL_INPUT_PIN_0 GPIO_NUM_33
#define USER_DIGITAL_INPUT_PIN_1 GPIO_NUM_35
#define DEFAULT_FO_RO_DEPENDENT true

// placa Nova
#define X_STEP_PIN              GPIO_NUM_17
#define X_DIRECTION_PIN         GPIO_NUM_14
#define B_STEP_PIN              GPIO_NUM_16
#define B_DIRECTION_PIN         GPIO_NUM_2
#define Z_STEP_PIN              GPIO_NUM_15
#define Z_DIRECTION_PIN         GPIO_NUM_4

#define DEFAULT_X_STEPS_PER_MM 100
#define DEFAULT_Z_STEPS_PER_MM 200
#define DEFAULT_B_STEPS_PER_MM 100

#define DEFAULT_X_MAX_RATE 10000
#define DEFAULT_Z_MAX_RATE 10000
#define DEFAULT_B_MAX_RATE 5000

#define DEFAULT_X_ACCELERATION 2000
#define DEFAULT_Z_ACCELERATION 2000
#define DEFAULT_B_ACCELERATION 400

#define DEFAULT_X_MAX_TRAVEL 281.500
#define DEFAULT_Z_MAX_TRAVEL 127.000
#define DEFAULT_B_MAX_TRAVEL  79.000

#define SPINDLE_TYPE            SpindleType::_10V// only one spindle at a time
#define SPINDLE_OUTPUT_PIN      GPIO_NUM_25
#define SPINDLE_FORWARD_PIN     GPIO_NUM_26
#define SPINDLE_REVERSE_PIN     GPIO_NUM_22
#define DEFAULT_SPINDLE_RPM_MAX 2000
#define DEFAULT_INVERT_SPINDLE_OUTPUT_PIN 1


#define X_LIMIT_PIN             GPIO_NUM_39
#define Z_LIMIT_PIN             GPIO_NUM_39
#define B_LIMIT_PIN             GPIO_NUM_39


#define CONTROL_FEED_HOLD_PIN   GPIO_NUM_34  // labeled Hold,  needs external pullup
#define CONTROL_CYCLE_START_PIN GPIO_NUM_21  // labeled Start, needs external pullup
#define CONTROL_RESET_PIN       GPIO_NUM_36  // labeled Reset, needs external pullup


#define COOLANT_MIST_PIN        GPIO_NUM_25

#define USER_DIGITAL_PIN_0 GPIO_NUM_13


#ifdef DEFAULT_HOMING_CYCLE_0
	#undef DEFAULT_HOMING_CYCLE_0
#endif
#ifdef DEFAULT_HOMING_CYCLE_1
	#undef DEFAULT_HOMING_CYCLE_1
#endif
#ifdef DEFAULT_HOMING_CYCLE_2
	#undef DEFAULT_HOMING_CYCLE_2
#endif

#define DEFAULT_HOMING_CYCLE_0 bit(Z_AXIS)
#define DEFAULT_HOMING_CYCLE_1 bit(X_AXIS)
#define DEFAULT_HOMING_CYCLE_2 bit(B_AXIS)

#define DEFAULT_HOMING_FEED_RATE 200.0
#define DEFAULT_HOMING_SEEK_RATE 1000.0

#ifdef CONTROL_SW_DEBOUNCE_PERIOD
	#undef CONTROL_SW_DEBOUNCE_PERIOD
#endif 
#define CONTROL_SW_DEBOUNCE_PERIOD 250

#define DEFAULT_DIRECTION_INVERT_MASK 0b00000  // $3 uint8_
#define DEFAULT_JUNCTION_DEVIATION 0.01  // $11 mm
#define DEFAULT_SOFT_LIMIT_ENABLE 1 // $20
#define DEFAULT_HOMING_ENABLE 1  // $22 
#define DEFAULT_HOMING_DIR_MASK 0  // $23 