#include "string.hpp"

#include <iostream>
#include <string>

int main() {
    MyString str = "abcdef";
    MyString substr = str.substr(0);
    MyString str2 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAaaa";
    str2.insert(5, str);

    std::cout << str2 << std::endl;
}
