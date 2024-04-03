#include "train.h"

int main() {
    s21::BST btree;

    // std::cout << btree.root->value;

    btree.insert(10);
    btree.insert(15);
    btree.insert(8);
    btree.insert(3);
    btree.insert(9);

    // s21::Node* temp = btree.search(10);

    btree.printTree();
    std::cout << std::endl;

    btree.deleteNode(9);
    btree.deleteNode(15);
    btree.deleteNode(8);

    btree.printTree();
    std::cout << std::endl;


    


    return 0;
}