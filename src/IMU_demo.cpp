#include <M5Unified.h>
#include <Wire.h>
#include <I2C_MPU6886.h>

I2C_MPU6886 IMU;
const int SDA_pin = 26;
const int SCL_pin = 32;

const int polling_rate = 100;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);

    Wire.begin(SDA_pin, SCL_pin); // SDA, SCL pins for the IMU to M5 Atom Lite Grove Port
    IMU.begin();

    // Print CSV header once at start (NOTE: use DCORE_DEBUG_LEVEL=1 in platformio.ini)
    Serial.println("acc_x, acc_y, acc_z, gyro_x, gyro_y, gyro_z\n");
}

void loop() {
    M5.update(); // Keeps the internal state updated

    // Create variables to hold our data
    float ax, ay, az; // Accelerometer (Gravity/Tilt)
    float gx, gy, gz; // Gyroscope (Rotation speed)

    // Grab the latest data from the sensor
    IMU.getAccel(&ax, &ay, &az);
    IMU.getGyro(&gx, &gy, &gz);

    // Print the Accelerometer data to the Serial Monitor
    Serial.printf("%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n", 
                    ax, ay, az, gx, gy, gz);
    delay(polling_rate); // Slows down text for readability
} 