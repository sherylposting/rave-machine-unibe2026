#include <M5Unified.h>
#include <Adafruit_NeoPixel.h>
#include "sensor.h"
#include "server.h"

// LED configuration
#define LED_PIN 27
#define NUM_LEDS 1
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

// IMU data configuration
const int polling_delay = 10;
char dataBuffer[128];

// Helper function to map IMU floats to RGB values
uint8_t mapFloatToColor(float g_value) {
    // Constrain the value just in case
    if (g_value < -1.0f) g_value = -1.0f;
    if (g_value > 1.0f) g_value = 1.0f;
    
    // Shift the range from [-1.0, 1.0] to [0.0, 2.0], then 127.5x ==> [0, 255]
    return (uint8_t)((g_value + 1.0f) * 127.5f);
}

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    Serial.begin(115200);

    initIMU();      // Call from IMUManager
    setupWiFi();    // Call from NetworkManager

    strip.begin();  // Set Atom LED to Black
    strip.setPixelColor(0, strip.Color(0,0,0));
    strip.show();
    
    Serial.println("System Ready!");
}

void loop() {
    M5.update();

    float ax, ay, az;

    // Get the data in 
    getData(dataBuffer, sizeof(dataBuffer), &ax, &ay, &az);

    // Map the 3 axes to Red, Green, and Blue values
    uint8_t r = mapFloatToColor(ax); // X tilts change Red
    uint8_t g = mapFloatToColor(ay); // Y tilts change Green
    uint8_t b = mapFloatToColor(az); // Z tilts change Blue

    // Update the LED
    strip.setPixelColor(0, strip.Color(r, g, b));
    strip.show();

    // Print it locally and send to Python server
    Serial.println(dataBuffer);
    sendDataToServer(dataBuffer);

    delay(polling_delay); 
}