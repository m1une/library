---
title: Eertree
documentation_of: ../../string/eertree.hpp
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
