#include "sensfuse.h"

SensorFusion::SensorFusion() 
    : last_micros(0),
      ptch_accum(0),
      roll_accum(0),
      fusion_correct_pitch(0),
      fusion_correct_roll(0),
      gyro_bias_x(0),
      gyro_bias_y(0)
{
}

bool SensorFusion::begin() {
    if (!ism330dhcx.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
        Serial.println("Failed to find ISM330DHCX chip1");
        while (1) delay(10);
    }

    float sumX = 0.0f, sumY = 0.0f;
    for (int i = 0; i < 500; i++) {
        float gx, gy, gz;
        ism330dhcx.readGyroscope(gx, gy, gz);
        sumX += gx;
        sumY += gy;
        delay(2);
    }

    gyro_bias_x = sumX / 500.0f;
    gyro_bias_y = sumY / 500.0f;

    float ax, ay, az;
    ism330dhcx.readAcceleration(ax, ay, az);

    ptch_accum = atan2f(-ax, sqrtf(ay * ay + az * az)) * 57.2958f;
    roll_accum = atan2f(ay, az) * 57.2958f;

    last_micros = micros();

    ism330dhcx.configInt1(false, false, true);
    ism330dhcx.configInt2(false, true, false);

    return true;
}

void SensorFusion::update() {
    unsigned long now = micros();
    float dt = (now - last_micros) * 1e-6f;
    last_micros = now;

    float gx, gy, gz;
    float ax, ay, az;
    ism330dhcx.readGyroscope(gx, gy, gz);
    ism330dhcx.readAcceleration(ax, ay, az);

    gx -= gyro_bias_x;
    gy -= gyro_bias_y;

    ptch_accum += (gx * dt) + fusion_correct_pitch;
    roll_accum += (gy * dt) + fusion_correct_roll;

    float ptch_acc_only = atan2f(-ax, sqrtf(ay * ay + az * az)) * 57.2958f;
    float roll_acc_only = atan2f(ay, az) * 57.2958f;

    if (ptch_acc_only > ptch_accum) fusion_correct_pitch += FUSION_STEP;
    else if (ptch_acc_only < ptch_accum) fusion_correct_pitch -= FUSION_STEP;

    if (roll_acc_only > roll_accum) fusion_correct_roll += FUSION_STEP;
    else if (roll_acc_only < roll_accum) fusion_correct_roll -= FUSION_STEP;
}

float SensorFusion::getPitch() {
    return ptch_accum;
}

float SensorFusion::getRoll() {
    return roll_accum;
}