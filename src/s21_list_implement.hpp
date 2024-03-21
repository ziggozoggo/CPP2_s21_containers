#pragma once
#include "s21_list.h"

// Class implementation
/* NODES */

template<typename T>
list<T>::Node::Node() {
  value_ = new T();
}

template<typename T>
list<T>::Node::Node(const T& value) {
  value_ = value;
}

// template<typename T>
// list<T>::Node::~Node() {
//   //~T();
//   std::cout << "Node destructor" << std::endl;
// }

template<typename T>
list<T>::list() : size_(0), head_(nullptr), tail_(nullptr) {
  base_node_ = new BaseNode();
  std::cout << "Base node address: " << &base_node_ << std::endl;
}

template<typename T>
list<T>::list(size_type count) : list() {
  T *value = new T();
  for (size_type i = 0; i < count; ++i) {
    this->push_back(*value);
  }
  
  delete value;
}

template<typename T>
list<T>::~list() {
  if (size_ != 0) {
    delete base_node_;
    delete head_;
    size_ = 0;
  }
}

template<typename T>
void list<T>::push_back(const T& value) {
  Node * new_node = new Node(value);

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
list<T>::iterator::iterator() : ptr_(nullptr) {};

template<typename T>
list<T>::iterator::iterator(BaseNode *ptr) : ptr_(ptr) {};

template<typename T>
T& list<T>::iterator::operator*() {
  // TODO throw exception
  return static_cast<Node*>(ptr_)->value_;
}

template<typename T>
typename list<T>::iterator list<T>::begin() {
  //TODO Throw exception
  return iterator(base_node_->next_);
}

template<typename T>
typename list<T>::iterator list<T>::end() {
  //TODO Throw exception
  return iterator(base_node_);
}


