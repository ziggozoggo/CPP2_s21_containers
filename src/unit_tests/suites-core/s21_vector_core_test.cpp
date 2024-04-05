#include "s21_containers_core_test.h"

#include <algorithm>
#include <vector>
#include <type_traits>
#include <string>

#include "core/s21_vector.h"

template <typename T>
void checkBasicField(const s21::vector<T>& actual, const std::vector<T>& expected) {
  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_NE(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());
}

/* NORMAL */

#define DEF_INT_VALS {1, 2, 3, 4, 5}
#define DEF_DBL_VALS {1.42, 2.5, 0.003, 664.452, 1.0035}
#define DEF_MOCK_VALS {1, 2, 44, 45}
#define DEF_STR_VALS {"hello", "world", "!"}

template<typename T>
void defaultInitAsContTest() {
  s21::IContainer* ct = new s21::vector<T>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_EMPTY_INIT_AS_CONT(suiteName) \
TEST(suiteName, uShortEmptyInitAsCont) { defaultInitAsContTest<unsigned short>(); } \
TEST(suiteName, intEmptyInitAsCont) { defaultInitAsContTest<int>(); } \
TEST(suiteName, doubleEmptyInitAsCont) { defaultInitAsContTest<double>(); } \
TEST(suiteName, MockClassEmptyInitAsCont) { defaultInitAsContTest<MockClass>(); } \
TEST(suiteName, stringEmptyInitAsCont) { defaultInitAsContTest<std::string>(); } \

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

#define TESTS_EMPTY_INIT(suiteName) \
TEST(suiteName, uShortEmptyInit) { defaultInitTest<unsigned short>(); } \
TEST(suiteName, intEmptyInit) { defaultInitTest<int>(); } \
TEST(suiteName, doubleEmptyInit) { defaultInitTest<double>(); } \
TEST(suiteName, MockClassEmptyInit) { defaultInitTest<MockClass>(); } \
TEST(suiteName, stringEmptyInit) { defaultInitTest<std::string>(); } \

TESTS_EMPTY_INIT(s21Vector)

// --------------------------------------

template<typename T>
void sizeInitTest() {
  const std::size_t size = 100;

  s21::vector<T> actual(size);
  std::vector<T> expected(size);

  checkBasicField(actual, expected);
}


#define TESTS_SIZE_INIT(suiteName) \
TEST(suiteName, uShortSizeInit) { sizeInitTest<unsigned short>(); } \
TEST(suiteName, intSizeInit) { sizeInitTest<int>(); } \
TEST(suiteName, doubleSizeInit) { sizeInitTest<double>(); } \
TEST(suiteName, MockClassSizeInit) { sizeInitTest<MockClass>(); } \
TEST(suiteName, stringSizeInit) { sizeInitTest<std::string>(); } \

TESTS_SIZE_INIT(s21Vector)

// --------------------------------------

template<typename T>
void listInitTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);
}

#define TESTS_LIST_INIT(suiteName) \
TEST(suiteName, uShortListInit) { listInitTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intListInit) { listInitTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleListInit) { listInitTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassListInit) { listInitTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringListInit) { listInitTest<std::string>(DEF_STR_VALS); } \

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

#define TESTS_COPY_INIT(suiteName) \
TEST(suiteName, uShortCopyInit) { copyInitTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intCopyInit) { copyInitTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleCopyInit) { copyInitTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassCopyInit) { copyInitTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringCopyInit) { copyInitTest<std::string>(DEF_STR_VALS); } \

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

#define TESTS_MOVE_INIT(suiteName) \
TEST(suiteName, uShortMoveInit) { moveInitTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intMoveInit) { moveInitTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleMoveInit) { moveInitTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassMoveInit) { moveInitTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringMoveInit) { moveInitTest<std::string>(DEF_STR_VALS); } \

TESTS_MOVE_INIT(s21Vector)

// --------------------------------------

template<typename T>
void operatorInitCopyTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  s21::vector<T> actualCopy = actual;

  std::vector<T> expected(items);
  std::vector<T> expectedCopy = items;

  EXPECT_EQ(actualCopy.size(), expectedCopy.size());
  EXPECT_EQ(actualCopy.capacity(), expectedCopy.capacity());
  EXPECT_NE(actualCopy.data(), expectedCopy.data());

  EXPECT_EQ(actualCopy.empty(), expectedCopy.empty());

  EXPECT_TRUE(actual == actualCopy);
}

#define TESTS_OPERATOR_COPY_INIT(suiteName) \
TEST(suiteName, uShortOperatorCopyInit) { operatorInitCopyTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intOperatorCopyInit) { operatorInitCopyTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleOperatorCopyInit) { operatorInitCopyTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassOperatorCopyInit) { operatorInitCopyTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringOperatorCopyInit) { operatorInitCopyTest<std::string>(DEF_STR_VALS); } \

TESTS_OPERATOR_COPY_INIT(s21Vector)

// --------------------------------------

template<typename T>
void operatorInitMoveTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  s21::vector<T> actualMove = std::move(actual);

  std::vector<T> expected(items);
  std::vector<T> expectedMove = std::move(expected);

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

#define TESTS_OPERATOR_MOVE_INIT(suiteName) \
TEST(suiteName, uShortOperatorMoveInit) { operatorInitMoveTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intOperatorMoveInit) { operatorInitMoveTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleOperatorMoveInit) { operatorInitMoveTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassOperatorMoveInit) { operatorInitMoveTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringOperatorMoveInit) { operatorInitMoveTest<std::string>(DEF_STR_VALS); } \

TESTS_OPERATOR_MOVE_INIT(s21Vector)

// --------------------------------------

template<typename T>
void clearTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  actual.clear();
  expected.clear();

  checkBasicField(actual, expected);
}

#define TESTS_CLEAR(suiteName) \
TEST(suiteName, uShortClear) { clearTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intClear) { clearTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleClear) { clearTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassClear) { clearTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringClear) { clearTest<std::string>(DEF_STR_VALS); } \

TESTS_CLEAR(s21Vector)

// --------------------------------------

template<typename T>
void clearAsContTest() {
  const std::size_t size = 100;

  s21::IContainer* ct = new s21::vector<T>(size);

  EXPECT_EQ(ct->size(), size);
  EXPECT_FALSE(ct->empty());

  ct->clear();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_CLEAR_AS_CONT(suiteName) \
TEST(suiteName, uShortClearAsCont) { clearAsContTest<unsigned short>(); } \
TEST(suiteName, intClearAsContr) { clearAsContTest<int>(); } \
TEST(suiteName, doubleClearAsCont) { clearAsContTest<double>(); } \
TEST(suiteName, MockClassClearAsCont) { clearAsContTest<MockClass>(); } \
TEST(suiteName, stringClearAsCont) { clearAsContTest<std::string>(); } \

TESTS_CLEAR_AS_CONT(s21Vector)

// --------------------------------------

template<typename T>
void beginTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_EQ(*actual.begin(), *expected.begin());
}

#define TESTS_BEGIN(suiteName) \
TEST(suiteName, uShortBegin) { beginTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intBegin) { beginTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleBegin) { beginTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassBegin) { beginTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringBegin) { beginTest<std::string>(DEF_STR_VALS); } \

TESTS_BEGIN(s21Vector)

// --------------------------------------

template<typename T>
void endTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  EXPECT_EQ(&(*actual.end()), actual.data() + actual.size());
  EXPECT_EQ(&(*expected.end()), expected.data() + expected.size());
}

#define TESTS_END(suiteName) \
TEST(suiteName, uShortEnd) { endTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intEnd) { endTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleEnd) { endTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassEnd) { endTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringEnd) { endTest<std::string>(DEF_STR_VALS); } \

TESTS_END(s21Vector)

// --------------------------------------

template<typename T>
void iteratorManualTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  auto itActual = actual.begin();
  auto itExpected = expected.begin();

  EXPECT_EQ(*itActual, *itExpected);

  for (std::size_t i = 0; i < actual.size() - 1; i++) {
    EXPECT_TRUE(itActual == itActual);
    EXPECT_FALSE(itActual != itActual);

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

#define TESTS_ITERATOR_MANUAL(suiteName) \
TEST(suiteName, uShortIteratorManual) { iteratorManualTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intIteratorManual) { iteratorManualTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleIteratorManual) { iteratorManualTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassIteratorManual) { iteratorManualTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringIteratorManual) { iteratorManualTest<std::string>(DEF_STR_VALS); } \

TESTS_ITERATOR_MANUAL(s21Vector)

// --------------------------------------

template<typename T>
void iteratorForeachTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (auto i : actual) {
    // #DEFECT - std::is_same() not work
    // if (std::is_same<T, std::string>::value) {
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

#define TESTS_ITERATOR_FOREACH(suiteName) \
TEST(suiteName, uShortIteratorForeach) { iteratorForeachTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intIteratorForeach) { iteratorForeachTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleIteratorForeach) { iteratorForeachTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassIteratorForeach) { iteratorForeachTest<MockClass>(DEF_MOCK_VALS); } \

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

#define TESTS_ITERATOR_EQUAL(suiteName) \
TEST(suiteName, uShortIteratorEqual) { iteratorEqualTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intIteratorEqual) { iteratorEqualTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleIteratorEqual) { iteratorEqualTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassIteratorEqual) { iteratorEqualTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringIteratorEqual) { iteratorEqualTest<std::string>(DEF_STR_VALS); } \

TESTS_ITERATOR_EQUAL(s21Vector)

// --------------------------------------

template<typename T>
void swapTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  s21::vector<T> actualSwap;
  actualSwap.swap(actual);

  EXPECT_EQ(actual.size(), 0);
  EXPECT_EQ(actual.capacity(), 0);
  EXPECT_EQ(actual.data(), nullptr);

  EXPECT_NE(actual.size(), actualSwap.size());
  EXPECT_NE(actual.capacity(), actualSwap.capacity());
  EXPECT_NE(actual.data(), actualSwap.data());

  EXPECT_NE(actual.empty(), actualSwap.empty());

  std::vector<T> expectedSwap;
  expectedSwap.swap(expected);

  EXPECT_EQ(expected.size(), 0);
  EXPECT_EQ(expected.capacity(), 0);
  EXPECT_EQ(expected.data(), nullptr);

  EXPECT_NE(expected.size(), expectedSwap.size());
  EXPECT_NE(expected.capacity(), expectedSwap.capacity());
  EXPECT_NE(expected.data(), expectedSwap.data());

  EXPECT_NE(expected.empty(), expectedSwap.empty());

  EXPECT_EQ(actual.size(), expected.size());
  EXPECT_EQ(actual.capacity(), expected.capacity());
  EXPECT_EQ(actual.data(), expected.data());

  EXPECT_EQ(actual.empty(), expected.empty());

  EXPECT_EQ(actualSwap.size(), expectedSwap.size());
  EXPECT_EQ(actualSwap.capacity(), expectedSwap.capacity());
  EXPECT_NE(actualSwap.data(), expectedSwap.data());

  EXPECT_EQ(actualSwap.empty(), expectedSwap.empty());
}

#define TESTS_SWAP(suiteName) \
TEST(suiteName, uShortSwap) { swapTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intSwap) { swapTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleSwap) { swapTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassSwap) { swapTest<MockClass>(DEF_MOCK_VALS); } \

TESTS_SWAP(s21Vector)

// --------------------------------------

template<typename T>
void atTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    EXPECT_EQ(actual.at(i), expected.at(i));
  }
}

#define TESTS_AT(suiteName) \
TEST(suiteName, uShortAt) { atTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intAt) { atTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleAt) { atTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassAt) { atTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringAt) { atTest<std::string>(DEF_STR_VALS); } \

TESTS_AT(s21Vector)

// --------------------------------------

template<typename T>
void atChangeTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    actual.at(i) = actual.at(i) * 2;
    expected.at(i) = expected.at(i) * 2;
    EXPECT_EQ(actual.at(i), expected.at(i));
  }
}

#define TESTS_AT_CHANGE(suiteName) \
TEST(suiteName, uShortAtChange) { atChangeTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intAtChange) { atChangeTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleAtChange) { atChangeTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassAtChange) { atChangeTest<MockClass>(DEF_MOCK_VALS); } \

TESTS_AT_CHANGE(s21Vector)

// --------------------------------------

template<typename T>
void constAtTest(const std::initializer_list<T>& items) {
  const s21::vector<T> actual(items);
  const std::vector<T> expected(items);

  checkBasicField(actual, expected);

  for (std::size_t i = 0; i < actual.size(); i++) {
    EXPECT_EQ(actual.at(i), expected.at(i));
  }
}

#define TESTS_CONST_AT(suiteName) \
TEST(suiteName, uShortConstAt) { constAtTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intConstAt) { constAtTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleConstAt) { constAtTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassConstAt) { constAtTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringConstAt) { constAtTest<std::string>(DEF_STR_VALS); } \

TESTS_CONST_AT(s21Vector)

// --------------------------------------

/* ANOMALY */

template<typename T>
void atOutOfRangeTest(const std::initializer_list<T>& items) {
  s21::vector<T> actual(items);
  std::vector<T> expected(items);

  checkBasicField(actual, expected);

  std::size_t pos = actual.size();

  EXPECT_THROW({
    actual.at(pos);
  }, std::out_of_range);

  EXPECT_THROW({
    expected.at(pos);
  }, std::out_of_range);

  pos = actual.size() + 2;

  EXPECT_THROW({
    actual.at(pos);
  }, std::out_of_range);

  EXPECT_THROW({
    expected.at(pos);
  }, std::out_of_range);
}

#define TESTS_ANOMALY_AT_OUT_RANGE(suiteName) \
TEST(suiteName, uShortAnomalyAtOutRange) { atOutOfRangeTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intAnomalyAtOutRange) { atOutOfRangeTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleAnomalyAtOutRange) { atOutOfRangeTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassAnomalyAtOutRange) { atOutOfRangeTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringAnomalyAtOutRange) { atOutOfRangeTest<std::string>(DEF_STR_VALS); } \

TESTS_ANOMALY_AT_OUT_RANGE(s21Vector)

// --------------------------------------

template<typename T>
void constAtOutOfRangeTest(const std::initializer_list<T>& items) {
  const s21::vector<T> actual(items);
  const std::vector<T> expected(items);

  checkBasicField(actual, expected);

  std::size_t pos = actual.size();

  EXPECT_THROW({
    actual.at(pos);
  }, std::out_of_range);

  EXPECT_THROW({
    expected.at(pos);
  }, std::out_of_range);

  pos = actual.size() + 2;

  EXPECT_THROW({
    actual.at(pos);
  }, std::out_of_range);

  EXPECT_THROW({
    expected.at(pos);
  }, std::out_of_range);
}

#define TESTS_ANOMALY_CONST_AT_OUT_RANGE(suiteName) \
TEST(suiteName, uShortAnomalyConstAtOutRange) { constAtOutOfRangeTest<unsigned short>(DEF_INT_VALS); } \
TEST(suiteName, intAnomalyConstAtOutRange) { constAtOutOfRangeTest<int>(DEF_INT_VALS); } \
TEST(suiteName, doubleAnomalyConstAtOutRange) { constAtOutOfRangeTest<double>(DEF_DBL_VALS); } \
TEST(suiteName, MockClassAnomalyConstAtOutRange) { constAtOutOfRangeTest<MockClass>(DEF_MOCK_VALS); } \
TEST(suiteName, stringAnomalyConstAtOutRange) { constAtOutOfRangeTest<std::string>(DEF_STR_VALS); } \

TESTS_ANOMALY_CONST_AT_OUT_RANGE(s21Vector)

// --------------------------------------