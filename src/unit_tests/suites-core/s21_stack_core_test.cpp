#include "s21_containers_core_test.h"

#include <stack>
#include "core/s21_stack.h"

TEST(s21_stack_suite, init_empty_stack) {
  std::stack<NoConstructClass> std_stack;
  s21::stack<NoConstructClass> s21_stack;
  ASSERT_EQ(std_stack.empty(), s21_stack.empty());
  ASSERT_EQ(std_stack.size(), s21_stack.size());
}

TEST(s21_stack_suite, init_list_stack) {
  s21::stack<int> s21_stack{21, 42, 84};
  int list_data[] = {21, 42, 84};
  int i = 2;
  while(!s21_stack.empty()) {
    ASSERT_EQ(list_data[i], s21_stack.top());
    s21_stack.pop();
    --i;
  }
  ASSERT_EQ(s21_stack.empty(), true);
  ASSERT_EQ(s21_stack.size(), 0);
}

TEST(s21_stack_suite, push_stack) {
  std::stack<int> std_stack;
  s21::stack<int> s21_stack;

  std_stack.push(21);
  s21_stack.push(21);

  ASSERT_EQ(std_stack.top(), s21_stack.top());

  std_stack.push(42);
  s21_stack.push(42);

  ASSERT_EQ(std_stack.top(), s21_stack.top());
}

TEST(s21_stack_suite, empty_swap) {
  s21::stack<int> s21_this;
  s21::stack<int> s21_other{21, 42, 84};

  s21_this.swap(s21_other);
  
  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), true);

  ASSERT_EQ(s21_this.size(), 3);
  ASSERT_EQ(s21_other.size(), 0);
}

TEST(s21_stack_suite, non_empty_swap) {
  s21::stack<int> s21_this{21, 42};
  s21::stack<int> s21_other{84, 96, 77, 31, 55};

  s21_this.swap(s21_other);
  
  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), false);

  ASSERT_EQ(s21_this.size(), 5);
  ASSERT_EQ(s21_other.size(), 2);

  ASSERT_EQ(s21_this.top(), 55);
  ASSERT_EQ(s21_other.top(), 42);
}

TEST(s21_stack_suite, move_constructor) {
  s21::stack<int> s21_this;
  s21::stack<int> s21_other{21, 42, 84};
  s21_this = std::move(s21_other);
  
  ASSERT_EQ(s21_this.empty(), false);
  ASSERT_EQ(s21_other.empty(), true);

  ASSERT_EQ(s21_this.size(), 3);
  ASSERT_EQ(s21_other.size(), 0);
}
