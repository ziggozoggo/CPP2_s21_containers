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

      stack() noexcept : size_(0), list_node_() {}
      bool is_empty() {
        return list_node_.empty();
      }

    private:
      size_type size_;
      list<value_type> list_node_;
  };
}

#endif // SRC_S21_STACK_H_