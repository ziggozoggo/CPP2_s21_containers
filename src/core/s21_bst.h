#ifndef S21_BST_H_
#define S21_BST_H_

#include <iostream>
#include <algorithm>
#include <optional>

namespace s21 {
template <typename T, typename U>
class BST {
private:
  enum class NodeColor {
    BLACK,
    RED
  };

public:
  struct Node {
    Node* left_;
    Node* right_;
    Node* parent_;
    NodeColor color_ = NodeColor::BLACK;
    std::pair<const T, U> pair_;

    Node() : left_(nil_), right_(nil_), parent_(nil_) {}
    Node(std::pair<const T, U> pair, Node* nil) : left_(nil), right_(nil), parent_(nil), color_(NodeColor::RED), pair_(pair) {}

    bool isNil() { return this == nil_; }
  };

private:
  static Node* nil_;
  Node* root_;
  
public:
  BST() : root_(nil_) {}
  BST(std::pair<const T, U> pair) : root_(new Node(pair, nil_)) {}

  ~BST() { deleteTree(root_); }

  bool isEmpty() { return root_ == nil_; }

  std::pair<Node*, bool> insert(const std::pair<const T, U>& pair) {
    return insertNode(pair.first, pair.second);
  }

  std::pair<Node*, bool> insert(const T& key) {
    U defaultValue;
    return insertNode(key, defaultValue);
  }

  std::pair<Node*, bool> insert(const T& key, const U& obj) {
    return insertNode(key, obj);
  }

  void remove(const T& key) { removeNode(key); }

  Node* search(const T& key) { return search(root_, key); }
  Node* getMin() const;
  Node* getMax() const;

  Node* getMin(Node* node) const;
  Node* getMax(Node* node) const;

  void moveClear() { root_ = nil_; }
  void clear();
  void printTree() { printTree(root_); }
  void swapTree(BST& other) { std::swap(root_, other.root_); }

private:
  std::pair<Node*, bool> insertNode(const T& key, const U& obj);
  void balanceInsert(Node* newNode);
  void removeNode(const T& key);
  void balanceRemove(Node* node);
  void rightRotate(Node* node);
  void leftRotate(Node* node);

  Node* search(Node* node, const T& key);
  Node* getChildOrMock(Node* node) { return node->left_->isNil() ? node->right_ : node->left_; }
  int getChildrenCount(Node* node);
  void transplateNode(Node* dest, Node* src);

  void swap(Node* a, Node* b);
  void swapValue(Node* dest, Node* src);

  void printTree(Node* node);
  void deleteTree(Node* node);
};

template<typename T, typename U>
typename BST<T, U>::Node* BST<T, U>::nil_ = new Node();

template<typename T, typename U>
std::pair<typename BST<T, U>::Node*, bool> BST<T, U>::insertNode(const T& key, const U& value) {
  Node* checkNode = search(key);
  if (checkNode != nullptr)
    return std::make_pair(checkNode, false);

  Node* currentNode = root_;
  Node* parent_ = nil_;
  while (!currentNode->isNil()) {
    parent_ = currentNode;
    (key < currentNode->pair_.first) ? currentNode = currentNode->left_
    : currentNode = currentNode->right_;
  }
  Node* newNode = new Node(std::make_pair(key, value), nil_);
  newNode->parent_ = parent_;
  if (parent_ == nil_) root_ = newNode;
  else if (key < parent_->pair_.first) parent_->left_ = newNode;
  else parent_->right_ = newNode;
  balanceInsert(newNode);
  return std::make_pair(newNode, true);
}

template<typename T, typename U>
void BST<T, U>::balanceInsert(Node* newNode) {
  Node* uncle;
  while (newNode->parent_->color_ == NodeColor::RED) {
    if (newNode->parent_ == newNode->parent_->parent_->left_) {
      uncle = newNode->parent_->parent_->right_;
      if (uncle->color_ == NodeColor::RED) {
        newNode->parent_->color_ = NodeColor::BLACK;
        uncle->color_ = NodeColor::BLACK;
        newNode->parent_->parent_->color_ = NodeColor::RED;
        newNode = newNode->parent_->parent_;
      } else {
        if (newNode == newNode->parent_->right_) {
          leftRotate(newNode->parent_);

          newNode->color_ = NodeColor::BLACK;
          newNode->parent_->color_ = NodeColor::RED;
          rightRotate(newNode->parent_);
          newNode = newNode->parent_;
        } else {
          newNode->parent_->color_ = NodeColor::BLACK;
          newNode->parent_->parent_->color_ = NodeColor::RED;
          rightRotate(newNode->parent_->parent_);
        }
      }
    } else {
      uncle = newNode->parent_->parent_->left_;
      if (uncle->color_ == NodeColor::RED) {
        newNode->parent_->color_ = NodeColor::BLACK;
        uncle->color_ = NodeColor::BLACK;
        newNode->parent_->parent_->color_ = NodeColor::RED;
        newNode = newNode->parent_->parent_;
      } else {
        if (newNode == newNode->parent_->left_) {
          rightRotate(newNode->parent_);

          newNode->color_ = NodeColor::BLACK;
          newNode->parent_->color_ = NodeColor::RED;
          leftRotate(newNode->parent_);
          newNode = newNode->parent_;
        } else {
          newNode->parent_->color_ = NodeColor::BLACK;
          newNode->parent_->parent_->color_ = NodeColor::RED;
          leftRotate(newNode->parent_->parent_);
        }
      }
    }
  }
  root_->color_ = NodeColor::BLACK;
}

template<typename T, typename U>
typename BST<T, U>::Node* BST<T, U>::search(Node* node, const T& key) {
  if (node->isNil()) return nullptr;

  if (node->pair_.first == key) return node;
  return (key < node->pair_.first) ? search(node->left_, key) : search(node->right_, key);
}

template<typename T, typename U>
void BST<T, U>::printTree(Node* node) {
  if (node->isNil()) return;

  printTree(node->left_);
  std::cout << node->pair_.first << ' ';
  printTree(node->right_);
}

template<typename T, typename U>
int BST<T, U>::getChildrenCount(Node* node) {
  int count = 0;
  if (!node->left_->isNil()) count++;
  if (!node->right_->isNil()) count++;
  return count;
}

template<typename T, typename U>
void BST<T, U>::transplateNode(Node* dest, Node* src) {
  if (dest == root_) root_ = src;
  else if (dest == dest->parent_->left_) dest->parent_->left_ = src;
  else dest->parent_->right_ = src;
  src->parent_ = dest->parent_;
  delete dest;
}

template<typename T, typename U>
void BST<T, U>::swapValue(Node* dest, Node* src) {
  Node* temp = new Node(src->pair_, nil_);
  temp->color_ = dest->color_;
  
  temp->left_ = dest->left_;
  temp->right_ = dest->right_;
  temp->parent_ = dest->parent_;

  dest->left_->parent_ = temp;
  dest->right_->parent_ = temp;
  if (dest != root_) {
    if (dest == dest->parent_->left_)
      dest->parent_->left_ = temp;
    else
      dest->parent_->right_ = temp;
  } else
    root_ = temp;

  delete dest;
}

template<typename T, typename U>
void BST<T, U>::removeNode(const T& key) {
  Node* nodeToDelete = search(key);
  if (nodeToDelete == nullptr) return;

  NodeColor removedNodeColor = nodeToDelete->color_;
  Node* child;

  if (getChildrenCount(nodeToDelete) < 2) {
    child = getChildOrMock(nodeToDelete);
    transplateNode(nodeToDelete, child);
  } else {
    Node* minNode = getMin(nodeToDelete->right_);
    swapValue(nodeToDelete, minNode);
    removedNodeColor = minNode->color_;
    child = getChildOrMock(minNode);
    transplateNode(minNode, child);
  }
  if (removedNodeColor == NodeColor::BLACK) balanceRemove(child);
}

template<typename T, typename U>
void BST<T, U>::balanceRemove(Node* node) {
  while (node != root_ && node->color_ == NodeColor::BLACK) {
    Node* brother;
    if (node == node->parent_->left_) {
      brother = node->parent_->right_;
      if (brother->color_ == NodeColor::RED) {
        brother->color_ = NodeColor::BLACK;
        node->parent_->color_ = NodeColor::RED;
        leftRotate(node->parent_);
        brother = node->parent_->right_;
      }
      if (brother->left_->color_ == NodeColor::BLACK && brother->right_->color_ == NodeColor::BLACK) {
        brother->color_ = NodeColor::RED;
        node = node->parent_;
      } else {
        if (brother->right_->color_ == NodeColor::BLACK) {
          brother->left_->color_ = NodeColor::BLACK;
          brother->color_ = NodeColor::RED;
          rightRotate(brother);
          brother = node->parent_->right_;
        }
        brother->color_ = node->parent_->color_;
        node->parent_->color_ = NodeColor::BLACK;
        brother->right_->color_ = NodeColor::BLACK;
        leftRotate(node->parent_);
        node = root_;
      }
    } else {
      brother = node->parent_->left_;
      if (brother->color_ == NodeColor::RED) {
        brother->color_ = NodeColor::BLACK;
        node->parent_->color_ = NodeColor::RED;
        rightRotate(node->parent_);
        brother = node->parent_->left_;
      }
      if (brother->left_->color_ == NodeColor::BLACK && brother->right_->color_ == NodeColor::BLACK) {
        brother->color_ = NodeColor::RED;
        node = node->parent_;
      } else {
        if (brother->left_->color_ == NodeColor::BLACK) {
          brother->right_->color_ = NodeColor::BLACK;
          brother->color_ = NodeColor::RED;
          leftRotate(brother);
          brother = node->parent_->left_;
        }
        brother->color_ = node->parent_->color_;
        node->parent_->color_ = NodeColor::BLACK;
        brother->left_->color_ = NodeColor::BLACK;
        rightRotate(node->parent_);
        node = root_;
      }
    }
  }
  node->color_ = NodeColor::BLACK;
}

template<typename T, typename U>
typename BST<T, U>::Node* BST<T, U>::getMin(Node* node) const {
  if (node->isNil()) return nullptr;

  if (node->left_->isNil()) return node;
  return getMin(node->left_);
}

template<typename T, typename U>
typename BST<T, U>::Node* BST<T, U>::getMin() const {
  if (root_->isNil() || root_->left_->isNil()) return root_;

  Node* temp = root_->left_;
  while (!temp->left_->isNil())
    temp = temp->left_;

  return temp;
}

template<typename T, typename U>
typename BST<T, U>::Node* BST<T, U>::getMax(Node* node) const {
  if (node->isNil()) return nullptr;

  if (node->right_->isNil()) return node;
  return getMax(node->right_);
}

template<typename T, typename U>
typename BST<T, U>::Node* BST<T, U>::getMax() const {
  if (root_->isNil() || root_->right_->isNil()) return root_;

  Node* temp = root_->right_;
  while (!temp->right_->isNil())
    temp = temp->right_;

  return temp->right_;
}

template<typename T, typename U>
void BST<T, U>::deleteTree(Node* node) {
  if (node->isNil()) return;

  deleteTree(node->left_);
  deleteTree(node->right_);
  delete node;
}

template<typename T, typename U>
void BST<T, U>::swap(Node* a, Node* b) {
  if (b == a->left_) {
    Node* aRight = a->right_;
    Node* bLeft = b->left_;
    a->right_ = b->right_;
    b->right_ = aRight;

    b->left_ = a;
    a->left_ = bLeft;

    if (!a->parent_->isNil()){
      if (a == a->parent_->left_)
        a->parent_->left_ = b;
      else
        a->parent_->right_ = b;
      b->parent_ = a->parent_;
    } else
      b->parent_ = nil_;
    a->parent_ = b;

    if (!b->right_->isNil())
      b->right_->parent_ = b;

    if (!a->right_->isNil())
      a->right_->parent_ = a;

    if (!a->left_->isNil())
      a->left_->parent_ = a;
  } else {
    Node* aLeft = a->left_;
    Node* bRight = b->right_;
    a->left_ = b->left_;
    b->left_ = aLeft;

    b->right_ = a;
    a->right_ = bRight;

    if (!a->parent_->isNil()){
      if (a == a->parent_->left_)
        a->parent_->left_ = b;
      else
        a->parent_->right_ = b;
      b->parent_ = a->parent_;
    } else
      b->parent_ = nil_;
    a->parent_ = b;

    if (!b->left_->isNil())
      b->left_->parent_ = b;

    if (!a->left_->isNil())
      a->left_->parent_ = a;

    if (!a->right_->isNil())
      a->right_->parent_ = a;
  }

  if (a == root_)
    root_ = b;
}

template<typename T, typename U>
void BST<T, U>::rightRotate(Node* node) {
  swap(node, node->left_);
  Node* temp = node->parent_->right_;
  node->parent_->right_ = node->parent_->left_;
  node->parent_->left_ = node->parent_->right_->left_;
  node->parent_->right_->left_ = node->parent_->right_->right_;
  node->parent_->right_->right_ = temp;
  
  node->parent_->left_->parent_ = node->parent_;
  if (!node->parent_->right_->right_->parent_->isNil())
    node->parent_->right_->right_->parent_ = node->parent_->right_;
}

template<typename T, typename U>
void BST<T, U>::leftRotate(Node* node) {
  swap(node, node->right_);
  Node* temp = node->parent_->left_;
  node->parent_->left_ = node->parent_->right_;
  node->parent_->right_ = node->parent_->left_->right_;
  node->parent_->left_->right_ = node->parent_->left_->left_;
  node->parent_->left_->left_ = temp;
  
  node->parent_->right_->parent_ = node->parent_;
  if (!node->parent_->left_->left_->parent_->isNil())
    node->parent_->left_->left_->parent_ = node->parent_->left_;
}

template<typename T, typename U>
void BST<T, U>::clear() {
  deleteTree(root_);
  root_ = nil_;
}
}

#endif //S21_BST_H_