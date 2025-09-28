---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/segtree/segtree.hpp
    title: Segment Tree
  - icon: ':heavy_check_mark:'
    path: math/affine.hpp
    title: math/affine.hpp
  - icon: ':heavy_check_mark:'
    path: monoid/monoid.hpp
    title: Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/monoids/affine_monoid.hpp
    title: monoid/monoids/affine_monoid.hpp
  - icon: ':heavy_check_mark:'
    path: utilities/bit_ceil.hpp
    title: utilities/bit_ceil.hpp
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
  bundledCode: "#line 1 \"verify/data_structure/segtree/segtree.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\n\n#line\
    \ 1 \"data_structure/segtree/segtree.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <functional>\n#include <type_traits>\n#include <vector>\n\n#line 1 \"utilities/bit_ceil.hpp\"\
    \n\n\n\nnamespace m1une {\ntemplate <typename T>\nconstexpr T bit_ceil(T n) {\n\
    \    if (n <= 1) return 1;\n    T x = 1;\n    while (x < n) x <<= 1;\n    return\
    \ x;\n}\n}  // namespace m1une\n\n\n#line 10 \"data_structure/segtree/segtree.hpp\"\
    \n\nnamespace m1une {\n\ntemplate <typename Monoid>\nstruct segment_tree {\n \
    \   using T = typename Monoid::value_type;\n\n   private:\n    int _n;\n    int\
    \ _size;\n    std::vector<T> _data;\n\n    void update(int k) {\n        _data[k]\
    \ = Monoid::op(_data[2 * k], _data[2 * k + 1]);\n    }\n\n   public:\n    segment_tree()\
    \ : segment_tree(0) {}\n    explicit segment_tree(int n) : segment_tree(std::vector<T>(n,\
    \ Monoid::id())) {}\n    explicit segment_tree(const std::vector<T>& v) : _n(v.size())\
    \ {\n        _size = bit_ceil((unsigned int)_n);\n        _data.assign(2 * _size,\
    \ Monoid::id());\n        for (int i = 0; i < _n; i++) {\n            _data[_size\
    \ + i] = v[i];\n        }\n        for (int i = _size - 1; i >= 1; i--) {\n  \
    \          update(i);\n        }\n    }\n\n    // Set value at position p\n  \
    \  void set(int p, T x) {\n        p += _size;\n        _data[p] = x;\n      \
    \  for (int i = 1; p >> i >= 1; i++) {\n            update(p >> i);\n        }\n\
    \    }\n\n    // Get value at position p\n    T get(int p) const {\n        return\
    \ _data[p + _size];\n    }\n\n    // Product of range [l, r)\n    T prod(int l,\
    \ int r) const {\n        T sml = Monoid::id(), smr = Monoid::id();\n        l\
    \ += _size;\n        r += _size;\n        while (l < r) {\n            if (l &\
    \ 1) sml = Monoid::op(sml, _data[l++]);\n            if (r & 1) smr = Monoid::op(_data[--r],\
    \ smr);\n            l >>= 1;\n            r >>= 1;\n        }\n        return\
    \ Monoid::op(sml, smr);\n    }\n\n    // Product of the whole range\n    T all_prod()\
    \ const {\n        return _data[1];\n    }\n\n    // Find max_right r such that\
    \ f(prod([l, r))) is true\n    int max_right(int l, auto f) const {\n        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (l == _n) return _n;\n        l += _size;\n\
    \        T sm = Monoid::id();\n        do {\n            while (l % 2 == 0) l\
    \ >>= 1;\n            if (!f(Monoid::op(sm, _data[l]))) {\n                while\
    \ (l < _size) {\n                    l = (2 * l);\n                    if (f(Monoid::op(sm,\
    \ _data[l]))) {\n                        sm = Monoid::op(sm, _data[l]);\n    \
    \                    l++;\n                    }\n                }\n        \
    \        return l - _size;\n            }\n            sm = Monoid::op(sm, _data[l]);\n\
    \            l++;\n        } while ((l & -l) != l);\n        return _n;\n    }\n\
    \n    // Find min_left l such that f(prod([l, r))) is true\n    int min_left(int\
    \ r, auto f) const {\n        static_assert(std::is_convertible_v<std::invoke_result_t<decltype(f),\
    \ T>, bool>,\n                      \"f must be a callable that takes a Monoid::value_type\
    \ and returns a boolean\");\n        if (r == 0) return 0;\n        r += _size;\n\
    \        T sm = Monoid::id();\n        do {\n            r--;\n            while\
    \ (r > 1 && (r % 2)) r >>= 1;\n            if (!f(Monoid::op(_data[r], sm))) {\n\
    \                while (r < _size) {\n                    r = (2 * r + 1);\n \
    \                   if (f(Monoid::op(_data[r], sm))) {\n                     \
    \   sm = Monoid::op(_data[r], sm);\n                        r--;\n           \
    \         }\n                }\n                return r + 1 - _size;\n      \
    \      }\n            sm = Monoid::op(_data[r], sm);\n        } while ((r & -r)\
    \ != r);\n        return 0;\n    }\n};\n\n}  // namespace m1une\n\n\n#line 4 \"\
    verify/data_structure/segtree/segtree.test.cpp\"\n\n#include <bits/stdc++.h>\n\
    \n#line 1 \"atcoder/modint.hpp\"\n\n\n\n#line 7 \"atcoder/modint.hpp\"\n\n#ifdef\
    \ _MSC_VER\n#include <intrin.h>\n#endif\n\n#line 1 \"atcoder/internal_math.hpp\"\
    \n\n\n\n#line 5 \"atcoder/internal_math.hpp\"\n\n#ifdef _MSC_VER\n#include <intrin.h>\n\
    #endif\n\nnamespace atcoder {\n\nnamespace internal {\n\n// @param m `1 <= m`\n\
    // @return x mod m\nconstexpr long long safe_mod(long long x, long long m) {\n\
    \    x %= m;\n    if (x < 0) x += m;\n    return x;\n}\n\n// Fast modular multiplication\
    \ by barrett reduction\n// Reference: https://en.wikipedia.org/wiki/Barrett_reduction\n\
    // NOTE: reconsider after Ice Lake\nstruct barrett {\n    unsigned int _m;\n \
    \   unsigned long long im;\n\n    // @param m `1 <= m`\n    explicit barrett(unsigned\
    \ int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}\n\n    // @return m\n\
    \    unsigned int umod() const { return _m; }\n\n    // @param a `0 <= a < m`\n\
    \    // @param b `0 <= b < m`\n    // @return `a * b % m`\n    unsigned int mul(unsigned\
    \ int a, unsigned int b) const {\n        // [1] m = 1\n        // a = b = im\
    \ = 0, so okay\n\n        // [2] m >= 2\n        // im = ceil(2^64 / m)\n    \
    \    // -> im * m = 2^64 + r (0 <= r < m)\n        // let z = a*b = c*m + d (0\
    \ <= c, d < m)\n        // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64\
    \ + c*r + d*im\n        // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64\
    \ + m * (m + 1) < 2^64 * 2\n        // ((ab * im) >> 64) == c or c + 1\n     \
    \   unsigned long long z = a;\n        z *= b;\n#ifdef _MSC_VER\n        unsigned\
    \ long long x;\n        _umul128(z, im, &x);\n#else\n        unsigned long long\
    \ x =\n            (unsigned long long)(((unsigned __int128)(z)*im) >> 64);\n\
    #endif\n        unsigned long long y = x * _m;\n        return (unsigned int)(z\
    \ - y + (z < y ? _m : 0));\n    }\n};\n\n// @param n `0 <= n`\n// @param m `1\
    \ <= m`\n// @return `(x ** n) % m`\nconstexpr long long pow_mod_constexpr(long\
    \ long x, long long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m\
    \ = (unsigned int)(m);\n    unsigned long long r = 1;\n    unsigned long long\
    \ y = safe_mod(x, m);\n    while (n) {\n        if (n & 1) r = (r * y) % _m;\n\
    \        y = (y * y) % _m;\n        n >>= 1;\n    }\n    return r;\n}\n\n// Reference:\n\
    // M. Forisek and J. Jancina,\n// Fast Primality Testing for Integers That Fit\
    \ into a Machine Word\n// @param n `0 <= n`\nconstexpr bool is_prime_constexpr(int\
    \ n) {\n    if (n <= 1) return false;\n    if (n == 2 || n == 7 || n == 61) return\
    \ true;\n    if (n % 2 == 0) return false;\n    long long d = n - 1;\n    while\
    \ (d % 2 == 0) d /= 2;\n    constexpr long long bases[3] = {2, 7, 61};\n    for\
    \ (long long a : bases) {\n        long long t = d;\n        long long y = pow_mod_constexpr(a,\
    \ t, n);\n        while (t != n - 1 && y != 1 && y != n - 1) {\n            y\
    \ = y * y % n;\n            t <<= 1;\n        }\n        if (y != n - 1 && t %\
    \ 2 == 0) {\n            return false;\n        }\n    }\n    return true;\n}\n\
    template <int n> constexpr bool is_prime = is_prime_constexpr(n);\n\n// @param\
    \ b `1 <= b`\n// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x\
    \ < b/g\nconstexpr std::pair<long long, long long> inv_gcd(long long a, long long\
    \ b) {\n    a = safe_mod(a, b);\n    if (a == 0) return {b, 0};\n\n    // Contracts:\n\
    \    // [1] s - m0 * a = 0 (mod b)\n    // [2] t - m1 * a = 0 (mod b)\n    //\
    \ [3] s * |m1| + t * |m0| <= b\n    long long s = b, t = a;\n    long long m0\
    \ = 0, m1 = 1;\n\n    while (t) {\n        long long u = s / t;\n        s -=\
    \ t * u;\n        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b\n\n        // [3]:\n\
    \        // (s - t * u) * |m1| + t * |m0 - m1 * u|\n        // <= s * |m1| - t\
    \ * u * |m1| + t * (|m0| + |m1| * u)\n        // = s * |m1| + t * |m0| <= b\n\n\
    \        auto tmp = s;\n        s = t;\n        t = tmp;\n        tmp = m0;\n\
    \        m0 = m1;\n        m1 = tmp;\n    }\n    // by [3]: |m0| <= b/g\n    //\
    \ by g != b: |m0| < b/g\n    if (m0 < 0) m0 += b / s;\n    return {s, m0};\n}\n\
    \n// Compile time primitive root\n// @param m must be prime\n// @return primitive\
    \ root (and minimum in now)\nconstexpr int primitive_root_constexpr(int m) {\n\
    \    if (m == 2) return 1;\n    if (m == 167772161) return 3;\n    if (m == 469762049)\
    \ return 3;\n    if (m == 754974721) return 11;\n    if (m == 998244353) return\
    \ 3;\n    int divs[20] = {};\n    divs[0] = 2;\n    int cnt = 1;\n    int x =\
    \ (m - 1) / 2;\n    while (x % 2 == 0) x /= 2;\n    for (int i = 3; (long long)(i)*i\
    \ <= x; i += 2) {\n        if (x % i == 0) {\n            divs[cnt++] = i;\n \
    \           while (x % i == 0) {\n                x /= i;\n            }\n   \
    \     }\n    }\n    if (x > 1) {\n        divs[cnt++] = x;\n    }\n    for (int\
    \ g = 2;; g++) {\n        bool ok = true;\n        for (int i = 0; i < cnt; i++)\
    \ {\n            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {\n    \
    \            ok = false;\n                break;\n            }\n        }\n \
    \       if (ok) return g;\n    }\n}\ntemplate <int m> constexpr int primitive_root\
    \ = primitive_root_constexpr(m);\n\n// @param n `n < 2^32`\n// @param m `1 <=\
    \ m < 2^32`\n// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)\nunsigned\
    \ long long floor_sum_unsigned(unsigned long long n,\n                       \
    \               unsigned long long m,\n                                      unsigned\
    \ long long a,\n                                      unsigned long long b) {\n\
    \    unsigned long long ans = 0;\n    while (true) {\n        if (a >= m) {\n\
    \            ans += n * (n - 1) / 2 * (a / m);\n            a %= m;\n        }\n\
    \        if (b >= m) {\n            ans += n * (b / m);\n            b %= m;\n\
    \        }\n\n        unsigned long long y_max = a * n + b;\n        if (y_max\
    \ < m) break;\n        // y_max < m * (n + 1)\n        // floor(y_max / m) <=\
    \ n\n        n = (unsigned long long)(y_max / m);\n        b = (unsigned long\
    \ long)(y_max % m);\n        std::swap(m, a);\n    }\n    return ans;\n}\n\n}\
    \  // namespace internal\n\n}  // namespace atcoder\n\n\n#line 1 \"atcoder/internal_type_traits.hpp\"\
    \n\n\n\n#line 7 \"atcoder/internal_type_traits.hpp\"\n\nnamespace atcoder {\n\n\
    namespace internal {\n\n#ifndef _MSC_VER\ntemplate <class T>\nusing is_signed_int128\
    \ =\n    typename std::conditional<std::is_same<T, __int128_t>::value ||\n   \
    \                               std::is_same<T, __int128>::value,\n          \
    \                    std::true_type,\n                              std::false_type>::type;\n\
    \ntemplate <class T>\nusing is_unsigned_int128 =\n    typename std::conditional<std::is_same<T,\
    \ __uint128_t>::value ||\n                                  std::is_same<T, unsigned\
    \ __int128>::value,\n                              std::true_type,\n         \
    \                     std::false_type>::type;\n\ntemplate <class T>\nusing make_unsigned_int128\
    \ =\n    typename std::conditional<std::is_same<T, __int128_t>::value,\n     \
    \                         __uint128_t,\n                              unsigned\
    \ __int128>;\n\ntemplate <class T>\nusing is_integral = typename std::conditional<std::is_integral<T>::value\
    \ ||\n                                                  is_signed_int128<T>::value\
    \ ||\n                                                  is_unsigned_int128<T>::value,\n\
    \                                              std::true_type,\n             \
    \                                 std::false_type>::type;\n\ntemplate <class T>\n\
    using is_signed_int = typename std::conditional<(is_integral<T>::value &&\n  \
    \                                               std::is_signed<T>::value) ||\n\
    \                                                    is_signed_int128<T>::value,\n\
    \                                                std::true_type,\n           \
    \                                     std::false_type>::type;\n\ntemplate <class\
    \ T>\nusing is_unsigned_int =\n    typename std::conditional<(is_integral<T>::value\
    \ &&\n                               std::is_unsigned<T>::value) ||\n        \
    \                          is_unsigned_int128<T>::value,\n                   \
    \           std::true_type,\n                              std::false_type>::type;\n\
    \ntemplate <class T>\nusing to_unsigned = typename std::conditional<\n    is_signed_int128<T>::value,\n\
    \    make_unsigned_int128<T>,\n    typename std::conditional<std::is_signed<T>::value,\n\
    \                              std::make_unsigned<T>,\n                      \
    \        std::common_type<T>>::type>::type;\n\n#else\n\ntemplate <class T> using\
    \ is_integral = typename std::is_integral<T>;\n\ntemplate <class T>\nusing is_signed_int\
    \ =\n    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,\n\
    \                              std::true_type,\n                             \
    \ std::false_type>::type;\n\ntemplate <class T>\nusing is_unsigned_int =\n   \
    \ typename std::conditional<is_integral<T>::value &&\n                       \
    \           std::is_unsigned<T>::value,\n                              std::true_type,\n\
    \                              std::false_type>::type;\n\ntemplate <class T>\n\
    using to_unsigned = typename std::conditional<is_signed_int<T>::value,\n     \
    \                                         std::make_unsigned<T>,\n           \
    \                                   std::common_type<T>>::type;\n\n#endif\n\n\
    template <class T>\nusing is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;\n\
    \ntemplate <class T>\nusing is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;\n\
    \ntemplate <class T> using to_unsigned_t = typename to_unsigned<T>::type;\n\n\
    }  // namespace internal\n\n}  // namespace atcoder\n\n\n#line 14 \"atcoder/modint.hpp\"\
    \n\nnamespace atcoder {\n\nnamespace internal {\n\nstruct modint_base {};\nstruct\
    \ static_modint_base : modint_base {};\n\ntemplate <class T> using is_modint =\
    \ std::is_base_of<modint_base, T>;\ntemplate <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
    \n}  // namespace internal\n\ntemplate <int m, std::enable_if_t<(1 <= m)>* = nullptr>\n\
    struct static_modint : internal::static_modint_base {\n    using mint = static_modint;\n\
    \n  public:\n    static constexpr int mod() { return m; }\n    static mint raw(int\
    \ v) {\n        mint x;\n        x._v = v;\n        return x;\n    }\n\n    static_modint()\
    \ : _v(0) {}\n    template <class T, internal::is_signed_int_t<T>* = nullptr>\n\
    \    static_modint(T v) {\n        long long x = (long long)(v % (long long)(umod()));\n\
    \        if (x < 0) x += umod();\n        _v = (unsigned int)(x);\n    }\n   \
    \ template <class T, internal::is_unsigned_int_t<T>* = nullptr>\n    static_modint(T\
    \ v) {\n        _v = (unsigned int)(v % umod());\n    }\n\n    int val() const\
    \ { return _v; }\n\n    mint& operator++() {\n        _v++;\n        if (_v ==\
    \ umod()) _v = 0;\n        return *this;\n    }\n    mint& operator--() {\n  \
    \      if (_v == 0) _v = umod();\n        _v--;\n        return *this;\n    }\n\
    \    mint operator++(int) {\n        mint result = *this;\n        ++*this;\n\
    \        return result;\n    }\n    mint operator--(int) {\n        mint result\
    \ = *this;\n        --*this;\n        return result;\n    }\n\n    mint& operator+=(const\
    \ mint& rhs) {\n        _v += rhs._v;\n        if (_v >= umod()) _v -= umod();\n\
    \        return *this;\n    }\n    mint& operator-=(const mint& rhs) {\n     \
    \   _v -= rhs._v;\n        if (_v >= umod()) _v += umod();\n        return *this;\n\
    \    }\n    mint& operator*=(const mint& rhs) {\n        unsigned long long z\
    \ = _v;\n        z *= rhs._v;\n        _v = (unsigned int)(z % umod());\n    \
    \    return *this;\n    }\n    mint& operator/=(const mint& rhs) { return *this\
    \ = *this * rhs.inv(); }\n\n    mint operator+() const { return *this; }\n   \
    \ mint operator-() const { return mint() - *this; }\n\n    mint pow(long long\
    \ n) const {\n        assert(0 <= n);\n        mint x = *this, r = 1;\n      \
    \  while (n) {\n            if (n & 1) r *= x;\n            x *= x;\n        \
    \    n >>= 1;\n        }\n        return r;\n    }\n    mint inv() const {\n \
    \       if (prime) {\n            assert(_v);\n            return pow(umod() -\
    \ 2);\n        } else {\n            auto eg = internal::inv_gcd(_v, m);\n   \
    \         assert(eg.first == 1);\n            return eg.second;\n        }\n \
    \   }\n\n    friend mint operator+(const mint& lhs, const mint& rhs) {\n     \
    \   return mint(lhs) += rhs;\n    }\n    friend mint operator-(const mint& lhs,\
    \ const mint& rhs) {\n        return mint(lhs) -= rhs;\n    }\n    friend mint\
    \ operator*(const mint& lhs, const mint& rhs) {\n        return mint(lhs) *= rhs;\n\
    \    }\n    friend mint operator/(const mint& lhs, const mint& rhs) {\n      \
    \  return mint(lhs) /= rhs;\n    }\n    friend bool operator==(const mint& lhs,\
    \ const mint& rhs) {\n        return lhs._v == rhs._v;\n    }\n    friend bool\
    \ operator!=(const mint& lhs, const mint& rhs) {\n        return lhs._v != rhs._v;\n\
    \    }\n\n  private:\n    unsigned int _v;\n    static constexpr unsigned int\
    \ umod() { return m; }\n    static constexpr bool prime = internal::is_prime<m>;\n\
    };\n\ntemplate <int id> struct dynamic_modint : internal::modint_base {\n    using\
    \ mint = dynamic_modint;\n\n  public:\n    static int mod() { return (int)(bt.umod());\
    \ }\n    static void set_mod(int m) {\n        assert(1 <= m);\n        bt = internal::barrett(m);\n\
    \    }\n    static mint raw(int v) {\n        mint x;\n        x._v = v;\n   \
    \     return x;\n    }\n\n    dynamic_modint() : _v(0) {}\n    template <class\
    \ T, internal::is_signed_int_t<T>* = nullptr>\n    dynamic_modint(T v) {\n   \
    \     long long x = (long long)(v % (long long)(mod()));\n        if (x < 0) x\
    \ += mod();\n        _v = (unsigned int)(x);\n    }\n    template <class T, internal::is_unsigned_int_t<T>*\
    \ = nullptr>\n    dynamic_modint(T v) {\n        _v = (unsigned int)(v % mod());\n\
    \    }\n\n    int val() const { return _v; }\n\n    mint& operator++() {\n   \
    \     _v++;\n        if (_v == umod()) _v = 0;\n        return *this;\n    }\n\
    \    mint& operator--() {\n        if (_v == 0) _v = umod();\n        _v--;\n\
    \        return *this;\n    }\n    mint operator++(int) {\n        mint result\
    \ = *this;\n        ++*this;\n        return result;\n    }\n    mint operator--(int)\
    \ {\n        mint result = *this;\n        --*this;\n        return result;\n\
    \    }\n\n    mint& operator+=(const mint& rhs) {\n        _v += rhs._v;\n   \
    \     if (_v >= umod()) _v -= umod();\n        return *this;\n    }\n    mint&\
    \ operator-=(const mint& rhs) {\n        _v += mod() - rhs._v;\n        if (_v\
    \ >= umod()) _v -= umod();\n        return *this;\n    }\n    mint& operator*=(const\
    \ mint& rhs) {\n        _v = bt.mul(_v, rhs._v);\n        return *this;\n    }\n\
    \    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }\n\
    \n    mint operator+() const { return *this; }\n    mint operator-() const { return\
    \ mint() - *this; }\n\n    mint pow(long long n) const {\n        assert(0 <=\
    \ n);\n        mint x = *this, r = 1;\n        while (n) {\n            if (n\
    \ & 1) r *= x;\n            x *= x;\n            n >>= 1;\n        }\n       \
    \ return r;\n    }\n    mint inv() const {\n        auto eg = internal::inv_gcd(_v,\
    \ mod());\n        assert(eg.first == 1);\n        return eg.second;\n    }\n\n\
    \    friend mint operator+(const mint& lhs, const mint& rhs) {\n        return\
    \ mint(lhs) += rhs;\n    }\n    friend mint operator-(const mint& lhs, const mint&\
    \ rhs) {\n        return mint(lhs) -= rhs;\n    }\n    friend mint operator*(const\
    \ mint& lhs, const mint& rhs) {\n        return mint(lhs) *= rhs;\n    }\n   \
    \ friend mint operator/(const mint& lhs, const mint& rhs) {\n        return mint(lhs)\
    \ /= rhs;\n    }\n    friend bool operator==(const mint& lhs, const mint& rhs)\
    \ {\n        return lhs._v == rhs._v;\n    }\n    friend bool operator!=(const\
    \ mint& lhs, const mint& rhs) {\n        return lhs._v != rhs._v;\n    }\n\n \
    \ private:\n    unsigned int _v;\n    static internal::barrett bt;\n    static\
    \ unsigned int umod() { return bt.umod(); }\n};\ntemplate <int id> internal::barrett\
    \ dynamic_modint<id>::bt(998244353);\n\nusing modint998244353 = static_modint<998244353>;\n\
    using modint1000000007 = static_modint<1000000007>;\nusing modint = dynamic_modint<-1>;\n\
    \nnamespace internal {\n\ntemplate <class T>\nusing is_static_modint = std::is_base_of<internal::static_modint_base,\
    \ T>;\n\ntemplate <class T>\nusing is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;\n\
    \ntemplate <class> struct is_dynamic_modint : public std::false_type {};\ntemplate\
    \ <int id>\nstruct is_dynamic_modint<dynamic_modint<id>> : public std::true_type\
    \ {};\n\ntemplate <class T>\nusing is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;\n\
    \n}  // namespace internal\n\n}  // namespace atcoder\n\n\n#line 1 \"math/affine.hpp\"\
    \n\n\n\n#line 5 \"math/affine.hpp\"\n\nnamespace m1une {\ntemplate <typename T>\n\
    T affine(std::pair<T, T> f, T x) {\n    return f.first * x + f.second;\n}\n} \
    \ // namespace m1une\n\n\n#line 1 \"monoid/monoids/affine_monoid.hpp\"\n\n\n\n\
    #line 5 \"monoid/monoids/affine_monoid.hpp\"\n\n#line 1 \"monoid/monoid.hpp\"\n\
    \n\n\n#line 6 \"monoid/monoid.hpp\"\n\nnamespace m1une {\n\ntemplate <typename\
    \ T, auto operation, auto identity, bool commutative>\nstruct monoid {\n    static_assert(std::is_convertible_v<decltype(operation),\
    \ std::function<T(T, T)>>, \"operation must work as T(T, T)\");\n    static_assert(std::is_convertible_v<decltype(identity),\
    \ std::function<T()>>, \"identity must work as T()\");\n\n    using value_type\
    \ = T;\n    static constexpr auto op = operation;\n    static constexpr auto id\
    \ = identity;\n    static constexpr bool is_commutative = commutative;\n};\n\n\
    }  // namespace m1une\n\n\n#line 7 \"monoid/monoids/affine_monoid.hpp\"\n\nnamespace\
    \ m1une {\n\n// Affine transformation f(x) = ax + b is represented as (a, b)\n\
    // perform f first, then g\n// op(f, g)(x) = g(f(x))\ntemplate <typename T>\n\
    using affine_monoid = monoid<std::pair<T, T>,\n                             [](std::pair<T,\
    \ T> f, std::pair<T, T> g) {\n                                 return std::pair<T,\
    \ T>(f.first * g.first, f.second * g.first + g.second);\n                    \
    \         },\n                             []() { return std::pair<T, T>(1, 0);\
    \ }, false>;\n\n}  // namespace m1une\n\n\n#line 10 \"verify/data_structure/segtree/segtree.test.cpp\"\
    \n\nusing mint = atcoder::modint998244353;\nusing namespace std;\nusing namespace\
    \ m1une;\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n   \
    \ std::cin.tie(NULL);\n}\n\nint main() {\n    fast_io();\n    int N, Q;\n    cin\
    \ >> N >> Q;\n    vector<pair<mint, mint>> f(N);\n    for (int i = 0; i < N; ++i)\
    \ {\n        int a, b;\n        cin >> a >> b;\n        f[i] = {a, b};\n    }\n\
    \    segment_tree<affine_monoid<mint>> seg(f);\n    while (Q--) {\n        int\
    \ t;\n        cin >> t;\n        if (t == 0) {\n            int p, c, d;\n   \
    \         cin >> p >> c >> d;\n            seg.set(p, {c, d});\n        } else\
    \ {\n            int l, r, x;\n            cin >> l >> r >> x;\n            cout\
    \ << affine(seg.prod(l, r), mint(x)).val() << \"\\n\";\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n\n#include \"data_structure/segtree/segtree.hpp\"\n\n#include <bits/stdc++.h>\n\
    \n#include \"atcoder/modint.hpp\"\n#include \"math/affine.hpp\"\n#include \"monoid/monoids/affine_monoid.hpp\"\
    \n\nusing mint = atcoder::modint998244353;\nusing namespace std;\nusing namespace\
    \ m1une;\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n   \
    \ std::cin.tie(NULL);\n}\n\nint main() {\n    fast_io();\n    int N, Q;\n    cin\
    \ >> N >> Q;\n    vector<pair<mint, mint>> f(N);\n    for (int i = 0; i < N; ++i)\
    \ {\n        int a, b;\n        cin >> a >> b;\n        f[i] = {a, b};\n    }\n\
    \    segment_tree<affine_monoid<mint>> seg(f);\n    while (Q--) {\n        int\
    \ t;\n        cin >> t;\n        if (t == 0) {\n            int p, c, d;\n   \
    \         cin >> p >> c >> d;\n            seg.set(p, {c, d});\n        } else\
    \ {\n            int l, r, x;\n            cin >> l >> r >> x;\n            cout\
    \ << affine(seg.prod(l, r), mint(x)).val() << \"\\n\";\n        }\n    }\n}\n"
  dependsOn:
  - data_structure/segtree/segtree.hpp
  - utilities/bit_ceil.hpp
  - math/affine.hpp
  - monoid/monoids/affine_monoid.hpp
  - monoid/monoid.hpp
  isVerificationFile: true
  path: verify/data_structure/segtree/segtree.test.cpp
  requiredBy: []
  timestamp: '2025-09-29 00:58:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/segtree/segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/segtree/segtree.test.cpp
- /verify/verify/data_structure/segtree/segtree.test.cpp.html
title: verify/data_structure/segtree/segtree.test.cpp
---
