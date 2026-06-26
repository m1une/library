---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/range_inversion_count.hpp
    title: Static Range Inversion Count
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
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
    \   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n    int\
    \ _value_count;\n    std::vector<int> _rank;\n    std::vector<std::vector<int>>\
    \ _boundary_less;\n    std::vector<std::vector<int>> _local_inversion;\n    std::vector<std::vector<int>>\
    \ _sorted_suffix;\n    std::vector<std::vector<int>> _sorted_prefix;\n    std::vector<long\
    \ long> _block_inversion;\n    std::vector<std::vector<long long>> _full_block_inversion;\n\
    \n    int block_start(int block) const {\n        return block * _block_size;\n\
    \    }\n\n    int block_end(int block) const {\n        return std::min(_n, block_start(block)\
    \ + _block_size);\n    }\n\n    int local_index(int block, int offset, int length)\
    \ const {\n        int block_length = block_end(block) - block_start(block);\n\
    \        return offset * (block_length + 1)\n               - offset * (offset\
    \ - 1) / 2\n               + length;\n    }\n\n    long long local_query(int left,\
    \ int right) const {\n        if (right - left <= 1) return 0;\n        int block\
    \ = left / _block_size;\n        int offset = left - block_start(block);\n   \
    \     return _local_inversion[block][\n            local_index(block, offset,\
    \ right - left)\n        ];\n    }\n\n    int count_less_blocks(int first_block,\
    \ int last_block, int rank) const {\n        if (first_block >= last_block) return\
    \ 0;\n        return _boundary_less[last_block][rank]\n               - _boundary_less[first_block][rank];\n\
    \    }\n\n    int count_greater_blocks(int first_block, int last_block, int rank)\
    \ const {\n        int length = block_start(last_block) - block_start(first_block);\n\
    \        return length - count_less_blocks(first_block, last_block, rank + 1);\n\
    \    }\n\n    static long long cross_inversions(\n        const std::vector<int>&\
    \ left,\n        const std::vector<int>& right\n    ) {\n        long long result\
    \ = 0;\n        int smaller = 0;\n        for (int value : left) {\n         \
    \   while (smaller < int(right.size()) && right[smaller] < value) {\n        \
    \        ++smaller;\n            }\n            result += smaller;\n        }\n\
    \        return result;\n    }\n\n    void build_local_data() {\n        _local_inversion.resize(_block_count);\n\
    \        _sorted_suffix.resize(_n);\n        _sorted_prefix.resize(_n + 1);\n\
    \        _block_inversion.assign(_block_count, 0);\n\n        for (int block =\
    \ 0; block < _block_count; ++block) {\n            int start = block_start(block);\n\
    \            int end = block_end(block);\n            int length = end - start;\n\
    \            std::vector<int> greater(length * length, 0);\n            _local_inversion[block].assign(length\
    \ * (length + 3) / 2, 0);\n\n            for (int right = 0; right < length; ++right)\
    \ {\n                int count = 0;\n                for (int left = right - 1;\
    \ 0 <= left; --left) {\n                    count += _rank[start + left] > _rank[start\
    \ + right];\n                    greater[left * length + right] = count;\n   \
    \             }\n            }\n\n            for (int left = 0; left < length;\
    \ ++left) {\n                long long inversions = 0;\n                for (int\
    \ right = left; right < length; ++right) {\n                    inversions +=\
    \ greater[left * length + right];\n                    _local_inversion[block][\n\
    \                        local_index(block, left, right - left + 1)\n        \
    \            ] =\n                        int(inversions);\n                }\n\
    \            }\n            _block_inversion[block] =\n                _local_inversion[block][local_index(block,\
    \ 0, length)];\n\n            std::vector<int> sorted;\n            for (int index\
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
    \ = sorted;\n            }\n        }\n    }\n\n    void build_boundary_counts()\
    \ {\n        _boundary_less.assign(\n            _block_count + 1,\n         \
    \   std::vector<int>(_value_count + 1, 0)\n        );\n        std::vector<int>\
    \ frequency(_value_count, 0);\n        for (int block = 0; block <= _block_count;\
    \ ++block) {\n            int boundary = std::min(_n, block_start(block));\n \
    \           if (block != 0) {\n                int previous = block_start(block\
    \ - 1);\n                for (int index = previous; index < boundary; ++index)\
    \ {\n                    frequency[_rank[index]]++;\n                }\n     \
    \       }\n            int count = 0;\n            for (int rank = 0; rank < _value_count;\
    \ ++rank) {\n                _boundary_less[block][rank] = count;\n          \
    \      count += frequency[rank];\n            }\n            _boundary_less[block][_value_count]\
    \ = count;\n        }\n    }\n\n    void build_full_block_inversions() {\n   \
    \     _full_block_inversion.assign(\n            _block_count + 1,\n         \
    \   std::vector<long long>(_block_count + 1, 0)\n        );\n        for (int\
    \ first = 0; first < _block_count; ++first) {\n            long long inversions\
    \ = 0;\n            for (int last = first; last < _block_count; ++last) {\n  \
    \              int prior_length = block_start(last) - block_start(first);\n  \
    \              for (\n                    int index = block_start(last);\n   \
    \                 index < block_end(last);\n                    ++index\n    \
    \            ) {\n                    int less_equal =\n                     \
    \   count_less_blocks(first, last, _rank[index] + 1);\n                    inversions\
    \ += prior_length - less_equal;\n                }\n                inversions\
    \ += _block_inversion[last];\n                _full_block_inversion[first][last\
    \ + 1] = inversions;\n            }\n        }\n    }\n\n   public:\n    RangeInversionCount()\n\
    \        : _n(0), _block_size(1), _block_count(0), _value_count(0) {}\n\n    explicit\
    \ RangeInversionCount(const std::vector<T>& values)\n        : _n(int(values.size())),\n\
    \          _block_size(1),\n          _block_count(0),\n          _value_count(0)\
    \ {\n        if (_n == 0) return;\n\n        _block_size = std::max(\n       \
    \     1,\n            int(std::sqrt(static_cast<long double>(_n)))\n        );\n\
    \        while (1LL * _block_size * _block_size < _n) ++_block_size;\n       \
    \ _block_count = (_n + _block_size - 1) / _block_size;\n\n        std::vector<T>\
    \ sorted = values;\n        std::sort(sorted.begin(), sorted.end());\n       \
    \ sorted.erase(std::unique(sorted.begin(), sorted.end()), sorted.end());\n   \
    \     _value_count = int(sorted.size());\n        _rank.resize(_n);\n        for\
    \ (int index = 0; index < _n; ++index) {\n            _rank[index] = int(\n  \
    \              std::lower_bound(\n                    sorted.begin(),\n      \
    \              sorted.end(),\n                    values[index]\n            \
    \    ) - sorted.begin()\n            );\n        }\n\n        build_local_data();\n\
    \        build_boundary_counts();\n        build_full_block_inversions();\n  \
    \  }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    // Returns the number of pairs (i, j)\
    \ with\n    // left <= i < j < right and values[i] > values[j].\n    long long\
    \ query(int left, int right) const {\n        assert(0 <= left && left <= right\
    \ && right <= _n);\n        if (right - left <= 1) return 0;\n\n        int left_block\
    \ = left / _block_size;\n        int right_block = (right - 1) / _block_size;\n\
    \        if (left_block == right_block) {\n            return local_query(left,\
    \ right);\n        }\n\n        int first_full = (left + _block_size - 1) / _block_size;\n\
    \        int last_full = right / _block_size;\n        int left_end = std::min(right,\
    \ block_start(first_full));\n        int right_start = std::max(left_end, block_start(last_full));\n\
    \n        long long result = _full_block_inversion[first_full][last_full];\n \
    \       result += local_query(left, left_end);\n        result += local_query(right_start,\
    \ right);\n\n        for (int index = left; index < left_end; ++index) {\n   \
    \         result += count_less_blocks(first_full, last_full, _rank[index]);\n\
    \        }\n\n        for (int index = right_start; index < right; ++index) {\n\
    \            result += count_greater_blocks(first_full, last_full, _rank[index]);\n\
    \        }\n\n        if (left < left_end && right_start < right) {\n        \
    \    result += cross_inversions(\n                _sorted_suffix[left],\n    \
    \            _sorted_prefix[right]\n            );\n        }\n        return\
    \ result;\n    }\n\n    long long inversion_count(int left, int right) const {\n\
    \        return query(left, right);\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <cstdio>\n#include\
    \ <string>\n#include <type_traits>\n\nnamespace m1une {\nnamespace utilities {\n\
    \nstruct FastInput {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n\
    \    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int _position;\n\
    \    int _length;\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream), _position(0), _length(0) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length) {\n           \
    \ _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n            _position\
    \ = 0;\n            if (_length == 0) return EOF;\n        }\n        return _buffer[_position++];\n\
    \    }\n\n    bool skip_spaces() {\n        int c = read_char_raw();\n       \
    \ while (c != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return\
    \ false;\n        --_position;\n        return true;\n    }\n\n    bool read(char&\
    \ value) {\n        if (!skip_spaces()) return false;\n        value = char(read_char_raw());\n\
    \        return true;\n    }\n\n    bool read(std::string& value) {\n        if\
    \ (!skip_spaces()) return false;\n        value.clear();\n        int c = read_char_raw();\n\
    \        while (c != EOF && c > ' ') {\n            value.push_back(char(c));\n\
    \            c = read_char_raw();\n        }\n        return true;\n    }\n\n\
    \    bool read(bool& value) {\n        int x;\n        if (!read(x)) return false;\n\
    \        value = x != 0;\n        return true;\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return false;\n\
    \n        bool negative = false;\n        if (c == '-') {\n            negative\
    \ = true;\n            c = read_char_raw();\n        }\n\n        if constexpr\
    \ (std::is_signed_v<T>) {\n            T result = 0;\n            while ('0' <=\
    \ c && c <= '9') {\n                int digit = c - '0';\n                result\
    \ = negative ? result * 10 - digit : result * 10 + digit;\n                c =\
    \ read_char_raw();\n            }\n            value = result;\n        } else\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               result = result * 10 + T(c - '0');\n                c = read_char_raw();\n\
    \            }\n            value = negative ? T(0) - result : result;\n     \
    \   }\n        return true;\n    }\n\n    template <class First, class Second,\
    \ class... Rest>\n    bool read(First& first, Second& second, Rest&... rest) {\n\
    \        if (!read(first)) return false;\n        return read(second, rest...);\n\
    \    }\n};\n\nstruct FastOutput {\n    static constexpr int buffer_size = 1 <<\
    \ 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n\n   public:\n    explicit FastOutput(std::FILE* stream =\
    \ stdout)\n        : _stream(stream), _position(0) {}\n\n    FastOutput(const\
    \ FastOutput&) = delete;\n    FastOutput& operator=(const FastOutput&) = delete;\n\
    \n    ~FastOutput() {\n        flush();\n    }\n\n    void flush() {\n       \
    \ if (_position == 0) return;\n        std::fwrite(_buffer, 1, _position, _stream);\n\
    \        _position = 0;\n    }\n\n    void write_char(char c) {\n        if (_position\
    \ == buffer_size) flush();\n        _buffer[_position++] = c;\n    }\n\n    void\
    \ write(const char* s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\
    \n    void write(const std::string& s) {\n        for (char c : s) write_char(c);\n\
    \    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\n    void\
    \ write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<\n        std::is_integral_v<T>\n          \
    \  && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n\
    \        if constexpr (std::is_signed_v<Raw>) {\n            if (value < 0) {\n\
    \                write_char('-');\n                magnitude = Unsigned(0) - Unsigned(value);\n\
    \            } else {\n                magnitude = Unsigned(value);\n        \
    \    }\n        } else {\n            magnitude = value;\n        }\n\n      \
    \  if (magnitude == 0) {\n            write_char('0');\n            return;\n\
    \        }\n\n        char digits[64];\n        int count = 0;\n        while\
    \ (magnitude > 0) {\n            digits[count++] = char('0' + magnitude % 10);\n\
    \            magnitude /= 10;\n        }\n        while (count--) write_char(digits[count]);\n\
    \    }\n\n    template <class First, class... Rest>\n    void print(const First&\
    \ first, const Rest&... rest) {\n        write(first);\n        ((write_char('\
    \ '), write(rest)), ...);\n    }\n\n    void println() {\n        write_char('\\\
    n');\n    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 5 \"verify/ds/range_query/range_inversion_count.test.cpp\"\
    \n\n#line 7 \"verify/ds/range_query/range_inversion_count.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#line 10 \"verify/ds/range_query/range_inversion_count.test.cpp\"\
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
    \       }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    // test_randomized();\n\
    \n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput output;\n\
    \n    int n, query_count;\n    input.read(n, query_count);\n    std::vector<int>\
    \ values(n);\n    for (int& value : values) input.read(value);\n    m1une::ds::RangeInversionCount<int>\
    \ structure(values);\n    while (query_count--) {\n        int left, right;\n\
    \        input.read(left, right);\n        output.println(structure.query(left,\
    \ right));\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_inversions_query\"\
    \n\n#include \"../../../ds/range_query/range_inversion_count.hpp\"\n#include \"\
    ../../../utilities/fast_io.hpp\"\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ <iostream>\n#include <vector>\n\nnamespace {\n\n[[maybe_unused]] long long brute(\n\
    \    const std::vector<int>& values,\n    int left,\n    int right\n) {\n    long\
    \ long result = 0;\n    for (int first = left; first < right; ++first) {\n   \
    \     for (int second = first + 1; second < right; ++second) {\n            result\
    \ += values[first] > values[second];\n        }\n    }\n    return result;\n}\n\
    \nvoid test_randomized() {\n    std::uint64_t state = 1511;\n    auto random =\
    \ [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n \
    \       return state;\n    };\n\n    for (int trial = 0; trial < 3000; ++trial)\
    \ {\n        int size = int(random() % 100);\n        std::vector<int> values(size);\n\
    \        for (int& value : values) value = int(random() % 20);\n        m1une::ds::RangeInversionCount<int>\
    \ structure(values);\n        assert(structure.size() == size);\n\n        for\
    \ (int left = 0; left <= size; ++left) {\n            for (int right = left; right\
    \ <= size; ++right) {\n                assert(\n                    structure.query(left,\
    \ right)\n                    == brute(values, left, right)\n                );\n\
    \            }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    //\
    \ test_randomized();\n\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n\n    int n, query_count;\n    input.read(n, query_count);\n    std::vector<int>\
    \ values(n);\n    for (int& value : values) input.read(value);\n    m1une::ds::RangeInversionCount<int>\
    \ structure(values);\n    while (query_count--) {\n        int left, right;\n\
    \        input.read(left, right);\n        output.println(structure.query(left,\
    \ right));\n    }\n}\n"
  dependsOn:
  - ds/range_query/range_inversion_count.hpp
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/ds/range_query/range_inversion_count.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 04:23:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/range_inversion_count.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/range_inversion_count.test.cpp
- /verify/verify/ds/range_query/range_inversion_count.test.cpp.html
title: verify/ds/range_query/range_inversion_count.test.cpp
---
