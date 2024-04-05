#ifndef SRC_CORE_S21_LIST_ITERATOR_H_
#define SRC_CORE_S21_LIST_ITERATOR_H_

#include "s21_list_node.h"

namespace s21 {
  template<typename T>
  class ListIterator {
    // BidirectionalIterator
    // ++iter; iter++
    // --iter; iter--
    // *iter
    public:
      ListIterator() : ptr_(nullptr) {}
      ListIterator(ListBaseNode *ptr) : ptr_(ptr) {}

      ListBaseNode* get_ptr() { return ptr_;}

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
        return static_cast<ListNode<T>*>(ptr_)->value_;
      } 

    private:
      ListBaseNode *ptr_ = nullptr;
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

#endif //!SRC_CORE_S21_LIST_ITERATOR_H_