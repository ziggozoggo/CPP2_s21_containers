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

  EXPECT_EQ(bst.search(5).value(), 5);
  EXPECT_EQ(bst.search(2).value(), 2);
  EXPECT_TRUE(!bst.search(10).has_value());

  // #NOTE: uncomment for debug or learn
  // std::cout << "BST INT insert(): ";
  // bst.printTree();
  // std::cout << std::endl;

  bst.remove(3);
  bst.remove(8);

  // std::cout << "BST INT remove(): ";
  // bst.printTree();
  // std::cout << std::endl;

  EXPECT_FALSE(bst.search(3).has_value());
  EXPECT_FALSE(bst.search(8).has_value());
}

TEST(BST, doubleIntegral) {
  s21::BST<double> bst;

  bst.insert(5.54);
  bst.insert(3.03);
  bst.insert(3.04);
  bst.insert(3424.423);
  bst.insert(4452.12);
  bst.insert(00000.12);
  bst.insert(455.45);
  bst.insert(6.34);

  // std::cout << "BST DOUBLE insert(): ";
  // bst.printTree();
  // std::cout << std::endl;

  EXPECT_EQ(bst.search(5.54).value(), 5.54);
  EXPECT_EQ(bst.search(3.04).value(), 3.04);
  EXPECT_TRUE(!bst.search(10).has_value());

  bst.remove(3.03);
  bst.remove(00000.12);

  // std::cout << "BST DOUBLE remove(): ";
  // bst.printTree();
  // std::cout << std::endl;

  EXPECT_FALSE(bst.search(3.03).has_value());
  EXPECT_FALSE(bst.search(00000.12).has_value());
}

/* EDGE */

// #TODO: edge cases

/* ANOMALY */

// #TODO: anomaly cases
