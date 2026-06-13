#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2858"

#include <bits/stdc++.h>
using namespace std;

#include "utilities/shifted_array.hpp"

constexpr long long MAX = 100000;

void test_shifted_array_edges() {
    m1une::utilities::ShiftedArray<int> stepped(-2, 4, 0, 2);
    stepped[-2] = 1;
    stepped[0] = 2;
    stepped[4] = 3;
    assert(stepped.index(2) == 2);
    assert(stepped[-2] == 1);
    assert(stepped[0] == 2);
    assert(stepped[4] == 3);

    bool rejected = false;
    try {
        (void)stepped[1];
    } catch (const out_of_range&) {
        rejected = true;
    }
    assert(rejected);

    rejected = false;
    try {
        m1une::utilities::ShiftedArray<int> invalid_step(0, 10, 0, 0);
    } catch (const invalid_argument&) {
        rejected = true;
    }
    assert(rejected);
}

long long solve(long long l, long long r) {
    vector<char> is_prime(MAX, 1);
    is_prime[0] = is_prime[1] = 0;
    m1une::utilities::ShiftedArray<vector<long long>> prime_factors(l, r);
    for (long long p = 2; p * p <= r; ++p) {
        if (!is_prime[p]) continue;
        for (long long x = 2 * p; x < MAX; x += p) {
            is_prime[x] = 0;
        }
        for (long long x = (l + p - 1) / p * p; x <= r; x += p) {
            prime_factors[x].emplace_back(p);
        }
    }
    long long res = 0;
    for (long long x = l; x <= r; ++x) {
        long long factor_count = 0;
        long long y = x;
        for (long long p : prime_factors[x]) {
            while (y % p == 0) {
                y /= p;
                ++factor_count;
            }
        }
        if (y > 1) {
            ++factor_count;
        }
        if (is_prime[factor_count]) {
            ++res;
        }
    }
    return res;
}

int main() {
    test_shifted_array_edges();

    long long l, r;
    cin >> l >> r;
    cout << solve(l, r) << endl;
}
