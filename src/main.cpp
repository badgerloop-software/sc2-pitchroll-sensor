#include "sensfuse.h"
#include <Adafruit_ISM330DHCX.h>

SensorFusion fusion; // Create sensor fusion object

void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(10); 

    Serial.println("Adafruit ISM330DHCX test!");
    if (!fusion.begin()) {
        Serial.println("IMU initialization failed");
        while (1) {
            delay(10);
        }
    }
}

void loop() {
    fusion.update();

    Serial.print("Pitch: ");
    Serial.print(fusion.getPitch());
    Serial.print("Roll: ");
    Serial.println(fusion.getRoll());

    delay(100);
}

