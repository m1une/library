---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ verify/unit_test/lazy_segtree.test.cpp: line 267: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#ifdef LOCAL\n#define _GLIBCXX_DEBUG\n#pragma GCC optimize(\"O0\")\n#else\n\
    #pragma GCC optimize(\"O3\")\n#pragma GCC optimize(\"unroll-loops\")\n#endif\n\
    \n#include <bits/stdc++.h>\n// #include <bits/extc++.h>\nusing namespace std;\n\
    \n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\nistream&\
    \ operator>>(istream& in, mint& x) {\n    long long a;\n    in >> a;\n    x =\
    \ a;\n    return in;\n}\nostream& operator<<(ostream& out, const mint& x) {\n\
    \    return out << x.val();\n}\n\nusing ll = long long;\nusing u32 = unsigned\
    \ int;\nusing u64 = unsigned long long;\nusing i128 = __int128;\nusing u128 =\
    \ unsigned __int128;\n// using f128 = __float128;\n\ntemplate <class T>\nconstexpr\
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
    \ std::priori`ty_queue<T, vector<T>, greater<T>>;\ntemplate <class T, class U>\n\
    using umap = unordered_map<T, U>;\n\n// template <typename K>\n// using tree =\
    \ __gnu_pbds::tree<K, __gnu_pbds::null_type, std::less<>,\n//                \
    \               __gnu_pbds::rb_tree_tag,\n//                               __gnu_pbds::tree_order_statistics_node_update>;\n\
    \n#define vv(type, name, h, ...) \\\n    vector<vector<type>> name(h, vector<type>(__VA_ARGS__))\n\
    #define vvv(type, name, h, w, ...)     \\\n    vector<vector<vector<type>>> name(\
    \ \\\n        h, vector<vector<type>>(w, vector<type>(__VA_ARGS__)))\n#define\
    \ vvvv(type, name, a, b, c, ...)         \\\n    vector<vector<vector<vector<type>>>>\
    \ name( \\\n        a, vector<vector<vector<type>>>(       \\\n              \
    \ b, vector<vector<type>>(c, vector<type>(__VA_ARGS__))))\n\n// FOR(a) :=  for\
    \ (ll _ = 0; _ < (ll)a; ++_)\n// FOR(i, a) := for (ll i = 0; i < (ll)a; ++i)\n\
    // FOR(i, a, b) := for (ll i = a; i < (ll)b; ++i)\n// FOR(i, a, b, c) := for (ll\
    \ i = a; i < (ll)b; i += (c))\n// FOR_R(a) := for (ll i = (a) - 1; i >= 0; --i)\n\
    // FOR_R(i, a) := for (ll i = (a) - 1; i >= 0; --i)\n// FOR_R(i, a, b) := for\
    \ (ll i = (b) - 1; i >= (ll)a; --i)\n#define FOR1(a) for (ll _ = 0; _ < (ll)a;\
    \ ++_)\n#define FOR2(i, a) for (ll i = 0; i < (ll)a; ++i)\n#define FOR3(i, a,\
    \ b) for (ll i = a; i < (ll)b; ++i)\n#define FOR4(i, a, b, c) for (ll i = a; i\
    \ < (ll)b; i += (c))\n#define FOR1_R(a) for (ll i = (a) - 1; i >= 0; --i)\n#define\
    \ FOR2_R(i, a) for (ll i = (a) - 1; i >= 0; --i)\n#define FOR3_R(i, a, b) for\
    \ (ll i = (b) - 1; i >= (ll)a; --i)\n#define overload4(a, b, c, d, e, ...) e\n\
    #define overload3(a, b, c, d, ...) d\n#define FOR(...) overload4(__VA_ARGS__,\
    \ FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)\n#define FOR_R(...) overload3(__VA_ARGS__,\
    \ FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)\n\n#define FOR_subset(t, s) \\\n    for\
    \ (int t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))\n#define all(x) x.begin(),\
    \ x.end()\n#define rall(x) x.rbegin(), x.rend()\n\nint popcnt(int x) { return\
    \ __builtin_popcount(x); }\nint popcnt(u32 x) { return __builtin_popcount(x);\
    \ }\nint popcnt(ll x) { return __builtin_popcountll(x); }\nint popcnt(u64 x) {\
    \ return __builtin_popcountll(x); }\n// int popcnt_mod_2(int x) { return __builtin_parity(x);\
    \ }\n// int popcnt_mod_2(u32 x) { return __builtin_parity(x); }\n// int popcnt_mod_2(ll\
    \ x) { return __builtin_parityll(x); }\n// int popcnt_mod_2(u64 x) { return __builtin_parityll(x);\
    \ }\n// (0, 1, 2, 3, 4) -> (-1, 0, 1, 1, 2)\nint topbit(int x) { return (x ==\
    \ 0 ? -1 : 31 - __builtin_clz(x)); }\nint topbit(u32 x) { return (x == 0 ? -1\
    \ : 31 - __builtin_clz(x)); }\nint topbit(ll x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x));\
    \ }\nint topbit(u64 x) { return (x == 0 ? -1 : 63 - __builtin_clzll(x)); }\n//\
    \ (0, 1, 2, 3, 4) -> (-1, 0, 1, 0, 2)\nint lowbit(int x) { return (x == 0 ? -1\
    \ : __builtin_ctz(x)); }\nint lowbit(u32 x) { return (x == 0 ? -1 : __builtin_ctz(x));\
    \ }\nint lowbit(ll x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }\nint lowbit(u64\
    \ x) { return (x == 0 ? -1 : __builtin_ctzll(x)); }\n\ntemplate <typename T>\n\
    T floor(T a, T b) {\n    return a / b - (a % b && (a ^ b) < 0);\n}\ntemplate <typename\
    \ T>\nT ceil(T x, T y) {\n    return floor(x + y - 1, y);\n}\ntemplate <typename\
    \ T>\nT bmod(T x, T y) {\n    return x - y * floor(x, y);\n}\ntemplate <typename\
    \ T>\npair<T, T> divmod(T x, T y) {\n    T q = floor(x, y);\n    return {q, x\
    \ - q * y};\n}\n\ntemplate <typename T, typename U>\nT POW(U x_, int n) {\n  \
    \  T x = x_;\n    T ret = 1;\n    while (n > 0) {\n        if (n & 1) ret *= x;\n\
    \        x *= x;\n        n >>= 1;\n    }\n    return ret;\n}\n\ntemplate <typename\
    \ T, typename U>\nT SUM(const vector<U> &A) {\n    T sm = 0;\n    for (auto &&a\
    \ : A) sm += a;\n    return sm;\n}\n\n#define LB(c, x) distance((c).begin(), lower_bound(all(c),\
    \ (x)))\n#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))\n#define\
    \ UNIQUE(x) \\\n    sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()\n\
    \ntemplate <class T, class S>\ninline bool chmax(T &a, const S &b) {\n    return\
    \ (a < b ? a = b, 1 : 0);\n}\ntemplate <class T, class S>\ninline bool chmin(T\
    \ &a, const S &b) {\n    return (a > b ? a = b, 1 : 0);\n}\n\n// ? \u306F -1\n\
    vc<int> s_to_vi(const string &S, char first_char) {\n    vc<int> A(S.size());\n\
    \    FOR(i, S.size()) { A[i] = (S[i] != '?' ? S[i] - first_char : -1); }\n   \
    \ return A;\n}\n\ntemplate <typename T, typename U>\nvector<T> cumsum(vector<U>\
    \ &A, int off = 1) {\n    int N = A.size();\n    vector<T> B(N + 1);\n    FOR(i,\
    \ N) { B[i + 1] = B[i] + A[i]; }\n    if (off == 0) B.erase(B.begin());\n    return\
    \ B;\n}\n\ntemplate <typename T>\nvector<int> argsort(const vector<T> &A) {\n\
    \    vector<int> ids(A.size());\n    iota(all(ids), 0);\n    sort(all(ids),\n\
    \         [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });\n\
    \    return ids;\n}\n\n// A[I[0]], A[I[1]], ...\ntemplate <typename T>\nvc<T>\
    \ rearrange(const vc<T> &A, const vc<int> &I) {\n    vc<T> B(I.size());\n    FOR(i,\
    \ I.size()) B[i] = A[I[i]];\n    return B;\n}\n\ntemplate<class... T>\nconstexpr\
    \ auto min(T... a){\n    return min(initializer_list<common_type_t<T...>>{a...});\n\
    }\ntemplate<class... T>\nconstexpr auto max(T... a){\n    return max(initializer_list<common_type_t<T...>>{a...});\n\
    }\n\nvoid print(){\n    cout << '\\n';\n}\ntemplate<class T>\nvoid print(const\
    \ T& a){\n    cout << a << '\\n';\n}\ntemplate<class T, class... Ts>\nvoid print(const\
    \ T& a, const Ts&... b){\n    cout << a;\n    (cout << ... << (cout << ' ', b));\n\
    \    cout << '\\n';\n}\ntemplate<class T>\nvoid print(vector<T> &a){\n    for\
    \ (int i = 0; i < (int)a.size(); ++i) {\n        cout << a[i] << \" \\n\"[i ==\
    \ (int)a.size() - 1];\n    }\n}\ntemplate<class T>\nvoid print(vector<T> &&a){\n\
    \    for (int i = 0; i < (int)a.size(); ++i) {\n        cout << a[i] << \" \\\
    n\"[i == (int)a.size() - 1];\n    }\n}\ntemplate<class T>\nvoid print(vector<vector<T>>\
    \ &a){\n    for (int i = 0; i < (int)a.size(); ++i) {\n        for (int j = 0;\
    \ j < (int)a[i].size(); ++j) {\n            cout << a[i][j] << \" \\n\"[j == (int)a[i].size()\
    \ - 1];\n        }\n    }\n}\ntemplate<class T>\nvoid print(vector<vector<T>>\
    \ &&a){\n    for (int i = 0; i < (int)a.size(); ++i) {\n        for (int j = 0;\
    \ j < (int)a[i].size(); ++j) {\n            cout << a[i][j] << \" \\n\"[j == (int)a[i].size()\
    \ - 1];\n        }\n    }\n}\nvoid YESNO(bool b) { cout << (b ? \"YES\" : \"NO\"\
    ) << endl; }\nvoid YesNo(bool b) { cout << (b ? \"Yes\" : \"No\") << endl; }\n\
    \n#ifdef LOCAL\n// https://zenn.dev/sassan/articles/19db660e4da0a4\n#include \"\
    /Library/cpp-dump/dump.hpp\"\n#define dump(...) cpp_dump(__VA_ARGS__)\nCPP_DUMP_DEFINE_EXPORT_OBJECT(mint,\
    \ val());\n#else\n#define dump(...)\n#define CPP_DUMP_SET_OPTION(...)\n#define\
    \ CPP_DUMP_DEFINE_EXPORT_OBJECT(...)\n#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)\n\
    #define CPP_DUMP_DEFINE_DANGEROUS_EXPORT_OBJECT(...)\n#endif\n\n\n//----------------------------------------------------------------\n\
    \nvoid solve() {\n    ll N;\n    cin >> N;\n}\n\nint main() {\n    ios::sync_with_stdio(false);\n\
    \    cin.tie(nullptr);\n    cout << fixed << setprecision(20);\n    CPP_DUMP_SET_OPTION(max_line_width,\
    \ 80);\n    CPP_DUMP_SET_OPTION(log_label_func, cpp_dump::log_label::filename());\n\
    \    CPP_DUMP_SET_OPTION(enable_asterisk, true);\n    solve();\n    return 0;\n\
    }"
  dependsOn: []
  isVerificationFile: true
  path: verify/unit_test/lazy_segtree.test.cpp
  requiredBy: []
  timestamp: '2025-09-29 23:15:18+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/unit_test/lazy_segtree.test.cpp
layout: document
redirect_from:
- /verify/verify/unit_test/lazy_segtree.test.cpp
- /verify/verify/unit_test/lazy_segtree.test.cpp.html
title: verify/unit_test/lazy_segtree.test.cpp
---
