#include "s21_bst.h"
#include <set>

int main() {
    s21::BST<char> btree;

    std::set <char> mySet;
    mySet.insert('a');
    mySet.erase('c');


    // std::cout << btree.root->value;

    btree.insert('a');
    btree.insert('b');
    btree.insert('h');
    btree.insert('z');
    btree.insert('e');
    btree.insert('u');
    btree.insert('x');

    // btree.insert(10);
    // btree.insert(20);
    // btree.insert(30);
    // btree.insert(40);
    // btree.insert(25);
    // btree.insert(35);
    // btree.insert(45);
    // btree.insert(5);
    // btree.insert(50);
    // btree.insert(42);
    // btree.insert(48);

    btree.printTree();
    std::cout << std::endl;

    btree.remove('p');

    btree.remove('h');
    btree.remove('b');
    btree.remove('u');
    btree.remove('a');
    btree.remove('z');
    btree.remove('x');
    btree.remove('e');

    // btree.remove(25);
    // btree.remove(45);
    // btree.remove(40);
    // btree.remove(35);
    // btree.remove(10);
    // btree.remove(30);
    // btree.remove(5);
    // btree.remove(48);
    // btree.remove(42);
    // btree.remove(50);
    // btree.remove(20);

    btree.printTree();
    std::cout << std::endl;
    
    s21::BST<std::string> bst;
    bst.insert("abc");
    bst.insert("cba");
    bst.insert("asdgaer");
    bst.insert("gafergf");
    bst.insert("grtsgfsdgvbaerg");
    bst.insert("temp");
    bst.insert("temp2");
    bst.insert("temporary");
    bst.insert("abccca");
    bst.insert("dfed");
    


    // std::cout << bst.search(5.54).value()->value;

    


    return 0;
}