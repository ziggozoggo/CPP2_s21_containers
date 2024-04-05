#include "s21_containers_core_test.h"

#include <algorithm>
#include <vector>
#include <type_traits>

#include "core/s21_vector.h"

template<typename T>
void defaultInitAsContTest() {
  s21::IContainer<T>* ct = new s21::vector<T>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_EMPTY_INIT_AS_CONT(suite_name) \
TEST(suite_name, uShortEmptyInitAsCont) { defaultInitAsContTest<unsigned short>(); } \
TEST(suite_name, intEmptyInitAsCont) { defaultInitAsContTest<int>(); } \
TEST(suite_name, doubleEmptyInitAsCont) { defaultInitAsContTest<double>(); } \
TEST(suite_name, MockClassEmptyInitAsCont) { defaultInitAsContTest<MockClass>(); } \

TESTS_EMPTY_INIT_AS_CONT(s21Vector)

// --------------------------------------

template<typename T>
void defaultInitTest() {
  s21::vector<T> actual;
  std::vector<T> expected;

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_EQ(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

#define TESTS_EMPTY_INIT(suite_name) \
TEST(suite_name, uShortEmptyInit) { defaultInitTest<unsigned short>(); } \
TEST(suite_name, intEmptyInit) { defaultInitTest<int>(); } \
TEST(suite_name, doubleEmptyInit) { defaultInitTest<double>(); } \
TEST(suite_name, MockClassEmptyInit) { defaultInitTest<MockClass>(); } \

TESTS_EMPTY_INIT(s21Vector)

// --------------------------------------

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

// --------------------------------------

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

// --------------------------------------

template<typename T>
void copyInitTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  s21::vector<T> actualCopy(actual);

  std::vector<T> expected(items);
  std::vector<T> expectedCopy(items);

  EXPECT_EQ(actualCopy.size(), expectedCopy.size());
  EXPECT_EQ(actualCopy.capacity(), expectedCopy.capacity());
  EXPECT_NE(actualCopy.data(), expectedCopy.data());

  EXPECT_EQ(actualCopy.empty(), expectedCopy.empty());

  EXPECT_TRUE(actual == actualCopy);
}

#define TESTS_COPY_INIT(suite_name) \
TEST(suite_name, uShortCopyInit) { copyInitTest<unsigned short>({1, 2, 3, 4, 5}); } \
TEST(suite_name, intCopyInit) { copyInitTest<int>({1, 2, 3, 4, 5}); } \
TEST(suite_name, doubleCopyInit) { copyInitTest<double>({1.42, 2.5, 0.003, 664.452, 1.0035}); } \
TEST(suite_name, MockClassCopyInit) { copyInitTest<MockClass>({1, 2, 44, 45}); } \

TESTS_COPY_INIT(s21Vector)

// --------------------------------------

template<typename T>
void moveInitTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  s21::vector<T> actualMove(std::move(actual));

  std::vector<T> expected(items);
  std::vector<T> expectedMove(std::move(expected));

  EXPECT_EQ(actualMove.size(), expectedMove.size());
  EXPECT_EQ(actualMove.capacity(), expectedMove.capacity());
  EXPECT_NE(actualMove.data(), expectedMove.data());

  EXPECT_EQ(actualMove.empty(), expectedMove.empty());

  EXPECT_TRUE(actual != actualMove);

  EXPECT_EQ(actual.size(), 0);
  EXPECT_EQ(actual.capacity(), 0);
  EXPECT_EQ(actual.data(), nullptr);

  EXPECT_EQ(expected.size(), 0);
  EXPECT_EQ(expected.capacity(), 0);
  EXPECT_EQ(expected.data(), nullptr);
}

#define TESTS_MOVE_INIT(suite_name) \
TEST(suite_name, uShortMoveInit) { moveInitTest<unsigned short>({1, 2, 3, 4, 5}); } \
TEST(suite_name, intMoveInit) { moveInitTest<int>({1, 2, 3, 4, 5}); } \
TEST(suite_name, doubleMoveInit) { moveInitTest<double>({1.42, 2.5, 0.003, 664.452, 1.0035}); } \
TEST(suite_name, MockClassMoveInit) { moveInitTest<MockClass>({1, 2, 44, 45}); } \

TESTS_MOVE_INIT(s21Vector)

// --------------------------------------

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

// --------------------------------------

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

// --------------------------------------

template<typename T>
void beginTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());

  EXPECT_EQ(*actual.begin(), *expected.begin());
}

#define TESTS_BEGIN(suite_name) \
TEST(suite_name, uShortBegin) { beginTest<unsigned short>({1, 2, 3, 4, 5}); } \
TEST(suite_name, intBegin) { beginTest<int>({1, 2, 3, 4, 5}); } \
TEST(suite_name, doubleBegin) { beginTest<double>({1.42, 2.5, 0.003, 664.452, 1.0035}); } \
TEST(suite_name, MockClassBegin) { beginTest<MockClass>({1, 2, 44, 45}); } \

TESTS_BEGIN(s21Vector)

// --------------------------------------

template<typename T>
void endTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());

  EXPECT_EQ(&(*actual.end()), actual.data() + actual.size());
  EXPECT_EQ(&(*expected.end()), expected.data() + expected.size());
}

#define TESTS_END(suite_name) \
TEST(suite_name, uShortEnd) { endTest<unsigned short>({1, 2, 3, 4, 5}); } \
TEST(suite_name, intEnd) { endTest<int>({1, 2, 3, 4, 5}); } \
TEST(suite_name, doubleEnd) { endTest<double>({1.42, 2.5, 0.003, 664.452, 1.0035}); } \
TEST(suite_name, MockClassEnd) { endTest<MockClass>({1, 2, 44, 45}); } \

TESTS_END(s21Vector)

// --------------------------------------

template<typename T>
void iteratorManualTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());

  auto itActual = actual.begin();
  auto itExpected = expected.begin();

  EXPECT_EQ(*itActual, *itExpected);

  for (std::size_t i = 0; i < actual.size() - 1; i++) {
    itActual++;
    itExpected++;

    EXPECT_EQ(*itActual, *itExpected);
  }

  for (std::size_t i = 0; i < actual.size() - 1; i++) {
    itActual--;
    itExpected--;

    EXPECT_EQ(*itActual, *itExpected);
  }
}

#define TESTS_ITERATOR_MANUAL(suite_name) \
TEST(suite_name, uShortIteratorManual) { iteratorManualTest<unsigned short>({1, 2, 3, 4, 5}); } \
TEST(suite_name, intIteratorManual) { iteratorManualTest<int>({1, 2, 3, 4, 5}); } \
TEST(suite_name, doubleIteratorManual) { iteratorManualTest<double>({1.42, 2.5, 0.003, 664.452, 1.0035}); } \
TEST(suite_name, MockClassIteratorManual) { iteratorManualTest<MockClass>({1, 2, 44, 45}); } \

TESTS_ITERATOR_MANUAL(s21Vector)

// --------------------------------------

template<typename T>
void iteratorForeachTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());

  for (auto i : actual) {
    i = i * 2;
  }

  for (auto i : expected) {
    i = i * 2;
  }

  auto itActual = actual.begin();
  auto itExpected = expected.begin();

  EXPECT_EQ(*itActual, *itExpected);

  for (std::size_t i = 0; i < actual.size() - 1; i++) {
    itActual++;
    itExpected++;

    EXPECT_EQ(*itActual, *itExpected);
  }
}

#define TESTS_ITERATOR_FOREACH(suite_name) \
TEST(suite_name, uShortIteratorForeach) { iteratorForeachTest<unsigned short>({1, 2, 3, 4, 5}); } \
TEST(suite_name, intIteratorForeach) { iteratorForeachTest<int>({1, 2, 3, 4, 5}); } \
TEST(suite_name, doubleIteratorForeach) { iteratorForeachTest<double>({1.42, 2.5, 0.003, 664.452, 1.0035}); } \
TEST(suite_name, MockClassIteratorForeach) { iteratorForeachTest<MockClass>({1, 2, 44, 45}); } \

TESTS_ITERATOR_FOREACH(s21Vector)

// --------------------------------------

template<typename T>
void iteratorEqualTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  s21::vector<T> actualCopy(actual);

  EXPECT_EQ(actual.size(), actualCopy.size());
  EXPECT_EQ(actual.capacity(), actualCopy.capacity());
  EXPECT_NE(actual.data(), actualCopy.data());

  EXPECT_EQ(actual.empty(), actualCopy.empty());

  std::equal(actual.begin(), actual.end(), actualCopy.begin());
}

#define TESTS_ITERATOR_EQUAL(suite_name) \
TEST(suite_name, uShortIteratorEqual) { iteratorEqualTest<unsigned short>({1, 2, 3, 4, 5}); } \
TEST(suite_name, intIteratorEqual) { iteratorEqualTest<int>({1, 2, 3, 4, 5}); } \
TEST(suite_name, doubleIteratorEqual) { iteratorEqualTest<double>({1.42, 2.5, 0.003, 664.452, 1.0035}); } \
TEST(suite_name, MockClassIteratorEqual) { iteratorEqualTest<MockClass>({1, 2, 44, 45}); } \

TESTS_ITERATOR_EQUAL(s21Vector)

// --------------------------------------