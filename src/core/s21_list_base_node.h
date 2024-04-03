#pragma once

namespace s21 {
  struct BaseNode {
    BaseNode() : next_(this), prev_(this) {}
    BaseNode *next_;
    BaseNode *prev_;
  };

  template<typename T>
  struct Node : BaseNode {
    Node() : value_(T()) {}
    Node(const T& value) : value_(value) {}
    T value_;
  };
}