#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include "../../../ds/range_query/sqrt_tree.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "../../../monoid/add.hpp"

namespace {

struct Concat {
    using value_type = std::string;

    static value_type id() {
        return "";
    }

    static value_type op(const value_type& first, const value_type& second) {
        return first + second;
    }
};

void test_fixed() {
    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> empty;
    assert(empty.empty());
    assert(empty.prod(0, 0) == 0);
    assert(empty.all_prod() == 0);

    std::vector<long long> values = {1, 2, 3, 4, 5};
    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> sum(values);
    assert(sum.size() == 5);
    assert(sum.prod(0, 5) == 15);
    assert(sum.prod(1, 4) == 9);
    assert(sum.prod(3, 3) == 0);

    std::vector<std::string> letters = {"a", "b", "c", "d", "e", "f"};
    m1une::ds::SqrtTree<Concat> text(letters);
    assert(text.prod(0, 6) == "abcdef");
    assert(text.prod(1, 5) == "bcde");
    assert(text.prod(2, 3) == "c");
}

void test_randomized() {
    std::uint64_t state = 601;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2000; ++trial) {
        int size = int(random() % 250);
        std::vector<long long> values(size);
        for (long long& value : values) {
            value = static_cast<long long>(random() % 101) - 50;
        }
        m1une::ds::SqrtTree<m1une::monoid::Add<long long>> tree(values);

        for (int query = 0; query < 300; ++query) {
            int left = int(random() % (size + 1));
            int right = int(random() % (size + 1));
            if (right < left) std::swap(left, right);

            [[maybe_unused]] long long expected = 0;
            for (int index = left; index < right; ++index) {
                expected += values[index];
            }
            assert(tree.prod(left, right) == expected);
        }
    }

    for (int size = 0; size <= 80; ++size) {
        std::vector<std::string> values(size);
        for (int index = 0; index < size; ++index) {
            values[index] = char('a' + index % 5);
        }
        m1une::ds::SqrtTree<Concat> tree(values);
        for (int left = 0; left <= size; ++left) {
            std::string expected;
            for (int right = left; right <= size; ++right) {
                assert(tree.prod(left, right) == expected);
                if (right < size) expected += values[right];
            }
        }
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    int n, q;
    std::cin >> n >> q;
    std::vector<long long> values(n);
    for (long long& value : values) std::cin >> value;

    m1une::ds::SqrtTree<m1une::monoid::Add<long long>> tree(values);
    while (q--) {
        int left, right;
        std::cin >> left >> right;
        std::cout << tree.prod(left, right) << '\n';
    }
}
