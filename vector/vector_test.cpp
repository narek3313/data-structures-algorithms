#include "vector.hpp"

#include <cassert>
#include <iostream>

int main() {
    using Vec = MyVector<int>;

    // test default constructor
    Vec v1;
    assert(v1.size() == 0 && v1.capacity() == 0);
    std::cout << "Default constructor passed" << std::endl;

    // test push_back
    v1.push_back(10);
    v1.push_back(20);
    assert(v1.size() == 2);
    assert(v1[0] == 10 && v1[1] == 20);
    std::cout << "Push_back passed" << std::endl;

    // test pop
    v1.pop();
    assert(v1.size() == 1);
    assert(v1[0] == 10);
    v1.pop();
    assert(v1.size() == 0);
    std::cout << "Pop passed" << std::endl;

    // test pop on empty vector
    v1.pop();  // should print warning but not crash
    std::cout << "Pop on empty passed" << std::endl;

    // test constructor with size and default value
    Vec v2(5, 42);
    assert(v2.size() == 5);
    for (size_t i = 0; i < v2.size(); i++) {
        assert(v2[i] == 42);
    }
    std::cout << "Constructor with size passed" << std::endl;

    // test copy constructor
    Vec v3 = v2;
    assert(v3.size() == 5);
    assert(v3[0] == 42);
    v3[0] = 100;
    assert(v2[0] == 42);
    std::cout << "Copy constructor passed" << std::endl;

    // test copy assignment
    Vec v4;
    v4 = v2;
    assert(v4.size() == 5 && v4[1] == 42);
    std::cout << "Copy assignment passed" << std::endl;

    // test move constructor
    Vec v5 = std::move(v4);
    assert(v5.size() == 5);
    assert(v4.size() == 0);
    std::cout << "Move constructor passed" << std::endl;

    // test move assignment
    Vec v6;
    v6 = std::move(v5);
    assert(v6.size() == 5);
    assert(v5.size() == 0);
    std::cout << "Move assignment passed" << std::endl;

    // test at() bounds check
    try {
        v6.at(10);      // out of range
        assert(false);  // should not reach here
    } catch (const std::out_of_range&) {
        std::cout << "At() bounds check passed" << std::endl;
    }

    // test resize
    v6.resize(8, 99);
    assert(v6.size() == 8);
    assert(v6[5] == 99 && v6[7] == 99);
    v6.resize(3);  // shrink
    assert(v6.size() == 3);
    std::cout << "Resize passed" << std::endl;

    // test reserve
    size_t old_cap = v6.capacity();
    v6.reserve(old_cap + 10);
    assert(v6.capacity() >= old_cap + 10);
    std::cout << "Reserve passed" << std::endl;

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
