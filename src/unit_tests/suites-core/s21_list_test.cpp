#include "s21_containers_core_test.h"
#include "../core/s21_list.h"

TEST(s21_list_suite, empty_pop_back_exception) {
  list<int> empty_list;
  EXPECT_THROW(empty_list.pop_back(), std::domain_error);
}