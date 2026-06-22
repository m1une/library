---
title: Combinatorics
documentation_of: ../../math/combinatorics.hpp
---

## Overview

`Combinatorics<Mint>` precomputes factorials and inverse factorials for
constant-time binomial coefficients, permutations, modular inverses, and
multiset combinations.

These operations answer common counting questions:

* How many ways can `k` objects be chosen from `n` objects?
* How many ways can `k` distinct positions be filled from `n` choices?
* How many ways can identical objects be distributed among several kinds?
* How many balanced parenthesis strings contain `n` pairs?

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

### Catalan Numbers

`catalan(n)` computes

$$
C_n
= \frac{1}{n+1}\binom{2n}{n}
= \binom{2n}{n}-\binom{2n}{n+1}.
$$

It counts balanced parenthesis strings with `n` pairs, binary tree shapes, and
many other recursively nested structures. The first values are
`1, 1, 2, 5, 14, 42`.

This method requires factorials through `2 * n`. To generate every Catalan
number through a limit in linear time, use `catalan_numbers` from
`math/combinatorial_sequences.hpp`.

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

```cpp
template <class Mint>
struct Combinatorics {
    explicit Combinatorics(int maximum = 0);

    int maximum() const;
    void ensure(int maximum);

    Mint factorial(int n) const;
    Mint inverse_factorial(int n) const;
    Mint inverse(int n) const;
    Mint binom(int n, int k) const;
    Mint perm(int n, int k) const;
    Mint multiset(int types, int count) const;
    Mint catalan(int n) const;
};
```

`Mint` is the return type of every arithmetic query. All indices and counts use
`int`. `ensure` modifies the precomputed tables and returns `void`; the other
methods shown as `const` do not modify the object.

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
| `catalan(n)` | Returns the `n`-th Catalan number. | $O(1)$ |

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
    std::cout << combinations.catalan(5) << "\n";      // 42
}
```
