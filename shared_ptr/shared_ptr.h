#ifndef SHAREDPTR
#define SHAREDPTR

#include <stdexcept>

class BadWeakPtr : public std::runtime_error {
 public:
  BadWeakPtr() : std::runtime_error("BadWeakPtr") {
  }
};

template <class T>
class SharedPtr {
 private:
  T* ptr_ = nullptr;
  size_t* strong_counter_ = nullptr;

  void Deleter() {
    if (strong_counter_) {
      (*strong_counter_)--;
      if (*strong_counter_ == 0) {
        delete strong_counter_;
        delete ptr_;
      }
    }
  }
  
 public:
  
  SharedPtr() : ptr_(nullptr), strong_counter_(nullptr) {};
  SharedPtr(std::nullptr_t) : ptr_(nullptr), strong_counter_(nullptr) {}; // NOLINT
  explicit SharedPtr(T* ptr) : ptr_(ptr), strong_counter_(new size_t(1)){
  }

  SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
    if (strong_counter_) {
      (*strong_counter_)++;
    }
  }
  SharedPtr& operator=(const SharedPtr<T>& other) {
    SharedPtr(other).Swap(*this);
    return *this;
  }

  SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), strong_counter_(other.strong_counter_) {
    other.ptr_ = nullptr;
    other.strong_counter_ = nullptr;
  };

  SharedPtr& operator=(SharedPtr<T>&& other) noexcept {
    SharedPtr(std::move(other)).Swap(*this);
    return *this;
  }

  ~SharedPtr() {
    Deleter();
  }

  void Reset(T* ptr = nullptr) {
    if (ptr == nullptr) {
      SharedPtr(nullptr).Swap(*this);
      return;
    }
    SharedPtr(ptr).Swap(*this);
  }

  void Swap(SharedPtr<T>& other) {
    std::swap(other.ptr_, ptr_);

    std::swap(other.strong_counter_, strong_counter_);
  }

  T* const Get() const {
    return ptr_;
  }

  T* operator->() const {
    return ptr_;
  }

  size_t UseCount() const {
    if (strong_counter_){
      return *strong_counter_;
    }
    return 0;
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  T& operator*() const {
    return *ptr_;
  }
};

template <class T, class ...Args>
SharedPtr<T> MakeShared(Args&&... args) {
  return UniquePtr(new T(std::forward<Args>(args)...));
}

#endif