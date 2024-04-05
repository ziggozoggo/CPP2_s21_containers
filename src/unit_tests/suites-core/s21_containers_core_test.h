#ifndef SRC_UNIT_S21_MATRIX_CORE_TEST_H_
#define SRC_UNIT_S21_MATRIX_CORE_TEST_H_

#include <gtest/gtest.h>
#include <list>

#include "core/s21_container.h"

#define LOOP_TESTS_QUANTITY 50

class NoConstructClass {
  NoConstructClass() = delete;
  int inner_value = 5;
};

#endif  // SRC_UNIT_S21_MATRIX_CORE_TEST_H_