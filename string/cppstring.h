#ifndef CPPSTRING_H
#define CPPSTRING_H

#include <cstring>
#include <iostream>
#include <stdexcept>

class StringOutOfRange : public std::out_of_range {
 public:
  StringOutOfRange() : std::out_of_range("StringOutOfRange") {
  }
};

class String {
 private:
  char* data_ = nullptr;
  size_t capacity_ = 0;
  size_t size_= 0;
  size_t k_capacity_ = 100;

 public:

  String() = default;
  explicit String(size_t size, char symbol);

  String(const char* string); //NOLINT

  String(const char* string, size_t size);

  ~String();

  bool Empty() const;

  size_t Size() const;

  size_t Length() const;

  size_t Capacity() const;

  const char* Data() const;

  const char* CStr() const;

  char* Data();

  char* CStr();

  void Swap(String& other);

  String(const String& other);

  String& operator=(const String& other);

  const char& operator[](size_t i) const;

  char& operator[](size_t i);

  const char& At(size_t i) const;

  char& At(size_t i);

  const char& Front() const;

  char& Front();

  const char& Back() const;

  char& Back();

  void Clear();

  void PopBack();

  void PushBack(char);

  String& operator+=(const String&);

  void Resize(size_t, char);

  void Reserve(size_t);

  void ShrinkToFit();
};

String operator+(const String& first, const String& second);

bool operator<(const String& first, const String& second);

bool operator>(const String& first, const String& second);

bool operator<=(const String& first, const String& second);

bool operator>=(const String& first, const String& second);

bool operator==(const String& first, const String& second);

bool operator!=(const String& first, const String& second);

std::ostream& operator<<(std::ostream& os, const String& string);

#endif // CPPSTRING_H
