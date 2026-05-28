---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':warning:'
    path: utilities/bit_ceil.hpp
    title: utilities/bit_ceil.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/segtree.hpp\"\n\n\n\n#include <vector>\n\
    #include <cassert>\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\
    \nnamespace m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies\
    \ the requirements of a Monoid.\n// A Monoid must have a `value_type`, an identity\
    \ element `id()`, and an associative binary operation `op()`.\ntemplate <typename\
    \ M>\nconcept IsMonoid = requires(typename M::value_type a, typename M::value_type\
    \ b) {\n    // 1. Must define `value_type`\n    typename M::value_type;\n    \n\
    \    // 2. Must have a static method `id()` returning `value_type`\n    { M::id()\
    \ } -> std::same_as<typename M::value_type>;\n    \n    // 3. Must have a static\
    \ method `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line\
    \ 1 \"utilities/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace utilities {\n\
    \ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 8 \"data_structure/segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\n// A generic Segment Tree\
    \ utilizing C++20 Concepts for type safety.\n// It requires a Monoid struct that\
    \ satisfies `m1une::monoid::IsMonoid`.\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct Segtree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    int _n, _size, _log;\n    std::vector<T> _d;\n\n    void update(int k) {\n\
    \        _d[k] = Monoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n   public:\n\
    \    // Constructs an empty segment tree.\n    Segtree() : Segtree(0) {}\n\n \
    \   // Constructs a segment tree of size `n`, initialized with the identity element.\n\
    \    explicit Segtree(int n) : Segtree(std::vector<T>(n, Monoid::id())) {}\n\n\
    \    // Constructs a segment tree from an existing vector.\n    explicit Segtree(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        _size = m1une::utilities::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0;\
    \ i < _n; i++) _d[_size + i] = v[i];\n        for (int i = _size - 1; i >= 1;\
    \ i--) update(i);\n    }\n\n    // Sets the value of the element at index `p`\
    \ to `x`.\n    void set(int p, T x) {\n        assert(0 <= p && p < _n);\n   \
    \     p += _size;\n        _d[p] = x;\n        for (int i = 1; i <= _log; i++)\
    \ update(p >> i);\n    }\n\n    // Returns the value of the element at index `p`.\n\
    \    T get(int p) const {\n        assert(0 <= p && p < _n);\n        return _d[p\
    \ + _size];\n    }\n\n    // Returns the product (result of the monoid operation)\
    \ in the range [l, r).\n    T prod(int l, int r) const {\n        assert(0 <=\
    \ l && l <= r && r <= _n);\n        T sml = Monoid::id(), smr = Monoid::id();\n\
    \        l += _size;\n        r += _size;\n        while (l < r) {\n         \
    \   if (l & 1) sml = Monoid::op(sml, _d[l++]);\n            if (r & 1) smr = Monoid::op(_d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n        return\
    \ Monoid::op(sml, smr);\n    }\n\n    // Returns the product of the entire array.\n\
    \    T all_prod() const { \n        return _d[1]; \n    }\n\n    // Finds the\
    \ largest `r` such that `f(prod(l, r))` is true.\n    // Uses a custom functor\
    \ or lambda `f`.\n    template <class F>\n    int max_right(int l, F f) const\
    \ {\n        assert(0 <= l && l <= _n);\n        assert(f(Monoid::id()));\n  \
    \      if (l == _n) return _n;\n        l += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            while (l % 2 == 0) l >>= 1;\n            if (!f(Monoid::op(sm,\
    \ _d[l]))) {\n                while (l < _size) {\n                    l = (2\
    \ * l);\n                    if (f(Monoid::op(sm, _d[l]))) {\n               \
    \         sm = Monoid::op(sm, _d[l]);\n                        l++;\n        \
    \            }\n                }\n                return l - _size;\n       \
    \     }\n            sm = Monoid::op(sm, _d[l]);\n            l++;\n        }\
    \ while ((l & -l) != l);\n        return _n;\n    }\n\n    // Finds the smallest\
    \ `l` such that `f(prod(l, r))` is true.\n    template <class F>\n    int min_left(int\
    \ r, F f) const {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (r == 0) return 0;\n        r += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!f(Monoid::op(_d[r], sm))) {\n                while (r < _size)\
    \ {\n                    r = (2 * r + 1);\n                    if (f(Monoid::op(_d[r],\
    \ sm))) {\n                        sm = Monoid::op(_d[r], sm);\n             \
    \           r--;\n                    }\n                }\n                return\
    \ r + 1 - _size;\n            }\n            sm = Monoid::op(_d[r], sm);\n   \
    \     } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace\
    \ data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_SEGTREE_HPP\n#define M1UNE_SEGTREE_HPP 1\n\n#include <vector>\n\
    #include <cassert>\n#include \"monoid/concept.hpp\"\n#include \"utilities/bit_ceil.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\n// A generic Segment Tree\
    \ utilizing C++20 Concepts for type safety.\n// It requires a Monoid struct that\
    \ satisfies `m1une::monoid::IsMonoid`.\ntemplate <m1une::monoid::IsMonoid Monoid>\n\
    struct Segtree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    int _n, _size, _log;\n    std::vector<T> _d;\n\n    void update(int k) {\n\
    \        _d[k] = Monoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n   public:\n\
    \    // Constructs an empty segment tree.\n    Segtree() : Segtree(0) {}\n\n \
    \   // Constructs a segment tree of size `n`, initialized with the identity element.\n\
    \    explicit Segtree(int n) : Segtree(std::vector<T>(n, Monoid::id())) {}\n\n\
    \    // Constructs a segment tree from an existing vector.\n    explicit Segtree(const\
    \ std::vector<T>& v) : _n(int(v.size())) {\n        _size = m1une::utilities::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, Monoid::id());\n        for (int i = 0;\
    \ i < _n; i++) _d[_size + i] = v[i];\n        for (int i = _size - 1; i >= 1;\
    \ i--) update(i);\n    }\n\n    // Sets the value of the element at index `p`\
    \ to `x`.\n    void set(int p, T x) {\n        assert(0 <= p && p < _n);\n   \
    \     p += _size;\n        _d[p] = x;\n        for (int i = 1; i <= _log; i++)\
    \ update(p >> i);\n    }\n\n    // Returns the value of the element at index `p`.\n\
    \    T get(int p) const {\n        assert(0 <= p && p < _n);\n        return _d[p\
    \ + _size];\n    }\n\n    // Returns the product (result of the monoid operation)\
    \ in the range [l, r).\n    T prod(int l, int r) const {\n        assert(0 <=\
    \ l && l <= r && r <= _n);\n        T sml = Monoid::id(), smr = Monoid::id();\n\
    \        l += _size;\n        r += _size;\n        while (l < r) {\n         \
    \   if (l & 1) sml = Monoid::op(sml, _d[l++]);\n            if (r & 1) smr = Monoid::op(_d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n        return\
    \ Monoid::op(sml, smr);\n    }\n\n    // Returns the product of the entire array.\n\
    \    T all_prod() const { \n        return _d[1]; \n    }\n\n    // Finds the\
    \ largest `r` such that `f(prod(l, r))` is true.\n    // Uses a custom functor\
    \ or lambda `f`.\n    template <class F>\n    int max_right(int l, F f) const\
    \ {\n        assert(0 <= l && l <= _n);\n        assert(f(Monoid::id()));\n  \
    \      if (l == _n) return _n;\n        l += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            while (l % 2 == 0) l >>= 1;\n            if (!f(Monoid::op(sm,\
    \ _d[l]))) {\n                while (l < _size) {\n                    l = (2\
    \ * l);\n                    if (f(Monoid::op(sm, _d[l]))) {\n               \
    \         sm = Monoid::op(sm, _d[l]);\n                        l++;\n        \
    \            }\n                }\n                return l - _size;\n       \
    \     }\n            sm = Monoid::op(sm, _d[l]);\n            l++;\n        }\
    \ while ((l & -l) != l);\n        return _n;\n    }\n\n    // Finds the smallest\
    \ `l` such that `f(prod(l, r))` is true.\n    template <class F>\n    int min_left(int\
    \ r, F f) const {\n        assert(0 <= r && r <= _n);\n        assert(f(Monoid::id()));\n\
    \        if (r == 0) return 0;\n        r += _size;\n        T sm = Monoid::id();\n\
    \        do {\n            r--;\n            while (r > 1 && (r % 2)) r >>= 1;\n\
    \            if (!f(Monoid::op(_d[r], sm))) {\n                while (r < _size)\
    \ {\n                    r = (2 * r + 1);\n                    if (f(Monoid::op(_d[r],\
    \ sm))) {\n                        sm = Monoid::op(_d[r], sm);\n             \
    \           r--;\n                    }\n                }\n                return\
    \ r + 1 - _size;\n            }\n            sm = Monoid::op(_d[r], sm);\n   \
    \     } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  // namespace\
    \ data_structure\n}  // namespace m1une\n\n#endif  // M1UNE_SEGTREE_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  - utilities/bit_ceil.hpp
  isVerificationFile: false
  path: data_structure/segtree.hpp
  requiredBy: []
  timestamp: '2026-05-29 02:17:41+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/segtree.hpp
layout: document
redirect_from:
- /library/data_structure/segtree.hpp
- /library/data_structure/segtree.hpp.html
title: data_structure/segtree.hpp
---
