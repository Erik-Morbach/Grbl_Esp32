/*
	custom_code_template.cpp (copy and use your machine name)
	Part of Grbl_ESP32

	copyright (c) 2020 -	Bart Dring. This file was intended for use on the ESP32

  ...add your date and name here.

	CPU. Do not use this with Grbl for atMega328P

	Grbl_ESP32 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Grbl_ESP32 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Grbl.  If not, see <http://www.gnu.org/licenses/>.

	=======================================================================

This is a template for user-defined C++ code functions.  Grbl can be
configured to call some optional functions. These functions have weak definitions
in the main code. If you create your own version they will be used instead

Put all of your functions in a .cpp file in the "Custom" folder.
Add this to your machine definition file
#define CUSTOM_CODE_FILENAME    "../Custom/YourFile.cpp" 

Be careful to return the correct values

===============================================================================

Below are all the current weak function

*/

void machine_init(){
	pinMode(FEED_OVERRIDE_BIT1_PIN,INPUT);
	pinMode(FEED_OVERRIDE_BIT2_PIN,INPUT);
}

void update_feedrate_override() {
	uint8_t value = digitalRead(FEED_OVERRIDE_BIT1_PIN) + digitalRead(FEED_OVERRIDE_BIT2_PIN)*2;	
	sys_rt_f_override = 
	sys_rt_r_override = (value==1)*25 + (value==2)*75 + (value==3)*100;
}

