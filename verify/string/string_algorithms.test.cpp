#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "string/all.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace {

void test_edge_cases() {
    std::string empty;
    assert(m1une::string::z_algorithm(empty).empty());
    assert(m1une::string::prefix_function(empty).empty());
    assert(m1une::string::suffix_array(empty).empty());
    assert(m1une::string::lcp_array(empty, std::vector<int>()).empty());

    auto empty_palindromes = m1une::string::manacher(empty);
    assert(empty_palindromes.empty());
    assert(empty_palindromes.longest_length() == 0);
    assert(empty_palindromes.is_palindrome(0, 0));

    std::string text = "aaaa";
    assert(
        m1une::string::kmp_search(text, std::string("aa")) ==
        std::vector<int>({0, 1, 2})
    );
    assert(
        m1une::string::kmp_search(text, empty) ==
        std::vector<int>({0, 1, 2, 3, 4})
    );

    std::vector<int> values;
    values.push_back(2);
    values.push_back(-1);
    values.push_back(2);
    assert(
        m1une::string::suffix_array(values) ==
        std::vector<int>({1, 2, 0})
    );
    assert(
        m1une::string::z_algorithm(values) ==
        std::vector<int>({3, 0, 1})
    );

    std::string bytes;
    bytes.push_back(char(255));
    bytes.push_back(char(0));
    bytes.push_back(char(128));
    assert(
        m1une::string::suffix_array(bytes) ==
        std::vector<int>({1, 2, 0})
    );
}

void test_randomized() {
    std::uint64_t state = 31;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1500; trial++) {
        int n = int(random() % 45);
        std::string text(n, 'a');
        for (char& character : text) character = char('a' + random() % 4);

        std::vector<int> z = m1une::string::z_algorithm(text);
        for (int i = 0; i < n; i++) {
            [[maybe_unused]] int expected = 0;
            while (
                i + expected < n &&
                text[expected] == text[i + expected]
            ) {
                expected++;
            }
            assert(z[i] == expected);
        }

        std::vector<int> prefix = m1une::string::prefix_function(text);
        for (int i = 0; i < n; i++) {
            [[maybe_unused]] int expected = 0;
            for (int length = 1; length <= i; length++) {
                if (
                    text.substr(0, length) ==
                    text.substr(i - length + 1, length)
                ) {
                    expected = length;
                }
            }
            assert(prefix[i] == expected);
        }

        int pattern_length = int(random() % 12);
        std::string pattern(pattern_length, 'a');
        for (char& character : pattern) character = char('a' + random() % 4);
        std::vector<int> expected_occurrences;
        for (int i = 0; i + pattern_length <= n; i++) {
            if (text.substr(i, pattern_length) == pattern) {
                expected_occurrences.push_back(i);
            }
        }
        assert(
            m1une::string::kmp_search(text, pattern) ==
            expected_occurrences
        );

        m1une::string::ManacherResult palindromes =
            m1une::string::manacher(text);
        int longest = 0;
        for (int left = 0; left <= n; left++) {
            for (int right = left; right <= n; right++) {
                bool expected = true;
                for (int offset = 0; offset < (right - left) / 2; offset++) {
                    if (text[left + offset] != text[right - 1 - offset]) {
                        expected = false;
                        break;
                    }
                }
                assert(palindromes.is_palindrome(left, right) == expected);
                if (expected) longest = std::max(longest, right - left);
            }
        }
        assert(palindromes.longest_length() == longest);

        std::vector<int> suffixes = m1une::string::suffix_array(text);
        std::vector<int> expected_suffixes(n);
        std::iota(expected_suffixes.begin(), expected_suffixes.end(), 0);
        std::sort(
            expected_suffixes.begin(),
            expected_suffixes.end(),
            [&text](int a, int b) {
                return text.substr(a) < text.substr(b);
            }
        );
        assert(suffixes == expected_suffixes);

        std::vector<int> lcp = m1une::string::lcp_array(text, suffixes);
        for (int i = 0; i + 1 < n; i++) {
            int expected = 0;
            while (
                suffixes[i] + expected < n &&
                suffixes[i + 1] + expected < n &&
                text[suffixes[i] + expected] ==
                    text[suffixes[i + 1] + expected]
            ) {
                expected++;
            }
            assert(lcp[i] == expected);
        }
    }
}

}  // namespace

int main() {
    test_edge_cases();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
