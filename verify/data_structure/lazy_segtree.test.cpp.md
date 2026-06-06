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
    path: data_structure/lazy_segtree.hpp
    title: Lazy Segment Tree
  - icon: ':heavy_check_mark:'
    path: utilities/bit_ceil.hpp
    title: Bit Ceil
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
    - https://zenn.dev/sassan/articles/19db660e4da0a4
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ verify/data_structure/lazy_segtree.test.cpp: line 810: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_affine_range_sum\"\
    \n\n#ifdef LOCAL\n#define _GLIBCXX_DEBUG\n#pragma GCC optimize(\"O0\")\n#else\n\
    #pragma GCC optimize(\"O3\")\n#pragma GCC optimize(\"unroll-loops\")\n#endif\n\
    \n#include <bits/stdc++.h>\n// #include <bits/extc++.h>\nusing namespace std;\n\
    \n\n#include <cassert>\n#include <numeric>\n#include <type_traits>\n\n#ifdef _MSC_VER\n\
    #include <intrin.h>\n#endif\n\n\n#include <utility>\n\n#ifdef _MSC_VER\n#include\
    \ <intrin.h>\n#endif\n\nnamespace atcoder {\n\nnamespace internal {\n\nconstexpr\
    \ long long safe_mod(long long x, long long m) {\n    x %= m;\n    if (x < 0)\
    \ x += m;\n    return x;\n}\n\nstruct barrett {\n    unsigned int _m;\n    unsigned\
    \ long long im;\n\n    explicit barrett(unsigned int m) : _m(m), im((unsigned\
    \ long long)(-1) / m + 1) {}\n\n    unsigned int umod() const { return _m; }\n\
    \n    unsigned int mul(unsigned int a, unsigned int b) const {\n\n        unsigned\
    \ long long z = a;\n        z *= b;\n#ifdef _MSC_VER\n        unsigned long long\
    \ x;\n        _umul128(z, im, &x);\n#else\n        unsigned long long x =\n  \
    \          (unsigned long long)(((unsigned __int128)(z)*im) >> 64);\n#endif\n\
    \        unsigned long long y = x * _m;\n        return (unsigned int)(z - y +\
    \ (z < y ? _m : 0));\n    }\n};\n\nconstexpr long long pow_mod_constexpr(long\
    \ long x, long long n, int m) {\n    if (m == 1) return 0;\n    unsigned int _m\
    \ = (unsigned int)(m);\n    unsigned long long r = 1;\n    unsigned long long\
    \ y = safe_mod(x, m);\n    while (n) {\n        if (n & 1) r = (r * y) % _m;\n\
    \        y = (y * y) % _m;\n        n >>= 1;\n    }\n    return r;\n}\n\nconstexpr\
    \ bool is_prime_constexpr(int n) {\n    if (n <= 1) return false;\n    if (n ==\
    \ 2 || n == 7 || n == 61) return true;\n    if (n % 2 == 0) return false;\n  \
    \  long long d = n - 1;\n    while (d % 2 == 0) d /= 2;\n    constexpr long long\
    \ bases[3] = {2, 7, 61};\n    for (long long a : bases) {\n        long long t\
    \ = d;\n        long long y = pow_mod_constexpr(a, t, n);\n        while (t !=\
    \ n - 1 && y != 1 && y != n - 1) {\n            y = y * y % n;\n            t\
    \ <<= 1;\n        }\n        if (y != n - 1 && t % 2 == 0) {\n            return\
    \ false;\n        }\n    }\n    return true;\n}\ntemplate <int n> constexpr bool\
    \ is_prime = is_prime_constexpr(n);\n\nconstexpr std::pair<long long, long long>\
    \ inv_gcd(long long a, long long b) {\n    a = safe_mod(a, b);\n    if (a == 0)\
    \ return {b, 0};\n\n    long long s = b, t = a;\n    long long m0 = 0, m1 = 1;\n\
    \n    while (t) {\n        long long u = s / t;\n        s -= t * u;\n       \
    \ m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b\n\n\n        auto tmp = s;\n   \
    \     s = t;\n        t = tmp;\n        tmp = m0;\n        m0 = m1;\n        m1\
    \ = tmp;\n    }\n    if (m0 < 0) m0 += b / s;\n    return {s, m0};\n}\n\nconstexpr\
    \ int primitive_root_constexpr(int m) {\n    if (m == 2) return 1;\n    if (m\
    \ == 167772161) return 3;\n    if (m == 469762049) return 3;\n    if (m == 754974721)\
    \ return 11;\n    if (m == 998244353) return 3;\n    int divs[20] = {};\n    divs[0]\
    \ = 2;\n    int cnt = 1;\n    int x = (m - 1) / 2;\n    while (x % 2 == 0) x /=\
    \ 2;\n    for (int i = 3; (long long)(i)*i <= x; i += 2) {\n        if (x % i\
    \ == 0) {\n            divs[cnt++] = i;\n            while (x % i == 0) {\n  \
    \              x /= i;\n            }\n        }\n    }\n    if (x > 1) {\n  \
    \      divs[cnt++] = x;\n    }\n    for (int g = 2;; g++) {\n        bool ok =\
    \ true;\n        for (int i = 0; i < cnt; i++) {\n            if (pow_mod_constexpr(g,\
    \ (m - 1) / divs[i], m) == 1) {\n                ok = false;\n               \
    \ break;\n            }\n        }\n        if (ok) return g;\n    }\n}\ntemplate\
    \ <int m> constexpr int primitive_root = primitive_root_constexpr(m);\n\nunsigned\
    \ long long floor_sum_unsigned(unsigned long long n,\n                       \
    \               unsigned long long m,\n                                      unsigned\
    \ long long a,\n                                      unsigned long long b) {\n\
    \    unsigned long long ans = 0;\n    while (true) {\n        if (a >= m) {\n\
    \            ans += n * (n - 1) / 2 * (a / m);\n            a %= m;\n        }\n\
    \        if (b >= m) {\n            ans += n * (b / m);\n            b %= m;\n\
    \        }\n\n        unsigned long long y_max = a * n + b;\n        if (y_max\
    \ < m) break;\n        n = (unsigned long long)(y_max / m);\n        b = (unsigned\
    \ long long)(y_max % m);\n        std::swap(m, a);\n    }\n    return ans;\n}\n\
    \n}  // namespace internal\n\n}  // namespace atcoder\n\n\n#include <cassert>\n\
    #include <numeric>\n#include <type_traits>\n\nnamespace atcoder {\n\nnamespace\
    \ internal {\n\n#ifndef _MSC_VER\ntemplate <class T>\nusing is_signed_int128 =\n\
    \    typename std::conditional<std::is_same<T, __int128_t>::value ||\n       \
    \                           std::is_same<T, __int128>::value,\n              \
    \                std::true_type,\n                              std::false_type>::type;\n\
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
    }  // namespace internal\n\n}  // namespace atcoder\n\n\nnamespace atcoder {\n\
    \nnamespace internal {\n\nstruct modint_base {};\nstruct static_modint_base :\
    \ modint_base {};\n\ntemplate <class T> using is_modint = std::is_base_of<modint_base,\
    \ T>;\ntemplate <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;\n\
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
    \n}  // namespace internal\n\n}  // namespace atcoder\n\nusing mint = atcoder::modint998244353;\n\
    istream& operator>>(istream& in, mint& x) {\n    long long a;\n    in >> a;\n\
    \    x = a;\n    return in;\n}\nostream& operator<<(ostream& out, const mint&\
    \ x) {\n    return out << x.val();\n}\n\nusing ll = long long;\nusing u32 = unsigned\
    \ int;\nusing u64 = unsigned long long;\nusing i128 = __int128;\nusing u128 =\
    \ unsigned __int128;\nusing f128 = __float128;\n\ntemplate <class T>\nconstexpr\
    \ T infty = 0;\ntemplate <>\nconstexpr int infty<int> = 1'000'000'000;\ntemplate\
    \ <>\nconstexpr ll infty<ll> = ll(infty<int>) * infty<int> * 2;\ntemplate <>\n\
    constexpr u32 infty<u32> = infty<int>;\ntemplate <>\nconstexpr u64 infty<u64>\
    \ = infty<ll>;\ntemplate <>\nconstexpr i128 infty<i128> = i128(infty<ll>) * infty<ll>;\n\
    template <>\nconstexpr double infty<double> = infty<ll>;\ntemplate <>\nconstexpr\
    \ long double infty<long double> = infty<ll>;\n\nusing pi = pair<int, int>;\n\
    using pl = pair<ll, ll>;\nusing vi = vector<int>;\nusing vl = vector<ll>;\ntemplate\
    \ <class T>\nusing vc = vector<T>;\ntemplate <class T>\nusing vvc = vector<vc<T>>;\n\
    using vvi = vvc<int>;\nusing vvl = vvc<ll>;\ntemplate <class T>\nusing vvvc =\
    \ vector<vvc<T>>;\ntemplate <class T>\nusing vvvvc = vector<vvvc<T>>;\ntemplate\
    \ <class T>\nusing vvvvvc = vector<vvvvc<T>>;\ntemplate <class T>\nusing pqg =\
    \ std::priority_queue<T, vector<T>, greater<T>>;\ntemplate <class T, class U>\n\
    using umap = unordered_map<T, U>;\n\n// template <typename K>\n// using tree =\
    \ __gnu_pbds::tree<K, __gnu_pbds::null_type, std::less<>,\n//                \
    \               __gnu_pbds::rb_tree_tag,\n//                               __gnu_pbds::tree_order_statistics_node_update>;\n\
    \n#define vv(type, name, h, ...) vector<vector<type>> name(h, vector<type>(__VA_ARGS__))\n\
    #define vvv(type, name, h, w, ...) \\\n    vector<vector<vector<type>>> name(h,\
    \ vector<vector<type>>(w, vector<type>(__VA_ARGS__)))\n#define vvvv(type, name,\
    \ a, b, c, ...)         \\\n    vector<vector<vector<vector<type>>>> name( \\\n\
    \        a, vector<vector<vector<type>>>(b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))\n\
    \n#define FOR1(a) for (ll _ = 0; _ < (ll)a; ++_)\n#define FOR2(i, a) for (ll i\
    \ = 0; i < (ll)a; ++i)\n#define FOR3(i, a, b) for (ll i = a; i < (ll)b; ++i)\n\
    #define FOR4(i, a, b, c) for (ll i = a; i < (ll)b; i += (c))\n#define FOR1_R(a)\
    \ for (ll i = (a) - 1; i >= 0; --i)\n#define FOR2_R(i, a) for (ll i = (a) - 1;\
    \ i >= 0; --i)\n#define FOR3_R(i, a, b) for (ll i = (b) - 1; i >= (ll)a; --i)\n\
    #define overload4(a, b, c, d, e, ...) e\n#define overload3(a, b, c, d, ...) d\n\
    #define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)\n\
    #define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)\n\
    \n#define FOR_subset(t, s) for (int t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1)\
    \ & (s)))\n#define all(x) x.begin(), x.end()\n#define rall(x) x.rbegin(), x.rend()\n\
    \nint popcnt(int x) {\n    return __builtin_popcount(x);\n}\nint popcnt(u32 x)\
    \ {\n    return __builtin_popcount(x);\n}\nint popcnt(ll x) {\n    return __builtin_popcountll(x);\n\
    }\nint popcnt(u64 x) {\n    return __builtin_popcountll(x);\n}\nint popcnt_mod_2(int\
    \ x) {\n    return __builtin_parity(x);\n}\nint popcnt_mod_2(u32 x) {\n    return\
    \ __builtin_parity(x);\n}\nint popcnt_mod_2(ll x) {\n    return __builtin_parityll(x);\n\
    }\nint popcnt_mod_2(u64 x) {\n    return __builtin_parityll(x);\n}\n// (0, 1,\
    \ 2, 3, 4) -> (-1, 0, 1, 1, 2)\nint topbit(int x) {\n    return (x == 0 ? -1 :\
    \ 31 - __builtin_clz(x));\n}\nint topbit(u32 x) {\n    return (x == 0 ? -1 : 31\
    \ - __builtin_clz(x));\n}\nint topbit(ll x) {\n    return (x == 0 ? -1 : 63 -\
    \ __builtin_clzll(x));\n}\nint topbit(u64 x) {\n    return (x == 0 ? -1 : 63 -\
    \ __builtin_clzll(x));\n}\n// (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)\nint lowbit(int\
    \ x) {\n    return (x == 0 ? -1 : __builtin_ctz(x));\n}\nint lowbit(u32 x) {\n\
    \    return (x == 0 ? -1 : __builtin_ctz(x));\n}\nint lowbit(ll x) {\n    return\
    \ (x == 0 ? -1 : __builtin_ctzll(x));\n}\nint lowbit(u64 x) {\n    return (x ==\
    \ 0 ? -1 : __builtin_ctzll(x));\n}\n\ntemplate <typename T>\nT floor(T a, T b)\
    \ {\n    return a / b - (a % b && (a ^ b) < 0);\n}\ntemplate <typename T>\nT ceil(T\
    \ x, T y) {\n    return floor(x + y - 1, y);\n}\ntemplate <typename T>\nT bmod(T\
    \ x, T y) {\n    return x - y * floor(x, y);\n}\ntemplate <typename T>\npair<T,\
    \ T> divmod(T x, T y) {\n    T q = floor(x, y);\n    return {q, x - q * y};\n\
    }\n\ntemplate <typename T, typename U>\nT POW(U x_, int n) {\n    T x = x_;\n\
    \    T ret = 1;\n    while (n > 0) {\n        if (n & 1) ret *= x;\n        x\
    \ *= x;\n        n >>= 1;\n    }\n    return ret;\n}\n\ntemplate <typename T,\
    \ typename U>\nT SUM(const vector<U>& A) {\n    T sm = 0;\n    for (auto&& a :\
    \ A) sm += a;\n    return sm;\n}\n\n#define LB(c, x) distance((c).begin(), lower_bound(all(c),\
    \ (x)))\n#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))\n#define\
    \ UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()\n\
    \ntemplate <class T, class S>\ninline bool chmax(T& a, const S& b) {\n    return\
    \ (a < b ? a = b, 1 : 0);\n}\ntemplate <class T, class S>\ninline bool chmin(T&\
    \ a, const S& b) {\n    return (a > b ? a = b, 1 : 0);\n}\n\n// ? \u306F -1\n\
    vc<int> s_to_vi(const string& S, char first_char) {\n    vc<int> A(S.size());\n\
    \    FOR(i, S.size()) {\n        A[i] = (S[i] != '?' ? S[i] - first_char : -1);\n\
    \    }\n    return A;\n}\n\ntemplate <typename T, typename U>\nvector<T> cumsum(vector<U>&\
    \ A, int off = 1) {\n    int N = A.size();\n    vector<T> B(N + 1);\n    FOR(i,\
    \ N) {\n        B[i + 1] = B[i] + A[i];\n    }\n    if (off == 0) B.erase(B.begin());\n\
    \    return B;\n}\n\ntemplate <typename T>\nvector<int> argsort(const vector<T>&\
    \ A) {\n    vector<int> ids(A.size());\n    iota(all(ids), 0);\n    sort(all(ids),\
    \ [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });\n    return\
    \ ids;\n}\n\n// A[I[0]], A[I[1]], ...\ntemplate <typename T>\nvc<T> rearrange(const\
    \ vc<T>& A, const vc<int>& I) {\n    vc<T> B(I.size());\n    FOR(i, I.size())\
    \ B[i] = A[I[i]];\n    return B;\n}\n\ntemplate <class... T>\nconstexpr auto min(T...\
    \ a) {\n    return min(initializer_list<common_type_t<T...>>{a...});\n}\ntemplate\
    \ <class... T>\nconstexpr auto max(T... a) {\n    return max(initializer_list<common_type_t<T...>>{a...});\n\
    }\n\nvoid print() {\n    cout << '\\n';\n}\ntemplate <class T>\nvoid print(const\
    \ T& a) {\n    cout << a << '\\n';\n}\ntemplate <class T, class... Ts>\nvoid print(const\
    \ T& a, const Ts&... b) {\n    cout << a;\n    (cout << ... << (cout << ' ', b));\n\
    \    cout << '\\n';\n}\ntemplate <class T>\nvoid print(vector<T>& a) {\n    for\
    \ (int i = 0; i < (int)a.size(); ++i) {\n        cout << a[i] << \" \\n\"[i ==\
    \ (int)a.size() - 1];\n    }\n}\ntemplate <class T>\nvoid print(vector<vector<T>>&\
    \ a) {\n    for (int i = 0; i < (int)a.size(); ++i) {\n        for (int j = 0;\
    \ j < (int)a[i].size(); ++j) {\n            cout << a[i][j] << \" \\n\"[j == (int)a[i].size()\
    \ - 1];\n        }\n    }\n}\nvoid YESNO(bool b) {\n    cout << (b ? \"YES\" :\
    \ \"NO\") << endl;\n}\nvoid YesNo(bool b) {\n    cout << (b ? \"Yes\" : \"No\"\
    ) << endl;\n}\n\n#ifdef LOCAL\n// https://zenn.dev/sassan/articles/19db660e4da0a4\n\
    #include \"/Library/cpp-dump/dump.hpp\"\n#define dump(...) cpp_dump(__VA_ARGS__)\n\
    CPP_DUMP_DEFINE_EXPORT_OBJECT(mint, val());\n#else\n#define dump(...)\n#define\
    \ CPP_DUMP_SET_OPTION(...)\n#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)\n#define\
    \ CPP_DUMP_DEFINE_EXPORT_ENUM(...)\n#define CPP_DUMP_DEFINE_DANGEROUS_EXPORT_OBJECT(...)\n\
    #endif\n\n//----------------------------------------------------------------\n\
    #include \"acted_monoid/range_affine_range_sum.hpp\"\n#include \"data_structure/lazy_segtree.hpp\"\
    \nusing AM = m1une::acted_monoid::RangeAffineRangeSum<mint>;\n\nvoid solve() {\n\
    \    ll N, Q;\n    cin >> N >> Q;\n    vl a(N);\n    FOR(i, N) cin >> a[i];\n\
    \    m1une::data_structure::LazySegtree<AM> seg(a);\n    FOR(Q) {\n        ll\
    \ t;\n        cin >> t;\n        if (t == 0) {\n            ll l, r, b, c;\n \
    \           cin >> l >> r >> b >> c;\n            seg.apply(l, r, {b, c});\n \
    \       } else {\n            ll l, r;\n            cin >> l >> r;\n         \
    \   auto prd = seg.prod(l, r);\n            print(prd.sum.val());\n        }\n\
    \    }\n}\n\nint main() {\n    ios::sync_with_stdio(false);\n    cin.tie(nullptr);\n\
    \    cout << fixed << setprecision(20);\n    CPP_DUMP_SET_OPTION(max_line_width,\
    \ 80);\n    CPP_DUMP_SET_OPTION(log_label_func, cpp_dump::log_label::filename());\n\
    \    CPP_DUMP_SET_OPTION(enable_asterisk, true);\n    solve();\n    return 0;\n\
    }\n"
  dependsOn:
  - acted_monoid/range_affine_range_sum.hpp
  - data_structure/lazy_segtree.hpp
  - acted_monoid/concept.hpp
  - utilities/bit_ceil.hpp
  isVerificationFile: true
  path: verify/data_structure/lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2026-06-06 19:35:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/lazy_segtree.test.cpp
- /verify/verify/data_structure/lazy_segtree.test.cpp.html
title: verify/data_structure/lazy_segtree.test.cpp
---
