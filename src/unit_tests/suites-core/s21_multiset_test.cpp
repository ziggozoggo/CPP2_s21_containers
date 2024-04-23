#include "s21_core_tests.h"
#include "core/s21_multiset.h"

#include <set>

#define DEF_INT_KEYS {1, 2, 3, 4, 8, 3, 4, 4}
#define DEF_DBL_KEYS {4.35, 2.977, 873.23, 6.875, 9.6534, 6.875, 2.977, 2.977}
#define DEF_MOCK_KEYS {1, 4, 44, 45, 88, 44, 1, 1}
#define DEF_STR_KEYS {"hello", "world", "!", "mock", "multiset", "!", "!", "world"}

#define DEF_INT_KEYS_DUBLICATE {6, 2, 3, 8, 10}
#define DEF_DBL_KEYS_DUBLICATE {5.41, 2.977, 873.23, 6.875, 123.123}
#define DEF_MOCK_KEYS_DUBLICATE {1, 9, 10, 45, 10}
#define DEF_STR_KEYS_DUBLICATE {"hello", "test", "!!!", "this", "mock"}

#define DEF_INT_KEYS_NO_DUBLICATE {6, 5, 10, 9, 11}
#define DEF_DBL_KEYS_NO_DUBLICATE {7.523, 234.4, 1.001, 1.002, 124.124}
#define DEF_MOCK_KEYS_NO_DUBLICATE {98, 9, 10, 11, 90}
#define DEF_STR_KEYS_NO_DUBLICATE {"this", "is", "test", "or", "not"}

#define INT_KEY 69
#define DBL_KEY 69.69
#define MOCK_KEY 69
#define STR_KEY "69"

#define INT_KEY_DUPLICATE 4
#define DBL_KEY_DUPLICATE 2.977
#define MOCK_KEY_DUPLICATE 1
#define STR_KEY_DUPLICATE "!"

template<typename key_type>
void checkFields(const s21::multiset<key_type>& s21_multiset
    , const std::multiset<key_type>& std_multiset) {
  auto std_it = std_multiset.begin();
  for (auto s21_it : s21_multiset) {
    EXPECT_EQ(s21_it, *std_it);

    ++std_it;
  }
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
}

template<typename key_type>
void checkFieldsEmpty(const s21::multiset<key_type>& s21_multiset
    , const std::multiset<key_type>& std_multiset) {
  auto std_it = std_multiset.begin();
  for (auto s21_it : s21_multiset) {
    EXPECT_EQ(s21_it, *std_it);

    ++std_it;
  }
  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
}

// -------------------------------------------------
// -------------------------------------------------
// -------------------------------------------------

template<typename key_type>
void constructorDefaultAsCont() {
  s21::IContainer* ct = new s21::multiset<key_type>();

  EXPECT_EQ(ct->size(), 0);
  EXPECT_TRUE(ct->empty());

  delete ct;
}

#define TESTS_CONSTRUCTOR_INIT_AS_CONT(suiteName) \
TEST(suiteName, intInitAsCont) { constructorDefaultAsCont<int>(); } \
TEST(suiteName, doubleInitAsCont) { constructorDefaultAsCont<double>(); } \
TEST(suiteName, mockClassInitAsCont) { constructorDefaultAsCont<MockClass>(); } \
TEST(suiteName, stringInitAsCont) { constructorDefaultAsCont<std::string>(); } \

TESTS_CONSTRUCTOR_INIT_AS_CONT(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void constructorDefault() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  checkFieldsEmpty(s21_multiset, std_multiset);
}

#define TESTS_DEFAULT_CONSTRUCTOR_INIT(suiteName) \
TEST(suiteName, intDefInit) { constructorDefault<int>(); } \
TEST(suiteName, doubleDefInit) { constructorDefault<double>(); } \
TEST(suiteName, mockClassDefInit) { constructorDefault<MockClass>(); } \
TEST(suiteName, stringDefInit) { constructorDefault<std::string>(); } \

TESTS_DEFAULT_CONSTRUCTOR_INIT(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void constructorInitList(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  checkFields(s21_multiset, std_multiset);
}

#define TESTS_CONSTRUCTOR_INIT_LIST(suiteName) \
TEST(suiteName, intInitList) { constructorInitList<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleInitList) { constructorInitList<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassInitList) { constructorInitList<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringInitList) { constructorInitList<std::string>(DEF_STR_KEYS); } \

TESTS_CONSTRUCTOR_INIT_LIST(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void constructorCopyEmpty() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  s21::multiset<key_type> s21_map_copy(s21_multiset);
  std::multiset<key_type> std_map_copy(std_multiset);

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_CONSTRUCTOR_COPY_EMPTY(suiteName) \
TEST(suiteName, intCopyEmpty) { constructorCopyEmpty<int>(); } \
TEST(suiteName, doubleCopyEmpty) { constructorCopyEmpty<double>(); } \
TEST(suiteName, mockClassCopyEmpty) { constructorCopyEmpty<MockClass>(); } \
TEST(suiteName, stringCopyEmpty) { constructorCopyEmpty<std::string>(); } \

TESTS_CONSTRUCTOR_COPY_EMPTY(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void constructorCopy(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_copy(s21_multiset);
  std::multiset<key_type> std_map_copy(std_multiset);

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_CONSTRUCTOR_COPY(suiteName) \
TEST(suiteName, intCopy) { constructorCopy<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleCopy) { constructorCopy<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassCopy) { constructorCopy<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringCopy) { constructorCopy<std::string>(DEF_STR_KEYS); } \

TESTS_CONSTRUCTOR_COPY(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void constructorMoveEmpty() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  s21::multiset<key_type> s21_map_move(std::move(s21_multiset));
  std::multiset<key_type> std_map_move(std::move(std_multiset));

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_CONSTRUCTOR_MOVE_EMPTY(suiteName) \
TEST(suiteName, intMoveEmpty) { constructorMoveEmpty<int>(); } \
TEST(suiteName, doubleMoveEmpty) { constructorMoveEmpty<double>(); } \
TEST(suiteName, mockClassMoveEmpty) { constructorMoveEmpty<MockClass>(); } \
TEST(suiteName, stringMoveEmpty) { constructorMoveEmpty<std::string>(); } \

TESTS_CONSTRUCTOR_MOVE_EMPTY(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void constructorMove(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_move(std::move(s21_multiset));
  std::multiset<key_type> std_map_move(std::move(std_multiset));

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_CONSTRUCTOR_MOVE(suiteName) \
TEST(suiteName, intMove) { constructorMove<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleMove) { constructorMove<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassMove) { constructorMove<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringMove) { constructorMove<std::string>(DEF_STR_KEYS); } \

TESTS_CONSTRUCTOR_MOVE(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void operatorCopyEmpty() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  s21::multiset<key_type> s21_map_copy = s21_multiset;
  std::multiset<key_type> std_map_copy = std_multiset;

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_OPERATOR_COPY_EMPTY(suiteName) \
TEST(suiteName, intOperatorCopyEmpty) { operatorCopyEmpty<int>(); } \
TEST(suiteName, doubleOperatorCopyEmpty) { operatorCopyEmpty<double>(); } \
TEST(suiteName, mockClassOperatorCopyEmpty) { operatorCopyEmpty<MockClass>(); } \
TEST(suiteName, stringOperatorCopyEmpty) { operatorCopyEmpty<std::string>(); } \

TESTS_OPERATOR_COPY_EMPTY(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void operatorCopy(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_copy = s21_multiset;
  std::multiset<key_type> std_map_copy = std_multiset;

  checkFields(s21_map_copy, std_map_copy);
}

#define TESTS_OPERATOR_COPY(suiteName) \
TEST(suiteName, intOperatorCopy) { operatorCopy<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleOperatorCopy) { operatorCopy<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassOperatorCopy) { operatorCopy<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringOperatorCopy) { operatorCopy<std::string>(DEF_STR_KEYS); } \

TESTS_OPERATOR_COPY(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void operatorMoveEmpty() {
  s21::multiset<key_type> s21_multiset;
  std::multiset<key_type> std_multiset;

  s21::multiset<key_type> s21_map_move = std::move(s21_multiset);
  std::multiset<key_type> std_map_move = std::move(std_multiset);

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_OPERATOR_MOVE_EMPTY(suiteName) \
TEST(suiteName, intOperatorMoveEmpty) { operatorMoveEmpty<int>(); } \
TEST(suiteName, doubleOperatorMoveEmpty) { operatorMoveEmpty<double>(); } \
TEST(suiteName, mockClassOperatorMoveEmpty) { operatorMoveEmpty<MockClass>(); } \
TEST(suiteName, stringOperatorMoveEmptye) { operatorMoveEmpty<std::string>(); } \

TESTS_OPERATOR_MOVE_EMPTY(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void operatorMove(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_move = std::move(s21_multiset);
  std::multiset<key_type> std_map_move = std::move(std_multiset);

  checkFields(s21_map_move, std_map_move);
}

#define TESTS_OPERATOR_MOVE(suiteName) \
TEST(suiteName, intOperatorMove) { operatorMove<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleOperatorMove) { operatorMove<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassOperatorMove) { operatorMove<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringOperatorMove) { operatorMove<std::string>(DEF_STR_KEYS); } \

TESTS_OPERATOR_MOVE(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodEmpty(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  EXPECT_EQ(s21_multiset.empty(), std_multiset.empty());
  EXPECT_EQ(s21_map_empty.empty(), std_map_empty.empty());
}

#define TESTS_EMPTY(suiteName) \
TEST(suiteName, intEmpty) { methodEmpty<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleEmpty) { methodEmpty<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassEmpty) { methodEmpty<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringEmpty) { methodEmpty<std::string>(DEF_STR_KEYS); } \

TESTS_EMPTY(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodSize(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  EXPECT_EQ(s21_multiset.size(), std_multiset.size());
  EXPECT_EQ(s21_map_empty.size(), std_map_empty.size());
}

#define TESTS_SIZE(suiteName) \
TEST(suiteName, intSize) { methodEmpty<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleSize) { methodEmpty<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassSize) { methodEmpty<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringSize) { methodEmpty<std::string>(DEF_STR_KEYS); } \

TESTS_SIZE(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodSwap(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  s21::multiset<key_type> s21_map_empty;

  std::multiset<key_type> std_multiset(items);

  checkFields(s21_multiset, std_multiset);
  s21_map_empty.swap(s21_multiset);
  checkFields(s21_map_empty, std_multiset);
}

#define TESTS_SWAP(suiteName) \
TEST(suiteName, intSwap) { methodSwap<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleSwap) { methodSwap<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassSwap) { methodSwap<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringSwap) { methodSwap<std::string>(DEF_STR_KEYS); } \

TESTS_SWAP(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodMergeWithDublicates(const std::initializer_list<key_type>& items
    , const std::initializer_list<key_type>& itemsDublicates) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_dublicate(itemsDublicates);
  std::multiset<key_type> std_map_dublicate(itemsDublicates);

  checkFields(s21_multiset, std_multiset);
  checkFields(s21_map_dublicate, std_map_dublicate);

  s21_multiset.merge(s21_map_dublicate);
  std_multiset.merge(std_map_dublicate);

  checkFields(s21_multiset, std_multiset);
}

#define TESTS_MERGE_WITH_DUBLICATES(suiteName) \
TEST(suiteName, intMergeWithDublicates) { methodMergeWithDublicates<int>(DEF_INT_KEYS, DEF_INT_KEYS_DUBLICATE); } \
TEST(suiteName, doubleMergeWithDublicates) { methodMergeWithDublicates<double>(DEF_DBL_KEYS, DEF_DBL_KEYS_DUBLICATE); } \
TEST(suiteName, mockClassMergeWithDublicates) { methodMergeWithDublicates<MockClass>(DEF_MOCK_KEYS, DEF_MOCK_KEYS_DUBLICATE); } \
TEST(suiteName, stringMergeWithDublicates) { methodMergeWithDublicates<std::string>(DEF_STR_KEYS, DEF_STR_KEYS_DUBLICATE); } \

TESTS_MERGE_WITH_DUBLICATES(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodMergeWithNoDublicates(const std::initializer_list<key_type>& items
    , const std::initializer_list<key_type>& itemsNoDublicates) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_no_dublicate(itemsNoDublicates);
  std::multiset<key_type> std_map_no_dublicate(itemsNoDublicates);

  checkFields(s21_multiset, std_multiset);
  checkFields(s21_map_no_dublicate, std_map_no_dublicate);

  s21_multiset.merge(s21_map_no_dublicate);
  std_multiset.merge(std_map_no_dublicate);

  checkFields(s21_multiset, std_multiset);
}

#define TESTS_MERGE_WITH_NO_DUBLICATES(suiteName) \
TEST(suiteName, intMergeWithNoDublicates) { methodMergeWithNoDublicates<int>(DEF_INT_KEYS, DEF_INT_KEYS_NO_DUBLICATE); } \
TEST(suiteName, doubleMergeWithNoDublicates) { methodMergeWithNoDublicates<double>(DEF_DBL_KEYS, DEF_DBL_KEYS_NO_DUBLICATE); } \
TEST(suiteName, mockClassMergeWithNoDublicates) { methodMergeWithNoDublicates<MockClass>(DEF_MOCK_KEYS, DEF_MOCK_KEYS_NO_DUBLICATE); } \
TEST(suiteName, stringMergeWithNoDublicates) { methodMergeWithNoDublicates<std::string>(DEF_STR_KEYS, DEF_STR_KEYS_NO_DUBLICATE); } \

TESTS_MERGE_WITH_NO_DUBLICATES(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodClear(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  s21_multiset.clear();
  std_multiset.clear();

  s21_map_empty.clear();
  std_map_empty.clear();

  checkFields(s21_multiset, std_multiset);
  checkFields(s21_map_empty, std_map_empty);
}

#define TESTS_CLEAR(suiteName) \
TEST(suiteName, intClear) { methodClear<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleClear) { methodClear<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassClear) { methodClear<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringClear) { methodClear<std::string>(DEF_STR_KEYS); } \

TESTS_CLEAR(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodBegin(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  typename s21::multiset<key_type>::iterator it1 = s21_map_empty.begin();
  typename std::multiset<key_type>::iterator it2 = std_map_empty.begin();

  EXPECT_EQ(it1 == s21_map_empty.end()
      , it2 == std_map_empty.end());

  typename s21::multiset<key_type>::iterator it3 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it4 = std_multiset.begin();

  EXPECT_EQ(it3 != s21_multiset.end()
      , it4 != std_multiset.end());
  EXPECT_EQ(*it3, *it4);
}

#define TESTS_BEGIN(suiteName) \
TEST(suiteName, intBegin) { methodBegin<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleBegin) { methodBegin<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassBegin) { methodBegin<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringBegin) { methodBegin<std::string>(DEF_STR_KEYS); } \

TESTS_BEGIN(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodBeginConst(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21::multiset<key_type> s21_map_empty;
  std::multiset<key_type> std_map_empty;

  typename s21::multiset<key_type>::const_iterator it1 = s21_map_empty.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_map_empty.begin();

  EXPECT_EQ(it1 == s21_map_empty.end()
      , it2 == std_map_empty.end());

  typename s21::multiset<key_type>::const_iterator it3 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it4 = std_multiset.begin();

  EXPECT_EQ(it3 != s21_multiset.end()
      , it4 != std_multiset.end());
  EXPECT_EQ(*it3, *it4);
}

#define TESTS_BEGIN_CONST(suiteName) \
TEST(suiteName, intBeginConst) { methodBeginConst<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleBeginConst) { methodBeginConst<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassBeginConst) { methodBeginConst<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringBeginConst) { methodBeginConst<std::string>(DEF_STR_KEYS); } \

TESTS_BEGIN_CONST(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorPlus(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_PLUS(suiteName) \
TEST(suiteName, intIteratorPlus) { methodIteratorPlus<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorPlus) { methodIteratorPlus<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorPlus) { methodIteratorPlus<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorPlus) { methodIteratorPlus<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_PLUS(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorMinus(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  --it1;
  --it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_MINUS(suiteName) \
TEST(suiteName, intIteratorMinus) { methodIteratorMinus<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorMinus) { methodIteratorMinus<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorMinus) { methodIteratorMinus<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorMinus) { methodIteratorMinus<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_MINUS(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorAssignment(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  typename s21::multiset<key_type>::iterator it3 = it1;
  typename std::multiset<key_type>::iterator it4 = it2;

  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*it2, *it4);
}

#define TESTS_ITERATOR_ASSIGNMENT(suiteName) \
TEST(suiteName, intIteratorAssignment) { methodIteratorAssignment<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorAssignment) { methodIteratorAssignment<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorAssignment) { methodIteratorAssignment<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorAssignment) { methodIteratorAssignment<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_ASSIGNMENT(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorEqual(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  typename s21::multiset<key_type>::iterator it3 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it4 = std_multiset.begin();

  EXPECT_EQ(it1 == it3, it2 == it4);
}

#define TESTS_ITERATOR_EQUAL(suiteName) \
TEST(suiteName, intIteratorEqual) { methodIteratorEqual<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorEqual) { methodIteratorEqual<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorEqual) { methodIteratorEqual<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorEqual) { methodIteratorEqual<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_EQUAL(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorNotEqual(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::iterator it2 = std_multiset.begin();

  EXPECT_EQ(it1 != s21_multiset.end(), it2 != std_multiset.end());
}

#define TESTS_ITERATOR_NOT_EQUAL(suiteName) \
TEST(suiteName, intIteratorNotEqual) { methodIteratorNotEqual<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorNotEqual) { methodIteratorNotEqual<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorNotEqual) { methodIteratorNotEqual<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorNotEqual) { methodIteratorNotEqual<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_NOT_EQUAL(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorPlusConst(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_PLUS_CONST(suiteName) \
TEST(suiteName, intIteratorPlusConst) { methodIteratorPlusConst<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorPlusConst) { methodIteratorPlusConst<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorPlusConst) { methodIteratorPlusConst<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorPlusConst) { methodIteratorPlusConst<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_PLUS_CONST(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorMinusConst(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  ++it1;
  ++it2;

  EXPECT_EQ(*it1, *it2);

  --it1;
  --it2;

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_ITERATOR_MINUS_CONST(suiteName) \
TEST(suiteName, intIteratorMinusConst) { methodIteratorMinusConst<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorMinusConst) { methodIteratorMinusConst<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorMinusConst) { methodIteratorMinusConst<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorMinusConst) { methodIteratorMinusConst<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_MINUS_CONST(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorAssignmentConst(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  typename s21::multiset<key_type>::const_iterator it3 = it1;
  typename std::multiset<key_type>::const_iterator it4 = it2;

  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*it2, *it4);
}

#define TESTS_ITERATOR_ASSIGNMENT_CONST(suiteName) \
TEST(suiteName, intIteratorAssignmentConst) { methodIteratorAssignmentConst<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorAssignmentConst) { methodIteratorAssignmentConst<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorAssignmentConst) { methodIteratorAssignmentConst<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorAssignmentConst) { methodIteratorAssignmentConst<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_ASSIGNMENT_CONST(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorEqualConst(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  typename s21::multiset<key_type>::const_iterator it3 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it4 = std_multiset.begin();

  EXPECT_EQ(it1 == it3, it2 == it4);
}

#define TESTS_ITERATOR_EQUAL_CONST(suiteName) \
TEST(suiteName, intIteratorEqualConst) { methodIteratorEqualConst<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorEqualConst) { methodIteratorEqualConst<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorEqualConst) { methodIteratorEqualConst<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorEqualConst) { methodIteratorEqualConst<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_EQUAL_CONST(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodIteratorNotEqualConst(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::const_iterator it1 = s21_multiset.begin();
  typename std::multiset<key_type>::const_iterator it2 = std_multiset.begin();

  EXPECT_EQ(it1 != s21_multiset.end(), it2 != std_multiset.end());
}

#define TESTS_ITERATOR_NOT_EQUAL_CONST(suiteName) \
TEST(suiteName, intIteratorNotEqualConst) { methodIteratorNotEqualConst<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleIteratorNotEqualConst) { methodIteratorNotEqualConst<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassIteratorNotEqualConst) { methodIteratorNotEqualConst<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringIteratorNotEqualConst) { methodIteratorNotEqualConst<std::string>(DEF_STR_KEYS); } \

TESTS_ITERATOR_NOT_EQUAL_CONST(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodInsertNoDuplicate(const std::initializer_list<key_type>& items
    , const key_type& key) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.insert(key);
  typename std::multiset<key_type>::iterator it2 = std_multiset.insert(key);

  checkFields(s21_multiset, std_multiset);

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_INSERT_NO_DUPLICATE(suiteName) \
TEST(suiteName, intInsertNoDuplicate) { methodInsertNoDuplicate<int>(DEF_INT_KEYS, INT_KEY); } \
TEST(suiteName, doubleInsertNoDuplicate) { methodInsertNoDuplicate<double>(DEF_DBL_KEYS, DBL_KEY); } \
TEST(suiteName, mockClassInsertNoDuplicate) { methodInsertNoDuplicate<MockClass>(DEF_MOCK_KEYS, MOCK_KEY); } \
TEST(suiteName, stringInsertNoDuplicate) { methodInsertNoDuplicate<std::string>(DEF_STR_KEYS, STR_KEY); } \

TESTS_INSERT_NO_DUPLICATE(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodInsertDuplicate(const std::initializer_list<key_type>& items
    , const key_type& key) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  typename s21::multiset<key_type>::iterator it1 = s21_multiset.insert(key);
  typename std::multiset<key_type>::iterator it2 = std_multiset.insert(key);

  checkFields(s21_multiset, std_multiset);

  EXPECT_EQ(*it1, *it2);
}

#define TESTS_INSERT_DUPLICATE(suiteName) \
TEST(suiteName, intInsertDuplicate) { methodInsertDuplicate<int>(DEF_INT_KEYS, INT_KEY_DUPLICATE); } \
TEST(suiteName, doubleInsertDuplicate) { methodInsertDuplicate<double>(DEF_DBL_KEYS, DBL_KEY_DUPLICATE); } \
TEST(suiteName, mockClassInsertDuplicate) { methodInsertDuplicate<MockClass>(DEF_MOCK_KEYS, MOCK_KEY_DUPLICATE); } \
TEST(suiteName, stringInsertDuplicate) { methodInsertDuplicate<std::string>(DEF_STR_KEYS, STR_KEY_DUPLICATE); } \

TESTS_INSERT_DUPLICATE(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodErase(const std::initializer_list<key_type>& items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21_multiset.erase(s21_multiset.begin());
  std_multiset.erase(std_multiset.begin());

  checkFields(s21_multiset, std_multiset);

  s21_multiset.erase(s21_multiset.begin());
  std_multiset.erase(std_multiset.begin());

  checkFields(s21_multiset, std_multiset);
}

#define TESTS_ERASE(suiteName) \
TEST(suiteName, intMethodErase) { methodErase<int>(DEF_INT_KEYS); } \
TEST(suiteName, doubleMethodErase) { methodErase<double>(DEF_DBL_KEYS); } \
TEST(suiteName, mockClassMethodErase) { methodErase<MockClass>(DEF_MOCK_KEYS); } \
TEST(suiteName, stringMethodErase) { methodErase<std::string>(DEF_STR_KEYS); } \

TESTS_ERASE(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodContains(const std::initializer_list<key_type>& items
    , const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);

  ASSERT_FALSE(s21_multiset.contains(key));
  ASSERT_TRUE(s21_multiset.contains(key_duplicate));
}

#define TESTS_CONTAINS(suiteName) \
TEST(suiteName, intMethodContains) { methodContains<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE); } \
TEST(suiteName, doubleMethodContains) { methodContains<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); } \
TEST(suiteName, mockClassMethodContains) { methodContains<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); } \
TEST(suiteName, stringMethodContains) { methodContains<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE); } \

TESTS_CONTAINS(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodInsertMany(const std::initializer_list<key_type>& items
    , const std::initializer_list<key_type>& insert_items) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  s21_multiset.insert_many(*insert_items.begin(), *(insert_items.begin() + 1), *(insert_items.begin() + 2));
  std_multiset.insert(*insert_items.begin());
  std_multiset.insert(*(insert_items.begin() + 1));
  std_multiset.insert(*(insert_items.begin() + 2));

  checkFields(s21_multiset, std_multiset);
}

#define TESTS_INSERT_MANY(suiteName) \
TEST(suiteName, intMethodInsertMany) { methodInsertMany<int>(DEF_INT_KEYS, DEF_INT_KEYS_NO_DUBLICATE); } \
TEST(suiteName, doubleMethodInsertMany) { methodInsertMany<double>(DEF_DBL_KEYS, DEF_DBL_KEYS_NO_DUBLICATE); } \
TEST(suiteName, mockClassMethodInsertMany) { methodInsertMany<MockClass>(DEF_MOCK_KEYS, DEF_MOCK_KEYS_NO_DUBLICATE); } \
TEST(suiteName, stringMethodInsertMany) { methodInsertMany<std::string>(DEF_STR_KEYS, DEF_STR_KEYS_NO_DUBLICATE); } \

TESTS_INSERT_MANY(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodFind(const std::initializer_list<key_type>& items
    , const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  EXPECT_EQ(s21_multiset.find(key) == s21_multiset.end(), std_multiset.find(key) == std_multiset.end());

  EXPECT_EQ(*(s21_multiset.find(key_duplicate)), *(std_multiset.find(key_duplicate)));
}

#define TESTS_FIND(suiteName) \
TEST(suiteName, intMethodFind) { methodFind<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE); } \
TEST(suiteName, doubleMethodFind) { methodFind<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); } \
TEST(suiteName, mockClassMethodFind) { methodFind<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); } \
TEST(suiteName, stringMethodFind) { methodFind<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE); } \

TESTS_FIND(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodCount(const std::initializer_list<key_type>& items
    , const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  EXPECT_EQ(s21_multiset.count(key) == 0, std_multiset.count(key) == 0);

  EXPECT_EQ(s21_multiset.count(key_duplicate), std_multiset.count(key_duplicate));
}

#define TESTS_COUNT(suiteName) \
TEST(suiteName, intMethodCount) { methodCount<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE); } \
TEST(suiteName, doubleMethodCount) { methodCount<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); } \
TEST(suiteName, mockClassMethodCount) { methodCount<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); } \
TEST(suiteName, stringMethodCount) { methodCount<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE); } \

TESTS_COUNT(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodLowerBound(const std::initializer_list<key_type>& items
    , const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  EXPECT_EQ(s21_multiset.lower_bound(key) == s21_multiset.end(), std_multiset.lower_bound(key) == std_multiset.end());

  EXPECT_EQ(*(s21_multiset.lower_bound(key_duplicate)--), *(std_multiset.lower_bound(key_duplicate)--));
}

#define TESTS_LOWER_BOUND(suiteName) \
TEST(suiteName, intMethodLowerBound) { methodLowerBound<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE); } \
TEST(suiteName, doubleMethodLowerBound) { methodLowerBound<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); } \
TEST(suiteName, mockClassMethodLowerBound) { methodLowerBound<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); } \
TEST(suiteName, stringMethodLowerBound) { methodLowerBound<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE); } \

TESTS_LOWER_BOUND(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodUpperBound(const std::initializer_list<key_type>& items
    , const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);
  std::multiset<key_type> std_multiset(items);

  EXPECT_EQ(s21_multiset.upper_bound(key) == s21_multiset.end(), std_multiset.upper_bound(key) == std_multiset.end());

  EXPECT_EQ(*(s21_multiset.upper_bound(key_duplicate)++), *(std_multiset.upper_bound(key_duplicate)++));
}

#define TESTS_UPPER_BOUND(suiteName) \
TEST(suiteName, intMethodUpperBound) { methodUpperBound<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE); } \
TEST(suiteName, doubleMethodUpperBound) { methodUpperBound<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); } \
TEST(suiteName, mockClassMethodUpperBound) { methodUpperBound<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); } \
TEST(suiteName, stringMethodUpperBound) { methodUpperBound<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE); } \

TESTS_UPPER_BOUND(s21Multiset)

// -------------------------------------------------

template<typename key_type>
void methodEqualRange(const std::initializer_list<key_type>& items
    , const key_type& key, const key_type& key_duplicate) {
  s21::multiset<key_type> s21_multiset(items);

  EXPECT_TRUE(s21_multiset.equal_range(key).first == s21_multiset.lower_bound(key));
  EXPECT_TRUE(s21_multiset.equal_range(key).second == s21_multiset.upper_bound(key));

  EXPECT_TRUE(s21_multiset.equal_range(key_duplicate).first == s21_multiset.lower_bound(key_duplicate));
  EXPECT_TRUE(s21_multiset.equal_range(key_duplicate).second == s21_multiset.upper_bound(key_duplicate));
}

#define TESTS_EQUAL_RANGE(suiteName) \
TEST(suiteName, intMethodEqualRange) { methodEqualRange<int>(DEF_INT_KEYS, INT_KEY, INT_KEY_DUPLICATE); } \
TEST(suiteName, doubleMethodEqualRange) { methodEqualRange<double>(DEF_DBL_KEYS, DBL_KEY, DBL_KEY_DUPLICATE); } \
TEST(suiteName, mockClassMethodEqualRange) { methodEqualRange<MockClass>(DEF_MOCK_KEYS, MOCK_KEY, MOCK_KEY_DUPLICATE); } \
TEST(suiteName, stringMethodEqualRange) { methodEqualRange<std::string>(DEF_STR_KEYS, STR_KEY, STR_KEY_DUPLICATE); } \

TESTS_EQUAL_RANGE(s21Multiset)

// -------------------------------------------------

#define TEST_ROUNDS 3000

template<typename key_type>
void bigLineTree(int rounds) {
  s21::multiset<key_type> actual;
  std::multiset<key_type> expected;

  srand(static_cast<int>((std::size_t)&actual));

  for (int i = 0; i < rounds; i++) {
    actual.insert(i);
    expected.insert(i);
  }

  checkFields(actual, expected);
}

#define TESTS_BIG_LINE_TREE(suiteName) \
TEST(suiteName, intBigLineTree) { bigLineTree<int>(TEST_ROUNDS); } \

TESTS_BIG_LINE_TREE(s21Multiset)

// -------------------------------------------------

double GetRandMultiset(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

template<typename key_type>
void bigRandomTree(int rMin, int rMax, int rounds) {
  s21::multiset<key_type> actual;
  std::multiset<key_type> expected;

  srand(static_cast<int>((std::size_t)&actual));

  for (int i = 0; i < rounds; i++) {
    auto val = GetRandMultiset(rMin, rMax);
    actual.insert(val);
    expected.insert(val);
  }

  checkFields(actual, expected);
}

#define TEST_RAND_MIN -10000
#define TEST_RAND_MAX 10000
#define TEST_RAND_ROUNDS 1000

#define TESTS_BIG_RANDOM_TREE(suiteName) \
TEST(suiteName, intBigRandomTree) { bigRandomTree<int>(TEST_RAND_MIN, TEST_RAND_MAX, TEST_RAND_ROUNDS); } \
TEST(suiteName, doubleBigRandomTree) { bigRandomTree<double>(TEST_RAND_MIN, TEST_RAND_MAX, TEST_RAND_ROUNDS); } \

TESTS_BIG_RANDOM_TREE(s21Multiset)