//
// Created by akhundzx on 14.10.2024.
//

#ifndef TEST_H
#define TEST_H

#include "unq_ptr.h"
#include <cassert>
#include <string>
#include "sharedptr.h"
#include "linkedlist.h"
#include "dinamicarray.h"


inline void test_unq_ptr_int() {
    UnqPtr<int> ptr;
    assert(ptr.get() == nullptr);
    ptr.reset(new int(10));
    assert(ptr.get() != nullptr);
    assert(*ptr == 10);
    int *p = ptr.release();
    assert(*p == 10);
    assert(ptr.get() == nullptr);
    UnqPtr<int> pointer(5);
    assert(pointer.get() != nullptr);
    assert(*pointer == 5);
    UnqPtr<int> pointer2(new int (15));
    assert(pointer2.get() != nullptr);
    assert(*pointer2 == 15);
}

inline void test_unq_ptr_string() {
    UnqPtr<std::string> ptr;
    assert(ptr.get() == nullptr);
    ptr.reset(new std::string("sui"));
    assert(ptr.get() != nullptr);
    assert(*ptr == "sui");
    std::string *p = ptr.release();
    assert(*p == "sui");
    assert(ptr.get() == nullptr);
    UnqPtr<std::string> pointer("mbappe");
    assert(pointer.get() != nullptr);
    assert(*pointer == "mbappe");
    UnqPtr<std::string> pointer2(new std::string ("mephi"));
    assert(pointer2.get() != nullptr);
    assert(*pointer2 == "mephi");
}

inline void test_unq_ptr_int_arr() {
    UnqPtr<int[]> ptr;
    assert(ptr.get() == nullptr);
    ptr.reset(new int[3]{1,2,3});
    assert(ptr.get() != nullptr);
    assert(*ptr == 1);
    assert(ptr[1] == 2);
    assert(ptr[2] == 3);
    int* p = ptr.release();
    assert(p != nullptr);
    assert(*p == 1);
    assert(ptr.get() == nullptr);
    UnqPtr<int[]> pointer2(new int[3]{5,4,7});
    assert(pointer2.get() != nullptr);
    assert(pointer2[0] == 5);
    assert(pointer2[1] == 4);
    assert(pointer2[2] == 7);
}

inline void test_shared_ptr_int() {
    SharedPtr<int> p(new int(2));
    assert(p.get_counter() == 1);
    assert(p.get_value() == 2);
    SharedPtr<int> q(p);
    assert(p.get_counter() == 2);
    assert(q.get_counter() == 2);
    assert(q.get_value() == 2);
    SharedPtr<int> r;
    assert(r.get_counter() == 0);
    assert(r.get() == nullptr);
    SharedPtr<int> s(5);
    assert(s.get_counter() == 1);
    assert(s.get_value() == 5);
    p.reset(new int(10));
    assert(p.get_counter() == 1);
    assert(*p == 10);
    assert(q.get_counter() == 1);
    q.reset();
    assert(q.get() == nullptr);
    const int * pointer = s.release();
    assert(s.get() == nullptr);
    assert(*pointer == 5);
    SharedPtr<int> p2 (new int(10));
    SharedPtr<int> p4 = p2;
    assert(p2.get_counter() == 2);
    assert(p4.get_counter() == 2);
    assert(*p2 == 10);
    assert(*p4 == 10);
    SharedPtr<int> p3;
    assert(p3.get() == nullptr);
    assert(p3.get_counter() == 0);
    p3 = p2;
    assert(*p2 == 10);
    assert(*p3 == 10);
    assert(p2.get_counter() == 3);
    assert(p3.get_counter() == 3);

}

inline void test_shared_ptr_arr_int() {
    SharedPtr<int[]> ptr_arr;
    assert(ptr_arr.get()== nullptr);
    assert(ptr_arr.get_counter() == 0);
    ptr_arr.reset(new int[3]{1,2,3});
    assert(ptr_arr.get_counter() == 1);
    assert(ptr_arr[0] == 1);
    assert(ptr_arr[1] == 2);
    assert(ptr_arr[2] == 3);
    SharedPtr<int[]> ptr_arr2 = ptr_arr;
    assert(ptr_arr2.get() == ptr_arr.get());
    assert(ptr_arr2.get_counter() == 2);
    assert(ptr_arr.get_counter() == 2);
    assert(ptr_arr2[0] == 1);
    assert(ptr_arr2[1] == 2);
    assert(ptr_arr2[2] == 3);
    SharedPtr<int[]> ptr(new int[5]{10,20,30,40,50});
    assert(ptr[0] == 10);
    assert(ptr[1] == 20);
    assert(ptr[2] == 30);
    assert(ptr[3] == 40);
    assert(ptr[4] == 50);
    assert(ptr.get_counter() == 1);
    int* pointer = ptr.release();
    assert(pointer[0] == 10);
    assert(pointer[1] == 20);
    assert(pointer[2] == 30);
    assert(pointer[3] == 40);
    assert(pointer[4] == 50);
    assert(ptr.get_counter() == 0);
    SharedPtr<int[]> ptr2(ptr_arr2);
    assert(ptr2.get_counter() == 3);
    assert(ptr_arr2.get_counter() == 3);
    assert(ptr_arr.get_counter() == 3);
    assert(ptr2[0] == 1);
    assert(ptr2[1] == 2);
    assert(ptr2[2] == 3);
}

inline void test_linked_list() {
    LinkedList<int> list;
    list.prepend(20);
    list.prepend(30);
    list.insert_at(4,2);
    assert(list.get(2) == 4);
    list.insert_at(10,1);
    assert(list.get(3) == 4);
    assert(list.get(1) == 10);
    list.append(5);
    assert(list.get(4) == 5);
    list.append(6);
    list.append(7);
    assert(list.get(5) == 6);
    assert(list.get(6) == 7);
    list.insert_at(15,1);
    assert(list.get(1) == 15);
    list.append(77);
    assert(list.get_size() == 9);
    assert(list.get(8) == 77);
    assert(list.get_first() == 30);
    //list.print_list();
}

inline void test_dinamic_array() {
    DinamicArray<int> array;
    array.push_back(2);
    array.push_back(3);
    array.insert(1,10);
    assert(array[0] == 2);
    assert(array[1] == 10);
    assert(array[2] == 3);
    for (int i = 0; i < 10; i++) {
        array.push_back(i);
    }
    array.erase(7);
    assert(array.get_size() == 12);
    assert(array.get_capacity() == 20);
    assert(array[7] == 5);
}
#endif //TEST_H
