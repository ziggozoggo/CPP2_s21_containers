#ifndef SRC_UNIT_S21_MATRIX_CORE_TEST_H_
#define SRC_UNIT_S21_MATRIX_CORE_TEST_H_

#include <gtest/gtest.h>

#include "s21_containers.h"

#define LOOP_TESTS_QUANTITY 50

class MockClass {
public:
  const int size_ = 10;
  int* data_;

  MockClass() : data_(new int[size_]) {
    for (int i = 0; i < size_; i++) {
      data_[i] = i * 2;
    }
  }

  ~MockClass() {
    delete[] data_;
  }
};

#endif  // SRC_UNIT_S21_MATRIX_CORE_TEST_H_