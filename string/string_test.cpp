// #include "string.hpp"

#include <algorithm>
#include <iostream>
#include <string>

int main() {
    std::string str = "Bitch";
    std::string str2 = "bitch";

    bool res = std::lexicographical_compare(str.begin(), str.end(), str2.begin(), str2.end());

    std::cout << res;
}
