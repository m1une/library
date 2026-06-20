#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <iostream>
#include <vector>

#include "../../sequence/inversion_count.hpp"
#include "../../sequence/lis.hpp"

struct LessOnly {
    int value;

    explicit LessOnly(int value) : value(value) {}

    friend bool operator<(const LessOnly& lhs, const LessOnly& rhs) {
        return lhs.value < rhs.value;
    }
};

template <typename T>
void assert_subsequence(
    const std::vector<T>& values,
    const std::vector<int>& indices,
    bool strict
) {
    for (int i = 0; i < int(indices.size()); ++i) {
        assert(0 <= indices[i] && indices[i] < int(values.size()));
        if (i == 0) continue;
        assert(indices[i - 1] < indices[i]);
        if (strict) {
            assert(values[indices[i - 1]] < values[indices[i]]);
        } else {
            assert(!(values[indices[i]] < values[indices[i - 1]]));
        }
    }
}

void test_lis() {
    const std::vector<int> values = {3, 1, 2, 2, 4};

    const auto strict = m1une::sequence::lis(values);
    assert(strict.size() == 3);
    assert_subsequence(values, strict, true);

    const auto non_decreasing = m1une::sequence::lis(values, false);
    assert(non_decreasing.size() == 4);
    assert_subsequence(values, non_decreasing, false);

    assert(m1une::sequence::lis(std::vector<int>()).empty());
}

void test_inversion_count() {
    assert(m1une::sequence::inversion_count(std::vector<int>{2, 4, 1, 3, 5}) == 3);
    assert(m1une::sequence::inversion_count(std::vector<int>{1, 1, 1}) == 0);
    assert(m1une::sequence::inversion_count(std::vector<int>{3, 2, 1}) == 3);

    std::vector<LessOnly> values = {LessOnly(2), LessOnly(1), LessOnly(1)};
    assert(m1une::sequence::inversion_count(values) == 2);
}

int main() {
    test_lis();
    test_inversion_count();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
