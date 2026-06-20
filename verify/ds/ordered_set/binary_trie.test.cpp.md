---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/ordered_set/binary_trie.hpp
    title: Binary Trie
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/set_xor_min
    links:
    - https://judge.yosupo.jp/problem/set_xor_min
  bundledCode: "#line 1 \"verify/ds/ordered_set/binary_trie.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#line 1 \"ds/ordered_set/binary_trie.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <initializer_list>\n\
    #include <limits>\n#include <type_traits>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <typename UInt = std::uint32_t, int BitWidth =\
    \ std::numeric_limits<UInt>::digits>\nstruct BinaryTrie {\n    static_assert(std::is_integral_v<UInt>);\n\
    \    static_assert(std::is_unsigned_v<UInt>);\n    static_assert(!std::is_same_v<UInt,\
    \ bool>);\n    static_assert(0 < BitWidth);\n    static_assert(BitWidth <= std::numeric_limits<UInt>::digits);\n\
    \n   private:\n    struct Node {\n        int child[2];\n        int count;\n\n\
    \        Node() : child{-1, -1}, count(0) {}\n    };\n\n    std::vector<Node>\
    \ nodes;\n    UInt lazy_xor;\n\n    static constexpr int bit(UInt value, int position)\
    \ {\n        return int((value >> position) & UInt(1));\n    }\n\n    static constexpr\
    \ UInt value_mask() {\n        if constexpr (BitWidth == std::numeric_limits<UInt>::digits)\
    \ {\n            return std::numeric_limits<UInt>::max();\n        } else {\n\
    \            return (UInt(1) << BitWidth) - UInt(1);\n        }\n    }\n\n   \
    \ static constexpr bool valid_value(UInt value) {\n        return (value & ~value_mask())\
    \ == UInt(0);\n    }\n\n    int new_node() {\n        nodes.emplace_back();\n\
    \        return int(nodes.size()) - 1;\n    }\n\n    int subtree_size(int node)\
    \ const {\n        return node == -1 ? 0 : nodes[node].count;\n    }\n\n    int\
    \ find_node(UInt value) const {\n        int node = 0;\n        value ^= lazy_xor;\n\
    \        for (int position = BitWidth - 1; position >= 0; --position) {\n    \
    \        node = nodes[node].child[bit(value, position)];\n            if (node\
    \ == -1 || nodes[node].count == 0) return -1;\n        }\n        return node;\n\
    \    }\n\n   public:\n    BinaryTrie() : nodes(1), lazy_xor(0) {}\n\n    BinaryTrie(std::initializer_list<UInt>\
    \ init) : BinaryTrie() {\n        for (UInt value : init) insert(value);\n   \
    \ }\n\n    template <typename Iterator>\n    BinaryTrie(Iterator first, Iterator\
    \ last) : BinaryTrie() {\n        while (first != last) {\n            insert(*first);\n\
    \            ++first;\n        }\n    }\n\n    int size() const {\n        return\
    \ nodes[0].count;\n    }\n\n    bool empty() const {\n        return size() ==\
    \ 0;\n    }\n\n    void clear() {\n        nodes.clear();\n        nodes.emplace_back();\n\
    \        lazy_xor = 0;\n    }\n\n    void insert(UInt value, int multiplicity\
    \ = 1) {\n        assert(valid_value(value));\n        assert(multiplicity > 0);\n\
    \        value ^= lazy_xor;\n        int node = 0;\n        nodes[node].count\
    \ += multiplicity;\n        for (int position = BitWidth - 1; position >= 0; --position)\
    \ {\n            const int direction = bit(value, position);\n            if (nodes[node].child[direction]\
    \ == -1) {\n                const int child = new_node();\n                nodes[node].child[direction]\
    \ = child;\n            }\n            node = nodes[node].child[direction];\n\
    \            nodes[node].count += multiplicity;\n        }\n    }\n\n    int count(UInt\
    \ value) const {\n        assert(valid_value(value));\n        const int node\
    \ = find_node(value);\n        return node == -1 ? 0 : nodes[node].count;\n  \
    \  }\n\n    bool contains(UInt value) const {\n        return count(value) > 0;\n\
    \    }\n\n    bool erase_one(UInt value) {\n        assert(valid_value(value));\n\
    \        if (!contains(value)) return false;\n        value ^= lazy_xor;\n   \
    \     int node = 0;\n        --nodes[node].count;\n        for (int position =\
    \ BitWidth - 1; position >= 0; --position) {\n            node = nodes[node].child[bit(value,\
    \ position)];\n            --nodes[node].count;\n        }\n        return true;\n\
    \    }\n\n    bool erase(UInt value) {\n        return erase_one(value);\n   \
    \ }\n\n    int erase_all(UInt value) {\n        assert(valid_value(value));\n\
    \        const int multiplicity = count(value);\n        if (multiplicity == 0)\
    \ return 0;\n        value ^= lazy_xor;\n        int node = 0;\n        nodes[node].count\
    \ -= multiplicity;\n        for (int position = BitWidth - 1; position >= 0; --position)\
    \ {\n            node = nodes[node].child[bit(value, position)];\n           \
    \ nodes[node].count -= multiplicity;\n        }\n        return multiplicity;\n\
    \    }\n\n    void xor_all(UInt value) {\n        assert(valid_value(value));\n\
    \        lazy_xor ^= value;\n    }\n\n    UInt kth_xor(int k, UInt value) const\
    \ {\n        assert(0 <= k && k < size());\n        assert(valid_value(value));\n\
    \        const UInt effective_xor = lazy_xor ^ value;\n        UInt result = 0;\n\
    \        int node = 0;\n        for (int position = BitWidth - 1; position >=\
    \ 0; --position) {\n            const int preferred = bit(effective_xor, position);\n\
    \            const int preferred_size = subtree_size(nodes[node].child[preferred]);\n\
    \            if (k < preferred_size) {\n                node = nodes[node].child[preferred];\n\
    \            } else {\n                k -= preferred_size;\n                node\
    \ = nodes[node].child[preferred ^ 1];\n                result |= UInt(1) << position;\n\
    \            }\n        }\n        return result;\n    }\n\n    UInt kth(int k)\
    \ const {\n        return kth_xor(k, 0);\n    }\n\n    UInt min() const {\n  \
    \      return kth(0);\n    }\n\n    UInt max() const {\n        return kth(size()\
    \ - 1);\n    }\n\n    UInt min_xor(UInt value) const {\n        return kth_xor(0,\
    \ value);\n    }\n\n    UInt max_xor(UInt value) const {\n        return kth_xor(size()\
    \ - 1, value);\n    }\n\n    int count_less_xor(UInt value, UInt upper) const\
    \ {\n        assert(valid_value(value));\n        if (!valid_value(upper)) return\
    \ size();\n        const UInt effective_xor = lazy_xor ^ value;\n        int result\
    \ = 0;\n        int node = 0;\n        for (int position = BitWidth - 1; position\
    \ >= 0 && node != -1; --position) {\n            const int zero = bit(effective_xor,\
    \ position);\n            if (bit(upper, position) == 1) {\n                result\
    \ += subtree_size(nodes[node].child[zero]);\n                node = nodes[node].child[zero\
    \ ^ 1];\n            } else {\n                node = nodes[node].child[zero];\n\
    \            }\n        }\n        return result;\n    }\n\n    int count_xor_less(UInt\
    \ value, UInt upper) const {\n        return count_less_xor(value, upper);\n \
    \   }\n\n    int count_xor_less_equal(UInt value, UInt upper) const {\n      \
    \  assert(valid_value(value));\n        assert(valid_value(upper));\n        if\
    \ (upper == value_mask()) return size();\n        return count_xor_less(value,\
    \ upper + UInt(1));\n    }\n\n    int count_xor_greater(UInt value, UInt lower)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        return size() - count_xor_less_equal(value, lower);\n    }\n\n    int\
    \ count_xor_greater_equal(UInt value, UInt lower) const {\n        assert(valid_value(value));\n\
    \        assert(valid_value(lower));\n        return size() - count_xor_less(value,\
    \ lower);\n    }\n\n    int count_xor_range(UInt value, UInt lower, UInt upper)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        assert(lower <= upper);\n        return count_xor_less(value, upper)\
    \ -\n               count_xor_less(value, lower);\n    }\n\n    int order_of_key(UInt\
    \ value) const {\n        return count_less_xor(0, value);\n    }\n\n    int count_less(UInt\
    \ value) const {\n        return order_of_key(value);\n    }\n\n    int count_less_equal(UInt\
    \ value) const {\n        assert(valid_value(value));\n        if (value == value_mask())\
    \ return size();\n        return count_less(value + UInt(1));\n    }\n\n    int\
    \ count_greater(UInt value) const {\n        return size() - count_less_equal(value);\n\
    \    }\n\n    int count_greater_equal(UInt value) const {\n        return size()\
    \ - count_less(value);\n    }\n\n    std::vector<UInt> to_vector() const {\n \
    \       std::vector<UInt> result;\n        result.reserve(size());\n        for\
    \ (int k = 0; k < size(); ++k) {\n            result.push_back(kth(k));\n    \
    \    }\n        return result;\n    }\n};\n\n}  // namespace ds\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/ds/ordered_set/binary_trie.test.cpp\"\n\n#include\
    \ <algorithm>\n#line 8 \"verify/ds/ordered_set/binary_trie.test.cpp\"\n#include\
    \ <iostream>\n#include <iterator>\n#include <set>\n#include <utility>\n#line 13\
    \ \"verify/ds/ordered_set/binary_trie.test.cpp\"\n\nvoid unit_test() {\n    using\
    \ Trie = m1une::ds::BinaryTrie<std::uint32_t, 10>;\n\n    Trie basic;\n    basic.insert(5,\
    \ 3);\n    basic.insert(9);\n    assert(basic.count(5) == 3);\n    assert(basic.kth_xor(0,\
    \ 7) == (5U ^ 7U));\n    assert(basic.erase_one(5));\n    assert(basic.erase_all(5)\
    \ == 2);\n    basic.xor_all(6);\n    assert(basic.contains(9U ^ 6U));\n    basic.clear();\n\
    \    basic.insert(1023);\n    assert(basic.count_less_equal(1023) == 1);\n   \
    \ assert(basic.count_less_xor(0, 1024) == 1);\n\n    Trie trie;\n    std::multiset<std::uint32_t>\
    \ expected;\n    std::uint64_t seed = 123456789;\n\n    for (int query = 0; query\
    \ < 10000; ++query) {\n        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n\
    \        const std::uint32_t value = std::uint32_t(seed >> 32) & 1023U;\n    \
    \    const int type = int(seed % 7);\n\n        if (type <= 1) {\n           \
    \ trie.insert(value);\n            expected.insert(value);\n        } else if\
    \ (type == 2) {\n            const bool erased = trie.erase_one(value);\n    \
    \        auto it = expected.find(value);\n            assert(erased == (it !=\
    \ expected.end()));\n            if (it != expected.end()) expected.erase(it);\n\
    \        } else if (type == 3) {\n            const int erased = trie.erase_all(value);\n\
    \            assert(erased == int(expected.count(value)));\n            expected.erase(value);\n\
    \        } else if (type == 4) {\n            trie.xor_all(value);\n         \
    \   std::multiset<std::uint32_t> transformed;\n            for (std::uint32_t\
    \ element : expected) {\n                transformed.insert(element ^ value);\n\
    \            }\n            expected = std::move(transformed);\n        } else\
    \ if (type == 5) {\n            assert(trie.count(value) == int(expected.count(value)));\n\
    \            assert(trie.count_less(value) ==\n                   int(std::distance(expected.begin(),\
    \ expected.lower_bound(value))));\n            assert(trie.count_less_equal(value)\
    \ ==\n                   int(std::distance(expected.begin(), expected.upper_bound(value))));\n\
    \        } else if (!expected.empty()) {\n            std::vector<std::uint32_t>\
    \ xor_values;\n            xor_values.reserve(expected.size());\n            for\
    \ (std::uint32_t element : expected) {\n                xor_values.push_back(element\
    \ ^ value);\n            }\n            std::sort(xor_values.begin(), xor_values.end());\n\
    \            assert(trie.min_xor(value) == xor_values.front());\n            assert(trie.max_xor(value)\
    \ == xor_values.back());\n            assert(trie.count_less_xor(value, 512) ==\n\
    \                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_less(value,\
    \ 512) ==\n                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_less_equal(value,\
    \ 512) ==\n                   int(std::upper_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_greater(value,\
    \ 512) ==\n                   int(xor_values.end() -\n                       std::upper_bound(xor_values.begin(),\
    \ xor_values.end(), 512)));\n            assert(trie.count_xor_greater_equal(value,\
    \ 512) ==\n                   int(xor_values.end() -\n                       std::lower_bound(xor_values.begin(),\
    \ xor_values.end(), 512)));\n            assert(trie.count_xor_range(value, 200,\
    \ 800) ==\n                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 800) -\n                       std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 200)));\n        }\n\n        assert(trie.size() == int(expected.size()));\n\
    \        assert(trie.empty() == expected.empty());\n        if (!expected.empty())\
    \ {\n            assert(trie.min() == *expected.begin());\n            assert(trie.max()\
    \ == *expected.rbegin());\n            const int k = int(seed % expected.size());\n\
    \            auto it = expected.begin();\n            std::advance(it, k);\n \
    \           assert(trie.kth(k) == *it);\n        }\n    }\n\n    assert(trie.to_vector()\
    \ ==\n           std::vector<std::uint32_t>(expected.begin(), expected.end()));\n\
    \    trie.clear();\n    assert(trie.empty());\n}\n\nint main() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    unit_test();\n\n    int query_count;\n    std::cin\
    \ >> query_count;\n\n    m1une::ds::BinaryTrie<std::uint32_t, 30> trie;\n    while\
    \ (query_count--) {\n        int type;\n        std::uint32_t value;\n       \
    \ std::cin >> type >> value;\n\n        if (type == 0) {\n            if (!trie.contains(value))\
    \ trie.insert(value);\n        } else if (type == 1) {\n            trie.erase(value);\n\
    \        } else {\n            std::cout << trie.min_xor(value) << '\\n';\n  \
    \      }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/set_xor_min\"\n\n#include\
    \ \"../../../ds/ordered_set/binary_trie.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <iterator>\n#include\
    \ <set>\n#include <utility>\n#include <vector>\n\nvoid unit_test() {\n    using\
    \ Trie = m1une::ds::BinaryTrie<std::uint32_t, 10>;\n\n    Trie basic;\n    basic.insert(5,\
    \ 3);\n    basic.insert(9);\n    assert(basic.count(5) == 3);\n    assert(basic.kth_xor(0,\
    \ 7) == (5U ^ 7U));\n    assert(basic.erase_one(5));\n    assert(basic.erase_all(5)\
    \ == 2);\n    basic.xor_all(6);\n    assert(basic.contains(9U ^ 6U));\n    basic.clear();\n\
    \    basic.insert(1023);\n    assert(basic.count_less_equal(1023) == 1);\n   \
    \ assert(basic.count_less_xor(0, 1024) == 1);\n\n    Trie trie;\n    std::multiset<std::uint32_t>\
    \ expected;\n    std::uint64_t seed = 123456789;\n\n    for (int query = 0; query\
    \ < 10000; ++query) {\n        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n\
    \        const std::uint32_t value = std::uint32_t(seed >> 32) & 1023U;\n    \
    \    const int type = int(seed % 7);\n\n        if (type <= 1) {\n           \
    \ trie.insert(value);\n            expected.insert(value);\n        } else if\
    \ (type == 2) {\n            const bool erased = trie.erase_one(value);\n    \
    \        auto it = expected.find(value);\n            assert(erased == (it !=\
    \ expected.end()));\n            if (it != expected.end()) expected.erase(it);\n\
    \        } else if (type == 3) {\n            const int erased = trie.erase_all(value);\n\
    \            assert(erased == int(expected.count(value)));\n            expected.erase(value);\n\
    \        } else if (type == 4) {\n            trie.xor_all(value);\n         \
    \   std::multiset<std::uint32_t> transformed;\n            for (std::uint32_t\
    \ element : expected) {\n                transformed.insert(element ^ value);\n\
    \            }\n            expected = std::move(transformed);\n        } else\
    \ if (type == 5) {\n            assert(trie.count(value) == int(expected.count(value)));\n\
    \            assert(trie.count_less(value) ==\n                   int(std::distance(expected.begin(),\
    \ expected.lower_bound(value))));\n            assert(trie.count_less_equal(value)\
    \ ==\n                   int(std::distance(expected.begin(), expected.upper_bound(value))));\n\
    \        } else if (!expected.empty()) {\n            std::vector<std::uint32_t>\
    \ xor_values;\n            xor_values.reserve(expected.size());\n            for\
    \ (std::uint32_t element : expected) {\n                xor_values.push_back(element\
    \ ^ value);\n            }\n            std::sort(xor_values.begin(), xor_values.end());\n\
    \            assert(trie.min_xor(value) == xor_values.front());\n            assert(trie.max_xor(value)\
    \ == xor_values.back());\n            assert(trie.count_less_xor(value, 512) ==\n\
    \                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_less(value,\
    \ 512) ==\n                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_less_equal(value,\
    \ 512) ==\n                   int(std::upper_bound(xor_values.begin(), xor_values.end(),\
    \ 512) -\n                       xor_values.begin()));\n            assert(trie.count_xor_greater(value,\
    \ 512) ==\n                   int(xor_values.end() -\n                       std::upper_bound(xor_values.begin(),\
    \ xor_values.end(), 512)));\n            assert(trie.count_xor_greater_equal(value,\
    \ 512) ==\n                   int(xor_values.end() -\n                       std::lower_bound(xor_values.begin(),\
    \ xor_values.end(), 512)));\n            assert(trie.count_xor_range(value, 200,\
    \ 800) ==\n                   int(std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 800) -\n                       std::lower_bound(xor_values.begin(), xor_values.end(),\
    \ 200)));\n        }\n\n        assert(trie.size() == int(expected.size()));\n\
    \        assert(trie.empty() == expected.empty());\n        if (!expected.empty())\
    \ {\n            assert(trie.min() == *expected.begin());\n            assert(trie.max()\
    \ == *expected.rbegin());\n            const int k = int(seed % expected.size());\n\
    \            auto it = expected.begin();\n            std::advance(it, k);\n \
    \           assert(trie.kth(k) == *it);\n        }\n    }\n\n    assert(trie.to_vector()\
    \ ==\n           std::vector<std::uint32_t>(expected.begin(), expected.end()));\n\
    \    trie.clear();\n    assert(trie.empty());\n}\n\nint main() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    unit_test();\n\n    int query_count;\n    std::cin\
    \ >> query_count;\n\n    m1une::ds::BinaryTrie<std::uint32_t, 30> trie;\n    while\
    \ (query_count--) {\n        int type;\n        std::uint32_t value;\n       \
    \ std::cin >> type >> value;\n\n        if (type == 0) {\n            if (!trie.contains(value))\
    \ trie.insert(value);\n        } else if (type == 1) {\n            trie.erase(value);\n\
    \        } else {\n            std::cout << trie.min_xor(value) << '\\n';\n  \
    \      }\n    }\n}\n"
  dependsOn:
  - ds/ordered_set/binary_trie.hpp
  isVerificationFile: true
  path: verify/ds/ordered_set/binary_trie.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/ordered_set/binary_trie.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/ordered_set/binary_trie.test.cpp
- /verify/verify/ds/ordered_set/binary_trie.test.cpp.html
title: verify/ds/ordered_set/binary_trie.test.cpp
---
