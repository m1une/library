#ifndef M1UNE_FPS_FORMAL_POWER_SERIES_HPP
#define M1UNE_FPS_FORMAL_POWER_SERIES_HPP 1

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <optional>
#include <utility>
#include <vector>

#include "convolution.hpp"

namespace m1une {
namespace fps {

namespace internal {

template <class Mint>
std::optional<Mint> modular_square_root(Mint value) {
    const uint32_t mod = Mint::mod();
    if (value == Mint(0)) return Mint(0);
    if (mod == 2) return value;
    if (value.pow((mod - 1) / 2) != Mint(1)) return std::nullopt;
    if (mod % 4 == 3) return value.pow((mod + 1) / 4);

    uint32_t q = mod - 1;
    int s = 0;
    while ((q & 1) == 0) {
        q >>= 1;
        s++;
    }

    Mint z = 2;
    while (z.pow((mod - 1) / 2) == Mint(1)) ++z;
    Mint c = z.pow(q);
    Mint x = value.pow((q + 1) / 2);
    Mint t = value.pow(q);
    int m = s;
    while (t != Mint(1)) {
        int i = 1;
        Mint squared = t * t;
        while (squared != Mint(1)) {
            squared *= squared;
            i++;
        }
        Mint b = c.pow(uint64_t(1) << (m - i - 1));
        x *= b;
        c = b * b;
        t *= c;
        m = i;
    }
    return x;
}

}  // namespace internal

template <class Mint>
struct FormalPowerSeries : std::vector<Mint> {
    using std::vector<Mint>::vector;
    using Fps = FormalPowerSeries;

    FormalPowerSeries() = default;
    FormalPowerSeries(const std::vector<Mint>& values) : std::vector<Mint>(values) {}
    FormalPowerSeries(std::vector<Mint>&& values) : std::vector<Mint>(std::move(values)) {}

    Fps& shrink() {
        while (!this->empty() && this->back() == Mint(0)) this->pop_back();
        return *this;
    }

    Fps pre(int degree) const {
        assert(degree >= 0);
        Fps result(this->begin(), this->begin() + std::min<int>(degree, this->size()));
        result.resize(degree);
        return result;
    }

    Fps reversed(int size = -1) const {
        Fps result = *this;
        if (size >= 0) result.resize(size);
        std::reverse(result.begin(), result.end());
        return result;
    }

    Fps& operator+=(const Fps& rhs) {
        if (this->size() < rhs.size()) this->resize(rhs.size());
        for (int i = 0; i < int(rhs.size()); i++) (*this)[i] += rhs[i];
        return *this;
    }

    Fps& operator-=(const Fps& rhs) {
        if (this->size() < rhs.size()) this->resize(rhs.size());
        for (int i = 0; i < int(rhs.size()); i++) (*this)[i] -= rhs[i];
        return *this;
    }

    Fps& operator*=(const Fps& rhs) {
        std::vector<Mint> lhs(this->begin(), this->end());
        *this = convolution(lhs, rhs);
        return *this;
    }

    Fps& operator*=(Mint rhs) {
        for (Mint& value : *this) value *= rhs;
        return *this;
    }

    Fps& operator/=(Mint rhs) {
        return *this *= rhs.inv();
    }

    Fps& operator<<=(int shift) {
        assert(shift >= 0);
        this->insert(this->begin(), shift, Mint(0));
        return *this;
    }

    Fps& operator>>=(int shift) {
        assert(shift >= 0);
        if (shift >= int(this->size())) {
            this->clear();
        } else {
            this->erase(this->begin(), this->begin() + shift);
        }
        return *this;
    }

    Fps operator+() const {
        return *this;
    }

    Fps operator-() const {
        Fps result = *this;
        for (Mint& value : result) value = Mint(0) - value;
        return result;
    }

    friend Fps operator+(Fps lhs, const Fps& rhs) {
        return lhs += rhs;
    }

    friend Fps operator-(Fps lhs, const Fps& rhs) {
        return lhs -= rhs;
    }

    friend Fps operator*(Fps lhs, const Fps& rhs) {
        return lhs *= rhs;
    }

    friend Fps operator*(Fps lhs, Mint rhs) {
        return lhs *= rhs;
    }

    friend Fps operator*(Mint lhs, Fps rhs) {
        return rhs *= lhs;
    }

    friend Fps operator/(Fps lhs, Mint rhs) {
        return lhs /= rhs;
    }

    friend Fps operator<<(Fps lhs, int shift) {
        return lhs <<= shift;
    }

    friend Fps operator>>(Fps lhs, int shift) {
        return lhs >>= shift;
    }

    Fps derivative() const {
        if (this->empty()) return {};
        Fps result(this->size() - 1);
        for (int i = 1; i < int(this->size()); i++) result[i - 1] = (*this)[i] * Mint(i);
        return result;
    }

    Fps integral() const {
        Fps result(this->size() + 1);
        if (this->empty()) return result;
        assert(this->size() < Mint::mod());

        std::vector<Mint> inverse(this->size() + 1);
        inverse[1] = 1;
        for (int i = 2; i <= int(this->size()); i++) {
            inverse[i] = Mint(0) - Mint(Mint::mod() / uint32_t(i)) * inverse[Mint::mod() % uint32_t(i)];
        }
        for (int i = 0; i < int(this->size()); i++) result[i + 1] = (*this)[i] * inverse[i + 1];
        return result;
    }

    Mint evaluate(Mint x) const {
        Mint result = 0;
        for (auto it = this->rbegin(); it != this->rend(); ++it) result = result * x + *it;
        return result;
    }

    Fps inv(int degree = -1) const {
        if (degree < 0) degree = int(this->size());
        assert(degree >= 0);
        if (degree == 0) return {};
        assert(!this->empty() && (*this)[0] != Mint(0));

        Fps result(1, (*this)[0].inv());
        for (int size = 1; size < degree; size <<= 1) {
            const int next_size = std::min(size << 1, degree);
            Fps product = this->pre(next_size) * result;
            product.resize(next_size);
            for (Mint& value : product) value = Mint(0) - value;
            product[0] += Mint(2);
            result = (result * product).pre(next_size);
        }
        return result.pre(degree);
    }

    Fps log(int degree = -1) const {
        if (degree < 0) degree = int(this->size());
        assert(degree >= 0);
        if (degree == 0) return {};
        assert(!this->empty() && (*this)[0] == Mint(1));
        return (derivative() * inv(degree)).pre(degree - 1).integral();
    }

    Fps exp(int degree = -1) const {
        if (degree < 0) degree = int(this->size());
        assert(degree >= 0);
        if (degree == 0) return {};
        assert(this->empty() || (*this)[0] == Mint(0));

        Fps result(1, Mint(1));
        for (int size = 1; size < degree; size <<= 1) {
            const int next_size = std::min(size << 1, degree);
            Fps correction = this->pre(next_size) - result.log(next_size);
            correction[0] += Mint(1);
            result = (result * correction).pre(next_size);
        }
        return result.pre(degree);
    }

    Fps pow(long long exponent, int degree = -1) const {
        if (degree < 0) degree = int(this->size());
        assert(exponent >= 0 && degree >= 0);
        if (degree == 0) return {};
        if (exponent == 0) {
            Fps result(degree);
            result[0] = 1;
            return result;
        }

        int first = 0;
        while (first < int(this->size()) && (*this)[first] == Mint(0)) first++;
        if (first == int(this->size()) || first > (degree - 1) / exponent) return Fps(degree);

        const int shift = int(first * exponent);
        const Mint leading = (*this)[first];
        Fps normalized = (*this >> first) / leading;
        Fps result = (normalized.log(degree - shift) * Mint(exponent)).exp(degree - shift);
        result *= leading.pow(exponent);
        result <<= shift;
        result.resize(degree);
        return result;
    }

    std::optional<Fps> sqrt(int degree = -1) const {
        if (degree < 0) degree = int(this->size());
        assert(degree >= 0);
        if (degree == 0) return Fps();

        int first = 0;
        while (first < int(this->size()) && (*this)[first] == Mint(0)) first++;
        if (first == int(this->size())) return Fps(degree);
        if (first >= degree) return Fps(degree);
        if (first & 1) return std::nullopt;

        const int shift = first / 2;
        auto leading_root = internal::modular_square_root((*this)[first]);
        if (!leading_root.has_value()) return std::nullopt;

        const int result_degree = degree - shift;
        Fps normalized = (*this >> first) / (*this)[first];
        Fps result = (normalized.log(result_degree) / Mint(2)).exp(result_degree);
        result *= *leading_root;
        result <<= shift;
        result.resize(degree);
        return result;
    }

    std::pair<Fps, Fps> divmod(const Fps& divisor) const {
        Fps dividend = *this;
        Fps normalized_divisor = divisor;
        dividend.shrink();
        normalized_divisor.shrink();
        assert(!normalized_divisor.empty());

        if (dividend.size() < normalized_divisor.size()) return std::make_pair(Fps(), dividend);
        const int quotient_size = int(dividend.size() - normalized_divisor.size() + 1);
        Fps quotient =
            (dividend.reversed().pre(quotient_size) * normalized_divisor.reversed().inv(quotient_size))
                .pre(quotient_size)
                .reversed();
        quotient.shrink();
        Fps remainder = dividend - normalized_divisor * quotient;
        remainder.resize(normalized_divisor.size() - 1);
        remainder.shrink();
        return std::make_pair(std::move(quotient), std::move(remainder));
    }

    Fps& operator/=(const Fps& rhs) {
        *this = divmod(rhs).first;
        return *this;
    }

    Fps& operator%=(const Fps& rhs) {
        *this = divmod(rhs).second;
        return *this;
    }

    friend Fps operator/(Fps lhs, const Fps& rhs) {
        return lhs /= rhs;
    }

    friend Fps operator%(Fps lhs, const Fps& rhs) {
        return lhs %= rhs;
    }

    Fps taylor_shift(Mint shift) const {
        const int n = int(this->size());
        if (n == 0) return {};
        assert(uint32_t(n) < Mint::mod());

        std::vector<Mint> factorial(n, Mint(1));
        std::vector<Mint> inverse_factorial(n, Mint(1));
        for (int i = 1; i < n; i++) factorial[i] = factorial[i - 1] * Mint(i);
        inverse_factorial[n - 1] = factorial[n - 1].inv();
        for (int i = n - 1; i > 0; i--) inverse_factorial[i - 1] = inverse_factorial[i] * Mint(i);

        Fps left(n);
        Fps right(n);
        Mint power = 1;
        for (int i = 0; i < n; i++) {
            left[n - 1 - i] = (*this)[i] * factorial[i];
            right[i] = power * inverse_factorial[i];
            power *= shift;
        }
        Fps product = left * right;
        Fps result(n);
        for (int i = 0; i < n; i++) result[i] = product[n - 1 - i] * inverse_factorial[i];
        return result;
    }
};

}  // namespace fps
}  // namespace m1une

#endif  // M1UNE_FPS_FORMAL_POWER_SERIES_HPP
