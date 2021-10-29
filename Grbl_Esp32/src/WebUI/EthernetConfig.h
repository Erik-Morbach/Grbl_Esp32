#pragma once



#include "WifiConfig.h"
#include "EthernetServices.h"
#include <EthernetENC.h>

namespace WebUI
{
    class EthernetConfig{
    public:
        EthernetConfig();
        static void begin();
        static void end();
        static void handle();

        static const char* info();

        ~EthernetConfig();
    };
    extern EthernetConfig ethernet_config;
    
} // namespace WebUI
