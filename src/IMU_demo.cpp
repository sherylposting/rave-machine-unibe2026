#include <M5Unified.h>

m5::imu_data_t imuData;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);

    if (M5.Imu.begin()) {
        Serial.println("IMU is ready!");
    } else {
        Serial.println("IMU failed to start. Check connection!");
    }
}

void loop() {
    M5.Imu.update();
    imuData = M5.Imu.getImuData();

    Serial.printf("\n Acc X = %6.2f  \n", imuData.accel.x);
    Serial.printf(" Acc Y = %6.2f  \n", imuData.accel.y);
    Serial.printf(" Acc Z = %6.2f  \n\n", imuData.accel.z);

    Serial.printf(" Gyr X = %6.2f  \n", imuData.gyro.x);
    Serial.printf(" Gyr Y = %6.2f  \n", imuData.gyro.y);
    Serial.printf(" Gyr Z = %6.2f  \n", imuData.gyro.z);

    delay(1000);
} 