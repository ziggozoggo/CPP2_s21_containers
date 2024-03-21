#pragma once
#include "s21_list.h"

// Class implementation
template<typename T>
list<T>::list() : size_(0), head_(nullptr), tail_(nullptr) {}

template<typename T>
list<T>::~list() {
  if (size_ != 0) {
    // 1. Delete nodes && Free memory
    // 2. Set ptrs to null, size_ = 0
  }
}

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

template<typename T>
T& list<T>::get_head() {
  return head_->value;
}

template<typename T>
T& list<T>::get_tail() {
  return tail_->value;
}

template<typename T>
T& list<T>::get_shift() {
  Node *node = head_->next;
  return node->value;
}

/* ITERATORS */

template<typename T>
T& list<T>::iterator::operator*() {
  // TODO throw exception
  return ptr_->value;
}

template<typename T>
typename list<T>::iterator list<T>::begin() {
  //TODO Throw exception
  iterator res(head_);
  return res;
}

template<typename T>
typename list<T>::iterator list<T>::end() {
  // List реализован в виде кольца, поэтому
  // указатель на элемент после последнего - head
  //TODO Throw exception && Переделать, т.к.:
  // iter = list.begin(); iter != list.end(); ++iter
  iterator res(head_);
  return res;
}

// template<typename T>
// list<T>::iterator::iterator() {
//   std::cout << "PREVED!!!" << std::endl;
// }