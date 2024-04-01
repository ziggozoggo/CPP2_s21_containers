#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int _value): value(_value), left(nullptr), right(nullptr) {}

    void insert(int _value) {
        if (_value < value) {
            if (left == nullptr) left = new Node(_value);
            else this->left->insert(_value);
        } else if (_value > value) {
            if (right == nullptr) right = new Node(_value);
            else this->right->insert(_value);
        } else return;
    }

    Node* search(int _value) {
        //if (this == nullptr) return nullptr;
        
        if (value == _value) return this;
        return (_value < value) ? this->left->search(_value) : this->right->search(_value);
    }

    Node* deleteNode(int _value) {
        //if (this == nullptr) return;

        if (_value < value) this->left = this->left->deleteNode(_value);
        else if (_value > value) this->right = this->right->deleteNode(_value);
        else {
            if (this->left == nullptr || this->right == nullptr) {
                Node* temp = (this->left == nullptr) ? this->right : this->left;
                delete this;
                return temp;
            }
        }
        return this;
    }

    void printTree() {
        //if (this == nullptr) return;
        this->left->printTree();
        std::cout << value << ' ';
        this->right->printTree();
    }

    void deleteTree(Node* node) {
        if (node == nullptr) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
};

struct BST {
    Node* root;

    BST(): root(nullptr) {}

    bool isEmpty() { return root == nullptr; }
    
};

