---
title: Aho-Corasick
documentation_of: ../../string/aho_corasick.hpp
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
