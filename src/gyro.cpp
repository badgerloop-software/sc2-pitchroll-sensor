#include "gyro.h"

void LSM6DS3::readRegisters(uint8_t address, uint8_t * data, size_t length){

  SPI.beginTransaction(SPISettings(14000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(address | 0x80);
  SPI.transfer(data,length);
  SPI.endTransaction();

}

void LSM6DS3::readGyroData(float* x, float* y, float* z){
    
  int16_t data[3];
  readRegisters(LSM6DS3_OUTX_L_G, (uint8_t*)data, sizeof(data));

  *x = data[0] * 2000.0 / 32768.0;
  *y = data[1] * 2000.0 / 32768.0;
  *z = data[2] * 2000.0 / 32768.0;

}

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