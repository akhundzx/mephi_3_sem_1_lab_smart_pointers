//
// Created by akhundzx on 10.10.2024.
//

#ifndef UNQ_PTR_H
#define UNQ_PTR_H

template <typename T>

class UnqPtr {
private:
    T *ptr;
public:
    UnqPtr():ptr(nullptr){}
    explicit UnqPtr(T* other):ptr(other){}
    explicit UnqPtr(T&& value): ptr(new T(value)){}
    UnqPtr(const UnqPtr&& other) noexcept{
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    UnqPtr& operator=(T* other) {
        if (ptr != other) {
            T* temp = ptr;
            ptr = other;
            delete temp;
            return *this;
        }
        return *this;
    }

    UnqPtr<T>& operator= (UnqPtr&& other) noexcept{
        if (this != &other) {
            delete this->ptr;
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    UnqPtr(const UnqPtr& other) = delete;
    UnqPtr& operator=(const UnqPtr& other) = delete;

    void reset(T* other = nullptr) {
        if (ptr != other) {
            T* del_ptr = ptr;
            ptr = other;
            delete del_ptr;
        }
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T* get() {
        return ptr;
    }


    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    ~UnqPtr() {
        delete ptr;
    }
};

template <typename T>
class UnqPtr<T[]> {
private:
    T* ptr;
public:
    UnqPtr():ptr(nullptr){}
    explicit UnqPtr(T* other):ptr(other){}
    explicit UnqPtr(T&& value): ptr(new T (value)){}
    UnqPtr(const UnqPtr<T[]>&& other) noexcept{
        ptr = other.ptr;
        other.ptr = nullptr;
    }
    UnqPtr& operator=(T* other) {
        if (ptr != other) {
            T* temp = ptr;
            ptr = other;
            delete[] temp;
            return *this;
        }
        return *this;
    }

    UnqPtr<T[]>& operator= (UnqPtr&& other) noexcept{
        if (this != &other) {
            delete[] this->ptr;
            this->ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    UnqPtr(const UnqPtr& other) = delete;
    UnqPtr& operator=(const UnqPtr& other) = delete;

    void reset(T* other = nullptr) {
        if (ptr != other) {
            T* del_ptr = ptr;
            ptr = other;
            delete[] del_ptr;
        }
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T* get() {
        return ptr;
    }


    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    T& operator[](size_t index) {
        return *(ptr+index);
    }


    ~UnqPtr() {
        delete[] ptr;
    }
};
#endif //UNQ_PTR_H
