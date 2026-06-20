---
title: Geometry Bundle
documentation_of: ../../geometry/all.hpp
---

## Overview

`geometry/all.hpp` includes the complete 2D geometry module.

## Included Headers

| Header | Contents |
| --- | --- |
| `geometry/point.hpp` | Points, vectors, dot/cross products, exact orientation, distance, and rotation. |
| `geometry/line.hpp` | Lines, segments, projection, intersection, and distances. |
| `geometry/polygon.hpp` | Area, convex hull, point containment, and convex diameter. |
| `geometry/circle.hpp` | Circle relations and intersection points. |

Integral predicates promote to signed 128-bit arithmetic. Constructions that
may be non-integral return `Point<long double>`.
