#pragma once

template <typename Type>
class my_vector {
    size_t size = 0;
    Type *arr   = nullptr;

  public:
    my_vector(size_t length, Type t) {
        arr = new type[size = length];
        for (auto &i : arr) {
            i = t;
        }
    }
    void push_back(Type t) {
    }
    Type *operator[](size_t i) {
        if (i >= size) return nullptr;
        return &arr[i];
    }
};