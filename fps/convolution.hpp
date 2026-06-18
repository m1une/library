#ifndef M1UNE_FPS_CONVOLUTION_HPP
#define M1UNE_FPS_CONVOLUTION_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <utility>
#include <vector>

#include "math/modint.hpp"

namespace m1une {
namespace fps {

namespace internal {

constexpr uint32_t primitive_root_constexpr(uint32_t mod) {
    if (mod == 2) return 1;
    if (mod == 167772161) return 3;
    if (mod == 469762049) return 3;
    if (mod == 754974721) return 11;
    if (mod == 998244353) return 3;
    if (mod == 1224736769) return 3;

    uint32_t divisors[32] = {};
    int count = 0;
    uint32_t x = mod - 1;
    for (uint32_t p = 2; uint64_t(p) * p <= x; p++) {
        if (x % p != 0) continue;
        divisors[count++] = p;
        while (x % p == 0) x /= p;
    }
    if (x > 1) divisors[count++] = x;

    for (uint32_t g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < count; i++) {
            uint64_t value = 1;
            uint64_t base = g;
            uint32_t exponent = (mod - 1) / divisors[i];
            while (exponent > 0) {
                if (exponent & 1) value = value * base % mod;
                base = base * base % mod;
                exponent >>= 1;
            }
            if (value == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}

constexpr int two_adic_order(uint32_t x) {
    int result = 0;
    while ((x & 1) == 0) {
        x >>= 1;
        result++;
    }
    return result;
}

template <class Mint>
struct NttRoots {
    static constexpr int max_base = two_adic_order(Mint::mod() - 1);
    std::array<Mint, max_base + 1> root;
    std::array<Mint, max_base + 1> inverse_root;

    NttRoots() {
        constexpr uint32_t primitive_root = primitive_root_constexpr(Mint::mod());
        for (int level = 1; level <= max_base; level++) {
            root[level] = Mint(primitive_root).pow((Mint::mod() - 1) >> level);
            inverse_root[level] = root[level].inv();
        }
    }
};

template <class Mint>
const NttRoots<Mint>& ntt_roots() {
    static const NttRoots<Mint> roots;
    return roots;
}

template <class Mint>
void ntt(std::vector<Mint>& a, bool inverse) {
    const int n = int(a.size());
    assert(n > 0 && (n & (n - 1)) == 0);
    assert((Mint::mod() - 1) % uint32_t(n) == 0);

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }

    const auto& roots = ntt_roots<Mint>();
    int level = 1;
    for (int len = 2; len <= n; len <<= 1, level++) {
        const Mint step = inverse ? roots.inverse_root[level] : roots.root[level];
        const int half = len >> 1;
        for (int offset = 0; offset < n; offset += len) {
            Mint w = 1;
            for (int j = 0; j < half; j++) {
                Mint even = a[offset + j];
                Mint odd = a[offset + j + half] * w;
                a[offset + j] = even + odd;
                a[offset + j + half] = even - odd;
                w *= step;
            }
        }
    }

    if (inverse) {
        const Mint inverse_n = Mint(n).inv();
        for (Mint& value : a) value *= inverse_n;
    }
}

}  // namespace internal

template <class Mint>
std::vector<Mint> convolution_naive(const std::vector<Mint>& a, const std::vector<Mint>& b) {
    if (a.empty() || b.empty()) return {};
    std::vector<Mint> result(a.size() + b.size() - 1);
    if (a.size() < b.size()) {
        for (int i = 0; i < int(a.size()); i++) {
            for (int j = 0; j < int(b.size()); j++) result[i + j] += a[i] * b[j];
        }
    } else {
        for (int j = 0; j < int(b.size()); j++) {
            for (int i = 0; i < int(a.size()); i++) result[i + j] += a[i] * b[j];
        }
    }
    return result;
}

template <class Mint>
std::vector<Mint> convolution_ntt(const std::vector<Mint>& a, const std::vector<Mint>& b) {
    const int result_size = int(a.size() + b.size() - 1);
    int n = 1;
    while (n < result_size) n <<= 1;
    assert((Mint::mod() - 1) % uint32_t(n) == 0);

    std::vector<Mint> fa(a.begin(), a.end());
    std::vector<Mint> fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);
    internal::ntt(fa, false);
    internal::ntt(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    internal::ntt(fa, true);
    fa.resize(result_size);
    return fa;
}

template <class Mint>
std::vector<Mint> convolution(const std::vector<Mint>& a, const std::vector<Mint>& b) {
    if (a.empty() || b.empty()) return {};
    if (std::min(a.size(), b.size()) <= 32) return convolution_naive(a, b);

    const int result_size = int(a.size() + b.size() - 1);
    int n = 1;
    while (n < result_size) n <<= 1;
    if ((Mint::mod() - 1) % uint32_t(n) == 0) return convolution_ntt(a, b);

    using Mint1 = math::ModInt<167772161>;
    using Mint2 = math::ModInt<469762049>;
    using Mint3 = math::ModInt<754974721>;
    assert(n <= (1 << 24));

    const unsigned __int128 coefficient_bound =
        static_cast<unsigned __int128>(std::min(a.size(), b.size())) * (Mint::mod() - 1) *
        (Mint::mod() - 1);
    const unsigned __int128 crt_modulus =
        static_cast<unsigned __int128>(Mint1::mod()) * Mint2::mod() * Mint3::mod();
    assert(coefficient_bound < crt_modulus);

    auto converted_convolution = [&]<class OtherMint>() {
        std::vector<OtherMint> converted_a(a.size());
        std::vector<OtherMint> converted_b(b.size());
        for (int i = 0; i < int(a.size()); i++) converted_a[i] = OtherMint(a[i].val());
        for (int i = 0; i < int(b.size()); i++) converted_b[i] = OtherMint(b[i].val());
        return convolution_ntt(converted_a, converted_b);
    };
    std::vector<Mint1> c1 = converted_convolution.template operator()<Mint1>();
    std::vector<Mint2> c2 = converted_convolution.template operator()<Mint2>();
    std::vector<Mint3> c3 = converted_convolution.template operator()<Mint3>();
    static const uint64_t inverse_mod1_mod2 = Mint2(Mint1::mod()).inv().val();
    static const uint64_t mod1_mod3 = Mint1::mod() % Mint3::mod();
    static const uint64_t mod1_mod2_mod3 =
        mod1_mod3 * (Mint2::mod() % Mint3::mod()) % Mint3::mod();
    static const uint64_t inverse_mod1_mod2_mod3 = Mint3(uint32_t(mod1_mod2_mod3)).inv().val();

    const uint64_t target_mod = Mint::mod();
    const uint64_t mod1_target = Mint1::mod() % target_mod;
    const uint64_t mod1_mod2_target = mod1_target * (Mint2::mod() % target_mod) % target_mod;
    std::vector<Mint> result(result_size);
    for (int i = 0; i < result_size; i++) {
        const uint64_t r1 = c1[i].val();
        const uint64_t r2 = c2[i].val();
        const uint64_t r3 = c3[i].val();
        const uint64_t first =
            (r2 + Mint2::mod() - r1 % Mint2::mod()) % Mint2::mod() * inverse_mod1_mod2 %
            Mint2::mod();
        const uint64_t combined_mod3 =
            (r1 % Mint3::mod() + mod1_mod3 * (first % Mint3::mod())) % Mint3::mod();
        const uint64_t second =
            (r3 + Mint3::mod() - combined_mod3) % Mint3::mod() * inverse_mod1_mod2_mod3 %
            Mint3::mod();

        uint64_t value = r1 % target_mod;
        value = (value + mod1_target * (first % target_mod)) % target_mod;
        value = (value + mod1_mod2_target * (second % target_mod)) % target_mod;
        result[i] = Mint::raw(uint32_t(value));
    }
    return result;
}

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_CONVOLUTION_HPP
