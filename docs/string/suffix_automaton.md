---
title: Suffix Automaton
documentation_of: ../../string/suffix_automaton.hpp
---

## Overview

`SuffixAutomaton` incrementally builds the minimal deterministic automaton whose
paths from the root spell every substring of the current text.

Appending one symbol takes amortized `O(1)` time. A text of length `N` creates
at most `2N - 1` states for nonempty text.

The implementation uses fixed transition arrays and a contiguous alphabet,
matching `Trie`, `AhoCorasick`, and `Eertree`. The default alphabet is lowercase
English letters.

## Template Parameters

- `AlphabetSize`: number of symbols, default `26`.
- `FirstCharacter`: character code mapped to transition zero, default `'a'`.

For decimal strings, use `SuffixAutomaton<10, '0'>`.

## State Fields

| Field | Meaning |
| --- | --- |
| `next[c]` | Transition by alphabet index `c`, or `null_state`. |
| `suffix_link` | State representing the largest proper suffix in a different end-position class. |
| `length` | Maximum length represented by this state. |
| `first_end` | Exclusive end of a representative occurrence of the maximum-length string. |
| `direct_occurrences` | Number of prefixes ending directly at this non-clone state. |
| `clone` | Whether this state was created by splitting another state. |

For non-root state `v`, it represents substring lengths
`state(suffix_link[v]).length + 1` through `state(v).length`.

## Methods

Let `S` be the number of states and `L` a query-sequence length.

| Method | Description | Complexity |
| --- | --- | --- |
| `SuffixAutomaton()` | Creates the root state for an empty text. | `O(1)` |
| `SuffixAutomaton(sequence)` | Builds from a sequence. | Amortized `O(N)` |
| `int state_count() const`, `int size() const` | Returns `S`, including the root. | `O(1)` |
| `bool empty() const` | Returns whether the text is empty. | `O(1)` |
| `int text_length() const` | Returns the text length. | `O(1)` |
| `state_id root() const` | Returns state zero. | `O(1)` |
| `state_id last() const` | Returns the state of the complete text. | `O(1)` |
| `const State& state(id) const` | Returns state metadata. | `O(1)` |
| `const vector<State>& states() const` | Returns all states. | `O(1)` |
| `int minimum_length(id) const` | Returns the minimum substring length represented by the state. | `O(1)` |
| `state_id transition(id, symbol) const` | Returns one transition, or `null_state`. | `O(1)` |
| `void reserve(capacity)` | Reserves enough state storage for the text capacity. | `O(S)` if reallocated |
| `void clear()` | Resets to the root state. | `O(S)` |
| `state_id add(symbol)` | Appends one symbol and returns the new last state. | Amortized `O(1)` |
| `void build(sequence)` | Appends a sequence. | Amortized `O(N)` |
| `state_id find(sequence) const` | Returns the reached state, or `null_state`. | `O(L)` |
| `bool contains(sequence) const` | Tests whether the sequence is a substring. | `O(L)` |
| `vector<state_id> length_order() const` | Returns states in nondecreasing maximum length. | `O(S + N)` |
| `vector<long long> occurrence_counts() const` | Returns end-position-class occurrence counts. | `O(S + N)` |
| `vector<bool> terminal_states() const` | Marks states representing suffixes of the complete text. | `O(N)` |
| `long long distinct_substring_count() const` | Counts distinct nonempty substrings. | `O(S)` |
| `pair<int, int> longest_representative(id) const` | Returns a representative interval for the state's maximum-length string. | `O(1)` |
| `pair<int, int> representative_occurrence(sequence) const` | Returns a representative interval, or `{-1, -1}`. | `O(L)` |
| `pair<int, int> longest_common_substring(sequence) const` | Returns a longest matching half-open interval in the query sequence. | `O(L)` |

`occurrence_counts()[v]` is the occurrence count shared by every substring
whose path ends at state `v`. The root count is the text length.

`terminal_states()` includes the root, representing the empty suffix.

Node handles remain valid until `clear()`. References returned by `state()` may
be invalidated by `add`, `build`, `reserve`, or `clear`.

## Example

```cpp
#include "string/suffix_automaton.hpp"
#include <iostream>
#include <string>

int main() {
    m1une::string::SuffixAutomaton<> automaton(std::string("ababa"));

    std::cout << automaton.contains(std::string("bab")) << '\n';  // 1
    std::cout << automaton.distinct_substring_count() << '\n';    // 9

    std::vector<long long> count = automaton.occurrence_counts();
    int state = automaton.find(std::string("aba"));
    std::cout << count[state] << '\n';  // 2
}
```
