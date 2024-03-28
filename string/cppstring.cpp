#include "cppstring.h"

#include <cstring>
#include <iostream>

void String::PopBack() {
  if (size_ == 0) {
    return;
  }
  data_[--size_] = '\0';
}

void String::PushBack(char symbol) {
  if (size_ == capacity_) {
    capacity_ = std::max(k_capacity_, 2 * capacity_);
    auto new_data = new char[capacity_ + 1];
    if (data_ != nullptr) {
      strncpy(new_data, data_, size_ + 1);
      delete[] data_;
    }
    data_ = new_data;     
  }
  data_[size_] = symbol;
  ++size_;
  data_[size_] = '\0';
}

String& String::operator+=(const String& other) {
  for (size_t i = 0; i < other.Size(); ++i) {
    this->PushBack(other.At(i));
  }
  return *this;
}


void String::Resize(size_t new_size, char symbol) {
  if (capacity_ < new_size) {
    capacity_ = new_size;
    auto new_data = new char[capacity_ + 1];
    if (data_ != nullptr) {
      strcpy(new_data, data_);
      delete[] data_;
    }
    data_ = new_data;
  }

  if (new_size > size_) {
    memset(data_ + size_, symbol, new_size - size_);
  }
  data_[new_size] = '\0';
  size_ = new_size;
}

void String::Reserve(size_t new_capacity) {
  if (capacity_ >= new_capacity) {
    return;
  }
  capacity_ = new_capacity;
  auto new_data = new char[capacity_ + 1];
  if (data_ != nullptr) {
    strcpy(new_data, data_);
    delete[] data_;
  } else {
    new_data[0] = '\0';
  }
  data_ = new_data;
}

void String::ShrinkToFit() {
  capacity_ = size_;
  if (size_ == 0) {
    delete[] data_;
    data_ = nullptr;
  }
  auto new_data = new char[capacity_ + 1];
  if (data_ != nullptr) {
    strcpy(new_data, data_);
    delete[] data_;
  }
  data_ = new_data;
}

void String::Clear() {
  size_ = 0;
}

char& String::Back() {
  return data_[size_ - 1];
}

const char& String::Back() const {
  return data_[size_ - 1];
}

char& String::Front() {
  return data_[0];
}

const char& String::Front() const {
  return data_[0];
}

char& String::At(size_t i) {
  if (i > size_ - 1) {
    throw StringOutOfRange{};
  }
  return data_[i];
}

const char& String::At(size_t i) const {
  if (i > size_ - 1) {
    throw StringOutOfRange{};
  }
  return data_[i];
}

char& String::operator[](size_t i) {
  return data_[i];
}

const char &String::operator[](size_t i) const {
  return data_[i];
}

String &String::operator=(const String &other) {
  String(other).Swap(*this);
  return *this;
}

String::String(const String& other) : data_(other.Empty() ? nullptr : new char[other.Size() + 1]), capacity_(other.Size()), size_(other.Size()) {
  if (data_ == nullptr) {
    return;
  }
  strncpy(data_, other.Data(), size_);
  data_[size_] = '\0';
}

void String::Swap(String& other) {
  std::swap(other.data_, data_);
  std::swap(other.capacity_, capacity_);
  std::swap(other.size_, size_);
}

String::String(const char* string, size_t size) : capacity_(0), size_(0) {
  if (size == 0 || string == nullptr) {
    return;
  }
  capacity_ = size;
  size_ = size;
  data_ = new char[capacity_ + 1];
  strncpy(data_, string, size);
  data_[size_] = '\0';
}

String::String(const char* string) { // NOLINT
  if (string == nullptr) {
    return;
  }
  size_ = strlen(string);
  capacity_ = size_;
  data_ = new char[capacity_ + 1];
  strncpy(data_, string, size_ + 1);
}

String::String(size_t size, char symbol) : capacity_(size), size_(size) {
  if (size == 0) {
    return;
  }
  data_ = new char[capacity_ + 1],
    std::memset(data_, symbol, size_);
  data_[size_] = '\0';
}

String::~String()  {
  delete[] data_;
}

bool String::Empty() const {
  return size_ == 0;
}

size_t String::Size() const {
  return size_;
}

size_t String::Length() const {
  return size_;
}

size_t String::Capacity() const {
  return capacity_;
}

const char* String::Data() const {
  return data_;
}

const char* String::CStr() const {
  return data_;
}

char* String::Data() {
  return data_;
}

char* String::CStr() {
  return data_;
}

String operator+(const String& first, const String& second) {
  String sum_string = first;
  sum_string += second;
  return sum_string;
}

bool operator<(const String& first, const String& second) {
  if (first.Data() == nullptr) {
    return second.Data() != nullptr;
  }
  if (second.Data() == nullptr) {
    return false;
  }
  return strcmp(first.Data(), second.Data()) < 0;
}

bool operator>(const String& first, const String& second) {
  return second < first;
}

bool operator<=(const String& first, const String& second) {
  return !(second < first);
}

bool operator>=(const String& first, const String& second) {
  return !(first < second);
}

bool operator==(const String& first, const String& second) {
  return !(second < first || first < second);
}

bool operator!=(const String& first, const String& second) {
  return (second < first || first < second);
}

std::ostream& operator<<(std::ostream& os, const String& string) {
  for (size_t i = 0; i < string.Size(); ++i) {
    os << string.At(i);
  }
  return os;
}
