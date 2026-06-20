---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: ds/range_query/sparse_table.hpp
    title: Sparse Table
  - icon: ':question:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/min.hpp
    title: Min Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"verify/ds/range_query/sparse_table.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#line 1 \"ds/range_query/sparse_table.hpp\"\
    \n\n\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n\n  \
    \  // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 11 \"ds/range_query/sparse_table.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A Sparse Table utilizing C++20 Concepts\
    \ for type safety.\n// It requires a Monoid struct that satisfies `m1une::monoid::IsMonoid`.\n\
    // [IMPORTANT] For O(1) range queries to work correctly, the monoid operation\
    \ MUST be idempotent.\n// i.e., Monoid::op(x, x) == x must hold (e.g., Min, Max,\
    \ GCD, Bitwise AND/OR).\ntemplate <m1une::monoid::IsMonoid Monoid>\nstruct SparseTable\
    \ {\n    using T = typename Monoid::value_type;\n\n   private:\n    int _n;\n\
    \    std::vector<std::vector<T>> _st;\n\n   public:\n    // Constructs an empty\
    \ sparse table.\n    SparseTable() : _n(0) {}\n\n    // Constructs a sparse table\
    \ from an existing vector in O(N log N) time.\n    explicit SparseTable(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n \
    \       // Compute the maximum power of 2 needed\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        // Initialize\
    \ the base level\n        for (int i = 0; i < _n; i++) {\n            _st[0][i]\
    \ = v[i];\n        }\n\n        // Build the sparse table\n        for (int k\
    \ = 1; k < max_log; k++) {\n            for (int i = 0; i + (1 << k) <= _n; i++)\
    \ {\n                _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 <<\
    \ (k - 1))]);\n            }\n        }\n    }\n    explicit SparseTable(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        if (_n == 0) return;\n\n        int max_log\
    \ = std::bit_width((unsigned int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\
    \n        for (int i = 0; i < _n; i++) {\n            _st[0][i] = std::move(v[i]);\n\
    \        }\n\n        for (int k = 1; k < max_log; k++) {\n            for (int\
    \ i = 0; i + (1 << k) <= _n; i++) {\n                _st[k][i] = Monoid::op(_st[k\
    \ - 1][i], _st[k - 1][i + (1 << (k - 1))]);\n            }\n        }\n    }\n\
    \n    // Constructs a sparse table from a vector of a different type U.\n    //\
    \ It automatically adapts to the Monoid's initialization requirements:\n    //\
    \ 1. Monoid::make(val) if it exists.\n    // 2. Monoid::make(val, index) if the\
    \ monoid requires global indices.\n    // 3. static_cast<T>(val) as a fallback\
    \ for simple monoids.\n    template <typename U>\n    requires (!std::same_as<U,\
    \ T>) && (\n        requires(U x) { Monoid::make(x); } ||\n        requires(U\
    \ x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U, T>\n  \
    \  )\n    explicit SparseTable(const std::vector<U>& v) : _n(int(v.size())) {\n\
    \        if (_n == 0) return;\n\n        int max_log = std::bit_width((unsigned\
    \ int)_n);\n        _st.assign(max_log, std::vector<T>(_n));\n\n        // Compile-time\
    \ branching based on the available make() signature\n        for (int i = 0; i\
    \ < _n; i++) {\n            if constexpr (requires(U x) { Monoid::make(x); })\
    \ {\n                _st[0][i] = Monoid::make(v[i]);\n            } else if constexpr\
    \ (requires(U x, int idx) { Monoid::make(x, idx); }) {\n                _st[0][i]\
    \ = Monoid::make(v[i], i);\n            } else {\n                _st[0][i] =\
    \ static_cast<T>(v[i]);\n            }\n        }\n        for (int k = 1; k <\
    \ max_log; k++) {\n            for (int i = 0; i + (1 << k) <= _n; i++) {\n  \
    \              _st[k][i] = Monoid::op(_st[k - 1][i], _st[k - 1][i + (1 << (k -\
    \ 1))]);\n            }\n        }\n    }\n\n    // Returns the product (result\
    \ of the monoid operation) in the range [l, r) in O(1) time.\n    // Requires\
    \ the monoid operation to be idempotent.\n    T prod(int l, int r) const {\n \
    \       assert(0 <= l && l <= r && r <= _n);\n        if (l == r) return Monoid::id();\n\
    \n        // Calculate the largest power of 2 less than or equal to the interval\
    \ length\n        int k = std::bit_width((unsigned int)(r - l)) - 1;\n       \
    \ return Monoid::op(_st[k][l], _st[k][r - (1 << k)]);\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 1 \"monoid/min.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <limits>\n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for minimum\
    \ (Range Minimum).\n// The identity element defaults to the maximum possible value\
    \ of type T, but can be overridden.\ntemplate <typename T, T Id = std::numeric_limits<T>::max()>\n\
    struct Min {\n    using value_type = T;\n\n    // Returns the identity element\
    \ for minimum.\n    static constexpr T id() {\n        return Id;\n    }\n\n \
    \   // Returns the minimum of a and b.\n    static constexpr T op(const T& a,\
    \ const T& b) {\n        return std::min(a, b);\n    }\n};\n\n}  // namespace\
    \ monoid\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/range_query/sparse_table.test.cpp\"\
    \n\n#include <iostream>\n#line 8 \"verify/ds/range_query/sparse_table.test.cpp\"\
    \n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    }\n\nint main() {\n    fast_io();\n\n    int N, Q;\n    std::cin >> N >> Q;\n\n\
    \    std::vector<long long> A(N);\n    for (int i = 0; i < N; ++i) {\n       \
    \ std::cin >> A[i];\n    }\n\n    m1une::ds::SparseTable<m1une::monoid::Min<long\
    \ long>> st(A);\n\n    for (int q = 0; q < Q; ++q) {\n        int l, r;\n    \
    \    std::cin >> l >> r;\n\n        std::cout << st.prod(l, r) << \"\\n\";\n \
    \   }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"../../../ds/range_query/sparse_table.hpp\"\n#include \"../../../monoid/min.hpp\"\
    \n\n#include <iostream>\n#include <vector>\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n}\n\nint main() {\n    fast_io();\n\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n\n    std::vector<long long> A(N);\n    for (int i =\
    \ 0; i < N; ++i) {\n        std::cin >> A[i];\n    }\n\n    m1une::ds::SparseTable<m1une::monoid::Min<long\
    \ long>> st(A);\n\n    for (int q = 0; q < Q; ++q) {\n        int l, r;\n    \
    \    std::cin >> l >> r;\n\n        std::cout << st.prod(l, r) << \"\\n\";\n \
    \   }\n\n    return 0;\n}\n"
  dependsOn:
  - ds/range_query/sparse_table.hpp
  - monoid/concept.hpp
  - monoid/min.hpp
  isVerificationFile: true
  path: verify/ds/range_query/sparse_table.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/sparse_table.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/sparse_table.test.cpp
- /verify/verify/ds/range_query/sparse_table.test.cpp.html
title: verify/ds/range_query/sparse_table.test.cpp
---
