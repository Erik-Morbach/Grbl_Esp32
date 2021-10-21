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

#define MACHINE_NAME            "Insui, BJM Machine"

#ifdef N_AXIS
        #undef N_AXIS
#endif
#define N_AXIS 6

#define X_STEP_PIN              GPIO_NUM_2
#define X_DIRECTION_PIN         GPIO_NUM_15
#define Y_STEP_PIN              GPIO_NUM_4
#define Y_DIRECTION_PIN         GPIO_NUM_0
#define Z_STEP_PIN              GPIO_NUM_17
#define Z_DIRECTION_PIN         GPIO_NUM_16
#define A_STEP_PIN              GPIO_NUM_12
#define A_DIRECTION_PIN         GPIO_NUM_13
#define B_STEP_PIN              GPIO_NUM_27
#define B_DIRECTION_PIN         GPIO_NUM_14
#define C_STEP_PIN              GPIO_NUM_32
#define C_DIRECTION_PIN         GPIO_NUM_33


#define SPINDLE_TYPE            SpindleType::PWM // only one spindle at a time
#define SPINDLE_OUTPUT_PIN      GPIO_NUM_25
#define SPINDLE_ENABLE_PIN      GPIO_NUM_22


#define X_LIMIT_PIN             GPIO_NUM_36
#define Y_LIMIT_PIN             GPIO_NUM_36
#define Z_LIMIT_PIN             GPIO_NUM_36
#define A_LIMIT_PIN             GPIO_NUM_36
#define B_LIMIT_PIN             GPIO_NUM_36
#define C_LIMIT_PIN             GPIO_NUM_36

#define USER_DIGITAL_PIN_0 GPIO_NUM_26


#define DEFAULT_VELOCITY_SELECTOR false
#define DEFAULT_FO_RO_DEPENDENT false

#define DEFAULT_X_STEPS_PER_MM 200
#define DEFAULT_Y_STEPS_PER_MM 200
#define DEFAULT_Z_STEPS_PER_MM 200
#define DEFAULT_A_STEPS_PER_MM 200
#define DEFAULT_B_STEPS_PER_MM 200
#define DEFAULT_C_STEPS_PER_MM 200

#define DEFAULT_X_MAX_RATE 2500
#define DEFAULT_Y_MAX_RATE 2500
#define DEFAULT_Z_MAX_RATE 2500
#define DEFAULT_A_MAX_RATE 2500
#define DEFAULT_B_MAX_RATE 2500
#define DEFAULT_C_MAX_RATE 2500

#define DEFAULT_X_ACCELERATION 400
#define DEFAULT_Y_ACCELERATION 400
#define DEFAULT_Z_ACCELERATION 400
#define DEFAULT_A_ACCELERATION 400
#define DEFAULT_B_ACCELERATION 400
#define DEFAULT_C_ACCELERATION 400

#define DEFAULT_X_MAX_TRAVEL 400.0
#define DEFAULT_Y_MAX_TRAVEL 495.4
#define DEFAULT_Z_MAX_TRAVEL 106.5
#define DEFAULT_A_MAX_TRAVEL 106.5
#define DEFAULT_B_MAX_TRAVEL 106.5
#define DEFAULT_C_MAX_TRAVEL 106.5


#define DEFAULT_SPINDLE_RPM_MAX 18000.0  // rpm
#define DEFAULT_SPINDLE_FREQ 5000.0  // $33 Hz (extended set)
#define DEFAULT_INVERT_SPINDLE_OUTPUT_PIN 1

#define DEFAULT_STATUS_REPORT_MASK 1  // $10
#define DEFAULT_REPORT_INCHES 0  // $13 false

#define DEFAULT_DIRECTION_INVERT_MASK 0b000001  // $3 uint8_
#define DEFAULT_JUNCTION_DEVIATION 0.01  // $11 mm
#define DEFAULT_SOFT_LIMIT_ENABLE 1 // $20
#define DEFAULT_HOMING_ENABLE 1  // $22 
#define DEFAULT_HOMING_DIR_MASK 0b000001  // $23 
#define DEFAULT_HOMING_DEBOUNCE_DELAY 250  // $26 msec (0-65k)
#define DEFAULT_HOMING_PULLOFF 4.0  // $27 mm


#define DEFAULT_HOMING_FEED_RATE 200.0
#define DEFAULT_HOMING_SEEK_RATE 700.0

#ifdef DEFAULT_HOMING_CYCLE_0
	#undef DEFAULT_HOMING_CYCLE_0
#endif
#ifdef DEFAULT_HOMING_CYCLE_1
	#undef DEFAULT_HOMING_CYCLE_1
#endif
#ifdef DEFAULT_HOMING_CYCLE_2
	#undef DEFAULT_HOMING_CYCLE_2
#endif
#ifdef DEFAULT_HOMING_CYCLE_3
	#undef DEFAULT_HOMING_CYCLE_3
#endif
#ifdef DEFAULT_HOMING_CYCLE_4
	#undef DEFAULT_HOMING_CYCLE_4
#endif
#ifdef DEFAULT_HOMING_CYCLE_5
	#undef DEFAULT_HOMING_CYCLE_5
#endif

#define DEFAULT_HOMING_CYCLE_0 bit(Z_AXIS)
#define DEFAULT_HOMING_CYCLE_1 bit(A_AXIS)
#define DEFAULT_HOMING_CYCLE_2 bit(B_AXIS)
#define DEFAULT_HOMING_CYCLE_3 bit(C_AXIS)
#define DEFAULT_HOMING_CYCLE_4 bit(Y_AXIS)
#define DEFAULT_HOMING_CYCLE_5 bit(X_AXIS)

#ifdef CONTROL_SW_DEBOUNCE_PERIOD
	#undef CONTROL_SW_DEBOUNCE_PERIOD
#endif 
#define CONTROL_SW_DEBOUNCE_PERIOD 250