#define PROBLEM "https://judge.yosupo.jp/problem/set_xor_min"

#include "ds/ordered_set/binary_trie.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>
#include <vector>

void unit_test() {
    using Trie = m1une::ds::BinaryTrie<std::uint32_t, 10>;

    Trie basic;
    basic.insert(5, 3);
    basic.insert(9);
    assert(basic.count(5) == 3);
    assert(basic.kth_xor(0, 7) == (5U ^ 7U));
    assert(basic.erase_one(5));
    assert(basic.erase_all(5) == 2);
    basic.xor_all(6);
    assert(basic.contains(9U ^ 6U));
    basic.clear();
    basic.insert(1023);
    assert(basic.count_less_equal(1023) == 1);
    assert(basic.count_less_xor(0, 1024) == 1);

    Trie trie;
    std::multiset<std::uint32_t> expected;
    std::uint64_t seed = 123456789;

    for (int query = 0; query < 10000; ++query) {
        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
        const std::uint32_t value = std::uint32_t(seed >> 32) & 1023U;
        const int type = int(seed % 7);

        if (type <= 1) {
            trie.insert(value);
            expected.insert(value);
        } else if (type == 2) {
            const bool erased = trie.erase_one(value);
            auto it = expected.find(value);
            assert(erased == (it != expected.end()));
            if (it != expected.end()) expected.erase(it);
        } else if (type == 3) {
            const int erased = trie.erase_all(value);
            assert(erased == int(expected.count(value)));
            expected.erase(value);
        } else if (type == 4) {
            trie.xor_all(value);
            std::multiset<std::uint32_t> transformed;
            for (std::uint32_t element : expected) {
                transformed.insert(element ^ value);
            }
            expected = std::move(transformed);
        } else if (type == 5) {
            assert(trie.count(value) == int(expected.count(value)));
            assert(trie.count_less(value) ==
                   int(std::distance(expected.begin(), expected.lower_bound(value))));
            assert(trie.count_less_equal(value) ==
                   int(std::distance(expected.begin(), expected.upper_bound(value))));
        } else if (!expected.empty()) {
            std::vector<std::uint32_t> xor_values;
            xor_values.reserve(expected.size());
            for (std::uint32_t element : expected) {
                xor_values.push_back(element ^ value);
            }
            std::sort(xor_values.begin(), xor_values.end());
            assert(trie.min_xor(value) == xor_values.front());
            assert(trie.max_xor(value) == xor_values.back());
            assert(trie.count_less_xor(value, 512) ==
                   int(std::lower_bound(xor_values.begin(), xor_values.end(), 512) -
                       xor_values.begin()));
            assert(trie.count_xor_less(value, 512) ==
                   int(std::lower_bound(xor_values.begin(), xor_values.end(), 512) -
                       xor_values.begin()));
            assert(trie.count_xor_less_equal(value, 512) ==
                   int(std::upper_bound(xor_values.begin(), xor_values.end(), 512) -
                       xor_values.begin()));
            assert(trie.count_xor_greater(value, 512) ==
                   int(xor_values.end() -
                       std::upper_bound(xor_values.begin(), xor_values.end(), 512)));
            assert(trie.count_xor_greater_equal(value, 512) ==
                   int(xor_values.end() -
                       std::lower_bound(xor_values.begin(), xor_values.end(), 512)));
            assert(trie.count_xor_range(value, 200, 800) ==
                   int(std::lower_bound(xor_values.begin(), xor_values.end(), 800) -
                       std::lower_bound(xor_values.begin(), xor_values.end(), 200)));
        }

        assert(trie.size() == int(expected.size()));
        assert(trie.empty() == expected.empty());
        if (!expected.empty()) {
            assert(trie.min() == *expected.begin());
            assert(trie.max() == *expected.rbegin());
            const int k = int(seed % expected.size());
            auto it = expected.begin();
            std::advance(it, k);
            assert(trie.kth(k) == *it);
        }
    }

    assert(trie.to_vector() ==
           std::vector<std::uint32_t>(expected.begin(), expected.end()));
    trie.clear();
    assert(trie.empty());
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    unit_test();

    int query_count;
    std::cin >> query_count;

    m1une::ds::BinaryTrie<std::uint32_t, 30> trie;
    while (query_count--) {
        int type;
        std::uint32_t value;
        std::cin >> type >> value;

        if (type == 0) {
            if (!trie.contains(value)) trie.insert(value);
        } else if (type == 1) {
            trie.erase(value);
        } else {
            std::cout << trie.min_xor(value) << '\n';
        }
    }
}
