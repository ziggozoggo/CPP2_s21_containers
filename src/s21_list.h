#pragma once

#include <iostream>

template<typename T>
class list {
  public:
    list() {
      fake_node_.next_ = &fake_node_;
      fake_node_.prev_ = &fake_node_;
      std::cout << "Empty constructor" << std::endl;
    }
    list(T value) : list() {
      Node new_node;
      new_node.value_ = value;
      new_node.next_ = &fake_node_;
      new_node.prev_ = &fake_node_;
      fake_node_.next_ = &new_node;
      fake_node_.prev_ = &new_node;
      std::cout << "With Param" << std::endl;
    }

  private:
    // Фейковая нода, создаваемая по умолчанию в пустом списке
    struct BaseNode {
      BaseNode *next_ = nullptr;
      BaseNode *prev_ = nullptr;
    };

    // Нода с данными
    struct Node : BaseNode {
      T value_;
    };

    BaseNode fake_node_;
};