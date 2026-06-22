---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/range_query/sliding_window_aggregation.test.cpp
    title: verify/ds/range_query/sliding_window_aggregation.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/range_query/sliding_window_aggregation.hpp\"\n\n\n\n\
    #include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 10 \"ds/range_query/sliding_window_aggregation.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A queue supporting the ordered product\
    \ of all elements in amortized O(1).\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct SlidingWindowAggregation {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Entry {\n        T value;\n        T product;\n    };\n\
    \n    std::vector<Entry> _front;\n    std::vector<Entry> _back;\n\n    void move_to_front()\
    \ {\n        if (!_front.empty()) return;\n        while (!_back.empty()) {\n\
    \            T value = std::move(_back.back().value);\n            _back.pop_back();\n\
    \            T product = _front.empty() ? value : Monoid::op(value, _front.back().product);\n\
    \            _front.push_back(Entry{\n                std::move(value),\n    \
    \            std::move(product),\n            });\n        }\n    }\n\n   public:\n\
    \    SlidingWindowAggregation() = default;\n\n    explicit SlidingWindowAggregation(const\
    \ std::vector<T>& values) {\n        reserve(values.size());\n        for (const\
    \ T& value : values) push(value);\n    }\n\n    explicit SlidingWindowAggregation(std::vector<T>&&\
    \ values) {\n        reserve(values.size());\n        for (T& value : values)\
    \ push(std::move(value));\n    }\n\n    std::size_t size() const {\n        return\
    \ _front.size() + _back.size();\n    }\n\n    bool empty() const {\n        return\
    \ _front.empty() && _back.empty();\n    }\n\n    void reserve(std::size_t capacity)\
    \ {\n        _front.reserve(capacity);\n        _back.reserve(capacity);\n   \
    \ }\n\n    void clear() {\n        _front.clear();\n        _back.clear();\n \
    \   }\n\n    void push(T value) {\n        T product = _back.empty() ? value :\
    \ Monoid::op(_back.back().product, value);\n        _back.push_back(Entry{\n \
    \           std::move(value),\n            std::move(product),\n        });\n\
    \    }\n\n    void push_back(T value) {\n        push(std::move(value));\n   \
    \ }\n\n    // Removes the oldest element.\n    void pop() {\n        assert(!empty());\n\
    \        move_to_front();\n        _front.pop_back();\n    }\n\n    void pop_front()\
    \ {\n        pop();\n    }\n\n    const T& front() {\n        assert(!empty());\n\
    \        move_to_front();\n        return _front.back().value;\n    }\n\n    const\
    \ T& back() const {\n        assert(!empty());\n        if (!_back.empty()) return\
    \ _back.back().value;\n        return _front.front().value;\n    }\n\n    // Returns\
    \ the product in queue order, or the identity when empty.\n    T prod() const\
    \ {\n        if (_front.empty()) {\n            return _back.empty() ? Monoid::id()\
    \ : _back.back().product;\n        }\n        if (_back.empty()) return _front.back().product;\n\
    \        return Monoid::op(_front.back().product, _back.back().product);\n   \
    \ }\n\n    T all_prod() const {\n        return prod();\n    }\n};\n\ntemplate\
    \ <m1une::monoid::IsMonoid Monoid>\nusing Swag = SlidingWindowAggregation<Monoid>;\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_HPP\n#define M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\
    \n#include \"../../monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\
    \n// A queue supporting the ordered product of all elements in amortized O(1).\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct SlidingWindowAggregation {\n\
    \    using T = typename Monoid::value_type;\n\n   private:\n    struct Entry {\n\
    \        T value;\n        T product;\n    };\n\n    std::vector<Entry> _front;\n\
    \    std::vector<Entry> _back;\n\n    void move_to_front() {\n        if (!_front.empty())\
    \ return;\n        while (!_back.empty()) {\n            T value = std::move(_back.back().value);\n\
    \            _back.pop_back();\n            T product = _front.empty() ? value\
    \ : Monoid::op(value, _front.back().product);\n            _front.push_back(Entry{\n\
    \                std::move(value),\n                std::move(product),\n    \
    \        });\n        }\n    }\n\n   public:\n    SlidingWindowAggregation() =\
    \ default;\n\n    explicit SlidingWindowAggregation(const std::vector<T>& values)\
    \ {\n        reserve(values.size());\n        for (const T& value : values) push(value);\n\
    \    }\n\n    explicit SlidingWindowAggregation(std::vector<T>&& values) {\n \
    \       reserve(values.size());\n        for (T& value : values) push(std::move(value));\n\
    \    }\n\n    std::size_t size() const {\n        return _front.size() + _back.size();\n\
    \    }\n\n    bool empty() const {\n        return _front.empty() && _back.empty();\n\
    \    }\n\n    void reserve(std::size_t capacity) {\n        _front.reserve(capacity);\n\
    \        _back.reserve(capacity);\n    }\n\n    void clear() {\n        _front.clear();\n\
    \        _back.clear();\n    }\n\n    void push(T value) {\n        T product\
    \ = _back.empty() ? value : Monoid::op(_back.back().product, value);\n       \
    \ _back.push_back(Entry{\n            std::move(value),\n            std::move(product),\n\
    \        });\n    }\n\n    void push_back(T value) {\n        push(std::move(value));\n\
    \    }\n\n    // Removes the oldest element.\n    void pop() {\n        assert(!empty());\n\
    \        move_to_front();\n        _front.pop_back();\n    }\n\n    void pop_front()\
    \ {\n        pop();\n    }\n\n    const T& front() {\n        assert(!empty());\n\
    \        move_to_front();\n        return _front.back().value;\n    }\n\n    const\
    \ T& back() const {\n        assert(!empty());\n        if (!_back.empty()) return\
    \ _back.back().value;\n        return _front.front().value;\n    }\n\n    // Returns\
    \ the product in queue order, or the identity when empty.\n    T prod() const\
    \ {\n        if (_front.empty()) {\n            return _back.empty() ? Monoid::id()\
    \ : _back.back().product;\n        }\n        if (_back.empty()) return _front.back().product;\n\
    \        return Monoid::op(_front.back().product, _back.back().product);\n   \
    \ }\n\n    T all_prod() const {\n        return prod();\n    }\n};\n\ntemplate\
    \ <m1une::monoid::IsMonoid Monoid>\nusing Swag = SlidingWindowAggregation<Monoid>;\n\
    \n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_DS_RANGE_QUERY_SLIDING_WINDOW_AGGREGATION_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/range_query/sliding_window_aggregation.hpp
  requiredBy: []
  timestamp: '2026-06-23 02:38:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/range_query/sliding_window_aggregation.test.cpp
documentation_of: ds/range_query/sliding_window_aggregation.hpp
layout: document
title: Sliding Window Aggregation
---

## Overview

`SlidingWindowAggregation<Monoid>` maintains a queue and the monoid product of
all its elements. It is commonly called SWAG.

Elements are stored in two aggregate stacks. Each element moves from the back
stack to the front stack at most once, giving amortized constant-time queue
operations.

`Swag<Monoid>` is a shorter alias.

## Ordering

The product follows queue order:

$$
a_0 \mathbin{\mathrm{op}} a_1 \mathbin{\mathrm{op}} \cdots
\mathbin{\mathrm{op}} a_{n-1}.
$$

The monoid does not need to be commutative. This matters for affine-function
composition, matrices, and string concatenation.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `push(value)`, `push_back(value)` | Appends an element. | Amortized $O(1)$ |
| `pop()`, `pop_front()` | Removes the oldest element. | Amortized $O(1)$ |
| `front()` | Returns the oldest element. | Amortized $O(1)$ |
| `back()` | Returns the newest element. | $O(1)$ |
| `prod()`, `all_prod()` | Returns the ordered product, or the identity when empty. | $O(1)$ |
| `size()` | Returns the number of elements. | $O(1)$ |
| `empty()` | Returns whether the queue is empty. | $O(1)$ |
| `clear()` | Removes every element. | $O(N)$ |
| `reserve(capacity)` | Reserves both internal stacks. | $O(N)$ |

`pop`, `pop_front`, `front`, and `back` require a nonempty queue.

## Example

This finds the minimum in every window of length three:

```cpp
#include "ds/range_query/sliding_window_aggregation.hpp"
#include "monoid/min.hpp"

#include <iostream>
#include <vector>

int main() {
    std::vector<int> values = {4, 2, 5, 1, 3};
    m1une::ds::Swag<m1une::monoid::Min<int>> window;

    for (int index = 0; index < int(values.size()); index++) {
        window.push(values[index]);
        if (window.size() > 3) window.pop();
        if (window.size() == 3) std::cout << window.prod() << "\n";
    }
}
```
