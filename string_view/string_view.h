#ifndef STRING_VIEW
#define STRING_VIEW

class StringView {
 public:
  const char* ptr_ = nullptr;
  size_t size_ = 0;
  StringView() = default;
  StringView(const char* a) : ptr_(a), size_(strlen(a)) {} // NOLINT
  StringView(const char* a, size_t s) : ptr_(a), size_(s) {}

  const char& operator[](size_t) const;

  const char& Front() const;

  const char& Back() const;

  size_t Size() const;

  size_t Length() const;

  bool Empty() const;

  const char* Data() const;

  void Swap(StringView&);

  void RemovePrefix(size_t);

  void RemoveSuffix(size_t);

  StringView Substr(size_t, size_t count = -1);
};

#endif