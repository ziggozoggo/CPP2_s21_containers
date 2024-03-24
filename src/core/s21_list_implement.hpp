#pragma once
#include "s21_list.h"

// Class implementation

/* NODES */

using namespace s21;

template<typename value_type>
list<value_type>::Node::Node() {
  value_ = new value_type();
}

template<typename value_type>
list<value_type>::Node::Node(const_reference value) {
  value_ = value;
}


/* LIST*/

// Constructors & Destructor
template<typename value_type>
list<value_type>::list() : size_(0), head_(nullptr), tail_(nullptr) {
  base_node_ = new BaseNode();
  // std::cout << "CREATE CONSTRUCTOR!" << std::endl;
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
list<value_type>::list(const std::initializer_list<value_type>& values) : list() {
  for (const_reference e : values) {
    this->push_back(e);
  }
}

template<typename value_type>
list<value_type>::list(const list& other) {
  size_ = 0;
  base_node_ = new BaseNode();
  head_ = nullptr;
  tail_ = nullptr;

  if (!other.empty()) {
    for (const_iterator iter = other.begin(); iter != other.end(); ++iter) {
      value_type value = *iter;
      this->push_back(value);
    }
  }
  // std::cout << "Copy constructor!!!!" << std::endl;
}

template<typename value_type>
list<value_type>::~list() {
  if (size_ != 0) {
    for (list<value_type>::size_type i = 0; i < size_; ++i) {
      this->pop_back();
    }
    size_ = 0;
  }
  // std::cout << "DESTRUCTOR!!!!" << std::endl;
  delete base_node_;
}

// Methods
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
    base_node_->prev_ = tail_;
  }
  
  ++size_;
}

template<typename value_type>
void list<value_type>::pop_back() {
  if (this->empty()) {
    throw std::domain_error("ERR: operation not defined for empty list!");
  }

  if (tail_ == head_) {
    delete tail_;
  } else {
    Node *current_tail = tail_;
    tail_ = static_cast<Node*>(current_tail->prev_);
    base_node_->prev_ = tail_;
    delete current_tail; 
  }
  --size_;
}

template<typename value_type>
bool list<value_type>::empty() const noexcept {
  return (size_) ? false : true;
}

template<typename value_type>
typename list<value_type>::size_type list<value_type>::size() const noexcept {
  return size_;
}

template<typename value_type>
typename list<value_type>::size_type list<value_type>::max_size() const noexcept {
  size_type size = (std::numeric_limits<size_type>::max() / sizeof(list<value_type>::Node)) / 2;
  return size;
}

template<typename value_type>
typename list<value_type>::const_reference list<value_type>::front() const {
  return head_->value_;
}

template<typename value_type>
typename list<value_type>::reference list<value_type>::front() {
  return head_->value_;
}

template<typename value_type>
typename list<value_type>::const_reference list<value_type>::back() const {
  return tail_->value_;
}

template<typename value_type>
typename list<value_type>::reference list<value_type>::back() {
  return tail_->value_;
}

template<typename value_type>
typename list<value_type>::iterator list<value_type>::begin() {
  return iterator(base_node_->next_);
}

template<typename value_type>
typename list<value_type>::const_iterator list<value_type>::begin() const {
  return iterator(base_node_->next_);
}

template<typename value_type>
typename list<value_type>::iterator list<value_type>::end() {
  return iterator(base_node_);
}

template<typename value_type>
typename list<value_type>::const_iterator list<value_type>::end() const {
  return iterator(base_node_);
}

template<typename value_type>
typename list<value_type>::const_reference list<value_type>::get_shift() {
  Node *node = static_cast<Node*>(head_->next_);
  return node->value_;
}

/* ITERATORS */

// Constructors
template<typename value_type>
list<value_type>::iterator::ListIterator() : ptr_(nullptr) {};

template<typename value_type>
list<value_type>::iterator::ListIterator(BaseNode *ptr) : ptr_(ptr) {};

// Operators
template<typename value_type>
typename list<value_type>::ListIterator& list<value_type>::ListIterator::operator++() {
  this->ptr_ = ptr_->next_;
  return *this;
}

template<typename value_type>
typename list<value_type>::ListIterator& list<value_type>::ListIterator::operator++(int) {
  this->ptr_ = ptr_->next_;
  return *this;
}

template<typename value_type>
typename list<value_type>::ListIterator& list<value_type>::ListIterator::operator--() {
  this->ptr_ = ptr_->prev_;
  return *this;
}

template<typename value_type>
typename list<value_type>::ListIterator& list<value_type>::ListIterator::operator--(int) {
  this->ptr_ = ptr_->prev_;
  return *this;
}

template<typename value_type>
typename list<value_type>::reference list<value_type>::iterator::operator*() {
  return static_cast<Node*>(ptr_)->value_;
}

template<typename value_type>
bool list<value_type>::ListIterator::operator==(const list<value_type>::ListIterator& other) {
  return this->ptr_ == other.ptr_;
}

template<typename value_type>
bool list<value_type>::ListIterator::operator!=(const list<value_type>::ListIterator& other) {
  return !(*this == other);
}


