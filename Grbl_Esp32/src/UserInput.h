#pragma once
/*
	UserInput.h

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
 
#include "Grbl.h"


namespace UserInput{
	class DigitalInput {
		public:
			DigitalInput();
			DigitalInput(uint8_t number, uint8_t pin, bool invert=false);

			bool get();
		protected:
			void init();
			void config_message();

			uint8_t _number = UNDEFINED_PIN;
			uint8_t _pin 	= UNDEFINED_PIN;
			bool _invert = false;
	};
	class AnalogInput {
		// TODO
	};
};

