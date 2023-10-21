#pragma once
#include <Arduino.h>
#include <FastLED.h>
#include <my_vector.hpp>

template <uint8_t PIN, uint16_t length>
class light_led {
  private:
    CRGB stick[length];
    uint8_t count_of_segments, length_of_segment;

    struct segment {
        uint16_t len, number;
    };

    tomatik::array<segment, length> arr_seg;
    size_t last_segment_number;

  public:
    light_led() : arr_seg(tomatik::array<segment, length>(segment{length, 1})), last_segment_number(1) {
        FastLED.addLeds<WS2812B, PIN, RGB>(stick, length);
    }

    size_t init() {
        arr_seg.clear();
        arr_seg.push(segment{length, 1});
        return length;
    }

    void setColor(uint32_t hex_color) {
        for (auto &i : stick) {
            i.setColorCode(hex_color);
        }
        FastLED.show();
    }

    void setColorSegment(uint32_t hex_color, uint8_t number_of_segment) {
        FastLED.show();
    }

    void insertSegment(uint8_t number_of_segment, uint16_t length_of_segment) {
        bool flag = 1;
        for (size_t i = 0; i < arr_seg.size(); i++) {
            if (arr_seg[i].number == number_of_segment) {
                if (arr_seg[i].len <= length_of_segment - 1)
                    break;
                arr_seg[i].len -= length_of_segment;
                arr_seg.insert(segment{
                                   length_of_segment,
                                   ++last_segment_number},
                               i);
                flag = 0;

                break;
            }
        }

        return flag;

        /*
                insertSegment - поиск сегмента по индексу (первое число) и выделение из него другого сегмента длиной, меньшей длины первого сегмента как минимум на единицу (второе число)
            return: получилось ли выделить (0 - да, появился новый сегмент, 1 - нет, не найден сегмент или слишком большая длина)
            numb | numb
            */
    }

    // void setColorOnePixel(uint32_t hex_color, uint16_t i) {
    //     if (i >= length) return;
    //     stick[i].setColorCode(hex_color);
    //     FastLED.show();
    // }
};

/*
    метод, заполняет всю ленту одним hex
    заполняет один сегмент hex

*/