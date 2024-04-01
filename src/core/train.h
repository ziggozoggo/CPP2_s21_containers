#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int _value): value(_value), left(nullptr), right(nullptr) {}

    void insert(Node& node, int _value) {
        if (_value < node.value) {
            if (node.left == nullptr) node.left = new Node(_value);
            else insert(*node.left, _value);
        } else if (_value > node.value) {
            if (node.right == nullptr) node.right = new Node(_value);
            else insert(*node.right, _value);
        } else return;
    }

    Node* search(Node* node, int _value) {
        if (node == nullptr) return nullptr;
        if (node->value == _value) return node;
        return (_value < node->value) ? search(node->left, _value) : search(node->right, _value);
    }

    Node* deleteNode(Node* node, int _value) {
        if (node == nullptr) return nullptr;

        if (_value < node->value) node->left = deleteNode(node->left, _value);
        else if (_value > node->value) node->right = deleteNode(node->right, _value);
        else {
            if (node->left == nullptr || node->right == nullptr) {
                node = (node->left == nullptr) ? node->right : node->left;
            }
        }
        return node;
    }

    void printTree(Node* node) {
        if (node == nullptr) return;
        printTree(node->left);
        std::cout << node->value << ' ';
        printTree(node->right);
    }

    
};

struct BST {
    Node* root;

    BST(): root(nullptr) {}

    bool isEmpty() { return root == nullptr; }
    
    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};