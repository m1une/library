---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/fenwick_tree.hpp
    title: Fenwick Tree (Binary Indexed Tree)
  - icon: ':heavy_check_mark:'
    path: ds/range_query/mo.hpp
    title: Mo's Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_inversions_query
    links:
    - https://judge.yosupo.jp/problem/static_range_inversions_query
  bundledCode: "#line 1 \"verify/ds/range_query/mo.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/static_range_inversions_query\"\n\n#line 1 \"\
    ds/range_query/mo.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cmath>\n#include <numeric>\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ ds {\n\n// Offline Mo's algorithm for half-open array ranges.\nstruct Mo {\n\
    \    struct Query {\n        int left;\n        int right;\n        int id;\n\
    \    };\n\n   private:\n    int _n;\n    std::vector<Query> _queries;\n\n   public:\n\
    \    Mo() : _n(0) {}\n\n    explicit Mo(int n) : _n(n) {\n        assert(0 <=\
    \ n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    int query_count()\
    \ const {\n        return int(_queries.size());\n    }\n\n    bool empty() const\
    \ {\n        return _queries.empty();\n    }\n\n    const std::vector<Query>&\
    \ queries() const {\n        return _queries;\n    }\n\n    void reserve(int query_capacity)\
    \ {\n        assert(0 <= query_capacity);\n        _queries.reserve(query_capacity);\n\
    \    }\n\n    void clear() {\n        _queries.clear();\n    }\n\n    // Adds\
    \ [left, right) and returns its insertion-order ID.\n    int add_query(int left,\
    \ int right) {\n        assert(0 <= left && left <= right && right <= _n);\n \
    \       int id = query_count();\n        _queries.push_back(Query{left, right,\
    \ id});\n        return id;\n    }\n\n    // Returns query IDs in Mo order. A\
    \ non-positive block size selects one\n    // automatically.\n    std::vector<int>\
    \ order(int block_size = 0) const {\n        int query_size = query_count();\n\
    \        std::vector<int> result(query_size);\n        std::iota(result.begin(),\
    \ result.end(), 0);\n        if (query_size == 0) return result;\n\n        if\
    \ (block_size <= 0) {\n            block_size = std::max(1, int(_n / std::sqrt(static_cast<double>(query_size))));\n\
    \        }\n\n        std::sort(result.begin(), result.end(), [&](int first, int\
    \ second) {\n            const Query& a = _queries[first];\n            const\
    \ Query& b = _queries[second];\n            int first_block = a.left / block_size;\n\
    \            int second_block = b.left / block_size;\n            if (first_block\
    \ != second_block) {\n                return first_block < second_block;\n   \
    \         }\n            if (first_block & 1) return a.right > b.right;\n    \
    \        return a.right < b.right;\n        });\n        return result;\n    }\n\
    \n    // Maintains [left, right). Each movement callback receives the array index\n\
    \    // being inserted or erased. `answer(query_id)` stores or reports a result.\n\
    \    template <class AddLeft, class AddRight, class RemoveLeft, class RemoveRight,\
    \ class Answer>\n    void run(AddLeft add_left, AddRight add_right, RemoveLeft\
    \ remove_left, RemoveRight remove_right, Answer answer,\n             int block_size\
    \ = 0) const {\n        int left = 0;\n        int right = 0;\n        for (int\
    \ query_index : order(block_size)) {\n            const Query& query = _queries[query_index];\n\
    \            while (query.left < left) add_left(--left);\n            while (right\
    \ < query.right) add_right(right++);\n            while (left < query.left) remove_left(left++);\n\
    \            while (query.right < right) remove_right(--right);\n            answer(query.id);\n\
    \        }\n    }\n\n    // Convenience overload for statistics whose update is\
    \ independent of\n    // which side moves.\n    template <class Add, class Remove,\
    \ class Answer>\n    void run(Add add, Remove remove, Answer answer, int block_size\
    \ = 0) const {\n        run(add, add, remove, remove, answer, block_size);\n \
    \   }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/mo.test.cpp\"\
    \n\n#line 7 \"verify/ds/range_query/mo.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#line 10 \"verify/ds/range_query/mo.test.cpp\"\n\n#line 1 \"ds/range_query/fenwick_tree.hpp\"\
    \n\n\n\n#line 6 \"ds/range_query/fenwick_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ ds {\n\ntemplate <typename T>\nstruct FenwickTree {\n   private:\n    int _n;\n\
    \    std::vector<T> _data;\n\n   public:\n    FenwickTree() : _n(0) {}\n\n   \
    \ explicit FenwickTree(int n) : _n(n), _data(n + 1, T{}) {}\n\n    explicit FenwickTree(const\
    \ std::vector<T>& a)\n        : _n(int(a.size())), _data(a.size() + 1, T{}) {\n\
    \        for (int i = 1; i <= _n; ++i) {\n            _data[i] += a[i - 1];\n\
    \            const int p = i + (i & -i);\n            if (p <= _n) {\n       \
    \         _data[p] += _data[i];\n            }\n        }\n    }\n\n    int size()\
    \ const {\n        return _n;\n    }\n\n    bool empty() const {\n        return\
    \ _n == 0;\n    }\n\n    // Adds `x` to the element at zero-based index `p`.\n\
    \    void add(int p, const T& x) {\n        assert(0 <= p && p < _n);\n      \
    \  ++p;\n        while (p <= _n) {\n            _data[p] += x;\n            p\
    \ += p & -p;\n        }\n    }\n\n    // Returns the sum of elements in the range\
    \ [0, r).\n    T sum(int r) const {\n        assert(0 <= r && r <= _n);\n    \
    \    T result{};\n        while (r > 0) {\n            result += _data[r];\n \
    \           r -= r & -r;\n        }\n        return result;\n    }\n\n    // Returns\
    \ the sum of elements in the range [l, r).\n    T sum(int l, int r) const {\n\
    \        assert(0 <= l && l <= r && r <= _n);\n        return sum(r) - sum(l);\n\
    \    }\n\n    // Returns the minimum index `r` such that the sum of [0, r) >=\
    \ w.\n    // Requires all elements in the tree to be non-negative.\n    int lower_bound(T\
    \ w) const {\n        if (w <= 0) return 0;\n        int x = 0;\n        int k\
    \ = 1;\n        while (k <= _n) k <<= 1;\n        for (k >>= 1; k > 0; k >>= 1)\
    \ {\n            if (x + k <= _n && _data[x + k] < w) {\n                w -=\
    \ _data[x + k];\n                x += k;\n            }\n        }\n        return\
    \ x + 1;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 12\
    \ \"verify/ds/range_query/mo.test.cpp\"\n\nnamespace {\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 503;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2500; ++trial) {\n        int n = int(random()\
    \ % 60);\n        int query_count = int(random() % 80);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 12);\n\n\
    \        m1une::ds::Mo mo(n);\n        mo.reserve(query_count);\n        std::vector<std::pair<int,\
    \ int>> ranges;\n        for (int query = 0; query < query_count; ++query) {\n\
    \            int left = int(random() % (n + 1));\n            int right = int(random()\
    \ % (n + 1));\n            if (right < left) std::swap(left, right);\n       \
    \     assert(mo.add_query(left, right) == query);\n            ranges.emplace_back(left,\
    \ right);\n        }\n\n        std::vector<int> frequency(12);\n        std::vector<int>\
    \ actual(query_count);\n        int distinct = 0;\n        mo.run(\n         \
    \   [&](int index) {\n                if (frequency[values[index]]++ == 0) distinct++;\n\
    \            },\n            [&](int index) {\n                if (--frequency[values[index]]\
    \ == 0) distinct--;\n            },\n            [&](int query_id) {\n       \
    \         actual[query_id] = distinct;\n            }\n        );\n\n        for\
    \ (int query = 0; query < query_count; ++query) {\n            std::vector<char>\
    \ seen(12);\n            [[maybe_unused]] int expected = 0;\n            for (\n\
    \                int index = ranges[query].first;\n                index < ranges[query].second;\n\
    \                ++index\n            ) {\n                if (!seen[values[index]])\
    \ {\n                    seen[values[index]] = true;\n                    expected++;\n\
    \                }\n            }\n            assert(actual[query] == expected);\n\
    \        }\n    }\n}\n\nstd::vector<long long> inversion_queries(\n    const std::vector<int>&\
    \ values,\n    const std::vector<std::pair<int, int>>& ranges\n) {\n    std::vector<int>\
    \ sorted = values;\n    std::sort(sorted.begin(), sorted.end());\n    sorted.erase(std::unique(sorted.begin(),\
    \ sorted.end()), sorted.end());\n\n    std::vector<int> compressed(values.size());\n\
    \    for (int index = 0; index < int(values.size()); ++index) {\n        compressed[index]\
    \ = int(\n            std::lower_bound(sorted.begin(), sorted.end(), values[index])\n\
    \            - sorted.begin()\n        );\n    }\n\n    m1une::ds::Mo mo(int(values.size()));\n\
    \    for (const auto& range : ranges) {\n        mo.add_query(range.first, range.second);\n\
    \    }\n\n    m1une::ds::FenwickTree<int> frequency(int(sorted.size()));\n   \
    \ std::vector<long long> result(ranges.size());\n    long long inversions = 0;\n\
    \    int current_size = 0;\n\n    mo.run(\n        [&](int index) {\n        \
    \    int value = compressed[index];\n            inversions += frequency.sum(value);\n\
    \            frequency.add(value, 1);\n            current_size++;\n        },\n\
    \        [&](int index) {\n            int value = compressed[index];\n      \
    \      inversions += current_size - frequency.sum(value + 1);\n            frequency.add(value,\
    \ 1);\n            current_size++;\n        },\n        [&](int index) {\n   \
    \         int value = compressed[index];\n            frequency.add(value, -1);\n\
    \            current_size--;\n            inversions -= frequency.sum(value);\n\
    \        },\n        [&](int index) {\n            int value = compressed[index];\n\
    \            frequency.add(value, -1);\n            current_size--;\n        \
    \    inversions -= current_size - frequency.sum(value + 1);\n        },\n    \
    \    [&](int query_id) {\n            result[query_id] = inversions;\n       \
    \ }\n    );\n    return result;\n}\n\nvoid test_directional_callbacks() {\n  \
    \  std::uint64_t state = 509;\n    auto random = [&state]() {\n        state ^=\
    \ state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n\
    \    for (int trial = 0; trial < 1500; ++trial) {\n        int n = 1 + int(random()\
    \ % 45);\n        int query_count = 1 + int(random() % 60);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 20);\n\
    \        std::vector<std::pair<int, int>> ranges;\n        for (int query = 0;\
    \ query < query_count; ++query) {\n            int left = int(random() % (n +\
    \ 1));\n            int right = int(random() % (n + 1));\n            if (right\
    \ < left) std::swap(left, right);\n            ranges.emplace_back(left, right);\n\
    \        }\n\n        auto actual = inversion_queries(values, ranges);\n     \
    \   for (int query = 0; query < query_count; ++query) {\n            [[maybe_unused]]\
    \ long long expected = 0;\n            for (int i = ranges[query].first; i < ranges[query].second;\
    \ ++i) {\n                for (int j = i + 1; j < ranges[query].second; ++j) {\n\
    \                    expected += values[i] > values[j];\n                }\n \
    \           }\n            assert(actual[query] == expected);\n        }\n   \
    \ }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n    test_directional_callbacks();\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<int> values(n);\n  \
    \  for (int& value : values) std::cin >> value;\n    std::vector<std::pair<int,\
    \ int>> ranges(q);\n    for (auto& range : ranges) {\n        std::cin >> range.first\
    \ >> range.second;\n    }\n    for (long long answer : inversion_queries(values,\
    \ ranges)) {\n        std::cout << answer << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"../../../ds/range_query/mo.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\n#include\
    \ \"../../../ds/range_query/fenwick_tree.hpp\"\n\nnamespace {\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 503;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2500; ++trial) {\n        int n = int(random()\
    \ % 60);\n        int query_count = int(random() % 80);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 12);\n\n\
    \        m1une::ds::Mo mo(n);\n        mo.reserve(query_count);\n        std::vector<std::pair<int,\
    \ int>> ranges;\n        for (int query = 0; query < query_count; ++query) {\n\
    \            int left = int(random() % (n + 1));\n            int right = int(random()\
    \ % (n + 1));\n            if (right < left) std::swap(left, right);\n       \
    \     assert(mo.add_query(left, right) == query);\n            ranges.emplace_back(left,\
    \ right);\n        }\n\n        std::vector<int> frequency(12);\n        std::vector<int>\
    \ actual(query_count);\n        int distinct = 0;\n        mo.run(\n         \
    \   [&](int index) {\n                if (frequency[values[index]]++ == 0) distinct++;\n\
    \            },\n            [&](int index) {\n                if (--frequency[values[index]]\
    \ == 0) distinct--;\n            },\n            [&](int query_id) {\n       \
    \         actual[query_id] = distinct;\n            }\n        );\n\n        for\
    \ (int query = 0; query < query_count; ++query) {\n            std::vector<char>\
    \ seen(12);\n            [[maybe_unused]] int expected = 0;\n            for (\n\
    \                int index = ranges[query].first;\n                index < ranges[query].second;\n\
    \                ++index\n            ) {\n                if (!seen[values[index]])\
    \ {\n                    seen[values[index]] = true;\n                    expected++;\n\
    \                }\n            }\n            assert(actual[query] == expected);\n\
    \        }\n    }\n}\n\nstd::vector<long long> inversion_queries(\n    const std::vector<int>&\
    \ values,\n    const std::vector<std::pair<int, int>>& ranges\n) {\n    std::vector<int>\
    \ sorted = values;\n    std::sort(sorted.begin(), sorted.end());\n    sorted.erase(std::unique(sorted.begin(),\
    \ sorted.end()), sorted.end());\n\n    std::vector<int> compressed(values.size());\n\
    \    for (int index = 0; index < int(values.size()); ++index) {\n        compressed[index]\
    \ = int(\n            std::lower_bound(sorted.begin(), sorted.end(), values[index])\n\
    \            - sorted.begin()\n        );\n    }\n\n    m1une::ds::Mo mo(int(values.size()));\n\
    \    for (const auto& range : ranges) {\n        mo.add_query(range.first, range.second);\n\
    \    }\n\n    m1une::ds::FenwickTree<int> frequency(int(sorted.size()));\n   \
    \ std::vector<long long> result(ranges.size());\n    long long inversions = 0;\n\
    \    int current_size = 0;\n\n    mo.run(\n        [&](int index) {\n        \
    \    int value = compressed[index];\n            inversions += frequency.sum(value);\n\
    \            frequency.add(value, 1);\n            current_size++;\n        },\n\
    \        [&](int index) {\n            int value = compressed[index];\n      \
    \      inversions += current_size - frequency.sum(value + 1);\n            frequency.add(value,\
    \ 1);\n            current_size++;\n        },\n        [&](int index) {\n   \
    \         int value = compressed[index];\n            frequency.add(value, -1);\n\
    \            current_size--;\n            inversions -= frequency.sum(value);\n\
    \        },\n        [&](int index) {\n            int value = compressed[index];\n\
    \            frequency.add(value, -1);\n            current_size--;\n        \
    \    inversions -= current_size - frequency.sum(value + 1);\n        },\n    \
    \    [&](int query_id) {\n            result[query_id] = inversions;\n       \
    \ }\n    );\n    return result;\n}\n\nvoid test_directional_callbacks() {\n  \
    \  std::uint64_t state = 509;\n    auto random = [&state]() {\n        state ^=\
    \ state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\n\
    \    for (int trial = 0; trial < 1500; ++trial) {\n        int n = 1 + int(random()\
    \ % 45);\n        int query_count = 1 + int(random() % 60);\n        std::vector<int>\
    \ values(n);\n        for (int& value : values) value = int(random() % 20);\n\
    \        std::vector<std::pair<int, int>> ranges;\n        for (int query = 0;\
    \ query < query_count; ++query) {\n            int left = int(random() % (n +\
    \ 1));\n            int right = int(random() % (n + 1));\n            if (right\
    \ < left) std::swap(left, right);\n            ranges.emplace_back(left, right);\n\
    \        }\n\n        auto actual = inversion_queries(values, ranges);\n     \
    \   for (int query = 0; query < query_count; ++query) {\n            [[maybe_unused]]\
    \ long long expected = 0;\n            for (int i = ranges[query].first; i < ranges[query].second;\
    \ ++i) {\n                for (int j = i + 1; j < ranges[query].second; ++j) {\n\
    \                    expected += values[i] > values[j];\n                }\n \
    \           }\n            assert(actual[query] == expected);\n        }\n   \
    \ }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n    test_directional_callbacks();\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<int> values(n);\n  \
    \  for (int& value : values) std::cin >> value;\n    std::vector<std::pair<int,\
    \ int>> ranges(q);\n    for (auto& range : ranges) {\n        std::cin >> range.first\
    \ >> range.second;\n    }\n    for (long long answer : inversion_queries(values,\
    \ ranges)) {\n        std::cout << answer << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/mo.hpp
  - ds/range_query/fenwick_tree.hpp
  isVerificationFile: true
  path: verify/ds/range_query/mo.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:21:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/mo.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/mo.test.cpp
- /verify/verify/ds/range_query/mo.test.cpp.html
title: verify/ds/range_query/mo.test.cpp
---
