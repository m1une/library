#ifndef M1UNE_MATH_TOTIENT_SUM_HPP
#define M1UNE_MATH_TOTIENT_SUM_HPP 1

#include <cassert>
#include <cstdint>
#include <unordered_map>
#include <vector>

namespace m1une {
namespace math {

struct TotientSum {
   private:
    int _precalculation_limit;
    std::vector<__uint128_t> _prefix_sum;
    std::unordered_map<uint64_t, __uint128_t> _memo;

    __uint128_t solve(uint64_t n) {
        if (n <= static_cast<uint64_t>(_precalculation_limit)) {
            return _prefix_sum[static_cast<int>(n)];
        }
        if (auto it = _memo.find(n); it != _memo.end()) {
            return it->second;
        }

        const __uint128_t wide_n = n;
        __uint128_t result = wide_n * (wide_n + 1) / 2;
        for (uint64_t left = 2; left <= n;) {
            const uint64_t quotient = n / left;
            const uint64_t right = n / quotient;
            result -= static_cast<__uint128_t>(right - left + 1) * solve(quotient);
            if (right == n) break;
            left = right + 1;
        }

        _memo.emplace(n, result);
        return result;
    }

   public:
    explicit TotientSum(int precalculation_limit = 1000000) : _precalculation_limit(precalculation_limit) {
        assert(precalculation_limit >= 0);

        std::vector<uint64_t> phi(precalculation_limit + 1);
        std::vector<int> primes;
        std::vector<bool> is_composite(precalculation_limit + 1);
        if (precalculation_limit >= 1) {
            phi[1] = 1;
        }
        for (int value = 2; value <= precalculation_limit; value++) {
            if (!is_composite[value]) {
                primes.push_back(value);
                phi[value] = static_cast<uint64_t>(value - 1);
            }
            for (int prime : primes) {
                if (value > precalculation_limit / prime) break;
                const int next = value * prime;
                is_composite[next] = true;
                if (value % prime == 0) {
                    phi[next] = phi[value] * static_cast<uint64_t>(prime);
                    break;
                }
                phi[next] = phi[value] * static_cast<uint64_t>(prime - 1);
            }
        }

        _prefix_sum.assign(precalculation_limit + 1, 0);
        for (int value = 1; value <= precalculation_limit; value++) {
            _prefix_sum[value] = _prefix_sum[value - 1] + phi[value];
        }
    }

    int precalculation_limit() const {
        return _precalculation_limit;
    }

    // Returns sum_{i=1}^n phi(i).
    __uint128_t prefix_sum(uint64_t n) {
        return solve(n);
    }

    __uint128_t operator()(uint64_t n) {
        return prefix_sum(n);
    }
};

inline __uint128_t totient_sum(uint64_t n, int precalculation_limit = 1000000) {
    TotientSum solver(precalculation_limit);
    return solver.prefix_sum(n);
}

}  // namespace math
}  // namespace m1une

#endif  // M1UNE_MATH_TOTIENT_SUM_HPP
