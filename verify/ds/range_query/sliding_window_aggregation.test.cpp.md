---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sliding_window_aggregation.hpp
    title: Sliding Window Aggregation
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"verify/ds/range_query/sliding_window_aggregation.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#line 1 \"ds/range_query/sliding_window_aggregation.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <utility>\n#include <vector>\n\n#line\
    \ 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace\
    \ monoid {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n// Concept for commutative\
    \ group monoids.\n// A type satisfying this concept must also obey commutativity\
    \ and inverse laws.\ntemplate <typename M>\nconcept IsCommutativeGroup = IsMonoid<M>\
    \ && requires(typename M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line\
    \ 10 \"ds/range_query/sliding_window_aggregation.hpp\"\n\nnamespace m1une {\n\
    namespace ds {\n\n// A queue supporting the ordered product of all elements in\
    \ amortized O(1).\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct SlidingWindowAggregation\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    struct Entry\
    \ {\n        T value;\n        T product;\n    };\n\n    std::vector<Entry> _front;\n\
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
    \n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/sliding_window_aggregation.test.cpp\"\
    \n\n#line 6 \"verify/ds/range_query/sliding_window_aggregation.test.cpp\"\n#include\
    \ <cstdint>\n#include <deque>\n#include <iostream>\n#include <string>\n#line 11\
    \ \"verify/ds/range_query/sliding_window_aggregation.test.cpp\"\n\nnamespace {\n\
    \nstruct Concat {\n    using value_type = std::string;\n\n    static value_type\
    \ id() {\n        return \"\";\n    }\n\n    static value_type op(const value_type&\
    \ first, const value_type& second) {\n        return first + second;\n    }\n\
    };\n\nconstexpr long long mod = 998244353;\n\nstruct Affine {\n    struct value_type\
    \ {\n        long long a;\n        long long b;\n    };\n\n    static value_type\
    \ id() {\n        return value_type{1, 0};\n    }\n\n    static value_type op(const\
    \ value_type& first, const value_type& second) {\n        return value_type{\n\
    \            second.a * first.a % mod,\n            (second.a * first.b + second.b)\
    \ % mod,\n        };\n    }\n};\n\nvoid test_fixed() {\n    m1une::ds::Swag<Concat>\
    \ queue;\n    assert(queue.empty());\n    assert(queue.prod().empty());\n\n  \
    \  queue.reserve(10);\n    queue.push(\"a\");\n    queue.push_back(\"b\");\n \
    \   queue.push(\"c\");\n    assert(queue.size() == 3);\n    assert(queue.front()\
    \ == \"a\");\n    assert(queue.back() == \"c\");\n    assert(queue.prod() == \"\
    abc\");\n\n    queue.pop();\n    assert(queue.front() == \"b\");\n    assert(queue.prod()\
    \ == \"bc\");\n    queue.push(\"d\");\n    assert(queue.all_prod() == \"bcd\"\
    );\n    queue.pop_front();\n    assert(queue.prod() == \"cd\");\n\n    queue.clear();\n\
    \    assert(queue.empty());\n    assert(queue.all_prod().empty());\n\n    std::vector<std::string>\
    \ values = {\"x\", \"y\", \"z\"};\n    m1une::ds::SlidingWindowAggregation<Concat>\
    \ built(values);\n    assert(built.prod() == \"xyz\");\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 809;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    m1une::ds::Swag<Concat> queue;\n    std::deque<std::string> expected;\n\
    \    for (int operation = 0; operation < 50000; ++operation) {\n        if (expected.empty()\
    \ || random() % 3 != 0) {\n            std::string value(1, char('a' + random()\
    \ % 5));\n            queue.push(value);\n            expected.push_back(value);\n\
    \        } else {\n            queue.pop();\n            expected.pop_front();\n\
    \        }\n\n        assert(queue.size() == expected.size());\n        assert(queue.empty()\
    \ == expected.empty());\n        std::string product;\n        for (const std::string&\
    \ value : expected) product += value;\n        assert(queue.prod() == product);\n\
    \        if (!expected.empty()) {\n            assert(queue.front() == expected.front());\n\
    \            assert(queue.back() == expected.back());\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n\
    \    int query_count;\n    std::cin >> query_count;\n    m1une::ds::Swag<Affine>\
    \ queue;\n    while (query_count--) {\n        int type;\n        std::cin >>\
    \ type;\n        if (type == 0) {\n            Affine::value_type function;\n\
    \            std::cin >> function.a >> function.b;\n            queue.push(function);\n\
    \        } else if (type == 1) {\n            queue.pop();\n        } else {\n\
    \            long long x;\n            std::cin >> x;\n            auto function\
    \ = queue.prod();\n            std::cout << (function.a * x + function.b) % mod\
    \ << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include \"../../../ds/range_query/sliding_window_aggregation.hpp\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <deque>\n#include <iostream>\n#include\
    \ <string>\n#include <vector>\n\nnamespace {\n\nstruct Concat {\n    using value_type\
    \ = std::string;\n\n    static value_type id() {\n        return \"\";\n    }\n\
    \n    static value_type op(const value_type& first, const value_type& second)\
    \ {\n        return first + second;\n    }\n};\n\nconstexpr long long mod = 998244353;\n\
    \nstruct Affine {\n    struct value_type {\n        long long a;\n        long\
    \ long b;\n    };\n\n    static value_type id() {\n        return value_type{1,\
    \ 0};\n    }\n\n    static value_type op(const value_type& first, const value_type&\
    \ second) {\n        return value_type{\n            second.a * first.a % mod,\n\
    \            (second.a * first.b + second.b) % mod,\n        };\n    }\n};\n\n\
    void test_fixed() {\n    m1une::ds::Swag<Concat> queue;\n    assert(queue.empty());\n\
    \    assert(queue.prod().empty());\n\n    queue.reserve(10);\n    queue.push(\"\
    a\");\n    queue.push_back(\"b\");\n    queue.push(\"c\");\n    assert(queue.size()\
    \ == 3);\n    assert(queue.front() == \"a\");\n    assert(queue.back() == \"c\"\
    );\n    assert(queue.prod() == \"abc\");\n\n    queue.pop();\n    assert(queue.front()\
    \ == \"b\");\n    assert(queue.prod() == \"bc\");\n    queue.push(\"d\");\n  \
    \  assert(queue.all_prod() == \"bcd\");\n    queue.pop_front();\n    assert(queue.prod()\
    \ == \"cd\");\n\n    queue.clear();\n    assert(queue.empty());\n    assert(queue.all_prod().empty());\n\
    \n    std::vector<std::string> values = {\"x\", \"y\", \"z\"};\n    m1une::ds::SlidingWindowAggregation<Concat>\
    \ built(values);\n    assert(built.prod() == \"xyz\");\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 809;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    m1une::ds::Swag<Concat> queue;\n    std::deque<std::string> expected;\n\
    \    for (int operation = 0; operation < 50000; ++operation) {\n        if (expected.empty()\
    \ || random() % 3 != 0) {\n            std::string value(1, char('a' + random()\
    \ % 5));\n            queue.push(value);\n            expected.push_back(value);\n\
    \        } else {\n            queue.pop();\n            expected.pop_front();\n\
    \        }\n\n        assert(queue.size() == expected.size());\n        assert(queue.empty()\
    \ == expected.empty());\n        std::string product;\n        for (const std::string&\
    \ value : expected) product += value;\n        assert(queue.prod() == product);\n\
    \        if (!expected.empty()) {\n            assert(queue.front() == expected.front());\n\
    \            assert(queue.back() == expected.back());\n        }\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n\
    \    int query_count;\n    std::cin >> query_count;\n    m1une::ds::Swag<Affine>\
    \ queue;\n    while (query_count--) {\n        int type;\n        std::cin >>\
    \ type;\n        if (type == 0) {\n            Affine::value_type function;\n\
    \            std::cin >> function.a >> function.b;\n            queue.push(function);\n\
    \        } else if (type == 1) {\n            queue.pop();\n        } else {\n\
    \            long long x;\n            std::cin >> x;\n            auto function\
    \ = queue.prod();\n            std::cout << (function.a * x + function.b) % mod\
    \ << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/range_query/sliding_window_aggregation.hpp
  - monoid/concept.hpp
  isVerificationFile: true
  path: verify/ds/range_query/sliding_window_aggregation.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:38:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/sliding_window_aggregation.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/sliding_window_aggregation.test.cpp
- /verify/verify/ds/range_query/sliding_window_aggregation.test.cpp.html
title: verify/ds/range_query/sliding_window_aggregation.test.cpp
---
