#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cstdint>
#include <iostream>
#include <stdexcept>

template <typename T>

class MyVector {
   public:
    using size_t = uint32_t;

    MyVector() {
        this->m_size = 0;
        this->m_capacity = 0;
        this->m_data = nullptr;
    }

    MyVector(size_t size, T value = T{}) {
        this->m_size = size;
        this->m_capacity = size;
        this->m_data = new T[size];
        this->fill_array(size, value);
    }

    // copy constructor
    MyVector(const MyVector& other) {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        if (m_size > 0) {
            m_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; i++) {
                m_data[i] = other.m_data[i];
            }
        } else {
            m_data = nullptr;
        }
    }

    MyVector(MyVector&& other) noexcept {
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    ~MyVector() { delete[] m_data; }

    void push_back(T value) {
        if (m_size == m_capacity) {
            m_capacity = (m_capacity == 0) ? 1 : m_capacity * 2;
            T* tmp = new T[m_capacity];
            for (size_t i = 0; i < m_size; i++) {
                tmp[i] = m_data[i];
            }
            delete[] m_data;
            m_data = tmp;
        }
        m_data[m_size++] = value;
    }

    void pop() {
        if (m_size > 0) {
            m_size--;
        } else {
            std::cerr << "Warning: pop() called on empty vector\n";
        }
    }

    // copy assignment
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            MyVector tmp(other);
            std::swap(m_data, tmp.m_data);
            std::swap(m_size, tmp.m_size);
            std::swap(m_capacity, tmp.m_capacity);
        }
        return *this;
    }

    // move assignment
    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            delete[] m_data;

            m_data = other.m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            other.m_data = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        return *this;
    }

    // ensures capacity is set without changing internal data of vector or size
    void reserve(size_t new_capacity) {
        if (new_capacity <= m_capacity) {
            return;
        }

        T* tmp = new T[new_capacity];
        for (size_t i = 0; i < m_size; i++) {
            tmp[i] = m_data[i];
        }

        delete[] m_data;
        m_data = tmp;
        m_capacity = new_capacity;
    }

    // change size of the vector
    void resize(size_t new_size, T value = T{}) {
        if (new_size > m_capacity) {
            size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity;
            while (new_capacity < new_size) new_capacity *= 2;
            reserve(new_capacity);
        }

        for (size_t i = m_size; i < new_size; i++) {
            m_data[i] = value;
        }

        m_size = new_size;
    }

    T& at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    const T& at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    T& operator[](size_t index) { return m_data[index]; }
    const T& operator[](size_t index) const { return m_data[index]; }

    /* getter */
    size_t size() const { return this->m_size; }
    size_t capacity() const { return this->m_capacity; }

   private:
    T* m_data;
    size_t m_size;
    size_t m_capacity;

    // param size size of the vector
    // param value optional value to fill the m_dataay with
    void fill_array(size_t size, T value = T{}) {
        for (size_t i = 0; i < size; i++) {
            this->m_data[i] = value;
        }
    }
};

#endif
