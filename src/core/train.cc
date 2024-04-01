#include "train.h"

int main() {
    Node* bst = new Node(5);
    BST btree;

    bst->insert(10);
    bst->insert(15);
    bst->insert(3);
    bst->insert(8);

    bst->deleteNode(8);

    bst->printTree();
    std::cout << std::endl;

    bst->deleteTree(bst);

    return 0;
}