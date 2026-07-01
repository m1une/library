---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: acted_monoid/concept.hpp
    title: Acted Monoid Concept
  - icon: ':heavy_check_mark:'
    path: acted_monoid/range_affine_range_sum.hpp
    title: Range Affine Range Sum
  - icon: ':heavy_check_mark:'
    path: ds/segtree/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_affine_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/lazy_segtree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\n\n#line 1 \"ds/segtree/lazy_segtree.hpp\"\
    \n\n\n\n#include <bit>\n#include <cassert>\n#include <concepts>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"acted_monoid/concept.hpp\"\n\n\n\n#line 5 \"acted_monoid/concept.hpp\"\
    \n\nnamespace m1une {\nnamespace acted_monoid {\n\n// Concept defining the requirements\
    \ for an Acted Monoid.\ntemplate <typename AM>\nconcept IsActedMonoid = requires(typename\
    \ AM::value_type a, typename AM::value_type b, typename AM::operator_type f,\n\
    \                                 typename AM::operator_type g) {\n    // 1. Value\
    \ Monoid\n    typename AM::value_type;\n    { AM::id() } -> std::same_as<typename\
    \ AM::value_type>;\n    { AM::op(a, b) } -> std::same_as<typename AM::value_type>;\n\
    \n    // 2. Operator Monoid\n    typename AM::operator_type;\n    { AM::op_id()\
    \ } -> std::same_as<typename AM::operator_type>;\n    { AM::op_comp(f, g) } ->\
    \ std::same_as<typename AM::operator_type>;  // Composition order: f(g(x))\n\n\
    \    // 3. Mapping: Operator x Value -> Value\n    { AM::mapping(f, a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n// Concept for acted monoids whose value monoid is a\
    \ commutative group.\n// The value operation must obey commutativity and inverse\
    \ laws.\ntemplate <typename AM>\nconcept IsCommutativeActedGroup = IsActedMonoid<AM>\
    \ && requires(typename AM::value_type a) {\n    { AM::inv(a) } -> std::same_as<typename\
    \ AM::value_type>;\n};\n\n}  // namespace acted_monoid\n}  // namespace m1une\n\
    \n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace math {\n\
    \ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1) return 1;\n\
    \    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n}  // namespace\
    \ math\n}  // namespace m1une\n\n\n#line 12 \"ds/segtree/lazy_segtree.hpp\"\n\n\
    namespace m1une {\nnamespace ds {\n\n// A highly generic Lazy Segment Tree utilizing\
    \ C++20 Concepts for type safety.\n// It operates on any Acted Monoid structure\
    \ satisfying the `m1une::acted_monoid::IsActedMonoid` concept.\ntemplate <m1une::acted_monoid::IsActedMonoid\
    \ ActedMonoid>\nstruct LazySegtree {\n    using T = typename ActedMonoid::value_type;\n\
    \    using F = typename ActedMonoid::operator_type;\n\n   private:\n    int _n,\
    \ _size, _log;\n    std::vector<T> _d;\n    std::vector<F> _lz;\n\n    // Recalculates\
    \ the value of the node k from its children.\n    void update(int k) {\n     \
    \   _d[k] = ActedMonoid::op(_d[2 * k], _d[2 * k + 1]);\n    }\n\n    static T\
    \ mapping_at(const F& f, const T& value, long long ord) {\n        if constexpr\
    \ (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {\n   \
    \         return ActedMonoid::mapping(f, value, ord);\n        } else {\n    \
    \        return ActedMonoid::mapping(f, value);\n        }\n    }\n\n    static\
    \ F shift_operator(const F& f, long long ord) {\n        if constexpr (requires(F\
    \ g, long long i) { ActedMonoid::op_shift(g, i); }) {\n            return ActedMonoid::op_shift(f,\
    \ ord);\n        } else {\n            return f;\n        }\n    }\n\n    int\
    \ node_length(int k) const {\n        int level = std::bit_width((unsigned int)k)\
    \ - 1;\n        return _size >> level;\n    }\n\n    int node_left(int k) const\
    \ {\n        int level = std::bit_width((unsigned int)k) - 1;\n        int len\
    \ = _size >> level;\n        return (k - (1 << level)) * len;\n    }\n\n    //\
    \ Applies the operator f to the node k and updates its lazy tag if it's an internal\
    \ node.\n    void all_apply(int k, F f) {\n        _d[k] = mapping_at(f, _d[k],\
    \ 0);\n        if (k < _size) {\n            _lz[k] = ActedMonoid::op_comp(f,\
    \ _lz[k]);\n        }\n    }\n\n    // Propagates the lazy tag of the node k down\
    \ to its children.\n    void push(int k) {\n        all_apply(2 * k, _lz[k]);\n\
    \        all_apply(2 * k + 1, shift_operator(_lz[k], node_length(k) / 2));\n \
    \       _lz[k] = ActedMonoid::op_id();\n    }\n\n   public:\n    // Constructs\
    \ an empty lazy segment tree.\n    LazySegtree() : LazySegtree(0) {}\n\n    //\
    \ Constructs a lazy segment tree of size `n`, initialized with the identity element.\n\
    \    explicit LazySegtree(int n) : LazySegtree(std::vector<T>(n, ActedMonoid::id()))\
    \ {}\n\n    // Constructs a lazy segment tree from an existing vector.\n    explicit\
    \ LazySegtree(const std::vector<T>& v) : _n(int(v.size())) {\n        _size =\
    \ m1une::math::bit_ceil((unsigned int)(_n));\n        _log = 0;\n        while\
    \ ((1U << _log) < (unsigned int)(_size)) _log++;\n        _d.assign(2 * _size,\
    \ ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n    \
    \    for (int i = 0; i < _n; i++) _d[_size + i] = v[i];\n        for (int i =\
    \ _size - 1; i >= 1; i--) update(i);\n    }\n    explicit LazySegtree(std::vector<T>&&\
    \ v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n\
    \        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n\
    \        _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size, ActedMonoid::op_id());\n\
    \        for (int i = 0; i < _n; i++) _d[_size + i] = std::move(v[i]);\n     \
    \   for (int i = _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Constructs\
    \ a lazy segment tree from a vector of a different type U.\n    // It automatically\
    \ adapts to the Monoid's initialization requirements:\n    // 1. ActedMonoid::make(val)\
    \ if it exists.\n    // 2. ActedMonoid::make(val, index) if the monoid requires\
    \ global indices.\n    // 3. static_cast<T>(val) as a fallback for simple monoids.\n\
    \    template <typename U>\n    requires (!std::same_as<U, T>) && (\n        requires(U\
    \ x) { ActedMonoid::make(x); } ||\n        requires(U x, int i) { ActedMonoid::make(x,\
    \ i); } ||\n        std::convertible_to<U, T>\n    )\n    explicit LazySegtree(const\
    \ std::vector<U>& v) : _n(int(v.size())) {\n        _size = m1une::math::bit_ceil((unsigned\
    \ int)(_n));\n        _log = 0;\n        while ((1U << _log) < (unsigned int)(_size))\
    \ _log++;\n        _d.assign(2 * _size, ActedMonoid::id());\n        _lz.assign(_size,\
    \ ActedMonoid::op_id());\n        for (int i = 0; i < _n; i++) {\n           \
    \ if constexpr (requires(U x) { ActedMonoid::make(x); }) {\n                _d[_size\
    \ + i] = ActedMonoid::make(v[i]);\n            } else if constexpr (requires(U\
    \ x, int idx) { ActedMonoid::make(x, idx); }) {\n                _d[_size + i]\
    \ = ActedMonoid::make(v[i], i);\n            } else {\n                _d[_size\
    \ + i] = static_cast<T>(v[i]);\n            }\n        }\n        for (int i =\
    \ _size - 1; i >= 1; i--) update(i);\n    }\n\n    // Returns the number of elements.\n\
    \    int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ tree is empty.\n    bool empty() const {\n        return _n == 0;\n    }\n\n\
    \    // Assigns x to the p-th element.\n    void set(int p, T x) {\n        assert(0\
    \ <= p && p < _n);\n        p += _size;\n        for (int i = _log; i >= 1; i--)\
    \ push(p >> i);\n        _d[p] = x;\n        for (int i = 1; i <= _log; i++) update(p\
    \ >> i);\n    }\n\n    // Returns the value of the p-th element.\n    T get(int\
    \ p) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for (int\
    \ i = _log; i >= 1; i--) push(p >> i);\n        return _d[p];\n    }\n\n    //\
    \ Returns the value of the p-th element.\n    T operator[](int p) {\n        return\
    \ get(p);\n    }\n\n    // Returns the product (result of the monoid operation)\
    \ in the range [l, r).\n    T prod(int l, int r) {\n        assert(0 <= l && l\
    \ <= r && r <= _n);\n        if (l == r) return ActedMonoid::id();\n\n       \
    \ l += _size;\n        r += _size;\n\n        for (int i = _log; i >= 1; i--)\
    \ {\n            if (((l >> i) << i) != l) push(l >> i);\n            if (((r\
    \ >> i) << i) != r) push((r - 1) >> i);\n        }\n\n        T sml = ActedMonoid::id(),\
    \ smr = ActedMonoid::id();\n        while (l < r) {\n            if (l & 1) sml\
    \ = ActedMonoid::op(sml, _d[l++]);\n            if (r & 1) smr = ActedMonoid::op(_d[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n\n        return\
    \ ActedMonoid::op(sml, smr);\n    }\n\n    // Returns the product of the entire\
    \ array.\n    T all_prod() const {\n        return _d[1];\n    }\n\n    // Returns\
    \ all elements as a vector.\n    std::vector<T> to_vector() {\n        for (int\
    \ k = 1; k < _size; k++) push(k);\n        std::vector<T> res;\n        res.reserve(_n);\n\
    \        for (int i = 0; i < _n; i++) res.push_back(_d[_size + i]);\n        return\
    \ res;\n    }\n\n    // Returns the elements in the range [l, r) as a vector.\n\
    \    std::vector<T> to_vector(int l, int r) {\n        assert(0 <= l && l <= r\
    \ && r <= _n);\n        std::vector<T> res;\n        res.reserve(r - l);\n   \
    \     for (int i = l; i < r; i++) res.push_back(get(i));\n        return res;\n\
    \    }\n\n    // Applies the operator f to the p-th element.\n    void apply(int\
    \ p, F f) {\n        assert(0 <= p && p < _n);\n        p += _size;\n        for\
    \ (int i = _log; i >= 1; i--) push(p >> i);\n        _d[p] = mapping_at(f, _d[p],\
    \ 0);\n        for (int i = 1; i <= _log; i++) update(p >> i);\n    }\n\n    //\
    \ Applies the operator f to all elements in the range [l, r).\n    void apply(int\
    \ l, int r, F f) {\n        assert(0 <= l && l <= r && r <= _n);\n        if (l\
    \ == r) return;\n\n        int base_l = l;\n        l += _size;\n        r +=\
    \ _size;\n\n        for (int i = _log; i >= 1; i--) {\n            if (((l >>\
    \ i) << i) != l) push(l >> i);\n            if (((r >> i) << i) != r) push((r\
    \ - 1) >> i);\n        }\n\n        {\n            int l2 = l, r2 = r;\n     \
    \       while (l < r) {\n                if (l & 1) {\n                    all_apply(l,\
    \ shift_operator(f, node_left(l) - base_l));\n                    l++;\n     \
    \           }\n                if (r & 1) {\n                    --r;\n      \
    \              all_apply(r, shift_operator(f, node_left(r) - base_l));\n     \
    \           }\n                l >>= 1;\n                r >>= 1;\n          \
    \  }\n            l = l2;\n            r = r2;\n        }\n\n        for (int\
    \ i = 1; i <= _log; i++) {\n            if (((l >> i) << i) != l) update(l >>\
    \ i);\n            if (((r >> i) << i) != r) update((r - 1) >> i);\n        }\n\
    \    }\n\n    // Finds the largest r such that g(prod(l, r)) is true.\n    template\
    \ <class F_pred>\n    int max_right(int l, F_pred g) {\n        assert(0 <= l\
    \ && l <= _n);\n        assert(g(ActedMonoid::id()));\n        if (l == _n) return\
    \ _n;\n        l += _size;\n        for (int i = _log; i >= 1; i--) push(l >>\
    \ i);\n        T sm = ActedMonoid::id();\n        do {\n            while (l %\
    \ 2 == 0) l >>= 1;\n            if (!g(ActedMonoid::op(sm, _d[l]))) {\n      \
    \          while (l < _size) {\n                    push(l);\n               \
    \     l = (2 * l);\n                    if (g(ActedMonoid::op(sm, _d[l]))) {\n\
    \                        sm = ActedMonoid::op(sm, _d[l]);\n                  \
    \      l++;\n                    }\n                }\n                return\
    \ l - _size;\n            }\n            sm = ActedMonoid::op(sm, _d[l]);\n  \
    \          l++;\n        } while ((l & -l) != l);\n        return _n;\n    }\n\
    \n    // Finds the smallest l such that g(prod(l, r)) is true.\n    template <class\
    \ F_pred>\n    int min_left(int r, F_pred g) {\n        assert(0 <= r && r <=\
    \ _n);\n        assert(g(ActedMonoid::id()));\n        if (r == 0) return 0;\n\
    \        r += _size;\n        for (int i = _log; i >= 1; i--) push((r - 1) >>\
    \ i);\n        T sm = ActedMonoid::id();\n        do {\n            r--;\n   \
    \         while (r > 1 && (r % 2)) r >>= 1;\n            if (!g(ActedMonoid::op(_d[r],\
    \ sm))) {\n                while (r < _size) {\n                    push(r);\n\
    \                    r = (2 * r + 1);\n                    if (g(ActedMonoid::op(_d[r],\
    \ sm))) {\n                        sm = ActedMonoid::op(_d[r], sm);\n        \
    \                r--;\n                    }\n                }\n            \
    \    return r + 1 - _size;\n            }\n            sm = ActedMonoid::op(_d[r],\
    \ sm);\n        } while ((r & -r) != r);\n        return 0;\n    }\n};\n\n}  //\
    \ namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/segtree/lazy_segtree.test.cpp\"\
    \n\n#include <bits/stdc++.h>\n\n#line 1 \"acted_monoid/range_affine_range_sum.hpp\"\
    \n\n\n\n#line 5 \"acted_monoid/range_affine_range_sum.hpp\"\n\nnamespace m1une\
    \ {\nnamespace acted_monoid {\n\ntemplate <typename T>\nstruct RangeAffineRangeSumNode\
    \ {\n    T sum;\n    long long size;\n};\n\n// Designed to accept Modint or similar\
    \ types as T\ntemplate <typename T>\nstruct RangeAffineRangeSum {\n    using value_type\
    \ = RangeAffineRangeSumNode<T>;\n    using operator_type = std::pair<T, T>;  //\
    \ {a, b} for ax + b\n\n    // Value Monoid\n    static constexpr value_type id()\
    \ {\n        return {T(0), 0};\n    }\n    static constexpr value_type op(const\
    \ value_type& a, const value_type& b) {\n        return {a.sum + b.sum, a.size\
    \ + b.size};\n    }\n\n    // Operator Monoid (Affine Composition)\n    // f(x)\
    \ = a1*x + b1, g(x) = a2*x + b2\n    // f(g(x)) = a1*(a2*x + b2) + b1 = (a1*a2)*x\
    \ + (a1*b2 + b1)\n    static constexpr operator_type op_id() {\n        return\
    \ {T(1), T(0)};\n    }\n    static constexpr operator_type op_comp(const operator_type&\
    \ f, const operator_type& g) {\n        return {f.first * g.first, f.first * g.second\
    \ + f.second};\n    }\n\n    // Mapping\n    // \\sum (a*x_i + b) = a * \\sum\
    \ x_i + b * size\n    static constexpr value_type mapping(const operator_type&\
    \ f, const value_type& x) {\n        return {f.first * x.sum + f.second * T(x.size),\
    \ x.size};\n    }\n\n    // Helper for initializing a leaf node\n    static constexpr\
    \ value_type make(const T& val) {\n        return {val, 1};\n    }\n};\n\n}  //\
    \ namespace acted_monoid\n}  // namespace m1une\n\n\n#line 1 \"math/modint.hpp\"\
    \n\n\n\n#line 6 \"math/modint.hpp\"\n#include <type_traits>\n#line 8 \"math/modint.hpp\"\
    \n\nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct\
    \ ModInt {\n    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n\
    \   private:\n    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod()\
    \ {\n        return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t\
    \ v) noexcept {\n        ModInt x;\n        x._v = v;\n        return x;\n   \
    \ }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template <class Integer,\
    \ std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n    constexpr ModInt(Integer\
    \ v) noexcept {\n        if constexpr (std::is_signed_v<Integer>) {\n        \
    \    int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n  \
    \          if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
    \        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
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
    \ m1une\n\n\n#line 9 \"verify/ds/segtree/lazy_segtree.test.cpp\"\n\nusing mint\
    \ = m1une::math::modint998244353;\n\nusing AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\
    \nusing namespace std;\nusing ll = long long;\n\nvoid solve() {\n    ll N, Q;\n\
    \    cin >> N >> Q;\n    vector<ll> a(N);\n    for (int i = 0; i < N; ++i) cin\
    \ >> a[i];\n\n    m1une::ds::LazySegtree<AM> seg(a);\n    assert(seg.size() ==\
    \ N);\n    assert(seg.empty() == (N == 0));\n    auto values = seg.to_vector();\n\
    \    assert(int(values.size()) == N);\n    for (int i = 0; i < N; i++) {\n   \
    \     assert(values[i].sum == mint(a[i]));\n        assert(seg[i].sum == mint(a[i]));\n\
    \    }\n    for (int q = 0; q < Q; ++q) {\n        ll t;\n        cin >> t;\n\
    \        if (t == 0) {\n            ll l, r, b, c;\n            cin >> l >> r\
    \ >> b >> c;\n            seg.apply(l, r, {b, c});\n        } else {\n       \
    \     ll l, r;\n            cin >> l >> r;\n            auto prd = seg.prod(l,\
    \ r);\n            cout << prd.sum << '\\n';\n        }\n    }\n}\n\nint main()\
    \ {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n    solve();\n \
    \   return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#include \"../../../ds/segtree/lazy_segtree.hpp\"\n\n#include <bits/stdc++.h>\n\
    \n#include \"../../../acted_monoid/range_affine_range_sum.hpp\"\n#include \"../../../math/modint.hpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\nusing AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\
    \nusing namespace std;\nusing ll = long long;\n\nvoid solve() {\n    ll N, Q;\n\
    \    cin >> N >> Q;\n    vector<ll> a(N);\n    for (int i = 0; i < N; ++i) cin\
    \ >> a[i];\n\n    m1une::ds::LazySegtree<AM> seg(a);\n    assert(seg.size() ==\
    \ N);\n    assert(seg.empty() == (N == 0));\n    auto values = seg.to_vector();\n\
    \    assert(int(values.size()) == N);\n    for (int i = 0; i < N; i++) {\n   \
    \     assert(values[i].sum == mint(a[i]));\n        assert(seg[i].sum == mint(a[i]));\n\
    \    }\n    for (int q = 0; q < Q; ++q) {\n        ll t;\n        cin >> t;\n\
    \        if (t == 0) {\n            ll l, r, b, c;\n            cin >> l >> r\
    \ >> b >> c;\n            seg.apply(l, r, {b, c});\n        } else {\n       \
    \     ll l, r;\n            cin >> l >> r;\n            auto prd = seg.prod(l,\
    \ r);\n            cout << prd.sum << '\\n';\n        }\n    }\n}\n\nint main()\
    \ {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n    solve();\n \
    \   return 0;\n}\n"
  dependsOn:
  - ds/segtree/lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - math/bit_ceil.hpp
  - acted_monoid/range_affine_range_sum.hpp
  - math/modint.hpp
  isVerificationFile: true
  path: verify/ds/segtree/lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/lazy_segtree.test.cpp
- /verify/verify/ds/segtree/lazy_segtree.test.cpp.html
title: verify/ds/segtree/lazy_segtree.test.cpp
---
