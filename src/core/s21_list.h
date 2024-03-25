#pragma once

#include <initializer_list>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <cstddef>

namespace s21 {
  template<typename T>
  class list {
    public:
      class ListIterator;
      class ListConstIterator;
      
      using size_type = std::size_t;
      using value_type = T;
      using reference = T&;
      using const_reference = const T&;
      using iterator = ListIterator;
      using const_iterator = ListConstIterator;

      list();
      list(size_type count);
      list(const std::initializer_list<value_type>& values);

      list(const list& other);
      list(list&& other);

      ~list();

      void swap(list& other);

      void push_back (const_reference value);
      void pop_back ();
      void push_front(const_reference value);
      void pop_front();

      iterator erase(iterator pos);
      void clear() noexcept;

      bool empty() const noexcept;
      size_type size() const noexcept;
      size_type max_size() const noexcept;

      const_reference front() const;
      const_reference back() const;
      reference front();
      reference back();


      const_reference get_shift();

      iterator begin();
      const_iterator begin() const; 
      iterator end();
      const_iterator end() const;

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


          ListIterator& operator ++();
          ListIterator& operator ++(int);
          ListIterator& operator --();
          ListIterator& operator --(int);

          reference operator*();
          bool operator ==(const ListIterator& other);
          bool operator !=(const ListIterator& other);

          BaseNode* get_ptr() { return ptr_;}
        
        private:
          BaseNode *ptr_ = nullptr;
      };

      class ListConstIterator : public ListIterator {
        public:
          ListConstIterator(ListIterator other) : ListIterator(other) {}
          const_reference operator*() {
            return ListIterator::operator*();
          }
      };
      
      // class ListConstIterator : public ListIterator<value_type> {
      //   public:
      //     ListConstIterator(ListIterator<value_type> other) : ListIterator<value_type>(other) {}
      //     const_reference operator*() {
      //       return ListIterator<value_type>::operator*();
      //     }
      // };
  };
}



#include "s21_list_implement.hpp"


