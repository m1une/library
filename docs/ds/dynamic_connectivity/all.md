---
title: Dynamic Connectivity
documentation_of: ../../../ds/dynamic_connectivity/all.hpp
---

## Included Headers

| Header | Use case |
| --- | --- |
| `online_dynamic_connectivity.hpp` | Operations must be answered immediately. |
| `offline_dynamic_connectivity.hpp` | The operation log may be processed together for faster deletion handling. |

Both structures maintain an undirected multigraph and erase edges by id.
