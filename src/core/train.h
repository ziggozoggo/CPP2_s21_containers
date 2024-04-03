#include <iostream>
#include <algorithm>

namespace s21 {
  struct Node {
    int value;
    Node* left;
    Node* right;
    int height = 0;

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
      root = deleteNode(root, val);
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
      updateHeight(node);
      balance(node);
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
        } else {
          Node* maxInLeft = getMax(node->left);
          node->value = maxInLeft->value;
          node->left = deleteNode(node->left, node->value);
        }
      }
      if (!isEmpty(node)) {
        updateHeight(node);
        balance(node);
      }
      return node;
    }

    Node* getMin(Node* node) {
      if (isEmpty(node)) return nullptr;

      if (node->left == nullptr) return node;
      return getMin(node->left);
    }

    Node* getMax(Node* node) {
      if (isEmpty(node)) return nullptr;

      if (node->right == nullptr) return node;
      return getMax(node->right);
    }

    void deleteTree(Node* node) {
      if (isEmpty(node)) return;

      deleteTree(node->left);
      deleteTree(node->right);
      delete node;
    }

    int getHeight(Node* node) {
      return isEmpty(node) ? -1 : node->height;
    }

    void updateHeight(Node* node) {
      node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    int getBalance(Node* node) {
      return isEmpty(node) ? 0 : getHeight(node->right) - getHeight(node->left);
    }

    void swap(Node* a, Node* b) {
      int temp = a->value;
      a->value = b->value;
      b->value = temp;
    }

    void rightRotate(Node* node) {
      swap(node, node->left);
      Node* temp = node->right;
      node->right = node->left;
      node->left = node->right->left;
      node->right->left = node->right->right;
      node->right->right = temp;
      updateHeight(node->right);
      updateHeight(node);
    }

    void leftRotate(Node* node) {
      swap(node, node->right);
      Node* temp = node->left;
      node->left = node->right;
      node->right = node->left->right;
      node->left->right = node->left->left;
      node->left->left = temp;
      updateHeight(node->left);
      updateHeight(node);
    }

    void balance(Node* node) {
      int balance = getBalance(node);
      if (balance == -2) {
        if (getBalance(node->left) == 1) leftRotate(node->left);
        rightRotate(node);
      } else if (balance == 2) {
        if (getBalance(node->right) == -1) rightRotate(node->right);
        leftRotate(node);
      }
    }
  };
}

