#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <bits/stdc++.h>
using namespace std;

#include "utilities/int128.hpp"
#include "utilities/random.hpp"
#include "utilities/timer.hpp"

void test_int128() {
    using m1une::utilities::i128;
    using m1une::utilities::parse_int128;
    using m1une::utilities::parse_uint128;
    using m1une::utilities::to_string;
    using m1une::utilities::u128;

    i128 x = parse_int128("-170141183460469231731687303715884105");
    assert(to_string(x) == "-170141183460469231731687303715884105");

    u128 y = parse_uint128("340282366920938463463374607431768211");
    assert(to_string(y) == "340282366920938463463374607431768211");

    stringstream ss;
    ss << x << " " << y;
    assert(ss.str() == "-170141183460469231731687303715884105 340282366920938463463374607431768211");

    i128 read_x;
    u128 read_y;
    ss >> read_x >> read_y;
    assert(read_x == x);
    assert(read_y == y);
}

void test_random() {
    m1une::utilities::Random rng1(42), rng2(42);
    for (int i = 0; i < 10; ++i) {
        assert(rng1() == rng2());
    }

    for (int i = 0; i < 100; ++i) {
        long long x = rng1.uniform(-5, 5);
        assert(-5 <= x && x <= 5);
        double y = rng1.real(-1.0, 2.0);
        assert(-1.0 <= y && y < 2.0);
    }

    vector<int> v = {1, 2, 3, 4, 5};
    rng1.shuffle(v);
    sort(v.begin(), v.end());
    assert((v == vector<int>{1, 2, 3, 4, 5}));
    int picked = rng1.choice(v);
    assert(1 <= picked && picked <= 5);
}

void test_timer() {
    m1une::utilities::Timer timer(0.0);
    assert(timer.elapsed() >= 0.0);
    assert(timer.elapsed_ms() >= 0);
    assert(timer.expired());
    timer.set_limit(1000000.0);
    timer.reset();
    assert(!timer.expired());
}

int main() {
    test_int128();
    test_random();
    test_timer();

    long long a, b;
    cin >> a >> b;
    cout << a + b << '\n';
}
