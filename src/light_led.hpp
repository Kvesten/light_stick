#pragma once
#include <Arduino.h>
#include <FastLED.h>

template <uint8_t PIN, uint16_t length>
class light_led {
  private:
    CRGB stick[length];
    uint8_t count_of_segments, length_of_segment;

  public:
    light_led(uint8_t count_of_segments = 1, uint8_t length_of_segment = length)
        : count_of_segments(count_of_segments), length_of_segment(length_of_segment) {
        FastLED.addLeds<WS2812B, PIN, RGB>(stick, length);
    }

    void setSegmentInit(uint8_t count_of_segments, uint8_t length_of_segment) {
        this->count_of_segments = count_of_segments;
        this->length_of_segment = length_of_segment;
    }

    void setColorAllLed(uint32_t hex_color) {
        for (auto &i : stick) {
            i.setColorCode(hex_color);
        }
        FastLED.show();
    }

    void setColorSegment(uint32_t hex_color, uint8_t number_of_segment) {
        size_t end = (number_of_segment + 1) * length_of_segment;
        if (end >= length) return;

        for (size_t i = (number_of_segment)*length_of_segment;
             i != end; i++) {
            stick[i].setColorCode(hex_color);
        }
        FastLED.show();
    }

    void setColorOnePixel(uint32_t hex_color, uint16_t i) {
        if (i >= length) return;
        stick[i].setColorCode(hex_color);
        FastLED.show();
    }
};

/*
    метод, заполняет всю ленту одним hex
    заполняет один сегмент hex

*/