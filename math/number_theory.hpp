#ifndef M1UNE_MATH_NUMBER_THEORY_HPP
#define M1UNE_MATH_NUMBER_THEORY_HPP 1

#include <cassert>
#include <cstdint>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

namespace m1une {
namespace math {

namespace internal {

inline long long safe_mod(long long x, long long mod) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

inline unsigned __int128 floor_sum_unsigned(unsigned long long n, unsigned long long mod, unsigned long long a,
                                            unsigned long long b) {
    unsigned __int128 answer = 0;
    while (true) {
        if (a >= mod) {
            answer += static_cast<unsigned __int128>(n) * (n - 1) / 2 * (a / mod);
            a %= mod;
        }
        if (b >= mod) {
            answer += static_cast<unsigned __int128>(n) * (b / mod);
            b %= mod;
        }

        const unsigned __int128 y_max = static_cast<unsigned __int128>(a) * n + b;
        if (y_max < mod) break;
        n = static_cast<unsigned long long>(y_max / mod);
        b = static_cast<unsigned long long>(y_max % mod);
        unsigned long long tmp = mod;
        mod = a;
        a = tmp;
    }
    return answer;
}

}  // namespace internal

// Returns (g, x, y), where g = gcd(a, b) is nonnegative and
// a * x + b * y = g. Returns (0, 0, 0) when a = b = 0.
inline std::tuple<long long, long long, long long> extended_gcd(long long a,
                                                               long long b) {
    using i128 = __int128;
    if (a == 0 && b == 0) return {0, 0, 0};

    i128 old_remainder = a;
    i128 remainder = b;
    if (old_remainder < 0) old_remainder = -old_remainder;
    if (remainder < 0) remainder = -remainder;
    i128 old_x = 1;
    i128 x = 0;
    i128 old_y = 0;
    i128 y = 1;

    while (remainder != 0) {
        i128 quotient = old_remainder / remainder;

        i128 next = old_remainder - quotient * remainder;
        old_remainder = remainder;
        remainder = next;

        next = old_x - quotient * x;
        old_x = x;
        x = next;

        next = old_y - quotient * y;
        old_y = y;
        y = next;
    }

    if (a < 0) old_x = -old_x;
    if (b < 0) old_y = -old_y;

#ifndef NDEBUG
    const i128 minimum = std::numeric_limits<long long>::min();
    const i128 maximum = std::numeric_limits<long long>::max();
    assert(old_remainder <= maximum);
    assert(minimum <= old_x && old_x <= maximum);
    assert(minimum <= old_y && old_y <= maximum);
#endif
    return {static_cast<long long>(old_remainder), static_cast<long long>(old_x),
            static_cast<long long>(old_y)};
}

inline long long pow_mod(long long x, unsigned long long exponent, long long mod) {
    assert(mod >= 1);
    if (mod == 1) return 0;

    unsigned long long base = static_cast<unsigned long long>(internal::safe_mod(x, mod));
    unsigned long long result = 1;
    const unsigned long long unsigned_mod = static_cast<unsigned long long>(mod);
    while (exponent > 0) {
        if (exponent & 1) {
            result = static_cast<unsigned long long>(static_cast<unsigned __int128>(result) * base % unsigned_mod);
        }
        base = static_cast<unsigned long long>(static_cast<unsigned __int128>(base) * base % unsigned_mod);
        exponent >>= 1;
    }
    return static_cast<long long>(result);
}

// Returns gcd(a, mod) and x such that a * x is congruent to gcd(a, mod)
// modulo mod. The returned x is in [0, mod / gcd(a, mod)).
inline std::pair<long long, long long> inv_gcd(long long a, long long mod) {
    assert(mod >= 1);
    a = internal::safe_mod(a, mod);
    if (a == 0) return {mod, 0};

    long long s = mod;
    long long t = a;
    long long m0 = 0;
    long long m1 = 1;
    while (t > 0) {
        const long long quotient = s / t;
        s -= t * quotient;
        m0 -= m1 * quotient;

        long long tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += mod / s;
    return {s, m0};
}

inline long long inv_mod(long long x, long long mod) {
    const auto result = inv_gcd(x, mod);
    assert(result.first == 1);
    return result.second;
}

// Returns the smallest nonnegative solution and the least common multiple of
// the moduli. Returns {0, 0} when the system is inconsistent.
inline std::pair<long long, long long> crt(const std::vector<long long>& remainders,
                                           const std::vector<long long>& moduli) {
    assert(remainders.size() == moduli.size());

    long long r0 = 0;
    long long m0 = 1;
    for (int i = 0; i < int(remainders.size()); i++) {
        assert(moduli[i] >= 1);
        long long r1 = internal::safe_mod(remainders[i], moduli[i]);
        long long m1 = moduli[i];

        if (m0 < m1) {
            long long tmp = r0;
            r0 = r1;
            r1 = tmp;
            tmp = m0;
            m0 = m1;
            m1 = tmp;
        }
        if (m0 % m1 == 0) {
            if (r0 % m1 != r1) return {0, 0};
            continue;
        }

        const auto inverse = inv_gcd(m0, m1);
        const long long gcd = inverse.first;
        const long long reduced_modulus = m1 / gcd;
        const __int128 difference = static_cast<__int128>(r1) - r0;
        if (difference % gcd != 0) return {0, 0};

        __int128 multiplier = difference / gcd % reduced_modulus;
        multiplier = multiplier * inverse.second % reduced_modulus;
        if (multiplier < 0) multiplier += reduced_modulus;

        const __int128 new_modulus = static_cast<__int128>(m0) * reduced_modulus;
        assert(new_modulus <= std::numeric_limits<long long>::max());
        __int128 new_remainder = static_cast<__int128>(r0) + multiplier * m0;
        new_remainder %= new_modulus;
        if (new_remainder < 0) new_remainder += new_modulus;
        r0 = static_cast<long long>(new_remainder);
        m0 = static_cast<long long>(new_modulus);
    }
    return {r0, m0};
}

// Returns sum_{i=0}^{n-1} floor((a * i + b) / mod).
inline long long floor_sum(long long n, long long mod, long long a, long long b) {
    assert(n >= 0);
    assert(mod >= 1);

    const long long normalized_a = internal::safe_mod(a, mod);
    const long long normalized_b = internal::safe_mod(b, mod);
    __int128 answer = (static_cast<__int128>(a) - normalized_a) / mod * n * (n - 1) / 2;
    answer += (static_cast<__int128>(b) - normalized_b) / mod * n;
    answer += internal::floor_sum_unsigned(static_cast<unsigned long long>(n), static_cast<unsigned long long>(mod),
                                           static_cast<unsigned long long>(normalized_a),
                                           static_cast<unsigned long long>(normalized_b));

    assert(answer >= std::numeric_limits<long long>::min());
    assert(answer <= std::numeric_limits<long long>::max());
    return static_cast<long long>(answer);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_NUMBER_THEORY_HPP
