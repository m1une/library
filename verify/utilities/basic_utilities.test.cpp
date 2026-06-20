#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "../../utilities/bigint.hpp"
#include "../../utilities/int128.hpp"
#include "../../utilities/random.hpp"
#include "../../utilities/timer.hpp"

void test_bigint() {
    using m1une::utilities::BigInt;

    const long long min_long_long = std::numeric_limits<long long>::min();
    BigInt minimum(min_long_long);
    assert(minimum.to_string() == std::to_string(min_long_long));

    BigInt scaled = 1;
    scaled *= std::numeric_limits<int>::min();
    assert(scaled.to_string() == std::to_string(std::numeric_limits<int>::min()));

    BigInt positive = -1;
    positive *= std::numeric_limits<int>::min();
    assert(positive.to_string() == "2147483648");

    BigInt large("12345678901234567890");
    assert(large.to_string() == "12345678901234567890");

    bool rejected_division_by_zero = false;
    try {
        (void)(large / BigInt(0));
    } catch (const std::domain_error&) {
        rejected_division_by_zero = true;
    }
    assert(rejected_division_by_zero);
}

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

    std::stringstream ss;
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

    std::vector<int> v = {1, 2, 3, 4, 5};
    rng1.shuffle(v);
    std::sort(v.begin(), v.end());
    assert((v == std::vector<int>{1, 2, 3, 4, 5}));
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
    test_bigint();
    test_int128();
    test_random();
    test_timer();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
