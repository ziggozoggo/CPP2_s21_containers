#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#ifdef DEBUG
#include <iostream>
#include <typeinfo>
#include <utility>
#endif

#include <limits>
#include <algorithm>

#include "s21_container.h"

namespace s21 {

template <typename T>
class VectorIterator {
// Types
public:
  using difference_type = std::ptrdiff_t;
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using iterator_category = std::random_access_iterator_tag;
  using const_reference = const T&;

// Public Methods
public:
  VectorIterator(T* ptr) : ptr_(ptr) {}
  VectorIterator(VectorIterator& other) : ptr_(other.ptr_) {}

  VectorIterator<T>& operator++() {
    ++ptr_;
    return *this;
  }

  VectorIterator<T> operator++(int) {
    VectorIterator<T> temp = *this;
    ++ptr_;
    return temp;
  }

  VectorIterator<T>& operator--() {
    --ptr_;
    return *this;
  }

  VectorIterator<T> operator--(int) {
    VectorIterator<T> temp = *this;
    --ptr_;
    return temp;
  }

  bool operator==(VectorIterator<T>& other) const {
    return (ptr_ == other.ptr_);
  }

  bool operator!=(VectorIterator<T>& other) const {
    return !(*this == other);
  }

  T& operator*() const {
    return *ptr_;
  }

// Data
private:
  T* ptr_;
};

template<typename T>
class VectorConstIterator : public VectorIterator<T> {
public:
  VectorConstIterator(VectorIterator<T> other) : VectorIterator<T>(other) {}
  const T& operator*() {
    return VectorIterator<T>::operator*();
  }
};

template <typename T>
class vector : public IContainer {

// Types
public:
  using size_type = std::size_t;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator<value_type>;
  using const_iterator = VectorConstIterator<value_type>;

// Public Methods
public:
  vector() noexcept;
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector<value_type> &v);
  vector(vector<value_type> &&v) noexcept;
  ~vector();

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;

  virtual size_type size() const noexcept override;
  virtual size_type max_size() const noexcept override;
  virtual bool empty() const noexcept override;

  size_type capacity() const noexcept;
  value_type* data() const noexcept;

  virtual void clear() override;

  bool operator==(const vector<value_type>& other) const;
  bool operator!=(const vector<value_type>& other) const;

// Data
private:
  size_type size_;
  size_type capacity_;
  value_type* data_;

// Private Methods
private:
#ifdef DEBUG
void printDebugInfo() {
    std::cout << "Vector: " << std::endl;
    std::cout << "\tValues type: " << typeid(decltype(std::declval<value_type>())).name() << std::endl;
    std::cout << "\tSize: " << size_ << std::endl;
    std::cout << "\tCapacity: " << capacity_ << std::endl;
}
#endif
};

template<typename T>
vector<T>::vector() noexcept
  : size_     { 0 }
  , capacity_ { 0 }
  , data_     { nullptr } {
  #ifdef DEBUG
    printDebugInfo();
  #endif
}

template<typename T>
vector<T>::vector(size_type n)
  : size_     { n }
  , capacity_ { n }
  , data_     { new T[capacity_] } {
  #ifdef DEBUG
    printDebugInfo();
  #endif
}

template<typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
  : size_     { items.size() }
  , capacity_ { items.size() }
  , data_     { new T[capacity_] } {
  #ifdef DEBUG
    printDebugInfo();
  #endif

  std::copy(items.begin(), items.end(), data_);
}

template<typename T>
vector<T>::vector(const vector<T>& other)
  : size_     { other.size_ }
  , capacity_ { other.capacity_ }
  , data_     { new T[capacity_] } {
  #ifdef DEBUG
    printDebugInfo();
  #endif

  std::copy(other.data_, other.data_ + size_, data_);
}

template<typename T>
vector<T>::vector(vector<T>&& other) noexcept
  : size_     { other.size_ }
  , capacity_ { other.capacity_ }
  , data_     { other.data_ }
{
  #ifdef DEBUG
    printDebugInfo();
  #endif

  if (this != &other) {
    other.size_ = 0;
    other.capacity_ = 0;
    other.data_ = nullptr;
  }
}

template<typename T>
vector<T>::~vector() {
  if (data_ != nullptr) delete[] data_;
}

template<typename T>
typename vector<T>::iterator vector<T>::begin() {
  return iterator(&data_[0]);
};

template<typename T>
typename vector<T>::const_iterator vector<T>::begin() const {
  return const_iterator(&data_[0]);
};

template<typename T>
typename vector<T>::iterator vector<T>::end() {
  return iterator(&data_[size_]);
};

template<typename T>
typename vector<T>::const_iterator vector<T>::end() const {
  return const_iterator(&data_[size_]);
};

template<typename T>
typename vector<T>::size_type vector<T>::size() const noexcept {
  return size_;
}

template<typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return ((std::numeric_limits<size_type>::max() / sizeof(T)) / 2);
}

template<typename T>
bool vector<T>::empty() const noexcept {
  return (size_ == 0);
}

template<typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

template<typename T>
T* vector<T>::data() const noexcept {
  return data_;
}

template<typename T>
void vector<T>::clear() {
  if (data_ != nullptr) delete[] data_;
  data_ = new T[capacity_];
  size_ = 0;
}

template<typename T>
bool vector<T>::operator==(const vector<T>& other) const {
  if (size() != other.size()) return false;

  return (std::equal(begin(), end(), other.begin()));
}

template<typename T>
bool vector<T>::operator!=(const vector<T>& other) const {
  return !(*this == other);
}

}

#endif  // SRC_S21_VECTOR_H_