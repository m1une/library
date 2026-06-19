---
title: Random
documentation_of: ../../utilities/random.hpp
---

## Overview

A convenience wrapper around `std::mt19937_64`. It supports deterministic seeds for reproducible stress tests and uses a chrono-based seed by default.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Random()` | Constructs a generator with a chrono-based seed. | $O(1)$ |
| `Random(unsigned long long seed)` | Constructs a generator with a fixed seed. | $O(1)$ |
| `void seed(unsigned long long value)` | Reseeds the generator. | $O(1)$ |
| `std::mt19937_64& engine()` | Returns the underlying engine. | $O(1)$ |
| `unsigned long long operator()()` | Returns the next raw generated value. | $O(1)$ |
| `long long uniform(long long l, long long r)` | Returns a uniformly random integer in the closed interval `[l, r]`. | $O(1)$ |
| `unsigned long long uniform_unsigned(unsigned long long l, unsigned long long r)` | Returns a uniformly random unsigned integer in `[l, r]`. | $O(1)$ |
| `double real(double l = 0.0, double r = 1.0)` | Returns a uniformly random real value in `[l, r)`. | $O(1)$ |
| `void shuffle(vector<T>& v)` | Shuffles a vector. | $O(N)$ |
| `void shuffle(Iterator first, Iterator last)` | Shuffles an iterator range. | $O(N)$ |
| `const T& choice(const vector<T>& v)` | Returns a random element from a non-empty vector. | $O(1)$ |

## Example

```cpp
#include "utilities/random.hpp"
#include <iostream>
#include <vector>

int main() {
    m1une::utilities::Random rng(12345);

    int x = rng.uniform(1, 6);
    double p = rng.real();

    std::vector<int> v = {1, 2, 3, 4, 5};
    rng.shuffle(v);
    std::cout << x << " " << p << " " << v.front() << "\n";
}
```
