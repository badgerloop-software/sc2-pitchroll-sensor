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

// begin function for SPI initialization
bool SensorFusion::begin() {
    if (!ism330dhcx.begin_SPI(LSM_CS, LSM_SCK, LSM_MISO, LSM_MOSI)) {
        Serial.println("Failed to find ISM330DHCX chip1");
        while (1) {
            delay(10);
        }
    }

    // Calibrate gyro bias while the board/car is not moving
    // Take readings to find the average bias error
    float sumX = 0.0f, sumY = 0.0f;
    for (int i = 0; i < 500; i++) {
        float gx, gy, gz;
        ism330dhcx.readGyroscope(gx, gy, gz);
        sumX += gx;
        sumY += gy;
        delay(2);
    }

    // Calculate average bias
    gyro_bias_x = sumX / 500.0f;
    gyro_bias_y = sumY / 500.0f;

    // Read in accelerometer data for initial angle calculation
    float ax, ay, az;
    ism330dhcx.readAcceleration(ax, ay, az);

    // Figure out the current tilt of the board (in degrees)
    // atan2 gives the angle in radians; multiply by 57.2958 (180/pi) to turn it into degrees
    ptch_accum = atan2f(-ax, sqrtf(ay * ay + az * az)) * 57.2958f;
    roll_accum = atan2f(ay, az) * 57.2958f;

    // Store the start time to calculate time difference next loop
    last_micros = micros();

    ism330dhcx.configInt1(false, false, true); // accelerometer DRDY on INT1
    ism330dhcx.configInt2(false, true, false); // gyro DRDY on INT2

    return true;
}

// Make functions for gyro, accelerometer calculations
// Perform function calls in main
// Main should be clean, only using function calls and tests.
void SensorFusion::update() {
    // Calculate time step (dt) in seconds for integration
    unsigned long now = micros();           // Current time in microseconds
    float dt = (now - last_micros) * 1e-6f; // Convert microseconds to seconds
    last_micros = now;                      // Update last_micros for next loop

    // Read sensor data
    float gx, gy, gz;
    float ax, ay, az;
    ism330dhcx.readGyroscope(gx, gy, gz);    // Read in the gyro data
    ism330dhcx.readAcceleration(ax, ay, az); // Read in the accelerometer data

    // Gyro bias correction
    gx -= gyro_bias_x;
    gy -= gyro_bias_y;

    // Integrate gyro data to get running angles
    // gx/y * dt = change in angle since last loop
    ptch_accum += (gx * dt) + fusion_correct_pitch;
    roll_accum += (gy * dt) + fusion_correct_roll;

    // Compute accelerometer-based angles (gravity reference)
    float ptch_acc_only = atan2f(-ax, sqrtf(ay * ay + az * az)) * 57.2958f;
    float roll_acc_only = atan2f(ay, az) * 57.2958f;

    // Sensor fusion correction loops
    // If the accelerometer says the angle should be bigger, bump fusion up.
    // If it says smaller, bump it down. This slowly keeps gyro drift in check.
    if (ptch_acc_only > ptch_accum) {
        fusion_correct_pitch += FUSION_STEP;
    } else if (ptch_acc_only < ptch_accum) {
        fusion_correct_pitch -= FUSION_STEP;
    }

    if (roll_acc_only > roll_accum) {
        fusion_correct_roll += FUSION_STEP;
    } else if (roll_acc_only < roll_accum) {
        fusion_correct_roll -= FUSION_STEP;
    }
}