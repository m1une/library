---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/dual_segtree.hpp
    title: Dual Segment Tree
  - icon: ':question:'
    path: math/bit_ceil.hpp
    title: Bit Ceil
  - icon: ':question:'
    path: math/modint.hpp
    title: ModInt
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
  bundledCode: "#line 1 \"verify/ds/segtree/dual_segtree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_affine_point_get\"\n\n#line 1 \"ds/segtree/dual_segtree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <concepts>\n#include <utility>\n#include\
    \ <vector>\n\n#line 1 \"math/bit_ceil.hpp\"\n\n\n\nnamespace m1une {\nnamespace\
    \ math {\n\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n    if (n <= 1)\
    \ return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return x;\n}\n\n} \
    \ // namespace math\n}  // namespace m1une\n\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
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
    \ 11 \"ds/segtree/dual_segtree.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    // A generic Dual Segment Tree for range monoid updates and point queries.\ntemplate\
    \ <m1une::monoid::IsMonoid Monoid>\nstruct DualSegtree {\n    using T = typename\
    \ Monoid::value_type;\n\n   private:\n    int _n, _size, _log;\n    std::vector<T>\
    \ _d;\n\n    void all_apply(int k, const T& x) {\n        _d[k] = Monoid::op(x,\
    \ _d[k]);\n    }\n\n    void push(int k) {\n        all_apply(2 * k, _d[k]);\n\
    \        all_apply(2 * k + 1, _d[k]);\n        _d[k] = Monoid::id();\n    }\n\n\
    \   public:\n    // Constructs an empty dual segment tree.\n    DualSegtree()\
    \ : DualSegtree(0) {}\n\n    // Constructs a dual segment tree of size `n`, initialized\
    \ with the identity element.\n    explicit DualSegtree(int n) : DualSegtree(std::vector<T>(n,\
    \ Monoid::id())) {}\n\n    // Constructs a dual segment tree from an existing\
    \ vector.\n    explicit DualSegtree(const std::vector<T>& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n       \
    \ _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size\
    \ + i] = v[i];\n    }\n    explicit DualSegtree(std::vector<T>&& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n       \
    \ _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) _d[_size\
    \ + i] = std::move(v[i]);\n    }\n\n    // Constructs a dual segment tree from\
    \ a vector of a different type U.\n    // It automatically adapts to the Monoid's\
    \ initialization requirements:\n    // 1. Monoid::make(val) if it exists.\n  \
    \  // 2. Monoid::make(val, index) if the monoid requires global indices.\n   \
    \ // 3. static_cast<T>(val) as a fallback for simple monoids.\n    template <typename\
    \ U>\n    requires (!std::same_as<U, T>) && (\n        requires(U x) { Monoid::make(x);\
    \ } ||\n        requires(U x, int i) { Monoid::make(x, i); } ||\n        std::convertible_to<U,\
    \ T>\n    )\n    explicit DualSegtree(const std::vector<U>& v) : _n(int(v.size()))\
    \ {\n        _size = m1une::math::bit_ceil((unsigned int)(_n));\n        _log\
    \ = 0;\n        while ((1U << _log) < (unsigned int)(_size)) _log++;\n       \
    \ _d.assign(2 * _size, Monoid::id());\n        for (int i = 0; i < _n; i++) {\n\
    \            if constexpr (requires(U x) { Monoid::make(x); }) {\n           \
    \     _d[_size + i] = Monoid::make(v[i]);\n            } else if constexpr (requires(U\
    \ x, int idx) { Monoid::make(x, idx); }) {\n                _d[_size + i] = Monoid::make(v[i],\
    \ i);\n            } else {\n                _d[_size + i] = static_cast<T>(v[i]);\n\
    \            }\n        }\n    }\n\n    // Returns the number of elements.\n \
    \   int size() const {\n        return _n;\n    }\n\n    // Returns whether the\
    \ tree is empty.\n    bool empty() const {\n        return _n == 0;\n    }\n\n\
    \    // Assigns x to the p-th element after applying pending updates on its path.\n\
    \    void set(int p, T x) {\n        assert(0 <= p && p < _n);\n        p += _size;\n\
    \        for (int i = _log; i >= 1; i--) push(p >> i);\n        _d[p] = std::move(x);\n\
    \    }\n\n    // Returns the value of the p-th element after applying pending\
    \ updates on its path.\n    T get(int p) {\n        assert(0 <= p && p < _n);\n\
    \        p += _size;\n        for (int i = _log; i >= 1; i--) push(p >> i);\n\
    \        return _d[p];\n    }\n\n    // Returns the value of the p-th element.\n\
    \    T operator[](int p) {\n        return get(p);\n    }\n\n    // Applies x\
    \ to the p-th element.\n    void apply(int p, T x) {\n        assert(0 <= p &&\
    \ p < _n);\n        p += _size;\n        for (int i = _log; i >= 1; i--) push(p\
    \ >> i);\n        all_apply(p, x);\n    }\n\n    // Applies x to all elements\
    \ in the range [l, r).\n    void apply(int l, int r, T x) {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        if (l == r) return;\n\n        l += _size;\n\
    \        r += _size;\n\n        for (int i = _log; i >= 1; i--) {\n          \
    \  if (((l >> i) << i) != l) push(l >> i);\n            if (((r >> i) << i) !=\
    \ r) push((r - 1) >> i);\n        }\n\n        while (l < r) {\n            if\
    \ (l & 1) all_apply(l++, x);\n            if (r & 1) all_apply(--r, x);\n    \
    \        l >>= 1;\n            r >>= 1;\n        }\n    }\n\n    // Returns all\
    \ elements as a vector after applying all pending updates.\n    std::vector<T>\
    \ to_vector() {\n        for (int k = 1; k < _size; k++) push(k);\n        std::vector<T>\
    \ res;\n        res.reserve(_n);\n        for (int i = 0; i < _n; i++) res.push_back(_d[_size\
    \ + i]);\n        return res;\n    }\n\n    // Returns the elements in the range\
    \ [l, r) as a vector.\n    std::vector<T> to_vector(int l, int r) {\n        assert(0\
    \ <= l && l <= r && r <= _n);\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        for (int i = l; i < r; i++) res.push_back(get(i));\n        return\
    \ res;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"\
    verify/ds/segtree/dual_segtree.test.cpp\"\n\n#include <bits/stdc++.h>\n\n#line\
    \ 1 \"math/modint.hpp\"\n\n\n\n#line 6 \"math/modint.hpp\"\n#include <type_traits>\n\
    #line 8 \"math/modint.hpp\"\n\nnamespace m1une {\nnamespace math {\n\ntemplate\
    \ <uint32_t Modulus>\nstruct ModInt {\n    static_assert(0 < Modulus, \"Modulus\
    \ must be positive\");\n\n   private:\n    uint32_t _v;\n\n   public:\n    static\
    \ constexpr uint32_t mod() {\n        return Modulus;\n    }\n\n    static constexpr\
    \ ModInt raw(uint32_t v) noexcept {\n        ModInt x;\n        x._v = v;\n  \
    \      return x;\n    }\n\n    constexpr ModInt() noexcept : _v(0) {}\n\n    template\
    \ <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>\n  \
    \  constexpr ModInt(Integer v) noexcept {\n        if constexpr (std::is_signed_v<Integer>)\
    \ {\n            int64_t x = static_cast<int64_t>(v) % static_cast<int64_t>(Modulus);\n\
    \            if (x < 0) x += Modulus;\n            _v = static_cast<uint32_t>(x);\n\
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
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 9 \"verify/ds/segtree/dual_segtree.test.cpp\"\
    \n\nusing mint = m1une::math::modint998244353;\nusing Affine = m1une::monoid::Affine<mint>;\n\
    \nusing namespace std;\nusing ll = long long;\n\nvoid solve() {\n    ll N, Q;\n\
    \    cin >> N >> Q;\n    vector<Affine::value_type> a(N);\n    for (int i = 0;\
    \ i < N; ++i) {\n        ll x;\n        cin >> x;\n        a[i] = {0, x};\n  \
    \  }\n\n    m1une::ds::DualSegtree<Affine> seg(a);\n    assert(seg.size() == N);\n\
    \    assert(seg.empty() == (N == 0));\n    auto values = seg.to_vector();\n  \
    \  assert(int(values.size()) == N);\n    for (int i = 0; i < N; i++) {\n     \
    \   assert(values[i].second == a[i].second);\n    }\n    for (int q = 0; q < Q;\
    \ ++q) {\n        ll t;\n        cin >> t;\n        if (t == 0) {\n          \
    \  ll l, r, b, c;\n            cin >> l >> r >> b >> c;\n            seg.apply(l,\
    \ r, {b, c});\n        } else {\n            ll i;\n            cin >> i;\n  \
    \          cout << seg.get(i).second << '\\n';\n        }\n    }\n}\n\nint main()\
    \ {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n    solve();\n \
    \   return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_point_get\"\
    \n\n#include \"../../../ds/segtree/dual_segtree.hpp\"\n\n#include <bits/stdc++.h>\n\
    \n#include \"../../../math/modint.hpp\"\n#include \"../../../monoid/affine.hpp\"\
    \n\nusing mint = m1une::math::modint998244353;\nusing Affine = m1une::monoid::Affine<mint>;\n\
    \nusing namespace std;\nusing ll = long long;\n\nvoid solve() {\n    ll N, Q;\n\
    \    cin >> N >> Q;\n    vector<Affine::value_type> a(N);\n    for (int i = 0;\
    \ i < N; ++i) {\n        ll x;\n        cin >> x;\n        a[i] = {0, x};\n  \
    \  }\n\n    m1une::ds::DualSegtree<Affine> seg(a);\n    assert(seg.size() == N);\n\
    \    assert(seg.empty() == (N == 0));\n    auto values = seg.to_vector();\n  \
    \  assert(int(values.size()) == N);\n    for (int i = 0; i < N; i++) {\n     \
    \   assert(values[i].second == a[i].second);\n    }\n    for (int q = 0; q < Q;\
    \ ++q) {\n        ll t;\n        cin >> t;\n        if (t == 0) {\n          \
    \  ll l, r, b, c;\n            cin >> l >> r >> b >> c;\n            seg.apply(l,\
    \ r, {b, c});\n        } else {\n            ll i;\n            cin >> i;\n  \
    \          cout << seg.get(i).second << '\\n';\n        }\n    }\n}\n\nint main()\
    \ {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n    solve();\n \
    \   return 0;\n}\n"
  dependsOn:
  - ds/segtree/dual_segtree.hpp
  - math/bit_ceil.hpp
  - monoid/concept.hpp
  - math/modint.hpp
  - monoid/affine.hpp
  isVerificationFile: true
  path: verify/ds/segtree/dual_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:11:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/dual_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/dual_segtree.test.cpp
- /verify/verify/ds/segtree/dual_segtree.test.cpp.html
title: verify/ds/segtree/dual_segtree.test.cpp
---
