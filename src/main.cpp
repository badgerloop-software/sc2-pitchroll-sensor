#include "gyro.h"
#include <LSM6DS3.h>


  float* x;
  float* y;
  float* z;

  float* f;
  float* g;
  float* h;
  
  float* t;

  #define SPI_CS D3
  #define SPI_SCLK A4
  #define SPI_MOSI D2
  #define SPI_MISO A5

SPIClass spi1(SPI_CS,SPI_SCLK,SPI_MOSI,SPI_MISO);
  
LSM6DS3Class board(spi1, SPI_CS, D6 );

LSM6DS3 board2;

void setup() {
  SPI.begin();
  Serial.begin(115200);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, HIGH);

  // if (IMU.begin() == 0) {
  //   Serial.printf("Failed\n");
  //   while(true);
  // }

  if (board2.whoAmICheck() != true) {
    Serial.printf("Failed\n");
    while(true);
  }
   Serial.printf("Not Failed\n");

}

void loop() {
  // //board.readGyroData(x, y, z);
  // IMU.readGyroscope(*x, *y, *z);
  // Serial.print("Gyro X,Y,Z: ");
  // Serial.print(*x, 2);
  // Serial.print(" ");
  // Serial.print(*y, 2);
  // Serial.print(" ");
  // Serial.print(*z, 2);
  // Serial.print("  ||  ");

  // //board.readAccelData(f, g, h);
  // IMU.readAcceleration(*f, *g, *h);
  // Serial.print("Accel X,Y,Z: ");
  // Serial.print(*f, 2);
  // Serial.print(" ");
  // Serial.print(*g, 2);
  // Serial.print(" ");
  // Serial.print(*h, 2);
  // Serial.print("  ||  ");

  // //board.readTempData(t);
  // IMU.readTemperature(*t);
  // Serial.print("Temp: ");
  // Serial.println(*t, 2);

  // delay(100);
}

