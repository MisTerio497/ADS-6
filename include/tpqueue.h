// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
struct Node {
    T data;
    Node* next;
    explicit Node(const T& data) : data(data), next(nullptr) {}
};

template<typename T>
class TPQueue {
 private:
    Node<T>* head;
    Node<T>* tail;
    int count;

 public:
    TPQueue() : head(nullptr), tail(nullptr), count(0) {}

    ~TPQueue() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const T& item) {
        Node<T>* newNode = new Node<T>(item);

        if (!head || item.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            if (!tail) tail = head;
            count++;
            return;
        }

        Node<T>* current = head;
        while (current->next && current->next->data.prior >= item.prior) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
        if (!newNode->next) {
            tail = newNode;
        }
        count++;
    }

    T pop() {
        if (!head) {
            throw std::underflow_error("Queue is empty");
        }

        Node<T>* temp = head;
        T item = head->data;
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
        delete temp;
        count--;
        return item;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int size() const {
        return count;
    }
};

struct SYM {
    char ch;
    int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
