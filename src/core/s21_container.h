#ifndef SRC_S21_CONTAINER_H_
#define SRC_S21_CONTAINER_H_

#include <cstddef>

namespace s21 {

template <typename T>
class IContainer {
public:
  using size_type = std::size_t;

  class iterator;
  class const_iterator;

  virtual ~IContainer() {}

  virtual size_type size() const = 0;
  virtual size_type max_size() const = 0;
  virtual bool empty() const = 0;

  virtual constexpr iterator insert(const_iterator pos, const T& value) = 0;
  virtual void clear() = 0;
  virtual void erase(const T& value) = 0;

  virtual void swap(IContainer& other) noexcept = 0;

  virtual iterator begin() = 0;
  virtual iterator end() = 0;

  virtual constexpr IContainer& operator=(const IContainer& other) = 0;
  virtual constexpr IContainer& operator=(IContainer&& other) noexcept = 0;
};

}

#endif  // SRC_S21_CONTAINER_H_