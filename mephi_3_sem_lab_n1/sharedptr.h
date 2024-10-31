//
// Created by akhundzx on 10.10.2024.
//

#ifndef SHAREDPTR_H
#define SHAREDPTR_H

#include "unq_ptr.h"

template <typename T>
class SharedPtr {
private:
    T* ptr;
    size_t* refcount;
public:
    SharedPtr():ptr(nullptr),refcount(nullptr){}
    explicit SharedPtr(T* p) {
        ptr = p;
        refcount = new size_t(1);
    }
    SharedPtr(const SharedPtr<T>& p) {
        ptr = p.ptr;
        refcount = p.refcount;
        ++(*refcount);
    }
    explicit SharedPtr(T&& value) {
        ptr = new T(value);
        refcount = new size_t(1);
    }

    size_t get_counter() {
        if (refcount == nullptr)
            return 0;
        return *refcount;
    }

    T& get_value() {
        if (ptr == nullptr)
            throw std::out_of_range("ptr is null");
        return *ptr;
    }

    T* get() {
        return ptr;
    }

    void reset(T* p = nullptr) {
        if (ptr != p) {
            (*refcount)--;
            if (*refcount == 0) {
                T* del_ptr = ptr;
                ptr = p;
                refcount = new size_t(1);
                delete del_ptr;
                return;
            }
            refcount = new size_t(1);
            ptr = p;
            return;
        }
        refcount = new size_t(1);
        ptr = p;
    }

    T* release() {
        *refcount--;
        T* pointer = ptr;
        ptr = nullptr;
        return pointer;
    }

    SharedPtr<T>& operator=(SharedPtr&& p) {
        if (refcount) {
            (*refcount)--;
            if (*refcount == 0) {
                delete ptr;
                delete refcount;
            }
        }
        this->ptr = p.ptr;
        this->refcount = p.refcount;
        (*refcount)++;
        return *this;
    }

    SharedPtr<T>& operator=(const SharedPtr& p) {
        if (refcount) {
            (*refcount)--;
            if (*refcount == 0) {
                delete ptr;
                delete refcount;
            }
        }
        this->ptr = p.ptr;
        this->refcount = p.refcount;
        (*refcount)++;
        return *this;
    }

    T& operator*() const {
        return *ptr;
    }

    T* operator->() const {
        return ptr;
    }

    ~SharedPtr() {
        if (refcount && --(*refcount) == 0) {
            delete ptr;
            delete refcount;
        }
    }
};

template <typename T>
class SharedPtr<T[]> {
private:
    T* ptr;
    size_t* refcount;
public:
    SharedPtr():ptr(nullptr),refcount(nullptr){}
    explicit SharedPtr(T* p) {
        ptr = p;
        refcount = new size_t(1);
    }
    SharedPtr(const SharedPtr<T[]>& p) {
        ptr = p.ptr;
        refcount = p.refcount;
        ++(*refcount);
    }
    explicit SharedPtr(T&& value) {
        ptr = new T(value);
        refcount = new size_t(1);
    }

    size_t get_counter() {
        if (refcount == nullptr)
            return 0;
        return *refcount;
    }

    T& get_value() {
        if (ptr == nullptr)
            throw std::out_of_range("ptr is null");
        return *ptr;
    }

    T* get() {
        return ptr;
    }

    void reset(T* p = nullptr) {
        if (ptr != p && refcount) {
            (*refcount)--;
            if (*refcount == 0) {
                T* del_ptr = ptr;
                ptr = p;
                refcount = new size_t(1);
                delete del_ptr;
                return;
            }
            ptr = p;
            refcount = new size_t(1);
            return;
        }
        ptr = p;
        refcount = new size_t(1);
    }

    T* release() {
        (*refcount)--;
        T* pointer = ptr;
        ptr = nullptr;
        return pointer;
    }

    SharedPtr<T[]>& operator=(SharedPtr<T[]>&& p) {
        if (refcount) {
            (*refcount)--;
            if (*refcount == 0) {
                delete[] ptr;
                delete refcount;
            }
        }
        this->ptr = p.ptr;
        this->refcount = p.refcount;
        *(this->refcount)++;
        return *this;
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

    ~SharedPtr() {
        if (refcount && --(*refcount) == 0) {
            delete[] ptr;
            delete refcount;
        }
    }
};
#endif //SHAREDPTR_H
