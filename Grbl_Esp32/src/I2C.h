#pragma once
#include "Grbl.h"
#ifdef ENABLE_I2C_PORT
#include "driver/i2c.h"
#include <list>
#include <utility>

#define MAX_I2C_DEVICES 10

#define ACK I2C_MASTER_ACK
#define NACK I2C_MASTER_NACK
#define DEFAULT_I2C_PORT I2C_NUM_0
#define I2C_MASTER_SDA_IO GPIO_NUM_0
#define I2C_MASTER_SCL_IO GPIO_NUM_22


namespace I2C{
    namespace{
        SemaphoreHandle_t i2cPortMutex;
        i2c_port_t i2cPort; 
        i2c_config_t config;
    }
    void updateDeviceTask(void *param); //Ok 
    void updateFunctionExecutionTask(void *param); // Ok

    class Device{
        public: 
            class Element;

            uint8_t deviceAddress;
            uint32_t period; //ms 
            uint32_t timeout; //ms

            std::list<Element*> elements;

            Device(uint8_t deviceAddress, uint32_t period, uint32_t timeout); // Ok
            void addElement(I2C::Device::Element &element); // Ok


        class Element{
            public:

                uint8_t registerAddress;
                i2c_rw_t flag;
                volatile uint8_t *values;
                Element(uint8_t registerAddress, i2c_rw_t flag, uint8_t size); // Ok

                bool setValues(uint8_t *values); // Ok
                SemaphoreHandle_t doUpdateFunction;     

                void (*updateFunction)(volatile uint8_t* values);
        };
    };


    class Module{
        private:
            Module(); // Ok
        public:
            static Module& getInstance(){
                static Module instance;
                return instance;
            }

            void operator=(Module const&)=delete; 
            Module(Module const&)=delete; 

            std::list<Device*> devices; 

            void init(); // Ok

            void addDevice(Device &device); // ok
    };


    class Mapper{
        private:
            Mapper(); //todo
            std::pair<I2C::Device::Element*,uint16_t> mapPin[256];
        public:
            void operator=(const Mapper&) = delete;
            Mapper(const Mapper &) = delete;

            static Mapper& getInstance(){
                static Mapper mapper;
                return mapper;
            }


            void write(uint8_t pin, uint8_t value) const; //todo

            uint8_t read(uint8_t pin) const; //todo

            void bindBit(I2C::Device::Element &element, uint16_t identifier, uint8_t pin); // todo

            void bindFunction(I2C::Device::Element &element, void (*updateFunc)(volatile uint8_t*)); //todo
    };
}
#endif