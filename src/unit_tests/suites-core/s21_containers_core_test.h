#ifndef SRC_UNIT_S21_MATRIX_CORE_TEST_H_
#define SRC_UNIT_S21_MATRIX_CORE_TEST_H_

#include <gtest/gtest.h>

#include "s21_containers.h"

#define LOOP_TESTS_QUANTITY 50

class MockClass {
public:
  MockClass() : data_(new int[size_]), subData_(42) {
    for (int i = 0; i < size_; i++) {
      data_[i] = i * 2;
    }
  }

  MockClass(int subData) : data_(new int[size_]), subData_(subData) {
    for (int i = 0; i < size_; i++) {
      data_[i] = i * 2;
    }
  }

  MockClass(const MockClass& other) : data_(new int[size_]), subData_(other.subData_) {
    for (int i = 0; i < size_; i++) {
      data_[i] = other.data_[i];
    }
  }

  MockClass(MockClass&& other) noexcept : data_(other.data_), subData_(other.subData_) {
    other.data_ = nullptr;
    other.subData_ = 0;
  }

  ~MockClass() {
    if (data_ != nullptr) delete[] data_;
    data_ = nullptr;
  }

  MockClass& operator=(const MockClass& other) {
    if (this != &other) {
      delete[] data_;
      data_ = new int[other.size_];
      for (int i = 0; i < size_; i++) {
        data_[i] = other.data_[i];
      }
      subData_ = other.subData_;
    }
    return *this;
  }

  MockClass& operator=(MockClass&& other) noexcept {
    if (this != &other) {
      delete[] data_;
      data_ = other.data_;
      subData_ = other.subData_;
      other.data_ = nullptr;
      other.subData_ = 0;
    }
    return *this;
  }

  bool operator==(const MockClass& other) const noexcept {
    bool res = subData_ == other.subData_;

    for (int i = 0; i < size_; i++) {
      res = (data_[i] == other.data_[i]);
    }

    return res;
  }

  MockClass& operator*(const int mult) noexcept {
    subData_ *= mult;

    for (int i = 0; i < size_; i++) {
      data_[i] *= mult;
    }

    return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, const MockClass& obj) {
    os << "Size: " << obj.size_ << ", " << "Subdata: " << obj.subData_ << std::endl;
    os << "Data: " << std::endl;
    for (int i = 0; i < obj.size_; i++) {
      os << "[" << i << "] = " << obj.data_[i] << std::endl;
    }

    return os;
  }

private:
  const int size_ = 10;
  int* data_;
  int subData_;
};

class NoConstructClass {
  NoConstructClass() = delete;
  int inner_value = 5;
};

#endif  // SRC_UNIT_S21_MATRIX_CORE_TEST_H_