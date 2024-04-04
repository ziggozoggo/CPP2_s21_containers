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
    btree.insert(50);

    // s21::Node* temp = btree.search(10);

    // btree.printTree();
    // std::cout << std::endl;

    // btree.deleteNode(2);

    btree.printTree();
    std::cout << std::endl;

    



    


    return 0;
}