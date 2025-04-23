// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <iostream>
#include <stdexcept>

template <typename T> struct Node {
  T data;
  Node *next;
  Node(const T &data) : data(data), next(nullptr) {}
};

template <typename T> class TPQueue {
  Node<T> *head;
  Node<T> *tail;
  int count;

public:
  TPQueue() : head(nullptr), tail(nullptr), count(0) {}

  ~TPQueue() {
    while (head) {
      Node<T> *temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(const T &item) {
    Node<T> *newNode = new Node<T>(item);

    if (!head) {
      head = tail = newNode;
      count++;
      return;
    }

    if (item.prior > head->data.prior) {
      newNode->next = head;
      head = newNode;
      count++;
      return;
    }

    Node<T> *current = head;
    while (current->next && item.prior <= current->next->data.prior) {
      current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;

    if (!newNode->next) {
      tail = newNode;
    }
    count++;
  }

  void peek() const {
    if (!head) {
      throw std::underflow_error("Queue is empty");
    }
    std::cout << head->data.ch << "-" << head->data.prior << '\n';
  }

  void pop(char ch) {
    if (!head) {
      throw std::underflow_error("Queue is empty");
    }

    if (head->data.ch == ch) {
      Node<T> *temp = head;
      head = head->next;
      if (!head) {
        tail = nullptr;
      }
      delete temp;
      count--;
      return;
    }

    Node<T> *current = head;
    while (current->next && current->next->data.ch != ch) {
      current = current->next;
    }

    if (!current->next) {
      throw std::runtime_error("Element not found");
    }

    Node<T> *temp = current->next;
    current->next = temp->next;

    if (!current->next) {
      tail = current;
    }

    delete temp;
    count--;
  }

  bool isEmpty() const { return head == nullptr; }

  int size() const { return count; }
};

struct SYM {
  char ch;
  int prior;
};

#endif // INCLUDE_TPQUEUE_H_
