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


//#define PROBE_PIN               GPIO_NUM_32
//#define COOLANT_MIST_PIN        GPIO_NUM_21

#define USER_DIGITAL_PIN_0 GPIO_NUM_26



