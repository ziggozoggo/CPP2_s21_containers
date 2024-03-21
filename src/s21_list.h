#pragma once

#include <iostream>
#include <cstddef>

template<typename T>
class list {
  public:
    using size_type = std::size_t;
    class iterator;

    list();
    list(size_type count);
    ~list();

    void push_back (const T& value);
    T& get_head();
    T& get_tail();
    T& get_shift();

    iterator begin(); 
    iterator end();

  private:    
    struct BaseNode {
      BaseNode *next_ = nullptr;
      BaseNode *prev_ = nullptr;
    };

    struct Node : BaseNode {
      Node();
      Node(const T& value);
      //~Node();
      T value_;
    };
    
    size_type size_;
    BaseNode *base_node_;
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


