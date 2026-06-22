#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/ordered_set/binary_trie_monoid.hpp"
#include "../../../monoid/add.hpp"
#include "../../../monoid/mul.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <vector>

void basic_test() {
    using Product = m1une::monoid::Mul<long long>;
    using ProductTrie =
        m1une::ds::BinaryTrieMonoid<Product, std::uint32_t, 10>;

    ProductTrie product;
    product.reserve(64);
    const auto one_node = product.insert(1, 2);
    product.insert(2, 3);
    product.insert(7, 5);
    const auto seven_node = product.insert(7, 11);

    assert(product.root() == 0);
    assert(product.find(1) == one_node);
    assert(product.find(7) == seven_node);
    assert(product.find(6) == ProductTrie::null_node);
    assert(product.node(product.root()).count == 4);
    assert(product.node(product.root()).prod == 330);
    assert(product.node(seven_node).count == 2);
    assert(product.node(seven_node).prod == 55);
    assert(product.node_count() == 1 + 10 + 2 + 3);
    assert(product.size() == 4);
    assert(product.count(7) == 2);
    assert(product.prod(7) == 55);
    assert(product.kth(0) == 1);
    assert(product.kth(2) == 7);
    assert(product.min() == 1);
    assert(product.max() == 7);
    assert(product.kth_xor(0, 3) == 1);
    assert(product.kth_xor(2, 3) == 4);
    assert(product.min_xor(3) == 1);
    assert(product.max_xor(3) == 4);
    assert(product.count_xor_equal(3, 4) == 2);
    assert(product.prod_xor_less(3, 4) == 6);
    assert(product.count_xor_less(3, 4) == 2);
    assert(product.count_less_xor(3, 4) == 2);
    assert(product.count_xor_less_equal(3, 4) == 4);
    assert(product.count_xor_greater(3, 2) == 2);
    assert(product.count_xor_greater_equal(3, 2) == 3);
    assert(product.count_xor_range(3, 2, 5) == 3);
    assert(product.prod_xor_equal(3, 4) == 55);
    assert(product.prod_xor_less_equal(3, 4) == 330);
    assert(product.prod_xor_greater(3, 2) == 55);
    assert(product.prod_xor_greater_equal(3, 2) == 110);
    assert(product.prod_xor_range(3, 2, 5) == 110);
    assert(product.prod_xor_less(3, 0) == 1);
    assert(product.prod_xor_less(0, 1024) == 330);
    assert(product.prod_xor_range(3, 2, 1024) == 110);
    assert(product.order_of_key(7) == 2);
    assert(product.count_less(7) == 2);
    assert(product.count_less_equal(7) == 4);
    assert(product.count_greater(2) == 2);
    assert(product.count_greater_equal(2) == 3);
    assert(product.count_range(2, 7) == 1);
    assert(product.prod_less(7) == 6);
    assert(product.prod_less_equal(7) == 330);
    assert(product.prod_greater(2) == 55);
    assert(product.prod_greater_equal(2) == 165);
    assert(product.prod_range(2, 7) == 3);

    product.xor_all(6);
    assert(product.xor_mask() == 6);
    assert(product.find(7 ^ 6) == seven_node);
    assert(product.prod(7 ^ 6) == 55);
    assert(product.prod_xor_less(5, 4) == 6);
    assert(product.erase_all(7 ^ 6) == 2);
    assert(product.all_prod() == 6);
    product.clear();
    assert(product.empty());
    assert(product.node_count() == 1);
    assert(product.xor_mask() == 0);

    std::vector<std::pair<std::uint32_t, long long>> entries;
    entries.emplace_back(4, 2);
    entries.emplace_back(9, 3);
    ProductTrie from_range(entries.begin(), entries.end());
    assert(from_range.all_prod() == 6);
}

void randomized_test() {
    using Sum = m1une::monoid::Add<long long>;
    using SumTrie =
        m1une::ds::BinaryTrieMonoid<Sum, std::uint32_t, 10>;

    SumTrie trie;
    std::vector<std::pair<std::uint32_t, long long>> entries;
    std::uint64_t seed = 123456789;

    for (int query = 0; query < 10000; ++query) {
        seed = seed * 6364136223846793005ULL +
               1442695040888963407ULL;
        const std::uint32_t key = std::uint32_t(seed >> 32) & 1023U;
        const std::uint32_t value = std::uint32_t(seed) & 1023U;
        const int type = int(seed % 6);

        if (type <= 1) {
            trie.insert(key, value);
            entries.emplace_back(key, value);
        } else if (type == 2) {
            trie.xor_all(key);
            for (auto& entry : entries) entry.first ^= key;
        } else if (type == 3) {
            int expected_erased = 0;
            for (const auto& entry : entries) {
                if (entry.first == key) ++expected_erased;
            }
            assert(trie.erase_all(key) == expected_erased);
            entries.erase(
                std::remove_if(
                    entries.begin(), entries.end(),
                    [&](const auto& entry) {
                        return entry.first == key;
                    }),
                entries.end());
        } else if (type == 4) {
            int expected_count = 0;
            long long expected_prod = 0;
            for (const auto& entry : entries) {
                if (entry.first == key) {
                    ++expected_count;
                    expected_prod += entry.second;
                }
            }
            assert(trie.count(key) == expected_count);
            assert(trie.prod(key) == expected_prod);
        } else {
            const std::uint32_t upper = std::uint32_t(seed >> 20) & 1023U;
            const std::uint32_t target = std::uint32_t(seed >> 12) & 1023U;
            const std::uint32_t other = std::uint32_t(seed >> 4) & 1023U;
            const std::uint32_t lower = std::min(upper, other);
            const std::uint32_t range_upper =
                std::max(upper, other) + 1;
            int expected_count = 0;
            long long expected_prod = 0;
            int expected_equal_count = 0;
            long long expected_equal_prod = 0;
            int expected_less_equal_count = 0;
            long long expected_less_equal_prod = 0;
            int expected_greater_count = 0;
            long long expected_greater_prod = 0;
            int expected_greater_equal_count = 0;
            long long expected_greater_equal_prod = 0;
            int expected_range_count = 0;
            long long expected_range_prod = 0;
            std::vector<std::uint32_t> xor_values;
            xor_values.reserve(entries.size());
            for (const auto& entry : entries) {
                const std::uint32_t xor_value = entry.first ^ key;
                xor_values.push_back(xor_value);
                if (xor_value == target) {
                    ++expected_equal_count;
                    expected_equal_prod += entry.second;
                }
                if (xor_value < upper) {
                    ++expected_count;
                    expected_prod += entry.second;
                }
                if (xor_value <= upper) {
                    ++expected_less_equal_count;
                    expected_less_equal_prod += entry.second;
                }
                if (xor_value > upper) {
                    ++expected_greater_count;
                    expected_greater_prod += entry.second;
                }
                if (xor_value >= upper) {
                    ++expected_greater_equal_count;
                    expected_greater_equal_prod += entry.second;
                }
                if (lower <= xor_value && xor_value < range_upper) {
                    ++expected_range_count;
                    expected_range_prod += entry.second;
                }
            }
            std::sort(xor_values.begin(), xor_values.end());

            assert(trie.count_xor_equal(key, target) ==
                   expected_equal_count);
            assert(trie.prod_xor_equal(key, target) ==
                   expected_equal_prod);
            assert(trie.count_xor_less(key, upper) == expected_count);
            assert(trie.count_less_xor(key, upper) == expected_count);
            assert(trie.prod_xor_less(key, upper) == expected_prod);
            assert(trie.count_xor_less_equal(key, upper) ==
                   expected_less_equal_count);
            assert(trie.prod_xor_less_equal(key, upper) ==
                   expected_less_equal_prod);
            assert(trie.count_xor_greater(key, upper) ==
                   expected_greater_count);
            assert(trie.prod_xor_greater(key, upper) ==
                   expected_greater_prod);
            assert(trie.count_xor_greater_equal(key, upper) ==
                   expected_greater_equal_count);
            assert(trie.prod_xor_greater_equal(key, upper) ==
                   expected_greater_equal_prod);
            assert(trie.count_xor_range(key, lower, range_upper) ==
                   expected_range_count);
            assert(trie.prod_xor_range(key, lower, range_upper) ==
                   expected_range_prod);

            if (!xor_values.empty()) {
                const int k = int(seed % xor_values.size());
                assert(trie.kth_xor(k, key) == xor_values[k]);
                assert(trie.min_xor(key) == xor_values.front());
                assert(trie.max_xor(key) == xor_values.back());
            }
        }

        assert(trie.size() == int(entries.size()));
        long long expected_all_prod = 0;
        for (const auto& entry : entries) {
            expected_all_prod += entry.second;
        }
        assert(trie.all_prod() == expected_all_prod);
    }
}

int main() {
    basic_test();
    randomized_test();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
