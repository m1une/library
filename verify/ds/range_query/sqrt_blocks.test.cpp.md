---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/range_query/sqrt_blocks.hpp
    title: Custom Square-Root Blocks
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/ds/range_query/sqrt_blocks.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/range_query/sqrt_blocks.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Square-root decomposition\
    \ framework with user-defined per-block state.\ntemplate <class T, class Block>\n\
    struct SqrtBlocks {\n   private:\n    int _n;\n    int _block_size;\n    int _block_count;\n\
    \    std::vector<T> _values;\n    std::vector<Block> _blocks;\n\n    void initialize_blocks(int\
    \ requested_block_size) {\n        if (requested_block_size > 0) {\n         \
    \   _block_size = requested_block_size;\n        } else {\n            _block_size\
    \ = std::max(\n                1,\n                int(std::ceil(std::sqrt(static_cast<long\
    \ double>(_n))))\n            );\n        }\n        _block_count = _n == 0 ?\
    \ 0 : 1 + (_n - 1) / _block_size;\n        _blocks.resize(_block_count);\n   \
    \     for (int block_index = 0; block_index < _block_count; ++block_index) {\n\
    \            rebuild(block_index);\n        }\n    }\n\n   public:\n    SqrtBlocks()\n\
    \        : _n(0), _block_size(1), _block_count(0) {}\n\n    explicit SqrtBlocks(std::vector<T>\
    \ values, int block_size = -1)\n        : _n(int(values.size())),\n          _block_size(1),\n\
    \          _block_count(0),\n          _values(std::move(values)) {\n        initialize_blocks(block_size);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    int block_size() const {\n  \
    \      return _block_size;\n    }\n\n    int block_count() const {\n        return\
    \ _block_count;\n    }\n\n    int block_of(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        return index / _block_size;\n    }\n\n   \
    \ std::pair<int, int> block_range(int block_index) const {\n        assert(0 <=\
    \ block_index && block_index < _block_count);\n        int left = block_index\
    \ * _block_size;\n        return {left, std::min(_n, left + _block_size)};\n \
    \   }\n\n    const std::vector<T>& values() const {\n        return _values;\n\
    \    }\n\n    const Block& block(int block_index) const {\n        assert(0 <=\
    \ block_index && block_index < _block_count);\n        return _blocks[block_index];\n\
    \    }\n\n    Block& block(int block_index) {\n        assert(0 <= block_index\
    \ && block_index < _block_count);\n        return _blocks[block_index];\n    }\n\
    \n    // Rebuilds the cached state from raw values. This does not push first.\n\
    \    void rebuild(int block_index) {\n        auto [left, right] = block_range(block_index);\n\
    \        _blocks[block_index].build(_values, left, right);\n    }\n\n    // Materializes\
    \ this block's optional lazy state into raw values.\n    void push(int block_index)\
    \ {\n        assert(0 <= block_index && block_index < _block_count);\n       \
    \ if constexpr (requires(\n            Block& current,\n            std::vector<T>&\
    \ values,\n            int left,\n            int right\n        ) {\n       \
    \     current.push(values, left, right);\n        }) {\n            auto [left,\
    \ right] = block_range(block_index);\n            _blocks[block_index].push(_values,\
    \ left, right);\n        }\n    }\n\n    T get(int index) const {\n        assert(0\
    \ <= index && index < _n);\n        const Block& current = _blocks[block_of(index)];\n\
    \        if constexpr (requires(\n            const Block& candidate,\n      \
    \      const T& raw,\n            int position\n        ) {\n            candidate.value(raw,\
    \ position);\n        }) {\n            return current.value(_values[index], index);\n\
    \        } else if constexpr (requires(const Block& candidate, const T& raw) {\n\
    \            candidate.value(raw);\n        }) {\n            return current.value(_values[index]);\n\
    \        } else {\n            return _values[index];\n        }\n    }\n\n  \
    \  T operator[](int index) const {\n        return get(index);\n    }\n\n    void\
    \ set(int index, T value) {\n        assert(0 <= index && index < _n);\n     \
    \   int block_index = block_of(index);\n        push(block_index);\n        _values[index]\
    \ = std::move(value);\n        rebuild(block_index);\n    }\n\n    template <class\
    \ F>\n    void apply_point(int index, F f) {\n        assert(0 <= index && index\
    \ < _n);\n        int block_index = block_of(index);\n        push(block_index);\n\
    \        f(_values[index]);\n        rebuild(block_index);\n    }\n\n    template\
    \ <class Full, class Partial>\n    void update_range(int left, int right, Full\
    \ full, Partial partial) {\n        assert(0 <= left && left <= right && right\
    \ <= _n);\n        while (left < right) {\n            int block_index = left\
    \ / _block_size;\n            auto [block_left, block_right] = block_range(block_index);\n\
    \            int segment_right = std::min(right, block_right);\n            if\
    \ (left == block_left && segment_right == block_right) {\n                full(block_index,\
    \ _blocks[block_index]);\n            } else {\n                push(block_index);\n\
    \                partial(\n                    left,\n                    segment_right,\n\
    \                    block_index,\n                    _values,\n            \
    \        _blocks[block_index]\n                );\n                rebuild(block_index);\n\
    \            }\n            left = segment_right;\n        }\n    }\n\n    template\
    \ <class Full, class Partial>\n    void query_range(int left, int right, Full\
    \ full, Partial partial) const {\n        assert(0 <= left && left <= right &&\
    \ right <= _n);\n        while (left < right) {\n            int block_index =\
    \ left / _block_size;\n            auto [block_left, block_right] = block_range(block_index);\n\
    \            int segment_right = std::min(right, block_right);\n            if\
    \ (left == block_left && segment_right == block_right) {\n                full(block_index,\
    \ _blocks[block_index]);\n            } else {\n                partial(left,\
    \ segment_right, block_index, _blocks[block_index]);\n            }\n        \
    \    left = segment_right;\n        }\n    }\n};\n\n}  // namespace ds\n}  //\
    \ namespace m1une\n\n\n#line 4 \"verify/ds/range_query/sqrt_blocks.test.cpp\"\n\
    \n#line 7 \"verify/ds/range_query/sqrt_blocks.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#line 11 \"verify/ds/range_query/sqrt_blocks.test.cpp\"\n\
    \nnamespace {\n\nstruct SortedBlock {\n    std::vector<long long> sorted;\n\n\
    \    void build(const std::vector<long long>& values, int left, int right) {\n\
    \        sorted.assign(values.begin() + left, values.begin() + right);\n     \
    \   std::sort(sorted.begin(), sorted.end());\n    }\n};\n\nstruct RangeCountLess\
    \ {\n    m1une::ds::SqrtBlocks<long long, SortedBlock> data;\n\n    explicit RangeCountLess(std::vector<long\
    \ long> values, int block_size = -1)\n        : data(std::move(values), block_size)\
    \ {}\n\n    void set(int index, long long value) {\n        data.set(index, value);\n\
    \    }\n\n    void increment(int index) {\n        data.apply_point(index, [](long\
    \ long& value) { ++value; });\n    }\n\n    int count_less(int left, int right,\
    \ long long x) const {\n        int result = 0;\n        data.query_range(\n \
    \           left,\n            right,\n            [&](int, const SortedBlock&\
    \ block) {\n                result += int(std::lower_bound(\n                \
    \    block.sorted.begin(),\n                    block.sorted.end(),\n        \
    \            x\n                ) - block.sorted.begin());\n            },\n \
    \           [&](int segment_left, int segment_right, int, const SortedBlock&)\
    \ {\n                for (int index = segment_left; index < segment_right; ++index)\
    \ {\n                    result += data.get(index) < x;\n                }\n \
    \           }\n        );\n        return result;\n    }\n};\n\nstruct AddBlock\
    \ {\n    std::vector<long long> sorted;\n    long long lazy = 0;\n\n    void build(const\
    \ std::vector<long long>& values, int left, int right) {\n        sorted.assign(values.begin()\
    \ + left, values.begin() + right);\n        std::sort(sorted.begin(), sorted.end());\n\
    \        lazy = 0;\n    }\n\n    void push(std::vector<long long>& values, int\
    \ left, int right) {\n        for (int index = left; index < right; ++index) {\n\
    \            values[index] += lazy;\n        }\n        lazy = 0;\n    }\n\n \
    \   long long value(const long long& raw, int) const {\n        return raw + lazy;\n\
    \    }\n};\n\nstruct RangeAddCountLess {\n    m1une::ds::SqrtBlocks<long long,\
    \ AddBlock> data;\n\n    explicit RangeAddCountLess(\n        std::vector<long\
    \ long> values,\n        int block_size = -1\n    ) : data(std::move(values),\
    \ block_size) {}\n\n    void add(int left, int right, long long value) {\n   \
    \     data.update_range(\n            left,\n            right,\n            [&](int,\
    \ AddBlock& block) {\n                block.lazy += value;\n            },\n \
    \           [&](int segment_left,\n                int segment_right,\n      \
    \          int,\n                std::vector<long long>& values,\n           \
    \     AddBlock&) {\n                for (int index = segment_left; index < segment_right;\
    \ ++index) {\n                    values[index] += value;\n                }\n\
    \            }\n        );\n    }\n\n    int count_less(int left, int right, long\
    \ long x) const {\n        int result = 0;\n        data.query_range(\n      \
    \      left,\n            right,\n            [&](int, const AddBlock& block)\
    \ {\n                result += int(std::lower_bound(\n                    block.sorted.begin(),\n\
    \                    block.sorted.end(),\n                    x - block.lazy\n\
    \                ) - block.sorted.begin());\n            },\n            [&](int\
    \ segment_left, int segment_right, int, const AddBlock&) {\n                for\
    \ (int index = segment_left; index < segment_right; ++index) {\n             \
    \       result += data.get(index) < x;\n                }\n            }\n   \
    \     );\n        return result;\n    }\n\n    long long get(int index) const\
    \ {\n        return data.get(index);\n    }\n};\n\nint naive_count_less(\n   \
    \ const std::vector<long long>& values,\n    int left,\n    int right,\n    long\
    \ long x\n) {\n    int result = 0;\n    for (int index = left; index < right;\
    \ ++index) {\n        result += values[index] < x;\n    }\n    return result;\n\
    }\n\nvoid test_fixed() {\n    RangeCountLess empty(std::vector<long long>{});\n\
    \    assert(empty.data.empty());\n    assert(empty.data.size() == 0);\n    assert(empty.data.block_size()\
    \ == 1);\n    assert(empty.data.block_count() == 0);\n    assert(empty.count_less(0,\
    \ 0, 10) == 0);\n\n    RangeAddCountLess custom_empty(std::vector<long long>{},\
    \ 7);\n    assert(custom_empty.data.block_size() == 7);\n    assert(custom_empty.data.block_count()\
    \ == 0);\n    custom_empty.add(0, 0, 3);\n    assert(custom_empty.count_less(0,\
    \ 0, 0) == 0);\n\n    RangeCountLess one(std::vector<long long>{4});\n    assert(one.count_less(0,\
    \ 1, 5) == 1);\n    one.set(0, 9);\n    assert(one.count_less(0, 1, 5) == 0);\n\
    \    one.increment(0);\n    assert(one.data[0] == 10);\n\n    std::vector<long\
    \ long> initial = {3, -1, 4, 1, 5};\n    RangeAddCountLess range_add(initial,\
    \ 3);\n    assert(range_add.data.block_size() == 3);\n    assert(range_add.data.block_count()\
    \ == 2);\n    assert(range_add.data.block_of(4) == 1);\n    std::pair<int, int>\
    \ expected_range(0, 3);\n    assert(range_add.data.block_range(0) == expected_range);\n\
    \    range_add.add(0, 3, 7);\n    initial[0] += 7;\n    initial[1] += 7;\n   \
    \ initial[2] += 7;\n    assert(range_add.get(1) == initial[1]);\n    range_add.add(1,\
    \ 5, -2);\n    for (int index = 1; index < 5; ++index) initial[index] -= 2;\n\
    \    for (int index = 0; index < 5; ++index) {\n        assert(range_add.get(index)\
    \ == initial[index]);\n    }\n    for (long long x = -5; x <= 15; ++x) {\n   \
    \     assert(\n            range_add.count_less(1, 5, x) ==\n            naive_count_less(initial,\
    \ 1, 5, x)\n        );\n    }\n}\n\nvoid test_range_count_less_randomized() {\n\
    \    std::uint64_t state = 0xA0761D6478BD642FULL;\n    auto random = [&]() {\n\
    \        state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 400; ++trial) {\n        int n = int(random()\
    \ % 26);\n        std::vector<long long> naive(n);\n        for (long long& value\
    \ : naive) {\n            value = static_cast<long long>(random() % 21) - 10;\n\
    \        }\n        int block_size = trial % 2 == 0 ? -1 : int(random() % 8) +\
    \ 1;\n        RangeCountLess blocks(naive, block_size);\n\n        for (int operation\
    \ = 0; operation < 250; ++operation) {\n            if (n != 0 && random() % 3\
    \ == 0) {\n                int index = int(random() % n);\n                long\
    \ long value = static_cast<long long>(random() % 31) - 15;\n                naive[index]\
    \ = value;\n                blocks.set(index, value);\n            } else {\n\
    \                int left = int(random() % (n + 1));\n                int right\
    \ = int(random() % (n + 1));\n                if (right < left) std::swap(left,\
    \ right);\n                long long x = static_cast<long long>(random() % 35)\
    \ - 17;\n                assert(\n                    blocks.count_less(left,\
    \ right, x) ==\n                    naive_count_less(naive, left, right, x)\n\
    \                );\n            }\n        }\n    }\n}\n\nvoid test_range_add_count_less_randomized()\
    \ {\n    std::uint64_t state = 0xE7037ED1A0B428DBULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 400; ++trial) {\n        int\
    \ n = int(random() % 26);\n        std::vector<long long> naive(n);\n        for\
    \ (long long& value : naive) {\n            value = static_cast<long long>(random()\
    \ % 21) - 10;\n        }\n        int block_size = trial % 2 == 0 ? -1 : int(random()\
    \ % 8) + 1;\n        RangeAddCountLess blocks(naive, block_size);\n\n        for\
    \ (int operation = 0; operation < 250; ++operation) {\n            int type =\
    \ int(random() % 3);\n            if (type == 0) {\n                int left =\
    \ int(random() % (n + 1));\n                int right = int(random() % (n + 1));\n\
    \                if (right < left) std::swap(left, right);\n                long\
    \ long value = static_cast<long long>(random() % 15) - 7;\n                blocks.add(left,\
    \ right, value);\n                for (int index = left; index < right; ++index)\
    \ {\n                    naive[index] += value;\n                }\n         \
    \   } else if (type == 1 || n == 0) {\n                int left = int(random()\
    \ % (n + 1));\n                int right = int(random() % (n + 1));\n        \
    \        if (right < left) std::swap(left, right);\n                long long\
    \ x = static_cast<long long>(random() % 61) - 30;\n                assert(\n \
    \                   blocks.count_less(left, right, x) ==\n                   \
    \ naive_count_less(naive, left, right, x)\n                );\n            } else\
    \ {\n                int index = int(random() % n);\n                assert(blocks.get(index)\
    \ == naive[index]);\n            }\n        }\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    test_fixed();\n    test_range_count_less_randomized();\n   \
    \ test_range_add_count_less_randomized();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/range_query/sqrt_blocks.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <utility>\n#include <vector>\n\
    \nnamespace {\n\nstruct SortedBlock {\n    std::vector<long long> sorted;\n\n\
    \    void build(const std::vector<long long>& values, int left, int right) {\n\
    \        sorted.assign(values.begin() + left, values.begin() + right);\n     \
    \   std::sort(sorted.begin(), sorted.end());\n    }\n};\n\nstruct RangeCountLess\
    \ {\n    m1une::ds::SqrtBlocks<long long, SortedBlock> data;\n\n    explicit RangeCountLess(std::vector<long\
    \ long> values, int block_size = -1)\n        : data(std::move(values), block_size)\
    \ {}\n\n    void set(int index, long long value) {\n        data.set(index, value);\n\
    \    }\n\n    void increment(int index) {\n        data.apply_point(index, [](long\
    \ long& value) { ++value; });\n    }\n\n    int count_less(int left, int right,\
    \ long long x) const {\n        int result = 0;\n        data.query_range(\n \
    \           left,\n            right,\n            [&](int, const SortedBlock&\
    \ block) {\n                result += int(std::lower_bound(\n                \
    \    block.sorted.begin(),\n                    block.sorted.end(),\n        \
    \            x\n                ) - block.sorted.begin());\n            },\n \
    \           [&](int segment_left, int segment_right, int, const SortedBlock&)\
    \ {\n                for (int index = segment_left; index < segment_right; ++index)\
    \ {\n                    result += data.get(index) < x;\n                }\n \
    \           }\n        );\n        return result;\n    }\n};\n\nstruct AddBlock\
    \ {\n    std::vector<long long> sorted;\n    long long lazy = 0;\n\n    void build(const\
    \ std::vector<long long>& values, int left, int right) {\n        sorted.assign(values.begin()\
    \ + left, values.begin() + right);\n        std::sort(sorted.begin(), sorted.end());\n\
    \        lazy = 0;\n    }\n\n    void push(std::vector<long long>& values, int\
    \ left, int right) {\n        for (int index = left; index < right; ++index) {\n\
    \            values[index] += lazy;\n        }\n        lazy = 0;\n    }\n\n \
    \   long long value(const long long& raw, int) const {\n        return raw + lazy;\n\
    \    }\n};\n\nstruct RangeAddCountLess {\n    m1une::ds::SqrtBlocks<long long,\
    \ AddBlock> data;\n\n    explicit RangeAddCountLess(\n        std::vector<long\
    \ long> values,\n        int block_size = -1\n    ) : data(std::move(values),\
    \ block_size) {}\n\n    void add(int left, int right, long long value) {\n   \
    \     data.update_range(\n            left,\n            right,\n            [&](int,\
    \ AddBlock& block) {\n                block.lazy += value;\n            },\n \
    \           [&](int segment_left,\n                int segment_right,\n      \
    \          int,\n                std::vector<long long>& values,\n           \
    \     AddBlock&) {\n                for (int index = segment_left; index < segment_right;\
    \ ++index) {\n                    values[index] += value;\n                }\n\
    \            }\n        );\n    }\n\n    int count_less(int left, int right, long\
    \ long x) const {\n        int result = 0;\n        data.query_range(\n      \
    \      left,\n            right,\n            [&](int, const AddBlock& block)\
    \ {\n                result += int(std::lower_bound(\n                    block.sorted.begin(),\n\
    \                    block.sorted.end(),\n                    x - block.lazy\n\
    \                ) - block.sorted.begin());\n            },\n            [&](int\
    \ segment_left, int segment_right, int, const AddBlock&) {\n                for\
    \ (int index = segment_left; index < segment_right; ++index) {\n             \
    \       result += data.get(index) < x;\n                }\n            }\n   \
    \     );\n        return result;\n    }\n\n    long long get(int index) const\
    \ {\n        return data.get(index);\n    }\n};\n\nint naive_count_less(\n   \
    \ const std::vector<long long>& values,\n    int left,\n    int right,\n    long\
    \ long x\n) {\n    int result = 0;\n    for (int index = left; index < right;\
    \ ++index) {\n        result += values[index] < x;\n    }\n    return result;\n\
    }\n\nvoid test_fixed() {\n    RangeCountLess empty(std::vector<long long>{});\n\
    \    assert(empty.data.empty());\n    assert(empty.data.size() == 0);\n    assert(empty.data.block_size()\
    \ == 1);\n    assert(empty.data.block_count() == 0);\n    assert(empty.count_less(0,\
    \ 0, 10) == 0);\n\n    RangeAddCountLess custom_empty(std::vector<long long>{},\
    \ 7);\n    assert(custom_empty.data.block_size() == 7);\n    assert(custom_empty.data.block_count()\
    \ == 0);\n    custom_empty.add(0, 0, 3);\n    assert(custom_empty.count_less(0,\
    \ 0, 0) == 0);\n\n    RangeCountLess one(std::vector<long long>{4});\n    assert(one.count_less(0,\
    \ 1, 5) == 1);\n    one.set(0, 9);\n    assert(one.count_less(0, 1, 5) == 0);\n\
    \    one.increment(0);\n    assert(one.data[0] == 10);\n\n    std::vector<long\
    \ long> initial = {3, -1, 4, 1, 5};\n    RangeAddCountLess range_add(initial,\
    \ 3);\n    assert(range_add.data.block_size() == 3);\n    assert(range_add.data.block_count()\
    \ == 2);\n    assert(range_add.data.block_of(4) == 1);\n    std::pair<int, int>\
    \ expected_range(0, 3);\n    assert(range_add.data.block_range(0) == expected_range);\n\
    \    range_add.add(0, 3, 7);\n    initial[0] += 7;\n    initial[1] += 7;\n   \
    \ initial[2] += 7;\n    assert(range_add.get(1) == initial[1]);\n    range_add.add(1,\
    \ 5, -2);\n    for (int index = 1; index < 5; ++index) initial[index] -= 2;\n\
    \    for (int index = 0; index < 5; ++index) {\n        assert(range_add.get(index)\
    \ == initial[index]);\n    }\n    for (long long x = -5; x <= 15; ++x) {\n   \
    \     assert(\n            range_add.count_less(1, 5, x) ==\n            naive_count_less(initial,\
    \ 1, 5, x)\n        );\n    }\n}\n\nvoid test_range_count_less_randomized() {\n\
    \    std::uint64_t state = 0xA0761D6478BD642FULL;\n    auto random = [&]() {\n\
    \        state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 400; ++trial) {\n        int n = int(random()\
    \ % 26);\n        std::vector<long long> naive(n);\n        for (long long& value\
    \ : naive) {\n            value = static_cast<long long>(random() % 21) - 10;\n\
    \        }\n        int block_size = trial % 2 == 0 ? -1 : int(random() % 8) +\
    \ 1;\n        RangeCountLess blocks(naive, block_size);\n\n        for (int operation\
    \ = 0; operation < 250; ++operation) {\n            if (n != 0 && random() % 3\
    \ == 0) {\n                int index = int(random() % n);\n                long\
    \ long value = static_cast<long long>(random() % 31) - 15;\n                naive[index]\
    \ = value;\n                blocks.set(index, value);\n            } else {\n\
    \                int left = int(random() % (n + 1));\n                int right\
    \ = int(random() % (n + 1));\n                if (right < left) std::swap(left,\
    \ right);\n                long long x = static_cast<long long>(random() % 35)\
    \ - 17;\n                assert(\n                    blocks.count_less(left,\
    \ right, x) ==\n                    naive_count_less(naive, left, right, x)\n\
    \                );\n            }\n        }\n    }\n}\n\nvoid test_range_add_count_less_randomized()\
    \ {\n    std::uint64_t state = 0xE7037ED1A0B428DBULL;\n    auto random = [&]()\
    \ {\n        state ^= state << 7;\n        state ^= state >> 9;\n        return\
    \ state;\n    };\n\n    for (int trial = 0; trial < 400; ++trial) {\n        int\
    \ n = int(random() % 26);\n        std::vector<long long> naive(n);\n        for\
    \ (long long& value : naive) {\n            value = static_cast<long long>(random()\
    \ % 21) - 10;\n        }\n        int block_size = trial % 2 == 0 ? -1 : int(random()\
    \ % 8) + 1;\n        RangeAddCountLess blocks(naive, block_size);\n\n        for\
    \ (int operation = 0; operation < 250; ++operation) {\n            int type =\
    \ int(random() % 3);\n            if (type == 0) {\n                int left =\
    \ int(random() % (n + 1));\n                int right = int(random() % (n + 1));\n\
    \                if (right < left) std::swap(left, right);\n                long\
    \ long value = static_cast<long long>(random() % 15) - 7;\n                blocks.add(left,\
    \ right, value);\n                for (int index = left; index < right; ++index)\
    \ {\n                    naive[index] += value;\n                }\n         \
    \   } else if (type == 1 || n == 0) {\n                int left = int(random()\
    \ % (n + 1));\n                int right = int(random() % (n + 1));\n        \
    \        if (right < left) std::swap(left, right);\n                long long\
    \ x = static_cast<long long>(random() % 61) - 30;\n                assert(\n \
    \                   blocks.count_less(left, right, x) ==\n                   \
    \ naive_count_less(naive, left, right, x)\n                );\n            } else\
    \ {\n                int index = int(random() % n);\n                assert(blocks.get(index)\
    \ == naive[index]);\n            }\n        }\n    }\n}\n\n}  // namespace\n\n\
    int main() {\n    test_fixed();\n    test_range_count_less_randomized();\n   \
    \ test_range_add_count_less_randomized();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - ds/range_query/sqrt_blocks.hpp
  isVerificationFile: true
  path: verify/ds/range_query/sqrt_blocks.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 19:54:19+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/range_query/sqrt_blocks.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/range_query/sqrt_blocks.test.cpp
- /verify/verify/ds/range_query/sqrt_blocks.test.cpp.html
title: verify/ds/range_query/sqrt_blocks.test.cpp
---
