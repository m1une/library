#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/integer_arithmetic.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>

namespace {

template <class T>
void test_square_roots() {
    using U = std::make_unsigned_t<T>;
    U limit = std::min<U>(std::numeric_limits<T>::max(), U(100000));
    for (U value = 0;; ++value) {
        T input = static_cast<T>(value);
        [[maybe_unused]] T floor = m1une::math::isqrt(input);
        [[maybe_unused]] T ceiling = m1une::math::ceil_sqrt(input);
        assert(floor <= input / (floor == 0 ? 1 : floor));
        assert(floor == 0 || floor + 1 > input / (floor + 1));
        assert(ceiling == floor || ceiling == floor + 1);
        assert(
            ceiling == floor
            ? floor * floor == input
            : floor * floor < input
        );
        if (value == limit) break;
    }
}

void test_boundaries() {
    constexpr std::uint64_t maximum =
        std::numeric_limits<std::uint64_t>::max();
    constexpr std::uint64_t root = 4294967295ULL;
    static_assert(m1une::math::isqrt(maximum) == root);
    static_assert(m1une::math::ceil_sqrt(maximum) == root + 1);
    static_assert(m1une::math::isqrt(root * root) == root);

    constexpr long long signed_maximum =
        std::numeric_limits<long long>::max();
    static_assert(m1une::math::isqrt(signed_maximum) == 3037000499LL);
    static_assert(m1une::math::ceil_sqrt(signed_maximum) == 3037000500LL);
}

void test_powers() {
    using m1une::math::checked_ipow;
    using m1une::math::ipow;

    static_assert(ipow(0LL, 0U) == 1);
    static_assert(ipow(2LL, 10U) == 1024);
    static_assert(ipow(-3LL, 3U) == -27);
    static_assert(ipow(-3LL, 4U) == 81);
    static_assert(
        ipow(-2LL, 63U) == std::numeric_limits<long long>::min()
    );
    static_assert(!checked_ipow(2LL, 63U).has_value());
    static_assert(!checked_ipow(-2LL, 64U).has_value());
    static_assert(!checked_ipow(10ULL, 20U).has_value());
    static_assert(checked_ipow(10ULL, 19U) == std::optional(10000000000000000000ULL));
    static_assert(
        checked_ipow(std::numeric_limits<long long>::min(), 1U)
        == std::optional(std::numeric_limits<long long>::min())
    );
    static_assert(
        !checked_ipow(std::numeric_limits<long long>::min(), 2U).has_value()
    );

    for (long long base = -20; base <= 20; ++base) {
        [[maybe_unused]] long long expected = 1;
        for (unsigned exponent = 0; exponent <= 8; ++exponent) {
            assert(ipow(base, exponent) == expected);
            expected *= base;
        }
    }
}

}  // namespace

int main() {
    test_square_roots<signed char>();
    test_square_roots<unsigned char>();
    test_square_roots<short>();
    test_square_roots<unsigned short>();
    test_square_roots<int>();
    test_square_roots<unsigned int>();
    test_square_roots<long long>();
    test_square_roots<unsigned long long>();
    test_boundaries();
    test_powers();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
