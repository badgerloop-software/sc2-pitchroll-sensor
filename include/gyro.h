#ifndef __gyro__h__
#define __gyro__h__
#include <SPI.h>
#include <Arduino.h>

#define LSM6S3_WHO_AM_I 0x0F

#define LSM6DS3_OUTX_L_G 0X22  //Angular rate sensor pitch axis (X) angular rate output register (r). The value is expressed as a 16-bit word in two’s complement
//#define LSM6DS3_OUTY_L_G 0x24 //Angular rate sensor roll axis (Y) angular rate output register (r). The value is expressed as a 16-bit word in two’s complement

#define LSM6DS3_OUTX_L_XL 0x28 //Linear acceleration sensor X-axis output register (r). The value is expressed as a 16-bit word in two’s complement
#define LSM6DS3_OUT_TEMP_L 0x20 //Temperature data output register (r). L and H registers together express a 16-bit word in two’s complement.


class LSM6DS3 {
    public:   
        void readRegisters(uint8_t address, uint8_t* data, size_t length);

        boolean whoAmICheck();
        
        void readGyroData(float* x, float* y, float* z);
        //void readRollData(float* x, float* y, float* z);

        void readAccelData(float* x, float* y, float* z);
        void readTempData(float* t);
};



#endif