#include <Arduino.h>
#include <FastLED.h>

#define DEBUG

#define LED_PIN 2
#define LED_COUNT 64

CRGB stick[LED_COUNT];

void setup() {
#ifdef DEBUG
    Serial.begin(9600);
    Serial.println("Start");
#endif
    FastLED.addLeds<WS2812B, LED_PIN, RGB>(stick, LED_COUNT);
}

void loop() {

    for (size_t i = 0; i < 2; i++) {
#ifdef DEBUG
        Serial.println(i);
#endif
        stick[i].setColorCode(0x101010);
        FastLED.show();
        delay(500);
    }
    for (size_t i = 0; i < 2; i++) {
        stick[i] = CRGB::Black;
    }
    FastLED.show();
    delay(500);
}