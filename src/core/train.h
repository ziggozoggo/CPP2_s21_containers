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
        Node* temp = this;
        if (temp == nullptr) return nullptr;

        if (value == _value) return this;
        return (_value < value) ? this->left->search(_value) : this->right->search(_value);
    }

    Node* deleteNode(int _value) {
        Node* temp = this;
        if (temp == nullptr) return nullptr;

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
        Node* temp = this;
        if (temp == nullptr) return;

        this->left->printTree();
        std::cout << value << ' ';
        this->right->printTree();
    }

    void deleteTree() {
        Node* temp = this;
        if (temp == nullptr) return;

        this->left->deleteTree();
        this->right->deleteTree();
        delete this;
    }
};

struct BST {
    Node* root;

    BST(): root(nullptr) {}

    bool isEmpty() { return root == nullptr; }
    
};

