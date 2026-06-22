---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sqrt_decomposition.hpp
    title: Square-Root Decomposition
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
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"verify/ds/range_query/sqrt_decomposition.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\n\n#line\
    \ 1 \"ds/range_query/sqrt_decomposition.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cmath>\n#include <concepts>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 12 \"ds/range_query/sqrt_decomposition.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// Mutable square-root decomposition\
    \ for point assignments and range products.\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct SqrtDecomposition {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n    std::vector<T>\
    \ _values;\n    std::vector<T> _block_product;\n\n    template <class U>\n   \
    \ static T make_value(const U& value, int index) {\n        if constexpr (requires(U\
    \ x) { Monoid::make(x); }) {\n            return Monoid::make(value);\n      \
    \  } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {\n    \
    \        return Monoid::make(value, index);\n        } else {\n            return\
    \ static_cast<T>(value);\n        }\n    }\n\n    void initialize_blocks() {\n\
    \        if (_n == 0) {\n            _block_size = 1;\n            _block_count\
    \ = 0;\n            _block_product.clear();\n            return;\n        }\n\
    \        _block_size = std::max(\n            1,\n            int(std::sqrt(static_cast<long\
    \ double>(_n)))\n        );\n        while (1LL * _block_size * _block_size <\
    \ _n) ++_block_size;\n        _block_count = (_n + _block_size - 1) / _block_size;\n\
    \        _block_product.assign(_block_count, Monoid::id());\n        for (int\
    \ block = 0; block < _block_count; ++block) {\n            rebuild_block(block);\n\
    \        }\n    }\n\n    void rebuild_block(int block) {\n        assert(0 <=\
    \ block && block < _block_count);\n        int left = block * _block_size;\n \
    \       int right = std::min(_n, left + _block_size);\n        T product = Monoid::id();\n\
    \        for (int index = left; index < right; ++index) {\n            product\
    \ = Monoid::op(product, _values[index]);\n        }\n        _block_product[block]\
    \ = std::move(product);\n    }\n\n   public:\n    SqrtDecomposition()\n      \
    \  : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit SqrtDecomposition(int\
    \ n)\n        : _n(n), _block_size(1), _block_count(0), _values(n, Monoid::id())\
    \ {\n        assert(0 <= n);\n        initialize_blocks();\n    }\n\n    explicit\
    \ SqrtDecomposition(const std::vector<T>& values)\n        : _n(int(values.size())),\n\
    \          _block_size(1),\n          _block_count(0),\n          _values(values)\
    \ {\n        initialize_blocks();\n    }\n\n    explicit SqrtDecomposition(std::vector<T>&&\
    \ values)\n        : _n(int(values.size())),\n          _block_size(1),\n    \
    \      _block_count(0),\n          _values(std::move(values)) {\n        initialize_blocks();\n\
    \    }\n\n    template <class U>\n    requires (!std::same_as<U, T>) && (\n  \
    \      requires(U x) { Monoid::make(x); } ||\n        requires(U x, int i) { Monoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit SqrtDecomposition(const\
    \ std::vector<U>& values)\n        : _n(int(values.size())),\n          _block_size(1),\n\
    \          _block_count(0),\n          _values(values.size(), Monoid::id()) {\n\
    \        for (int index = 0; index < _n; ++index) {\n            _values[index]\
    \ = make_value(values[index], index);\n        }\n        initialize_blocks();\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    int block_count() const {\n        return\
    \ _block_count;\n    }\n\n    int block_of(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        return index / _block_size;\n    }\n\n   \
    \ std::pair<int, int> block_range(int block) const {\n        assert(0 <= block\
    \ && block < _block_count);\n        int left = block * _block_size;\n       \
    \ return {left, std::min(_n, left + _block_size)};\n    }\n\n    const std::vector<T>&\
    \ values() const {\n        return _values;\n    }\n\n    const std::vector<T>&\
    \ block_products() const {\n        return _block_product;\n    }\n\n    const\
    \ T& get(int index) const {\n        assert(0 <= index && index < _n);\n     \
    \   return _values[index];\n    }\n\n    const T& operator[](int index) const\
    \ {\n        return get(index);\n    }\n\n    // Assigns one element and rebuilds\
    \ its block.\n    void set(int index, T value) {\n        assert(0 <= index &&\
    \ index < _n);\n        _values[index] = std::move(value);\n        rebuild_block(block_of(index));\n\
    \    }\n\n    // Returns the ordered monoid product over [left, right).\n    T\
    \ prod(int left, int right) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        T result = Monoid::id();\n        while (left < right\
    \ && left % _block_size != 0) {\n            result = Monoid::op(result, _values[left++]);\n\
    \        }\n        while (left + _block_size <= right) {\n            result\
    \ = Monoid::op(\n                result,\n                _block_product[left\
    \ / _block_size]\n            );\n            left += _block_size;\n        }\n\
    \        while (left < right) {\n            result = Monoid::op(result, _values[left++]);\n\
    \        }\n        return result;\n    }\n\n    T all_prod() const {\n      \
    \  T result = Monoid::id();\n        for (const T& product : _block_product) {\n\
    \            result = Monoid::op(result, product);\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4\
    \ \"verify/ds/range_query/sqrt_decomposition.test.cpp\"\n\n#line 6 \"verify/ds/range_query/sqrt_decomposition.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#include <string>\n#line 10 \"verify/ds/range_query/sqrt_decomposition.test.cpp\"\
    \n\nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n  \
    \  static value_type id() {\n        return \"\";\n    }\n\n    static value_type\
    \ op(const value_type& first, const value_type& second) {\n        return first\
    \ + second;\n    }\n};\n\nconstexpr long long mod = 998244353;\n\nstruct Affine\
    \ {\n    struct value_type {\n        long long a;\n        long long b;\n   \
    \ };\n\n    static value_type id() {\n        return value_type{1, 0};\n    }\n\
    \n    static value_type op(const value_type& first, const value_type& second)\
    \ {\n        return value_type{\n            second.a * first.a % mod,\n     \
    \       (second.a * first.b + second.b) % mod,\n        };\n    }\n};\n\nvoid\
    \ test_fixed() {\n    m1une::ds::SqrtDecomposition<Concat> empty;\n    assert(empty.empty());\n\
    \    assert(empty.prod(0, 0).empty());\n\n    std::vector<std::string> values\
    \ = {\"a\", \"b\", \"c\", \"d\", \"e\"};\n    m1une::ds::SqrtDecomposition<Concat>\
    \ blocks(values);\n    assert(blocks.prod(0, 5) == \"abcde\");\n    assert(blocks.prod(1,\
    \ 4) == \"bcd\");\n    blocks.set(2, \"x\");\n    assert(blocks.prod(0, 5) ==\
    \ \"abxde\");\n    assert(blocks.all_prod() == \"abxde\");\n\n    for (int block\
    \ = 0; block < blocks.block_count(); ++block) {\n        auto range = blocks.block_range(block);\n\
    \        std::string expected;\n        for (int index = range.first; index <\
    \ range.second; ++index) {\n            expected += blocks[index];\n         \
    \   assert(blocks.block_of(index) == block);\n        }\n        assert(blocks.block_products()[block]\
    \ == expected);\n    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state\
    \ = 701;\n    auto random = [&state]() {\n        state ^= state << 7;\n     \
    \   state ^= state >> 9;\n        return state;\n    };\n\n    for (int trial\
    \ = 0; trial < 2000; ++trial) {\n        int size = int(random() % 180);\n   \
    \     std::vector<std::string> values(size);\n        for (std::string& value\
    \ : values) {\n            value = char('a' + random() % 5);\n        }\n    \
    \    m1une::ds::SqrtDecomposition<Concat> blocks(values);\n\n        for (int\
    \ operation = 0; operation < 300; ++operation) {\n            if (size != 0 &&\
    \ random() % 3 == 0) {\n                int index = int(random() % size);\n  \
    \              std::string value(1, char('a' + random() % 5));\n             \
    \   values[index] = value;\n                blocks.set(index, value);\n      \
    \      } else {\n                int left = int(random() % (size + 1));\n    \
    \            int right = int(random() % (size + 1));\n                if (right\
    \ < left) std::swap(left, right);\n                std::string expected;\n   \
    \             for (int index = left; index < right; ++index) {\n             \
    \       expected += values[index];\n                }\n                assert(blocks.prod(left,\
    \ right) == expected);\n            }\n        }\n    }\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n\n    int n, q;\n \
    \   std::cin >> n >> q;\n    std::vector<Affine::value_type> values(n);\n    for\
    \ (auto& value : values) std::cin >> value.a >> value.b;\n    m1une::ds::SqrtDecomposition<Affine>\
    \ blocks(values);\n\n    while (q--) {\n        int type;\n        std::cin >>\
    \ type;\n        if (type == 0) {\n            int index;\n            Affine::value_type\
    \ value;\n            std::cin >> index >> value.a >> value.b;\n            blocks.set(index,\
    \ value);\n        } else {\n            int left, right;\n            long long\
    \ x;\n            std::cin >> left >> right >> x;\n            auto function =\
    \ blocks.prod(left, right);\n            std::cout << (function.a * x + function.b)\
    \ % mod << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include \"../../../ds/range_query/sqrt_decomposition.hpp\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <string>\n#include <vector>\n\
    \nnamespace {\n\nstruct Concat {\n    using value_type = std::string;\n\n    static\
    \ value_type id() {\n        return \"\";\n    }\n\n    static value_type op(const\
    \ value_type& first, const value_type& second) {\n        return first + second;\n\
    \    }\n};\n\nconstexpr long long mod = 998244353;\n\nstruct Affine {\n    struct\
    \ value_type {\n        long long a;\n        long long b;\n    };\n\n    static\
    \ value_type id() {\n        return value_type{1, 0};\n    }\n\n    static value_type\
    \ op(const value_type& first, const value_type& second) {\n        return value_type{\n\
    \            second.a * first.a % mod,\n            (second.a * first.b + second.b)\
    \ % mod,\n        };\n    }\n};\n\nvoid test_fixed() {\n    m1une::ds::SqrtDecomposition<Concat>\
    \ empty;\n    assert(empty.empty());\n    assert(empty.prod(0, 0).empty());\n\n\
    \    std::vector<std::string> values = {\"a\", \"b\", \"c\", \"d\", \"e\"};\n\
    \    m1une::ds::SqrtDecomposition<Concat> blocks(values);\n    assert(blocks.prod(0,\
    \ 5) == \"abcde\");\n    assert(blocks.prod(1, 4) == \"bcd\");\n    blocks.set(2,\
    \ \"x\");\n    assert(blocks.prod(0, 5) == \"abxde\");\n    assert(blocks.all_prod()\
    \ == \"abxde\");\n\n    for (int block = 0; block < blocks.block_count(); ++block)\
    \ {\n        auto range = blocks.block_range(block);\n        std::string expected;\n\
    \        for (int index = range.first; index < range.second; ++index) {\n    \
    \        expected += blocks[index];\n            assert(blocks.block_of(index)\
    \ == block);\n        }\n        assert(blocks.block_products()[block] == expected);\n\
    \    }\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 701;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 2000;\
    \ ++trial) {\n        int size = int(random() % 180);\n        std::vector<std::string>\
    \ values(size);\n        for (std::string& value : values) {\n            value\
    \ = char('a' + random() % 5);\n        }\n        m1une::ds::SqrtDecomposition<Concat>\
    \ blocks(values);\n\n        for (int operation = 0; operation < 300; ++operation)\
    \ {\n            if (size != 0 && random() % 3 == 0) {\n                int index\
    \ = int(random() % size);\n                std::string value(1, char('a' + random()\
    \ % 5));\n                values[index] = value;\n                blocks.set(index,\
    \ value);\n            } else {\n                int left = int(random() % (size\
    \ + 1));\n                int right = int(random() % (size + 1));\n          \
    \      if (right < left) std::swap(left, right);\n                std::string\
    \ expected;\n                for (int index = left; index < right; ++index) {\n\
    \                    expected += values[index];\n                }\n         \
    \       assert(blocks.prod(left, right) == expected);\n            }\n       \
    \ }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<Affine::value_type>\
    \ values(n);\n    for (auto& value : values) std::cin >> value.a >> value.b;\n\
    \    m1une::ds::SqrtDecomposition<Affine> blocks(values);\n\n    while (q--) {\n\
    \        int type;\n        std::cin >> type;\n        if (type == 0) {\n    \
    \        int index;\n            Affine::value_type value;\n            std::cin\
    \ >> index >> value.a >> value.b;\n            blocks.set(index, value);\n   \
    \     } else {\n            int left, right;\n            long long x;\n     \
    \       std::cin >> left >> right >> x;\n            auto function = blocks.prod(left,\
    \ right);\n            std::cout << (function.a * x + function.b) % mod << '\\\
    n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/range_query/sqrt_decomposition.hpp
  - monoid/concept.hpp
  isVerificationFile: true
  path: verify/ds/range_query/sqrt_decomposition.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:29:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/sqrt_decomposition.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/sqrt_decomposition.test.cpp
- /verify/verify/ds/range_query/sqrt_decomposition.test.cpp.html
title: verify/ds/range_query/sqrt_decomposition.test.cpp
---
