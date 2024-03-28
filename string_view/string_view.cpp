#include <iostream>
#include <cstring>
#include "string_view.h"
const char& StringView::operator[](size_t i) const {
  return ptr_[i];
}

const char& StringView::Front() const {
  return ptr_[0];
}

const char& StringView::Back() const {
  return ptr_[size_ - 1];
}

size_t StringView::Size() const {
  return size_;
}

size_t StringView::Length() const {
  return size_;
}

bool StringView::Empty() const {
  return size_ == 0; 
}

const char* StringView::Data() const {
  return ptr_;
}

void StringView::Swap(StringView& str) {
  const char* tmp_ptr = ptr_;
  size_t tmp_size = size_;
  ptr_ = str.ptr_;
  size_ = str.size_;
  str.ptr_ = tmp_ptr;
  str.size_ = tmp_size;
}

void StringView::RemovePrefix(size_t prefix_size) {
  ptr_ = Data() + prefix_size;
  size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
  size_ = Size() - suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) {
  const char* ptr_str = pos + ptr_;
  size_t size__str = count < StringView::Size() - pos ? count : StringView::Size() - pos;
  StringView str(ptr_str, size__str);
  return str;
}

// int main() {
//   const char* str = "some_test_string";
//   StringView sv = str;
//   std::cout << sv.Size();
//   sv.RemovePrefix(5);
//   std::cout << sv.Size();
// }