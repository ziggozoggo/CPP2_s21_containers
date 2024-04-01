#include "train.h"

int main() {
    Node bst(5);
    BST btree;

    bst.insert(bst, 10);
    bst.insert(bst, 15);
    bst.insert(bst, 3);
    bst.insert(bst, 8);

    // bst.deleteNode(&bst, 8);

    bst.printTree(&bst);
    std::cout << std::endl;

    btree.deleteTree(&bst);

    return 0;
}