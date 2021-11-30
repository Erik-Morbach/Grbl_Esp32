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
#include "src/Grbl.h"
volatile unsigned long lastEncoderChange;
SemaphoreHandle_t macroMutex;
constexpr char tag[10] = "message";
void IRAM_ATTR encoderRead(){
	lastEncoderChange = millis();	
}
/*
This function is used as a one time setup for your machine.
*/
void machine_init() {
	pinMode(ENCODER_INPUT,INPUT);
	attachInterrupt(digitalPinToInterrupt(ENCODER_INPUT),encoderRead,CHANGE);
	lastEncoderChange = millis();
	client_write(CLIENT_SERIAL,"SEVENCUT INIT\n");
	macroMutex = xSemaphoreCreateMutex();

	esp_log_level_set(tag,ESP_LOG_VERBOSE);
}

/*
This is used to initialize a display.
*/
void display_init() {}

/*
  limitsCheckTravel() is called to check soft limits
  It returns true if the motion is outside the limit values
bool limitsCheckTravel() {
    return false;
}
*/

/*
  user_defined_homing(uint8_t cycle_mask) is called at the begining of the normal Grbl_ESP32 homing
  sequence.  If user_defined_homing(uint8_t cycle_mask) returns false, the rest of normal Grbl_ESP32
  homing is skipped if it returns false, other normal homing continues.  For
  example, if you need to manually prep the machine for homing, you could implement
  user_defined_homing(uint8_t cycle_mask) to wait for some button to be pressed, then return true.
bool user_defined_homing(uint8_t cycle_mask) {
    // True = done with homing, false = continue with normal Grbl_ESP32 homing
    return true;
}
*/

/*
  Inverse Kinematics converts X,Y,Z cartesian coordinate to the steps
  on your "joint" motors.  It requires the following three functions:
*/

/*
  cartesian_to_motors() converts from cartesian coordinates to motor space.

  Grbl_ESP32 processes arcs by converting them into tiny little line segments.
  Kinematics in Grbl_ESP32 works the same way. Search for this function across
  Grbl_ESP32 for examples. You are basically converting cartesian X,Y,Z... targets to

    target = an N_AXIS array of target positions (where the move is supposed to go)
    pl_data = planner data (see the definition of this type to see what it is)
    position = an N_AXIS array of where the machine is starting from for this move
bool cartesian_to_motors(float* target, plan_line_data_t* pl_data, float* position) {
    // this simply moves to the target. Replace with your kinematics.
    return mc_line(target, pl_data);
}
*/

/*
  kinematics_pre_homing() is called before normal homing
  You can use it to do special homing or just to set stuff up

  cycle_mask is a bit mask of the axes being homed this time.
bool kinematics_pre_homing(uint8_t cycle_mask) {
    return false;  // finish normal homing cycle
}
*/

/*
  kinematics_post_homing() is called at the end of normal homing
void kinematics_post_homing() {}
*/

/*
  The status command uses motors_to_cartesian() to convert
  your motor positions to cartesian X,Y,Z... coordinates.

  Convert the N_AXIS array of motor positions to cartesian in your code.
void motors_to_cartesian(float* cartesian, float* motors, int n_axis) {
    // position[X_AXIS] =
    // position[Y_AXIS] =
}
*/

/*
  user_tool_change() is called when tool change gcode is received,
  to perform appropriate actions for your machine.
*/
void user_tool_change(uint8_t new_tool) {}

/*
  options.  user_defined_macro() is called with the button number to
  perform whatever actions you choose.
*/
void codeSend(std::string code){
	gc_execute_line(&code.front(),CLIENT_SERIAL);	
}
bool checkSystem(){
	static constexpr uint8_t mask = (1<<4)|(1<<5)|(1<<6);
	uint8_t digitalInput = sys_get_digital_inputs();
	if(digitalInput&mask){
		String tmp = "Reset!\n";
		client_write(CLIENT_SERIAL,(char*)tmp.c_str());
		return true;
	}
	return false;
}
void endProcess(){
	codeSend("M5");
	sys_digital_all_off();
	xSemaphoreGive(macroMutex);
}
bool wait(uint32_t waitTime){
	int blocks = pdMS_TO_TICKS(100);
	uint32_t accumulator = 0;
	while(accumulator<waitTime){
		if(checkSystem()) 
			return false;
		if(accumulator + 100 > waitTime) blocks = pdMS_TO_TICKS(waitTime%100);
		vTaskDelay(blocks);
		accumulator += 100;
	}
	return true;
}
void user_defined_macro(uint8_t index) {
	if(xSemaphoreTake(macroMutex,0)!=pdTRUE) return;
	char msg[30] = "Macro  \n";
	msg[6] = index + '0';
	client_write(CLIENT_SERIAL,msg);
	uint16_t waitTime = 0;
	const std::vector<std::pair<uint8_t,uint16_t>> list{
		{USER_DIGITAL_INPUT_PIN_0,SELECT_TIMER_0},
		{USER_DIGITAL_INPUT_PIN_1,SELECT_TIMER_1},
		{USER_DIGITAL_INPUT_PIN_2,SELECT_TIMER_2},
		{USER_DIGITAL_INPUT_PIN_3,SELECT_TIMER_3}};
	for(auto pinnPower: list){
		waitTime += pinnPower.second*(digitalRead(pinnPower.first)^1);
		if(waitTime) break;
	}

	sprintf(msg, "1° %d\n",waitTime);
	client_write(CLIENT_SERIAL,msg);
	sys.state = State::Idle;

	if(checkSystem()) {
		endProcess();
		return;
	}
	codeSend("M3S800");
	codeSend("M62P0");
	client_write(CLIENT_SERIAL,"Wait!\n");
	if(!wait(waitTime)){
		endProcess();
		return;
	}
	client_write(CLIENT_SERIAL,"Go!\n");
	codeSend("M4S3500");
	if(!wait(INVERT_ROTATION_PERIOD)){
		endProcess();
		return;
	}
	codeSend("M62P1");
	if(checkSystem()) {
		endProcess();
		return;
	}
	wait(300);

	client_write(CLIENT_SERIAL,"Encoder!\n");
	while((millis()-lastEncoderChange)<=ENCODER_TL){
		if(checkSystem()) {
			endProcess();
			return;
		}
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	client_write(CLIENT_SERIAL,"End!\n");
	wait(END_OPERATION_PERIOD);
	endProcess();
}

/*
  user_m30() is called when an M30 gcode signals the end of a gcode file.
*/
void user_m30() {}

// If you add any additional functions specific to your machine that
// require calls from common code, guard their calls in the common code with
// #ifdef USE_WHATEVER and add function prototypes (also guarded) to grbl.h
//
