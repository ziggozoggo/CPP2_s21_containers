#ifndef SRC_CORE_S21_LIST_H_
#define SRC_CORE_S21_LIST_H_

#include <initializer_list>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <cstddef>


#include "s21_list_iterator.h"
#include "s21_list_node.h"

namespace s21 {
  template<typename T>
  class list {
    public:
      //class ListIterator;
      //class ListConstIterator;
      
      using size_type = std::size_t;
      using value_type = T;
      using reference = T&;
      using const_reference = const T&;
      using iterator = ListIterator<value_type>;
      using const_iterator = ListConstIterator<value_type>;

      list();
      list(size_type count);
      list(const std::initializer_list<value_type>& values);

      list(const list& other);
      list(list&& other);

      ~list();

      void swap(list& other);
      void merge_insert(const list& other);
      void merge(list& other);
      void reverse() noexcept;
      void unique();
      void splice(const_iterator pos, list& other);
      void sort();
      list& operator=(list&& other);

      void push_back (const_reference value);
      void pop_back();
      void push_front(const_reference value);
      void pop_front();
      iterator insert(iterator pos, const_reference value);


      iterator erase(iterator pos);
      void clear() noexcept;

      bool empty() const noexcept;
      size_type size() const noexcept;
      size_type max_size() const noexcept;

      const_reference front() const;
      const_reference back() const;
      reference front();
      reference back();

      void print_list();
      void print_reverse_list();

      iterator begin();
      const_iterator begin() const; 
      iterator end();
      const_iterator end() const;

      template<class... Args>
      void insert_many_back(Args&&... args);
      template<class... Args>
      void insert_many_front(Args&&... args);
      template<class... Args>
      iterator insert_many(const_iterator pos, Args&&... args);

    private: 

      size_type size_;
      ListBaseNode *base_node_;
      ListNode<value_type> *head_;
      ListNode<value_type> *tail_;

      void merge_data(const_iterator& this_iterator, const_iterator& other_iterator);
      void merge_tail(list& other, const_iterator& other_iterator);
  };
}



#include "s21_list_implement.hpp"

#endif //!SRC_CORE_S21_LIST_H_
