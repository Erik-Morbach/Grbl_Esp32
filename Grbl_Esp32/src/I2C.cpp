#include "I2C.h"

#ifdef ENABLE_I2C_PORT
I2C::Module::Module(){
    I2C::i2cPort = DEFAULT_I2C_PORT;
    I2C::config = { 
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE
        //.clk_speed = I2C_MASTER_FREQ_HZ 
    };
    I2C::i2cPortMutex = xSemaphoreCreateMutex();
    this->init();
    xTaskCreate(I2C::updateFunctionExecutionTask,
                "FunctionExecTask",
                4128,
                nullptr,
                1,
                nullptr);
}

void I2C::Module::init(){
    i2c_driver_delete(i2cPort);
    gpio_reset_pin(I2C_MASTER_SDA_IO);
    gpio_reset_pin(I2C_MASTER_SCL_IO);
    gpio_set_direction(I2C_MASTER_SDA_IO,GPIO_MODE_INPUT_OUTPUT);
    gpio_set_direction(I2C_MASTER_SCL_IO,GPIO_MODE_OUTPUT);
    gpio_set_level(I2C_MASTER_SDA_IO,0);
    gpio_set_level(I2C_MASTER_SCL_IO,0);
    i2c_driver_install(I2C::i2cPort,I2C::config.mode,0,0,0);
    i2c_set_data_mode(I2C::i2cPort,I2C_DATA_MODE_MSB_FIRST,I2C_DATA_MODE_MSB_FIRST);
}



void I2C::Module::addDevice(I2C::Device &device){
    this->devices.push_back(&device);
    char name[10];
    sprintf(name,"Device %d",device.deviceAddress);

    xTaskCreate(I2C::updateDeviceTask,
                name,
                4128,
                &device,
                2,
                nullptr);
}

I2C::Device::Device(uint8_t deviceAddress, uint32_t period, uint32_t timeout)
:deviceAddress(deviceAddress), period(period), timeout(timeout){

}

void I2C::Device::addElement(I2C::Device::Element &element){
    this->elements.push_back(&element);
}



I2C::Device::Element::Element(uint8_t registerAddress, i2c_rw_t flag, uint8_t size)
:registerAddress(registerAddress), flag(flag), values(new uint8_t[size]){

}

bool I2C::Device::Element::setValues(uint8_t *values){
    size_t size = sizeof(this->values);
    bool isDiferent = false;
    for(int index = 0;index<size; ++index){
        isDiferent |= (values[index] != this->values[index]);

        this->values[index] = values[index];
    }
    return isDiferent;
}



I2C::Mapper::Mapper(){

}

void I2C::Mapper::write(uint8_t pin, uint8_t value) const{
    value = !(!value);
    uint8_t index = this->mapPin[pin].second>>8;
    uint8_t bitMask = this->mapPin[pin].second%255; 
    this->mapPin[pin].first->values[index] &= ~(bitMask);
    this->mapPin[pin].first->values[index] |= value*bitMask;
}

uint8_t I2C::Mapper::read(uint8_t pin) const{
    uint8_t index = this->mapPin[pin].second>>8;
    uint8_t bitMask = this->mapPin[pin].second%255; 
    return (mapPin[pin].first->values[index]&bitMask) != 0;
}


void I2C::Mapper::bindBit(I2C::Device::Element &element, uint16_t identifier, uint8_t pin){
    mapPin[pin] = {&element,identifier};
}

void I2C::Mapper::bindFunction(I2C::Device::Element &element, void (*updateFunc)(volatile uint8_t*)){
    element.updateFunction = updateFunc;
}








void I2C::updateDeviceTask(void *param){  
    I2C::Device *device = (I2C::Device*) param;
    while(1){
        if(xSemaphoreTake(I2C::i2cPortMutex,portMAX_DELAY)!=pdTRUE)
            continue;
        for(I2C::Device::Element *element: device->elements){
            size_t elementSize = sizeof(element->values);
            uint8_t *data = new uint8_t[elementSize];

            i2c_cmd_handle_t cmd = i2c_cmd_link_create();
            i2c_master_start(cmd);
            i2c_master_write_byte(cmd,(device->deviceAddress<<1)|I2C_MASTER_WRITE,ACK);

            i2c_master_write_byte(cmd,element->registerAddress,ACK);


            if(element->flag==I2C_MASTER_READ){
                i2c_master_start(cmd);
                i2c_master_write_byte(cmd,(device->deviceAddress<<1)|element->flag,ACK);

                i2c_master_read(cmd,data,elementSize,ACK);
            }
            else if(element->flag==I2C_MASTER_WRITE){
                // if Write necessary, copy element->values to data
                for(int index=0;index<elementSize;++index)
                    data[index] = element->values[index];
                i2c_master_write(cmd,data,elementSize,ACK); 
            }
            i2c_master_stop(cmd);
            esp_err_t error = i2c_master_cmd_begin(I2C::i2cPort,cmd,device->timeout / portTICK_PERIOD_MS);
            i2c_cmd_link_delete(cmd);

            if(error==ESP_OK && element->setValues(data))
                xSemaphoreGive(element->doUpdateFunction);
            else 
                I2C::Module::getInstance().init();
        }
        xSemaphoreGive(I2C::i2cPortMutex);
        vTaskDelay(device->period / portTICK_PERIOD_MS);
    }
}

void I2C::updateFunctionExecutionTask(void *param){
    I2C::Module &module = I2C::Module::getInstance();
    // Load minPeriod outside while(1)
    uint32_t minPeriod = portMAX_DELAY;
    for(I2C::Device *currentDevice: module.devices) 
        minPeriod = min(minPeriod, currentDevice->period);

    while(1){
        for(I2C::Device *currentDevice: module.devices){
            for(I2C::Device::Element *currentElement: currentDevice->elements){
                if(xSemaphoreTake(currentElement->doUpdateFunction,0)==pdTRUE
                && currentElement->updateFunction != nullptr){
                    currentElement->updateFunction(currentElement->values);
                }        
            }
        } 
        vTaskDelay(minPeriod/ portTICK_PERIOD_MS);
    }
}
#endif