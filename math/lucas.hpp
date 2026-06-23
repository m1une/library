#ifndef M1UNE_MATH_LUCAS_HPP
#define M1UNE_MATH_LUCAS_HPP 1

#include <cassert>
#include <cstdint>
#include <vector>

namespace m1une {
namespace math {

template <class Mint>
struct Lucas {
   private:
    std::vector<Mint> _factorial;
    std::vector<Mint> _inverse_factorial;

    Mint small_binom(uint32_t n, uint32_t k) const {
        if (k > n) return Mint(0);
        return _factorial[n] * _inverse_factorial[k] * _inverse_factorial[n - k];
    }

   public:
    Lucas() {
        const uint32_t prime = Mint::mod();
        assert(2 <= prime);
        _factorial.resize(prime);
        _inverse_factorial.resize(prime);
        _factorial[0] = Mint(1);
        for (uint32_t i = 1; i < prime; i++) {
            _factorial[i] = _factorial[i - 1] * Mint(i);
        }
        _inverse_factorial[prime - 1] = _factorial[prime - 1].inv();
        for (uint32_t i = prime - 1; i > 0; i--) {
            _inverse_factorial[i - 1] = _inverse_factorial[i] * Mint(i);
        }
    }

    uint32_t prime() const {
        return Mint::mod();
    }

    Mint binom(uint64_t n, uint64_t k) const {
        if (k > n) return Mint(0);
        const uint64_t modulus = Mint::mod();
        Mint result = Mint(1);
        while (n > 0 || k > 0) {
            uint32_t n_digit = uint32_t(n % modulus);
            uint32_t k_digit = uint32_t(k % modulus);
            if (k_digit > n_digit) return Mint(0);
            result *= small_binom(n_digit, k_digit);
            n /= modulus;
            k /= modulus;
        }
        return result;
    }

    Mint operator()(uint64_t n, uint64_t k) const {
        return binom(n, k);
    }
};

template <class Mint>
using LucasTheorem = Lucas<Mint>;

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_LUCAS_HPP
