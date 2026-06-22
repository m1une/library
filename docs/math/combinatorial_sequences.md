---
title: Combinatorial Sequences
documentation_of: ../../math/combinatorial_sequences.hpp
---

## Overview

This header generates several standard counting sequences:

* Catalan numbers;
* Bernoulli numbers;
* Bell numbers;
* Stirling numbers of the second kind;
* integer partition numbers;
* derangement numbers.

Every function returns a vector of modular values. Except for the Stirling
function, requesting `maximum` returns every value from index `0` through
`maximum`.

The Bernoulli, Bell, Stirling, and partition implementations use formal power
series and fast convolution. They are suitable for hundreds of thousands of
terms, rather than only the small sizes supported by quadratic dynamic
programming.

## Catalan Numbers

The `n`-th Catalan number is

$$
C_n = \frac{1}{n+1}\binom{2n}{n}.
$$

The first values are:

```text
n:   0  1  2  3   4   5
C_n: 1  1  2  5  14  42
```

Catalan numbers count many equivalent structures, including:

* balanced parenthesis strings containing `n` pairs;
* binary tree shapes with `n` internal vertices;
* ways to triangulate a convex polygon with `n + 2` vertices;
* monotone grid paths that never cross above the diagonal.

For example, the two balanced strings with two pairs are:

```text
()()
(())
```

`catalan_numbers<Mint>(maximum)` computes the sequence in $O(\text{maximum})$
time using

$$
C_{n+1}
= C_n \frac{2(2n+1)}{n+2}.
$$

If a `Combinatorics<Mint>` object already contains factorials through `2 * n`,
its `catalan(n)` method returns one Catalan number in $O(1)$ time.

## Bernoulli Numbers

Bernoulli numbers are rational numbers defined by the exponential generating
function

$$
\frac{x}{e^x-1}
= \sum_{n=0}^{\infty} B_n \frac{x^n}{n!}.
$$

This header uses the convention

$$
B_1 = -\frac{1}{2}.
$$

The first values are:

```text
B_0 = 1
B_1 = -1/2
B_2 = 1/6
B_3 = 0
B_4 = -1/30
B_5 = 0
B_6 = 1/42
```

Bernoulli numbers do not directly count a simple family of objects. Their most
common contest use is evaluating sums of powers. For example,

$$
1^p + 2^p + \cdots + n^p
= \frac{1}{p+1}
  \sum_{j=0}^{p}
  (-1)^j \binom{p+1}{j} B_j n^{p+1-j}.
$$

They also appear in finite differences, polynomial interpolation, and advanced
number theory.

The returned values are modular representations of the rational numbers.
For example, `B_1` is `-1 * inverse(2)` modulo `Mint::mod()`.

`bernoulli_numbers<Mint>(maximum)` computes all terms in
$O(\text{maximum} \log \text{maximum})$ time by inverting the series

$$
\frac{e^x-1}{x}
= \sum_{n=0}^{\infty}\frac{x^n}{(n+1)!}.
$$

## Stirling Numbers of the Second Kind

The Stirling number of the second kind $S(n,k)$ counts ways to divide a set of
`n` distinct elements into exactly `k` nonempty, unlabeled groups.

For the set containing `a`, `b`, and `c`:

* $S(3,1)=1$: all elements are in one group;
* $S(3,2)=3$: one element is alone and the other two are together;
* $S(3,3)=1$: every element is alone.

The row for `n = 5` is:

```text
k:       0  1   2   3   4  5
S(5,k):  0  1  15  25  10  1
```

`stirling_numbers_second_kind<Mint>(n)` returns this entire row. It uses the
convolution identity

$$
S(n,k)
= \sum_{i=0}^{k}
  \frac{(-1)^{k-i} i^n}{i!(k-i)!}
$$

and runs in $O(n \log n)$ time.

## Bell Numbers

The Bell number counts ways to divide a set of `n` distinct elements into any
number of nonempty, unlabeled groups.

The first values are:

```text
n:       0  1  2  3   4   5
Bell_n:  1  1  2  5  15  52
```

Bell numbers and Stirling numbers are related by

$$
\operatorname{Bell}_n = \sum_{k=0}^{n} S(n,k).
$$

Their exponential generating function is

$$
\exp(e^x-1)
= \sum_{n=0}^{\infty}
  \operatorname{Bell}_n \frac{x^n}{n!}.
$$

`bell_numbers<Mint>(maximum)` evaluates this series in
$O(\text{maximum} \log \text{maximum})$ time.

Bernoulli numbers and Bell numbers are both traditionally written as `B_n`,
but they are unrelated sequences. The API uses distinct function names to
avoid that ambiguity.

## Integer Partition Numbers

The partition number $p(n)$ counts ways to write `n` as a sum of positive
integers when order does not matter.

For example, $p(5)=7$:

```text
5
4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1
```

This is different from a Bell number: integer partitions split an integer,
while Bell numbers split a set of distinct elements.

The generating function is

$$
\prod_{k=1}^{\infty}\frac{1}{1-x^k}
= \sum_{n=0}^{\infty}p(n)x^n.
$$

Euler's pentagonal number theorem gives a sparse denominator, which the
implementation inverts with formal power series. Therefore
`partition_numbers<Mint>(maximum)` runs in
$O(\text{maximum} \log \text{maximum})$ time.

## Derangements

A derangement is a permutation in which no element remains in its original
position.

For three elements, the two derangements are:

```text
2 3 1
3 1 2
```

The first values are:

```text
n:    0  1  2  3  4   5
D_n:  1  0  1  2  9  44
```

The sequence satisfies

$$
D_n = (n-1)(D_{n-1}+D_{n-2}).
$$

`derangement_numbers<Mint>(maximum)` uses this recurrence and runs in
$O(\text{maximum})$ time.

## API

```cpp
template <class Mint>
std::vector<Mint> catalan_numbers(int maximum);

template <class Mint>
std::vector<Mint> bernoulli_numbers(int maximum);

template <class Mint>
std::vector<Mint> bell_numbers(int maximum);

template <class Mint>
std::vector<Mint> stirling_numbers_second_kind(int n);

template <class Mint>
std::vector<Mint> partition_numbers(int maximum);

template <class Mint>
std::vector<Mint> derangement_numbers(int maximum);
```

The template argument `Mint` is the element type of the returned
`std::vector<Mint>`. The function argument is an `int` and must be
nonnegative. Except for Stirling numbers, a call with `maximum` returns a
vector of length `maximum + 1`. The Stirling function returns a vector of
length `n + 1`.

| Function | Returned values | Complexity |
| --- | --- | --- |
| `catalan_numbers<Mint>(maximum)` | `C_0` through `C_maximum` | $O(n)$ |
| `bernoulli_numbers<Mint>(maximum)` | `B_0` through `B_maximum` | $O(n \log n)$ |
| `bell_numbers<Mint>(maximum)` | Bell numbers `0` through `maximum` | $O(n \log n)$ |
| `stirling_numbers_second_kind<Mint>(n)` | `S(n, 0)` through `S(n, n)` | $O(n \log n)$ |
| `partition_numbers<Mint>(maximum)` | `p(0)` through `p(maximum)` | $O(n \log n)$ |
| `derangement_numbers<Mint>(maximum)` | `D_0` through `D_maximum` | $O(n)$ |

Every function uses $O(n)$ memory.

## Requirements

The fast formulas are intended for a static modular integer such as
`modint998244353`.

* The modulus should be prime for Catalan, Bernoulli, Bell, and Stirling
  numbers because the algorithms use modular inverses.
* `maximum + 1` must be smaller than the modulus for Catalan and Bernoulli
  numbers.
* `maximum` must be smaller than the modulus for Bell and Stirling numbers.
* The formal-power-series transform length must be supported by the convolution
  implementation. Modulus `998244353` is the standard fast choice.

These functions return residues modulo `Mint::mod()`, not arbitrary-precision
integers.

## Example

```cpp
#include "math/combinatorial_sequences.hpp"
#include "math/modint.hpp"

#include <iostream>

using Mint = m1une::math::modint998244353;

int main() {
    auto catalan = m1une::math::catalan_numbers<Mint>(10);
    auto bernoulli = m1une::math::bernoulli_numbers<Mint>(10);
    auto partitions = m1une::math::partition_numbers<Mint>(10);

    std::cout << catalan[5] << "\n";     // 42
    std::cout << bernoulli[1] * 2 << "\n";  // -1 modulo 998244353
    std::cout << partitions[5] << "\n";  // 7
}
```
