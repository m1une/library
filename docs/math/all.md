---
title: Math All
documentation_of: ../../math/all.hpp
---

## Overview

`math/all.hpp` includes every general math header in this directory.

## Choosing a Header

You usually do not need to include this entire bundle:

* Use `modint.hpp` for arithmetic modulo a fixed number such as `998244353`.
* Use `bitwise_convolution.hpp` for OR, AND, or XOR convolution over mask
  indices.
* Use `zeta_mobius_transform.hpp` for subset, superset, divisor, and multiple
  transforms.
* Use `combinatorics.hpp` for many factorial, combination, or permutation
  queries under a prime modulus.
* Use `lucas.hpp` for binomial coefficients with huge arguments modulo a small
  prime.
* Use `combinatorial_sequences.hpp` for Catalan, Bernoulli, Bell, Stirling,
  partition, or derangement numbers.
* Use `prime_sieve.hpp` when all queried integers are at most a manageable
  limit, usually a few million or tens of millions.
* Use `prime_factorization.hpp` for isolated 64-bit integers that are too large
  for a sieve.
* Use `number_theory.hpp` for modular inverses, simultaneous remainder
  constraints, and sums involving floor division.
* Use `integer_arithmetic.hpp` for exact integer square roots and powers.
* Use `rational.hpp` for normalized exact fractions.

`math/all.hpp` is convenient during a contest when compile time and including a
few unused headers do not matter.

## Included Headers

| Header | Contents |
| --- | --- |
| `math/bitwise_convolution.hpp` | OR, AND, XOR convolutions and the Walsh-Hadamard transform. |
| `math/bit_ceil.hpp` | Smallest power of two at least a given value. |
| `math/integer_arithmetic.hpp` | Exact integer square roots and overflow-aware powers. |
| `math/lucas.hpp` | Lucas's theorem for huge binomial arguments modulo a small prime. |
| `math/modint.hpp` | Static modular integer type. |
| `math/combinatorics.hpp` | Factorials, binomial coefficients, permutations, and multiset counts. |
| `math/combinatorial_sequences.hpp` | Fast standard counting sequences and special numbers. |
| `math/number_theory.hpp` | Modular power and inverse, CRT, and floor sum. |
| `math/prime_sieve.hpp` | Linear sieve with smallest prime factors. |
| `math/prime_factorization.hpp` | Deterministic 64-bit primality test and Pollard-Rho factorization. |
| `math/rational.hpp` | Exact normalized rational arithmetic over signed integers. |
| `math/zeta_mobius_transform.hpp` | Subset, superset, divisor, and multiple zeta/Mobius transforms. |
