#ifndef __sensfuse__h__
#define __sensfuse__h__
#include <SPI.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ISM330DHCX.h>

// For SPI mode we need a CS pin
#define LSM_CS PA4 
// For software-SPI mode we need SCK/MOSI/MISO pins
#define LSM_SCK D13
#define LSM_MISO D12
#define LSM_MOSI D11

#define FUSION_STEP 0.05f // Fusion correct constant

// begin() function declaration
class SensorFusion {
    public: 

        SensorFusion();

        bool begin();
        void update();

        float getPitch() {
            return ptch_accum;
        }

        float getRoll() {
            return roll_accum;
        }

    private:

        Adafruit_ISM330DHCX ism330dhcx;  // Create an instance of the gyro/accelerometer class

        unsigned long last_micros;

        float ptch_accum;
        float roll_accum; 

        float fusion_correct_pitch;
        float fusion_correct_roll;

        float gyro_bias_x;
        float gyro_bias_y;

};

#endif 