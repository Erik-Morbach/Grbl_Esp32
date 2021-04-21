#include "TecoL510.h"

/*
    TecoL510.cpp

    Part of Grbl_ESP32
    2021 -  Jesse Schoch

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

                         WARNING!!!!
    VFDs are very dangerous. They have high voltages and are very powerful
    Remove power before changing bits.

    See TecoL510.md for details
*/

namespace Spindles {
    L510::L510() : VFD() {
        _baudrate = 9600;
        _parity   = Uart::Parity::None;
        _max_rpm = 24000;
        _max_freq = 40000;
    }

    void L510::direction_command(SpindleState mode, ModbusCommand& data) {
        // NOTE: data length is excluding the CRC16 checksum.
        data.tx_length = 6;
        data.rx_length = 6;

        data.msg[1] = 0x06;  // WRITE
        data.msg[2] = 0x25;  // Command ID 0x2501
        data.msg[3] = 0x01;
        data.msg[4] = 0x01;
        if(mode == SpindleState::Ccw){
            data.msg[5] = 1;
        }else{
            data.msg[5] = 0;
        }
        grbl_msg_sendf(CLIENT_SERIAL,MsgLevel::Info,"sending dir: state:  %d",mode;
    }

    void L510::start_command(ModbusCommand& data){
        data.tx_length = 6;
        data.rx_length = 6;
        data.msg[1] = 0x06;
        data.msg[2] = 0x25;
        data.msg[3] = 0x01;
        data.msg[4] = 0x00;
        data.msg[5] = 0x01;

    }

    void L510::set_speed_command(uint32_t rpm, ModbusCommand& data) {

                // NOTE: data length is excluding the CRC16 checksum.
        data.tx_length = 6;
        data.rx_length = 6;

        // We have to know the max RPM before we can set the current RPM:
        auto max_rpm = this->_max_rpm;
        auto max_freq = this->_max_freq;

        // Assuming max frequncy is 400Hz
        // Speed is in [0..40,000] 
        uint16_t speed = (uint16_t(rpm) * max_freq) / uint32_t(max_rpm);
        if (speed < 0) {
            speed = 0;
        }
        if (speed > 40000) {
            speed = 40000;
        }

        data.msg[1] = 0x06;  // WRITE
        data.msg[2] = 0x25;  // Command ID 0x2502
        data.msg[3] = 0x02;
        data.msg[4] = uint8_t(speed >> 8);  // RPM
        data.msg[5] = uint8_t(speed & 0xFF);

        grbl_msg_sendf(CLIENT_SERIAL,MsgLevel::Info,"setting speed to: %d",speed);
    }
    uint16_t L510::rpm_to_frequency(uint32_t rpm){
        auto max_rpm = this->_max_rpm;
        uint16_t freq = (uint32_t(rpm) * 40000L) / uint32_t(max_rpm);
        return freq;
    }

    uint32_t L510::freq_to_rpm(uint16_t freq){
        auto max_rpm = this->_max_rpm;
        auto max_freq = this->_max_freq;
        uint32_t rpm = (freq/max_freq)/max_rpm;
    }

    VFD::response_parser L510::initialization_sequence(int index, ModbusCommand& data) {
        if (index == -1) {
            // NOTE: data length is excluding the CRC16 checksum.
            data.tx_length = 6;
            data.rx_length = 5;

            
            // Send: 
            data.msg[1] = 0x03;  // READ
            data.msg[2] = 0x02;  // 0x0203 = Get RPM
            data.msg[3] = 0x03;
            data.msg[4] = 0x00;  // Read 1 value
            data.msg[5] = 0x01;
            
            /*
           // Hack to see if a known working register can be read
           data.msg[1] = 0x03;  // READ
            data.msg[2] = 0x25;  // 0x2523 = Get RPM
            data.msg[3] = 0x23;
            data.msg[4] = 0x00;  // Read 1 value
            data.msg[5] = 0x01;
            */


            //  Recv: ??

            return [](const uint8_t* response, Spindles::VFD* vfd) -> bool {
                //uint16_t rpm  = (uint16_t(response[4]) << 8) | uint16_t(response[5]);
                //TODO remove hardcoding
                //vfd->_max_rpm = rpm;
                vfd->_max_rpm = 24000;

                grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "L510 spindle hardcoded 24000 %d ", vfd->_max_rpm);

                return true;
            };
        } else {
            return nullptr;
        }
    }

    VFD::response_parser L510::get_current_rpm(ModbusCommand& data) {
        // NOTE: data length is excluding the CRC16 checksum.
        data.tx_length = 6;
        data.rx_length = 5;

        // Send: 01 03 700C 0002
        data.msg[1] = 0x03;  // READ
        data.msg[2] = 0x25;  // 0x2523 = Get RPM
        data.msg[3] = 0x23;
        data.msg[4] = 0x00;  // Read 1 value
        data.msg[5] = 0x01;

        return [](const uint8_t* response, Spindles::VFD* vfd) -> bool {
            uint16_t freq = (response[3] << 8) | response[4];
            grbl_msg_sendf(CLIENT_SERIAL,MsgLevel::Info,"current frequency: %d",freq);

            // Set current RPM value? Somewhere?
            //vfd->_sync_rpm = vfd->freq_to_rpm(freq);

            //TODO: how do get access to the object I was in before wandering into this lambda?
            // undo hardcoded garbage
            vfd->_sync_rpm = (freq/40000)*24000;
            return true;
        };
    }

    VFD::response_parser L510::get_current_direction(ModbusCommand& data) {
        // NOTE: data length is excluding the CRC16 checksum.
        data.tx_length = 6;
        data.rx_length = 6;

        // Send: 01 03 30 00 00 01
        data.msg[1] = 0x03;  // READ
        data.msg[2] = 0x25;  // 0x2520
        data.msg[3] = 0x20;
        data.msg[4] = 0x00;  // Message ID
        data.msg[5] = 0x01;

        // Receive: 01 03 00 02 00 02
        //                      ----- status

        // TODO: this doesn't seem to do anything in H2A
        return [](const uint8_t* response, Spindles::VFD* vfd) -> bool { 
            uint16_t got = (uint16_t(response[4]) << 8) | uint16_t(response[5]);
            bool dir = bitRead(got,1);
            grbl_msg_sendf(CLIENT_SERIAL, MsgLevel::Info, "L510 dir %d", int(dir));
            return true; 
            };
    }
}