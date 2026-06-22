---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/range_inversion_count.hpp
    title: Static Range Inversion Count
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
  bundledCode: "#line 1 \"verify/ds/range_query/range_inversion_count.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#line 1 \"ds/range_query/range_inversion_count.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cmath>\n#include <vector>\n\nnamespace m1une {\n\
    namespace ds {\n\n// Static range inversion counts with O(N sqrt N) preprocessing\
    \ and\n// O(sqrt N) queries.\ntemplate <class T>\nstruct RangeInversionCount {\n\
    \   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n    std::vector<int>\
    \ _rank;\n    std::vector<std::vector<int>> _boundary_less;\n    std::vector<std::vector<long\
    \ long>> _from_boundary;\n    std::vector<std::vector<long long>> _local_inversion;\n\
    \    std::vector<std::vector<int>> _sorted_suffix;\n    std::vector<std::vector<int>>\
    \ _sorted_prefix;\n    std::vector<int> _greater_before_in_block;\n\n    int block_start(int\
    \ block) const {\n        return block * _block_size;\n    }\n\n    int block_end(int\
    \ block) const {\n        return std::min(_n, block_start(block) + _block_size);\n\
    \    }\n\n    static long long cross_inversions(\n        const std::vector<int>&\
    \ left,\n        const std::vector<int>& right\n    ) {\n        long long result\
    \ = 0;\n        std::size_t smaller = 0;\n        for (int value : left) {\n \
    \           while (smaller < right.size() && right[smaller] < value) {\n     \
    \           smaller++;\n            }\n            result += static_cast<long\
    \ long>(smaller);\n        }\n        return result;\n    }\n\n    void build_local_data()\
    \ {\n        _local_inversion.resize(_n);\n        _sorted_suffix.resize(_n);\n\
    \        _sorted_prefix.resize(_n + 1);\n        _greater_before_in_block.assign(_n,\
    \ 0);\n\n        for (int block = 0; block < _block_count; ++block) {\n      \
    \      int start = block_start(block);\n            int end = block_end(block);\n\
    \            int length = end - start;\n            std::vector<std::vector<int>>\
    \ greater(\n                length,\n                std::vector<int>(length,\
    \ 0)\n            );\n\n            for (int right = 0; right < length; ++right)\
    \ {\n                int count = 0;\n                for (int left = right - 1;\
    \ 0 <= left; --left) {\n                    count += _rank[start + left] > _rank[start\
    \ + right];\n                    greater[left][right] = count;\n             \
    \   }\n                _greater_before_in_block[start + right] =\n           \
    \         right == 0 ? 0 : greater[0][right];\n            }\n\n            for\
    \ (int left = 0; left < length; ++left) {\n                _local_inversion[start\
    \ + left].assign(\n                    length - left + 1,\n                  \
    \  0\n                );\n                long long inversions = 0;\n        \
    \        for (int right = left; right < length; ++right) {\n                 \
    \   inversions += greater[left][right];\n                    _local_inversion[start\
    \ + left][right - left + 1] =\n                        inversions;\n         \
    \       }\n            }\n\n            std::vector<int> sorted;\n           \
    \ if (start == 0) _sorted_prefix[start] = sorted;\n            for (int index\
    \ = start; index < end; ++index) {\n                sorted.insert(\n         \
    \           std::upper_bound(\n                        sorted.begin(),\n     \
    \                   sorted.end(),\n                        _rank[index]\n    \
    \                ),\n                    _rank[index]\n                );\n  \
    \              _sorted_prefix[index + 1] = sorted;\n            }\n\n        \
    \    sorted.clear();\n            for (int index = end - 1; start <= index; --index)\
    \ {\n                sorted.insert(\n                    std::upper_bound(\n \
    \                       sorted.begin(),\n                        sorted.end(),\n\
    \                        _rank[index]\n                    ),\n              \
    \      _rank[index]\n                );\n                _sorted_suffix[index]\
    \ = sorted;\n            }\n        }\n    }\n\n    void build_boundary_counts(int\
    \ value_count) {\n        _boundary_less.assign(\n            _block_count + 1,\n\
    \            std::vector<int>(value_count + 1, 0)\n        );\n        std::vector<int>\
    \ frequency(value_count, 0);\n        for (int block = 0; block <= _block_count;\
    \ ++block) {\n            int boundary = std::min(_n, block_start(block));\n \
    \           if (block != 0) {\n                int previous = block_start(block\
    \ - 1);\n                for (int index = previous; index < boundary; ++index)\
    \ {\n                    frequency[_rank[index]]++;\n                }\n     \
    \       }\n            int count = 0;\n            for (int rank = 0; rank < value_count;\
    \ ++rank) {\n                _boundary_less[block][rank] = count;\n          \
    \      count += frequency[rank];\n            }\n            _boundary_less[block][value_count]\
    \ = count;\n        }\n    }\n\n    void build_boundary_inversions() {\n     \
    \   _from_boundary.assign(\n            _block_count + 1,\n            std::vector<long\
    \ long>(_n + 1, 0)\n        );\n        for (int first_block = 0; first_block\
    \ < _block_count; ++first_block) {\n            int start = block_start(first_block);\n\
    \            long long inversions = 0;\n            for (int index = start; index\
    \ < _n; ++index) {\n                int current_block = index / _block_size;\n\
    \                int full_length =\n                    block_start(current_block)\
    \ - start;\n                int less_equal =\n                    _boundary_less[current_block][_rank[index]\
    \ + 1]\n                    - _boundary_less[first_block][_rank[index] + 1];\n\
    \                int greater_in_full_blocks = full_length - less_equal;\n    \
    \            inversions +=\n                    greater_in_full_blocks\n     \
    \               + _greater_before_in_block[index];\n                _from_boundary[first_block][index\
    \ + 1] = inversions;\n            }\n        }\n    }\n\n   public:\n    RangeInversionCount()\n\
    \        : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit RangeInversionCount(const\
    \ std::vector<T>& values)\n        : _n(int(values.size())), _block_size(1), _block_count(0)\
    \ {\n        if (_n == 0) return;\n\n        _block_size = std::max(\n       \
    \     1,\n            int(std::sqrt(static_cast<long double>(_n)))\n        );\n\
    \        while (1LL * _block_size * _block_size < _n) ++_block_size;\n       \
    \ _block_count = (_n + _block_size - 1) / _block_size;\n\n        std::vector<T>\
    \ sorted = values;\n        std::sort(sorted.begin(), sorted.end());\n       \
    \ sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());\n   \
    \     _rank.resize(_n);\n        for (int index = 0; index < _n; ++index) {\n\
    \            _rank[index] = int(\n                std::lower_bound(\n        \
    \            sorted.begin(),\n                    sorted.end(),\n            \
    \        values[index]\n                ) - sorted.begin()\n            );\n \
    \       }\n\n        build_local_data();\n        build_boundary_counts(int(sorted.size()));\n\
    \        build_boundary_inversions();\n    }\n\n    int size() const {\n     \
    \   return _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n \
    \   }\n\n    int block_size() const {\n        return _block_size;\n    }\n\n\
    \    // Returns the number of pairs (i, j) with\n    // left <= i < j < right\
    \ and values[i] > values[j].\n    long long query(int left, int right) const {\n\
    \        assert(0 <= left && left <= right && right <= _n);\n        if (right\
    \ - left <= 1) return 0;\n\n        int left_block = left / _block_size;\n   \
    \     int right_block = (right - 1) / _block_size;\n        if (left_block ==\
    \ right_block) {\n            return _local_inversion[left][right - left];\n \
    \       }\n\n        int middle_left = block_end(left_block);\n        int middle_block\
    \ = left_block + 1;\n        long long result = _local_inversion[left][middle_left\
    \ - left];\n        result += _from_boundary[middle_block][right];\n\n       \
    \ int trailing_block = (right - 1) / _block_size;\n        for (int index = left;\
    \ index < middle_left; ++index) {\n            int rank = _rank[index];\n    \
    \        result +=\n                _boundary_less[trailing_block][rank]\n   \
    \             - _boundary_less[middle_block][rank];\n        }\n\n        result\
    \ += cross_inversions(\n            _sorted_suffix[left],\n            _sorted_prefix[right]\n\
    \        );\n        return result;\n    }\n\n    long long inversion_count(int\
    \ left, int right) const {\n        return query(left, right);\n    }\n};\n\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/range_query/range_inversion_count.test.cpp\"\
    \n\n#line 6 \"verify/ds/range_query/range_inversion_count.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#line 9 \"verify/ds/range_query/range_inversion_count.test.cpp\"\
    \n\nnamespace {\n\n[[maybe_unused]] long long brute(\n    const std::vector<int>&\
    \ values,\n    int left,\n    int right\n) {\n    long long result = 0;\n    for\
    \ (int first = left; first < right; ++first) {\n        for (int second = first\
    \ + 1; second < right; ++second) {\n            result += values[first] > values[second];\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 1511;\n    auto random = [&state]() {\n        state ^= state << 7;\n\
    \        state ^= state >> 9;\n        return state;\n    };\n\n    for (int trial\
    \ = 0; trial < 3000; ++trial) {\n        int size = int(random() % 100);\n   \
    \     std::vector<int> values(size);\n        for (int& value : values) value\
    \ = int(random() % 20);\n        m1une::ds::RangeInversionCount<int> structure(values);\n\
    \        assert(structure.size() == size);\n\n        for (int left = 0; left\
    \ <= size; ++left) {\n            for (int right = left; right <= size; ++right)\
    \ {\n                assert(\n                    structure.query(left, right)\n\
    \                    == brute(values, left, right)\n                );\n     \
    \       }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    int n, query_count;\n    std::cin >> n >> query_count;\n    std::vector<int>\
    \ values(n);\n    for (int& value : values) std::cin >> value;\n    m1une::ds::RangeInversionCount<int>\
    \ structure(values);\n    while (query_count--) {\n        int left, right;\n\
    \        std::cin >> left >> right;\n        std::cout << structure.query(left,\
    \ right) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"../../../ds/range_query/range_inversion_count.hpp\"\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <vector>\n\nnamespace\
    \ {\n\n[[maybe_unused]] long long brute(\n    const std::vector<int>& values,\n\
    \    int left,\n    int right\n) {\n    long long result = 0;\n    for (int first\
    \ = left; first < right; ++first) {\n        for (int second = first + 1; second\
    \ < right; ++second) {\n            result += values[first] > values[second];\n\
    \        }\n    }\n    return result;\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 1511;\n    auto random = [&state]() {\n        state ^= state << 7;\n\
    \        state ^= state >> 9;\n        return state;\n    };\n\n    for (int trial\
    \ = 0; trial < 3000; ++trial) {\n        int size = int(random() % 100);\n   \
    \     std::vector<int> values(size);\n        for (int& value : values) value\
    \ = int(random() % 20);\n        m1une::ds::RangeInversionCount<int> structure(values);\n\
    \        assert(structure.size() == size);\n\n        for (int left = 0; left\
    \ <= size; ++left) {\n            for (int right = left; right <= size; ++right)\
    \ {\n                assert(\n                    structure.query(left, right)\n\
    \                    == brute(values, left, right)\n                );\n     \
    \       }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    int n, query_count;\n    std::cin >> n >> query_count;\n    std::vector<int>\
    \ values(n);\n    for (int& value : values) std::cin >> value;\n    m1une::ds::RangeInversionCount<int>\
    \ structure(values);\n    while (query_count--) {\n        int left, right;\n\
    \        std::cin >> left >> right;\n        std::cout << structure.query(left,\
    \ right) << '\\n';\n    }\n}\n"
  dependsOn:
  - ds/range_query/range_inversion_count.hpp
  isVerificationFile: true
  path: verify/ds/range_query/range_inversion_count.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 03:10:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/range_inversion_count.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/range_inversion_count.test.cpp
- /verify/verify/ds/range_query/range_inversion_count.test.cpp.html
title: verify/ds/range_query/range_inversion_count.test.cpp
---
