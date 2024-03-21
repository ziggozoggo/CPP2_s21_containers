#pragma once

#include <iostream>

template<typename T>
class list {
  public:
    using size_type = std::size_t;
    class iterator;

    list();
    ~list();

    void push_back (T value);
    T& get_head();
    T& get_tail();
    T& get_shift();

    iterator begin(); 
    iterator end();

  private:
    struct Node {
      T value;
      Node *next;
      Node *prev;
    };
    
    size_type size_;
    Node *head_;
    Node *tail_;

  // Iterators stuff
  public:
    class iterator {
      // BidirectionalIterator
      // ++iter; iter++
      // --iter; iter--
      // *iter
      public:
        iterator() : ptr_(nullptr) {};
        iterator(Node *ptr) : ptr_(ptr) {};

        T& operator*();
      
      private:
        Node *ptr_ = nullptr;
    };
};

#include "s21_list_implement.hpp"


