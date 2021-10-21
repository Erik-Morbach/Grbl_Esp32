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
#define MACHINE_NAME            "sevencut, BJM Machine"

#ifdef N_AXIS
        #undef N_AXIS
#endif
#define N_AXIS 3

#define SPINDLE_TYPE            SpindleType::PWM // only one spindle at a time
#define SPINDLE_DIR_PIN 	GPIO_NUM_15
#define SPINDLE_OUTPUT_PIN      GPIO_NUM_25
#define SPINDLE_CW_PIN	 	GPIO_NUM_22
#define SPINDLE_CCW_PIN		GPIO_NUM_26


#define USER_DIGITAL_PIN_0 GPIO_NUM_15
#define USER_DIGITAL_PIN_1 GPIO_NUM_2

#define USER_DIGITAL_INPUT_PIN_0  GPIO_NUM_32
#define USER_DIGITAL_INPUT_PIN_1  GPIO_NUM_33
#define USER_DIGITAL_INPUT_PIN_2  GPIO_NUM_27
#define USER_DIGITAL_INPUT_PIN_3  GPIO_NUM_13

#define SELECT_TIMER_0 		  2
#define SELECT_TIMER_1		  3
#define SELECT_TIMER_2		  4
#define SELECT_TIMER_3		  5

#define INVERT_ROTATION_PERIOD	  2

#define END_OPERATION_PERIOD	  2.25

#define ENCODER_TL 		  750
#define ENCODER_INPUT             GPIO_NUM_34
#define MACRO_BUTTON_0_PIN 	  GPIO_NUM_35
#define MACRO_BUTTON_1_PIN	  GPIO_NUM_36

#define CUSTOM_CODE_FILENAME "Custom/sevencut.cpp"



