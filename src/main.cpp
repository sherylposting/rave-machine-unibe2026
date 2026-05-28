#include <M5Unified.h>
#include "sensor.h"
#include "server.h"

const int polling_delay = 10;
char dataBuffer[128];

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);

    initIMU();      // Call from IMUManager
    setupWiFi();    // Call from NetworkManager
    
    Serial.println("System Ready!");
}

void loop() {
    M5.update();

    // 1. Get the data
    getData(dataBuffer, sizeof(dataBuffer));

    // 2. Print it locally
    Serial.println(dataBuffer);

    // 3. Send it to your Python server[cite: 2]
    sendDataToServer(dataBuffer);

    delay(polling_delay); 
}