#include "train.h"

int main() {
    s21::BST btree;

    // std::cout << btree.root->value;

    btree.insert(1);
    btree.insert(2);
    btree.insert(3);
    btree.insert(4);
    btree.insert(5);
    btree.insert(6);

    // s21::Node* temp = btree.search(10);

    btree.printTree();
    std::cout << std::endl;

    btree.deleteNode(2);

    btree.printTree();
    std::cout << std::endl;



    


    return 0;
}