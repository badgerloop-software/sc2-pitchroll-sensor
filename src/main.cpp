#include "gyro.h"


float* x;
float* y;
float* z;

float* f;
float* g;
float* h;

float* t;
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


   //pointers need memory allocation
   x = (float*)malloc(sizeof(float));
   y = (float*)malloc(sizeof(float));
   z = (float*)malloc(sizeof(float));

   f = (float*)malloc(sizeof(float));
   g = (float*)malloc(sizeof(float));
   h = (float*)malloc(sizeof(float));

   t = (float*)malloc(sizeof(float));

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

