#ifndef M1UNE_MATH_MODINT_HPP
#define M1UNE_MATH_MODINT_HPP 1

#include <cstdint>
#include <iostream>
#include <type_traits>
#include <utility>

namespace m1une {
namespace math {

template <uint32_t Modulus>
struct ModInt {
    static_assert(0 < Modulus, "Modulus must be positive");

   private:
    uint32_t _v;

   public:
    static constexpr uint32_t mod() {
        return Modulus;
    }

    static constexpr ModInt raw(uint32_t v) noexcept {
        ModInt x;
        x._v = v;
        return x;
    }

    constexpr ModInt() noexcept : _v(0) {}

    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
    constexpr ModInt(Integer v) noexcept {
        if constexpr (std::is_signed_v<Integer>) {
            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);
            if (x < 0) x += Modulus;
            _v = static_cast<uint32_t>(x);
        } else {
            _v = static_cast<uint32_t>(static_cast<uint64_t>(v) % Modulus);
        }
    }

    constexpr uint32_t val() const noexcept {
        return _v;
    }

    constexpr ModInt& operator++() noexcept {
        _v++;
        if (_v == Modulus) _v = 0;
        return *this;
    }

    constexpr ModInt& operator--() noexcept {
        if (_v == 0) _v = Modulus;
        _v--;
        return *this;
    }

    constexpr ModInt operator++(int) noexcept {
        ModInt res = *this;
        ++*this;
        return res;
    }

    constexpr ModInt operator--(int) noexcept {
        ModInt res = *this;
        --*this;
        return res;
    }

    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {
        _v += rhs._v;
        if (_v >= Modulus) _v -= Modulus;
        return *this;
    }

    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {
        _v -= rhs._v;
        if (_v >= Modulus) _v += Modulus;
        return *this;
    }

    constexpr ModInt& operator*=(const ModInt& rhs) noexcept {
        uint64_t z = _v;
        z *= rhs._v;
        _v = static_cast<uint32_t>(z % Modulus);
        return *this;
    }

    constexpr ModInt& operator/=(const ModInt& rhs) noexcept {
        return *this *= rhs.inv();
    }

    constexpr ModInt operator+(const ModInt& rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    constexpr ModInt operator-(const ModInt& rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    constexpr ModInt operator*(const ModInt& rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    constexpr ModInt operator/(const ModInt& rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    constexpr bool operator==(const ModInt& rhs) const noexcept {
        return _v == rhs._v;
    }
    constexpr bool operator!=(const ModInt& rhs) const noexcept {
        return _v != rhs._v;
    }

    constexpr ModInt pow(long long n) const noexcept {
        ModInt res = raw(1), x = *this;
        while (n > 0) {
            if (n & 1) res *= x;
            x *= x;
            n >>= 1;
        }
        return res;
    }

    constexpr ModInt inv() const noexcept {
        int64_t a = _v, b = Modulus, u = 1, v = 0;
        while (b) {
            int64_t t = a / b;
            a -= t * b;
            std::swap(a, b);
            u -= t * v;
            std::swap(u, v);
        }
        if (u < 0) u += Modulus;
        return raw(static_cast<uint32_t>(u));
    }

    friend std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {
        return os << rhs._v;
    }

    friend std::istream& operator>>(std::istream& is, ModInt& rhs) {
        long long v;
        is >> v;
        rhs = ModInt(v);
        return is;
    }
};

using modint998244353 = ModInt<998244353>;
using modint1000000007 = ModInt<1000000007>;

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_MODINT_HPP
