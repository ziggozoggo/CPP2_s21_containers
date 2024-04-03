#include <iostream>

namespace s21 {
  struct Node {
    int value;
    Node* left;
    Node* right;

    Node(): left(nullptr), right(nullptr) {}
    Node(int val): value(val), left(nullptr), right(nullptr) {}
  };

  class BST {
  private:
    Node* root;

  public:
    BST(): root(nullptr) {}
    BST(int val): root(new Node(val)) {}

    ~BST() {
      deleteTree(root);
    }

    bool isEmpty() { return root == nullptr; }

    void insert(int val) {
      root = insert(root, val);
    }

    Node* search(int val) {
      return search(root, val);
    }

    void printTree() {
      printTree(root);
    }

    void deleteNode(int val) {
      deleteNode(root, val);
    }

  private:
    bool isEmpty(Node* node) { return node == nullptr; }

    Node* insert(Node* node, int val) {
      if (isEmpty(node)) {
        return new Node(val);
      }
      if (val < node->value) {
        node->left = insert(node->left, val);
      } else if (val > node->value) {
        node->right = insert(node->right, val);
      }
      return node;
    }

    Node* search(Node* node, int val) {
      if (isEmpty(node)) return nullptr;

      if (node->value == val) return node;
      return (val < node->value) ? search(node->left, val) : search(node->right, val);
    }

    void printTree(Node* node) {
      if (isEmpty(node)) return;

      printTree(node->left);
      std::cout << node->value << ' ';
      printTree(node->right);
    }

    Node* deleteNode(Node* node, int val) {
      if (isEmpty(node)) return nullptr;

      if (val < node->value) node->left = deleteNode(node->left, val);
      else if (val > node->value) node->right = deleteNode(node->right, val);
      else {
        if (node->left == nullptr || node->right == nullptr) {
          Node* temp = (node->left == nullptr) ? node->right : node->left;
          delete node;
          return temp;
        }
      }
      return node;
    }

     void deleteTree(Node* node) {
      if (isEmpty(node)) return;

      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }

  };
}

