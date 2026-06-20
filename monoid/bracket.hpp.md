---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"monoid/bracket.hpp\"\n\n\n\n#include <algorithm>\n\nnamespace\
    \ m1une {\nnamespace monoid {\n\nstruct BracketNode {\n    int matched;\n    int\
    \ unmatched_right;  // Count of unmatched ')'\n    int unmatched_left;   // Count\
    \ of unmatched '('\n};\n\n// Monoid for matching parentheses (Bracket Sequences).\n\
    struct Bracket {\n    using value_type = BracketNode;\n\n    // The identity element\
    \ is an empty sequence.\n    static constexpr value_type id() {\n        return\
    \ {0, 0, 0};\n    }\n\n    // Merges two bracket sequences.\n    // The unmatched\
    \ '(' from the left perfectly matches the unmatched ')' from the right.\n    static\
    \ constexpr value_type op(const value_type& a, const value_type& b) {\n      \
    \  int match = std::min(a.unmatched_left, b.unmatched_right);\n        return\
    \ {a.matched + b.matched + match, a.unmatched_right + b.unmatched_right - match,\n\
    \                a.unmatched_left + b.unmatched_left - match};\n    }\n\n    //\
    \ Helper to securely create a leaf node from a single character.\n    static constexpr\
    \ value_type make(char c) {\n        if (c == '(') return {0, 0, 1};\n       \
    \ if (c == ')') return {0, 1, 0};\n        return {0, 0, 0};\n    }\n};\n\n} \
    \ // namespace monoid\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_MONOID_BRACKET_HPP\n#define M1UNE_MONOID_BRACKET_HPP 1\n\n\
    #include <algorithm>\n\nnamespace m1une {\nnamespace monoid {\n\nstruct BracketNode\
    \ {\n    int matched;\n    int unmatched_right;  // Count of unmatched ')'\n \
    \   int unmatched_left;   // Count of unmatched '('\n};\n\n// Monoid for matching\
    \ parentheses (Bracket Sequences).\nstruct Bracket {\n    using value_type = BracketNode;\n\
    \n    // The identity element is an empty sequence.\n    static constexpr value_type\
    \ id() {\n        return {0, 0, 0};\n    }\n\n    // Merges two bracket sequences.\n\
    \    // The unmatched '(' from the left perfectly matches the unmatched ')' from\
    \ the right.\n    static constexpr value_type op(const value_type& a, const value_type&\
    \ b) {\n        int match = std::min(a.unmatched_left, b.unmatched_right);\n \
    \       return {a.matched + b.matched + match, a.unmatched_right + b.unmatched_right\
    \ - match,\n                a.unmatched_left + b.unmatched_left - match};\n  \
    \  }\n\n    // Helper to securely create a leaf node from a single character.\n\
    \    static constexpr value_type make(char c) {\n        if (c == '(') return\
    \ {0, 0, 1};\n        if (c == ')') return {0, 1, 0};\n        return {0, 0, 0};\n\
    \    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\n#endif  // M1UNE_MONOID_BRACKET_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: monoid/bracket.hpp
  requiredBy: []
  timestamp: '2026-06-13 20:51:48+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: monoid/bracket.hpp
layout: document
title: Bracket Monoid
---

## Overview

A monoid for processing bracket sequences (parentheses matching). It maintains the number of successfully matched pairs, as well as the count of unmatched closing `)` and opening `(` brackets.

A sequence is considered a "valid bracket sequence" if both `unmatched_right` and `unmatched_left` are `0`.

## Example

```cpp
#include "ds/segtree/segtree.hpp"
#include "monoid/bracket.hpp"
#include <iostream>
#include <string>
#include <vector>

using BracketM = m1une::monoid::Bracket;

int main() {
    std::string S = "())(()()";
    int N = S.size();

    std::vector<BracketM::value_type> init_data(N);
    for (int i = 0; i < N; ++i) {
        init_data[i] = BracketM::make(S[i]);
    }

    m1une::ds::Segtree<BracketM> seg(init_data);

    // Query range [3, 8) -> "(()()"
    auto res = seg.prod(3, 8);

    std::cout << "Matched Pairs: " << res.matched << "\n"; // Output: 2
    std::cout << "Unmatched '(': " << res.unmatched_left << "\n"; // Output: 1
    std::cout << "Unmatched ')': " << res.unmatched_right << "\n"; // Output: 0

    return 0;
}
```
