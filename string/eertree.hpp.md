---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/eertree.test.cpp
    title: verify/string/eertree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/eertree.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace string {\n\ntemplate <int AlphabetSize = 26, int\
    \ FirstCharacter = 'a'>\nstruct Eertree {\n    static_assert(0 < AlphabetSize);\n\
    \n    using node_id = int;\n    static constexpr node_id even_root = 0;\n    static\
    \ constexpr node_id odd_root = 1;\n    static constexpr node_id null_node = -1;\n\
    \n    struct Node {\n        std::array<node_id, AlphabetSize> next;\n       \
    \ node_id suffix_link;\n        node_id series_link;\n        int length;\n  \
    \      int diff;\n        int suffix_count;\n        int first_end;\n        long\
    \ long suffix_occurrences;\n\n        Node(int length_value = 0, node_id suffix_link_value\
    \ = even_root, node_id series_link_value = even_root)\n            : suffix_link(suffix_link_value),\n\
    \              series_link(series_link_value),\n              length(length_value),\n\
    \              diff(0),\n              suffix_count(0),\n              first_end(0),\n\
    \              suffix_occurrences(0) {\n            next.fill(null_node);\n  \
    \      }\n    };\n\n   private:\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _text;\n    std::vector<node_id> _longest_suffix;\n    node_id _last;\n\n  \
    \  template <class Symbol>\n    static int symbol_index(const Symbol& symbol)\
    \ {\n        int index = int(symbol) - FirstCharacter;\n        assert(0 <= index\
    \ && index < AlphabetSize);\n        return index;\n    }\n\n    node_id find_extendable(node_id\
    \ node, int position, int symbol) const {\n        while (true) {\n          \
    \  int length = _nodes[node].length;\n            int left = position - length\
    \ - 1;\n            if (0 <= left && _text[left] == symbol) return node;\n   \
    \         node = _nodes[node].suffix_link;\n        }\n    }\n\n    node_id new_node(int\
    \ length) {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(length);\n        return int(_nodes.size()) - 1;\n\
    \    }\n\n   public:\n    Eertree() {\n        clear();\n    }\n\n    template\
    \ <class Sequence>\n    explicit Eertree(const Sequence& sequence) {\n       \
    \ clear();\n        build(sequence);\n    }\n\n    int size() const {\n      \
    \  return int(_nodes.size()) - 2;\n    }\n\n    bool empty() const {\n       \
    \ return size() == 0;\n    }\n\n    int node_count() const {\n        return int(_nodes.size());\n\
    \    }\n\n    int text_length() const {\n        return int(_text.size());\n \
    \   }\n\n    node_id last() const {\n        return _last;\n    }\n\n    int longest_suffix_length()\
    \ const {\n        return _nodes[_last].length;\n    }\n\n    const Node& node(node_id\
    \ id) const {\n        assert(0 <= id && id < node_count());\n        return _nodes[id];\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    node_id longest_suffix_node(int prefix_length) const {\n       \
    \ assert(1 <= prefix_length && prefix_length <= text_length());\n        return\
    \ _longest_suffix[prefix_length - 1];\n    }\n\n    const std::vector<node_id>&\
    \ longest_suffix_nodes() const {\n        return _longest_suffix;\n    }\n\n \
    \   template <class Callback>\n    void for_each_suffix(node_id id, Callback callback)\
    \ const {\n        assert(0 <= id && id < node_count());\n        while (id >=\
    \ 2) {\n            callback(id);\n            id = _nodes[id].suffix_link;\n\
    \        }\n    }\n\n    template <class Callback>\n    void for_each_suffix(Callback\
    \ callback) const {\n        for_each_suffix(_last, callback);\n    }\n\n    void\
    \ reserve(std::size_t text_capacity) {\n        _text.reserve(text_capacity);\n\
    \        _longest_suffix.reserve(text_capacity);\n        _nodes.reserve(text_capacity\
    \ + 2);\n    }\n\n    void clear() {\n        _nodes.clear();\n        _nodes.emplace_back(0,\
    \ odd_root, even_root);\n        _nodes.emplace_back(-1, odd_root, odd_root);\n\
    \        _text.clear();\n        _longest_suffix.clear();\n        _last = even_root;\n\
    \    }\n\n    template <class Symbol>\n    node_id add(const Symbol& value) {\n\
    \        int symbol = symbol_index(value);\n        int position = int(_text.size());\n\
    \        _text.push_back(symbol);\n\n        node_id current = find_extendable(_last,\
    \ position, symbol);\n        node_id next = _nodes[current].next[symbol];\n \
    \       if (next == null_node) {\n            int length = _nodes[current].length\
    \ + 2;\n            next = new_node(length);\n            _nodes[current].next[symbol]\
    \ = next;\n\n            node_id suffix_link = even_root;\n            if (length\
    \ != 1) {\n                node_id candidate = find_extendable(_nodes[current].suffix_link,\
    \ position, symbol);\n                suffix_link = _nodes[candidate].next[symbol];\n\
    \                assert(suffix_link != null_node);\n            }\n\n        \
    \    Node& created = _nodes[next];\n            created.suffix_link = suffix_link;\n\
    \            created.diff = created.length - _nodes[suffix_link].length;\n   \
    \         created.series_link =\n                created.diff == _nodes[suffix_link].diff\
    \ ? _nodes[suffix_link].series_link : suffix_link;\n            created.suffix_count\
    \ = _nodes[suffix_link].suffix_count + 1;\n            created.first_end = position\
    \ + 1;\n        }\n\n        _last = next;\n        _nodes[_last].suffix_occurrences++;\n\
    \        _longest_suffix.push_back(_last);\n        return _last;\n    }\n\n \
    \   template <class Sequence>\n    void build(const Sequence& sequence) {\n  \
    \      for (const auto& symbol : sequence) add(symbol);\n    }\n\n    std::vector<long\
    \ long> occurrence_counts() const {\n        std::vector<long long> result(_nodes.size(),\
    \ 0);\n        for (node_id id = 0; id < node_count(); id++) {\n            result[id]\
    \ = _nodes[id].suffix_occurrences;\n        }\n        for (node_id id = node_count()\
    \ - 1; id >= 2; id--) {\n            result[_nodes[id].suffix_link] += result[id];\n\
    \        }\n        return result;\n    }\n\n    std::pair<int, int> first_occurrence(node_id\
    \ id) const {\n        assert(2 <= id && id < node_count());\n        int end\
    \ = _nodes[id].first_end;\n        return {end - _nodes[id].length, end};\n  \
    \  }\n};\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nusing\
    \ PalindromicTree = Eertree<AlphabetSize, FirstCharacter>;\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_EERTREE_HPP\n#define M1UNE_STRING_EERTREE_HPP 1\n\n\
    #include <array>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct Eertree {\n\
    \    static_assert(0 < AlphabetSize);\n\n    using node_id = int;\n    static\
    \ constexpr node_id even_root = 0;\n    static constexpr node_id odd_root = 1;\n\
    \    static constexpr node_id null_node = -1;\n\n    struct Node {\n        std::array<node_id,\
    \ AlphabetSize> next;\n        node_id suffix_link;\n        node_id series_link;\n\
    \        int length;\n        int diff;\n        int suffix_count;\n        int\
    \ first_end;\n        long long suffix_occurrences;\n\n        Node(int length_value\
    \ = 0, node_id suffix_link_value = even_root, node_id series_link_value = even_root)\n\
    \            : suffix_link(suffix_link_value),\n              series_link(series_link_value),\n\
    \              length(length_value),\n              diff(0),\n              suffix_count(0),\n\
    \              first_end(0),\n              suffix_occurrences(0) {\n        \
    \    next.fill(null_node);\n        }\n    };\n\n   private:\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _text;\n    std::vector<node_id> _longest_suffix;\n\
    \    node_id _last;\n\n    template <class Symbol>\n    static int symbol_index(const\
    \ Symbol& symbol) {\n        int index = int(symbol) - FirstCharacter;\n     \
    \   assert(0 <= index && index < AlphabetSize);\n        return index;\n    }\n\
    \n    node_id find_extendable(node_id node, int position, int symbol) const {\n\
    \        while (true) {\n            int length = _nodes[node].length;\n     \
    \       int left = position - length - 1;\n            if (0 <= left && _text[left]\
    \ == symbol) return node;\n            node = _nodes[node].suffix_link;\n    \
    \    }\n    }\n\n    node_id new_node(int length) {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back(length);\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n   public:\n    Eertree() {\n\
    \        clear();\n    }\n\n    template <class Sequence>\n    explicit Eertree(const\
    \ Sequence& sequence) {\n        clear();\n        build(sequence);\n    }\n\n\
    \    int size() const {\n        return int(_nodes.size()) - 2;\n    }\n\n   \
    \ bool empty() const {\n        return size() == 0;\n    }\n\n    int node_count()\
    \ const {\n        return int(_nodes.size());\n    }\n\n    int text_length()\
    \ const {\n        return int(_text.size());\n    }\n\n    node_id last() const\
    \ {\n        return _last;\n    }\n\n    int longest_suffix_length() const {\n\
    \        return _nodes[_last].length;\n    }\n\n    const Node& node(node_id id)\
    \ const {\n        assert(0 <= id && id < node_count());\n        return _nodes[id];\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    node_id longest_suffix_node(int prefix_length) const {\n       \
    \ assert(1 <= prefix_length && prefix_length <= text_length());\n        return\
    \ _longest_suffix[prefix_length - 1];\n    }\n\n    const std::vector<node_id>&\
    \ longest_suffix_nodes() const {\n        return _longest_suffix;\n    }\n\n \
    \   template <class Callback>\n    void for_each_suffix(node_id id, Callback callback)\
    \ const {\n        assert(0 <= id && id < node_count());\n        while (id >=\
    \ 2) {\n            callback(id);\n            id = _nodes[id].suffix_link;\n\
    \        }\n    }\n\n    template <class Callback>\n    void for_each_suffix(Callback\
    \ callback) const {\n        for_each_suffix(_last, callback);\n    }\n\n    void\
    \ reserve(std::size_t text_capacity) {\n        _text.reserve(text_capacity);\n\
    \        _longest_suffix.reserve(text_capacity);\n        _nodes.reserve(text_capacity\
    \ + 2);\n    }\n\n    void clear() {\n        _nodes.clear();\n        _nodes.emplace_back(0,\
    \ odd_root, even_root);\n        _nodes.emplace_back(-1, odd_root, odd_root);\n\
    \        _text.clear();\n        _longest_suffix.clear();\n        _last = even_root;\n\
    \    }\n\n    template <class Symbol>\n    node_id add(const Symbol& value) {\n\
    \        int symbol = symbol_index(value);\n        int position = int(_text.size());\n\
    \        _text.push_back(symbol);\n\n        node_id current = find_extendable(_last,\
    \ position, symbol);\n        node_id next = _nodes[current].next[symbol];\n \
    \       if (next == null_node) {\n            int length = _nodes[current].length\
    \ + 2;\n            next = new_node(length);\n            _nodes[current].next[symbol]\
    \ = next;\n\n            node_id suffix_link = even_root;\n            if (length\
    \ != 1) {\n                node_id candidate = find_extendable(_nodes[current].suffix_link,\
    \ position, symbol);\n                suffix_link = _nodes[candidate].next[symbol];\n\
    \                assert(suffix_link != null_node);\n            }\n\n        \
    \    Node& created = _nodes[next];\n            created.suffix_link = suffix_link;\n\
    \            created.diff = created.length - _nodes[suffix_link].length;\n   \
    \         created.series_link =\n                created.diff == _nodes[suffix_link].diff\
    \ ? _nodes[suffix_link].series_link : suffix_link;\n            created.suffix_count\
    \ = _nodes[suffix_link].suffix_count + 1;\n            created.first_end = position\
    \ + 1;\n        }\n\n        _last = next;\n        _nodes[_last].suffix_occurrences++;\n\
    \        _longest_suffix.push_back(_last);\n        return _last;\n    }\n\n \
    \   template <class Sequence>\n    void build(const Sequence& sequence) {\n  \
    \      for (const auto& symbol : sequence) add(symbol);\n    }\n\n    std::vector<long\
    \ long> occurrence_counts() const {\n        std::vector<long long> result(_nodes.size(),\
    \ 0);\n        for (node_id id = 0; id < node_count(); id++) {\n            result[id]\
    \ = _nodes[id].suffix_occurrences;\n        }\n        for (node_id id = node_count()\
    \ - 1; id >= 2; id--) {\n            result[_nodes[id].suffix_link] += result[id];\n\
    \        }\n        return result;\n    }\n\n    std::pair<int, int> first_occurrence(node_id\
    \ id) const {\n        assert(2 <= id && id < node_count());\n        int end\
    \ = _nodes[id].first_end;\n        return {end - _nodes[id].length, end};\n  \
    \  }\n};\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nusing\
    \ PalindromicTree = Eertree<AlphabetSize, FirstCharacter>;\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_EERTREE_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/eertree.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-06-23 11:42:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/eertree.test.cpp
documentation_of: string/eertree.hpp
layout: document
title: Eertree
---

## Overview

`Eertree` is a palindromic tree. It stores every distinct nonempty palindrome
appearing in an incrementally built sequence.

Appending one symbol takes amortized `O(1)` time. The complete structure uses
at most `N + 2` nodes for a text of length `N`: one node per distinct
palindrome, plus roots representing lengths zero and minus one.

The implementation uses fixed transition arrays and a contiguous alphabet,
matching `Trie` and `AhoCorasick`. The default alphabet is lowercase English
letters.

`PalindromicTree` is an alias for `Eertree`.

## Template Parameters

- `AlphabetSize`: number of symbols, default `26`.
- `FirstCharacter`: character code mapped to transition zero, default `'a'`.

For example, `Eertree<10, '0'>` accepts decimal digits.

## Node Fields

| Field | Meaning |
| --- | --- |
| `next[c]` | Palindrome obtained by adding symbol `c` to both ends, or `null_node`. |
| `suffix_link` | Longest proper palindromic suffix. |
| `series_link` | Nearest suffix-link ancestor having a different `diff`. |
| `length` | Palindrome length. |
| `diff` | `length - length[suffix_link]`, used in series-link DP. |
| `suffix_count` | Number of nonempty palindromic suffixes of this palindrome. |
| `first_end` | Exclusive end position of its first occurrence. |
| `suffix_occurrences` | Number of prefixes for which this node was the longest palindromic suffix. |

`occurrence_counts()` propagates `suffix_occurrences` through suffix links and
returns the total number of occurrences of each palindrome.

## Roots and Node IDs

- `even_root` has node id zero and length zero.
- `odd_root` has node id one and length minus one.
- Real palindrome nodes begin at id two.

`size()` counts only real palindrome nodes, while `node_count()` includes both
roots.

## Methods

Let `D` be the number of distinct palindromes.

| Method | Description | Complexity |
| --- | --- | --- |
| `Eertree()` | Creates an empty tree. | `O(1)` |
| `Eertree(sequence)` | Builds from a sequence. | `O(N)` amortized |
| `int size() const` | Returns `D`. | `O(1)` |
| `bool empty() const` | Returns whether `D` is zero. | `O(1)` |
| `int node_count() const` | Returns `D + 2`. | `O(1)` |
| `int text_length() const` | Returns the appended sequence length. | `O(1)` |
| `node_id last() const` | Returns the longest palindromic suffix node. | `O(1)` |
| `int longest_suffix_length() const` | Returns its length. | `O(1)` |
| `const Node& node(id) const` | Returns node metadata. | `O(1)` |
| `const vector<Node>& nodes() const` | Returns all nodes. | `O(1)` |
| `node_id longest_suffix_node(prefix_length) const` | Returns the longest suffix of that nonempty prefix. | `O(1)` |
| `const vector<node_id>& longest_suffix_nodes() const` | Returns this node for every prefix. | `O(1)` |
| `void for_each_suffix(id, callback) const` | Enumerates nonempty palindromic suffix nodes beginning at `id`. | `O(P)` |
| `void for_each_suffix(callback) const` | Enumerates suffixes of the complete current text. | `O(P)` |
| `void reserve(capacity)` | Reserves text and node storage. | `O(D)` if reallocated |
| `void clear()` | Resets to the two roots. | `O(D)` |
| `node_id add(symbol)` | Appends one symbol and returns the new longest suffix. | Amortized `O(1)` |
| `void build(sequence)` | Appends every symbol in the sequence. | Amortized `O(N)` |
| `vector<long long> occurrence_counts() const` | Returns total occurrence counts by node id. | `O(D)` |
| `pair<int, int> first_occurrence(id) const` | Returns its first half-open interval. | `O(1)` |

Here `P` is the number of reported palindromic suffixes.

Node handles remain valid until `clear()`. References returned by `node()` may
be invalidated by `add`, `build`, `reserve`, or `clear`.

## Example

```cpp
#include "string/eertree.hpp"
#include <iostream>
#include <string>

int main() {
    m1une::string::Eertree<> tree(std::string("ababa"));
    std::vector<long long> count = tree.occurrence_counts();

    std::cout << tree.size() << '\n';  // 5
    for (int id = 2; id < tree.node_count(); id++) {
        auto [left, right] = tree.first_occurrence(id);
        std::cout << tree.node(id).length << ' ' << count[id] << ' '
                  << left << ' ' << right << '\n';
    }
}
```
