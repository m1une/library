---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: utilities/bit_ceil.hpp
    title: utilities/bit_ceil.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: Segment Tree
    links: []
  bundledCode: "#line 1 \"data_structure/segtree/segtree.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <functional>\n#include <type_traits>\n#include <vector>\n\n#line 1 \"\
    utilities/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\ntemplate <typename T>\nconstexpr\
    \ T bit_ceil(T n) {\n    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n)\
    \ x <<= 1;\n    return x;\n}\n}  // namespace m1une\n\n\n#line 10 \"data_structure/segtree/segtree.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename Monoid>\nstruct segment_tree {\n \
    \   using T = typename Monoid::value_type;\n\n   private:\n    int _n;\n    int\
    \ _size;\n    std::vector<T> _data;\n\n    void update(int k) {\n        _data[k]\
    \ = Monoid::op(_data[2 * k], _data[2 * k + 1]);\n    }\n\n   public:\n    segment_tree()\
    \ : segment_tree(0) {}\n    explicit segment_tree(int n) : segment_tree(std::vector<T>(n,\
    \ Monoid::e())) {}\n    explicit segment_tree(const std::vector<T>& v) : _n(v.size())\
    \ {\n        _size = bit_ceil((unsigned int)_n);\n        _data.assign(2 * _size,\
    \ Monoid::e());\n        for (int i = 0; i < _n; i++) {\n            _data[_size\
    \ + i] = v[i];\n        }\n        for (int i = _size - 1; i >= 1; i--) {\n  \
    \          update(i);\n        }\n    }\n\n    // Set value at position p\n  \
    \  void set(int p, T x) {\n        p += _size;\n        _data[p] = x;\n      \
    \  for (int i = 1; p >> i >= 1; i++) {\n            update(p >> i);\n        }\n\
    \    }\n\n    // Get value at position p\n    T get(int p) const {\n        return\
    \ _data[p + _size];\n    }\n\n    // Product of range [l, r)\n    T prod(int l,\
    \ int r) const {\n        T sml = Monoid::e(), smr = Monoid::e();\n        l +=\
    \ _size;\n        r += _size;\n        while (l < r) {\n            if (l & 1)\
    \ sml = Monoid::op(sml, _data[l++]);\n            if (r & 1) smr = Monoid::op(_data[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n        return\
    \ Monoid::op(sml, smr);\n    }\n\n    // Product of the whole range\n    T all_prod()\
    \ const {\n        return _data[1];\n    }\n\n    // Find max_right r such that\
    \ f(prod([l, r))) is true\n    int max_right(int l, auto f) const {\n        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (l == _n) return _n;\n        l += _size;\n\
    \        T sm = Monoid::e();\n        do {\n            while (l % 2 == 0) l >>=\
    \ 1;\n            if (!f(Monoid::op(sm, _data[l]))) {\n                while (l\
    \ < _size) {\n                    l = (2 * l);\n                    if (f(Monoid::op(sm,\
    \ _data[l]))) {\n                        sm = Monoid::op(sm, _data[l]);\n    \
    \                    l++;\n                    }\n                }\n        \
    \        return l - _size;\n            }\n            sm = Monoid::op(sm, _data[l]);\n\
    \            l++;\n        } while ((l & -l) != l);\n        return _n;\n    }\n\
    \n    // Find min_left l such that f(prod([l, r))) is true\n    int min_left(int\
    \ r, auto f) const {\n        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (r == 0) return 0;\n        r += _size;\n\
    \        T sm = Monoid::e();\n        do {\n            r--;\n            while\
    \ (r > 1 && (r % 2)) r >>= 1;\n            if (!f(Monoid::op(_data[r], sm))) {\n\
    \                while (r < _size) {\n                    r = (2 * r + 1);\n \
    \                   if (f(Monoid::op(_data[r], sm))) {\n                     \
    \   sm = Monoid::op(_data[r], sm);\n                        r--;\n           \
    \         }\n                }\n                return r + 1 - _size;\n      \
    \      }\n            sm = Monoid::op(_data[r], sm);\n        } while ((r & -r)\
    \ != r);\n        return 0;\n    }\n};\n\n}  // namespace m1une\n\n\n\n/**\n *\
    \ @brief Segment Tree\n */\n"
  code: "#ifndef M1UNE_SEGTREE_HPP\n#define M1UNE_SEGTREE_HPP 1\n\n#include <algorithm>\n\
    #include <functional>\n#include <type_traits>\n#include <vector>\n\n#include \"\
    ../../utilities/bit_ceil.hpp\"\n\nnamespace m1une {\n\ntemplate <typename Monoid>\n\
    struct segment_tree {\n    using T = typename Monoid::value_type;\n\n   private:\n\
    \    int _n;\n    int _size;\n    std::vector<T> _data;\n\n    void update(int\
    \ k) {\n        _data[k] = Monoid::op(_data[2 * k], _data[2 * k + 1]);\n    }\n\
    \n   public:\n    segment_tree() : segment_tree(0) {}\n    explicit segment_tree(int\
    \ n) : segment_tree(std::vector<T>(n, Monoid::e())) {}\n    explicit segment_tree(const\
    \ std::vector<T>& v) : _n(v.size()) {\n        _size = bit_ceil((unsigned int)_n);\n\
    \        _data.assign(2 * _size, Monoid::e());\n        for (int i = 0; i < _n;\
    \ i++) {\n            _data[_size + i] = v[i];\n        }\n        for (int i\
    \ = _size - 1; i >= 1; i--) {\n            update(i);\n        }\n    }\n\n  \
    \  // Set value at position p\n    void set(int p, T x) {\n        p += _size;\n\
    \        _data[p] = x;\n        for (int i = 1; p >> i >= 1; i++) {\n        \
    \    update(p >> i);\n        }\n    }\n\n    // Get value at position p\n   \
    \ T get(int p) const {\n        return _data[p + _size];\n    }\n\n    // Product\
    \ of range [l, r)\n    T prod(int l, int r) const {\n        T sml = Monoid::e(),\
    \ smr = Monoid::e();\n        l += _size;\n        r += _size;\n        while\
    \ (l < r) {\n            if (l & 1) sml = Monoid::op(sml, _data[l++]);\n     \
    \       if (r & 1) smr = Monoid::op(_data[--r], smr);\n            l >>= 1;\n\
    \            r >>= 1;\n        }\n        return Monoid::op(sml, smr);\n    }\n\
    \n    // Product of the whole range\n    T all_prod() const {\n        return\
    \ _data[1];\n    }\n\n    // Find max_right r such that f(prod([l, r))) is true\n\
    \    int max_right(int l, auto f) const {\n        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (l == _n) return _n;\n        l += _size;\n\
    \        T sm = Monoid::e();\n        do {\n            while (l % 2 == 0) l >>=\
    \ 1;\n            if (!f(Monoid::op(sm, _data[l]))) {\n                while (l\
    \ < _size) {\n                    l = (2 * l);\n                    if (f(Monoid::op(sm,\
    \ _data[l]))) {\n                        sm = Monoid::op(sm, _data[l]);\n    \
    \                    l++;\n                    }\n                }\n        \
    \        return l - _size;\n            }\n            sm = Monoid::op(sm, _data[l]);\n\
    \            l++;\n        } while ((l & -l) != l);\n        return _n;\n    }\n\
    \n    // Find min_left l such that f(prod([l, r))) is true\n    int min_left(int\
    \ r, auto f) const {\n        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (r == 0) return 0;\n        r += _size;\n\
    \        T sm = Monoid::e();\n        do {\n            r--;\n            while\
    \ (r > 1 && (r % 2)) r >>= 1;\n            if (!f(Monoid::op(_data[r], sm))) {\n\
    \                while (r < _size) {\n                    r = (2 * r + 1);\n \
    \                   if (f(Monoid::op(_data[r], sm))) {\n                     \
    \   sm = Monoid::op(_data[r], sm);\n                        r--;\n           \
    \         }\n                }\n                return r + 1 - _size;\n      \
    \      }\n            sm = Monoid::op(_data[r], sm);\n        } while ((r & -r)\
    \ != r);\n        return 0;\n    }\n};\n\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_SEGTREE_HPP\n\n/**\n * @brief Segment Tree\n */\n"
  dependsOn:
  - utilities/bit_ceil.hpp
  isVerificationFile: false
  path: data_structure/segtree/segtree.hpp
  requiredBy: []
  timestamp: '2025-09-28 20:54:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/segtree/segtree.hpp
layout: document
redirect_from:
- /library/data_structure/segtree/segtree.hpp
- /library/data_structure/segtree/segtree.hpp.html
title: Segment Tree
---
