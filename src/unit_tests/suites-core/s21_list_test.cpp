#include "s21_containers_core_test.h"
#include "../../core/s21_list.h"


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

TEST(s21_list_suite, copy_empty_list) {
  s21::list<int> s21_list_this;
  s21::list<int> s21_list_other(s21_list_this);
  s21::list<int> s21_list_another = s21_list_this;
  
  ASSERT_EQ(s21_list_this.size(), s21_list_other.size());
  ASSERT_EQ(s21_list_this.size(), s21_list_another.size());
}

TEST(s21_list_suite, copy_list) {
  s21::list<int> s21_list_this = {21, 42, 84, 77};
  s21::list<int> s21_list_other(s21_list_this);
  s21::list<int> s21_list_another = s21_list_this;
  
  ASSERT_EQ(s21_list_this.size(), s21_list_other.size());
  ASSERT_EQ(s21_list_this.size(), s21_list_another.size());

  s21::list<int>::const_iterator iter_this = s21_list_this.begin();
  s21::list<int>::const_iterator iter_other = s21_list_other.begin();
  s21::list<int>::const_iterator iter_another = s21_list_another.begin();

  for (std::size_t i = 0; i < s21_list_this.size(); ++i) {
    ASSERT_EQ(*iter_this, *iter_other);
    ASSERT_EQ(*iter_this, *iter_another);
    ++iter_this;
    ++iter_other;
    ++iter_another;
  }
}

TEST(s21_list_suite, move_list) {
  s21::list<std::string> s21_src_list = {"Hello", "World"};
  std::list<std::string> std_src_list = {"Hello", "World"};
  s21::list<std::string> s21_dst_list = std::move(s21_src_list);
  std::list<std::string> std_dst_list = std::move(std_src_list);
  
  ASSERT_EQ(std_src_list.size(), s21_src_list.size());
  ASSERT_EQ(std_dst_list.size(), s21_dst_list.size());

  s21::list<std::string>::iterator s21_iter = s21_dst_list.begin();
  auto std_iter = std_dst_list.begin();

  for (std::size_t i = 0; i < s21_dst_list.size(); ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    ++s21_iter;
    ++std_iter;
  }
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

TEST(s21_list_suite, push_front_01) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  s21_list.push_front(21);
  std_list.push_front(21);
  
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.size(), s21_list.size());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (std::size_t i = 0; i < s21_list.size(); ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;  
  }
}

TEST(s21_list_suite, push_front_02) {
  s21::list<int> s21_list = {21, 42, 84};
  std::list<int> std_list = {21, 42, 84};

  s21_list.push_front(168);
  std_list.push_front(168);
  
  ASSERT_EQ(std_list.back(), s21_list.back());
  ASSERT_EQ(std_list.front(), s21_list.front());
  ASSERT_EQ(std_list.size(), s21_list.size());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (std::size_t i = 0; i < s21_list.size(); ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;  
  }
}

TEST(s21_list_suite, empty_list_exceptions) {
  s21::list<int> empty_list;
  EXPECT_THROW(empty_list.pop_back(), std::out_of_range);
  EXPECT_THROW(empty_list.front(), std::out_of_range);
  EXPECT_THROW(empty_list.back(), std::out_of_range);
}

TEST(s21_list_suite,pop_back) {
  s21::list<int> s21_list = {21, 42, 84, 77};
  std::list<int> std_list = {21, 42, 84, 77};
  
  std_list.pop_back();
  s21_list.pop_back();

  ASSERT_EQ(std_list.size(), s21_list.size());
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

TEST(s21_list_suite, swap_empty) {
  s21::list<int> s21_list;
  s21::list<int> s21_list_other = {15, 25, 35};
  
  std::list<int> std_list;
  std::list<int> std_list_other = {15, 25, 35};

  s21_list.swap(s21_list_other);
  std_list.swap(std_list_other);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list_other.size(), s21_list_other.size());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;  
  }
}

TEST(s21_list_suite, swap_non_empty) {
  s21::list<int> s21_list = {21, 42, 84};
  s21::list<int> s21_list_other = {15, 25, 35};
  
  std::list<int> std_list = {21, 42, 84};
  std::list<int> std_list_other = {15, 25, 35};

  s21_list.swap(s21_list_other);
  std_list.swap(std_list_other);

  ASSERT_EQ(std_list.size(), s21_list.size());
  ASSERT_EQ(std_list_other.size(), s21_list_other.size());

  auto s21_iter = s21_list.begin();
  auto std_iter = std_list.begin();

  for (int i = 0; i < 3; ++i) {
    ASSERT_EQ(*std_iter, *s21_iter);
    s21_iter++;
    std_iter++;  
  }
}










