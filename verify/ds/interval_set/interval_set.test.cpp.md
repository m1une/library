---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: ds/interval_set/interval_set.hpp
    title: ds/interval_set/interval_set.hpp
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
  bundledCode: "#line 1 \"verify/ds/interval_set/interval_set.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/interval_set/interval_set.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <initializer_list>\n\
    #include <iterator>\n#include <memory>\n#include <set>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace ds {\n\ntemplate <class T>\nstruct\
    \ IntervalSet {\n    using value_type = T;\n    using interval_type = std::pair<T,\
    \ T>;\n\nprivate:\n    std::set<interval_type> intervals;\n\n    typename std::set<interval_type>::iterator\
    \ first_intersecting_or_touching(T l) {\n        auto it = intervals.lower_bound(interval_type(l,\
    \ l));\n        if (it != intervals.begin()) {\n            auto prev = std::prev(it);\n\
    \            if (prev->second >= l) it = prev;\n        }\n        return it;\n\
    \    }\n\n    typename std::set<interval_type>::const_iterator first_intersecting_or_touching(T\
    \ l) const {\n        auto it = intervals.lower_bound(interval_type(l, l));\n\
    \        if (it != intervals.begin()) {\n            auto prev = std::prev(it);\n\
    \            if (prev->second >= l) it = prev;\n        }\n        return it;\n\
    \    }\n\n    typename std::set<interval_type>::const_iterator find_interval(T\
    \ x) const {\n        auto it = intervals.lower_bound(interval_type(x, x));\n\
    \        if (it != intervals.end() && it->first == x) return it;\n        if (it\
    \ == intervals.begin()) return intervals.end();\n        --it;\n        if (it->first\
    \ <= x && x < it->second) return it;\n        return intervals.end();\n    }\n\
    \npublic:\n    IntervalSet() = default;\n\n    IntervalSet(std::initializer_list<interval_type>\
    \ init) {\n        for (auto [l, r] : init) insert(l, r);\n    }\n\n    template\
    \ <class Iterator>\n    IntervalSet(Iterator first, Iterator last) {\n       \
    \ while (first != last) {\n            insert(first->first, first->second);\n\
    \            ++first;\n        }\n    }\n\n    int size() const { return int(intervals.size());\
    \ }\n\n    bool empty() const { return intervals.empty(); }\n\n    void clear()\
    \ { intervals.clear(); }\n\n    bool contains(T x) const { return find_interval(x)\
    \ != intervals.end(); }\n\n    bool contains(T l, T r) const {\n        assert(l\
    \ <= r);\n        if (l == r) return true;\n        auto it = find_interval(l);\n\
    \        return it != intervals.end() && r <= it->second;\n    }\n\n    interval_type\
    \ get(T x) const {\n        auto it = find_interval(x);\n        assert(it !=\
    \ intervals.end());\n        return *it;\n    }\n\n    const interval_type* get_if(T\
    \ x) const {\n        auto it = find_interval(x);\n        return it == intervals.end()\
    \ ? nullptr : std::addressof(*it);\n    }\n\n    bool intersects(T l, T r) const\
    \ {\n        assert(l <= r);\n        if (l == r) return false;\n\n        auto\
    \ it = intervals.lower_bound(interval_type(l, l));\n\n        if (it != intervals.begin())\
    \ {\n            auto prev = std::prev(it);\n            if (l < prev->second)\
    \ return true;\n        }\n\n        return it != intervals.end() && it->first\
    \ < r;\n    }\n\n    void insert(T l, T r) {\n        assert(l <= r);\n      \
    \  if (l == r) return;\n\n        auto it = first_intersecting_or_touching(l);\n\
    \n        while (it != intervals.end() && it->first <= r) {\n            l = std::min(l,\
    \ it->first);\n            r = std::max(r, it->second);\n            it = intervals.erase(it);\n\
    \        }\n\n        intervals.emplace(l, r);\n    }\n\n    void erase(T l, T\
    \ r) {\n        assert(l <= r);\n        if (l == r) return;\n\n        auto it\
    \ = first_intersecting_or_touching(l);\n\n        while (it != intervals.end()\
    \ && it->first < r) {\n            const T a = it->first;\n            const T\
    \ b = it->second;\n\n            if (b <= l) {\n                ++it;\n      \
    \          continue;\n            }\n\n            it = intervals.erase(it);\n\
    \n            if (a < l) intervals.emplace(a, l);\n            if (r < b) {\n\
    \                intervals.emplace(r, b);\n                break;\n          \
    \  }\n        }\n    }\n\n    T mex(T x) const {\n        auto it = find_interval(x);\n\
    \        return it == intervals.end() ? x : it->second;\n    }\n\n    T min_not_covered(T\
    \ x) const { return mex(x); }\n\n    std::vector<interval_type> to_vector() const\
    \ {\n        return std::vector<interval_type>(intervals.begin(), intervals.end());\n\
    \    }\n\n    auto begin() const { return intervals.begin(); }\n\n    auto end()\
    \ const { return intervals.end(); }\n};\n\n} // namespace ds\n} // namespace m1une\n\
    \n\n#line 4 \"verify/ds/interval_set/interval_set.test.cpp\"\n\n#line 6 \"verify/ds/interval_set/interval_set.test.cpp\"\
    \n#include <iostream>\n\nint main() {\n    long long A, B;\n    std::cin >> A\
    \ >> B;\n\n    m1une::ds::IntervalSet<int> st;\n    st.insert(1, 5);\n    st.insert(5,\
    \ 8);\n    assert(st.to_vector() == std::vector<std::pair<int, int>>({{1, 8}}));\n\
    \n    st.erase(3, 6);\n    assert(st.to_vector() == std::vector<std::pair<int,\
    \ int>>({{1, 3}, {6, 8}}));\n\n    assert(st.contains(2));\n    assert(!st.contains(3));\n\
    \    assert(st.contains(1, 3));\n    assert(!st.contains(1, 4));\n    assert(st.intersects(4,\
    \ 7));\n    assert(!st.intersects(3, 6));\n    assert(st.mex(1) == 3);\n    assert(st.mex(4)\
    \ == 4);\n    assert(st.mex(6) == 8);\n\n    std::cout << A + B << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/interval_set/interval_set.hpp\"\n\n#include <cassert>\n#include <iostream>\n\
    \nint main() {\n    long long A, B;\n    std::cin >> A >> B;\n\n    m1une::ds::IntervalSet<int>\
    \ st;\n    st.insert(1, 5);\n    st.insert(5, 8);\n    assert(st.to_vector() ==\
    \ std::vector<std::pair<int, int>>({{1, 8}}));\n\n    st.erase(3, 6);\n    assert(st.to_vector()\
    \ == std::vector<std::pair<int, int>>({{1, 3}, {6, 8}}));\n\n    assert(st.contains(2));\n\
    \    assert(!st.contains(3));\n    assert(st.contains(1, 3));\n    assert(!st.contains(1,\
    \ 4));\n    assert(st.intersects(4, 7));\n    assert(!st.intersects(3, 6));\n\
    \    assert(st.mex(1) == 3);\n    assert(st.mex(4) == 4);\n    assert(st.mex(6)\
    \ == 8);\n\n    std::cout << A + B << '\\n';\n}\n"
  dependsOn:
  - ds/interval_set/interval_set.hpp
  isVerificationFile: true
  path: verify/ds/interval_set/interval_set.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 13:10:40+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/ds/interval_set/interval_set.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/interval_set/interval_set.test.cpp
- /verify/verify/ds/interval_set/interval_set.test.cpp.html
title: verify/ds/interval_set/interval_set.test.cpp
---
