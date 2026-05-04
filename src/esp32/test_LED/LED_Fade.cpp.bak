#include <M5Unified.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 27
#define NUM_LEDS 1 // Atom Lite has only 1 LED

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    auto cfg = M5.config();
    cfg.serial_baudrate = 115200;
    M5.begin(cfg);

    // Initialize the NeoPixel strip (black)
    strip.begin();
    strip.setPixelColor(0, strip.Color(0, 0, 0));
    strip.show();

    Serial.println("LED Fade Example");

    delay(1000);
}

void loop() {
    int change_time = 10; // ms - adjust this to change the speed of the color change
    int step = 65535 / 255; // Step size for hue change for SRGB color space
    for (long hue = 0; hue < 65535; hue += step) {

        // Convert HSV to RGB and set the pixel color
        uint32_t color = strip.ColorHSV(hue, 255, 255);
        
        strip.setPixelColor(0, color);
        Serial.printf("pixel color : Ox%X\n", color);
        strip.show();

        delay(change_time);
    }
}