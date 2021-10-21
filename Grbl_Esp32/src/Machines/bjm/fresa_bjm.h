#pragma once
// clang-format off

/*
    4axis_external_driver.h
    Part of Grbl_ESP32

    Pin assignments for the buildlog.net 4-axis external driver board
    https://github.com/bdring/4_Axis_SPI_CNC

    2018    - Bart Dring
    2020    - Mitch Bradley

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

#define MACHINE_NAME            "Fresa BJM, BJM Machine"

#ifdef N_AXIS
        #undef N_AXIS
#endif
#define N_AXIS 3

#define X_STEP_PIN              GPIO_NUM_17
#define X_DIRECTION_PIN         GPIO_NUM_14
#define Y_STEP_PIN              GPIO_NUM_16
#define Y_DIRECTION_PIN         GPIO_NUM_2
#define Z_STEP_PIN              GPIO_NUM_15
#define Z_DIRECTION_PIN         GPIO_NUM_4

#define X_LIMIT_PIN             GPIO_NUM_39
#define Y_LIMIT_PIN             GPIO_NUM_39
#define Z_LIMIT_PIN             GPIO_NUM_39
//#define CONTROL_RESET_PIN       GPIO_NUM_36


#define USER_DIGITAL_PIN_0 GPIO_NUM_26

#define SPINDLE_TYPE            SpindleType::PWM // only one spindle at a time
#define SPINDLE_OUTPUT_PIN      GPIO_NUM_13
#define SPINDLE_ENABLE_PIN      GPIO_NUM_22


#define USER_DIGITAL_INPUT_PIN_0 GPIO_NUM_33
#define USER_DIGITAL_INPUT_PIN_1 GPIO_NUM_35
#define USER_DIGITAL_INPUT_PIN_2 GPIO_NUM_34
#define USER_DIGITAL_INPUT_PIN_3 GPIO_NUM_21


#define DEFAULT_X_STEPS_PER_MM 200
#define DEFAULT_Y_STEPS_PER_MM 200
#define DEFAULT_Z_STEPS_PER_MM 200

#define DEFAULT_X_MAX_RATE 3000
#define DEFAULT_Y_MAX_RATE 3000
#define DEFAULT_Z_MAX_RATE 3000

#define DEFAULT_X_ACCELERATION 400
#define DEFAULT_Y_ACCELERATION 400
#define DEFAULT_Z_ACCELERATION 400

#define DEFAULT_X_MAX_TRAVEL 327.00
#define DEFAULT_Y_MAX_TRAVEL 420.00
#define DEFAULT_Z_MAX_TRAVEL 111.00

#define DEFAULT_SPINDLE_RPM_MAX 8000
#define DEFAULT_INVERT_SPINDLE_OUTPUT_PIN 1

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
#define DEFAULT_HOMING_CYCLE_2 bit(Y_AXIS)

#define DEFAULT_HOMING_FEED_RATE 50.0
#define DEFAULT_HOMING_SEEK_RATE 1000.0

#ifdef CONTROL_SW_DEBOUNCE_PERIOD
	#undef CONTROL_SW_DEBOUNCE_PERIOD
#endif 
#define CONTROL_SW_DEBOUNCE_PERIOD 500

#define DEFAULT_DIRECTION_INVERT_MASK 0b00001  // $3 uint8_
#define DEFAULT_JUNCTION_DEVIATION 0.01  // $11 mm
#define DEFAULT_SOFT_LIMIT_ENABLE 1 // $20
#define DEFAULT_HOMING_ENABLE 1  // $22 
#define DEFAULT_HOMING_DIR_MASK 0b00000010  // $23 