//
// Created by akhundzx on 18.10.2024.
//

#ifndef DINAMICARRAY_H
#define DINAMICARRAY_H


#include "unq_ptr.h"
#include <stdexcept>
template<typename T>

class DinamicArray {
private:
    UnqPtr<T[]> data;
    size_t size;
    size_t capacity;

    void resize(size_t new_capacity) {
        UnqPtr<T[]> new_data(new T[new_capacity]);
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        data = std::move(new_data);
        capacity = new_capacity;
    }
public:
    DinamicArray():size(0), capacity(10),data(new T[10]){}

    size_t get_size() const {
        return size;
    }

    size_t get_capacity() const {
        return capacity;
    }

    bool isEmpty() const {
        return size == 0;
    }


    T& operator[](size_t index) {
        if (index >= size)
            throw std::out_of_range("index out of range");
        return data[index];
    }
    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    void push_back(const T&& value) {
        if (size == capacity) {
            resize(capacity * 2);
        }
        data[size++] = value;
    }

    void insert(size_t index, const T& value) {
        if (index > size) {
            throw std::out_of_range("Index out of range");
        }

        if (size == capacity) {
            resize(capacity * 2);
        }


        for (size_t i = size; i > index; --i) {
            data[i] = std::move(data[i - 1]);
        }
        data[index] = value;
        ++size;
    }

    void erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }

        --size;
    }

};
#endif //DINAMICARRAY_H
