#pragma once
#include <Arduino.h>

class run_protocol {

    struct com {
        const uint8_t kw;
        enum : uint8_t {
            null,
            hex,
            numb
        } types[];
    };
    /*  init - возврат длины ленты и сброс сегментацию, цвета, якрость (перезгружает)
        segment - номер сегмента и цвет
        delenie -
    */

    static const inline com coms[] = {
        com{1, {com::null}},
        com{2, {com::numb, com::hex}}};

  public:
    enum class err {
        ok,
        prog_more_buf
    };

    static inline err run(size_t length_buffer) {

        char buf[length_buffer] = {0};
        size_t buf_size         = 0;

        while (Serial.available() > 0) {
            buf[buf_size++] = Serial.read();
            if (buf_size == length_buffer) return err::prog_more_buf;
        }

        for (size_t i = 0; i != buf_size; i++) {
            for (const auto &j : coms) {
                if (buf[i] == j.kw) {
                }
            }
        }
    }
};