#pragma once
#include "s21_list.h"

// Class implementation
/* NODES */

template<typename value_type>
list<value_type>::Node::Node() {
  value_ = new value_type();
}

template<typename value_type>
list<value_type>::Node::Node(const_reference value) {
  value_ = value;
}

template<typename value_type>
list<value_type>::list() : size_(0), head_(nullptr), tail_(nullptr) {
  base_node_ = new BaseNode();
}

template<typename value_type>
list<value_type>::list(size_type count) : list() {
  value_type *value = new value_type();
  for (size_type i = 0; i < count; ++i) {
    this->push_back(*value);
  }
  
  delete value;
}

template<typename value_type>
list<value_type>::~list() {
  if (size_ != 0) {
    delete base_node_;
    delete head_;
    size_ = 0;
  }
}

template<typename value_type>
void list<value_type>::push_back(const_reference value) {
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

template<typename value_type>
typename list<value_type>::const_reference list<value_type>::get_head() {
  return head_->value_;
}

template<typename value_type>
typename list<value_type>::const_reference list<value_type>::get_tail() {
  return tail_->value_;
}

template<typename value_type>
typename list<value_type>::const_reference list<value_type>::get_shift() {
  Node *node = static_cast<Node*>(head_->next_);
  return node->value_;
}

/* ITERATORS */

template<typename value_type>
list<value_type>::iterator::ListIterator() : ptr_(nullptr) {};

template<typename value_type>
list<value_type>::iterator::ListIterator(BaseNode *ptr) : ptr_(ptr) {};

template<typename value_type>
typename list<value_type>::const_reference list<value_type>::iterator::operator*() {
  return static_cast<Node*>(ptr_)->value_;
}

template<typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(base_node_->next_);
}

template<typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(base_node_);
}


