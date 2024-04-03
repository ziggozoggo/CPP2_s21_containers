#ifndef SRC_S21_ITERATOR_H_
#define SRC_S21_ITERATOR_H_

namespace s21 {

template <typename T>
class BaseIterator {
public:
  BaseIterator() : item_(nullptr) {}
  BaseIterator(const T& item) : item_(&item) {}
  BaseIterator(const T* item) : item_(item) {}
  virtual ~BaseIterator() {}

  virtual BaseIterator<T>& operator++()    = 0;
  virtual BaseIterator<T>& operator++(int) = 0;
  virtual BaseIterator<T>& operator--()    = 0;
  virtual BaseIterator<T>& operator--(int) = 0;

  virtual T& operator*() const { return *item_; };

protected:
  T* item_;
};

}


#endif  // SRC_S21_CONTAINER_H_