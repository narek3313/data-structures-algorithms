#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cstdint>

template <typename T> class MyVector {
public:
  using size_t = uint32_t;

  // Constructors & Destructor
  MyVector();
  MyVector(size_t size, T value = T{});
  MyVector(const MyVector &other);
  MyVector(MyVector &&other) noexcept;
  ~MyVector();

  // Assignment operators
  MyVector &operator=(const MyVector &other);
  MyVector &operator=(MyVector &&other) noexcept;

  // Element access
  T &at(size_t index);
  const T &at(size_t index) const;
  T &operator[](size_t index);
  const T &operator[](size_t index) const;

  // Capacity
  size_t size() const;
  size_t capacity() const;
  void reserve(size_t new_capacity);
  void resize(size_t new_size, T value = T{});

  // Modifiers
  void push_back(T value);
  void pop();

private:
  T *m_data;
  size_t m_size;
  size_t m_capacity;

  // Helper
  void fill_array(size_t size, T value = T{});
};

#endif // MYVECTOR_HPP
