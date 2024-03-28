#ifndef ARRAY
#define ARRAY

#include <algorithm>

template <class T, std::size_t N>
class Array {
 private:
  T buffer_[N];

 public:
  Array() {
    for (size_t i = 0; i < N; ++i) {
      buffer_[i] = T{};
    }
  }

  Array(std::initializer_list<T> init) {
    for (size_t i = 0; i < N; ++i) {
      buffer_[i] = T{};
    }
    std::copy(init.begin(), init.end(), buffer_);
  }

  const T& operator[](size_t i) const {
    return buffer_[i];
  }

  const T& Front() const {
    return buffer_[0];
  }

  const T& Back() const {
    return buffer_[N - 1];
  }

  const T* Data() const {
    return buffer_;
  }

  T& operator[](size_t i) {
    return buffer_[i];
  }

  T& Front() {
    return buffer_[0];
  }

  T& Back() {
    return buffer_[N - 1];
  }

  T* Data() {
    return buffer_;
  }

  size_t Size() const {
    return N;
  }

  bool Empty() const {
    return N == 0ll;
  }

  void Fill(const T& value) {
    for (size_t i = 0; i < N; ++i) {
      buffer_[i] = value;
    }
  }

  void Swap(Array<T, N>& other) {
    for (size_t i = 0; i < N; ++i) {
      T tmp = std::move(other[i]);
      other[i] = std::move(buffer_[i]);
      buffer_[i] = std::move(tmp);
    }
  }
};

#endif