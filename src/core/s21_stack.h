#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

#include "s21_container.h"
#include "s21_list.h"

namespace s21 {
  template <typename T>
  class stack {
    public:
      using size_type = std::size_t;
      using value_type = T;
      using reference = T&;
      using const_reference = const T&;

      stack() noexcept;
      stack(const std::initializer_list<value_type>& values);
      stack(const stack &other);
      stack(stack&& other);
      ~stack();

      bool empty() noexcept;
      size_type size() noexcept;
      
      void push(const_reference value);
      void pop();
      const_reference top();
      void swap(stack &other);

      stack& operator=(stack&& other);

    private:
      list<value_type> list_struct_;
  };

  template<typename value_type>
  stack<value_type>::stack() noexcept : list_struct_ {} {}

  template<typename value_type>
  stack<value_type>::stack(const std::initializer_list<value_type>& values) : stack() {
    for (const_reference e : values) {
      this->push(e);
    }
  }

  template<typename value_type>
  stack<value_type>::stack(const stack &other) : list_struct_ {other.list_struct_} {}

  template<typename value_type>
  stack<value_type>::stack(stack&& other) {
    this->swap(other);
  }

  template<typename value_type>
  stack<value_type>::~stack() {}

  template<typename value_type>
  bool stack<value_type>::empty() noexcept {
    return list_struct_.empty();
  }

  template<typename value_type>
  typename stack<value_type>::size_type stack<value_type>::size() noexcept {
    return list_struct_.size();
  }

  template<typename value_type>
  void stack<value_type>::push(const_reference value) {
    list_struct_.push_back(value);
  }

  template<typename value_type>
  void stack<value_type>::pop() {
    if (!this->empty()) {
      list_struct_.pop_back();
    }
  }

  template<typename value_type>
  typename stack<value_type>::const_reference stack<value_type>::top() {
    return list_struct_.back();
  }

  template<typename value_type>
  void stack<value_type>::swap(stack& other) {
    std::swap(this->list_struct_, other.list_struct_);
  }

  template<typename value_type>
  stack<value_type>& stack<value_type>::operator=(stack&& other) {
    this->swap(other);
    return *this;
  }
}


#endif // SRC_S21_STACK_H_