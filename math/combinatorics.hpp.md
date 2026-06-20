---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/all.hpp
    title: Math All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/math/math_algorithms.test.cpp
    title: verify/math/math_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/combinatorics.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstdint>\n#include <vector>\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <class Mint>\nstruct Combinatorics {\n   private:\n    std::vector<Mint> _factorial;\n\
    \    std::vector<Mint> _inverse_factorial;\n\n   public:\n    explicit Combinatorics(int\
    \ maximum = 0)\n        : _factorial(1, Mint(1)), _inverse_factorial(1, Mint(1))\
    \ {\n        ensure(maximum);\n    }\n\n    int maximum() const {\n        return\
    \ int(_factorial.size()) - 1;\n    }\n\n    void ensure(int maximum) {\n     \
    \   assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum) < Mint::mod());\n\
    \        if (maximum <= this->maximum()) return;\n\n        const int old_maximum\
    \ = this->maximum();\n        _factorial.resize(maximum + 1);\n        _inverse_factorial.resize(maximum\
    \ + 1);\n        for (int i = old_maximum + 1; i <= maximum; i++) {\n        \
    \    _factorial[i] = _factorial[i - 1] * Mint(i);\n        }\n        _inverse_factorial[maximum]\
    \ = _factorial[maximum].inv();\n        for (int i = maximum; i > old_maximum;\
    \ i--) {\n            _inverse_factorial[i - 1] = _inverse_factorial[i] * Mint(i);\n\
    \        }\n    }\n\n    Mint factorial(int n) const {\n        assert(0 <= n\
    \ && n <= maximum());\n        return _factorial[n];\n    }\n\n    Mint inverse_factorial(int\
    \ n) const {\n        assert(0 <= n && n <= maximum());\n        return _inverse_factorial[n];\n\
    \    }\n\n    Mint inverse(int n) const {\n        assert(1 <= n && n <= maximum());\n\
    \        return _factorial[n - 1] * _inverse_factorial[n];\n    }\n\n    Mint\
    \ binom(int n, int k) const {\n        if (k < 0 || k > n) return Mint(0);\n \
    \       assert(n <= maximum());\n        return _factorial[n] * _inverse_factorial[k]\
    \ * _inverse_factorial[n - k];\n    }\n\n    Mint perm(int n, int k) const {\n\
    \        if (k < 0 || k > n) return Mint(0);\n        assert(n <= maximum());\n\
    \        return _factorial[n] * _inverse_factorial[n - k];\n    }\n\n    Mint\
    \ multiset(int types, int count) const {\n        if (types < 0 || count < 0)\
    \ return Mint(0);\n        if (types == 0) return Mint(count == 0);\n        const\
    \ long long total = static_cast<long long>(types) + count - 1;\n        assert(total\
    \ <= maximum());\n        return binom(static_cast<int>(total), count);\n    }\n\
    };\n\n}  // namespace math\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MATH_COMBINATORICS_HPP\n#define M1UNE_MATH_COMBINATORICS_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <class Mint>\nstruct Combinatorics {\n\
    \   private:\n    std::vector<Mint> _factorial;\n    std::vector<Mint> _inverse_factorial;\n\
    \n   public:\n    explicit Combinatorics(int maximum = 0)\n        : _factorial(1,\
    \ Mint(1)), _inverse_factorial(1, Mint(1)) {\n        ensure(maximum);\n    }\n\
    \n    int maximum() const {\n        return int(_factorial.size()) - 1;\n    }\n\
    \n    void ensure(int maximum) {\n        assert(maximum >= 0);\n        assert(static_cast<uint64_t>(maximum)\
    \ < Mint::mod());\n        if (maximum <= this->maximum()) return;\n\n       \
    \ const int old_maximum = this->maximum();\n        _factorial.resize(maximum\
    \ + 1);\n        _inverse_factorial.resize(maximum + 1);\n        for (int i =\
    \ old_maximum + 1; i <= maximum; i++) {\n            _factorial[i] = _factorial[i\
    \ - 1] * Mint(i);\n        }\n        _inverse_factorial[maximum] = _factorial[maximum].inv();\n\
    \        for (int i = maximum; i > old_maximum; i--) {\n            _inverse_factorial[i\
    \ - 1] = _inverse_factorial[i] * Mint(i);\n        }\n    }\n\n    Mint factorial(int\
    \ n) const {\n        assert(0 <= n && n <= maximum());\n        return _factorial[n];\n\
    \    }\n\n    Mint inverse_factorial(int n) const {\n        assert(0 <= n &&\
    \ n <= maximum());\n        return _inverse_factorial[n];\n    }\n\n    Mint inverse(int\
    \ n) const {\n        assert(1 <= n && n <= maximum());\n        return _factorial[n\
    \ - 1] * _inverse_factorial[n];\n    }\n\n    Mint binom(int n, int k) const {\n\
    \        if (k < 0 || k > n) return Mint(0);\n        assert(n <= maximum());\n\
    \        return _factorial[n] * _inverse_factorial[k] * _inverse_factorial[n -\
    \ k];\n    }\n\n    Mint perm(int n, int k) const {\n        if (k < 0 || k >\
    \ n) return Mint(0);\n        assert(n <= maximum());\n        return _factorial[n]\
    \ * _inverse_factorial[n - k];\n    }\n\n    Mint multiset(int types, int count)\
    \ const {\n        if (types < 0 || count < 0) return Mint(0);\n        if (types\
    \ == 0) return Mint(count == 0);\n        const long long total = static_cast<long\
    \ long>(types) + count - 1;\n        assert(total <= maximum());\n        return\
    \ binom(static_cast<int>(total), count);\n    }\n};\n\n}  // namespace math\n\
    }  // namespace m1une\n\n#endif  // M1UNE_MATH_COMBINATORICS_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: math/combinatorics.hpp
  requiredBy:
  - math/all.hpp
  timestamp: '2026-06-20 09:06:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/math/math_algorithms.test.cpp
documentation_of: math/combinatorics.hpp
layout: document
title: Combinatorics
---

## Overview

`Combinatorics<Mint>` precomputes factorials and inverse factorials for
constant-time binomial coefficients, permutations, modular inverses, and
multiset combinations.

These operations answer common counting questions:

* How many ways can `k` objects be chosen from `n` objects?
* How many ways can `k` distinct positions be filled from `n` choices?
* How many ways can identical objects be distributed among several kinds?

`Mint` must provide the static-modulus interface used by `ModInt`, and the
modulus must be prime. The largest prepared index must be smaller than the
modulus.

## Mathematical Meaning

The factorial of `n` is

$$
n! = 1 \cdot 2 \cdot 3 \cdots n,
$$

with $0! = 1$.

### Binomial Coefficients

`binom(n, k)` computes

$$
\binom{n}{k} = \frac{n!}{k!(n-k)!}.
$$

This counts ways to choose `k` items from `n` distinct items when order does not
matter. For example, choosing two people from Alice, Bob, and Carol gives
$\binom{3}{2} = 3$ choices.

### Permutations

`perm(n, k)` computes

$$
P(n,k) = \frac{n!}{(n-k)!}.
$$

This counts ordered selections. Choosing a gold and silver medalist from three
people gives $P(3,2) = 6$, because Alice then Bob differs from Bob then Alice.

### Multiset Combinations

`multiset(types, count)` computes

$$
\binom{\text{types}+\text{count}-1}{\text{count}}.
$$

This counts ways to choose `count` items from `types` kinds when repetitions are
allowed and order does not matter. For example, choosing four scoops from three
ice-cream flavors gives $\binom{6}{4} = 15$ possibilities.

This is also called the stars-and-bars formula. It frequently appears when
counting nonnegative integer solutions of

$$
x_1 + x_2 + \cdots + x_k = n.
$$

There are `multiset(k, n)` such solutions.

## Why Inverse Factorials Are Used

Ordinary integer division cannot be used after taking a remainder. Under a
prime modulus, division by a nonzero value is multiplication by its modular
inverse. The class therefore stores both `n!` and the modular inverse of `n!`,
allowing each formula above to be evaluated in constant time.

For example, modulo a prime `mod`,

```text
binom(n, k) = factorial[n]
              * inverse_factorial[k]
              * inverse_factorial[n - k]
              modulo mod.
```

## API

| Method | Description | Complexity |
| --- | --- | --- |
| `Combinatorics(maximum)` | Prepares every value through `maximum`. | $O(\text{maximum} + \log \text{mod})$ |
| `ensure(maximum)` | Extends the prepared range when needed. | $O(\text{new maximum} - \text{old maximum} + \log \text{mod})$ |
| `maximum()` | Returns the largest prepared index. | $O(1)$ |
| `factorial(n)` | Returns `n!`. | $O(1)$ |
| `inverse_factorial(n)` | Returns the inverse of `n!`. | $O(1)$ |
| `inverse(n)` | Returns the modular inverse of `n`. | $O(1)$ |
| `binom(n, k)` | Returns the binomial coefficient. Invalid `k` returns zero. | $O(1)$ |
| `perm(n, k)` | Returns the number of ordered selections. Invalid `k` returns zero. | $O(1)$ |
| `multiset(types, count)` | Returns the number of multisets of size `count` from `types` kinds. | $O(1)$ |

## Preconditions and Common Pitfalls

* Call the constructor or `ensure` with at least the largest `n` that a later
  query will use.
* The modulus must be prime.
* Every prepared index must be smaller than the modulus. Otherwise its
  factorial is zero modulo the modulus and cannot be inverted.
* `binom(n, k)` and `perm(n, k)` return zero when `k < 0` or `k > n`.
* This class does not directly handle huge `n` with small `k`, or combinations
  modulo a composite number.

## Example

```cpp
#include "math/combinatorics.hpp"
#include "math/modint.hpp"

#include <iostream>

int main() {
    using mint = m1une::math::modint998244353;
    m1une::math::Combinatorics<mint> combinations(100);

    std::cout << combinations.binom(5, 2) << "\n";     // 10
    std::cout << combinations.perm(5, 2) << "\n";      // 20
    std::cout << combinations.multiset(3, 4) << "\n";  // 15
}
```
