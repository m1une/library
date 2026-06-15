---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/basic_utilities.test.cpp
    title: verify/utilities/basic_utilities.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/random.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <chrono>\n#include <random>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\nstruct Random {\n   private:\n    std::mt19937_64 _engine;\n\n\
    \    static unsigned long long chrono_seed() {\n        return static_cast<unsigned\
    \ long long>(\n            std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    }\n\n   public:\n    Random() : _engine(chrono_seed()) {}\n    explicit Random(unsigned\
    \ long long seed) : _engine(seed) {}\n\n    void seed(unsigned long long value)\
    \ {\n        _engine.seed(value);\n    }\n\n    std::mt19937_64& engine() {\n\
    \        return _engine;\n    }\n\n    unsigned long long operator()() {\n   \
    \     return _engine();\n    }\n\n    long long uniform(long long l, long long\
    \ r) {\n        return std::uniform_int_distribution<long long>(l, r)(_engine);\n\
    \    }\n\n    unsigned long long uniform_unsigned(unsigned long long l, unsigned\
    \ long long r) {\n        return std::uniform_int_distribution<unsigned long long>(l,\
    \ r)(_engine);\n    }\n\n    double real(double l = 0.0, double r = 1.0) {\n \
    \       return std::uniform_real_distribution<double>(l, r)(_engine);\n    }\n\
    \n    template <typename T>\n    void shuffle(std::vector<T>& v) {\n        std::shuffle(v.begin(),\
    \ v.end(), _engine);\n    }\n\n    template <typename Iterator>\n    void shuffle(Iterator\
    \ first, Iterator last) {\n        std::shuffle(first, last, _engine);\n    }\n\
    \n    template <typename T>\n    const T& choice(const std::vector<T>& v) {\n\
    \        return v[uniform(0, static_cast<long long>(v.size()) - 1)];\n    }\n\
    };\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_RANDOM_HPP\n#define M1UNE_RANDOM_HPP 1\n\n#include <algorithm>\n\
    #include <chrono>\n#include <random>\n#include <vector>\n\nnamespace m1une {\n\
    namespace utilities {\n\nstruct Random {\n   private:\n    std::mt19937_64 _engine;\n\
    \n    static unsigned long long chrono_seed() {\n        return static_cast<unsigned\
    \ long long>(\n            std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    }\n\n   public:\n    Random() : _engine(chrono_seed()) {}\n    explicit Random(unsigned\
    \ long long seed) : _engine(seed) {}\n\n    void seed(unsigned long long value)\
    \ {\n        _engine.seed(value);\n    }\n\n    std::mt19937_64& engine() {\n\
    \        return _engine;\n    }\n\n    unsigned long long operator()() {\n   \
    \     return _engine();\n    }\n\n    long long uniform(long long l, long long\
    \ r) {\n        return std::uniform_int_distribution<long long>(l, r)(_engine);\n\
    \    }\n\n    unsigned long long uniform_unsigned(unsigned long long l, unsigned\
    \ long long r) {\n        return std::uniform_int_distribution<unsigned long long>(l,\
    \ r)(_engine);\n    }\n\n    double real(double l = 0.0, double r = 1.0) {\n \
    \       return std::uniform_real_distribution<double>(l, r)(_engine);\n    }\n\
    \n    template <typename T>\n    void shuffle(std::vector<T>& v) {\n        std::shuffle(v.begin(),\
    \ v.end(), _engine);\n    }\n\n    template <typename Iterator>\n    void shuffle(Iterator\
    \ first, Iterator last) {\n        std::shuffle(first, last, _engine);\n    }\n\
    \n    template <typename T>\n    const T& choice(const std::vector<T>& v) {\n\
    \        return v[uniform(0, static_cast<long long>(v.size()) - 1)];\n    }\n\
    };\n\n}  // namespace utilities\n}  // namespace m1une\n\n#endif  // M1UNE_RANDOM_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/random.hpp
  requiredBy: []
  timestamp: '2026-06-15 23:35:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/basic_utilities.test.cpp
documentation_of: utilities/random.hpp
layout: document
title: Random
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
#include <vector>

int main() {
    m1une::utilities::Random rng(12345);

    int x = rng.uniform(1, 6);
    double p = rng.real();

    std::vector<int> v = {1, 2, 3, 4, 5};
    rng.shuffle(v);
}
```
