#include "s21_containers_core_test.h"

#include <vector>
#include <type_traits>

#include "core/s21_vector.h"

template<typename T>
void emptyInitAsContTest() {
  s21::IContainer<T>* ct = new s21::vector<T>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_EMPTY_INIT_AS_CONT(suite_name) \
TEST(suite_name, uShortEmptyInitAsCont) { emptyInitAsContTest<unsigned short>(); } \
TEST(suite_name, intEmptyInitAsCont) { emptyInitAsContTest<int>(); } \
TEST(suite_name, doubleEmptyInitAsCont) { emptyInitAsContTest<double>(); } \
TEST(suite_name, MockClassEmptyInitAsCont) { emptyInitAsContTest<MockClass>(); } \

TESTS_EMPTY_INIT_AS_CONT(s21Vector)

// -------------------

template<typename T>
void emptyInitTest() {
  s21::vector<T> actual;
  std::vector<T> expected;

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_EQ(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

#define TESTS_EMPTY_INIT(suite_name) \
TEST(suite_name, uShortEmptyInit) { emptyInitTest<unsigned short>(); } \
TEST(suite_name, intEmptyInit) { emptyInitTest<int>(); } \
TEST(suite_name, doubleEmptyInit) { emptyInitTest<double>(); } \
TEST(suite_name, MockClassEmptyInit) { emptyInitTest<MockClass>(); } \

TESTS_EMPTY_INIT(s21Vector)

// -------------------

template<typename T>
void sizeInitTest() {
  const std::size_t size = 100;

  s21::vector<T> actual(size);
  std::vector<T> expected(size);

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}


#define TESTS_SIZE_INIT(suite_name) \
TEST(suite_name, uShortSizeInit) { sizeInitTest<unsigned short>(); } \
TEST(suite_name, intSizeInit) { sizeInitTest<int>(); } \
TEST(suite_name, doubleSizeInit) { sizeInitTest<double>(); } \
TEST(suite_name, MockClassSizeInit) { sizeInitTest<MockClass>(); } \

TESTS_SIZE_INIT(s21Vector)

// -------------------

template<typename T>
void clearTest() {
  const std::size_t size = 100;

  s21::vector<T> actual(size);
  std::vector<T> expected(size);

  actual.clear();
  expected.clear();

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

#define TESTS_CLEAR(suite_name) \
TEST(suite_name, uShortClear) { clearTest<unsigned short>(); } \
TEST(suite_name, intClear) { clearTest<int>(); } \
TEST(suite_name, doubleClear) { clearTest<double>(); } \
TEST(suite_name, MockClassClear) { clearTest<MockClass>(); } \

TESTS_CLEAR(s21Vector)

// -------------------

template<typename T>
void clearAsContTest() {
  const std::size_t size = 100;

  s21::IContainer<T>* ct = new s21::vector<T>(size);

  EXPECT_EQ(ct->size(), size);
  EXPECT_FALSE(ct->empty());

  ct->clear();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_CLEAR_AS_CONT(suite_name) \
TEST(suite_name, uShortClearAsCont) { clearAsContTest<unsigned short>(); } \
TEST(suite_name, intClearAsContr) { clearAsContTest<int>(); } \
TEST(suite_name, doubleClearAsCont) { clearAsContTest<double>(); } \
TEST(suite_name, MockClassClearAsCont) { clearAsContTest<MockClass>(); } \

TESTS_CLEAR_AS_CONT(s21Vector)

// -------------------

template<typename T>
void listInitTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

#define TESTS_LIST_INIT(suite_name) \
TEST(suite_name, uShortListInit) { listInitTest<unsigned short>({1, 2, 3, 4, 5}); } \
TEST(suite_name, intListInit) { listInitTest<int>({1, 2, 3, 4, 5}); } \
TEST(suite_name, doubleListInit) { listInitTest<double>({1.42, 2.5, 0.003, 664.452, 1.0035}); } \
TEST(suite_name, MockClassListInit) { listInitTest<MockClass>({1, 2, 44, 45}); } \

TESTS_LIST_INIT(s21Vector)

// -------------------