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
  using typename IContainer::size_type;
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
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();

  static size_type max_size();

  virtual size_type size() const noexcept override;
  virtual bool empty() const noexcept override;
  virtual void clear() override;

  size_type capacity() const noexcept;

  value_type* data() const noexcept;

  iterator begin();
  const_iterator begin() const;

  iterator end();
  const_iterator end() const;

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  const_reference front() const;
  const_reference back() const;

  void reserve(size_type size);
  void shrink_to_fit();

  void swap(vector<value_type>& other) noexcept;
  void push_back(const_reference value);

  bool operator==(const vector<value_type>& other) const;
  bool operator!=(const vector<value_type>& other) const;

  vector<value_type>& operator=(const vector<value_type>& other);
  vector<value_type>& operator=(vector<value_type>&& other);

// Data
private:
  size_type size_;
  size_type capacity_;
  value_type* data_;

// Private Methods
private:
void replaceData(value_type* newData);
void setCapacity(size_type newCapacity);

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
  , data_     { nullptr } {}

template<typename T>
vector<T>::vector(size_type n)
  : size_     { n }
  , capacity_ { n }
  , data_     { nullptr } {
  if (capacity_ > max_size()) throw std::length_error("Cannot create s21::vector larger than max_size()");

  data_ = new T[capacity_];
}

template<typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
  : size_     { items.size() }
  , capacity_ { items.size() }
  , data_     { nullptr } {
  if (capacity_ > max_size()) throw std::length_error("Cannot create s21::vector larger than max_size()");

  data_ = new T[capacity_];
  std::copy(items.begin(), items.end(), data_);
}

template<typename T>
vector<T>::vector(const vector& other)
  : size_     { other.size_ }
  , capacity_ { other.capacity_ }
  , data_     { new T[capacity_] } {
  std::copy(other.data_, other.data_ + size_, data_);
}

template<typename T>
vector<T>::vector(vector&& other) noexcept
  : size_     { other.size_ }
  , capacity_ { other.capacity_ }
  , data_     { other.data_ }
{
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
typename vector<T>::size_type vector<T>::max_size() {
  return ((std::numeric_limits<size_type>::max() / sizeof(T)) / 4294967296); // #NOTE: 2^32
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

template<typename value_type>
typename vector<value_type>::reference vector<value_type>::at(size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index out of vector boundary");

  return data_[pos];
}

template<typename value_type>
typename vector<value_type>::const_reference vector<value_type>::at(size_type pos) const {
  if (pos >= size_) throw std::out_of_range("Index out of vector boundary");

  return data_[pos];
}

template<typename value_type>
typename vector<value_type>::reference vector<value_type>::operator[](size_type pos) {
  return data_[pos];
}

template<typename value_type>
typename vector<value_type>::const_reference vector<value_type>::operator[](size_type pos) const {
  return data_[pos];
}

template<typename value_type>
void vector<value_type>::replaceData(value_type* newData) {
  if (newData == nullptr) throw std::invalid_argument("newData argument cannot be null");

  if (data_ != nullptr) {
    for (size_type i = 0; i < size_; i++) {
      newData[i] = std::move(data_[i]);
    }

    delete[] data_;
  }

  data_ = newData;
}

template<typename value_type>
void vector<value_type>::setCapacity(size_type newCapacity) {
  capacity_ = newCapacity;
  if (capacity_ > max_size()) throw std::length_error("Cannot expand s21::vector larger than max_size()");

  value_type* newData = new value_type[capacity_];
  replaceData(newData);
}

template<typename value_type>
void vector<value_type>::reserve(size_type size) {
  if (size <= capacity_) return;
  setCapacity(size);
}

template<typename value_type>
void vector<value_type>::shrink_to_fit() {
  if (size_ == capacity_) return;
  setCapacity(size_);
}

template<typename T>
void vector<T>::clear() {
  if (data_ != nullptr) delete[] data_;
  data_ = new T[capacity_];
  size_ = 0;
}

template<typename T>
void vector<T>::swap(vector<T>& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
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

template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& other) {
  if (this == &other) {
    return *this;
  }

  vector<T> tmp { other };
  this->swap(tmp);

  return *this;
}

template<typename T>
vector<T>& vector<T>::operator=(vector<T>&& other) {
  vector<T> tmp { std::move(other) };
  this->swap(tmp);

  return *this;
}

template<typename value_type>
typename vector<value_type>::const_reference vector<value_type>::front() const {
  return data_[0];
}

template<typename value_type>
typename vector<value_type>::const_reference vector<value_type>::back() const {
  return data_[size_ - 1];
}

template<typename value_type>
void vector<value_type>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    if (capacity_ == 0) {
      setCapacity(1);
    } else {
      setCapacity(capacity_ * 2);
    }
  }

  data_[size_++] = value;
}

}

#endif  // SRC_S21_VECTOR_H_