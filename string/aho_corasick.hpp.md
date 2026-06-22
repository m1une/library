---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/aho_corasick.test.cpp
    title: verify/string/aho_corasick.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/aho_corasick.hpp\"\n\n\n\n#include <array>\n#include\
    \ <cassert>\n#include <cstddef>\n#include <limits>\n#include <queue>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace string {\n\n// Aho-Corasick automaton\
    \ for a contiguous character alphabet.\ntemplate <int AlphabetSize = 26, int FirstCharacter\
    \ = 'a'>\nstruct AhoCorasick {\n    static_assert(0 < AlphabetSize);\n\n    using\
    \ node_id = int;\n    static constexpr node_id null_node = -1;\n\n    struct Node\
    \ {\n        // Completed automaton transitions. Valid after build().\n      \
    \  std::array<node_id, AlphabetSize> next;\n        node_id failure;\n       \
    \ node_id output_link;\n        node_id parent;\n        int parent_symbol;\n\
    \        int depth;\n        std::vector<node_id> children;\n        std::vector<node_id>\
    \ failure_children;\n        std::vector<int> pattern_ids;\n\n        Node(\n\
    \            node_id parent_value = null_node,\n            int parent_symbol_value\
    \ = -1,\n            int depth_value = 0\n        ) : failure(0),\n          \
    \  output_link(null_node),\n            parent(parent_value),\n            parent_symbol(parent_symbol_value),\n\
    \            depth(depth_value) {\n            next.fill(null_node);\n       \
    \ }\n    };\n\n   private:\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _pattern_length;\n    std::vector<node_id> _pattern_node;\n    std::vector<node_id>\
    \ _bfs_order;\n    bool _built;\n\n    template <class Symbol>\n    static int\
    \ symbol_index(const Symbol& symbol) {\n        int index = int(symbol) - FirstCharacter;\n\
    \        assert(0 <= index && index < AlphabetSize);\n        return index;\n\
    \    }\n\n    node_id new_node(node_id parent, int parent_symbol) {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        assert(_nodes[parent].depth\
    \ < std::numeric_limits<int>::max());\n        _nodes.emplace_back(parent, parent_symbol,\
    \ _nodes[parent].depth + 1);\n        return int(_nodes.size()) - 1;\n    }\n\n\
    \   public:\n    AhoCorasick() : _nodes(1), _built(false) {}\n\n    node_id root()\
    \ const {\n        return 0;\n    }\n\n    bool built() const {\n        return\
    \ _built;\n    }\n\n    int pattern_count() const {\n        return int(_pattern_length.size());\n\
    \    }\n\n    int pattern_length(int pattern_id) const {\n        assert(0 <=\
    \ pattern_id && pattern_id < pattern_count());\n        return _pattern_length[pattern_id];\n\
    \    }\n\n    node_id pattern_node(int pattern_id) const {\n        assert(0 <=\
    \ pattern_id && pattern_id < pattern_count());\n        return _pattern_node[pattern_id];\n\
    \    }\n\n    std::size_t node_count() const {\n        return _nodes.size();\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id &&\
    \ std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n   \
    \ // Returns nodes in failure-link BFS order, beginning with the root.\n    const\
    \ std::vector<node_id>& bfs_order() const {\n        assert(_built);\n       \
    \ return _bfs_order;\n    }\n\n    void reserve(std::size_t node_capacity) {\n\
    \        assert(!_built);\n        _nodes.reserve(node_capacity);\n    }\n\n \
    \   void clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n\
    \        _pattern_length.clear();\n        _pattern_node.clear();\n        _bfs_order.clear();\n\
    \        _built = false;\n    }\n\n    // Inserts a pattern and returns its insertion-order\
    \ ID.\n    template <class Sequence>\n    int insert(const Sequence& pattern)\
    \ {\n        assert(!_built);\n        int pattern_id = pattern_count();\n   \
    \     int length = 0;\n        node_id state = root();\n        for (const auto&\
    \ symbol : pattern) {\n            assert(length < std::numeric_limits<int>::max());\n\
    \            int index = symbol_index(symbol);\n            if (_nodes[state].next[index]\
    \ == null_node) {\n                node_id child = new_node(state, index);\n \
    \               _nodes[state].next[index] = child;\n                _nodes[state].children.push_back(child);\n\
    \            }\n            state = _nodes[state].next[index];\n            length++;\n\
    \        }\n        _nodes[state].pattern_ids.push_back(pattern_id);\n       \
    \ _pattern_length.push_back(length);\n        _pattern_node.push_back(state);\n\
    \        return pattern_id;\n    }\n\n    // Builds failure links and completes\
    \ every automaton transition.\n    void build() {\n        assert(!_built);\n\
    \        std::queue<node_id> queue;\n        _bfs_order.clear();\n        _bfs_order.reserve(_nodes.size());\n\
    \        _bfs_order.push_back(root());\n\n        for (int symbol = 0; symbol\
    \ < AlphabetSize; ++symbol) {\n            node_id child = _nodes[root()].next[symbol];\n\
    \            if (child == null_node) {\n                _nodes[root()].next[symbol]\
    \ = root();\n            } else {\n                _nodes[root()].next[symbol]\
    \ = child;\n                _nodes[child].failure = root();\n                _nodes[child].output_link\
    \ =\n                    _nodes[root()].pattern_ids.empty() ? null_node : root();\n\
    \                _nodes[root()].failure_children.push_back(child);\n         \
    \       queue.push(child);\n            }\n        }\n\n        while (!queue.empty())\
    \ {\n            node_id state = queue.front();\n            queue.pop();\n  \
    \          _bfs_order.push_back(state);\n\n            for (int symbol = 0; symbol\
    \ < AlphabetSize; ++symbol) {\n                node_id child = _nodes[state].next[symbol];\n\
    \                if (child == null_node) {\n                    _nodes[state].next[symbol]\
    \ =\n                        _nodes[_nodes[state].failure].next[symbol];\n   \
    \                 continue;\n                }\n\n                _nodes[state].next[symbol]\
    \ = child;\n                node_id failure =\n                    _nodes[_nodes[state].failure].next[symbol];\n\
    \                _nodes[child].failure = failure;\n                _nodes[child].output_link\
    \ =\n                    _nodes[failure].pattern_ids.empty()\n               \
    \         ? _nodes[failure].output_link\n                        : failure;\n\
    \                _nodes[failure].failure_children.push_back(child);\n        \
    \        queue.push(child);\n            }\n        }\n        _built = true;\n\
    \    }\n\n    template <class Symbol>\n    node_id transition(node_id state, const\
    \ Symbol& symbol) const {\n        assert(_built);\n        assert(0 <= state\
    \ && std::size_t(state) < _nodes.size());\n        return _nodes[state].next[symbol_index(symbol)];\n\
    \    }\n\n    // Calls callback(pattern_id) for every pattern ending at `state`.\n\
    \    template <class Callback>\n    void for_each_output(node_id state, Callback\
    \ callback) const {\n        assert(_built);\n        assert(0 <= state && std::size_t(state)\
    \ < _nodes.size());\n        while (state != null_node) {\n            for (int\
    \ pattern_id : _nodes[state].pattern_ids) {\n                callback(pattern_id);\n\
    \            }\n            state = _nodes[state].output_link;\n        }\n  \
    \  }\n\n    // Calls callback(end, pattern_id) for every occurrence. `end` is\
    \ the\n    // exclusive end position. Empty patterns occur at every text boundary.\n\
    \    template <class Sequence, class Callback>\n    void match(const Sequence&\
    \ text, Callback callback) const {\n        assert(_built);\n        node_id state\
    \ = root();\n        for_each_output(state, [&callback](int pattern_id) {\n  \
    \          callback(0, pattern_id);\n        });\n\n        int end = 0;\n   \
    \     for (const auto& symbol : text) {\n            state = transition(state,\
    \ symbol);\n            end++;\n            for_each_output(state, [&callback,\
    \ end](int pattern_id) {\n                callback(end, pattern_id);\n       \
    \     });\n        }\n    }\n\n    // Counts occurrences of every inserted pattern\
    \ in linear time.\n    template <class Sequence>\n    std::vector<long long> count_occurrences(const\
    \ Sequence& text) const {\n        assert(_built);\n        std::vector<long long>\
    \ visits(_nodes.size(), 0);\n        node_id state = root();\n        visits[root()]++;\n\
    \        for (const auto& symbol : text) {\n            state = transition(state,\
    \ symbol);\n            visits[state]++;\n        }\n\n        for (std::size_t\
    \ index = _bfs_order.size(); index-- > 1;) {\n            node_id current = _bfs_order[index];\n\
    \            visits[_nodes[current].failure] += visits[current];\n        }\n\n\
    \        std::vector<long long> result(pattern_count(), 0);\n        for (node_id\
    \ current : _bfs_order) {\n            for (int pattern_id : _nodes[current].pattern_ids)\
    \ {\n                result[pattern_id] = visits[current];\n            }\n  \
    \      }\n        return result;\n    }\n};\n\n}  // namespace string\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_AHO_CORASICK_HPP\n#define M1UNE_STRING_AHO_CORASICK_HPP\
    \ 1\n\n#include <array>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \n// Aho-Corasick automaton for a contiguous character alphabet.\ntemplate <int\
    \ AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct AhoCorasick {\n    static_assert(0\
    \ < AlphabetSize);\n\n    using node_id = int;\n    static constexpr node_id null_node\
    \ = -1;\n\n    struct Node {\n        // Completed automaton transitions. Valid\
    \ after build().\n        std::array<node_id, AlphabetSize> next;\n        node_id\
    \ failure;\n        node_id output_link;\n        node_id parent;\n        int\
    \ parent_symbol;\n        int depth;\n        std::vector<node_id> children;\n\
    \        std::vector<node_id> failure_children;\n        std::vector<int> pattern_ids;\n\
    \n        Node(\n            node_id parent_value = null_node,\n            int\
    \ parent_symbol_value = -1,\n            int depth_value = 0\n        ) : failure(0),\n\
    \            output_link(null_node),\n            parent(parent_value),\n    \
    \        parent_symbol(parent_symbol_value),\n            depth(depth_value) {\n\
    \            next.fill(null_node);\n        }\n    };\n\n   private:\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _pattern_length;\n    std::vector<node_id> _pattern_node;\n\
    \    std::vector<node_id> _bfs_order;\n    bool _built;\n\n    template <class\
    \ Symbol>\n    static int symbol_index(const Symbol& symbol) {\n        int index\
    \ = int(symbol) - FirstCharacter;\n        assert(0 <= index && index < AlphabetSize);\n\
    \        return index;\n    }\n\n    node_id new_node(node_id parent, int parent_symbol)\
    \ {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        assert(_nodes[parent].depth < std::numeric_limits<int>::max());\n   \
    \     _nodes.emplace_back(parent, parent_symbol, _nodes[parent].depth + 1);\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n   public:\n    AhoCorasick()\
    \ : _nodes(1), _built(false) {}\n\n    node_id root() const {\n        return\
    \ 0;\n    }\n\n    bool built() const {\n        return _built;\n    }\n\n   \
    \ int pattern_count() const {\n        return int(_pattern_length.size());\n \
    \   }\n\n    int pattern_length(int pattern_id) const {\n        assert(0 <= pattern_id\
    \ && pattern_id < pattern_count());\n        return _pattern_length[pattern_id];\n\
    \    }\n\n    node_id pattern_node(int pattern_id) const {\n        assert(0 <=\
    \ pattern_id && pattern_id < pattern_count());\n        return _pattern_node[pattern_id];\n\
    \    }\n\n    std::size_t node_count() const {\n        return _nodes.size();\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id &&\
    \ std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n   \
    \ // Returns nodes in failure-link BFS order, beginning with the root.\n    const\
    \ std::vector<node_id>& bfs_order() const {\n        assert(_built);\n       \
    \ return _bfs_order;\n    }\n\n    void reserve(std::size_t node_capacity) {\n\
    \        assert(!_built);\n        _nodes.reserve(node_capacity);\n    }\n\n \
    \   void clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n\
    \        _pattern_length.clear();\n        _pattern_node.clear();\n        _bfs_order.clear();\n\
    \        _built = false;\n    }\n\n    // Inserts a pattern and returns its insertion-order\
    \ ID.\n    template <class Sequence>\n    int insert(const Sequence& pattern)\
    \ {\n        assert(!_built);\n        int pattern_id = pattern_count();\n   \
    \     int length = 0;\n        node_id state = root();\n        for (const auto&\
    \ symbol : pattern) {\n            assert(length < std::numeric_limits<int>::max());\n\
    \            int index = symbol_index(symbol);\n            if (_nodes[state].next[index]\
    \ == null_node) {\n                node_id child = new_node(state, index);\n \
    \               _nodes[state].next[index] = child;\n                _nodes[state].children.push_back(child);\n\
    \            }\n            state = _nodes[state].next[index];\n            length++;\n\
    \        }\n        _nodes[state].pattern_ids.push_back(pattern_id);\n       \
    \ _pattern_length.push_back(length);\n        _pattern_node.push_back(state);\n\
    \        return pattern_id;\n    }\n\n    // Builds failure links and completes\
    \ every automaton transition.\n    void build() {\n        assert(!_built);\n\
    \        std::queue<node_id> queue;\n        _bfs_order.clear();\n        _bfs_order.reserve(_nodes.size());\n\
    \        _bfs_order.push_back(root());\n\n        for (int symbol = 0; symbol\
    \ < AlphabetSize; ++symbol) {\n            node_id child = _nodes[root()].next[symbol];\n\
    \            if (child == null_node) {\n                _nodes[root()].next[symbol]\
    \ = root();\n            } else {\n                _nodes[root()].next[symbol]\
    \ = child;\n                _nodes[child].failure = root();\n                _nodes[child].output_link\
    \ =\n                    _nodes[root()].pattern_ids.empty() ? null_node : root();\n\
    \                _nodes[root()].failure_children.push_back(child);\n         \
    \       queue.push(child);\n            }\n        }\n\n        while (!queue.empty())\
    \ {\n            node_id state = queue.front();\n            queue.pop();\n  \
    \          _bfs_order.push_back(state);\n\n            for (int symbol = 0; symbol\
    \ < AlphabetSize; ++symbol) {\n                node_id child = _nodes[state].next[symbol];\n\
    \                if (child == null_node) {\n                    _nodes[state].next[symbol]\
    \ =\n                        _nodes[_nodes[state].failure].next[symbol];\n   \
    \                 continue;\n                }\n\n                _nodes[state].next[symbol]\
    \ = child;\n                node_id failure =\n                    _nodes[_nodes[state].failure].next[symbol];\n\
    \                _nodes[child].failure = failure;\n                _nodes[child].output_link\
    \ =\n                    _nodes[failure].pattern_ids.empty()\n               \
    \         ? _nodes[failure].output_link\n                        : failure;\n\
    \                _nodes[failure].failure_children.push_back(child);\n        \
    \        queue.push(child);\n            }\n        }\n        _built = true;\n\
    \    }\n\n    template <class Symbol>\n    node_id transition(node_id state, const\
    \ Symbol& symbol) const {\n        assert(_built);\n        assert(0 <= state\
    \ && std::size_t(state) < _nodes.size());\n        return _nodes[state].next[symbol_index(symbol)];\n\
    \    }\n\n    // Calls callback(pattern_id) for every pattern ending at `state`.\n\
    \    template <class Callback>\n    void for_each_output(node_id state, Callback\
    \ callback) const {\n        assert(_built);\n        assert(0 <= state && std::size_t(state)\
    \ < _nodes.size());\n        while (state != null_node) {\n            for (int\
    \ pattern_id : _nodes[state].pattern_ids) {\n                callback(pattern_id);\n\
    \            }\n            state = _nodes[state].output_link;\n        }\n  \
    \  }\n\n    // Calls callback(end, pattern_id) for every occurrence. `end` is\
    \ the\n    // exclusive end position. Empty patterns occur at every text boundary.\n\
    \    template <class Sequence, class Callback>\n    void match(const Sequence&\
    \ text, Callback callback) const {\n        assert(_built);\n        node_id state\
    \ = root();\n        for_each_output(state, [&callback](int pattern_id) {\n  \
    \          callback(0, pattern_id);\n        });\n\n        int end = 0;\n   \
    \     for (const auto& symbol : text) {\n            state = transition(state,\
    \ symbol);\n            end++;\n            for_each_output(state, [&callback,\
    \ end](int pattern_id) {\n                callback(end, pattern_id);\n       \
    \     });\n        }\n    }\n\n    // Counts occurrences of every inserted pattern\
    \ in linear time.\n    template <class Sequence>\n    std::vector<long long> count_occurrences(const\
    \ Sequence& text) const {\n        assert(_built);\n        std::vector<long long>\
    \ visits(_nodes.size(), 0);\n        node_id state = root();\n        visits[root()]++;\n\
    \        for (const auto& symbol : text) {\n            state = transition(state,\
    \ symbol);\n            visits[state]++;\n        }\n\n        for (std::size_t\
    \ index = _bfs_order.size(); index-- > 1;) {\n            node_id current = _bfs_order[index];\n\
    \            visits[_nodes[current].failure] += visits[current];\n        }\n\n\
    \        std::vector<long long> result(pattern_count(), 0);\n        for (node_id\
    \ current : _bfs_order) {\n            for (int pattern_id : _nodes[current].pattern_ids)\
    \ {\n                result[pattern_id] = visits[current];\n            }\n  \
    \      }\n        return result;\n    }\n};\n\n}  // namespace string\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_STRING_AHO_CORASICK_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/aho_corasick.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-06-23 02:00:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
  - verify/string/aho_corasick.test.cpp
documentation_of: string/aho_corasick.hpp
layout: document
title: Aho-Corasick
---

## Overview

`AhoCorasick` finds occurrences of many patterns in one text. It stores the
patterns in a trie and adds failure links, allowing the text to be scanned in
linear time plus the number of reported matches.

The alphabet must be a contiguous range of character codes. The default
`AhoCorasick<>` accepts lowercase English letters. For decimal digits, use
`AhoCorasick<10, '0'>`.

## Construction

Insert every pattern, then call `build()`:

```cpp
m1une::string::AhoCorasick<> automaton;
int first_id = automaton.insert(std::string("he"));
int second_id = automaton.insert(std::string("she"));
automaton.build();
```

Pattern IDs are assigned in insertion order, starting from zero. Duplicate and
empty patterns are supported and receive separate IDs.

No pattern may be inserted after `build()`. Call `clear()` to reuse the object
with a new pattern set.

## Methods

Let $K$ be the automaton node count, $P$ the pattern count, $\sigma$ the
alphabet size, $N$ the text length, and $Z$ the number of reported
occurrences.

| Method | Description | Complexity |
| --- | --- | --- |
| `insert(pattern)` | Inserts a pattern and returns its ID. | $O(|pattern|)$ |
| `build()` | Builds failure links and all transitions. | $O(K\sigma)$ |
| `built()` | Returns whether `build()` has been called. | $O(1)$ |
| `pattern_count()` | Returns the number of inserted patterns. | $O(1)$ |
| `pattern_length(id)` | Returns a pattern's length. | $O(1)$ |
| `pattern_node(id)` | Returns the terminal node of a pattern. | $O(1)$ |
| `node_count()` | Returns the number of trie nodes. | $O(1)$ |
| `root()` | Returns the root node ID. | $O(1)$ |
| `node(id)` | Returns a read-only node view. | $O(1)$ |
| `nodes()` | Returns a read-only view of the complete node array. | $O(1)$ |
| `bfs_order()` | Returns node IDs in failure-link BFS order. | $O(1)$ |
| `transition(state, symbol)` | Takes one automaton transition. | $O(1)$ |
| `for_each_output(state, callback)` | Reports patterns ending at a state. | $O(1 + output)$ |
| `match(text, callback)` | Reports every occurrence in the text. | $O(N+Z)$ |
| `count_occurrences(text)` | Returns an occurrence count for each pattern ID. | $O(N+K+P)$ |
| `reserve(node_capacity)` | Reserves trie-node storage before building. | $O(K)$ |
| `clear()` | Removes all patterns and returns to the insertion phase. | $O(K)$ |

`match` calls `callback(end, pattern_id)`, where `end` is the exclusive end
position. The occurrence starts at
`end - automaton.pattern_length(pattern_id)`.

An empty pattern occurs at every text boundary, including positions zero and
`text.size()`.

## Node Data

Each `Node` exposes:

* `next`: completed automaton transitions after `build()`
* `failure`: the failure-link node
* `output_link`: the nearest failure ancestor containing patterns, or
  `null_node`
* `parent`: parent in the original trie, or `null_node` for the root
* `parent_symbol`: alphabet index of the edge from `parent`, or `-1` for the
  root
* `depth`: trie depth, equal to the represented prefix length
* `children`: children in the original trie
* `failure_children`: children in the failure-link tree
* `pattern_ids`: patterns ending exactly at this trie node

`nodes()` and `bfs_order()` make graph algorithms convenient without repeated
accessor calls. For example, iterate `bfs_order()` in reverse to aggregate
values from a node into its failure parent, or traverse `failure_children` to
run a tree DP.

`children`, `parent`, and `parent_symbol` describe the sparse trie graph, while
`next` describes the complete deterministic automaton graph. This distinction
remains available after `build()` without storing two full transition tables
per node.

Node IDs remain valid until `clear()`. References and iterators into `nodes()`
may be invalidated by `insert()` or `reserve()` before construction finishes,
so retain node IDs across insertions.

## Example

```cpp
#include "string/aho_corasick.hpp"

#include <iostream>
#include <string>

int main() {
    m1une::string::AhoCorasick<> automaton;
    automaton.insert(std::string("aba"));
    automaton.insert(std::string("ba"));
    automaton.build();

    automaton.match(std::string("ababa"), [](int end, int pattern_id) {
        std::cout << pattern_id << ' ' << end << "\n";
    });
}
```
