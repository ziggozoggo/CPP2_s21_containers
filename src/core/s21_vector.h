#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

#ifdef DEBUG
#include <iostream>
#include <typeinfo>
#include <utility>
#endif

#include <limits>

#include "s21_BaseIterator.h"
#include "s21_container.h"

namespace s21 {

template <typename T>
class VectorIterator : public BaseIterator<T> {
public:
  virtual VectorIterator<T>& operator++()    override { return *this; };
  virtual VectorIterator<T>& operator++(int) override { return *this; };
  virtual VectorIterator<T>& operator--()    override { return *this; };
  virtual VectorIterator<T>& operator--(int) override { return *this; };
};

template <typename T>
class vector : public IContainer<T> {

// Types
public:
  using typename IContainer<T>::size_type;
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = VectorIterator<value_type>;

// Public Methods
public:
  vector() noexcept;
  vector(size_type n);
  // vector(std::initializer_list<value_type> const &items);
  // vector(const vector &v);
  // vector(vector &&v);
  ~vector();

  virtual size_type size() const noexcept override;
  virtual size_type max_size() const noexcept override;
  virtual bool empty() const noexcept override;

  size_type capacity() const noexcept;
  value_type* data() const noexcept;

  virtual void clear() override;

  virtual void swap(IContainer<value_type>& other) noexcept override { (void)other; };

  virtual iterator* begin() override { return nullptr; };
  virtual iterator* end() override { return nullptr; };

  virtual vector<value_type>& operator=(const IContainer<value_type>& other) { (void)other; return *this; };
  virtual vector<value_type>& operator=(IContainer<value_type>&& other) noexcept { (void)other; return *this; };

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
  : size_(0), capacity_(0), data_(nullptr) {
  #ifdef DEBUG
    printDebugInfo();
  #endif
}

template<typename T>
vector<T>::vector(size_type n)
  : size_(n), capacity_(n), data_(new T[capacity_]) {
  #ifdef DEBUG
    printDebugInfo();
  #endif
}

template<typename T>
vector<T>::~vector() {
  if (data_ != nullptr) delete[] data_;
}

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

}

#endif  // SRC_S21_VECTOR_H_