#pragma once

#include <iostream>

template<typename T>
class list {
  public:
    using size_type = std::size_t;
    
    list();
    ~list();

    void push_back (T value);
    T& get_head();
    T& get_tail();
    T& get_shift();

  private:
    struct Node {
      T value;
      Node *next;
      Node *prev;
    };
    
    size_type size_;
    Node *head_;
    Node *tail_;
};

#include "s21_list_implement.hpp"


