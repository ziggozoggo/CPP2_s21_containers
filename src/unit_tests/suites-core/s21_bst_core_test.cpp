#include "s21_containers_core_test.h"

#include "core/s21_bst.h"

/* NORMAL */

// #TODO: random generation values

TEST(BST, intIntegral) {
  s21::BST<int> bst;

  bst.insert(5);
  bst.insert(3);
  bst.insert(7);
  bst.insert(2);
  bst.insert(4);
  bst.insert(6);
  bst.insert(8);

  EXPECT_EQ(bst.search(5).value()->value, 5);
  EXPECT_EQ(bst.search(2).value()->value, 2);
  EXPECT_TRUE(!bst.search(10).has_value());

  bst.remove(3);
  bst.remove(8);

  EXPECT_FALSE(bst.search(3).has_value());
  EXPECT_FALSE(bst.search(8).has_value());
}

TEST(BST, doubleIntegral) {
  s21::BST<double> bst;

  bst.insert(5.54);
  bst.insert(5.54);
  bst.insert(3.03);
  bst.insert(3.04);
  bst.insert(3424.423);
  bst.insert(4452.12);
  bst.insert(00000.12);
  bst.insert(455.45);
  bst.insert(6.34);

  EXPECT_EQ(bst.search(5.54).value()->value, 5.54);
  EXPECT_EQ(bst.search(3.04).value()->value, 3.04);
  EXPECT_TRUE(!bst.search(10).has_value());

  bst.remove(3.03);
  bst.remove(00000.12);

  EXPECT_FALSE(bst.search(3.03).has_value());
  EXPECT_FALSE(bst.search(00000.12).has_value());
}

TEST(BST, charIntegral) {
  s21::BST<char> bst;

  bst.insert('a');
  bst.insert('c');
  bst.insert('z');
  bst.insert('y');
  bst.insert('n');
  bst.insert('f');
  bst.insert('b');
  bst.insert('q');
  bst.insert('x');
  bst.insert('x');

  EXPECT_EQ(bst.search('z').value()->value, 'z');
  EXPECT_EQ(bst.search('n').value()->value, 'n');
  EXPECT_TRUE(!bst.search('o').has_value());

  bst.remove('b');
  bst.remove('n');
  bst.remove('u');

  EXPECT_FALSE(bst.search('b').has_value());
  EXPECT_FALSE(bst.search('n').has_value());
  EXPECT_FALSE(bst.search('u').has_value());
}

TEST(BST, stringIntegral) {
  s21::BST<std::string> bst;

  bst.insert("abc");
  bst.insert("cba");
  bst.insert("asdgaer");
  bst.insert("gafergf");
  bst.insert("grtsgfsdgvbaerg");
  bst.insert("temp");
  bst.insert("temp2");
  bst.insert("temporary");
  bst.insert("abccca");
  bst.insert("dfed");

  EXPECT_EQ(bst.search("abc").value()->value, "abc");
  EXPECT_EQ(bst.search("temp2").value()->value, "temp2");
  EXPECT_TRUE(!bst.search("temp3").has_value());

  bst.remove("temp2");
  bst.remove("temporary");
  bst.remove("dfed");
  bst.remove("temp3");

  EXPECT_FALSE(bst.search("temp2").has_value());
  EXPECT_FALSE(bst.search("temporary").has_value());
  EXPECT_FALSE(bst.search("dfed").has_value());
  EXPECT_FALSE(bst.search("temp3").has_value());
}

/* EDGE */

// #TODO: edge cases

/* ANOMALY */

// #TODO: anomaly cases
