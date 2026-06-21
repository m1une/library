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
| `geometry/ray.hpp` | Rays, containment, projection, intersections, and distances with other linear objects. |
| `geometry/polygon.hpp` | Area, centroids, triangulation, hulls, containment, ray queries, intersection, clipping, and Minkowski sums. |
| `geometry/circle.hpp` | Circle relations, line/ray intersections, and ray reflection. |

Integral predicates promote to signed 128-bit arithmetic. Constructions that
may be non-integral return `Point<long double>`.
