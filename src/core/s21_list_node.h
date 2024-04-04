#ifndef SRC_CORE_S21_LIST_NODE_H_
#define SRC_CORE_S21_LIST_NODE_H_

#pragma once

namespace s21 {
  struct ListBaseNode {
    ListBaseNode() : next_(this), prev_(this) {}
    ListBaseNode *next_;
    ListBaseNode *prev_;
  };

  template<typename T>
  struct ListNode : ListBaseNode {
    ListNode() : value_(T()) {}
    ListNode(const T& value) : value_(value) {}
    T value_;
  };
}

#endif //!SRC_CORE_S21_LIST_NODE_H_