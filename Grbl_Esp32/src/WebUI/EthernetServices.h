#pragma once

namespace WebUI {
    class EthernetServices {
    public:
        EthernetServices();

        static bool begin();
        static void end();
        static void handle();

        ~EthernetServices();
    };

    extern EthernetServices ethernet_services;


}
