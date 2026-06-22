#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "../../../ds/range_query/sqrt_decomposition.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

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

constexpr long long mod = 998244353;

struct Affine {
    struct value_type {
        long long a;
        long long b;
    };

    static value_type id() {
        return value_type{1, 0};
    }

    static value_type op(const value_type& first, const value_type& second) {
        return value_type{
            second.a * first.a % mod,
            (second.a * first.b + second.b) % mod,
        };
    }
};

void test_fixed() {
    m1une::ds::SqrtDecomposition<Concat> empty;
    assert(empty.empty());
    assert(empty.prod(0, 0).empty());

    std::vector<std::string> values = {"a", "b", "c", "d", "e"};
    m1une::ds::SqrtDecomposition<Concat> blocks(values);
    assert(blocks.prod(0, 5) == "abcde");
    assert(blocks.prod(1, 4) == "bcd");
    blocks.set(2, "x");
    assert(blocks.prod(0, 5) == "abxde");
    assert(blocks.all_prod() == "abxde");

    for (int block = 0; block < blocks.block_count(); ++block) {
        auto range = blocks.block_range(block);
        std::string expected;
        for (int index = range.first; index < range.second; ++index) {
            expected += blocks[index];
            assert(blocks.block_of(index) == block);
        }
        assert(blocks.block_products()[block] == expected);
    }
}

void test_randomized() {
    std::uint64_t state = 701;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 2000; ++trial) {
        int size = int(random() % 180);
        std::vector<std::string> values(size);
        for (std::string& value : values) {
            value = char('a' + random() % 5);
        }
        m1une::ds::SqrtDecomposition<Concat> blocks(values);

        for (int operation = 0; operation < 300; ++operation) {
            if (size != 0 && random() % 3 == 0) {
                int index = int(random() % size);
                std::string value(1, char('a' + random() % 5));
                values[index] = value;
                blocks.set(index, value);
            } else {
                int left = int(random() % (size + 1));
                int right = int(random() % (size + 1));
                if (right < left) std::swap(left, right);
                std::string expected;
                for (int index = left; index < right; ++index) {
                    expected += values[index];
                }
                assert(blocks.prod(left, right) == expected);
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
    std::vector<Affine::value_type> values(n);
    for (auto& value : values) std::cin >> value.a >> value.b;
    m1une::ds::SqrtDecomposition<Affine> blocks(values);

    while (q--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            int index;
            Affine::value_type value;
            std::cin >> index >> value.a >> value.b;
            blocks.set(index, value);
        } else {
            int left, right;
            long long x;
            std::cin >> left >> right >> x;
            auto function = blocks.prod(left, right);
            std::cout << (function.a * x + function.b) % mod << '\n';
        }
    }
}
