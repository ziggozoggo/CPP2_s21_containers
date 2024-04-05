#include "train.h"

int main() {
    s21::BST btree;

    // std::cout << btree.root->value;

    // btree.insert(15);
    // btree.insert(8);
    // btree.insert(18);
    // btree.insert(4);
    // btree.insert(9);
    // btree.insert(11);
    // btree.insert(12);

    btree.insert(10);
    btree.insert(20);
    btree.insert(30);
    btree.insert(40);
    btree.insert(25);
    btree.insert(35);
    btree.insert(45);
    btree.insert(5);
    btree.insert(50);
    btree.insert(42);
    btree.insert(48);

    btree.printTree();
    std::cout << std::endl;

    btree.remove(25);
    btree.remove(45);
    btree.remove(40);
    btree.remove(35);
    btree.remove(10);
    btree.remove(30);
    btree.remove(5);
    btree.remove(48);
    btree.remove(42);
    btree.remove(50);
    btree.remove(20);

    btree.printTree();
    std::cout << std::endl;
    


    


    return 0;
}