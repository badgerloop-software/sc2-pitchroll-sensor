#ifndef __gyro__h__
#define __gyro__h__
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>

#define LSM6DS3_OUTX_L_G 0X22  //gyroscope
#define LSM6DS3_OUTX_L_XL 0x28 //accelerometer
#define LSM6DS3_OUT_TEMP_L 0x20 //temperature

class LSM6DS3 {
    public:   
        void readRegisters(uint8_t address, uint8_t* data, size_t length);
        
        void readGyroData(float* x, float* y, float* z);        
        void readAccelData(float* x, float* y, float* z);
        void readTempData(float* t);
};



#endif