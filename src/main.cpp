#include "gyro.h"



void setup() {
  SPI.begin();
  Serial.begin(115200);
  Wire.begin();

  float x;
  float y;
  float z;
}

void loop() {
  // LSM6DS3.readGyroData(x, y, z);
  // Serial.println();

}

