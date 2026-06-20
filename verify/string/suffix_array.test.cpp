#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../string/suffix_array.hpp"

#include <iostream>
#include <string>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string text;
    std::cin >> text;
    std::vector<int> suffixes = m1une::string::suffix_array(text);
    for (int i = 0; i < int(suffixes.size()); i++) {
        if (i != 0) std::cout << ' ';
        std::cout << suffixes[i];
    }
    std::cout << '\n';
}
