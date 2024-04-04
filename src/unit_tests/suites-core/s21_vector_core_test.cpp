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

#define ALL_TESTS_EMPTY_INIT_AS_CONT(suite_name) \
TEST(suite_name, uShortEmptyInitAsCont) { emptyInitAsContTest<unsigned short>(); } \
TEST(suite_name, intEmptyInitAsCont) { emptyInitAsContTest<int>(); } \
TEST(suite_name, doubleEmptyInitAsCont) { emptyInitAsContTest<double>(); } \
TEST(suite_name, MockClassEmptyInitAsCont) { emptyInitAsContTest<MockClass>(); } \

ALL_TESTS_EMPTY_INIT_AS_CONT(s21Vector)

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

#define ALL_TESTS_EMPTY_INIT(suite_name) \
TEST(suite_name, uShortEmptyInit) { emptyInitTest<unsigned short>(); } \
TEST(suite_name, intEmptyInit) { emptyInitTest<int>(); } \
TEST(suite_name, doubleEmptyInit) { emptyInitTest<double>(); } \
TEST(suite_name, MockClassEmptyInit) { emptyInitTest<MockClass>(); } \

ALL_TESTS_EMPTY_INIT(s21Vector)

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


#define ALL_TESTS_SIZE_INIT(suite_name) \
TEST(suite_name, uShortSizeInit) { sizeInitTest<unsigned short>(); } \
TEST(suite_name, intSizeInit) { sizeInitTest<int>(); } \
TEST(suite_name, doubleSizeInit) { sizeInitTest<double>(); } \
TEST(suite_name, MockClassSizeInit) { sizeInitTest<MockClass>(); } \

ALL_TESTS_SIZE_INIT(s21Vector)

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

#define ALL_TESTS_CLEAR(suite_name) \
TEST(suite_name, uShortClear) { clearTest<unsigned short>(); } \
TEST(suite_name, intClear) { clearTest<int>(); } \
TEST(suite_name, doubleClear) { clearTest<double>(); } \
TEST(suite_name, MockClassClear) { clearTest<MockClass>(); } \

ALL_TESTS_CLEAR(s21Vector)

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

#define ALL_TESTS_CLEAR_AS_CONT(suite_name) \
TEST(suite_name, uShortClearAsCont) { clearAsContTest<unsigned short>(); } \
TEST(suite_name, intCleaAsContr) { clearAsContTest<int>(); } \
TEST(suite_name, doubleClearAsCont) { clearAsContTest<double>(); } \
TEST(suite_name, MockClassClearAsCont) { clearAsContTest<MockClass>(); } \

ALL_TESTS_CLEAR_AS_CONT(s21Vector)

// -------------------
