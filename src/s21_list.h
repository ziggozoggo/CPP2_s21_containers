#pragma once

#include <iostream>

template<typename T>
class list {
  public:
    using size_type = std::size_t;
    list();
    void push_back (T value);
    
    T& get_tail() {
      return tail_->value;
    }
    T& get_head() {
      return head_->value;
    }
    T& get_shift() {
      Node *node = head_->next;
      return node->value;
    }

  private:
    struct Node {
      T value;
      Node *next;
      Node *prev;
    };
    
    size_type size_;
    Node *head_;
    Node *tail_;
};

// Class implementation
template<typename T>
list<T>::list() : size_(0), head_(nullptr), tail_(nullptr) {}

template<typename T>
void list<T>::push_back(T value) {
  Node *new_node = new Node();
  new_node->value = value;
  if (size_ == 0) {
    head_ = new_node;
    tail_ = new_node;
    
    head_->next = tail_;
    head_->prev = tail_;

    tail_->prev = head_;
    tail_->next = head_;

  } else {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;

    head_->prev = tail_;
    tail_->next = head_;
  }
  ++size_;
}

