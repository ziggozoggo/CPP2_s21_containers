#include "s21_containers_core_test.h"
#include "../../core/s21_list.h"

TEST(s21_list_suite, empty_pop_back_exception) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.pop_back(), std::domain_error);
}

TEST(s21_list_suite, init_empty_list) {
  std::list<NoConstructClass> std_list;
  s21::list<NoConstructClass> s21_list;
  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
}

TEST(s21_list_suite, init_empty_n_list) {
  std::list<int> std_list(5);
  s21::list<int> s21_list(5);
  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.empty(), s21_list.empty());
}

TEST(s21_list_suite, basic_operations) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
}

TEST(s21_list_suite, push_back_01) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.push_back(21);
  std_list.push_back(21);
  
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
}

TEST(s21_list_suite, push_back_02) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  s21_list.push_back(168);
  std_list.push_back(168);
  
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.front(), s21_list.front());
}

TEST(s21_list_suite, iterator_clockwise01) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    ++s21_iter;
    ++std_iter;  
  }
}

TEST(s21_list_suite, iterator_clockwise02) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;  
  }
}

TEST(s21_list_suite, iterator_counterclockwise01) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.end();
  auto std_iter = std_list.end();
  s21_iter--;
  std_iter--;
  ASSERT_EQ(*std_iter, *s21_iter);

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter--;
    std_iter--;  
  }
}

TEST(s21_list_suite, iterator_counterclockwise02) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.end();
  auto std_iter = std_list.end();
  --s21_iter;
  --std_iter;
  ASSERT_EQ(*std_iter, *s21_iter);

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    --s21_iter;
    --std_iter;  
  }
}

TEST(s21_list_suite, iterator_circular_behavior) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  auto s21_iter = s21_list.end();
  auto std_iter = std_list.end();
  s21_iter++;
  std_iter++;
  ASSERT_EQ(*std_iter, *s21_iter);
}

TEST(s21_list_suite, iterator_compare) {
  s21::list<int> s21_list = {21, 42, 84};

  auto s21_iter_begin = s21_list.begin(); 
  auto s21_iter_end = s21_list.end();

  ASSERT_TRUE(s21_iter_begin != s21_iter_end);
  
  for (std::size_t i = 0; i < s21_list.size(); ++i) {
    --s21_iter_end;
  }
  
  ASSERT_TRUE(s21_iter_begin == s21_iter_end);
}

TEST(s21_list_suite, max_size) {
  s21::list<int> s21_list;
  std::list<int> std_list;
  ASSERT_EQ(std_list.max_size(), s21_list.max_size());
}







