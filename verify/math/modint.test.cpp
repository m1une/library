#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <limits>
#include <random>
#include <type_traits>

#include "../../math/modint.hpp"

using mint = m1une::math::modint998244353;

static_assert(std::is_constructible_v<mint, signed char>);
static_assert(std::is_constructible_v<mint, unsigned char>);
static_assert(std::is_constructible_v<mint, short>);
static_assert(std::is_constructible_v<mint, unsigned short>);
static_assert(std::is_constructible_v<mint, int>);
static_assert(std::is_constructible_v<mint, unsigned int>);
static_assert(std::is_constructible_v<mint, long>);
static_assert(std::is_constructible_v<mint, unsigned long>);
static_assert(std::is_constructible_v<mint, long long>);
static_assert(std::is_constructible_v<mint, unsigned long long>);

constexpr bool test_constexpr_construction() {
    constexpr std::uint64_t mod = mint::mod();
    constexpr long long signed_value = std::numeric_limits<long long>::min();
    constexpr unsigned long long unsigned_value =
        std::numeric_limits<unsigned long long>::max();

    mint from_signed = signed_value;
    mint from_unsigned = unsigned_value;
    std::int64_t signed_remainder = signed_value % std::int64_t(mod);
    if (signed_remainder < 0) signed_remainder += mod;
    return from_signed.val() == std::uint64_t(signed_remainder) &&
           from_unsigned.val() == unsigned_value % mod;
}

static_assert(test_constexpr_construction());

void test_integral_construction() {
    assert(mint(-1).val() == mint::mod() - 1);
    assert(mint(std::numeric_limits<unsigned long long>::max()).val() ==
           std::numeric_limits<unsigned long long>::max() % mint::mod());

    std::mt19937 random(123456789);
    mint from_random = random();
    assert(from_random.val() < mint::mod());
    from_random = random() % 100;
    assert(from_random.val() < 100);
}

int main() {
    test_integral_construction();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
