//
// Created by akhundzx on 14.10.2024.
//

#ifndef TIME_TEST_H
#define TIME_TEST_H

#include <ctime>
#include <iostream>
#include "sharedptr.h"
#include "unq_ptr.h"
#include <chrono>
#include <cstdlib>
#include <memory>
#include "linkedlist.h"

inline void swap_raw(int* data, int i,int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

inline void swap_smart(SharedPtr<int[]>& data, int i,int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

inline void swap_unq(UnqPtr<int[]>& data, int i,int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

inline void swap_stl_unq_ptr(std::unique_ptr<int[]>& data, int i,int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

inline void swap_stl_shared_ptr(std::shared_ptr<int[]>& data, int i,int j) {
    int temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}


inline void bubble_sort_raw(int* data,size_t len) {
    for(int i=0;i<len;i++) {
        for(int j=0;j<len-i-1;j++) {
            if(data[j] > data[j+1]) {
                swap_raw(data,j,j+1);
            }
        }
    }
}

inline void bubble_sort_smart(SharedPtr<int[]>& data,size_t len) {
    for(int i=0;i<len;i++) {
        for(int j=0;j<len-i-1;j++) {
            if(data[j] > data[j+1]) {
                swap_smart(data,j,j+1);
            }
        }
    }
}

inline void bubble_sort_unq(UnqPtr<int[]>& data,size_t len) {
    for(int i=0;i<len;i++) {
        for(int j=0;j<len-i-1;j++) {
            if(data[j] > data[j+1]) {
                swap_unq(data,j,j+1);
            }
        }
    }
}

inline void bubble_sort_stl_unq(std::unique_ptr<int[]>& data,size_t len) {
    for(int i=0;i<len;i++) {
        for(int j=0;j<len-i-1;j++) {
            if(data[j] > data[j+1]) {
                swap_stl_unq_ptr(data,j,j+1);
            }
        }
    }
}

inline void bubble_sort_stl_shared_ptr(std::shared_ptr<int[]>& data,size_t len) {
    for(int i=0;i<len;i++) {
        for(int j=0;j<len-i-1;j++) {
            if(data[j] > data[j+1]) {
                swap_stl_shared_ptr(data,j,j+1);
            }
        }
    }
}
inline void compare() {
    int data_raw[10000] = {0};
    srand(time(NULL));
    for(int i=0;i<10000;i++) {
        data_raw[i] = rand();
    }
    SharedPtr<int[]> data_smart(new int[10000]{0});
    for(int i=0;i<10000;i++) {
        data_smart[i] = rand();
    }

    UnqPtr<int[]> data_unq(new int[10000]{0});
    for(int i=0;i<10000;i++) {
        data_unq[i] = rand();
    }

    std::unique_ptr<int[]> data_stl_unq(new int[10000]{0});
    for(int i=0;i<10000;i++) {
        data_stl_unq[i] = rand();
    }

    std::shared_ptr<int[]> data_stl_shared_ptr(new int[10000]{0});
    for(int i=0;i<10000;i++) {
        data_stl_shared_ptr[i] = rand();
    }
    auto begin = std::chrono::steady_clock::now();
    bubble_sort_raw(data_raw,10000);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time on the raw pointers: " << elapsed_ms.count() << " ms\n";
    begin = std::chrono::steady_clock::now();
    bubble_sort_smart(data_smart,10000);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time on the SharedPointers: " << elapsed_ms.count() << " ms\n";
    begin = std::chrono::steady_clock::now();
    bubble_sort_unq(data_unq,10000);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time on the UniquePointers: " << elapsed_ms.count() << " ms\n";
    begin = std::chrono::steady_clock::now();
    bubble_sort_stl_unq(data_stl_unq,10000);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time on the stl::UniquePointers: " << elapsed_ms.count() << " ms\n";
    begin = std::chrono::steady_clock::now();
    bubble_sort_stl_shared_ptr(data_stl_shared_ptr,10000);
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "The time on the stl::SharedPointers: " << elapsed_ms.count() << " ms\n";
    begin = std::chrono::steady_clock::now();
    LinkedList<int> list;
    for(int i=0;i<10000;i++) {
        list.append(rand());
    }
    //std::cout << list.get_size() << std::endl;
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout << "\n\nThe time on the append in LinkedLists: " << elapsed_ms.count() << " ms\n";
}

#endif //TIME_TEST_H
