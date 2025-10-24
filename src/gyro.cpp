#include "gyro.h"

void LSM6DS3::readRegisters(uint8_t address, uint8_t * data, size_t length){

  SPI.beginTransaction(SPISettings(8000000, MSBFIRST, SPI_MODE3));
  digitalWrite(SPI_CS, LOW);
  SPI.transfer(address | 0x80);

  for (size_t i = 0; i < length; i++){
    data[i] = SPI.transfer(0x00); // Send dummy bytes to keep SPI happy
  }

  digitalWrite(SPI_CS, HIGH);
  SPI.endTransaction();
}

boolean LSM6DS3::whoAmICheck(){
  uint8_t data[1] = {0};
  Serial.printf("verified: %x \n", data[0]);
  readRegisters(LSM6S3_WHO_AM_I, data, sizeof(data));

  int verified = data[0];
  Serial.printf("verified: %x \n", verified);

  if (verified == 0b01101010) {
    return true;
  } else {
    return false;
  }
}

void LSM6DS3::readGyroData(float* x, float* y, float* z){
    
  int16_t data[3];
  readRegisters(LSM6DS3_OUTX_L_G, (uint8_t*)data, sizeof(data));

  *x = data[0] * 2000.0 / 32768.0;
  *y = data[1] * 2000.0 / 32768.0;
  *z = data[2] * 2000.0 / 32768.0;

}

/*
void LSM6DS3::readRollData(float* x, float* y, float* z){
    
  int16_t data[3];
  readRegisters(LSM6DS3_OUTY_L_G, (uint8_t*)data, sizeof(data));

  *x = data[0] * 2000.0 / 32768.0;
  *y = data[1] * 2000.0 / 32768.0;
  *z = data[2] * 2000.0 / 32768.0;

}
*/

void LSM6DS3::readAccelData(float* x, float* y, float* z){
    
  int16_t data[3];
  readRegisters(LSM6DS3_OUTX_L_XL, (uint8_t*)data, sizeof(data));

  *x = data[0] * 4.0 / 32768.0;
  *y = data[1] * 4.0 / 32768.0;
  *z = data[2] * 4.0 / 32768.0;

}

void LSM6DS3::readTempData(float* t){
 
  int16_t data[1];

  readRegisters(LSM6DS3_OUT_TEMP_L, (uint8_t*)data, sizeof(data));
  *t = data[0] / 16.0 + 2;

}