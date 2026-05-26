#include <M5Unified.h>
#include <Wire.h>
#include <I2C_MPU6886.h>
#include "sensor.h"

I2C_MPU6886 IMU;
const int SDA_pin = 26;
const int SCL_pin = 32;


void initIMU() {
    Wire.begin(SDA_pin, SCL_pin); // SDA, SCL pins for the IMU to M5 Atom Lite Grove Port
    IMU.begin();
}

void getData(char* buffer, int size) {
    // Create variables to hold our data
    float ax, ay, az; // Accelerometer (Gravity/Tilt)
    float gx, gy, gz; // Gyroscope (Rotation speed)

    // Grab the latest data from the sensor
    IMU.getAccel(&ax, &ay, &az);
    IMU.getGyro(&gx, &gy, &gz);

    // Save the IMU data as a string in JSON format
    snprintf(buffer, size, "{\n\"acc_x\": %.2f,\n\"acc_y\": %.2f,\n\"acc_z\": %.2f,\n\"gyro_x\": %.2f,\n\"gyro_y\": %.2f,\n\"gyro_z\": %.2f\n}", 
                            ax, ay, az, gx, gy, gz);
} 