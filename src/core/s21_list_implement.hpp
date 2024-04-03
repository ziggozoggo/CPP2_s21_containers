#ifndef SRC_CORE_S21_LIST_IMPLEMENT_H_
#define SRC_CORE_S21_LIST_IMPLEMENT_H_

#include "s21_list.h"

// Class implementation

/* LIST*/

// Constructors & Destructor
template<typename value_type>
s21::list<value_type>::list() : size_(0), base_node_(new BaseNode()), head_(nullptr), tail_(nullptr) {
  // std::cout << "CREATE CONSTRUCTOR!" << std::endl;
}

template<typename value_type>
s21::list<value_type>::list(size_type count) : list() {
  if (count > this->max_size()) {
    throw std::length_error("size more than max_size for that list!");
  }

  for (size_type i = 0; i < count; ++i) {
    this->push_back(value_type());
  }
  
}

template<typename value_type>
s21::list<value_type>::list(const std::initializer_list<value_type>& values) : list() {
  for (const_reference e : values) {
    this->push_back(e);
  }
}

template<typename value_type>
s21::list<value_type>::list(const list& other) : list() {
  if (!other.empty()) {
    for (const_iterator iter = other.begin(); iter != other.end(); ++iter) {
      this->push_back(*iter);
    }
  }
  // std::cout << "Copy constructor!!!!" << std::endl;
}

template<typename value_type>
s21::list<value_type>::list(list&& other) {
  // list&& other <- rvalue reference 
  this->swap(other);

  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.base_node_ = new BaseNode();

  // std::cout << "Move constructor!!!!" << std::endl;
}

template<typename value_type>
s21::list<value_type>::~list() {
  this->clear();
  // std::cout << "DESTRUCTOR!!!!" << std::endl;
  delete base_node_;
}

// Methods
template<typename value_type>
void s21::list<value_type>::swap(list& other) {
  std::swap(this->size_, other.size_);
  std::swap(this->base_node_, other.base_node_);
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
}

template<typename value_type>
void s21::list<value_type>::merge_insert(const list& other) {
  if (other.empty()) return;
  const_iterator this_iterator = this->begin();
  const_iterator other_iterator = other.begin();

  while (this_iterator != this->end() && other_iterator != other.end()) {
    if (*this_iterator <= *other_iterator) {
      ++this_iterator;
    } else {
      this_iterator = this->insert(this_iterator, *other_iterator);
      ++other_iterator;
      ++this_iterator;
    }
  }

  if (other_iterator != other.end()) {
    for (; other_iterator != other.end(); ++other_iterator) {
      this->push_back(*other_iterator);
    }
  }
}

template<typename value_type>
void s21::list<value_type>::merge(list& other) {
  if (other.empty()) return;
  
  const_iterator other_iterator = other.begin();
  const_iterator this_iterator = this->begin();

  while (this_iterator != this->end() && other_iterator != other.end()) {
    this->merge_data(this_iterator, other_iterator);
  }
  
  if (other_iterator != other.end()) {
    this->merge_tail(other, other_iterator);    
  }

  other.base_node_->next_ = other.base_node_;
  other.base_node_->prev_ = other.base_node_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;

}

template<typename value_type>
void s21::list<value_type>::merge_data(const_iterator& this_iterator, const_iterator& other_iterator) {
  if (*this_iterator <= *other_iterator) {
    ++this_iterator;
  } else {
    Node<value_type> *other_node = static_cast<Node<value_type>*>(other_iterator.get_ptr());
    Node<value_type> *current_node = static_cast<Node<value_type>*>(this_iterator.get_ptr());
    ++other_iterator;

    other_node->prev_ = current_node->prev_;
    other_node->next_ = current_node;
    current_node->prev_->next_ = other_node;
    current_node->prev_ = other_node;

    if (this->head_ == current_node) {
      this->head_ = other_node;
    }
    
    ++size_;
  }
}

template<typename value_type>
void s21::list<value_type>::merge_tail(list& other, const_iterator& other_iterator) {
  BaseNode *other_node = other_iterator.get_ptr();

  if (this->head_ == nullptr) {
    this->base_node_->next_ = other_node;
    this->head_ = static_cast<Node<value_type>*>(other_node);
    other_node->prev_ = base_node_;
  } else {
    this->tail_->next_ = other_node;
    other_node->prev_ = this->tail_;
  }

  size_type counter = 0;
  for (; other_iterator != other.end(); ++other_iterator) {
    ++counter;
  }
  size_ += counter;

  this->tail_ = other.tail_;
  this->tail_->next_ = this->base_node_;
  this->base_node_->prev_ = this->tail_;
}

template<typename value_type>
void s21::list<value_type>::reverse() noexcept {
  if (this->empty()) return;
  
  head_->prev_ = nullptr;
  tail_->next_ = nullptr;

  Node<value_type> *curr = head_;

  while (curr != nullptr) {
    Node<value_type> *temp = static_cast<Node<value_type>*>(curr->next_);
    curr->next_ = curr->prev_;
    if (temp != nullptr) {
      curr->prev_ = temp;
      curr = temp;
    } else {
      curr->prev_ = nullptr;
      curr = nullptr;
    }
  }

  std::swap(head_, tail_);
  std::swap(base_node_->next_, base_node_->prev_);  
  head_->prev_ = base_node_;
  tail_->next_ = base_node_;
}

template<typename value_type>
void s21::list<value_type>::unique() {
  if (this->empty() || this->size_ == 1) return;
  
  iterator iter = this->begin();
  value_type current_value = *iter;
  ++iter;

  while (iter != this->end()) {
    if (current_value == *iter) {
      iter = this->erase(iter);
    } else {
      current_value = *iter;
      ++iter;
    }
  }
}

template<typename value_type>
void s21::list<value_type>::splice(const_iterator pos, list& other) {
  if (other.empty()) return;
  
  BaseNode *current_node = pos.get_ptr();
  
  other.head_->prev_ = current_node->prev_;
  other.tail_->next_ = current_node;
  current_node->prev_->next_ = other.head_;
  current_node->prev_ = other.tail_;

  if (this->head_ == static_cast<Node<value_type>*>(current_node) || 
      this->head_ == nullptr) {
    this->head_ = other.head_;
  }

  if (pos == this->end()) {
    this->tail_ = other.tail_; 
  }
  
  this->size_ += other.size_;

  other.base_node_->next_ = other.base_node_;
  other.base_node_->prev_ = other.base_node_;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.size_ = 0;
}

template<typename value_type>
void s21::list<value_type>::sort() {
  if (size_ <= 1) return;
  size_type medium = size_ / 2;
  size_type init_size = size_;
  size_type counter = 0;

  list<value_type> tmp_left;
  list<value_type> tmp_right;
  const_iterator iter_this = this->begin();
  const_iterator iter_left = tmp_left.begin();
  const_iterator iter_right = tmp_right.begin();

  for (; counter < medium; ++counter) {
    tmp_left.insert(iter_left, *iter_this);
    iter_this = this->erase(iter_this);
    ++iter_left;
  }

  for (; counter < init_size; ++counter) {
    tmp_right.insert(iter_right, *iter_this);
    iter_this = this->erase(iter_this);
    ++iter_right;
  }

  tmp_left.sort();
  tmp_right.sort();
  
  tmp_left.merge(tmp_right);
  this->merge(tmp_left);
}

template<typename value_type>
s21::list<value_type>& s21::list<value_type>::operator=(list&& other) {
  this->clear();
  this->splice(this->begin(), other);
  return *this;
}

template<typename value_type>
void s21::list<value_type>::push_back(const_reference value) {
  Node<value_type> * new_node = new Node<value_type>(value);

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
void s21::list<value_type>::pop_back() {
  if (this->empty()) {
    throw std::out_of_range("operation not defined for empty list!");
  }

  if (tail_ == head_) {
    delete tail_;
    base_node_->next_ = base_node_;
    base_node_->prev_ = base_node_;
    tail_ = nullptr;
    head_ = nullptr;
  } else {
    Node<value_type> *current_tail = tail_;
    tail_ = static_cast<Node<value_type>*>(current_tail->prev_);
    tail_->next_ = base_node_;
    base_node_->prev_ = tail_;
    delete current_tail; 
  }
  --size_;
}

template<typename value_type>
void s21::list<value_type>::push_front(const_reference value) {
  Node<value_type> *new_node = new Node<value_type>(value);
  if (head_ == nullptr) {
    head_ = new_node;
    tail_ = new_node;

    head_->next_ = base_node_;
    head_->prev_ = base_node_;   
    
    base_node_->next_ = new_node;
    base_node_->prev_ = new_node;

  } else {
    new_node->prev_ = base_node_;
    new_node->next_ = head_;

    head_->prev_ = new_node;
    head_ = new_node;
    base_node_->next_ = head_;
  }
  ++size_;
}

template<typename value_type>
void s21::list<value_type>::pop_front() {
  if (this->empty()) {
    throw std::out_of_range("operation not defined for empty list!");
  }
  if (head_ == tail_) {
    delete head_;
    base_node_->next_ = base_node_;
    base_node_->prev_ = base_node_;
    tail_ = nullptr;
    head_ = nullptr;
  } else {
    Node<value_type> *current_head = head_;
    head_ = static_cast<Node<value_type>*>(current_head->next_);
    base_node_->next_ = head_;
    if (head_ == tail_) {
      head_->prev_ = base_node_;
    }
    delete current_head;
  }
  --size_;
}

template<typename value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::insert(iterator pos, const_reference value) {
  if (this->empty()) {
    this->push_back(value);
    return this->begin();
  }

  if (pos == this->end()) {
    this->push_back(value);
    return --this->end();
  }
  
  if (pos == this->begin()) {
    this->push_front(value);
    return this->begin();
  }

  Node<value_type> *current_node = static_cast<Node<value_type>*>(pos.get_ptr());
  Node<value_type> *new_node = new Node<value_type>(value);

  new_node->next_ = current_node;
  new_node->prev_ = current_node->prev_;

  current_node->prev_->next_ = new_node;
  current_node->prev_ = new_node;
  
  ++size_;

  return iterator(new_node);
}


/**
 * @brief Удаления значения, на которое указывает итератора
 * @param pos Итератор
 * @return Итератор следующего элемента; если очищается последний - итератор на end(); 
 */

template<typename value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::erase(iterator pos) {
  
  if (this->empty()) {
    throw std::out_of_range("operation not defined for empty list!");
  }

  if (size_ == 1) {
    this->pop_back();
    return this->end();
  }

  if (pos == this->begin()) {
    this->pop_front();
    return this->begin();
  }

  if (pos == --this->end()) {
    this->pop_back();
    return this->end();
  }
  
  Node<value_type> *current_node = static_cast<Node<value_type>*>(pos.get_ptr());
  ++pos;

  BaseNode *prev_node = current_node->prev_;
  BaseNode *next_node = current_node->next_;

  prev_node->next_ = next_node;
  next_node->prev_ = prev_node;

  --size_;
  delete current_node;

  return pos;
}

template<typename value_type>
void s21::list<value_type>::clear() noexcept {
  while(!this->empty()) {
    this->pop_back();
  }
}

template<typename value_type>
bool s21::list<value_type>::empty() const noexcept {
  return (size_ == 0) ? true : false;
}

template<typename value_type>
typename s21::list<value_type>::size_type s21::list<value_type>::size() const noexcept {
  return size_;
}

template<typename value_type>
typename s21::list<value_type>::size_type s21::list<value_type>::max_size() const noexcept {
  size_type size = (std::numeric_limits<size_type>::max() / sizeof(Node<value_type>)) / 2;
  return size;
}

template<typename value_type>
typename s21::list<value_type>::const_reference s21::list<value_type>::front() const {
  if (this->empty()) {
    throw std::out_of_range("operation not defined for empty list!");
  }
  return head_->value_;
}

template<typename value_type>
typename s21::list<value_type>::reference s21::list<value_type>::front() {
  if (this->empty()) {
    throw std::out_of_range("operation not defined for empty list!");
  }
  return head_->value_;
}

template<typename value_type>
typename s21::list<value_type>::const_reference s21::list<value_type>::back() const {
  if (this->empty()) {
    throw std::out_of_range("operation not defined for empty list!");
  }
  return tail_->value_;
}

template<typename value_type>
typename s21::list<value_type>::reference s21::list<value_type>::back() {
  if (this->empty()) {
    throw std::out_of_range("operation not defined for empty list!");
  }
  return tail_->value_;
}

template<typename value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::begin() {
  return iterator(base_node_->next_);
}

template<typename value_type>
typename s21::list<value_type>::const_iterator s21::list<value_type>::begin() const {
  return iterator(base_node_->next_);
}

template<typename value_type>
typename s21::list<value_type>::iterator s21::list<value_type>::end() {
  return iterator(base_node_);
}

template<typename value_type>
typename s21::list<value_type>::const_iterator s21::list<value_type>::end() const {
  return iterator(base_node_);
}

template<typename value_type>
template<class... Args>
void s21::list<value_type>::insert_many_back(Args&&... args) {
  for (auto arg : {args...}) {
    this->push_back(arg);
  }
}

template<typename value_type>
template<class... Args>
void s21::list<value_type>::insert_many_front(Args&&... args) {
  for (auto arg : {args...}) {
    this->push_front(arg);
  }
}

template<typename value_type>
template<class... Args>
typename s21::list<value_type>::iterator s21::list<value_type>::insert_many(const_iterator pos, Args&&... args) {
  // Inserts value before pos.
  // return: Iterator pointing to the inserted value.
  for (auto arg : {args...}) {
    pos = this->insert(pos, arg);
  }
  return pos;
}

template<typename value_type>
void s21::list<value_type>::print_list() {
  for (const_iterator iter = this->begin(); iter != this->end(); ++iter) {
    std::cout << *iter << " "; 
  }
  std::cout << std::endl;
}

template<typename value_type>
void s21::list<value_type>::print_reverse_list() {
  for (const_iterator iter = --this->end(); iter != this->end(); --iter) {
    std::cout << *iter << " "; 
  }
  std::cout << std::endl;
}

/* ITERATORS */



// template<typename value_type>
// bool s21::list<value_type>::ListIterator::operator==(const list<value_type>::ListIterator& other) {
//   return this->ptr_ == other.ptr_;
// }

// template<typename value_type>
// bool s21::list<value_type>::ListIterator::operator!=(const list<value_type>::ListIterator& other) {
//   return !(*this == other);
// }

#endif //!SRC_CORE_S21_LIST_IMPLEMENT_H_
