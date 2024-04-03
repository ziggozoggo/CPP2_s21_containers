#pragma once

#include "s21_list_base_node.h"
#include "s21_list.h"

namespace s21 {
  template<typename T>
  class ListIterator {
    // BidirectionalIterator
    // ++iter; iter++
    // --iter; iter--
    // *iter
    public:
      ListIterator() : ptr_(nullptr) {}
      ListIterator(BaseNode *ptr) : ptr_(ptr) {}

      BaseNode* get_ptr() { return ptr_;}

      ListIterator& operator++() {
        this->ptr_ = ptr_->next_;
        return *this;
      }

      ListIterator& operator++(int) {
        this->ptr_ = ptr_->next_;
        return *this;
      }

      ListIterator& operator--() {
        this->ptr_ = ptr_->prev_;
        return *this;
      }

      ListIterator& operator--(int) {
        this->ptr_ = ptr_->prev_;
        return *this;
      }

      bool operator==(const ListIterator& other) {
        return this->ptr_ == other.ptr_;
      }

      bool operator!=(const ListIterator& other) {
        return !(*this == other);
      }

      T& operator*() {
        return static_cast<Node<T>*>(ptr_)->value_;
      } 

    private:
      BaseNode *ptr_ = nullptr;
  };

  template<typename T>
  class ListConstIterator : public ListIterator<T> {
    public:
      ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
      const T& operator*() {
        return ListIterator<T>::operator*();
      }
  };
}