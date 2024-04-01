#ifndef SRC_S21_BST_H_
#define SRC_S21_BST_H_

#include <iostream>
#include <optional>

namespace s21 {

template <typename T>
class BST {
public:
  BST() : root_(nullptr) {}
  ~BST() { deleteTree(root_); }

  bool isEmpty() { return root_ == nullptr; }

  void insert(const T& val) {
    root_ = insertRecursive(root_, val);
  }

  std::optional<T> search(const T& val) {
    return searchRecursive(root_, val);
  }

  void remove(const T& val) {
    root_ = removeRecursive(root_, val);
  }

  void printTree() {
    printInOrder(root_);
  }

private:
  struct Node {
    T val_;
    Node* left_;
    Node* right_;

    Node(T val) : val_(val), left_(nullptr), right_(nullptr) {}
  };

  Node* root_;

  Node* insertRecursive(Node* node, const T& val) {
    if (node == nullptr) return new Node(val);

    if (val < node->val_) {
      node->left_ = insertRecursive(node->left_, val);
    } else if (val > node->val_) {
      node->right_ = insertRecursive(node->right_, val);
    }

    return node;
  }

  std::optional<T> searchRecursive(Node* node, const T& val) {
    if (node == nullptr) return std::nullopt;

    if (node->val_ == val) return node->val_;
    else if (val < node->val_) return searchRecursive(node->left_, val);
    else return searchRecursive(node->right_, val);
  }

  Node* removeRecursive(Node* node, const T& val) {
    if (node == nullptr) return nullptr;

    if (val < node->val_) {
      node->left_ = removeRecursive(node->left_, val);
    } else if (val > node->val_) {
      node->right_ = removeRecursive(node->right_, val);
    } else {
      if (node->left_ == nullptr) {
        Node* temp = node->right_;
        delete node;
        return temp;
      } else if (node->right_ == nullptr) {
        Node* temp = node->left_;
        delete node;
        return temp;
      }

      Node* temp = minValueNode(node->right_);
      node->val_ = temp->val_;
      node->right_ = removeRecursive(node->right_, temp->val_);
    }

    return node;
  }

    Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left_ != nullptr) {
      current = current->left_;
    }
    return current;
  }

    void printInOrder(Node* node) {
    if (node == nullptr) return;

    printInOrder(node->left_);
    std::cout << node->val_ << " ";
    printInOrder(node->right_);
  }

  void deleteTree(Node* node) {
    if (node == nullptr) return;

    deleteTree(node->left_);
    deleteTree(node->right_);
    delete node;
  }
};

}

#endif  // SRC_S21_BST_H_