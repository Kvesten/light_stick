#pragma once
#include <stdint.h>
#include <stdlib.h>

namespace tomatik {

    template <typename Type, size_t max_size>
    class array {
        Type arr[max_size];
        size_t length = 0;
        size_t *flag;

      public:
        array(Type el, size_t *flag = nullptr) : flag(flag) {
            for (auto &i : arr)
                i = el;
        }

        size_t push(Type el) {
            if (length == max_size) return 1;
            arr[length++] = el;
            return 0;
        }

        Type pop() {
            if (flag && length == 0) {
                *flag = 1;
                return arr[length];
            }
            if (flag) *flag = 0;
            return arr[length--];
        }

        Type &peek() {
            return arr[length];
        }

        const size_t &size() {
            return length;
        }

        size_t insert(Type el, size_t pos) {
            if (length == max_size || pos >= length) return 1;
            for (int32_t i = ++length - 1; i != pos; i--) {
                arr[i] = arr[i - 1];
            }
            arr[pos] = el;

            return 0;
        }

        size_t erase(size_t pos) {
            if (length == 0 || pos >= length) return 1;
            for (size_t i = pos; i < length; i++) {
                arr[i] = arr[i + 1];
            }
            return 0;
        }

        void clear() {
            length = 0;
        }

        Type &operator[](size_t i) {
            if (i >= length) {
                if (flag) *flag = 1;
                return arr[length - 1];
            }
            if (flag) *flag = 0;
            return arr[i];
        }
    };
}  // namespace tomatik