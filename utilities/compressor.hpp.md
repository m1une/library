---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/extra_utilities.test.cpp
    title: verify/utilities/extra_utilities.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/compressor.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <initializer_list>\n#include <stdexcept>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <typename T>\n\
    struct Compressor {\n   private:\n    std::vector<T> _values;\n\n   public:\n\
    \    Compressor() = default;\n\n    explicit Compressor(std::vector<T> values)\
    \ : _values(std::move(values)) {\n        build();\n    }\n\n    Compressor(std::initializer_list<T>\
    \ values) : _values(values) {\n        build();\n    }\n\n    template <typename\
    \ Iterator>\n    Compressor(Iterator first, Iterator last) : _values(first, last)\
    \ {\n        build();\n    }\n\n    void add(const T& value) {\n        _values.push_back(value);\n\
    \    }\n\n    void build() {\n        std::sort(_values.begin(), _values.end());\n\
    \        _values.erase(std::unique(_values.begin(), _values.end()), _values.end());\n\
    \    }\n\n    int get(const T& value) const {\n        auto it = std::lower_bound(_values.begin(),\
    \ _values.end(), value);\n        if (it == _values.end() || *it != value) {\n\
    \            throw std::out_of_range(\"value is not contained in Compressor\"\
    );\n        }\n        return static_cast<int>(it - _values.begin());\n    }\n\
    \n    int lower_bound(const T& value) const {\n        return static_cast<int>(std::lower_bound(_values.begin(),\
    \ _values.end(), value) - _values.begin());\n    }\n\n    int upper_bound(const\
    \ T& value) const {\n        return static_cast<int>(std::upper_bound(_values.begin(),\
    \ _values.end(), value) - _values.begin());\n    }\n\n    bool contains(const\
    \ T& value) const {\n        auto it = std::lower_bound(_values.begin(), _values.end(),\
    \ value);\n        return it != _values.end() && *it == value;\n    }\n\n    const\
    \ T& operator[](int index) const {\n        return _values.at(index);\n    }\n\
    \n    const std::vector<T>& values() const {\n        return _values;\n    }\n\
    \n    int size() const {\n        return static_cast<int>(_values.size());\n \
    \   }\n\n    bool empty() const {\n        return _values.empty();\n    }\n};\n\
    \n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_COMPRESSOR_HPP\n#define M1UNE_COMPRESSOR_HPP 1\n\n#include\
    \ <algorithm>\n#include <initializer_list>\n#include <stdexcept>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <typename\
    \ T>\nstruct Compressor {\n   private:\n    std::vector<T> _values;\n\n   public:\n\
    \    Compressor() = default;\n\n    explicit Compressor(std::vector<T> values)\
    \ : _values(std::move(values)) {\n        build();\n    }\n\n    Compressor(std::initializer_list<T>\
    \ values) : _values(values) {\n        build();\n    }\n\n    template <typename\
    \ Iterator>\n    Compressor(Iterator first, Iterator last) : _values(first, last)\
    \ {\n        build();\n    }\n\n    void add(const T& value) {\n        _values.push_back(value);\n\
    \    }\n\n    void build() {\n        std::sort(_values.begin(), _values.end());\n\
    \        _values.erase(std::unique(_values.begin(), _values.end()), _values.end());\n\
    \    }\n\n    int get(const T& value) const {\n        auto it = std::lower_bound(_values.begin(),\
    \ _values.end(), value);\n        if (it == _values.end() || *it != value) {\n\
    \            throw std::out_of_range(\"value is not contained in Compressor\"\
    );\n        }\n        return static_cast<int>(it - _values.begin());\n    }\n\
    \n    int lower_bound(const T& value) const {\n        return static_cast<int>(std::lower_bound(_values.begin(),\
    \ _values.end(), value) - _values.begin());\n    }\n\n    int upper_bound(const\
    \ T& value) const {\n        return static_cast<int>(std::upper_bound(_values.begin(),\
    \ _values.end(), value) - _values.begin());\n    }\n\n    bool contains(const\
    \ T& value) const {\n        auto it = std::lower_bound(_values.begin(), _values.end(),\
    \ value);\n        return it != _values.end() && *it == value;\n    }\n\n    const\
    \ T& operator[](int index) const {\n        return _values.at(index);\n    }\n\
    \n    const std::vector<T>& values() const {\n        return _values;\n    }\n\
    \n    int size() const {\n        return static_cast<int>(_values.size());\n \
    \   }\n\n    bool empty() const {\n        return _values.empty();\n    }\n};\n\
    \n}  // namespace utilities\n}  // namespace m1une\n\n#endif  // M1UNE_COMPRESSOR_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/compressor.hpp
  requiredBy: []
  timestamp: '2026-06-16 01:13:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/extra_utilities.test.cpp
documentation_of: utilities/compressor.hpp
layout: document
title: Compressor
---

## Overview

Coordinate compression helper. It stores sorted unique values and maps original values to dense zero-based indices.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `Compressor()` | Creates an empty compressor. | $O(1)$ |
| `Compressor(vector<T> values)` | Builds from a vector. | $O(N \log N)$ |
| `Compressor(first, last)` | Builds from an iterator range. | $O(N \log N)$ |
| `void add(const T& value)` | Adds a value before rebuilding. | Amortized $O(1)$ |
| `void build()` | Sorts and removes duplicates. | $O(N \log N)$ |
| `int get(const T& value) const` | Returns the compressed index of an existing value. | $O(\log N)$ |
| `int lower_bound(const T& value) const` | Returns the first compressed index with value `>= value`. | $O(\log N)$ |
| `int upper_bound(const T& value) const` | Returns the first compressed index with value `> value`. | $O(\log N)$ |
| `bool contains(const T& value) const` | Returns whether the value exists. | $O(\log N)$ |
| `const T& operator[](int index) const` | Restores an original value from a compressed index. | $O(1)$ |
| `const vector<T>& values() const` | Returns all sorted unique values. | $O(1)$ |

## Example

```cpp
#include "utilities/compressor.hpp"
#include <vector>

int main() {
    std::vector<long long> xs = {100, -5, 100, 7};
    m1une::utilities::Compressor<long long> comp(xs);

    int id = comp.get(100);     // 2
    long long value = comp[id]; // 100
}
```
