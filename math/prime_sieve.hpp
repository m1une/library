#ifndef M1UNE_MATH_PRIME_SIEVE_HPP
#define M1UNE_MATH_PRIME_SIEVE_HPP 1

#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

namespace m1une {
namespace math {

struct PrimeSieve {
   private:
    int _limit;
    std::vector<int> _min_prime_factor;
    std::vector<int> _primes;

   public:
    explicit PrimeSieve(int limit = 0) : _limit(0) {
        assert(limit >= 0);
        _limit = limit;
        _min_prime_factor.assign(limit + 1, 0);
        if (limit >= 1) _min_prime_factor[1] = 1;
        for (int value = 2; value <= limit; value++) {
            if (_min_prime_factor[value] == 0) {
                _min_prime_factor[value] = value;
                _primes.push_back(value);
            }
            for (int prime : _primes) {
                if (prime > _min_prime_factor[value] || value > limit / prime) break;
                _min_prime_factor[value * prime] = prime;
            }
        }
    }

    int limit() const {
        return _limit;
    }

    const std::vector<int>& primes() const {
        return _primes;
    }

    const std::vector<int>& min_prime_factors() const {
        return _min_prime_factor;
    }

    bool is_prime(int value) const {
        assert(0 <= value && value <= _limit);
        return value >= 2 && _min_prime_factor[value] == value;
    }

    int min_prime_factor(int value) const {
        assert(2 <= value && value <= _limit);
        return _min_prime_factor[value];
    }

    std::vector<std::pair<int, int>> factorize(int value) const {
        assert(1 <= value && value <= _limit);
        std::vector<std::pair<int, int>> result;
        while (value > 1) {
            const int prime = _min_prime_factor[value];
            int exponent = 0;
            do {
                value /= prime;
                exponent++;
            } while (value > 1 && _min_prime_factor[value] == prime);
            result.emplace_back(prime, exponent);
        }
        return result;
    }

    std::vector<int> divisors(int value) const {
        std::vector<int> result = {1};
        for (const auto& factor : factorize(value)) {
            const int current_size = int(result.size());
            int power = 1;
            for (int exponent = 1; exponent <= factor.second; exponent++) {
                power *= factor.first;
                for (int i = 0; i < current_size; i++) {
                    result.push_back(result[i] * power);
                }
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    int totient(int value) const {
        assert(1 <= value && value <= _limit);
        int result = value;
        for (const auto& factor : factorize(value)) {
            result = result / factor.first * (factor.first - 1);
        }
        return result;
    }

    int mobius(int value) const {
        assert(1 <= value && value <= _limit);
        int result = 1;
        for (const auto& factor : factorize(value)) {
            if (factor.second >= 2) return 0;
            result = -result;
        }
        return result;
    }

    std::vector<int> totient_table() const {
        std::vector<int> result(_limit + 1);
        if (_limit >= 1) result[1] = 1;
        for (int value = 2; value <= _limit; value++) {
            const int prime = _min_prime_factor[value];
            const int reduced = value / prime;
            result[value] = reduced % prime == 0
                                ? result[reduced] * prime
                                : result[reduced] * (prime - 1);
        }
        return result;
    }

    std::vector<int> mobius_table() const {
        std::vector<int> result(_limit + 1);
        if (_limit >= 1) result[1] = 1;
        for (int value = 2; value <= _limit; value++) {
            const int prime = _min_prime_factor[value];
            const int reduced = value / prime;
            result[value] = reduced % prime == 0 ? 0 : -result[reduced];
        }
        return result;
    }
};

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_PRIME_SIEVE_HPP
