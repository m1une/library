#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../math/lucas.hpp"
#include "../../math/modint.hpp"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

namespace {

template <uint32_t Prime>
void test_prime() {
    using Mint = m1une::math::ModInt<Prime>;
    m1une::math::Lucas<Mint> lucas;
    assert(lucas.prime() == Prime);

    const int maximum = 500;
    std::vector<Mint> previous(maximum + 2);
    previous[0] = Mint(1);
    for (int n = 0; n <= maximum; n++) {
        for (int k = 0; k <= n; k++) {
            assert(lucas.binom(n, k) == previous[k]);
            assert(lucas(n, k) == previous[k]);
        }
        assert(lucas.binom(n, uint64_t(n) + 1) == Mint(0));

        std::vector<Mint> next(maximum + 2);
        next[0] = Mint(1);
        for (int k = 1; k <= n + 1; k++) {
            next[k] = previous[k - 1] + previous[k];
        }
        previous.swap(next);
    }
}

void test_large_arguments() {
    using Mint2 = m1une::math::ModInt<2>;
    m1une::math::Lucas<Mint2> binary;
    uint64_t n = 0xF0F0F0F0F0F0F0F0ULL;
    uint64_t subset = 0x1010101010101010ULL;
    uint64_t not_subset = subset | 1ULL;
    assert(binary(n, subset) == Mint2(1));
    assert(binary(n, not_subset) == Mint2(0));

    using Mint5 = m1une::math::ModInt<5>;
    m1une::math::LucasTheorem<Mint5> base_five;
    const uint64_t power = 7450580596923828125ULL;
    assert(base_five.binom(power, 0) == Mint5(1));
    assert(base_five.binom(power, power) == Mint5(1));
    assert(base_five.binom(power, 1) == Mint5(0));
    assert(base_five.binom(power + 3, 2) == Mint5(3));
}

}  // namespace

int main() {
    test_prime<2>();
    test_prime<3>();
    test_prime<5>();
    test_prime<7>();
    test_prime<11>();
    test_prime<13>();
    test_large_arguments();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
