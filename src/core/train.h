#ifndef TRAIN_H_
#define TRAIN_H_

#include <iostream>
#include <algorithm>

namespace s21 {
  class BST {
  private:
    enum class NodeColor {
      BLACK,
      RED
    };

    struct Node {
      int value;
      Node* left;
      Node* right;
      Node* parent;
      NodeColor color = NodeColor::BLACK;

      Node(): left(nullptr), right(nullptr), parent(nullptr) {}
      Node(int val, Node* nil_): value(val), left(nil_), right(nil_), parent(nil_), color(NodeColor::RED) {}
    };

    Node* nil = new Node();
    Node* root;
   
  public:
    BST(): root(nil) {}
    BST(int val): root(new Node(val, nil)) {}

    ~BST() {  
      deleteTree(root);
      delete nil;
    }

    bool isEmpty() { return root == nullptr; }

    void insert(int val) {
      insertNode(val);
    }

    Node* search(int val) {
      return search(root, val);
    }

    void printTree() {
      printTree(root);
    }

    void remove(int val) {
      removeNode(val);
    }

  private:
    bool isEmpty(Node* node) { return node == nil; }

    void insertNode(int val) {
      Node* currentNode = root;
      Node* parent = nil;
      while (!isEmpty(currentNode)) {
        parent = currentNode;
        (val < currentNode->value) ? currentNode = currentNode->left
        : currentNode = currentNode->right;
      }
      Node* newNode = new Node(val, nil);
      newNode->parent = parent;
      if (parent == nil) root = newNode;
      else if (val < parent->value) parent->left = newNode;
      else parent->right = newNode;
      balanceInsert(newNode);
    }

    void balanceInsert(Node* newNode) {
      Node* uncle;
      while (newNode->parent->color == NodeColor::RED) {
        if (newNode->parent == newNode->parent->parent->left) {
          uncle = newNode->parent->parent->right;
          if (uncle->color == NodeColor::RED) {
            newNode->parent->color = NodeColor::BLACK;
            uncle->color = NodeColor::BLACK;
            newNode->parent->parent->color = NodeColor::RED;
            newNode = newNode->parent->parent;
          } else {
            if (newNode == newNode->parent->right) {
              // newNode = newNode->parent;
              leftRotate(newNode->parent);
            }
            newNode->parent->color = NodeColor::BLACK;
            newNode->parent->parent->color = NodeColor::RED;
            rightRotate(newNode->parent->parent);
          }
        } else {
          uncle = newNode->parent->parent->left;
          if (uncle->color == NodeColor::RED) {
            newNode->parent->color = NodeColor::BLACK;
            uncle->color = NodeColor::BLACK;
            newNode->parent->parent->color = NodeColor::RED;
            newNode = newNode->parent->parent;
          } else {
            if (newNode == newNode->parent->left) {
              // newNode = newNode->parent;
              rightRotate(newNode->parent);
            }
            newNode->parent->color = NodeColor::BLACK;
            newNode->parent->parent->color = NodeColor::RED;
            leftRotate(newNode->parent->parent);
          }
        }
      }
      root->color = NodeColor::BLACK;
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

    int getChildrenCount(Node* node) {
      int count = 0;
      if (!isEmpty(node->left)) count++;
      if (!isEmpty(node->right)) count++;
      return count;
    }

    Node* getChildOrMock(Node* node) {
      return isEmpty(node->left) ? node->right : node->left;
    }

    void transplateNode(Node* dest, Node* src) {
      if (dest == root) root = src;
      else if (dest == dest->parent->left) dest->parent->left = src;
      else dest->parent->right = src;
      src->parent = dest->parent;
      delete dest;
    }

    void removeNode(int val) {
      Node* nodeToDelete = search(val);
      NodeColor removedNodeColor = nodeToDelete->color;
      Node* child;

      if (getChildrenCount(nodeToDelete) < 2) {
        child = getChildOrMock(nodeToDelete);
        transplateNode(nodeToDelete, child);
      } else {
        Node* minNode = getMin(nodeToDelete->right);
        nodeToDelete->value = minNode->value;
        removedNodeColor = minNode->color;
        child = getChildOrMock(minNode);
        transplateNode(minNode, child);
      }
      if (removedNodeColor == NodeColor::BLACK) balanceRemove(child);
    }

    void balanceRemove(Node* node) {
      while (node != root && node->color == NodeColor::BLACK) {
        Node* brother;
        if (node == node->parent->left) {
          brother = node->parent->right;
          if (brother->color == NodeColor::RED) {
            brother->color = NodeColor::BLACK;
            node->parent->color = NodeColor::RED;
            leftRotate(node->parent);
            brother = node->parent->right;
          }
          if (brother->left->color == NodeColor::BLACK && brother->right->color == NodeColor::BLACK) {
            brother->color = NodeColor::RED;
            node = node->parent;
          } else {
            if (brother->right->color == NodeColor::BLACK) {
              brother->left->color = NodeColor::BLACK;
              brother->color = NodeColor::RED;
              rightRotate(brother);
              brother = node->parent->right;
            }
            brother->color = node->parent->color;
            node->parent->color = NodeColor::BLACK;
            brother->right->color = NodeColor::BLACK;
            leftRotate(node->parent);
            node = root;
          }
        } else {
          brother = node->parent->left;
          if (brother->color == NodeColor::RED) {
            brother->color = NodeColor::BLACK;
            node->parent->color = NodeColor::RED;
            rightRotate(node->parent);
            brother = node->parent->left;
          }
          if (brother->left->color == NodeColor::BLACK && brother->right->color == NodeColor::BLACK) {
            // rightRotate(node->parent);
            // brother = node->parent->left;
            brother->color = NodeColor::RED;
            node = node->parent;
          } else {
            if (brother->left->color == NodeColor::BLACK) {
              brother->right->color = NodeColor::BLACK;
              brother->color = NodeColor::RED;
              leftRotate(brother);
              brother = node->parent->left;
            }
            brother->color = node->parent->color;
            node->parent->color = NodeColor::BLACK;
            brother->left->color = NodeColor::BLACK;
            rightRotate(node->parent);
            node = root;
          }
        }
      }
      node->color = NodeColor::BLACK;
    }

    Node* getMin(Node* node) {
      if (isEmpty(node)) return node;

      if (isEmpty(node->left)) return node;
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

    void swap(Node* a, Node* b) {
      int temp = a->value;
      NodeColor tempColor = a->color;

      a->color = b->color;
      b->color = tempColor;
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
      
      node->left->parent = node;
      node->right->right->parent = node->right;
    }

    void leftRotate(Node* node) {
      swap(node, node->right);
      Node* temp = node->left;
      node->left = node->right;
      node->right = node->left->right;
      node->left->right = node->left->left;
      node->left->left = temp;
      
      node->right->parent = node;
      node->left->left->parent = node->left;
    }


  };
}

#endif //TRAIN_H