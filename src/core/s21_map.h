#ifndef S21_MAP_H_
#define S21_MAP_H_

#include "s21_bst.h"
#include <limits>

namespace s21 {
template<typename T, typename U>
class MapIterator {
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = std::pair<const T, U>;
  using difference_type = std::ptrdiff_t;
  using pointer = value_type*;
  using reference = value_type&;
public:
  MapIterator() = default;
  MapIterator(typename BST<T, U>::Node *ptr) : ptr_(ptr) {}

  bool operator==(const MapIterator& other) { return ptr_ == other.ptr_; }
  bool operator!=(const MapIterator& other) { return !(*this == other); }

  MapIterator& operator++() {
    ptr_ = RBT_increment(ptr_);
    return *this;
  }

  MapIterator operator++(int) {
    MapIterator temp = *this;
    ++*this;
    return temp;
  }

  MapIterator& operator--() {
    ptr_ = RBT_decrement(ptr_);
    return *this;
  }
  
  MapIterator operator--(int) {
    MapIterator temp = *this;
    --*this;
    return temp;
  }

  reference operator*() {
    return ptr_->pair_;
  }

private:
  typename BST<T, U>::Node *ptr_ = nullptr;
  typename BST<T, U>::Node* RBT_increment(typename BST<T, U>::Node *ptr);
  typename BST<T, U>::Node* RBT_decrement(typename BST<T, U>::Node *ptr);
};

template<typename T, typename U>
typename BST<T, U>::Node* MapIterator<T, U>::RBT_increment(typename BST<T, U>::Node *ptr) {
  if (!ptr->right_->isNil()) {
    ptr = ptr->right_;
    while (!ptr->left_->isNil())
      ptr = ptr->left_;
  } else {
    typename BST<T, U>::Node* parent = ptr->parent_;
    while (ptr == parent->right_) {
      ptr = parent;
      parent = parent->parent_;
    }
    if (ptr->right_ != parent)
      ptr = parent;
  }
  return ptr;
}

template<typename T, typename U>
typename BST<T, U>::Node* MapIterator<T, U>::RBT_decrement(typename BST<T, U>::Node *ptr) {
  if (!ptr->left_->isNil()) {
    ptr = ptr->left_;
    while (!ptr->right_->isNil())
      ptr = ptr->right_;
  } else {
    typename BST<T, U>::Node* parent = ptr->parent_;
    while (ptr == parent->left_) {
      ptr = parent;
      parent = parent->parent_;
    }
    if (ptr->left_ != parent)
      ptr = parent;
  }
  return ptr;
}

template<typename T, typename U>
class MapConstIterator : public MapIterator<T, U> {
public:
  using value_type = std::pair<const T, U>;
  using const_reference = const value_type&;
public:
  MapConstIterator(MapIterator<T, U> other) : MapIterator<T, U>(other) {}
  const_reference operator*() {
    return MapIterator<T, U>::operator*();
  }
};

template<typename T, typename U>
class map {
public:
  using key_type = T;
  using mapped_type = U;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = MapIterator<key_type, mapped_type>;
  using const_iterator = MapConstIterator<key_type, mapped_type>;
  using size_type = std::size_t;
private:
  BST<T, U> btree_;
  size_type size_;
public:
  map();
  map(std::initializer_list<value_type> const &items);
  map(const map &other);
  map(map &&other) noexcept;

  map<key_type, mapped_type>& operator=(map &&other);
  mapped_type& at(const key_type& key);
  mapped_type& at(const key_type& key) const;
  mapped_type& operator[](const key_type& key);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;

  bool empty() { return btree_.isEmpty(); }
  size_type size() { return size_; }
  static size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const key_type& key, const mapped_type& obj);
  std::pair<iterator, bool> insert_or_assign(const key_type& key, const mapped_type& obj);

  void erase(iterator pos);
  void swap(map& other);
  void merge(map& other);
};

template<typename key_type, typename mapped_type>
typename map<key_type, mapped_type>::size_type map<key_type, mapped_type>::max_size() {
  return std::numeric_limits<size_type>::max()
  / sizeof(typename BST<key_type, mapped_type>::Node)
  / 4294967296;
}

template<typename key_type, typename mapped_type>
map<key_type, mapped_type>::map()
  : btree_()
  , size_(0) {}

template<typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(std::initializer_list<value_type> const &items)
  : btree_()
  , size_(0) {
  for (const_reference p : items)
    if (btree_.insert(p).second)
      size_++;
}

template<typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(const map& other)
  : btree_()
  , size_(other.size_) {
  //~isEmpty!
  for (auto it : other)
    this->btree_.insert(it);
}

template<typename key_type, typename mapped_type>
map<key_type, mapped_type>::map(map &&other) noexcept
  : btree_(other.btree_)
  , size_(other.size_) {
  if (this != &other) {
    other.btree_.moveClear();
    other.size_ = 0;
  }
}

template<typename key_type, typename mapped_type>
map<key_type, mapped_type>& map<key_type, mapped_type>::operator=(map &&other) {
  if (this == &other)
    return *this;
  map<key_type, mapped_type> temp{std::move(this)};
  btree_ = other.btree_;
  size_ = other.size_;

  other.btree_.moveClear();
  other.size_ = 0;

  return *this;
}

template<typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::at(const key_type& key) {
  typename BST<key_type, mapped_type>::Node* temp = btree_.search(key);
  if (temp == nullptr)
    throw std::out_of_range("Element with the current key was not found!");
  else
    return temp->pair_.second;
}

template<typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::at(const key_type& key) const {
  typename BST<key_type, mapped_type>::Node* temp = btree_.search(key);
  if (temp == nullptr)
    throw std::out_of_range("Element with the current key was not found!");
  else
    return temp->pair_.second;
}

template<typename key_type, typename mapped_type>
mapped_type& map<key_type, mapped_type>::operator[](const key_type& key) {
  std::pair<typename BST<key_type, mapped_type>::Node*, bool> temp = btree_.insert(key);
  if (temp.second)
    size_++;
  return temp.first->pair_.second;
}

template<typename key_type, typename mapped_type>
MapIterator<key_type, mapped_type> map<key_type, mapped_type>::begin() {
  MapIterator<key_type, mapped_type> it{btree_.getMin()};
  return it;
}

template<typename key_type, typename mapped_type>
MapConstIterator<key_type, mapped_type> map<key_type, mapped_type>::begin() const {
  MapConstIterator<key_type, mapped_type> it{btree_.getMin()};
  return it;
}

template<typename key_type, typename mapped_type>
MapIterator<key_type, mapped_type> map<key_type, mapped_type>::end() {
  MapIterator<key_type, mapped_type> it{btree_.getMax()};
  return it;
}

template<typename key_type, typename mapped_type>
MapConstIterator<key_type, mapped_type> map<key_type, mapped_type>::end() const {
  MapConstIterator<key_type, mapped_type> it{btree_.getMax()};
  return it;
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::clear() {
  btree_.clear();
  size_ = 0;
}

template<typename key_type, typename mapped_type>
std::pair<MapIterator<key_type, mapped_type>, bool> map<key_type, mapped_type>::insert(const value_type& value) {
  std::pair<typename BST<key_type, mapped_type>::Node*, bool> temp = btree_.insert(value);
  if (temp.second)
    size_++;
  return std::make_pair(MapIterator<key_type, mapped_type>(temp.first), temp.second);
}

template<typename key_type, typename mapped_type>
std::pair<MapIterator<key_type, mapped_type>, bool> map<key_type, mapped_type>::insert(const key_type& key, const mapped_type& obj) {
  std::pair<typename BST<key_type, mapped_type>::Node*, bool> temp = btree_.insert(key, obj);
  if (temp.second)
    size_++;
  return std::make_pair(MapIterator<key_type, mapped_type>(temp.first), temp.second);
}

template<typename key_type, typename mapped_type>
std::pair<MapIterator<key_type, mapped_type>, bool> map<key_type, mapped_type>::insert_or_assign(const key_type& key, const mapped_type& obj) {
  std::pair<typename BST<key_type, mapped_type>::Node*, bool> temp = btree_.insert(key, obj);
  if (temp.second)
    size_++;
  else
    temp.first->pair_.second = obj;
  return std::make_pair(MapIterator<key_type, mapped_type>(temp.first), temp.second);
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::erase(iterator pos) {
  btree_.remove((*pos).first);
  size_--;
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::swap(map& other) {
  btree_.swapTree(other.btree_);
  std::swap(size_, other.size_);
}

template<typename key_type, typename mapped_type>
void map<key_type, mapped_type>::merge(map& other) {
  for (auto it : other)
    insert(it);
}
}

#endif //S21_MAP_H_