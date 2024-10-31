//
// Created by akhundzx on 03.10.2024.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdexcept>
#include "unq_ptr.h"
template<typename T>
struct Node {
    T data;
    UnqPtr<Node<T>> next;
    explicit Node(T val) : data(val), next(nullptr) {}
};

template<typename T>
class LinkedList {
private:
    UnqPtr<Node<T>> head;
    size_t length;
public:
    LinkedList() : head(nullptr), length(0) {}

    void prepend(const T& value) {
        UnqPtr<Node<T>> newHead(new Node<T>(value));
        newHead->next = std::move(head);
        head = std::move(newHead);
        length++;
    }

    void append(const T& value) {
        if (head.get() == nullptr) {
            prepend(value);
            return;
        }
        UnqPtr<Node<T>> newNode(new Node<T>(value));
        Node<T>* current = head.get();
        for (size_t i = 0; i < length - 1; i++) {
            current = current->next.get();
        }
        current->next = std::move(newNode);
        length++;
    }

    void insert_at(const T& value, size_t index) {
        if (index > length) {
            throw std::out_of_range("index out of range");
        }
        if (index == 0) {
            prepend(value);
            return;
        }
        Node<T>* current = head.get();
        for (size_t i = 0; i < index-1; i++) {
            current = current->next.get();
        }
        UnqPtr<Node<T>> newNode(new Node<T>(value));
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
        length++;
    }
    T& get_first() {
        if (head.get() == nullptr) {
            throw std::out_of_range("empty list");
        }
        return head->data;
    }

    T& get(size_t index) {
        if (index > length) {
            throw std::out_of_range("index out of range");
        }
        Node<T>* current = head.get();
        for (size_t i = 0; i < index; i++) {
            current = current->next.get();
        }
        return current->data;
    }

    size_t& get_size() {
        return length;
    }

    void print_list() {
        for (size_t i = 0; i < length; i++) {
            std::cout << this->get(i) << " ";
        }
    }

    ~LinkedList() {
        if (head.get() != nullptr) {
          for (int i = 0; i < length; i++) {
              UnqPtr<Node<T>> oldHead;
              oldHead = std::move(head);
              head = std::move(oldHead->next);
                --length;
            }
      }
    }
};

#endif //LINKEDLIST_H
