#include "s21_map.h"
// #include <set>
// #include <map>

int main() {
    // s21::BST<int, int> btree;
    // s21::map<int, int> myMap({{5, 30}, {4, 13}, {3, 34}, {2, 23}
    //     , {1, 56}, {0, 30}, {10, 13}, {11, 34}, {8, 23}, {6, 56}
    //     , {15, 56}});

    s21::map<std::string, char> myMap{{"Anna", 'b'}, {"Bob", 'a'}, {"Zerka", 'k'}, {"Kolin", 'h'}
        , {"Nigger", 'n'}, {"Bob", 'x'}, {"Ivan", 'y'}, {"Loki", 'g'}, {"Pupka", 'i'}, {"Zalupka", 'm'}
        , {"Pushkin", 'q'}};

    s21::map<std::string, char> copyMap{myMap};

    s21::map<std::string, char> movedMap = std::move(copyMap);

    std::cout << myMap.empty() << copyMap.empty() << movedMap.empty() << '\n';

    

    // btree.insert({5, 22});
    // btree.insert({4, 41});
    // btree.insert({3, 34});
    // btree.insert({2, 23});
    // btree.insert({1, 56});
    // btree.insert({0, 30});
    // btree.insert({10, 13});
    // btree.insert({11, 34});
    // btree.insert({8, 23});
    // btree.insert({6, 56});
    // btree.insert({15, 56});
    // btree.insert({15, 56});
    // btree.insert({15, 56});

    s21::MapIterator<std::string, char> it = myMap.end();
    
    s21::MapConstIterator<std::string, char> const_it(it);

    // myMap.at("Nigger") = 'z';

    std::cout << myMap.at("Nigger") << ' ' << myMap.at("Zalupka") << '\n';

    myMap["Nigger"] = 'z';
    myMap["Travoman"] = 'q';

    std::cout << myMap["Nigger"] << ' ' << myMap["Zalupka"] << ' ' << myMap["Travoman"] << '\n';

    for (auto it1 : myMap)
        std::cout << it1.first << ' ' << it1.second << '\n';

    movedMap.clear();

    movedMap.insert({"aboba", 'f'});
    movedMap.insert({"pencil", 'o'});
    movedMap.insert({"mnt", 'l'});
    movedMap.insert("popa", 'r');
    movedMap.insert("lol", 'g');
    movedMap.insert_or_assign("lol", 'u');
    movedMap.insert_or_assign("lolo", 'a');

    s21::MapIterator<std::string, char> it3 = movedMap.begin();
    ++it3;
    std::cout << (*it3).first << '\n';
    movedMap.erase(it3);
    std::cout << myMap.size() << ' ' << copyMap.size() << ' ' << movedMap.size() << '\n';

    myMap.swap(movedMap);
    std::cout << myMap.size() << ' ' << copyMap.size() << ' ' << movedMap.size() << '\n';

    myMap.merge(movedMap);
    for (auto it4 : myMap)
        std::cout << it4.first << ' ' << it4.second << "  ";
    std::cout << '\n';
    std::cout << myMap.size() << '\n';

    std::cout << myMap.contains("Zerka") << ' ' << myMap.contains("Zerkala") << '\n';




    // std::cout << (*const_it).first << ' ' << (*it).second << '\n';
    // (*it).second = 18;
    // std::cout << (*const_it).first << ' ' << (*it).second << '\n';

    

    // btree.printTree();
    // std::cout << std::endl;

    // btree.remove(4);
    // btree.remove(2);
    // btree.remove(10);
    // btree.remove(5);
    // btree.remove(6);
    // btree.remove(1);
    // btree.remove(11);
    // btree.remove(15);
    // btree.remove(3);
    // btree.remove(8);
    // btree.remove(0);

    // btree.printTree();


    return 0;
}