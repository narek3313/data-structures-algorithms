#ifndef MYSTRING_HPP
#define MYSTRING_HPP

#include <cstddef>
#include <iterator>
#define NULL_TERM 1
#define DEF_CAPACITY 15

#include <cstdint>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <utility>

class MyString {
    using size_t = uint64_t;

   public:
    struct Iterator {
        /* defining tags */
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = char;
        using pointer = char*;
        using reference = char&;

        /* constructors */

        Iterator(pointer ptr) { m_ptr = ptr; }
        Iterator(const Iterator& other) { m_ptr = other.m_ptr; }

        /* overriding operators */

        reference operator*() { return *m_ptr; }
        pointer operator->() { return m_ptr; }

        // prefix
        Iterator& operator++() {
            m_ptr++;
            return *this;
        }

        // postfix
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; }
        friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; }

        Iterator& operator=(const Iterator& other) {
            m_ptr = other.m_ptr;
            return *this;
        }

        ~Iterator() { m_ptr = nullptr; }

       private:
        pointer m_ptr;
    };
    /* constructors */
    MyString() {
        m_size = 0;
        m_capacity = DEF_CAPACITY;
        m_data = new char[m_capacity];
        m_data[0] = '\0';
    }

    MyString(const char* c_string) {
        size_t cs_size = get_size_cs(c_string);

        m_size = cs_size;
        m_capacity = cs_size < DEF_CAPACITY ? DEF_CAPACITY : cs_size + DEF_CAPACITY;
        m_data = new char[m_capacity];

        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = c_string[i];
        }
        m_data[m_size] = '\0';
    }

    MyString(const char* c_string, size_t count) {
        m_size = count;
        m_capacity = count + DEF_CAPACITY;
        m_data = new char[m_capacity];

        for (size_t i = 0; i < count; i++) {
            m_data[i] = c_string[i];
        }

        m_data[m_size] = '\0';
    }

    MyString(size_t count, char c) {
        m_size = count;
        if (count < DEF_CAPACITY) {
            m_capacity = DEF_CAPACITY;
        } else {
            m_capacity = count + DEF_CAPACITY;
        }
        m_data = new char[m_capacity];

        for (size_t i = 0; i < count; i++) {
            m_data[i] = c;
        }

        m_data[m_size] = '\0';
    }

    // copy constructor
    MyString(const MyString& other) {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        if (m_capacity == NULL_TERM) {
            m_data = new char[m_capacity];
            m_data[0] = '\0';
        }
        m_data = new char[m_capacity];
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
        m_data[m_size] = '\0';
    }

    MyString(MyString&& other) noexcept {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = new char[m_capacity];
        for (size_t i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
        m_data[m_size] = '\0';

        other.m_data[0] = '\0';
        other.m_size = 0;
        other.m_capacity = DEF_CAPACITY;
    }

    /* desctructor */

    ~MyString() { delete[] m_data; }

    /* operator overriding */

    // copy assignment
    MyString& operator=(const MyString& other) {
        if (this != &other) {
            MyString tmp(other);
            std::swap(m_data, tmp.m_data);
            std::swap(m_size, tmp.m_size);
            std::swap(m_capacity, tmp.m_capacity);
        }
        return *this;
    }

    // move assignment
    MyString& operator=(MyString&& other) noexcept {
        if (this != &other) {
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            // deleting the old data and reallocating with new capacity
            delete[] m_data;
            m_data = new char[m_capacity];
            for (size_t i = 0; i < m_size; i++) {
                m_data[i] = other.m_data[i];
            }

            m_data[m_size] = '\0';

            other.m_data[0] = '\0';
            other.m_size = 0;
            other.m_capacity = DEF_CAPACITY;
        }

        return *this;
    }

    friend std::ostream& operator<<(std::ostream& target, const MyString& source) {
        target << source.m_data;
        return target;
    }

    char& at(size_t index) {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    const char& at(size_t index) const {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_data[index];
    }

    MyString& operator+=(const MyString& other) {
        reserve_if_needed(other.m_size);

        size_t new_size = m_size + other.m_size;

        size_t other_idx = 0;
        for (size_t i = m_size; i < new_size && other_idx < other.m_size; i++, other_idx++) {
            m_data[i] = other[other_idx];
        }

        m_size = new_size;
        m_data[m_size] = '\0';

        return *this;
    }

    bool operator==(const MyString& other) {
        if (m_size != other.m_size) {
            return false;
        }

        for (size_t i = 0; i < m_size; i++) {
            if (m_data[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const MyString& other) {
        if (m_size != other.m_size) {
            return true;
        }

        for (size_t i = 0; i < m_size; i++) {
            if (m_data[i] != other[i]) {
                return true;
            }
        }

        return false;
    }

    /* compare */

    static bool lexicographical_compare(Iterator first1, Iterator last1, Iterator first2,
                                        Iterator last2) {}

    char& operator[](size_t index) { return m_data[index]; }
    const char& operator[](size_t index) const { return m_data[index]; }

    /* size, data manipulations */

    // NOTE: capacity also includes the null terminator.
    //  When you want to reserve room for a
    //  string of size n make the new_capacity atleas n+1
    //
    //
    void reserve(size_t new_capacity) {
        if (new_capacity <= m_capacity) {
            return;
        }

        char* tmp = new char[new_capacity];
        for (size_t i = 0; i < m_size; i++) {
            tmp[i] = m_data[i];
        }

        delete[] m_data;
        m_data = tmp;
        m_data[m_size] = '\0';
        m_capacity = new_capacity;
    }

    void resize(size_t new_size, char value = char{}) {
        if (new_size > m_capacity) {
            size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity;
            while (new_capacity < new_size) new_capacity *= 2;
            reserve(new_capacity);
        }

        for (size_t i = m_size; i < new_size; i++) {
            m_data[i] = value;
        }

        m_size = new_size;

        m_data[m_size] = '\0';
    }

    void shrink_to_fit() {
        if (m_size >= m_capacity) {
            return;
        }
        if (m_size <= DEF_CAPACITY) {
            // Capacity should always be atleas 1 more than size to fit the null term
            m_capacity = DEF_CAPACITY + NULL_TERM;
        } else {
            m_capacity = m_size + NULL_TERM;
        }
        char* tmp = new char[m_capacity];
        for (size_t i = 0; i < m_size; i++) {
            tmp[i] = m_data[i];
        }

        delete[] m_data;

        m_data = tmp;

        m_data[m_size] = '\0';
    }

    void push_back(char c) {
        reserve_if_needed();

        m_data[m_size++] = c;
        m_data[m_size] = '\0';
    }

    void pop_back() { m_data[--m_size] = '\0'; }

    MyString& append(const char* c_string) {
        size_t cs_size = get_size_cs(c_string);
        reserve_if_needed(cs_size);
        size_t new_size = m_size + cs_size;

        size_t cs_idx = 0;
        for (size_t i = m_size; i < new_size; i++) {
            m_data[i] = c_string[cs_idx];
            cs_idx++;
        }

        m_size = new_size;

        m_data[m_size] = '\0';

        return *this;
    }

    MyString& append(const char* c_string, size_t count) {
        size_t cs_size = get_size_cs(c_string);
        if (cs_size < count) {
            throw std::out_of_range("Count cannot be bigger than the string size");
        }
        reserve_if_needed(count);
        size_t new_size = m_size + count;

        size_t cs_idx = 0;
        size_t i = m_size;
        while (cs_idx < count && i < new_size) {
            m_data[i] = c_string[cs_idx];
            i++;
            cs_idx++;
        }

        m_size = new_size;

        m_data[m_size] = '\0';

        return *this;
    }

    MyString& append(const MyString& other) { return *this += other; }

    MyString substr(size_t pos = 0, size_t len = npos) {
        if (pos > m_size - 1) {
            throw std::out_of_range("Position is out of range");
        }

        if (pos + len > m_size) {
            len = m_size - pos;
        }

        MyString substr;

        for (size_t i = pos; i < pos + len; i++) {
            substr.push_back(m_data[i]);
        }
        substr[substr.m_size] = '\0';
        return substr;
    }

    // TODO: there is a better way to do this, but i dont know how yet
    MyString& insert(size_t pos, const MyString& str, size_t len = npos) {
        if (len > str.m_size) {
            len = str.m_size;
        }
        reserve_if_needed(len);

        MyString left_substr = this->substr(0, pos);
        MyString right_substr = this->substr(pos);
        left_substr += str;

        left_substr += right_substr;
        *this = left_substr;

        return *this;
    }

    MyString& erase(size_t pos = 0, size_t len = npos) {
        MyString left_substr = this->substr(0, pos);
        MyString right_substr = this->substr(pos + len, npos);

        left_substr += right_substr;

        *this = left_substr;

        return *this;
    }

    /* iterators */

    Iterator begin() { return Iterator(&m_data[0]); }
    Iterator end() { return Iterator(&m_data[m_size]); }

    const Iterator begin() const { return Iterator(&m_data[0]); }
    const Iterator end() const { return Iterator(&m_data[m_capacity + 1]); }

    /* getters */
    size_t size() const { return m_size; }
    size_t capacity() const { return m_capacity; }
    bool empty() const { return m_size == 0; }
    char& front() const { return m_data[0]; }
    char& back() const { return m_size == 0 ? m_data[0] : m_data[m_size - NULL_TERM]; }
    const char* c_str() const {
        char* arr = new char[m_capacity];
        for (size_t i = 0; i < m_size; i++) {
            arr[i] = m_data[i];
        }

        arr[m_size] = '\0';

        return arr;
    }

    char* c_str() {
        char* arr = new char[m_capacity];
        for (size_t i = 0; i < m_size; i++) {
            arr[i] = m_data[i];
        }

        arr[m_size] = '\0';

        return arr;
    }

   private:
    size_t m_size;
    size_t m_capacity;
    char* m_data;
    static const size_t npos = 4294967295;

    void reserve_if_needed(size_t added = 0) {
        if (npos - added < m_size) {
            throw std::out_of_range("Max size exceeded");
        }
        size_t new_capacity = (m_capacity == 0) ? 1 : m_capacity;
        // we cant multiply if its more than half of the limit
        if (new_capacity >= npos / 2) {
            new_capacity += new_capacity / 4;
        } else {
            while (m_size + added >= new_capacity - NULL_TERM) new_capacity *= 2;
        }
        reserve(new_capacity);
    }

    size_t get_size_cs(const char* c_string) {
        size_t idx = 0;
        size_t size = 0;
        while (c_string[idx] != '\0') {
            idx++;
            size++;
        }
        return size;
    }
};

#endif
