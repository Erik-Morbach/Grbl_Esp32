#pragma once
// clang-format off

/*
    sevencut_bjm.h
    Part of Grbl_ESP32:BJM

    2021- Erik Morbach

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

#define SELECT_TIMER_0 		  2000 // ms
#define SELECT_TIMER_1		  3000 // ms
#define SELECT_TIMER_2		  4000 // ms
#define SELECT_TIMER_3		  5000 // ms

#define INVERT_ROTATION_PERIOD	  2000 // ms

#define END_OPERATION_PERIOD	  2250 // ms

#define ENCODER_TL 		  750 // ms
#define ENCODER_INPUT             GPIO_NUM_34
#define MACRO_BUTTON_0_PIN 	  GPIO_NUM_35
#define CONTROL_RESET_PIN       GPIO_NUM_21
#define USER_DIGITAL_INPUT_PIN_4  GPIO_NUM_21
#define USER_DIGITAL_INPUT_PIN_5  GPIO_NUM_39
#define USER_DIGITAL_INPUT_PIN_6  GPIO_NUM_36

#ifdef INVERT_CONTROL_PIN_MASK
#   undef INVERT_CONTROL_PIN_MASK
#endif
#define INVERT_CONTROL_PIN_MASK B00000010
#define USER_DIGITAL_INPUT_INVERT_4 1
#define USER_DIGITAL_INPUT_INVERT_5 1
#define USER_DIGITAL_INPUT_INVERT_6 1

#define CUSTOM_CODE_FILENAME "Custom/sevencut.cpp"



