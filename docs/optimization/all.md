---
title: Optimization All
documentation_of: ../../optimization/all.hpp
---

## Overview

`optimization/all.hpp` includes optimization algorithms whose public interface
is not naturally a graph, data structure, or algebraic object.

## Included Headers

| Header | Contents |
| --- | --- |
| `optimization/alien_trick.hpp` | Alien Trick helpers for exact-count optimization through Lagrangian relaxation. |
| `optimization/convex_hull_trick.hpp` | Monotone-slope CHT for minimum or maximum line queries. |
| `optimization/hungarian.hpp` | Hungarian algorithm for minimum-cost and maximum-cost rectangular assignment. |
| `optimization/integer_lp.hpp` | Branch-and-bound solver for integer linear programming in standard inequality form. |
| `optimization/li_chao_tree.hpp` | Dynamic Li Chao tree for arbitrary line and line-segment insertion. |
| `optimization/project_selection.hpp` | Minimum-cut solver for binary project selection with gains, implication penalties, and hard constraints. |
| `optimization/simplex.hpp` | Two-phase simplex algorithm for linear programming in standard inequality form. |
| `optimization/slope_trick.hpp` | Heap-based representation of convex piecewise-linear functions. |
