---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/suffix_automaton.test.cpp
    title: verify/string/suffix_automaton.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/suffix_automaton.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <array>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct SuffixAutomaton\
    \ {\n    static_assert(0 < AlphabetSize);\n\n    using state_id = int;\n    static\
    \ constexpr state_id root_state = 0;\n    static constexpr state_id null_state\
    \ = -1;\n\n    struct State {\n        std::array<state_id, AlphabetSize> next;\n\
    \        state_id suffix_link;\n        int length;\n        int first_end;\n\
    \        int direct_occurrences;\n        bool clone;\n\n        State(int length_value\
    \ = 0)\n            : suffix_link(null_state),\n              length(length_value),\n\
    \              first_end(0),\n              direct_occurrences(0),\n         \
    \     clone(false) {\n            next.fill(null_state);\n        }\n    };\n\n\
    \   private:\n    std::vector<State> _states;\n    state_id _last;\n    int _text_length;\n\
    \n    template <class Symbol>\n    static int symbol_index(const Symbol& symbol)\
    \ {\n        int index = int(symbol) - FirstCharacter;\n        assert(0 <= index\
    \ && index < AlphabetSize);\n        return index;\n    }\n\n    state_id new_state(int\
    \ length) {\n        assert(_states.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _states.emplace_back(length);\n        return int(_states.size()) - 1;\n\
    \    }\n\n   public:\n    SuffixAutomaton() {\n        clear();\n    }\n\n   \
    \ template <class Sequence>\n    explicit SuffixAutomaton(const Sequence& sequence)\
    \ {\n        clear();\n        build(sequence);\n    }\n\n    int state_count()\
    \ const {\n        return int(_states.size());\n    }\n\n    int size() const\
    \ {\n        return state_count();\n    }\n\n    bool empty() const {\n      \
    \  return _text_length == 0;\n    }\n\n    int text_length() const {\n       \
    \ return _text_length;\n    }\n\n    state_id root() const {\n        return root_state;\n\
    \    }\n\n    state_id last() const {\n        return _last;\n    }\n\n    const\
    \ State& state(state_id id) const {\n        assert(0 <= id && id < state_count());\n\
    \        return _states[id];\n    }\n\n    const std::vector<State>& states()\
    \ const {\n        return _states;\n    }\n\n    int minimum_length(state_id id)\
    \ const {\n        assert(0 <= id && id < state_count());\n        return id ==\
    \ root_state ? 0 : _states[_states[id].suffix_link].length + 1;\n    }\n\n   \
    \ template <class Symbol>\n    state_id transition(state_id id, const Symbol&\
    \ symbol) const {\n        assert(0 <= id && id < state_count());\n        return\
    \ _states[id].next[symbol_index(symbol)];\n    }\n\n    void reserve(std::size_t\
    \ text_capacity) {\n        _states.reserve(2 * text_capacity);\n    }\n\n   \
    \ void clear() {\n        _states.clear();\n        _states.emplace_back();\n\
    \        _last = root_state;\n        _text_length = 0;\n    }\n\n    template\
    \ <class Symbol>\n    state_id add(const Symbol& value) {\n        int symbol\
    \ = symbol_index(value);\n        assert(_text_length < std::numeric_limits<int>::max());\n\
    \        _text_length++;\n\n        state_id current = new_state(_states[_last].length\
    \ + 1);\n        _states[current].first_end = _text_length;\n        _states[current].direct_occurrences\
    \ = 1;\n\n        state_id p = _last;\n        while (p != null_state && _states[p].next[symbol]\
    \ == null_state) {\n            _states[p].next[symbol] = current;\n         \
    \   p = _states[p].suffix_link;\n        }\n\n        if (p == null_state) {\n\
    \            _states[current].suffix_link = root_state;\n        } else {\n  \
    \          state_id q = _states[p].next[symbol];\n            if (_states[p].length\
    \ + 1 == _states[q].length) {\n                _states[current].suffix_link =\
    \ q;\n            } else {\n                state_id clone = new_state(_states[p].length\
    \ + 1);\n                _states[clone] = _states[q];\n                _states[clone].length\
    \ = _states[p].length + 1;\n                _states[clone].direct_occurrences\
    \ = 0;\n                _states[clone].clone = true;\n\n                while\
    \ (p != null_state && _states[p].next[symbol] == q) {\n                    _states[p].next[symbol]\
    \ = clone;\n                    p = _states[p].suffix_link;\n                }\n\
    \                _states[q].suffix_link = clone;\n                _states[current].suffix_link\
    \ = clone;\n            }\n        }\n\n        _last = current;\n        return\
    \ current;\n    }\n\n    template <class Sequence>\n    void build(const Sequence&\
    \ sequence) {\n        for (const auto& symbol : sequence) add(symbol);\n    }\n\
    \n    template <class Sequence>\n    state_id find(const Sequence& sequence) const\
    \ {\n        state_id current = root_state;\n        for (const auto& symbol :\
    \ sequence) {\n            current = transition(current, symbol);\n          \
    \  if (current == null_state) return null_state;\n        }\n        return current;\n\
    \    }\n\n    template <class Sequence>\n    bool contains(const Sequence& sequence)\
    \ const {\n        return find(sequence) != null_state;\n    }\n\n    std::vector<state_id>\
    \ length_order() const {\n        std::vector<int> count(_text_length + 1, 0);\n\
    \        for (const State& current : _states) count[current.length]++;\n     \
    \   for (int length = 1; length <= _text_length; length++) count[length] += count[length\
    \ - 1];\n\n        std::vector<state_id> order(state_count());\n        for (state_id\
    \ id = state_count() - 1; id >= 0; id--) {\n            order[--count[_states[id].length]]\
    \ = id;\n        }\n        return order;\n    }\n\n    std::vector<long long>\
    \ occurrence_counts() const {\n        std::vector<long long> result(state_count(),\
    \ 0);\n        for (state_id id = 0; id < state_count(); id++) {\n           \
    \ result[id] = _states[id].direct_occurrences;\n        }\n        std::vector<state_id>\
    \ order = length_order();\n        for (int i = int(order.size()) - 1; i > 0;\
    \ i--) {\n            state_id id = order[i];\n            result[_states[id].suffix_link]\
    \ += result[id];\n        }\n        return result;\n    }\n\n    std::vector<bool>\
    \ terminal_states() const {\n        std::vector<bool> result(state_count(), false);\n\
    \        for (state_id id = _last; id != null_state; id = _states[id].suffix_link)\
    \ {\n            result[id] = true;\n        }\n        return result;\n    }\n\
    \n    long long distinct_substring_count() const {\n        long long result =\
    \ 0;\n        for (state_id id = 1; id < state_count(); id++) {\n            result\
    \ += _states[id].length - _states[_states[id].suffix_link].length;\n        }\n\
    \        return result;\n    }\n\n    std::pair<int, int> longest_representative(state_id\
    \ id) const {\n        assert(0 <= id && id < state_count());\n        int end\
    \ = _states[id].first_end;\n        return {end - _states[id].length, end};\n\
    \    }\n\n    template <class Sequence>\n    std::pair<int, int> representative_occurrence(const\
    \ Sequence& sequence) const {\n        state_id id = root_state;\n        int\
    \ length = 0;\n        for (const auto& symbol : sequence) {\n            id =\
    \ transition(id, symbol);\n            if (id == null_state) return {-1, -1};\n\
    \            length++;\n        }\n        int end = _states[id].first_end;\n\
    \        return {end - length, end};\n    }\n\n    template <class Sequence>\n\
    \    std::pair<int, int> longest_common_substring(const Sequence& sequence) const\
    \ {\n        state_id current = root_state;\n        int current_length = 0;\n\
    \        int best_length = 0;\n        int best_end = 0;\n        int end = 0;\n\
    \n        for (const auto& value : sequence) {\n            int symbol = symbol_index(value);\n\
    \            while (current != root_state && _states[current].next[symbol] ==\
    \ null_state) {\n                current = _states[current].suffix_link;\n   \
    \             current_length = std::min(current_length, _states[current].length);\n\
    \            }\n            state_id next = _states[current].next[symbol];\n \
    \           if (next == null_state) {\n                current = root_state;\n\
    \                current_length = 0;\n            } else {\n                current\
    \ = next;\n                current_length++;\n            }\n            end++;\n\
    \            if (best_length < current_length) {\n                best_length\
    \ = current_length;\n                best_end = end;\n            }\n        }\n\
    \        return {best_end - best_length, best_end};\n    }\n};\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_SUFFIX_AUTOMATON_HPP\n#define M1UNE_STRING_SUFFIX_AUTOMATON_HPP\
    \ 1\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\n\
    struct SuffixAutomaton {\n    static_assert(0 < AlphabetSize);\n\n    using state_id\
    \ = int;\n    static constexpr state_id root_state = 0;\n    static constexpr\
    \ state_id null_state = -1;\n\n    struct State {\n        std::array<state_id,\
    \ AlphabetSize> next;\n        state_id suffix_link;\n        int length;\n  \
    \      int first_end;\n        int direct_occurrences;\n        bool clone;\n\n\
    \        State(int length_value = 0)\n            : suffix_link(null_state),\n\
    \              length(length_value),\n              first_end(0),\n          \
    \    direct_occurrences(0),\n              clone(false) {\n            next.fill(null_state);\n\
    \        }\n    };\n\n   private:\n    std::vector<State> _states;\n    state_id\
    \ _last;\n    int _text_length;\n\n    template <class Symbol>\n    static int\
    \ symbol_index(const Symbol& symbol) {\n        int index = int(symbol) - FirstCharacter;\n\
    \        assert(0 <= index && index < AlphabetSize);\n        return index;\n\
    \    }\n\n    state_id new_state(int length) {\n        assert(_states.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _states.emplace_back(length);\n\
    \        return int(_states.size()) - 1;\n    }\n\n   public:\n    SuffixAutomaton()\
    \ {\n        clear();\n    }\n\n    template <class Sequence>\n    explicit SuffixAutomaton(const\
    \ Sequence& sequence) {\n        clear();\n        build(sequence);\n    }\n\n\
    \    int state_count() const {\n        return int(_states.size());\n    }\n\n\
    \    int size() const {\n        return state_count();\n    }\n\n    bool empty()\
    \ const {\n        return _text_length == 0;\n    }\n\n    int text_length() const\
    \ {\n        return _text_length;\n    }\n\n    state_id root() const {\n    \
    \    return root_state;\n    }\n\n    state_id last() const {\n        return\
    \ _last;\n    }\n\n    const State& state(state_id id) const {\n        assert(0\
    \ <= id && id < state_count());\n        return _states[id];\n    }\n\n    const\
    \ std::vector<State>& states() const {\n        return _states;\n    }\n\n   \
    \ int minimum_length(state_id id) const {\n        assert(0 <= id && id < state_count());\n\
    \        return id == root_state ? 0 : _states[_states[id].suffix_link].length\
    \ + 1;\n    }\n\n    template <class Symbol>\n    state_id transition(state_id\
    \ id, const Symbol& symbol) const {\n        assert(0 <= id && id < state_count());\n\
    \        return _states[id].next[symbol_index(symbol)];\n    }\n\n    void reserve(std::size_t\
    \ text_capacity) {\n        _states.reserve(2 * text_capacity);\n    }\n\n   \
    \ void clear() {\n        _states.clear();\n        _states.emplace_back();\n\
    \        _last = root_state;\n        _text_length = 0;\n    }\n\n    template\
    \ <class Symbol>\n    state_id add(const Symbol& value) {\n        int symbol\
    \ = symbol_index(value);\n        assert(_text_length < std::numeric_limits<int>::max());\n\
    \        _text_length++;\n\n        state_id current = new_state(_states[_last].length\
    \ + 1);\n        _states[current].first_end = _text_length;\n        _states[current].direct_occurrences\
    \ = 1;\n\n        state_id p = _last;\n        while (p != null_state && _states[p].next[symbol]\
    \ == null_state) {\n            _states[p].next[symbol] = current;\n         \
    \   p = _states[p].suffix_link;\n        }\n\n        if (p == null_state) {\n\
    \            _states[current].suffix_link = root_state;\n        } else {\n  \
    \          state_id q = _states[p].next[symbol];\n            if (_states[p].length\
    \ + 1 == _states[q].length) {\n                _states[current].suffix_link =\
    \ q;\n            } else {\n                state_id clone = new_state(_states[p].length\
    \ + 1);\n                _states[clone] = _states[q];\n                _states[clone].length\
    \ = _states[p].length + 1;\n                _states[clone].direct_occurrences\
    \ = 0;\n                _states[clone].clone = true;\n\n                while\
    \ (p != null_state && _states[p].next[symbol] == q) {\n                    _states[p].next[symbol]\
    \ = clone;\n                    p = _states[p].suffix_link;\n                }\n\
    \                _states[q].suffix_link = clone;\n                _states[current].suffix_link\
    \ = clone;\n            }\n        }\n\n        _last = current;\n        return\
    \ current;\n    }\n\n    template <class Sequence>\n    void build(const Sequence&\
    \ sequence) {\n        for (const auto& symbol : sequence) add(symbol);\n    }\n\
    \n    template <class Sequence>\n    state_id find(const Sequence& sequence) const\
    \ {\n        state_id current = root_state;\n        for (const auto& symbol :\
    \ sequence) {\n            current = transition(current, symbol);\n          \
    \  if (current == null_state) return null_state;\n        }\n        return current;\n\
    \    }\n\n    template <class Sequence>\n    bool contains(const Sequence& sequence)\
    \ const {\n        return find(sequence) != null_state;\n    }\n\n    std::vector<state_id>\
    \ length_order() const {\n        std::vector<int> count(_text_length + 1, 0);\n\
    \        for (const State& current : _states) count[current.length]++;\n     \
    \   for (int length = 1; length <= _text_length; length++) count[length] += count[length\
    \ - 1];\n\n        std::vector<state_id> order(state_count());\n        for (state_id\
    \ id = state_count() - 1; id >= 0; id--) {\n            order[--count[_states[id].length]]\
    \ = id;\n        }\n        return order;\n    }\n\n    std::vector<long long>\
    \ occurrence_counts() const {\n        std::vector<long long> result(state_count(),\
    \ 0);\n        for (state_id id = 0; id < state_count(); id++) {\n           \
    \ result[id] = _states[id].direct_occurrences;\n        }\n        std::vector<state_id>\
    \ order = length_order();\n        for (int i = int(order.size()) - 1; i > 0;\
    \ i--) {\n            state_id id = order[i];\n            result[_states[id].suffix_link]\
    \ += result[id];\n        }\n        return result;\n    }\n\n    std::vector<bool>\
    \ terminal_states() const {\n        std::vector<bool> result(state_count(), false);\n\
    \        for (state_id id = _last; id != null_state; id = _states[id].suffix_link)\
    \ {\n            result[id] = true;\n        }\n        return result;\n    }\n\
    \n    long long distinct_substring_count() const {\n        long long result =\
    \ 0;\n        for (state_id id = 1; id < state_count(); id++) {\n            result\
    \ += _states[id].length - _states[_states[id].suffix_link].length;\n        }\n\
    \        return result;\n    }\n\n    std::pair<int, int> longest_representative(state_id\
    \ id) const {\n        assert(0 <= id && id < state_count());\n        int end\
    \ = _states[id].first_end;\n        return {end - _states[id].length, end};\n\
    \    }\n\n    template <class Sequence>\n    std::pair<int, int> representative_occurrence(const\
    \ Sequence& sequence) const {\n        state_id id = root_state;\n        int\
    \ length = 0;\n        for (const auto& symbol : sequence) {\n            id =\
    \ transition(id, symbol);\n            if (id == null_state) return {-1, -1};\n\
    \            length++;\n        }\n        int end = _states[id].first_end;\n\
    \        return {end - length, end};\n    }\n\n    template <class Sequence>\n\
    \    std::pair<int, int> longest_common_substring(const Sequence& sequence) const\
    \ {\n        state_id current = root_state;\n        int current_length = 0;\n\
    \        int best_length = 0;\n        int best_end = 0;\n        int end = 0;\n\
    \n        for (const auto& value : sequence) {\n            int symbol = symbol_index(value);\n\
    \            while (current != root_state && _states[current].next[symbol] ==\
    \ null_state) {\n                current = _states[current].suffix_link;\n   \
    \             current_length = std::min(current_length, _states[current].length);\n\
    \            }\n            state_id next = _states[current].next[symbol];\n \
    \           if (next == null_state) {\n                current = root_state;\n\
    \                current_length = 0;\n            } else {\n                current\
    \ = next;\n                current_length++;\n            }\n            end++;\n\
    \            if (best_length < current_length) {\n                best_length\
    \ = current_length;\n                best_end = end;\n            }\n        }\n\
    \        return {best_end - best_length, best_end};\n    }\n};\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_SUFFIX_AUTOMATON_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/suffix_automaton.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-06-23 12:05:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/suffix_automaton.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/suffix_automaton.hpp
layout: document
title: Suffix Automaton
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
