#ifndef SRC_S21_IITERABLE_H_
#define SRC_S21_IITERABLE_H_

#include "s21_BaseIterator.h"

namespace s21 {

template <typename T>
class IIterable
{
public:
  virtual BaseIterator<T>* begin() = 0;
  virtual BaseIterator<T>* end() = 0;
};

}

#endif  // SRC_S21_ITERABLE_H_