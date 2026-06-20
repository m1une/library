#ifndef M1UNE_MATH_COMBINATORICS_HPP
#define M1UNE_MATH_COMBINATORICS_HPP 1

#include <cassert>
#include <cstdint>
#include <vector>

namespace m1une {
namespace math {

template <class Mint>
struct Combinatorics {
   private:
    std::vector<Mint> _factorial;
    std::vector<Mint> _inverse_factorial;

   public:
    explicit Combinatorics(int maximum = 0) : _factorial(1, Mint(1)), _inverse_factorial(1, Mint(1)) {
        ensure(maximum);
    }

    int maximum() const {
        return int(_factorial.size()) - 1;
    }

    void ensure(int maximum) {
        assert(maximum >= 0);
        assert(static_cast<uint64_t>(maximum) < Mint::mod());
        if (maximum <= this->maximum()) return;

        const int old_maximum = this->maximum();
        _factorial.resize(maximum + 1);
        _inverse_factorial.resize(maximum + 1);
        for (int i = old_maximum + 1; i <= maximum; i++) {
            _factorial[i] = _factorial[i - 1] * Mint(i);
        }
        _inverse_factorial[maximum] = _factorial[maximum].inv();
        for (int i = maximum; i > old_maximum; i--) {
            _inverse_factorial[i - 1] = _inverse_factorial[i] * Mint(i);
        }
    }

    Mint factorial(int n) const {
        assert(0 <= n && n <= maximum());
        return _factorial[n];
    }

    Mint inverse_factorial(int n) const {
        assert(0 <= n && n <= maximum());
        return _inverse_factorial[n];
    }

    Mint inverse(int n) const {
        assert(1 <= n && n <= maximum());
        return _factorial[n - 1] * _inverse_factorial[n];
    }

    Mint binom(int n, int k) const {
        if (k < 0 || k > n) return Mint(0);
        assert(n <= maximum());
        return _factorial[n] * _inverse_factorial[k] * _inverse_factorial[n - k];
    }

    Mint perm(int n, int k) const {
        if (k < 0 || k > n) return Mint(0);
        assert(n <= maximum());
        return _factorial[n] * _inverse_factorial[n - k];
    }

    Mint multiset(int types, int count) const {
        if (types < 0 || count < 0) return Mint(0);
        if (types == 0) return Mint(count == 0);
        const long long total = static_cast<long long>(types) + count - 1;
        assert(total <= maximum());
        return binom(static_cast<int>(total), count);
    }

    Mint catalan(int n) const {
        assert(n >= 0);
        const long long doubled = 2LL * n;
        assert(doubled <= maximum());
        return binom(int(doubled), n) - binom(int(doubled), n + 1);
    }
};

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_COMBINATORICS_HPP
