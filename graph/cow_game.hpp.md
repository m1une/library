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
  - icon: ':heavy_check_mark:'
    path: graph/shortest_path.hpp
    title: Shortest Path
  - icon: ':heavy_check_mark:'
    path: graph/undirected.hpp
    title: Undirected Graph Algorithms
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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/cow_game.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <limits>\n#include <optional>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T>\n\
    struct CowGameConstraint {\n    int from;\n    int to;\n    T upper_bound;\n};\n\
    \ntemplate <class T>\nstruct CowGameSolution {\n    bool feasible = false;\n \
    \   std::vector<T> value;\n\n    bool is_feasible() const {\n        return feasible;\n\
    \    }\n};\n\ntemplate <class T>\nstruct CowGameUpperBounds {\n    bool feasible;\n\
    \    std::vector<T> upper_bound;\n    T inf;\n\n    bool is_feasible() const {\n\
    \        return feasible;\n    }\n\n    bool bounded(int variable) const {\n \
    \       assert(0 <= variable && variable < int(upper_bound.size()));\n       \
    \ return feasible && upper_bound[variable] != inf;\n    }\n};\n\ntemplate <class\
    \ T>\nstruct CowGameDifferenceBounds {\n    bool feasible;\n    std::optional<T>\
    \ lower_bound;\n    std::optional<T> upper_bound;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n\n    bool bounded_below() const {\n   \
    \     return feasible && lower_bound.has_value();\n    }\n\n    bool bounded_above()\
    \ const {\n        return feasible && upper_bound.has_value();\n    }\n};\n\n\
    template <class T>\nclass CowGame {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct RelaxationResult {\n        bool has_negative_cycle;\n\
    \        std::vector<T> dist;\n    };\n\n    int _n;\n    std::vector<CowGameConstraint<T>>\
    \ _constraints;\n    mutable bool _solution_cached = false;\n    mutable CowGameSolution<T>\
    \ _cached_solution;\n\n    void assert_variable(int variable) const {\n      \
    \  (void)variable;\n        assert(0 <= variable && variable < _n);\n    }\n\n\
    \    T negate(T value) const {\n        assert(value != std::numeric_limits<T>::lowest());\n\
    \        return -value;\n    }\n\n    RelaxationResult relax(std::vector<T> dist,\
    \ T inf, bool skip_unreachable) const {\n        for (int iteration = 0; iteration\
    \ < _n; iteration++) {\n            bool updated = false;\n            for (const\
    \ auto& constraint : _constraints) {\n                if (skip_unreachable &&\
    \ dist[constraint.from] == inf) continue;\n                T candidate = dist[constraint.from]\
    \ + constraint.upper_bound;\n                if (dist[constraint.to] <= candidate)\
    \ continue;\n                dist[constraint.to] = candidate;\n              \
    \  updated = true;\n                if (iteration == _n - 1) return RelaxationResult{true,\
    \ std::move(dist)};\n            }\n            if (!updated) break;\n       \
    \ }\n        return RelaxationResult{false, std::move(dist)};\n    }\n\n    RelaxationResult\
    \ check_feasibility() const {\n        return relax(std::vector<T>(_n, T()), T(),\
    \ false);\n    }\n\n    RelaxationResult shortest_paths(int source, T inf) const\
    \ {\n        std::vector<T> dist(_n, inf);\n        dist[source] = T();\n    \
    \    return relax(std::move(dist), inf, true);\n    }\n\n   public:\n    CowGame()\
    \ : CowGame(0) {}\n\n    explicit CowGame(int variable_count) : _n(variable_count)\
    \ {\n        assert(variable_count >= 0);\n    }\n\n    int size() const {\n \
    \       return _n;\n    }\n\n    int constraint_count() const {\n        return\
    \ int(_constraints.size());\n    }\n\n    const CowGameConstraint<T>& get_constraint(int\
    \ id) const {\n        assert(0 <= id && id < int(_constraints.size()));\n   \
    \     return _constraints[id];\n    }\n\n    const std::vector<CowGameConstraint<T>>&\
    \ constraints() const {\n        return _constraints;\n    }\n\n    int add_upper_bound(int\
    \ from, int to, T upper_bound) {\n        assert_variable(from);\n        assert_variable(to);\n\
    \        int id = int(_constraints.size());\n        _constraints.push_back(CowGameConstraint<T>{from,\
    \ to, upper_bound});\n        _solution_cached = false;\n        return id;\n\
    \    }\n\n    int add_constraint(int from, int to, T upper_bound) {\n        return\
    \ add_upper_bound(from, to, upper_bound);\n    }\n\n    int add_lower_bound(int\
    \ from, int to, T lower_bound) {\n        return add_upper_bound(to, from, negate(lower_bound));\n\
    \    }\n\n    void add_bounds(int from, int to, T lower_bound, T upper_bound)\
    \ {\n        assert(lower_bound <= upper_bound);\n        add_lower_bound(from,\
    \ to, lower_bound);\n        add_upper_bound(from, to, upper_bound);\n    }\n\n\
    \    void add_equality(int from, int to, T difference) {\n        add_bounds(from,\
    \ to, difference, difference);\n    }\n\n    CowGameSolution<T> solve() const\
    \ {\n        if (_solution_cached) return _cached_solution;\n\n        auto result\
    \ = check_feasibility();\n        _cached_solution.feasible = !result.has_negative_cycle;\n\
    \        _cached_solution.value.clear();\n        if (_cached_solution.feasible)\
    \ _cached_solution.value = std::move(result.dist);\n        _solution_cached =\
    \ true;\n        return _cached_solution;\n    }\n\n    bool is_feasible() const\
    \ {\n        if (!_solution_cached) (void)solve();\n        return _cached_solution.feasible;\n\
    \    }\n\n    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {\n\
    \        assert_variable(source);\n        T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n        CowGameUpperBounds<T> result;\n        result.feasible = is_feasible();\n\
    \        result.inf = inf;\n        result.upper_bound.assign(_n, inf);\n    \
    \    if (!result.feasible) return result;\n\n        result.upper_bound = shortest_paths(source,\
    \ inf).dist;\n        return result;\n    }\n\n    CowGameDifferenceBounds<T>\
    \ difference_bounds(int from, int to) const {\n        assert_variable(from);\n\
    \        assert_variable(to);\n        T inf = std::numeric_limits<T>::max() /\
    \ T(4);\n        CowGameDifferenceBounds<T> result;\n        result.feasible =\
    \ is_feasible();\n        if (!result.feasible) return result;\n\n        auto\
    \ forward = shortest_paths(from, inf);\n        if (forward.dist[to] != inf) result.upper_bound\
    \ = forward.dist[to];\n\n        auto backward = shortest_paths(to, inf);\n  \
    \      if (backward.dist[from] != inf) result.lower_bound = negate(backward.dist[from]);\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nusing DifferenceConstraints\
    \ = CowGame<T>;\n\n}  // namespace graph\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_GRAPH_COW_GAME_HPP\n#define M1UNE_GRAPH_COW_GAME_HPP 1\n\n\
    #include <cassert>\n#include <limits>\n#include <optional>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace graph {\n\
    \ntemplate <class T>\nstruct CowGameConstraint {\n    int from;\n    int to;\n\
    \    T upper_bound;\n};\n\ntemplate <class T>\nstruct CowGameSolution {\n    bool\
    \ feasible = false;\n    std::vector<T> value;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n};\n\ntemplate <class T>\nstruct CowGameUpperBounds\
    \ {\n    bool feasible;\n    std::vector<T> upper_bound;\n    T inf;\n\n    bool\
    \ is_feasible() const {\n        return feasible;\n    }\n\n    bool bounded(int\
    \ variable) const {\n        assert(0 <= variable && variable < int(upper_bound.size()));\n\
    \        return feasible && upper_bound[variable] != inf;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct CowGameDifferenceBounds {\n    bool feasible;\n    std::optional<T>\
    \ lower_bound;\n    std::optional<T> upper_bound;\n\n    bool is_feasible() const\
    \ {\n        return feasible;\n    }\n\n    bool bounded_below() const {\n   \
    \     return feasible && lower_bound.has_value();\n    }\n\n    bool bounded_above()\
    \ const {\n        return feasible && upper_bound.has_value();\n    }\n};\n\n\
    template <class T>\nclass CowGame {\n    static_assert(std::is_arithmetic_v<T>\
    \ && std::is_signed_v<T>);\n\n    struct RelaxationResult {\n        bool has_negative_cycle;\n\
    \        std::vector<T> dist;\n    };\n\n    int _n;\n    std::vector<CowGameConstraint<T>>\
    \ _constraints;\n    mutable bool _solution_cached = false;\n    mutable CowGameSolution<T>\
    \ _cached_solution;\n\n    void assert_variable(int variable) const {\n      \
    \  (void)variable;\n        assert(0 <= variable && variable < _n);\n    }\n\n\
    \    T negate(T value) const {\n        assert(value != std::numeric_limits<T>::lowest());\n\
    \        return -value;\n    }\n\n    RelaxationResult relax(std::vector<T> dist,\
    \ T inf, bool skip_unreachable) const {\n        for (int iteration = 0; iteration\
    \ < _n; iteration++) {\n            bool updated = false;\n            for (const\
    \ auto& constraint : _constraints) {\n                if (skip_unreachable &&\
    \ dist[constraint.from] == inf) continue;\n                T candidate = dist[constraint.from]\
    \ + constraint.upper_bound;\n                if (dist[constraint.to] <= candidate)\
    \ continue;\n                dist[constraint.to] = candidate;\n              \
    \  updated = true;\n                if (iteration == _n - 1) return RelaxationResult{true,\
    \ std::move(dist)};\n            }\n            if (!updated) break;\n       \
    \ }\n        return RelaxationResult{false, std::move(dist)};\n    }\n\n    RelaxationResult\
    \ check_feasibility() const {\n        return relax(std::vector<T>(_n, T()), T(),\
    \ false);\n    }\n\n    RelaxationResult shortest_paths(int source, T inf) const\
    \ {\n        std::vector<T> dist(_n, inf);\n        dist[source] = T();\n    \
    \    return relax(std::move(dist), inf, true);\n    }\n\n   public:\n    CowGame()\
    \ : CowGame(0) {}\n\n    explicit CowGame(int variable_count) : _n(variable_count)\
    \ {\n        assert(variable_count >= 0);\n    }\n\n    int size() const {\n \
    \       return _n;\n    }\n\n    int constraint_count() const {\n        return\
    \ int(_constraints.size());\n    }\n\n    const CowGameConstraint<T>& get_constraint(int\
    \ id) const {\n        assert(0 <= id && id < int(_constraints.size()));\n   \
    \     return _constraints[id];\n    }\n\n    const std::vector<CowGameConstraint<T>>&\
    \ constraints() const {\n        return _constraints;\n    }\n\n    int add_upper_bound(int\
    \ from, int to, T upper_bound) {\n        assert_variable(from);\n        assert_variable(to);\n\
    \        int id = int(_constraints.size());\n        _constraints.push_back(CowGameConstraint<T>{from,\
    \ to, upper_bound});\n        _solution_cached = false;\n        return id;\n\
    \    }\n\n    int add_constraint(int from, int to, T upper_bound) {\n        return\
    \ add_upper_bound(from, to, upper_bound);\n    }\n\n    int add_lower_bound(int\
    \ from, int to, T lower_bound) {\n        return add_upper_bound(to, from, negate(lower_bound));\n\
    \    }\n\n    void add_bounds(int from, int to, T lower_bound, T upper_bound)\
    \ {\n        assert(lower_bound <= upper_bound);\n        add_lower_bound(from,\
    \ to, lower_bound);\n        add_upper_bound(from, to, upper_bound);\n    }\n\n\
    \    void add_equality(int from, int to, T difference) {\n        add_bounds(from,\
    \ to, difference, difference);\n    }\n\n    CowGameSolution<T> solve() const\
    \ {\n        if (_solution_cached) return _cached_solution;\n\n        auto result\
    \ = check_feasibility();\n        _cached_solution.feasible = !result.has_negative_cycle;\n\
    \        _cached_solution.value.clear();\n        if (_cached_solution.feasible)\
    \ _cached_solution.value = std::move(result.dist);\n        _solution_cached =\
    \ true;\n        return _cached_solution;\n    }\n\n    bool is_feasible() const\
    \ {\n        if (!_solution_cached) (void)solve();\n        return _cached_solution.feasible;\n\
    \    }\n\n    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {\n\
    \        assert_variable(source);\n        T inf = std::numeric_limits<T>::max()\
    \ / T(4);\n        CowGameUpperBounds<T> result;\n        result.feasible = is_feasible();\n\
    \        result.inf = inf;\n        result.upper_bound.assign(_n, inf);\n    \
    \    if (!result.feasible) return result;\n\n        result.upper_bound = shortest_paths(source,\
    \ inf).dist;\n        return result;\n    }\n\n    CowGameDifferenceBounds<T>\
    \ difference_bounds(int from, int to) const {\n        assert_variable(from);\n\
    \        assert_variable(to);\n        T inf = std::numeric_limits<T>::max() /\
    \ T(4);\n        CowGameDifferenceBounds<T> result;\n        result.feasible =\
    \ is_feasible();\n        if (!result.feasible) return result;\n\n        auto\
    \ forward = shortest_paths(from, inf);\n        if (forward.dist[to] != inf) result.upper_bound\
    \ = forward.dist[to];\n\n        auto backward = shortest_paths(to, inf);\n  \
    \      if (backward.dist[from] != inf) result.lower_bound = negate(backward.dist[from]);\n\
    \        return result;\n    }\n};\n\ntemplate <class T>\nusing DifferenceConstraints\
    \ = CowGame<T>;\n\n}  // namespace graph\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_GRAPH_COW_GAME_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/cow_game.hpp
  requiredBy:
  - graph/all.hpp
  - graph/undirected.hpp
  - graph/directed.hpp
  - graph/shortest_path.hpp
  timestamp: '2026-06-22 23:27:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/graph/cow_game.test.cpp
  - verify/graph/range_edge_graph.test.cpp
  - verify/graph/graph_algorithms.test.cpp
documentation_of: graph/cow_game.hpp
layout: document
title: Cow Game (Difference Constraints)
---

## Overview

`CowGame<T>` solves a system of difference constraints. Each variable is a
number `x[i]`, and the primitive constraint is

$$
x[\mathrm{to}] - x[\mathrm{from}] \le \mathrm{upper\_bound}.
$$

This family is sometimes called a “cow game” in competitive-programming
slang, after several classic cow-placement problems with distance constraints.
`DifferenceConstraints<T>` is provided as a descriptive alias of
`CowGame<T>`.

The solver can:

- determine whether all constraints are simultaneously feasible;
- return one feasible assignment;
- find the tightest upper bounds relative to one variable;
- find the tightest lower and upper bounds on one difference;
- report when either side of a difference is unbounded.

Internally, every constraint becomes a directed edge and the implementation
uses Bellman-Ford relaxation. A negative cycle means that the system is
infeasible.

## Adding Constraints

All variable indices are zero-based.

| Method | Added condition |
| --- | --- |
| `add_upper_bound(from, to, upper)` | `x[to] - x[from] <= upper` |
| `add_constraint(from, to, upper)` | Alias of `add_upper_bound` |
| `add_lower_bound(from, to, lower)` | `lower <= x[to] - x[from]` |
| `add_bounds(from, to, lower, upper)` | `lower <= x[to] - x[from] <= upper` |
| `add_equality(from, to, difference)` | `x[to] - x[from] == difference` |

`add_upper_bound` and `add_constraint` return the id of the generated
constraint. A lower bound is represented by reversing the edge and negating
the bound. Bounds and equalities therefore generate two primitive constraints.

## Feasible Assignment

`solve()` returns `CowGameSolution<T>`:

| Member / Method | Meaning |
| --- | --- |
| `feasible` | Whether the whole system is feasible. |
| `value` | One assignment satisfying every constraint when feasible. |
| `is_feasible()` | Returns `feasible`. |

The system contains only differences, so adding the same constant to every
value preserves feasibility. The assignment returned by `solve()` is one
convenient representative, not a uniquely normalized solution.

`is_feasible()` checks feasibility without returning the assignment.
The feasibility result is cached until another constraint is added, which
avoids repeating the global negative-cycle check across bound queries.

## Tight Difference Bounds

`tightest_upper_bounds(source)` returns `CowGameUpperBounds<T>`. When the
system is feasible, `upper_bound[v]` is the smallest implied upper bound on
`x[v] - x[source]`. It equals the shortest-path distance from `source` to `v`.

If no directed constraint path exists, the difference is unbounded above:
`bounded(v)` is false and `upper_bound[v]` equals the result's `inf` sentinel.

`difference_bounds(from, to)` returns `CowGameDifferenceBounds<T>`:

| Member / Method | Meaning |
| --- | --- |
| `feasible` | Whether the whole system is feasible. |
| `lower_bound` | Tightest lower bound on `x[to] - x[from]`, or empty if unbounded below. |
| `upper_bound` | Tightest upper bound on `x[to] - x[from]`, or empty if unbounded above. |
| `bounded_below()` | Whether `lower_bound` exists. |
| `bounded_above()` | Whether `upper_bound` exists. |

Check feasibility before interpreting bounds. In an infeasible system, neither
bound is meaningful.

## Constraint Inspection

`CowGameConstraint<T>` stores `from`, `to`, and `upper_bound`.

| Method | Meaning |
| --- | --- |
| `size()` | Number of variables. |
| `constraint_count()` | Number of primitive upper-bound constraints. |
| `get_constraint(id)` | Returns one primitive constraint. |
| `constraints()` | Returns all primitive constraints. |

## Complexity

Let `N` be the number of variables and `M` the number of primitive constraints.

| Operation | Time | Memory |
| --- | --- | --- |
| Add or inspect one constraint | Amortized $O(1)$ | $O(1)$ additional |
| First `solve` or `is_feasible` after adding a constraint | $O(NM)$ | $O(N + M)$ |
| Later `solve`, `is_feasible` before another addition | $O(N)$ for `solve`, $O(1)$ for `is_feasible` | $O(N)$ returned by `solve` |
| `tightest_upper_bounds` | $O(NM)$ | $O(N + M)$ |
| `difference_bounds` | $O(NM)$ | $O(N + M)$ |

All relaxations stop early when an entire pass makes no update.

## Numeric Requirements

`T` must be a signed arithmetic type. `long long` is recommended. Negated
lower bounds, finite path sums, and answers must fit in `T`. For bound queries,
finite path sums must also stay strictly inside the sentinel range based on
`numeric_limits<T>::max() / 4`.

## Example

```cpp
#include "graph/cow_game.hpp"
#include <iostream>

int main() {
    m1une::graph::CowGame<long long> game(3);

    // 2 <= x[1] - x[0] <= 5
    game.add_bounds(0, 1, 2, 5);

    // x[2] - x[1] == 4
    game.add_equality(1, 2, 4);

    auto bounds = game.difference_bounds(0, 2);
    if (!bounds.is_feasible()) {
        std::cout << "infeasible\n";
        return 0;
    }

    std::cout << *bounds.lower_bound << " " << *bounds.upper_bound << "\n";
    // 6 9
}
```
