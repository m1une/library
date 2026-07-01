---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/enumerate_primes.test.cpp
    title: verify/math/enumerate_primes.test.cpp
  - icon: ':x:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/prime_sieve.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ math {\n\nstruct PrimeSieve {\n   private:\n    int _limit;\n    std::vector<int>\
    \ _min_prime_factor;\n    std::vector<int> _primes;\n\n   public:\n    explicit\
    \ PrimeSieve(int limit = 0) : _limit(0) {\n        assert(limit >= 0);\n     \
    \   _limit = limit;\n        _min_prime_factor.assign(limit + 1, 0);\n       \
    \ if (limit >= 1) _min_prime_factor[1] = 1;\n        for (int value = 2; value\
    \ <= limit; value++) {\n            if (_min_prime_factor[value] == 0) {\n   \
    \             _min_prime_factor[value] = value;\n                _primes.push_back(value);\n\
    \            }\n            for (int prime : _primes) {\n                if (prime\
    \ > _min_prime_factor[value] || value > limit / prime) break;\n              \
    \  _min_prime_factor[value * prime] = prime;\n            }\n        }\n    }\n\
    \n    int limit() const {\n        return _limit;\n    }\n\n    const std::vector<int>&\
    \ primes() const {\n        return _primes;\n    }\n\n    const std::vector<int>&\
    \ min_prime_factors() const {\n        return _min_prime_factor;\n    }\n\n  \
    \  bool is_prime(int value) const {\n        assert(0 <= value && value <= _limit);\n\
    \        return value >= 2 && _min_prime_factor[value] == value;\n    }\n\n  \
    \  int min_prime_factor(int value) const {\n        assert(2 <= value && value\
    \ <= _limit);\n        return _min_prime_factor[value];\n    }\n\n    std::vector<std::pair<int,\
    \ int>> factorize(int value) const {\n        assert(1 <= value && value <= _limit);\n\
    \        std::vector<std::pair<int, int>> result;\n        while (value > 1) {\n\
    \            const int prime = _min_prime_factor[value];\n            int exponent\
    \ = 0;\n            do {\n                value /= prime;\n                exponent++;\n\
    \            } while (value > 1 && _min_prime_factor[value] == prime);\n     \
    \       result.emplace_back(prime, exponent);\n        }\n        return result;\n\
    \    }\n\n    std::vector<int> divisors(int value) const {\n        std::vector<int>\
    \ result = {1};\n        for (const auto& factor : factorize(value)) {\n     \
    \       const int current_size = int(result.size());\n            int power =\
    \ 1;\n            for (int exponent = 1; exponent <= factor.second; exponent++)\
    \ {\n                power *= factor.first;\n                for (int i = 0; i\
    \ < current_size; i++) {\n                    result.push_back(result[i] * power);\n\
    \                }\n            }\n        }\n        std::sort(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    int totient(int value)\
    \ const {\n        assert(1 <= value && value <= _limit);\n        int result\
    \ = value;\n        for (const auto& factor : factorize(value)) {\n          \
    \  result = result / factor.first * (factor.first - 1);\n        }\n        return\
    \ result;\n    }\n\n    int mobius(int value) const {\n        assert(1 <= value\
    \ && value <= _limit);\n        int result = 1;\n        for (const auto& factor\
    \ : factorize(value)) {\n            if (factor.second >= 2) return 0;\n     \
    \       result = -result;\n        }\n        return result;\n    }\n\n    std::vector<int>\
    \ totient_table() const {\n        std::vector<int> result(_limit + 1);\n    \
    \    if (_limit >= 1) result[1] = 1;\n        for (int value = 2; value <= _limit;\
    \ value++) {\n            const int prime = _min_prime_factor[value];\n      \
    \      const int reduced = value / prime;\n            result[value] = reduced\
    \ % prime == 0 ? result[reduced] * prime : result[reduced] * (prime - 1);\n  \
    \      }\n        return result;\n    }\n\n    std::vector<int> mobius_table()\
    \ const {\n        std::vector<int> result(_limit + 1);\n        if (_limit >=\
    \ 1) result[1] = 1;\n        for (int value = 2; value <= _limit; value++) {\n\
    \            const int prime = _min_prime_factor[value];\n            const int\
    \ reduced = value / prime;\n            result[value] = reduced % prime == 0 ?\
    \ 0 : -result[reduced];\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_PRIME_SIEVE_HPP\n#define M1UNE_MATH_PRIME_SIEVE_HPP 1\n\
    \n#include <algorithm>\n#include <cassert>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace math {\n\nstruct PrimeSieve {\n   private:\n  \
    \  int _limit;\n    std::vector<int> _min_prime_factor;\n    std::vector<int>\
    \ _primes;\n\n   public:\n    explicit PrimeSieve(int limit = 0) : _limit(0) {\n\
    \        assert(limit >= 0);\n        _limit = limit;\n        _min_prime_factor.assign(limit\
    \ + 1, 0);\n        if (limit >= 1) _min_prime_factor[1] = 1;\n        for (int\
    \ value = 2; value <= limit; value++) {\n            if (_min_prime_factor[value]\
    \ == 0) {\n                _min_prime_factor[value] = value;\n               \
    \ _primes.push_back(value);\n            }\n            for (int prime : _primes)\
    \ {\n                if (prime > _min_prime_factor[value] || value > limit / prime)\
    \ break;\n                _min_prime_factor[value * prime] = prime;\n        \
    \    }\n        }\n    }\n\n    int limit() const {\n        return _limit;\n\
    \    }\n\n    const std::vector<int>& primes() const {\n        return _primes;\n\
    \    }\n\n    const std::vector<int>& min_prime_factors() const {\n        return\
    \ _min_prime_factor;\n    }\n\n    bool is_prime(int value) const {\n        assert(0\
    \ <= value && value <= _limit);\n        return value >= 2 && _min_prime_factor[value]\
    \ == value;\n    }\n\n    int min_prime_factor(int value) const {\n        assert(2\
    \ <= value && value <= _limit);\n        return _min_prime_factor[value];\n  \
    \  }\n\n    std::vector<std::pair<int, int>> factorize(int value) const {\n  \
    \      assert(1 <= value && value <= _limit);\n        std::vector<std::pair<int,\
    \ int>> result;\n        while (value > 1) {\n            const int prime = _min_prime_factor[value];\n\
    \            int exponent = 0;\n            do {\n                value /= prime;\n\
    \                exponent++;\n            } while (value > 1 && _min_prime_factor[value]\
    \ == prime);\n            result.emplace_back(prime, exponent);\n        }\n \
    \       return result;\n    }\n\n    std::vector<int> divisors(int value) const\
    \ {\n        std::vector<int> result = {1};\n        for (const auto& factor :\
    \ factorize(value)) {\n            const int current_size = int(result.size());\n\
    \            int power = 1;\n            for (int exponent = 1; exponent <= factor.second;\
    \ exponent++) {\n                power *= factor.first;\n                for (int\
    \ i = 0; i < current_size; i++) {\n                    result.push_back(result[i]\
    \ * power);\n                }\n            }\n        }\n        std::sort(result.begin(),\
    \ result.end());\n        return result;\n    }\n\n    int totient(int value)\
    \ const {\n        assert(1 <= value && value <= _limit);\n        int result\
    \ = value;\n        for (const auto& factor : factorize(value)) {\n          \
    \  result = result / factor.first * (factor.first - 1);\n        }\n        return\
    \ result;\n    }\n\n    int mobius(int value) const {\n        assert(1 <= value\
    \ && value <= _limit);\n        int result = 1;\n        for (const auto& factor\
    \ : factorize(value)) {\n            if (factor.second >= 2) return 0;\n     \
    \       result = -result;\n        }\n        return result;\n    }\n\n    std::vector<int>\
    \ totient_table() const {\n        std::vector<int> result(_limit + 1);\n    \
    \    if (_limit >= 1) result[1] = 1;\n        for (int value = 2; value <= _limit;\
    \ value++) {\n            const int prime = _min_prime_factor[value];\n      \
    \      const int reduced = value / prime;\n            result[value] = reduced\
    \ % prime == 0 ? result[reduced] * prime : result[reduced] * (prime - 1);\n  \
    \      }\n        return result;\n    }\n\n    std::vector<int> mobius_table()\
    \ const {\n        std::vector<int> result(_limit + 1);\n        if (_limit >=\
    \ 1) result[1] = 1;\n        for (int value = 2; value <= _limit; value++) {\n\
    \            const int prime = _min_prime_factor[value];\n            const int\
    \ reduced = value / prime;\n            result[value] = reduced % prime == 0 ?\
    \ 0 : -result[reduced];\n        }\n        return result;\n    }\n};\n\n}  //\
    \ namespace math\n}  // namespace m1une\n\n#endif  // M1UNE_MATH_PRIME_SIEVE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/prime_sieve.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-20 09:18:49+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - verify/math/enumerate_primes.test.cpp
  - verify/math/math_algorithms.test.cpp
documentation_of: math/prime_sieve.hpp
layout: document
title: Prime Sieve
---

## Overview

`PrimeSieve` builds a linear sieve and stores the smallest prime factor of every
integer up to a chosen limit. It is intended for contests with many primality,
factorization, divisor, totient, or Mobius queries in a bounded range.

For example, after constructing `PrimeSieve(1000000)`, primality checks for any
integer through one million take constant time, and factorizations repeatedly
divide by a stored smallest prime factor.

## What the Sieve Stores

For each integer `x >= 2`, `min_prime_factor(x)` is the smallest prime dividing
`x`.

| `x` | Smallest prime factor |
| --- | --- |
| `2` | `2` |
| `15` | `3` |
| `49` | `7` |
| `91` | `7` |

A number `x >= 2` is prime exactly when its smallest prime factor is itself.

To factor `360`, repeatedly divide by the smallest stored factor:

```text
360 / 2 = 180
180 / 2 = 90
 90 / 2 = 45
 45 / 3 = 15
 15 / 3 = 5
  5 / 5 = 1
```

Therefore $360 = 2^3 \cdot 3^2 \cdot 5$.

## Construction

```cpp
explicit PrimeSieve(int limit = 0);
```

Construction takes $O(\text{limit})$ time and $O(\text{limit})$ memory.

The implementation is a linear sieve: each composite number is generated from
its smallest prime factor only once. This gives linear construction time,
unlike the more familiar Eratosthenes analysis of $O(n \log \log n)$.

## Euler's Totient Function

`totient(x)` returns Euler's totient function $\varphi(x)$: the number of
integers from `1` through `x` that are coprime to `x`.

For example, `1`, `5`, `7`, and `11` are the four integers coprime to `12`, so
`totient(12)` is `4`.

From the distinct prime divisors of `x`, it is computed as

$$
\varphi(x) = x \prod_{p \mid x}\frac{p-1}{p}.
$$

Totients are useful for counting reduced fractions and for modular arithmetic,
especially Euler's theorem. See `prime_factorization.hpp` for a longer
explanation and examples.

## Mobius Function

`mobius(x)` returns:

* `1` for `x = 1`;
* `0` when some prime square divides `x`;
* `1` or `-1` otherwise, depending on whether `x` has an even or odd number of
  distinct prime factors.

For example:

* `mobius(6) = 1` because $6 = 2 \cdot 3$ has two distinct prime factors;
* `mobius(30) = -1` because $30 = 2 \cdot 3 \cdot 5$ has three;
* `mobius(12) = 0` because $2^2$ divides `12`.

The Mobius function is mainly used for inclusion-exclusion over divisors and
for counting objects whose gcd is exactly `1`. See `prime_factorization.hpp`
for the Mobius inversion formula.

## API

```cpp
struct PrimeSieve {
    explicit PrimeSieve(int limit = 0);

    int limit() const;
    const std::vector<int>& primes() const;
    const std::vector<int>& min_prime_factors() const;

    bool is_prime(int value) const;
    int min_prime_factor(int value) const;
    std::vector<std::pair<int, int>> factorize(int value) const;
    std::vector<int> divisors(int value) const;
    int totient(int value) const;
    int mobius(int value) const;

    std::vector<int> totient_table() const;
    std::vector<int> mobius_table() const;
};
```

The limit, query arguments, primes, exponents, totients, and Mobius values all
use `int`. `is_prime` returns `bool`. The two stored-table accessors return
`const std::vector<int>&`; the reference remains valid while the sieve object
exists. Other vector-valued methods return new vectors by value.

| Method | Description | Complexity |
| --- | --- | --- |
| `limit()` | Returns the sieve limit. | $O(1)$ |
| `primes()` | Returns all primes up to the limit. | $O(1)$ |
| `min_prime_factors()` | Returns the complete smallest-prime-factor table. | $O(1)$ |
| `is_prime(x)` | Tests whether `x` is prime. | $O(1)$ |
| `min_prime_factor(x)` | Returns the smallest prime divisor of `x`. | $O(1)$ |
| `factorize(x)` | Returns `(prime, exponent)` pairs in increasing order. | $O(\log x)$ |
| `divisors(x)` | Returns all positive divisors in increasing order. | $O(d(x) \log d(x))$ |
| `totient(x)` | Returns Euler's totient function. | $O(\log x)$ |
| `mobius(x)` | Returns the Mobius function. | $O(\log x)$ |
| `totient_table()` | Returns totients for the whole sieve range. | $O(\text{limit})$ |
| `mobius_table()` | Returns Mobius values for the whole sieve range. | $O(\text{limit})$ |

Queries require their argument to be within the constructed range.

`factorize(1)` returns an empty list, while `divisors(1)` returns a list
containing only `1`.

The table methods are useful when nearly every value in the range will be
queried. Calling `totient(x)` or `mobius(x)` separately is usually preferable
for only a few values.

## When to Use This Instead of Pollard-Rho

Use `PrimeSieve` when:

* there are many queries;
* every input is at most a known, manageable limit;
* $O(\text{limit})$ memory is acceptable.

Use `prime_factorization.hpp` when inputs may be large 64-bit values. It avoids
the large table, but each factorization is more expensive.

## Example

```cpp
#include "math/prime_sieve.hpp"

#include <iostream>

int main() {
    m1une::math::PrimeSieve sieve(1000000);
    for (const auto& factor : sieve.factorize(360)) {
        std::cout << factor.first << " " << factor.second << "\n";
    }

    std::cout << sieve.totient(12) << "\n";  // 4
    std::cout << sieve.mobius(30) << "\n";   // -1
}
```
