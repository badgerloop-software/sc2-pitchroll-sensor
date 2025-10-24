#ifndef __gyro__h__
#define __gyro__h__
#include <SPI.h>
#include <Arduino.h>

#define LSM6S3_WHO_AM_I 0x0F

#define LSM6DS3_OUTX_L_G 0X22  //Angular rate sensor pitch axis (X) angular rate output register (r). The value is expressed as a 16-bit word in two’s complement
//#define LSM6DS3_OUTY_L_G 0x24 //Angular rate sensor roll axis (Y) angular rate output register (r). The value is expressed as a 16-bit word in two’s complement

#define LSM6DS3_OUTX_L_XL 0x28 //Linear acceleration sensor X-axis output register (r). The value is expressed as a 16-bit word in two’s complement
#define LSM6DS3_OUT_TEMP_L 0x20 //Temperature data output register (r). L and H registers together express a 16-bit word in two’s complement.

#define SPI_CS PB_0  //Need to use this instead of A3 because A3 is mapped to something else
#define SPI_SCLK PA_5  // OR D13
#define SPI_MOSI PA_7 //OR D11
#define SPI_MISO PA_6  //OR D12


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