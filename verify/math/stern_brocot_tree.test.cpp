#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/stern_brocot_tree.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

namespace {

using Fraction = m1une::math::Rational<long long>;
using Direction = m1une::math::SternBrocotDirection;
using Path = m1une::math::SternBrocotPath;

std::vector<Direction> expand(const Path& path) {
    std::vector<Direction> result;
    for (const auto& run : path.runs) {
        for (uint64_t i = 0; i < run.count; i++) result.push_back(run.direction);
    }
    return result;
}

void test_features() {
    Path root = m1une::math::stern_brocot_path(1LL, 1LL);
    assert(root.empty());
    assert(root.depth() == 0);
    assert(m1une::math::stern_brocot_decode<long long>(root) == Fraction(1, 1));

    Path path = m1une::math::stern_brocot_path(5LL, 3LL);
    assert(path.depth() == 3);
    assert(path.runs.size() == 3);
    m1une::math::SternBrocotRun right_once{Direction::Right, 1};
    m1une::math::SternBrocotRun left_once{Direction::Left, 1};
    assert(path.runs[0] == right_once);
    assert(path.runs[1] == left_once);
    assert(path.runs[2] == right_once);
    assert(m1une::math::stern_brocot_decode<long long>(path) == Fraction(5, 3));
    assert(m1une::math::stern_brocot_parent(5LL, 3LL) == Fraction(3, 2));
    assert(m1une::math::stern_brocot_ancestor(5LL, 3LL, 2) == Fraction(2, 1));
    assert(m1une::math::stern_brocot_ancestor(5LL, 3LL, 3) == Fraction(1, 1));

    assert(
        m1une::math::stern_brocot_move(1LL, 1LL, Direction::Left, 4)
        == Fraction(1, 5)
    );
    assert(
        m1une::math::stern_brocot_move(1LL, 1LL, Direction::Right, 4)
        == Fraction(5, 1)
    );
    assert(m1une::math::stern_brocot_lca(5LL, 3LL, 7LL, 4LL) == Fraction(5, 3));
    assert(m1une::math::stern_brocot_lca(2LL, 5LL, 5LL, 2LL) == Fraction(1, 1));

    auto bounds = m1une::math::stern_brocot_bounds<long long>(path);
    std::pair<long long, long long> expected_left(3, 2);
    std::pair<long long, long long> expected_right(2, 1);
    assert(bounds.left == expected_left);
    assert(bounds.right == expected_right);
}

void test_exhaustive() {
    std::vector<Fraction> fractions;
    std::vector<Path> paths;
    for (long long numerator = 1; numerator <= 100; numerator++) {
        for (long long denominator = 1; denominator <= 100; denominator++) {
            if (std::gcd(numerator, denominator) != 1) continue;
            Path path = m1une::math::stern_brocot_path(numerator, denominator);
            Fraction decoded = m1une::math::stern_brocot_decode<long long>(path);
            assert(decoded == Fraction(numerator, denominator));
            assert(path.depth() == m1une::math::stern_brocot_depth(numerator, denominator));

            auto bounds = m1une::math::stern_brocot_bounds<long long>(path);
            auto [left_numerator, left_denominator] = bounds.left;
            auto [right_numerator, right_denominator] = bounds.right;
            assert(
                __int128(numerator) * left_denominator
                - __int128(left_numerator) * denominator
                == 1
            );
            assert(
                __int128(right_numerator) * denominator
                - __int128(numerator) * right_denominator
                == 1
            );

            auto left_child = m1une::math::stern_brocot_move(
                numerator,
                denominator,
                Direction::Left
            );
            auto right_child = m1une::math::stern_brocot_move(
                numerator,
                denominator,
                Direction::Right
            );
            assert(
                left_child
                == Fraction(
                    numerator + left_numerator,
                    denominator + left_denominator
                )
            );
            assert(
                right_child
                == Fraction(
                    numerator + right_numerator,
                    denominator + right_denominator
                )
            );
            assert(
                m1une::math::stern_brocot_parent(
                    left_child.numerator(),
                    left_child.denominator()
                )
                == Fraction(numerator, denominator)
            );
            assert(
                m1une::math::stern_brocot_parent(
                    right_child.numerator(),
                    right_child.denominator()
                )
                == Fraction(numerator, denominator)
            );

            fractions.emplace_back(numerator, denominator);
            paths.push_back(path);
        }
    }

    for (int first = 0; first < int(paths.size()); first += 17) {
        for (int second = 0; second < int(paths.size()); second += 23) {
            std::vector<Direction> first_expanded = expand(paths[first]);
            std::vector<Direction> second_expanded = expand(paths[second]);
            int common = 0;
            while (
                common < int(first_expanded.size()) &&
                common < int(second_expanded.size()) &&
                first_expanded[common] == second_expanded[common]
            ) {
                common++;
            }
            Path expected;
            for (int i = 0; i < common; i++) expected.push(first_expanded[i]);
            Path actual = m1une::math::stern_brocot_lca_path(paths[first], paths[second]);
            assert(actual == expected);
            assert(
                m1une::math::stern_brocot_lca(
                    fractions[first].numerator(),
                    fractions[first].denominator(),
                    fractions[second].numerator(),
                    fractions[second].denominator()
                )
                == m1une::math::stern_brocot_decode<long long>(expected)
            );
        }
    }
}

}  // namespace

int main() {
    test_features();
    test_exhaustive();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
