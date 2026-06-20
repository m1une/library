#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_palindromes"

#include "string/manacher.hpp"

#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;
    m1une::string::ManacherResult result = m1une::string::manacher(text);

    for (int center = 0; center < 2 * int(text.size()) - 1; center++) {
        if (center != 0) std::cout << ' ';
        if (center & 1) {
            std::cout << 2 * result.even[(center + 1) / 2];
        } else {
            std::cout << 2 * result.odd[center / 2] - 1;
        }
    }
    std::cout << '\n';
}
