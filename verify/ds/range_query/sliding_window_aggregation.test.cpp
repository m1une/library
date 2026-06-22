#define PROBLEM "https://judge.yosupo.jp/problem/queue_operate_all_composite"

#include "../../../ds/range_query/sliding_window_aggregation.hpp"

#include <cassert>
#include <cstdint>
#include <deque>
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
    m1une::ds::Swag<Concat> queue;
    assert(queue.empty());
    assert(queue.prod().empty());

    queue.reserve(10);
    queue.push("a");
    queue.push_back("b");
    queue.push("c");
    assert(queue.size() == 3);
    assert(queue.front() == "a");
    assert(queue.back() == "c");
    assert(queue.prod() == "abc");

    queue.pop();
    assert(queue.front() == "b");
    assert(queue.prod() == "bc");
    queue.push("d");
    assert(queue.all_prod() == "bcd");
    queue.pop_front();
    assert(queue.prod() == "cd");

    queue.clear();
    assert(queue.empty());
    assert(queue.all_prod().empty());

    std::vector<std::string> values = {"x", "y", "z"};
    m1une::ds::SlidingWindowAggregation<Concat> built(values);
    assert(built.prod() == "xyz");
}

void test_randomized() {
    std::uint64_t state = 809;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    m1une::ds::Swag<Concat> queue;
    std::deque<std::string> expected;
    for (int operation = 0; operation < 50000; ++operation) {
        if (expected.empty() || random() % 3 != 0) {
            std::string value(1, char('a' + random() % 5));
            queue.push(value);
            expected.push_back(value);
        } else {
            queue.pop();
            expected.pop_front();
        }

        assert(queue.size() == expected.size());
        assert(queue.empty() == expected.empty());
        std::string product;
        for (const std::string& value : expected) product += value;
        assert(queue.prod() == product);
        if (!expected.empty()) {
            assert(queue.front() == expected.front());
            assert(queue.back() == expected.back());
        }
    }
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();

    int query_count;
    std::cin >> query_count;
    m1une::ds::Swag<Affine> queue;
    while (query_count--) {
        int type;
        std::cin >> type;
        if (type == 0) {
            Affine::value_type function;
            std::cin >> function.a >> function.b;
            queue.push(function);
        } else if (type == 1) {
            queue.pop();
        } else {
            long long x;
            std::cin >> x;
            auto function = queue.prod();
            std::cout << (function.a * x + function.b) % mod << '\n';
        }
    }
}
