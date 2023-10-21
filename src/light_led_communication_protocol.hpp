#pragma once
#include "light_led.hpp"
#include <Arduino.h>

template <typename class_light_led>
class lldprot {
  public:
    enum {
        init,
        setColor,
        setSegment,
        insertSegment,
        deleteSegment,
    };

  private:
    struct com {
        const uint8_t kw;
        enum : uint8_t {
            null,
            hex,
            int8,
            int16,
            bool_flag
        } types[];
    };
    /*
        init - сброс сегментов (вся лента становится одним сегментом) и установка цвета в 0
            return: int возврат длины ленты
            no args

        setColor - все сегменты перекрашиваются в цвет
            no return
            hex

        setColorSegment - выбор сегмента по индексу(если он не слишком большой) и установка для каждого светодиода света hex
            return: bool правильный ли был индекс (0 - да, 1 - нет)
            int8 | hex

        insertSegment - поиск сегмента по индексу (первое число) и выделение из него другого сегмента длиной, меньшей длины первого сегмента как минимум на единицу (второе число)
            return: получилось ли выделить (0 - да, появился новый сегмент, 1 - нет, не найден сегмент или слишком большая длина)
            int8 | int16

        deleteSegment - поиск сегмента по индексу (первое число) и удаление его; вся его память присоединяется к левому (если флаг 1) или к правому (если флаг 0)
            return: получилось ли удалить (не получится удалить, если сегмент крайне левый, крайне парвый или единственный); возврат 0, если да, и 1, если нет
            int8 | bool_flag


    */

    static const inline com coms[] = {
        com{init, {com::null}},
        com{setColor, {com::hex}},
        com{setSegment, {com::int8, com::hex}},
        com{insertSegment, {com::int8, com::int16}},
        com{deleteSegment, {com::int8, com::bool_flag}}

    };
#define coms_size (sizeof coms / sizeof *coms)

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
            for (size_t j = 0; j != coms_size; j++) {
                if (buf[i] == coms[j].kw) {
                    ptrdiff_t arr_size = (char *)&coms[j + 1] - (char *)&coms[j].types;
                    for (size_t k = 0; k != arr_size; k++) {
                        switch (coms[j].types[k]) {
                            case com::hex:
                                int32_t tmp = *(int32_t *)&buf[++i];
                                i += 4;
                                break;
                            case com::int16:
                                int16_t tmp = *(int16_t *)&buf[++i];
                                i += 2;
                                break;
                            case com::int8:
                                int8_t tmp = buf[++i];
                                ++i;
                            case com::null:
                            default: break;
                        }

                        break;
                    }
                }
            }
        }
        return err::ok;
    }
};