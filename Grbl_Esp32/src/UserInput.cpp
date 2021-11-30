#include "UserInput.h"
/*
	UserInput.cpp

	Part of Grbl_ESP32: BJM

	2021 -	Erik Morbach

	Grbl is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.
	Grbl is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	You should have received a copy of the GNU General Public License
	along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
 */

namespace UserInput{
	DigitalInput::DigitalInput(){}

	DigitalInput::DigitalInput(uint8_t number, uint8_t pin,bool invert):
		_number(number), _pin(pin),_invert(invert)
	{
		if(this->_pin==UNDEFINED_PIN) 
			return;
		this->init();
	}

	bool DigitalInput::get(){
		if(_pin==UNDEFINED_PIN) return false;
		return digitalRead(_pin) ^ this->_invert;
	}

	void DigitalInput::init(){
		pinMode(this->_pin,INPUT_PULLDOWN);

		this->config_message();
	}

	void DigitalInput::config_message(){
		grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "User Digital Input:%d on Pin:%s", _number, pinName(_pin).c_str());
	}
};
