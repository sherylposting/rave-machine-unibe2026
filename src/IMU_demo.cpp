#include <M5Unified.h>
#include <Wire.h>
#include <I2C_MPU6886.h>

m5::imu_data_t imuData;
I2C_MPU6886 IMU;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);

    Wire.begin(26, 32); // SDA, SCL pins for the IMU to M5 Atom Lite Grove Port
    IMU.begin();
}

void loop() {
    M5.update(); // Keeps the internal state updated

    // Create variables to hold our data
    float ax, ay, az; // Accelerometer (Gravity/Tilt)
    float gx, gy, gz; // Gyroscope (Rotation speed)

    // Grab the latest data from the sensor
    M5.Imu.getAccel(&ax, &ay, &az);
    M5.Imu.getGyro(&gx, &gy, &gz);

    // Print the Accelerometer data to the Serial Monitor
    Serial.printf("Accel: %5.2f, %5.2f, %5.2f | Gyro: %5.2f, %5.2f, %5.2f\n", 
                  ax, ay, az, gx, gy, gz);

    delay(100); // Slow down the text so it's readable
} 