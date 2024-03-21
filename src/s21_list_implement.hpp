#pragma once
#include "s21_list.h"

// Class implementation
/* NODES */
// template<typename T>
// list<T>::Node::Node() {

//   T* obj = reinterpret_cast<T*>(new uint8_t[sizeof(T)]);
//   is_fake_ = true;
//   std::cout << "Make fake node!" << std::endl;
// }

template<typename T>
list<T>::Node::Node(T& value) {
  //TODO logic
  value_ = value;
  std::cout << "Node with value: " << value << std::endl;
}

// template<typename T>
// list<T>::iterator::iterator() {
//   std::cout << "PREVED!!!" << std::endl;
// }

template<typename T>
list<T>::list() : size_(0), head_(nullptr), tail_(nullptr) {
  base_node_ = new BaseNode();
  //TODO Создание fake_node
}

template<typename T>
list<T>::~list() {
  if (size_ != 0) {
    // 1. Delete nodes && Free memory
    // 2. Set ptrs to null, size_ = 0
  }
}

template<typename T>
void list<T>::push_back(T value) {
  Node * new_node = new Node(value);
  // Если это первая нода в списке
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;

    head_->next_ = base_node_;
    head_->prev_ = base_node_;   
    
    base_node_->next_ = new_node;
    base_node_->prev_ = new_node;

  } else {
    new_node->prev_ = tail_;
    new_node->next_ = base_node_;
    
    tail_->next_ = new_node;
    tail_ = new_node;
  }
  
  ++size_;
}

template<typename T>
T& list<T>::get_head() {
  return head_->value_;
}

template<typename T>
T& list<T>::get_tail() {
  return tail_->value_;
}

template<typename T>
T& list<T>::get_shift() {
  Node *node = static_cast<Node*>(head_->next_);
  return node->value_;
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