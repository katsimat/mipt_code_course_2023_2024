#ifndef UNIQUEPTR
#define UNIQUEPTR
#define MAKE_UNIQUE_IMPLEMENTED

template <class T>
class UniquePtr {
 private:
  T* ptr_ = nullptr;

 public:
  UniquePtr() = default;
  explicit UniquePtr(T* ptr) : ptr_(ptr) {
  };

  UniquePtr(const UniquePtr& other) = delete;
  UniquePtr& operator=(const UniquePtr& other) = delete;

  UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
  };
  UniquePtr& operator=(UniquePtr<T>&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = other.ptr_;
      other.ptr_ = nullptr;
    }
    return *this;
  }

  ~UniquePtr() {
    delete ptr_;
  }

  T* Release() {
    auto tmp_ptr = Get();
    ptr_ = nullptr;
    return tmp_ptr;
  }

  void Reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
    ptr = nullptr;
  }

  void Swap(UniquePtr<T>& other) {
    UniquePtr<T> tmp = std::move(other);
    other = std::move(*this);
    *this = std::move(tmp);
  }

  T* Get() const {
    return ptr_;
  }

  T* operator->() const {
    return std::move(ptr_);
  }

  explicit operator bool() const {
    return ptr_ != nullptr;
  }

  T& operator*() const {
    return *ptr_;
  }
};

template <class T, class ...Args>
UniquePtr<T> MakeUnique(Args&&... args) {
  return UniquePtr(new T(std::forward<Args>(args)...));
}

#endif