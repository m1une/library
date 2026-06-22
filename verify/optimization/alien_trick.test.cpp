#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

#include "../../optimization/alien_trick.hpp"

namespace {

void test_minimize() {
    for (int test = 0; test < 200; test++) {
        int n = 1 + test % 30;
        std::vector<long long> exact(n + 1);
        exact[0] = (test * 17) % 31 - 15;
        long long slope = -100 - test;
        for (int count = 1; count <= n; count++) {
            slope += 1 + (test * 13 + count * 7) % 8;
            exact[count] = exact[count - 1] + slope;
        }

        auto oracle = [&exact](long long penalty) {
            std::pair<long long, int> best;
            best.first = std::numeric_limits<long long>::max();
            best.second = -1;
            for (int count = 0; count < int(exact.size()); count++) {
                long long value = exact[count] + penalty * count;
                if (value < best.first
                    || (value == best.first && best.second < count)) {
                    best.first = value;
                    best.second = count;
                }
            }
            return best;
        };

        for (int target = 0; target <= n; target++) {
            long long answer = m1une::optimization::alien_trick_minimize(
                -1000LL,
                1000LL,
                target,
                oracle
            );
            assert(answer == exact[target]);
        }
    }
}

void test_maximize() {
    for (int test = 0; test < 200; test++) {
        int n = 1 + test % 30;
        std::vector<long long> exact(n + 1);
        exact[0] = (test * 19) % 37 - 18;
        long long slope = 100 + test;
        for (int count = 1; count <= n; count++) {
            slope -= 1 + (test * 11 + count * 5) % 8;
            exact[count] = exact[count - 1] + slope;
        }

        auto oracle = [&exact](long long penalty) {
            std::pair<long long, int> best;
            best.first = std::numeric_limits<long long>::lowest();
            best.second = -1;
            for (int count = 0; count < int(exact.size()); count++) {
                long long value = exact[count] - penalty * count;
                if (best.first < value
                    || (best.first == value && best.second < count)) {
                    best.first = value;
                    best.second = count;
                }
            }
            return best;
        };

        for (int target = 0; target <= n; target++) {
            long long answer = m1une::optimization::alien_trick_maximize(
                -1000LL,
                1000LL,
                target,
                oracle
            );
            assert(answer == exact[target]);
        }
    }
}

void test_tie_breaking() {
    std::vector<long long> exact = {12, 8, 4, 0};
    auto oracle = [&exact](int penalty) {
        std::pair<long long, int> best;
        best.first = std::numeric_limits<long long>::max();
        best.second = -1;
        for (int count = 0; count < int(exact.size()); count++) {
            long long value = exact[count] + 1LL * penalty * count;
            if (value < best.first
                || (value == best.first && best.second < count)) {
                best.first = value;
                best.second = count;
            }
        }
        return best;
    };

    for (int target = 0; target < int(exact.size()); target++) {
        assert(m1une::optimization::alien_trick_minimize(
                   -20,
                   20,
                   target,
                   oracle
               )
               == exact[target]);
    }
}

}  // namespace

int main() {
    test_minimize();
    test_maximize();
    test_tie_breaking();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
