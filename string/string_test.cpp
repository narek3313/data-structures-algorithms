#include "string.hpp"

#include <cassert>
#include <iostream>

void test_constructors() {
    MyString s1;
    assert(s1.size() == 0);
    std::cout << "constructors: default success\n";

    MyString s2("hello");
    assert(s2.size() == 5 && s2[0] == 'h');
    std::cout << "constructors: c-string success\n";

    MyString s3("world", 3);
    assert(s3.size() == 3 && s3[2] == 'r');
    std::cout << "constructors: partial success\n";

    MyString s4(4, 'x');
    assert(s4.size() == 4 && s4[1] == 'x');
    std::cout << "constructors: fill success\n";

    MyString s5(s2);
    assert(s5 == s2);
    std::cout << "constructors: copy success\n";

    MyString s6(std::move(s3));
    assert(s6.size() == 3);
    std::cout << "constructors: move success\n";
}

void test_assignment() {
    MyString s1("abc");
    MyString s2;
    s2 = s1;
    assert(s2 == s1);
    std::cout << "assignment: copy success\n";

    MyString s3("xyz");
    s2 = std::move(s3);
    assert(s2.size() == 3);
    std::cout << "assignment: move success\n";
}

void test_append() {
    MyString s1("Hi");
    s1.append(" there");
    assert(s1 == MyString("Hi there"));
    std::cout << "append: c-string success\n";

    MyString s2("A");
    s2.append("BCD", 2);
    assert(s2 == MyString("ABC"));
    std::cout << "append: partial success\n";

    MyString s3("123");
    s3.append(MyString("456"));
    assert(s3 == MyString("123456"));
    std::cout << "append: MyString success\n";
}

void test_plus_equal() {
    MyString s1("Hello"), s2("World");
    s1 += s2;
    assert(s1 == MyString("HelloWorld"));
    std::cout << "operator+= success\n";
}

void test_push_pop() {
    MyString s("a");
    s.push_back('b');
    assert(s == MyString("ab"));
    std::cout << "push_back success\n";
    s.pop_back();
    assert(s == MyString("a"));
    std::cout << "pop_back success\n";
}

void test_resize_reserve_shrink() {
    MyString s("test");
    s.resize(6, 'x');
    assert(s.size() == 6);
    std::cout << "resize success\n";
    s.shrink_to_fit();
    assert(s.capacity() >= s.size() + 1);
    std::cout << "shrink_to_fit success\n";
}

void test_at_and_index() {
    MyString s("code");
    assert(s.at(0) == 'c');
    bool threw = false;
    try {
        s.at(10);
    } catch (...) {
        threw = true;
    }
    assert(threw);
    std::cout << "at() success\n";
}

void test_substr_insert_erase() {
    MyString s("abcdef");
    MyString sub = s.substr(2, 3);
    assert(sub == MyString("cde"));
    std::cout << "substr success\n";

    s.insert(3, MyString("XYZ"));
    assert(s == MyString("abcXYZdef"));
    std::cout << "insert success\n";

    s.erase(3, 3);
    assert(s == MyString("abcdef"));
    std::cout << "erase success\n";
}

void test_iterators() {
    MyString s("abc");
    std::string temp;
    for (auto it = s.begin(); it != s.end(); ++it) temp.push_back(*it);
    assert(temp == "abc");
    std::cout << "iterators success\n";
}

void test_c_str() {
    MyString s("yo");
    const char* cs = s.c_str();
    assert(cs[0] == 'y' && cs[1] == 'o');
    delete[] cs;
    std::cout << "c_str success\n";
}

void test_comparisons() {
    MyString a("same"), b("same"), c("diff");
    assert(a == b);
    assert(a != c);
    std::cout << "comparisons success\n";
}

void test_lexicographical_compare() {
    MyString s1("abc"), s2("abd"), s3("abc"), s4("ab");
    assert(MyString::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end()));
    assert(!MyString::lexicographical_compare(s2.begin(), s2.end(), s1.begin(), s1.end()));
    assert(!MyString::lexicographical_compare(s1.begin(), s1.end(), s3.begin(), s3.end()));
    assert(!MyString::lexicographical_compare(s1.begin(), s1.end(), s4.begin(), s4.end()));
    assert(MyString::lexicographical_compare(s4.begin(), s4.end(), s1.begin(), s1.end()));
    std::cout << "lexicographical_compare success\n";
}

int main() {
    test_constructors();
    test_assignment();
    test_append();
    test_plus_equal();
    test_push_pop();
    test_resize_reserve_shrink();
    test_at_and_index();
    test_substr_insert_erase();
    test_iterators();
    test_c_str();
    test_comparisons();
    test_lexicographical_compare();
    std::cout << "\n✅ All tests passed\n";
    return 0;
}
