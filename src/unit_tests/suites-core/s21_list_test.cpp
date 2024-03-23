#include "s21_containers_core_test.h"
#include "../core/s21_list.h"

TEST(s21_list_suite, empty_pop_back_exception) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.pop_back(), std::domain_error);
}

TEST(s21_list_suite, init_empty_list) {
  std::list<NoConstructClass> std_list;
  s21::list<NoConstructClass> s21_list;
  ASSERT_EQ(std_list.size(), s21_list.size());
}





