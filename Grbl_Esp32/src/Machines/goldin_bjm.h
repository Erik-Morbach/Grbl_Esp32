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

#define MACHINE_NAME            "Goldin, Bjm Machine"

#ifdef N_AXIS
        #undef N_AXIS
#endif
#define N_AXIS 3

#define X_STEP_PIN              GPIO_NUM_2
#define X_DIRECTION_PIN         GPIO_NUM_15
#define Z_STEP_PIN              GPIO_NUM_17
#define Z_DIRECTION_PIN         GPIO_NUM_16

#define SPINDLE_TYPE            SpindleType::DAC // only one spindle at a time
#define SPINDLE_OUTPUT_PIN      GPIO_NUM_25
#define SPINDLE_ENABLE_PIN      GPIO_NUM_22


#define X_LIMIT_PIN             GPIO_NUM_34
#define Z_LIMIT_PIN             GPIO_NUM_35

//#define PROBE_PIN               GPIO_NUM_39
#define COOLANT_MIST_PIN        GPIO_NUM_21

#define USER_DIGITAL_PIN_0 GPIO_NUM_26



#ifdef DEFAULT_HOMING_CYCLE_0
	#undef DEFAULT_HOMING_CYCLE_0
#endif
#ifdef DEFAULT_HOMING_CYCLE_1
	#undef DEFAULT_HOMING_CYCLE_1
#endif
#define DEFAULT_HOMING_CYCLE_0 bit(Z_AXIS)
#define DEFAULT_HOMING_CYCLE_1 bit(X_AXIS)
