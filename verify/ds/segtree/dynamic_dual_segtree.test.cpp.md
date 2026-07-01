---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_dual_segtree.hpp
    title: Dynamic Dual Segment Tree
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dynamic_segtree_common.hpp
    title: ds/segtree/dynamic_segtree_common.hpp
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/affine.hpp
    title: Affine Monoid
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
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_point_get
    links:
    - https://judge.yosupo.jp/problem/range_affine_point_get
  bundledCode: "#line 1 \"verify/ds/segtree/dynamic_dual_segtree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/range_affine_point_get\"\n\n#line\
    \ 1 \"ds/segtree/dynamic_dual_segtree.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <concepts>\n#include <cstddef>\n#include <limits>\n#include <numeric>\n#include\
    \ <type_traits>\n#include <utility>\n#include <vector>\n\n#line 1 \"ds/segtree/dynamic_segtree_common.hpp\"\
    \n\n\n\n#line 11 \"ds/segtree/dynamic_segtree_common.hpp\"\n\nnamespace m1une\
    \ {\nnamespace ds {\nnamespace detail {\n\ntemplate <std::integral Index>\nusing\
    \ dynamic_size_type = std::make_unsigned_t<Index>;\n\ntemplate <std::integral\
    \ Index>\nconstexpr dynamic_size_type<Index> dynamic_distance(Index left, Index\
    \ right) {\n    return static_cast<dynamic_size_type<Index>>(right) - static_cast<dynamic_size_type<Index>>(left);\n\
    }\n\ntemplate <class Monoid, class Size>\ntypename Monoid::value_type monoid_repeat(typename\
    \ Monoid::value_type value, Size count) {\n    typename Monoid::value_type result\
    \ = Monoid::id();\n    while (count != 0) {\n        if (count & 1) result = Monoid::op(result,\
    \ value);\n        count >>= 1;\n        if (count != 0) value = Monoid::op(value,\
    \ value);\n    }\n    return result;\n}\n\ntemplate <class ActedMonoid>\ntypename\
    \ ActedMonoid::value_type dynamic_mapping(\n    const typename ActedMonoid::operator_type&\
    \ f,\n    const typename ActedMonoid::value_type& value\n) {\n    using F = typename\
    \ ActedMonoid::operator_type;\n    using T = typename ActedMonoid::value_type;\n\
    \    if constexpr (requires(F g, T x, long long ord) { ActedMonoid::mapping(g,\
    \ x, ord); }) {\n        return ActedMonoid::mapping(f, value, 0);\n    } else\
    \ {\n        return ActedMonoid::mapping(f, value);\n    }\n}\n\ntemplate <class\
    \ ActedMonoid, class Size>\ntypename ActedMonoid::operator_type dynamic_shift(\n\
    \    const typename ActedMonoid::operator_type& f,\n    Size offset\n) {\n   \
    \ using F = typename ActedMonoid::operator_type;\n    if constexpr (requires(F\
    \ g, long long ord) { ActedMonoid::op_shift(g, ord); }) {\n        assert(offset\
    \ <= static_cast<Size>(std::numeric_limits<long long>::max()));\n        return\
    \ ActedMonoid::op_shift(f, static_cast<long long>(offset));\n    } else {\n  \
    \      return f;\n    }\n}\n\ntemplate <class Monoid, std::integral Index>\nclass\
    \ UniformMonoidDomain {\n   public:\n    using T = typename Monoid::value_type;\n\
    \    using size_type = dynamic_size_type<Index>;\n\n   private:\n    struct Level\
    \ {\n        size_type small_length;\n        T small_value;\n        T large_value;\n\
    \    };\n\n    Index _left;\n    Index _right;\n    T _initial_value;\n    std::vector<Level>\
    \ _levels;\n\n   public:\n    UniformMonoidDomain(Index left, Index right, T initial_value)\n\
    \        : _left(left), _right(right), _initial_value(std::move(initial_value))\
    \ {\n        assert(left <= right);\n        size_type n = size();\n        constexpr\
    \ int digits = std::numeric_limits<size_type>::digits;\n        _levels.reserve(digits\
    \ + 1);\n        for (int depth = 0; depth <= digits; depth++) {\n           \
    \ size_type small = depth == digits ? 0 : n >> depth;\n            size_type large\
    \ = small;\n            if (depth != 0) {\n                bool has_remainder;\n\
    \                if (depth == digits) {\n                    has_remainder = n\
    \ != 0;\n                } else {\n                    size_type mask = (size_type(1)\
    \ << depth) - 1;\n                    has_remainder = (n & mask) != 0;\n     \
    \           }\n                if (has_remainder) large++;\n            }\n  \
    \          _levels.push_back(Level{\n                small,\n                monoid_repeat<Monoid>(_initial_value,\
    \ small),\n                monoid_repeat<Monoid>(_initial_value, large),\n   \
    \         });\n        }\n    }\n\n    Index left_bound() const {\n        return\
    \ _left;\n    }\n\n    Index right_bound() const {\n        return _right;\n \
    \   }\n\n    size_type size() const {\n        return dynamic_distance(_left,\
    \ _right);\n    }\n\n    bool empty() const {\n        return _left == _right;\n\
    \    }\n\n    const T& initial_value() const {\n        return _initial_value;\n\
    \    }\n\n    const T& default_product(int depth, Index left, Index right) const\
    \ {\n        assert(0 <= depth && depth < int(_levels.size()));\n        const\
    \ Level& level = _levels[depth];\n        size_type length = dynamic_distance(left,\
    \ right);\n        if (length == level.small_length) return level.small_value;\n\
    \        assert(length == level.small_length + 1);\n        return level.large_value;\n\
    \    }\n};\n\n}  // namespace detail\n}  // namespace ds\n}  // namespace m1une\n\
    \n\n#line 1 \"monoid/concept.hpp\"\n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
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
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 15 \"ds/segtree/dynamic_dual_segtree.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\n// A sparse dual segment tree over an\
    \ integral half-open interval.\ntemplate <m1une::monoid::IsMonoid Monoid, std::integral\
    \ Index = long long>\nrequires(!std::same_as<std::remove_cv_t<Index>, bool>)\n\
    struct DynamicDualSegtree {\n    using T = typename Monoid::value_type;\n    using\
    \ index_type = Index;\n    using size_type = detail::dynamic_size_type<Index>;\n\
    \n   private:\n    struct Node {\n        T val;\n        int left;\n        int\
    \ right;\n        bool has_lazy;\n\n        Node() : val(Monoid::id()), left(0),\
    \ right(0), has_lazy(false) {}\n    };\n\n    Index _left;\n    Index _right;\n\
    \    T _initial_value;\n    int _root;\n    std::vector<Node> _nodes;\n\n    int\
    \ new_node() {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    void all_apply(int& t, Index left, Index right, const T& x) {\n        if\
    \ (!t) t = new_node();\n        Node& node = _nodes[t];\n        if (std::midpoint(left,\
    \ right) == left) {\n            T value = node.has_lazy ? node.val : _initial_value;\n\
    \            node.val = Monoid::op(x, value);\n            node.has_lazy = true;\n\
    \        } else {\n            node.val = node.has_lazy ? Monoid::op(x, node.val)\
    \ : x;\n            node.has_lazy = true;\n        }\n    }\n\n    void push(int\
    \ t, Index left, Index right) {\n        if (!_nodes[t].has_lazy) return;\n  \
    \      Index middle = std::midpoint(left, right);\n        if (middle == left)\
    \ return;\n\n        T lazy = _nodes[t].val;\n        int left_child = _nodes[t].left;\n\
    \        int right_child = _nodes[t].right;\n        all_apply(left_child, left,\
    \ middle, lazy);\n        all_apply(right_child, middle, right, lazy);\n\n   \
    \     Node& node = _nodes[t];\n        node.left = left_child;\n        node.right\
    \ = right_child;\n        node.val = Monoid::id();\n        node.has_lazy = false;\n\
    \    }\n\n    int set_node(int t, Index left, Index right, Index p, T x) {\n \
    \       if (!t) t = new_node();\n        Index middle = std::midpoint(left, right);\n\
    \        if (middle == left) {\n            Node& node = _nodes[t];\n        \
    \    node.val = std::move(x);\n            node.has_lazy = true;\n           \
    \ return t;\n        }\n\n        push(t, left, right);\n        if (p < middle)\
    \ {\n            int child = set_node(_nodes[t].left, left, middle, p, std::move(x));\n\
    \            _nodes[t].left = child;\n        } else {\n            int child\
    \ = set_node(_nodes[t].right, middle, right, p, std::move(x));\n            _nodes[t].right\
    \ = child;\n        }\n        return t;\n    }\n\n    int apply_node(\n     \
    \   int t,\n        Index left,\n        Index right,\n        Index query_left,\n\
    \        Index query_right,\n        const T& x\n    ) {\n        if (query_right\
    \ <= left || right <= query_left) return t;\n        if (query_left <= left &&\
    \ right <= query_right) {\n            all_apply(t, left, right, x);\n       \
    \     return t;\n        }\n\n        if (!t) t = new_node();\n        push(t,\
    \ left, right);\n        Index middle = std::midpoint(left, right);\n        int\
    \ left_child = apply_node(_nodes[t].left, left, middle, query_left, query_right,\
    \ x);\n        int right_child = apply_node(_nodes[t].right, middle, right, query_left,\
    \ query_right, x);\n        _nodes[t].left = left_child;\n        _nodes[t].right\
    \ = right_child;\n        return t;\n    }\n\n    T compose(const T& inherited,\
    \ int t) const {\n        if (!t || !_nodes[t].has_lazy) return inherited;\n \
    \       return Monoid::op(inherited, _nodes[t].val);\n    }\n\n   public:\n  \
    \  DynamicDualSegtree()\n        : DynamicDualSegtree(Index(0), Index(0), Monoid::id())\
    \ {}\n\n    explicit DynamicDualSegtree(Index n)\n        : DynamicDualSegtree(Index(0),\
    \ n, Monoid::id()) {\n        if constexpr (std::signed_integral<Index>) assert(Index(0)\
    \ <= n);\n    }\n\n    DynamicDualSegtree(Index left, Index right)\n        :\
    \ DynamicDualSegtree(left, right, Monoid::id()) {}\n\n    DynamicDualSegtree(Index\
    \ left, Index right, T initial_value)\n        : _left(left),\n          _right(right),\n\
    \          _initial_value(std::move(initial_value)),\n          _root(0),\n  \
    \        _nodes(1) {\n        assert(left <= right);\n    }\n\n    size_type size()\
    \ const {\n        return detail::dynamic_distance(_left, _right);\n    }\n\n\
    \    bool empty() const {\n        return _left == _right;\n    }\n\n    Index\
    \ left_bound() const {\n        return _left;\n    }\n\n    Index right_bound()\
    \ const {\n        return _right;\n    }\n\n    const T& initial_value() const\
    \ {\n        return _initial_value;\n    }\n\n    void reserve(std::size_t node_capacity)\
    \ {\n        assert(node_capacity < std::numeric_limits<std::size_t>::max());\n\
    \        _nodes.reserve(node_capacity + 1);\n    }\n\n    std::size_t node_count()\
    \ const {\n        return _nodes.size() - 1;\n    }\n\n    void clear() {\n  \
    \      _root = 0;\n        _nodes.resize(1);\n    }\n\n    void set(Index p, T\
    \ x) {\n        assert(_left <= p && p < _right);\n        _root = set_node(_root,\
    \ _left, _right, p, std::move(x));\n    }\n\n    T get(Index p) const {\n    \
    \    assert(_left <= p && p < _right);\n        int t = _root;\n        Index\
    \ left = _left;\n        Index right = _right;\n        T inherited = Monoid::id();\n\
    \n        while (t) {\n            Index middle = std::midpoint(left, right);\n\
    \            if (middle == left) {\n                T value = _nodes[t].has_lazy\
    \ ? _nodes[t].val : _initial_value;\n                return Monoid::op(inherited,\
    \ value);\n            }\n            inherited = compose(inherited, t);\n   \
    \         if (p < middle) {\n                t = _nodes[t].left;\n           \
    \     right = middle;\n            } else {\n                t = _nodes[t].right;\n\
    \                left = middle;\n            }\n        }\n        return Monoid::op(inherited,\
    \ _initial_value);\n    }\n\n    T operator[](Index p) const {\n        return\
    \ get(p);\n    }\n\n    void apply(Index p, const T& x) {\n        assert(_left\
    \ <= p && p < _right);\n        apply(p, p + 1, x);\n    }\n\n    void apply(Index\
    \ left, Index right, const T& x) {\n        assert(_left <= left && left <= right\
    \ && right <= _right);\n        if (left == right) return;\n        _root = apply_node(_root,\
    \ _left, _right, left, right, x);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/ds/segtree/dynamic_dual_segtree.test.cpp\"\n\n#include\
    \ <algorithm>\n#line 7 \"verify/ds/segtree/dynamic_dual_segtree.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#line 11 \"verify/ds/segtree/dynamic_dual_segtree.test.cpp\"\
    \n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line 8 \"math/modint.hpp\"\n\nnamespace\
    \ m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt {\n\
    \    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n   private:\n\
    \    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod() {\n     \
    \   return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept\
    \ {\n        ModInt x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr\
    \ ModInt() noexcept : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add\
    \ {\n    using value_type = T;\n\n    // Returns the identity element for addition,\
    \ which is 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n\
    \    // Returns the sum of a and b.\n    static constexpr T op(const T& a, const\
    \ T& b) {\n        return a + b;\n    }\n\n    static constexpr T inv(const T&\
    \ x) {\n        return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"monoid/affine.hpp\"\n\n\n\n#line 5 \"monoid/affine.hpp\"\
    \n\nnamespace m1une {\nnamespace monoid {\n\n// Monoid for affine transformations\
    \ f(x) = ax + b.\n// Represented as a pair {a, b}.\ntemplate <typename T>\nstruct\
    \ Affine {\n    using value_type = std::pair<T, T>;\n\n    // The identity transformation\
    \ is f(x) = 1*x + 0.\n    static constexpr value_type id() {\n        return {T(1),\
    \ T(0)};\n    }\n\n    // Composes two affine transformations.\n    // f(g(x))\
    \ where f = a, g = b.\n    // a.first * (b.first * x + b.second) + a.second\n\
    \    // = (a.first * b.first) * x + (a.first * b.second + a.second)\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  return {a.first * b.first, a.first * b.second + a.second};\n    }\n\n    //\
    \ Helpers to create common affine transformations\n    static constexpr value_type\
    \ make_add(const T& b) {\n        return {T(1), b};\n    }\n    static constexpr\
    \ value_type make_mul(const T& a) {\n        return {a, T(0)};\n    }\n    static\
    \ constexpr value_type make_assign(const T& b) {\n        return {T(0), b};\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 15 \"verify/ds/segtree/dynamic_dual_segtree.test.cpp\"\
    \n\nnamespace {\n\nvoid test_randomized() {\n    using Add = m1une::monoid::Add<long\
    \ long>;\n    constexpr int left = -43;\n    constexpr int right = 51;\n    m1une::ds::DynamicDualSegtree<Add,\
    \ int> seg(left, right, 7);\n    std::vector<long long> a(right - left, 7);\n\n\
    \    std::uint64_t state = 3;\n    auto random = [&state]() {\n        state ^=\
    \ state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n \
    \   auto value_at = [&a](int p) -> long long& {\n        return a[std::size_t(p\
    \ - left)];\n    };\n\n    for (int step = 0; step < 4000; step++) {\n       \
    \ int type = int(random() % 3);\n        if (type == 0) {\n            int l =\
    \ left + int(random() % (a.size() + 1));\n            int r = left + int(random()\
    \ % (a.size() + 1));\n            if (r < l) std::swap(l, r);\n            long\
    \ long x = static_cast<long long>(random() % 21);\n            seg.apply(l, r,\
    \ x);\n            for (int p = l; p < r; p++) value_at(p) += x;\n        } else\
    \ if (type == 1) {\n            [[maybe_unused]] int p = left + int(random() %\
    \ a.size());\n            long long x = static_cast<long long>(random() % 100);\n\
    \            seg.set(p, x);\n            value_at(p) = x;\n        } else {\n\
    \            [[maybe_unused]] int p = left + int(random() % a.size());\n     \
    \       assert(seg.get(p) == value_at(p));\n        }\n    }\n\n    for (int p\
    \ = left; p < right; p++) assert(seg[p] == value_at(p));\n    assert(seg.node_count()\
    \ != 0);\n    seg.clear();\n    assert(seg.node_count() == 0);\n    for (int p\
    \ = left; p < right; p++) assert(seg.get(p) == 7);\n}\n\n}  // namespace\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    test_randomized();\n\n    using mint = m1une::math::modint998244353;\n \
    \   using Affine = m1une::monoid::Affine<mint>;\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    m1une::ds::DynamicDualSegtree<Affine, int> seg(0, n, Affine::id());\n\
    \    seg.reserve(std::size_t(4) * std::size_t(n + q));\n\n    for (int i = 0;\
    \ i < n; i++) {\n        long long x;\n        std::cin >> x;\n        Affine::value_type\
    \ value;\n        value.first = mint(0);\n        value.second = mint(x);\n  \
    \      seg.set(i, value);\n    }\n\n    for (int query = 0; query < q; query++)\
    \ {\n        int type;\n        std::cin >> type;\n        if (type == 0) {\n\
    \            int l, r;\n            long long b, c;\n            std::cin >> l\
    \ >> r >> b >> c;\n            Affine::value_type f;\n            f.first = mint(b);\n\
    \            f.second = mint(c);\n            seg.apply(l, r, f);\n        } else\
    \ {\n            int p;\n            std::cin >> p;\n            std::cout <<\
    \ seg.get(p).second << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_point_get\"\
    \n\n#include \"../../../ds/segtree/dynamic_dual_segtree.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../../math/modint.hpp\"\n#include \"../../../monoid/add.hpp\"\
    \n#include \"../../../monoid/affine.hpp\"\n\nnamespace {\n\nvoid test_randomized()\
    \ {\n    using Add = m1une::monoid::Add<long long>;\n    constexpr int left =\
    \ -43;\n    constexpr int right = 51;\n    m1une::ds::DynamicDualSegtree<Add,\
    \ int> seg(left, right, 7);\n    std::vector<long long> a(right - left, 7);\n\n\
    \    std::uint64_t state = 3;\n    auto random = [&state]() {\n        state ^=\
    \ state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n \
    \   auto value_at = [&a](int p) -> long long& {\n        return a[std::size_t(p\
    \ - left)];\n    };\n\n    for (int step = 0; step < 4000; step++) {\n       \
    \ int type = int(random() % 3);\n        if (type == 0) {\n            int l =\
    \ left + int(random() % (a.size() + 1));\n            int r = left + int(random()\
    \ % (a.size() + 1));\n            if (r < l) std::swap(l, r);\n            long\
    \ long x = static_cast<long long>(random() % 21);\n            seg.apply(l, r,\
    \ x);\n            for (int p = l; p < r; p++) value_at(p) += x;\n        } else\
    \ if (type == 1) {\n            [[maybe_unused]] int p = left + int(random() %\
    \ a.size());\n            long long x = static_cast<long long>(random() % 100);\n\
    \            seg.set(p, x);\n            value_at(p) = x;\n        } else {\n\
    \            [[maybe_unused]] int p = left + int(random() % a.size());\n     \
    \       assert(seg.get(p) == value_at(p));\n        }\n    }\n\n    for (int p\
    \ = left; p < right; p++) assert(seg[p] == value_at(p));\n    assert(seg.node_count()\
    \ != 0);\n    seg.clear();\n    assert(seg.node_count() == 0);\n    for (int p\
    \ = left; p < right; p++) assert(seg.get(p) == 7);\n}\n\n}  // namespace\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    test_randomized();\n\n    using mint = m1une::math::modint998244353;\n \
    \   using Affine = m1une::monoid::Affine<mint>;\n\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    m1une::ds::DynamicDualSegtree<Affine, int> seg(0, n, Affine::id());\n\
    \    seg.reserve(std::size_t(4) * std::size_t(n + q));\n\n    for (int i = 0;\
    \ i < n; i++) {\n        long long x;\n        std::cin >> x;\n        Affine::value_type\
    \ value;\n        value.first = mint(0);\n        value.second = mint(x);\n  \
    \      seg.set(i, value);\n    }\n\n    for (int query = 0; query < q; query++)\
    \ {\n        int type;\n        std::cin >> type;\n        if (type == 0) {\n\
    \            int l, r;\n            long long b, c;\n            std::cin >> l\
    \ >> r >> b >> c;\n            Affine::value_type f;\n            f.first = mint(b);\n\
    \            f.second = mint(c);\n            seg.apply(l, r, f);\n        } else\
    \ {\n            int p;\n            std::cin >> p;\n            std::cout <<\
    \ seg.get(p).second << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/dynamic_dual_segtree.hpp
  - ds/segtree/dynamic_segtree_common.hpp
  - monoid/concept.hpp
  - math/modint.hpp
  - monoid/add.hpp
  - monoid/affine.hpp
  isVerificationFile: true
  path: verify/ds/segtree/dynamic_dual_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/dynamic_dual_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/dynamic_dual_segtree.test.cpp
- /verify/verify/ds/segtree/dynamic_dual_segtree.test.cpp.html
title: verify/ds/segtree/dynamic_dual_segtree.test.cpp
---
