#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include "string/prefix_function.hpp"

#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::string pattern;
    std::cin >> text >> pattern;

    for (int position : m1une::string::kmp_search(text, pattern)) {
        std::cout << position << '\n';
    }
}
