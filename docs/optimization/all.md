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
| `optimization/hungarian.hpp` | Hungarian algorithm for minimum-cost and maximum-cost rectangular assignment. |
| `optimization/integer_lp.hpp` | Branch-and-bound solver for integer linear programming in standard inequality form. |
| `optimization/project_selection.hpp` | Minimum-cut solver for binary project selection with gains, implication penalties, and hard constraints. |
| `optimization/simplex.hpp` | Two-phase simplex algorithm for linear programming in standard inequality form. |
| `optimization/slope_trick.hpp` | Heap-based representation of convex piecewise-linear functions. |
