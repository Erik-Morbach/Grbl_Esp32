#include "EthernetConfig.h"

namespace WebUI{
    EthernetConfig ethernet_config;


    EthernetConfig::EthernetConfig() {}
    EthernetConfig::~EthernetConfig() {}

    const char* EthernetConfig::info() {
        static String result;
        String        tmp;
        result = "[MSG:Hardware=";
        switch(Ethernet.hardwareStatus()){
            case EthernetNoHardware: result += "NoHardware"; break;
            case EthernetENC28J60: result += "ENC28J60"; break;
            case EthernetW5100: result += "W5100"; break;
            default: result += "Not Configured"; break;
        }

        if (Ethernet.hardwareStatus()!=EthernetNoHardware) {
            result += ":Status=";
            result += (Ethernet.linkStatus() == LinkON) ? "Connected" : "Not connected";
            result += ":IP=";
            result += Ethernet.localIP().toString();
        }
        result += "]\n";
        return result.c_str();
    }

    void EthernetConfig::begin(){
        ethernet_services.end();
        ethernet_services.begin();
    }

    void EthernetConfig::handle(){
        ethernet_services.handle();
    }
}