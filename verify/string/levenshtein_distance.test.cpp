#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/DPL_1_E"

#include "../../string/levenshtein_distance.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace {

template <class Sequence1, class Sequence2>
int naive_distance(const Sequence1& first, const Sequence2& second) {
    int n = int(first.size());
    int m = int(second.size());
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int substitution = dp[i - 1][j - 1] + (first[i - 1] == second[j - 1] ? 0 : 1);
            dp[i][j] = std::min({dp[i - 1][j] + 1, dp[i][j - 1] + 1, substitution});
        }
    }
    return dp[n][m];
}

void test_edge_cases() {
    using m1une::string::levenshtein_distance;
    assert(levenshtein_distance(std::string(), std::string()) == 0);
    assert(levenshtein_distance(std::string(), std::string("abc")) == 3);
    assert(levenshtein_distance(std::string("abc"), std::string()) == 3);
    assert(levenshtein_distance(std::string("kitten"), std::string("sitting")) == 3);
    assert(levenshtein_distance(std::string("kitten"), std::string("sitting"), 3) == 3);
    assert(levenshtein_distance(std::string("kitten"), std::string("sitting"), 2) == 3);
    assert(levenshtein_distance(std::string("flaw"), std::string("lawn")) == 2);
    assert(levenshtein_distance(std::string("same"), std::string("same"), 0) == 0);
    assert(levenshtein_distance(std::string("a"), std::string("bbbb"), 1) == 2);

    std::vector<int> first = {1, 2, 3};
    std::vector<int> second = {1, 3, 4};
    assert(levenshtein_distance(first, second) == 2);

    std::string long_first(100000, 'a');
    std::string long_second = long_first;
    long_second.back() = 'b';
    assert(levenshtein_distance(long_first, long_second, 1) == 1);
}

void test_randomized() {
    std::uint64_t state = 123456789;
    auto random = [&]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2000; trial++) {
        int n = int(random() % 16);
        int m = int(random() % 16);
        std::string first(n, 'a');
        std::string second(m, 'a');
        for (char& value : first) value = char('a' + random() % 4);
        for (char& value : second) value = char('a' + random() % 4);

        [[maybe_unused]] int expected = naive_distance(first, second);
        assert(m1une::string::levenshtein_distance(first, second) == expected);
        assert(m1une::string::levenshtein_distance(second, first) == expected);
        for (int max_distance = 0; max_distance <= 8; max_distance++) {
            [[maybe_unused]] int bounded_expected = std::min(expected, max_distance + 1);
            assert(m1une::string::levenshtein_distance(first, second, max_distance) ==
                   bounded_expected);
            assert(m1une::string::levenshtein_distance(second, first, max_distance) ==
                   bounded_expected);
        }
    }
}

}  // namespace

int main() {
    test_edge_cases();
    test_randomized();

    std::string first, second;
    std::cin >> first >> second;
    std::cout << m1une::string::levenshtein_distance(first, second) << '\n';
}
