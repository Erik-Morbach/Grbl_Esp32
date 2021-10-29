/*
  EthernetServices.cpp -  Ethernet services functions class

  Copyright (c) 2014 Luc Lebosse. All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "../Grbl.h"

#ifdef ENABLE_ETHERNET
#    include <WiFi.h>
#    include <EthernetENC.h>
#    include "EthernetServices.h"
#    ifdef ENABLE_TELNET
#        include "TelnetServer.h"
#    endif
#    include "Commands.h"

namespace WebUI {
    EthernetServices ethernet_services;

    EthernetServices::EthernetServices() {}
    EthernetServices::~EthernetServices() { end(); }

    bool EthernetServices::begin() {
        bool no_error = true;
        //Sanity check
        if (Ethernet.hardwareStatus() == EthernetNoHardware) {
            String sen ="Ethernet not found\n";
            grbl_send(CLIENT_ALL, (char*) sen.c_str());
            return false;
        }

        Ethernet.init(GPIO_NUM_5);
        uint8_t macadd[6];
        WiFi.softAPmacAddress(macadd);
        IPAddress testIp;
        testIp.fromString(WebUI::DEFAULT_ET_IP);

        Ethernet.begin(macadd,testIp);
        String sen = Ethernet.localIP().toString() + " --- " + testIp.toString();
        grbl_send(CLIENT_ALL,(char*)sen.c_str()); 

        String h = WebUI::DEFAULT_HOSTNAME;


#    ifdef ENABLE_TELNET
        telnet_server.begin();
#    endif

        return no_error;
    }
    void EthernetServices::end() {
        EthernetServices::begin();
#    ifdef ENABLE_TELNET
        telnet_server.end();
#    endif
    }

    void EthernetServices::handle() {
        COMMANDS::wait(0);
        Ethernet.maintain();
        //to avoid mixed mode due to scan network
#    ifdef ENABLE_TELNET
        telnet_server.handle();
#    endif
    }

}
#endif  // ENABLE_WIFI
