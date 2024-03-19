#include "s21_list.h"

template<typename T>
list<T>::list() {
  std::cout << "TEST" << std::endl;
}

template class list<int>;

template<typename T>
list<T>::list(T value) : list() {
  Node new_node;
  new_node.value_ = value;
  new_node.next_ = &fake_node_;
  new_node.prev_ = &fake_node_;
  std::cout << "With params" << std::endl;
}
