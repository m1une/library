---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: utilities/bisect.hpp
    title: Bisect
  - icon: ':x:'
    path: utilities/chmin_chmax.hpp
    title: Chmin Chmax
  - icon: ':x:'
    path: utilities/compressor.hpp
    title: Compressor
  - icon: ':x:'
    path: utilities/run_length_encoding.hpp
    title: Run Length Encoding
  - icon: ':x:'
    path: utilities/y_combinator.hpp
    title: Y Combinator
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/utilities/extra_utilities.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\nusing\
    \ namespace std;\n\n#line 1 \"utilities/bisect.hpp\"\n\n\n\n#line 5 \"utilities/bisect.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <typename F>\nlong long\
    \ first_true(long long ng, long long ok, F pred) {\n    auto distance = [](long\
    \ long a, long long b) {\n        return a > b ? static_cast<__int128_t>(a) -\
    \ b : static_cast<__int128_t>(b) - a;\n    };\n    while (distance(ng, ok) > 1)\
    \ {\n        long long mid = std::midpoint(ng, ok);\n        if (pred(mid)) {\n\
    \            ok = mid;\n        } else {\n            ng = mid;\n        }\n \
    \   }\n    return ok;\n}\n\ntemplate <typename F>\nlong long last_true(long long\
    \ ok, long long ng, F pred) {\n    auto distance = [](long long a, long long b)\
    \ {\n        return a > b ? static_cast<__int128_t>(a) - b : static_cast<__int128_t>(b)\
    \ - a;\n    };\n    while (distance(ok, ng) > 1) {\n        long long mid = std::midpoint(ok,\
    \ ng);\n        if (pred(mid)) {\n            ok = mid;\n        } else {\n  \
    \          ng = mid;\n        }\n    }\n    return ok;\n}\n\ntemplate <typename\
    \ F>\ndouble real_first_true(double ng, double ok, F pred, int iterations = 80)\
    \ {\n    for (int i = 0; i < iterations; ++i) {\n        double mid = (ng + ok)\
    \ / 2.0;\n        if (pred(mid)) {\n            ok = mid;\n        } else {\n\
    \            ng = mid;\n        }\n    }\n    return ok;\n}\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/chmin_chmax.hpp\"\n\
    \n\n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <typename T, typename\
    \ U>\nbool chmin(T& a, const U& b) {\n    if (b < a) {\n        a = b;\n     \
    \   return true;\n    }\n    return false;\n}\n\ntemplate <typename T, typename\
    \ U>\nbool chmax(T& a, const U& b) {\n    if (a < b) {\n        a = b;\n     \
    \   return true;\n    }\n    return false;\n}\n\n}  // namespace utilities\n}\
    \  // namespace m1une\n\n\n#line 1 \"utilities/compressor.hpp\"\n\n\n\n#line 5\
    \ \"utilities/compressor.hpp\"\n#include <initializer_list>\n#line 9 \"utilities/compressor.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\ntemplate <typename T>\nstruct\
    \ Compressor {\n   private:\n    std::vector<T> _values;\n\n   public:\n    Compressor()\
    \ = default;\n\n    explicit Compressor(std::vector<T> values) : _values(std::move(values))\
    \ {\n        build();\n    }\n\n    Compressor(std::initializer_list<T> values)\
    \ : _values(values) {\n        build();\n    }\n\n    template <typename Iterator>\n\
    \    Compressor(Iterator first, Iterator last) : _values(first, last) {\n    \
    \    build();\n    }\n\n    void add(const T& value) {\n        _values.push_back(value);\n\
    \    }\n\n    void build() {\n        std::sort(_values.begin(), _values.end());\n\
    \        _values.erase(std::unique(_values.begin(), _values.end()), _values.end());\n\
    \    }\n\n    int get(const T& value) const {\n        auto it = std::lower_bound(_values.begin(),\
    \ _values.end(), value);\n        if (it == _values.end() || *it != value) {\n\
    \            throw std::out_of_range(\"value is not contained in Compressor\"\
    );\n        }\n        return static_cast<int>(it - _values.begin());\n    }\n\
    \n    int lower_bound(const T& value) const {\n        return static_cast<int>(std::lower_bound(_values.begin(),\
    \ _values.end(), value) - _values.begin());\n    }\n\n    int upper_bound(const\
    \ T& value) const {\n        return static_cast<int>(std::upper_bound(_values.begin(),\
    \ _values.end(), value) - _values.begin());\n    }\n\n    bool contains(const\
    \ T& value) const {\n        auto it = std::lower_bound(_values.begin(), _values.end(),\
    \ value);\n        return it != _values.end() && *it == value;\n    }\n\n    const\
    \ T& operator[](int index) const {\n        return _values.at(index);\n    }\n\
    \n    const std::vector<T>& values() const {\n        return _values;\n    }\n\
    \n    int size() const {\n        return static_cast<int>(_values.size());\n \
    \   }\n\n    bool empty() const {\n        return _values.empty();\n    }\n};\n\
    \n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/run_length_encoding.hpp\"\
    \n\n\n\n#line 7 \"utilities/run_length_encoding.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\ntemplate <typename Container>\nauto run_length_encoding(const\
    \ Container& values) {\n    using T = typename Container::value_type;\n    std::vector<std::pair<T,\
    \ long long>> result;\n\n    auto it = std::begin(values);\n    auto last = std::end(values);\n\
    \    if (it == last) {\n        return result;\n    }\n\n    T current = *it;\n\
    \    long long count = 0;\n    for (; it != last; ++it) {\n        if (*it ==\
    \ current) {\n            ++count;\n        } else {\n            result.emplace_back(current,\
    \ count);\n            current = *it;\n            count = 1;\n        }\n   \
    \ }\n    result.emplace_back(current, count);\n    return result;\n}\n\n}  //\
    \ namespace utilities\n}  // namespace m1une\n\n\n#line 1 \"utilities/y_combinator.hpp\"\
    \n\n\n\n#include <type_traits>\n#line 6 \"utilities/y_combinator.hpp\"\n\nnamespace\
    \ m1une {\nnamespace utilities {\n\ntemplate <typename F>\nstruct YCombinator\
    \ {\n   private:\n    F _f;\n\n   public:\n    explicit YCombinator(F&& f) : _f(std::forward<F>(f))\
    \ {}\n\n    template <typename... Args>\n    decltype(auto) operator()(Args&&...\
    \ args) {\n        return _f(*this, std::forward<Args>(args)...);\n    }\n\n \
    \   template <typename... Args>\n    decltype(auto) operator()(Args&&... args)\
    \ const {\n        return _f(*this, std::forward<Args>(args)...);\n    }\n};\n\
    \ntemplate <typename F>\nauto y_combinator(F&& f) {\n    return YCombinator<std::decay_t<F>>(std::forward<F>(f));\n\
    }\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n#line 11 \"verify/utilities/extra_utilities.test.cpp\"\
    \n\nvoid test_chmin_chmax() {\n    int x = 10;\n    assert(m1une::utilities::chmin(x,\
    \ 3));\n    assert(x == 3);\n    assert(!m1une::utilities::chmin(x, 7));\n   \
    \ assert(m1une::utilities::chmax(x, 7));\n    assert(x == 7);\n    assert(!m1une::utilities::chmax(x,\
    \ 4));\n}\n\nvoid test_compressor() {\n    vector<long long> xs = {100, -5, 100,\
    \ 7};\n    m1une::utilities::Compressor<long long> comp(xs);\n\n    assert(comp.size()\
    \ == 3);\n    assert(comp[0] == -5);\n    assert(comp[1] == 7);\n    assert(comp[2]\
    \ == 100);\n    assert(comp.get(100) == 2);\n    assert(comp.lower_bound(8) ==\
    \ 2);\n    assert(comp.upper_bound(7) == 2);\n    assert(comp.contains(-5));\n\
    \    assert(!comp.contains(6));\n\n    m1une::utilities::Compressor<int> incremental;\n\
    \    incremental.add(4);\n    incremental.add(1);\n    incremental.add(4);\n \
    \   incremental.build();\n    assert(incremental.size() == 2);\n    assert(incremental.get(1)\
    \ == 0);\n    assert(incremental.get(4) == 1);\n\n    bool rejected = false;\n\
    \    try {\n        (void)comp.get(6);\n    } catch (const out_of_range&) {\n\
    \        rejected = true;\n    }\n    assert(rejected);\n}\n\nvoid test_y_combinator()\
    \ {\n    auto fact = m1une::utilities::y_combinator([](auto self, int n) -> long\
    \ long {\n        if (n == 0) return 1;\n        return n * self(n - 1);\n   \
    \ });\n    assert(fact(10) == 3628800);\n}\n\nvoid test_bisect() {\n    long long\
    \ n = 100;\n    long long first = m1une::utilities::first_true(0, n + 1, [&](long\
    \ long x) {\n        return x * x >= n;\n    });\n    assert(first == 10);\n\n\
    \    long long last = m1une::utilities::last_true(n + 1, 0, [&](long long x) {\n\
    \        return x * x >= n;\n    });\n    assert(last == 10);\n\n    double root\
    \ = m1une::utilities::real_first_true(0.0, 2.0, [](double x) {\n        return\
    \ x * x >= 2.0;\n    });\n    assert(abs(root * root - 2.0) < 1e-12);\n}\n\nvoid\
    \ test_run_length_encoding() {\n    string s = \"aaabbc\";\n    auto runs = m1une::utilities::run_length_encoding(s);\n\
    \    assert(runs.size() == 3);\n    assert(runs[0] == make_pair('a', 3LL));\n\
    \    assert(runs[1] == make_pair('b', 2LL));\n    assert(runs[2] == make_pair('c',\
    \ 1LL));\n\n    vector<int> v = {1, 1, 2, 2, 2, 1};\n    auto vector_runs = m1une::utilities::run_length_encoding(v);\n\
    \    assert(vector_runs[0] == make_pair(1, 2LL));\n    assert(vector_runs[1] ==\
    \ make_pair(2, 3LL));\n    assert(vector_runs[2] == make_pair(1, 1LL));\n}\n\n\
    int main() {\n    test_chmin_chmax();\n    test_compressor();\n    test_y_combinator();\n\
    \    test_bisect();\n    test_run_length_encoding();\n\n    long long a, b;\n\
    \    cin >> a >> b;\n    cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\n\n#include \"../../utilities/bisect.hpp\"\n#include \"../../utilities/chmin_chmax.hpp\"\
    \n#include \"../../utilities/compressor.hpp\"\n#include \"../../utilities/run_length_encoding.hpp\"\
    \n#include \"../../utilities/y_combinator.hpp\"\n\nvoid test_chmin_chmax() {\n\
    \    int x = 10;\n    assert(m1une::utilities::chmin(x, 3));\n    assert(x ==\
    \ 3);\n    assert(!m1une::utilities::chmin(x, 7));\n    assert(m1une::utilities::chmax(x,\
    \ 7));\n    assert(x == 7);\n    assert(!m1une::utilities::chmax(x, 4));\n}\n\n\
    void test_compressor() {\n    vector<long long> xs = {100, -5, 100, 7};\n    m1une::utilities::Compressor<long\
    \ long> comp(xs);\n\n    assert(comp.size() == 3);\n    assert(comp[0] == -5);\n\
    \    assert(comp[1] == 7);\n    assert(comp[2] == 100);\n    assert(comp.get(100)\
    \ == 2);\n    assert(comp.lower_bound(8) == 2);\n    assert(comp.upper_bound(7)\
    \ == 2);\n    assert(comp.contains(-5));\n    assert(!comp.contains(6));\n\n \
    \   m1une::utilities::Compressor<int> incremental;\n    incremental.add(4);\n\
    \    incremental.add(1);\n    incremental.add(4);\n    incremental.build();\n\
    \    assert(incremental.size() == 2);\n    assert(incremental.get(1) == 0);\n\
    \    assert(incremental.get(4) == 1);\n\n    bool rejected = false;\n    try {\n\
    \        (void)comp.get(6);\n    } catch (const out_of_range&) {\n        rejected\
    \ = true;\n    }\n    assert(rejected);\n}\n\nvoid test_y_combinator() {\n   \
    \ auto fact = m1une::utilities::y_combinator([](auto self, int n) -> long long\
    \ {\n        if (n == 0) return 1;\n        return n * self(n - 1);\n    });\n\
    \    assert(fact(10) == 3628800);\n}\n\nvoid test_bisect() {\n    long long n\
    \ = 100;\n    long long first = m1une::utilities::first_true(0, n + 1, [&](long\
    \ long x) {\n        return x * x >= n;\n    });\n    assert(first == 10);\n\n\
    \    long long last = m1une::utilities::last_true(n + 1, 0, [&](long long x) {\n\
    \        return x * x >= n;\n    });\n    assert(last == 10);\n\n    double root\
    \ = m1une::utilities::real_first_true(0.0, 2.0, [](double x) {\n        return\
    \ x * x >= 2.0;\n    });\n    assert(abs(root * root - 2.0) < 1e-12);\n}\n\nvoid\
    \ test_run_length_encoding() {\n    string s = \"aaabbc\";\n    auto runs = m1une::utilities::run_length_encoding(s);\n\
    \    assert(runs.size() == 3);\n    assert(runs[0] == make_pair('a', 3LL));\n\
    \    assert(runs[1] == make_pair('b', 2LL));\n    assert(runs[2] == make_pair('c',\
    \ 1LL));\n\n    vector<int> v = {1, 1, 2, 2, 2, 1};\n    auto vector_runs = m1une::utilities::run_length_encoding(v);\n\
    \    assert(vector_runs[0] == make_pair(1, 2LL));\n    assert(vector_runs[1] ==\
    \ make_pair(2, 3LL));\n    assert(vector_runs[2] == make_pair(1, 1LL));\n}\n\n\
    int main() {\n    test_chmin_chmax();\n    test_compressor();\n    test_y_combinator();\n\
    \    test_bisect();\n    test_run_length_encoding();\n\n    long long a, b;\n\
    \    cin >> a >> b;\n    cout << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/bisect.hpp
  - utilities/chmin_chmax.hpp
  - utilities/compressor.hpp
  - utilities/run_length_encoding.hpp
  - utilities/y_combinator.hpp
  isVerificationFile: true
  path: verify/utilities/extra_utilities.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/utilities/extra_utilities.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/extra_utilities.test.cpp
- /verify/verify/utilities/extra_utilities.test.cpp.html
title: verify/utilities/extra_utilities.test.cpp
---
