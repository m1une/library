---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/all.hpp
    title: Graph All
  - icon: ':heavy_check_mark:'
    path: graph/directed.hpp
    title: Directed Graph Algorithms
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/graph/cow_game.test.cpp
    title: verify/graph/cow_game.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/graph_algorithms.test.cpp
    title: verify/graph/graph_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/range_edge_graph.test.cpp
    title: verify/graph/range_edge_graph.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/graph/two_sat.test.cpp
    title: verify/graph/two_sat.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/two_sat.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <cstddef>\n#include <limits>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace graph {\n\n// A 2-SAT solver using iterative strongly connected\
    \ components.\nstruct TwoSat {\n   private:\n    struct Csr {\n        std::vector<int>\
    \ start;\n        std::vector<int> to;\n    };\n\n    int _n;\n    std::vector<std::pair<int,\
    \ int>> _edges;\n    bool _solved;\n    bool _satisfiable;\n    std::vector<bool>\
    \ _answer;\n\n    int node(int variable, bool value) const {\n        assert(0\
    \ <= variable && variable < _n);\n        return 2 * variable + int(value);\n\
    \    }\n\n    void add_edge(int from, int to) {\n        _edges.emplace_back(from,\
    \ to);\n        _solved = false;\n        _answer.clear();\n    }\n\n    Csr build_csr(bool\
    \ reverse) const {\n        int vertices = 2 * _n;\n        Csr graph;\n     \
    \   graph.start.assign(vertices + 1, 0);\n        graph.to.resize(_edges.size());\n\
    \n        for (auto [from, to] : _edges) {\n            int source = reverse ?\
    \ to : from;\n            graph.start[source + 1]++;\n        }\n        for (int\
    \ v = 0; v < vertices; v++) {\n            graph.start[v + 1] += graph.start[v];\n\
    \        }\n\n        std::vector<int> cursor = graph.start;\n        for (auto\
    \ [from, to] : _edges) {\n            int source = reverse ? to : from;\n    \
    \        int target = reverse ? from : to;\n            graph.to[cursor[source]++]\
    \ = target;\n        }\n        return graph;\n    }\n\n   public:\n    TwoSat()\
    \ : TwoSat(0) {}\n\n    explicit TwoSat(int n)\n        : _n(n), _solved(false),\
    \ _satisfiable(false) {\n        assert(0 <= n);\n        assert(n <= std::numeric_limits<int>::max()\
    \ / 2);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Reserves space for\
    \ approximately `clause_count` two-literal clauses.\n    void reserve(std::size_t\
    \ clause_count) {\n        assert(clause_count <= std::size_t(std::numeric_limits<int>::max())\
    \ / 2);\n        _edges.reserve(2 * clause_count);\n    }\n\n    // Adds (variable\
    \ i == f) OR (variable j == g).\n    void add_clause(int i, bool f, int j, bool\
    \ g) {\n        int a = node(i, f);\n        int b = node(j, g);\n        add_edge(a\
    \ ^ 1, b);\n        add_edge(b ^ 1, a);\n    }\n\n    // Adds (variable i == f)\
    \ => (variable j == g).\n    void add_implication(int i, bool f, int j, bool g)\
    \ {\n        add_clause(i, !f, j, g);\n    }\n\n    // Forces variable i to equal\
    \ value.\n    void set_value(int i, bool value) {\n        add_clause(i, value,\
    \ i, value);\n    }\n\n    // Forces variables i and j to have equal values.\n\
    \    void add_equal(int i, int j) {\n        add_clause(i, false, j, true);\n\
    \        add_clause(i, true, j, false);\n    }\n\n    // Forces variables i and\
    \ j to have different values.\n    void add_not_equal(int i, int j) {\n      \
    \  add_clause(i, true, j, true);\n        add_clause(i, false, j, false);\n  \
    \  }\n\n    bool satisfiable() {\n        if (_solved) return _satisfiable;\n\
    \        assert(_edges.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n        int vertices = 2 * _n;\n        Csr graph = build_csr(false);\n    \
    \    Csr reverse_graph = build_csr(true);\n\n        std::vector<char> seen(vertices,\
    \ false);\n        std::vector<int> order;\n        order.reserve(vertices);\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.reserve(vertices);\n\
    \n        for (int start = 0; start < vertices; start++) {\n            if (seen[start])\
    \ continue;\n            seen[start] = true;\n            stack.emplace_back(start,\
    \ graph.start[start]);\n\n            while (!stack.empty()) {\n             \
    \   int v = stack.back().first;\n                int& edge = stack.back().second;\n\
    \                if (edge == graph.start[v + 1]) {\n                    order.push_back(v);\n\
    \                    stack.pop_back();\n                    continue;\n      \
    \          }\n\n                int to = graph.to[edge++];\n                if\
    \ (!seen[to]) {\n                    seen[to] = true;\n                    stack.emplace_back(to,\
    \ graph.start[to]);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ component(vertices, -1);\n        std::vector<int> vertices_stack;\n       \
    \ vertices_stack.reserve(vertices);\n        int component_count = 0;\n      \
    \  for (int index = vertices - 1; index >= 0; index--) {\n            int start\
    \ = order[index];\n            if (component[start] != -1) continue;\n\n     \
    \       component[start] = component_count;\n            vertices_stack.push_back(start);\n\
    \            while (!vertices_stack.empty()) {\n                int v = vertices_stack.back();\n\
    \                vertices_stack.pop_back();\n                for (int edge = reverse_graph.start[v];\n\
    \                     edge < reverse_graph.start[v + 1];\n                   \
    \  edge++) {\n                    int to = reverse_graph.to[edge];\n         \
    \           if (component[to] == -1) {\n                        component[to]\
    \ = component_count;\n                        vertices_stack.push_back(to);\n\
    \                    }\n                }\n            }\n            component_count++;\n\
    \        }\n\n        _answer.assign(_n, false);\n        _satisfiable = true;\n\
    \        for (int i = 0; i < _n; i++) {\n            if (component[2 * i] == component[2\
    \ * i + 1]) {\n                _satisfiable = false;\n                _answer.clear();\n\
    \                break;\n            }\n            _answer[i] = component[2 *\
    \ i] < component[2 * i + 1];\n        }\n        _solved = true;\n        return\
    \ _satisfiable;\n    }\n\n    const std::vector<bool>& answer() const {\n    \
    \    assert(_solved && _satisfiable);\n        return _answer;\n    }\n\n    bool\
    \ value(int variable) const {\n        assert(_solved && _satisfiable);\n    \
    \    assert(0 <= variable && variable < _n);\n        return _answer[variable];\n\
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_TWO_SAT_HPP\n#define M1UNE_GRAPH_TWO_SAT_HPP 1\n\n#include\
    \ <cassert>\n#include <cstddef>\n#include <limits>\n#include <utility>\n#include\
    \ <vector>\n\nnamespace m1une {\nnamespace graph {\n\n// A 2-SAT solver using\
    \ iterative strongly connected components.\nstruct TwoSat {\n   private:\n   \
    \ struct Csr {\n        std::vector<int> start;\n        std::vector<int> to;\n\
    \    };\n\n    int _n;\n    std::vector<std::pair<int, int>> _edges;\n    bool\
    \ _solved;\n    bool _satisfiable;\n    std::vector<bool> _answer;\n\n    int\
    \ node(int variable, bool value) const {\n        assert(0 <= variable && variable\
    \ < _n);\n        return 2 * variable + int(value);\n    }\n\n    void add_edge(int\
    \ from, int to) {\n        _edges.emplace_back(from, to);\n        _solved = false;\n\
    \        _answer.clear();\n    }\n\n    Csr build_csr(bool reverse) const {\n\
    \        int vertices = 2 * _n;\n        Csr graph;\n        graph.start.assign(vertices\
    \ + 1, 0);\n        graph.to.resize(_edges.size());\n\n        for (auto [from,\
    \ to] : _edges) {\n            int source = reverse ? to : from;\n           \
    \ graph.start[source + 1]++;\n        }\n        for (int v = 0; v < vertices;\
    \ v++) {\n            graph.start[v + 1] += graph.start[v];\n        }\n\n   \
    \     std::vector<int> cursor = graph.start;\n        for (auto [from, to] : _edges)\
    \ {\n            int source = reverse ? to : from;\n            int target = reverse\
    \ ? from : to;\n            graph.to[cursor[source]++] = target;\n        }\n\
    \        return graph;\n    }\n\n   public:\n    TwoSat() : TwoSat(0) {}\n\n \
    \   explicit TwoSat(int n)\n        : _n(n), _solved(false), _satisfiable(false)\
    \ {\n        assert(0 <= n);\n        assert(n <= std::numeric_limits<int>::max()\
    \ / 2);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Reserves space for\
    \ approximately `clause_count` two-literal clauses.\n    void reserve(std::size_t\
    \ clause_count) {\n        assert(clause_count <= std::size_t(std::numeric_limits<int>::max())\
    \ / 2);\n        _edges.reserve(2 * clause_count);\n    }\n\n    // Adds (variable\
    \ i == f) OR (variable j == g).\n    void add_clause(int i, bool f, int j, bool\
    \ g) {\n        int a = node(i, f);\n        int b = node(j, g);\n        add_edge(a\
    \ ^ 1, b);\n        add_edge(b ^ 1, a);\n    }\n\n    // Adds (variable i == f)\
    \ => (variable j == g).\n    void add_implication(int i, bool f, int j, bool g)\
    \ {\n        add_clause(i, !f, j, g);\n    }\n\n    // Forces variable i to equal\
    \ value.\n    void set_value(int i, bool value) {\n        add_clause(i, value,\
    \ i, value);\n    }\n\n    // Forces variables i and j to have equal values.\n\
    \    void add_equal(int i, int j) {\n        add_clause(i, false, j, true);\n\
    \        add_clause(i, true, j, false);\n    }\n\n    // Forces variables i and\
    \ j to have different values.\n    void add_not_equal(int i, int j) {\n      \
    \  add_clause(i, true, j, true);\n        add_clause(i, false, j, false);\n  \
    \  }\n\n    bool satisfiable() {\n        if (_solved) return _satisfiable;\n\
    \        assert(_edges.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n        int vertices = 2 * _n;\n        Csr graph = build_csr(false);\n    \
    \    Csr reverse_graph = build_csr(true);\n\n        std::vector<char> seen(vertices,\
    \ false);\n        std::vector<int> order;\n        order.reserve(vertices);\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.reserve(vertices);\n\
    \n        for (int start = 0; start < vertices; start++) {\n            if (seen[start])\
    \ continue;\n            seen[start] = true;\n            stack.emplace_back(start,\
    \ graph.start[start]);\n\n            while (!stack.empty()) {\n             \
    \   int v = stack.back().first;\n                int& edge = stack.back().second;\n\
    \                if (edge == graph.start[v + 1]) {\n                    order.push_back(v);\n\
    \                    stack.pop_back();\n                    continue;\n      \
    \          }\n\n                int to = graph.to[edge++];\n                if\
    \ (!seen[to]) {\n                    seen[to] = true;\n                    stack.emplace_back(to,\
    \ graph.start[to]);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ component(vertices, -1);\n        std::vector<int> vertices_stack;\n       \
    \ vertices_stack.reserve(vertices);\n        int component_count = 0;\n      \
    \  for (int index = vertices - 1; index >= 0; index--) {\n            int start\
    \ = order[index];\n            if (component[start] != -1) continue;\n\n     \
    \       component[start] = component_count;\n            vertices_stack.push_back(start);\n\
    \            while (!vertices_stack.empty()) {\n                int v = vertices_stack.back();\n\
    \                vertices_stack.pop_back();\n                for (int edge = reverse_graph.start[v];\n\
    \                     edge < reverse_graph.start[v + 1];\n                   \
    \  edge++) {\n                    int to = reverse_graph.to[edge];\n         \
    \           if (component[to] == -1) {\n                        component[to]\
    \ = component_count;\n                        vertices_stack.push_back(to);\n\
    \                    }\n                }\n            }\n            component_count++;\n\
    \        }\n\n        _answer.assign(_n, false);\n        _satisfiable = true;\n\
    \        for (int i = 0; i < _n; i++) {\n            if (component[2 * i] == component[2\
    \ * i + 1]) {\n                _satisfiable = false;\n                _answer.clear();\n\
    \                break;\n            }\n            _answer[i] = component[2 *\
    \ i] < component[2 * i + 1];\n        }\n        _solved = true;\n        return\
    \ _satisfiable;\n    }\n\n    const std::vector<bool>& answer() const {\n    \
    \    assert(_solved && _satisfiable);\n        return _answer;\n    }\n\n    bool\
    \ value(int variable) const {\n        assert(_solved && _satisfiable);\n    \
    \    assert(0 <= variable && variable < _n);\n        return _answer[variable];\n\
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  // M1UNE_GRAPH_TWO_SAT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/two_sat.hpp
  requiredBy:
  - graph/all.hpp
  - graph/directed.hpp
  timestamp: '2026-06-21 02:34:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/two_sat.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/two_sat.hpp
layout: document
title: Two-Satisfiability
---

## Overview

`m1une::graph::TwoSat` solves boolean formulas whose clauses contain at most
two literals. It converts every clause to implications and checks strongly
connected components.

The implementation stores implications in a flat edge list and builds compact
CSR graphs when solving. Both SCC passes are iterative, so large formulas do
not depend on the process recursion limit.

## Literal Convention

The expression:

```cpp
add_clause(i, f, j, g)
```

adds the clause:

```text
(variable i == f) OR (variable j == g)
```

For example, `add_clause(0, true, 1, false)` means
$x_0 \lor \lnot x_1$.

## Construction

* `TwoSat()`: creates a formula with zero variables.
* `TwoSat(int n)`: creates a formula with variables `0` through `n - 1`.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size()` | Returns the number of variables. | $O(1)$ |
| `bool empty()` | Returns whether there are no variables. | $O(1)$ |
| `void reserve(size_t clauses)` | Reserves implication-edge storage for approximately `clauses` ordinary clauses. | $O(M)$ |
| `void add_clause(i, f, j, g)` | Adds `(x_i == f) OR (x_j == g)`. | Amortized $O(1)$ |
| `void add_implication(i, f, j, g)` | Adds `(x_i == f) => (x_j == g)`. | Amortized $O(1)$ |
| `void set_value(i, value)` | Forces `x_i` to equal `value`. | Amortized $O(1)$ |
| `void add_equal(i, j)` | Forces `x_i == x_j`. | Amortized $O(1)$ |
| `void add_not_equal(i, j)` | Forces `x_i != x_j`. | Amortized $O(1)$ |
| `bool satisfiable()` | Solves the current formula and returns whether an assignment exists. | $O(N + M)$ |
| `const vector<bool>& answer()` | Returns one satisfying assignment. Call only after a successful `satisfiable()`. | $O(1)$ |
| `bool value(int i)` | Returns the assigned value of variable `i`. | $O(1)$ |

Here $M$ is the number of implication edges, which is twice the number of
ordinary clauses. Calling `satisfiable()` again without adding constraints
returns the cached result in $O(1)$. Adding any constraint invalidates the
cached result.

`add_implication(a, f, b, g)` also adds its contrapositive, as required by its
equivalent 2-CNF clause.

## Example

```cpp
#include "graph/two_sat.hpp"

#include <iostream>

int main() {
    m1une::graph::TwoSat sat(3);

    sat.add_clause(0, true, 1, false); // x0 OR NOT x1
    sat.add_implication(1, true, 2, true);
    sat.set_value(0, true);

    if (!sat.satisfiable()) {
        std::cout << "impossible\n";
        return 0;
    }

    for (bool value : sat.answer()) {
        std::cout << value << "\n";
    }
}
```
