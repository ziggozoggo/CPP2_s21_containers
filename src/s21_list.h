#pragma once

#include <iostream>
#include <cstddef>

template<typename T>
class list {
  public:
    class ListIterator;
    
    using size_type = std::size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = ListIterator;

    list();
    list(size_type count);
    ~list();

    void push_back (const_reference value);
    const_reference get_head();
    const_reference get_tail();
    const_reference get_shift();

    iterator begin(); 
    iterator end();

  private:    
    struct BaseNode {
      BaseNode *next_ = nullptr;
      BaseNode *prev_ = nullptr;
    };

    struct Node : BaseNode {
      Node();
      Node(const_reference value);
      value_type value_;
    };
    
    size_type size_;
    BaseNode *base_node_;
    Node *head_;
    Node *tail_;

  // Iterators stuff
  public:
    class ListIterator {
      // BidirectionalIterator
      // ++iter; iter++
      // --iter; iter--
      // *iter
      public:
        ListIterator();
        ListIterator(BaseNode *ptr);

        const_reference operator*();
      
      private:
        BaseNode *ptr_ = nullptr;
    };
};

#include "s21_list_implement.hpp"


