#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "utilities/bisect.hpp"
#include "utilities/chmin_chmax.hpp"
#include "utilities/compressor.hpp"
#include "utilities/run_length_encoding.hpp"
#include "utilities/y_combinator.hpp"

void test_chmin_chmax() {
    int x = 10;
    assert(m1une::utilities::chmin(x, 3));
    assert(x == 3);
    assert(!m1une::utilities::chmin(x, 7));
    assert(m1une::utilities::chmax(x, 7));
    assert(x == 7);
    assert(!m1une::utilities::chmax(x, 4));
}

void test_compressor() {
    vector<long long> xs = {100, -5, 100, 7};
    m1une::utilities::Compressor<long long> comp(xs);

    assert(comp.size() == 3);
    assert(comp[0] == -5);
    assert(comp[1] == 7);
    assert(comp[2] == 100);
    assert(comp.get(100) == 2);
    assert(comp.lower_bound(8) == 2);
    assert(comp.upper_bound(7) == 2);
    assert(comp.contains(-5));
    assert(!comp.contains(6));

    m1une::utilities::Compressor<int> incremental;
    incremental.add(4);
    incremental.add(1);
    incremental.add(4);
    incremental.build();
    assert(incremental.size() == 2);
    assert(incremental.get(1) == 0);
    assert(incremental.get(4) == 1);

    bool rejected = false;
    try {
        (void)comp.get(6);
    } catch (const out_of_range&) {
        rejected = true;
    }
    assert(rejected);
}

void test_y_combinator() {
    auto fact = m1une::utilities::y_combinator([](auto self, int n) -> long long {
        if (n == 0) return 1;
        return n * self(n - 1);
    });
    assert(fact(10) == 3628800);
}

void test_bisect() {
    long long n = 100;
    long long first = m1une::utilities::first_true(0, n + 1, [&](long long x) {
        return x * x >= n;
    });
    assert(first == 10);

    long long last = m1une::utilities::last_true(n + 1, 0, [&](long long x) {
        return x * x >= n;
    });
    assert(last == 10);

    double root = m1une::utilities::real_first_true(0.0, 2.0, [](double x) {
        return x * x >= 2.0;
    });
    assert(abs(root * root - 2.0) < 1e-12);
}

void test_run_length_encoding() {
    string s = "aaabbc";
    auto runs = m1une::utilities::run_length_encoding(s);
    assert(runs.size() == 3);
    assert(runs[0] == make_pair('a', 3LL));
    assert(runs[1] == make_pair('b', 2LL));
    assert(runs[2] == make_pair('c', 1LL));

    vector<int> v = {1, 1, 2, 2, 2, 1};
    auto vector_runs = m1une::utilities::run_length_encoding(v);
    assert(vector_runs[0] == make_pair(1, 2LL));
    assert(vector_runs[1] == make_pair(2, 3LL));
    assert(vector_runs[2] == make_pair(1, 1LL));
}

int main() {
    test_chmin_chmax();
    test_compressor();
    test_y_combinator();
    test_bisect();
    test_run_length_encoding();

    long long a, b;
    cin >> a >> b;
    cout << a + b << '\n';
}
