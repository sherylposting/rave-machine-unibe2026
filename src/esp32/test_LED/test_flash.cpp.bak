#include <Adafruit_NeoPixel.h>

/// note: you need to install the adafruit neopixel library
// tools -> manage libraries

#define LED_PIN 27
#define NUM_LEDS 1

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
    strip.begin();
    strip.show(); // off
}

void loop() {
    // ON (red)
    strip.setPixelColor(0, 255, 0, 0);
    strip.show();
    delay(500);

    // OFF
    strip.setPixelColor(0, 0, 0, 0);
    strip.show();
    delay(500);
}
