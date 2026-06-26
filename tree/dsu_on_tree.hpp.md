---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/all.hpp
    title: Tree All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/tree/dsu_on_tree.test.cpp
    title: verify/tree/dsu_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/tree/tree_algorithms.test.cpp
    title: verify/tree/tree_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/dsu_on_tree.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <utility>\n#include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"\
    graph/graph.hpp\"\n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T\
    \ = int>\nstruct Edge {\n    using cost_type = T;\n\n    int from;\n    int to;\n\
    \    T cost;\n    int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()),\
    \ id(-1), alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_\
    \ = -1, bool alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_),\
    \ alive(alive_) {}\n\n    int other(int v) const {\n        assert(v == from ||\
    \ v == to);\n        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\n\
    struct Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n \
    \  private:\n    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>>\
    \ _g;\n    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n\
    \   public:\n    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n)\
    \ : _n(n), _edge_count(0), _g(n) {\n        assert(0 <= n);\n    }\n\n    int\
    \ size() const {\n        return _n;\n    }\n\n    bool empty() const {\n    \
    \    return _n == 0;\n    }\n\n    int edge_count() const {\n        return _edge_count;\n\
    \    }\n\n    int add_vertex() {\n        _g.emplace_back();\n        return _n++;\n\
    \    }\n\n    int add_directed_edge(int from, int to, T cost = T(1)) {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     int id = _edge_count++;\n        int idx = int(_g[from].size());\n     \
    \   _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({from, idx});\n        return id;\n\
    \    }\n\n    int add_edge(int u, int v, T cost = T(1)) {\n        assert(0 <=\
    \ u && u < _n);\n        assert(0 <= v && v < _n);\n        int id = _edge_count++;\n\
    \        int u_idx = int(_g[u].size());\n        int v_idx = int(_g[v].size());\n\
    \        _g[u].push_back(edge_type(u, v, cost, id));\n        _g[v].push_back(edge_type(v,\
    \ u, cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({u,\
    \ u_idx});\n        _edge_positions.back().push_back({v, v_idx});\n        return\
    \ id;\n    }\n\n    void set_edge_alive(int id, bool alive) {\n        assert(0\
    \ <= id && id < _edge_count);\n        for (auto [v, idx] : _edge_positions[id])\
    \ {\n            _g[v][idx].alive = alive;\n        }\n    }\n\n    void erase_edge(int\
    \ id) {\n        set_edge_alive(id, false);\n    }\n\n    void revive_edge(int\
    \ id) {\n        set_edge_alive(id, true);\n    }\n\n    bool is_edge_alive(int\
    \ id) const {\n        assert(0 <= id && id < _edge_count);\n        assert(!_edge_positions[id].empty());\n\
    \        auto [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n\
    \    }\n\n    const std::vector<edge_type>& operator[](int v) const {\n      \
    \  assert(0 <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
    \ operator[](int v) {\n        assert(0 <= v && v < _n);\n        return _g[v];\n\
    \    }\n\n    const std::vector<std::vector<edge_type>>& adjacency() const {\n\
    \        return _g;\n    }\n\n    std::vector<std::vector<edge_type>>& adjacency()\
    \ {\n        return _g;\n    }\n\n    std::vector<edge_type> edges(bool include_inactive\
    \ = false) const {\n        std::vector<edge_type> result;\n        result.reserve(_edge_count);\n\
    \        std::vector<char> used(_edge_count, false);\n        for (int v = 0;\
    \ v < _n; v++) {\n            for (const auto& e : _g[v]) {\n                if\
    \ (!include_inactive && !e.alive) continue;\n                if (0 <= e.id &&\
    \ e.id < _edge_count) {\n                    if (used[e.id]) continue;\n     \
    \               used[e.id] = true;\n                }\n                result.push_back(e);\n\
    \            }\n        }\n        return result;\n    }\n\n    Graph reversed()\
    \ const {\n        Graph result(_n);\n        result._edge_count = _edge_count;\n\
    \        result._edge_positions.assign(_edge_count, {});\n        for (int v =\
    \ 0; v < _n; v++) {\n            for (const auto& e : _g[v]) {\n             \
    \   int idx = int(result._g[e.to].size());\n                result._g[e.to].push_back(edge_type(e.to,\
    \ e.from, e.cost, e.id, e.alive));\n                if (0 <= e.id && e.id < _edge_count)\
    \ result._edge_positions[e.id].push_back({e.to, idx});\n            }\n      \
    \  }\n        return result;\n    }\n};\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 9 \"tree/dsu_on_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ tree {\n\ntemplate <class T = int>\nstruct DsuOnTree {\n    int n;\n    int\
    \ root;\n    std::vector<int> parent;\n    std::vector<int> parent_edge;\n   \
    \ std::vector<int> depth;\n    std::vector<int> subtree_size;\n    std::vector<int>\
    \ heavy_child;\n    std::vector<int> tin;\n    std::vector<int> tout;\n    std::vector<int>\
    \ order;\n    std::vector<std::vector<int>> children;\n\n    DsuOnTree() : n(0),\
    \ root(-1) {}\n\n    explicit DsuOnTree(\n        const m1une::graph::Graph<T>&\
    \ graph,\n        int root_vertex = 0\n    ) {\n        build(graph, root_vertex);\n\
    \    }\n\n    void build(\n        const m1une::graph::Graph<T>& graph,\n    \
    \    int root_vertex = 0\n    ) {\n        n = graph.size();\n        root = n\
    \ == 0 ? -1 : root_vertex;\n        parent.assign(n, -2);\n        parent_edge.assign(n,\
    \ -1);\n        depth.assign(n, 0);\n        subtree_size.assign(n, 1);\n    \
    \    heavy_child.assign(n, -1);\n        tin.assign(n, -1);\n        tout.assign(n,\
    \ -1);\n        order.clear();\n        order.reserve(n);\n        children.assign(n,\
    \ {});\n        if (n == 0) return;\n\n        assert(0 <= root && root < n);\n\
    \        std::vector<int> stack;\n        stack.push_back(root);\n        parent[root]\
    \ = -1;\n        while (!stack.empty()) {\n            int vertex = stack.back();\n\
    \            stack.pop_back();\n            tin[vertex] = int(order.size());\n\
    \            order.push_back(vertex);\n\n            for (const auto& edge : graph[vertex])\
    \ {\n                if (!edge.alive || parent[edge.to] != -2) continue;\n   \
    \             parent[edge.to] = vertex;\n                parent_edge[edge.to]\
    \ = edge.id;\n                depth[edge.to] = depth[vertex] + 1;\n          \
    \      children[vertex].push_back(edge.to);\n                stack.push_back(edge.to);\n\
    \            }\n        }\n        assert(int(order.size()) == n);\n\n       \
    \ for (int index = n - 1; index >= 0; --index) {\n            int vertex = order[index];\n\
    \            for (int child : children[vertex]) {\n                subtree_size[vertex]\
    \ += subtree_size[child];\n                if (\n                    heavy_child[vertex]\
    \ == -1 ||\n                    subtree_size[heavy_child[vertex]] < subtree_size[child]\n\
    \                ) {\n                    heavy_child[vertex] = child;\n     \
    \           }\n            }\n            tout[vertex] = tin[vertex] + subtree_size[vertex];\n\
    \        }\n    }\n\n    int size() const {\n        return n;\n    }\n\n    bool\
    \ empty() const {\n        return n == 0;\n    }\n\n    std::pair<int, int> subtree_range(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < n);\n        return\
    \ {tin[vertex], tout[vertex]};\n    }\n\n    // Runs DSU on tree. `add(v)` inserts\
    \ one vertex into the maintained state,\n    // `remove(v)` erases it, and `answer(v)`\
    \ observes the state for subtree(v).\n    template <class Add, class Remove, class\
    \ Answer>\n    void run(Add add, Remove remove, Answer answer) const {\n     \
    \   if (n == 0) return;\n\n        enum ActionType {\n            Process,\n \
    \           AddSubtree,\n            AddVertex,\n            AnswerVertex,\n \
    \           RemoveSubtree,\n        };\n        struct Action {\n            ActionType\
    \ type;\n            int vertex;\n            bool keep;\n        };\n\n     \
    \   std::vector<Action> actions;\n        actions.reserve(3 * std::size_t(n));\n\
    \        actions.push_back(Action{Process, root, true});\n\n        while (!actions.empty())\
    \ {\n            Action action = actions.back();\n            actions.pop_back();\n\
    \            int vertex = action.vertex;\n\n            if (action.type == AddSubtree)\
    \ {\n                for (int index = tin[vertex]; index < tout[vertex]; ++index)\
    \ {\n                    add(order[index]);\n                }\n            }\
    \ else if (action.type == AddVertex) {\n                add(vertex);\n       \
    \     } else if (action.type == AnswerVertex) {\n                answer(vertex);\n\
    \            } else if (action.type == RemoveSubtree) {\n                for (int\
    \ index = tin[vertex]; index < tout[vertex]; ++index) {\n                    remove(order[index]);\n\
    \                }\n            } else {\n                if (!action.keep) {\n\
    \                    actions.push_back(Action{\n                        RemoveSubtree,\n\
    \                        vertex,\n                        false,\n           \
    \         });\n                }\n                actions.push_back(Action{AnswerVertex,\
    \ vertex, false});\n                actions.push_back(Action{AddVertex, vertex,\
    \ false});\n\n                for (int child : children[vertex]) {\n         \
    \           if (child != heavy_child[vertex]) {\n                        actions.push_back(Action{\n\
    \                            AddSubtree,\n                            child,\n\
    \                            false,\n                        });\n           \
    \         }\n                }\n                if (heavy_child[vertex] != -1)\
    \ {\n                    actions.push_back(Action{\n                        Process,\n\
    \                        heavy_child[vertex],\n                        true,\n\
    \                    });\n                }\n                for (int child :\
    \ children[vertex]) {\n                    if (child != heavy_child[vertex]) {\n\
    \                        actions.push_back(Action{Process, child, false});\n \
    \                   }\n                }\n            }\n        }\n    }\n};\n\
    \n}  // namespace tree\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_TREE_DSU_ON_TREE_HPP\n#define M1UNE_TREE_DSU_ON_TREE_HPP 1\n\
    \n#include <cassert>\n#include <utility>\n#include <vector>\n\n#include \"../graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace tree {\n\ntemplate <class T = int>\nstruct DsuOnTree\
    \ {\n    int n;\n    int root;\n    std::vector<int> parent;\n    std::vector<int>\
    \ parent_edge;\n    std::vector<int> depth;\n    std::vector<int> subtree_size;\n\
    \    std::vector<int> heavy_child;\n    std::vector<int> tin;\n    std::vector<int>\
    \ tout;\n    std::vector<int> order;\n    std::vector<std::vector<int>> children;\n\
    \n    DsuOnTree() : n(0), root(-1) {}\n\n    explicit DsuOnTree(\n        const\
    \ m1une::graph::Graph<T>& graph,\n        int root_vertex = 0\n    ) {\n     \
    \   build(graph, root_vertex);\n    }\n\n    void build(\n        const m1une::graph::Graph<T>&\
    \ graph,\n        int root_vertex = 0\n    ) {\n        n = graph.size();\n  \
    \      root = n == 0 ? -1 : root_vertex;\n        parent.assign(n, -2);\n    \
    \    parent_edge.assign(n, -1);\n        depth.assign(n, 0);\n        subtree_size.assign(n,\
    \ 1);\n        heavy_child.assign(n, -1);\n        tin.assign(n, -1);\n      \
    \  tout.assign(n, -1);\n        order.clear();\n        order.reserve(n);\n  \
    \      children.assign(n, {});\n        if (n == 0) return;\n\n        assert(0\
    \ <= root && root < n);\n        std::vector<int> stack;\n        stack.push_back(root);\n\
    \        parent[root] = -1;\n        while (!stack.empty()) {\n            int\
    \ vertex = stack.back();\n            stack.pop_back();\n            tin[vertex]\
    \ = int(order.size());\n            order.push_back(vertex);\n\n            for\
    \ (const auto& edge : graph[vertex]) {\n                if (!edge.alive || parent[edge.to]\
    \ != -2) continue;\n                parent[edge.to] = vertex;\n              \
    \  parent_edge[edge.to] = edge.id;\n                depth[edge.to] = depth[vertex]\
    \ + 1;\n                children[vertex].push_back(edge.to);\n               \
    \ stack.push_back(edge.to);\n            }\n        }\n        assert(int(order.size())\
    \ == n);\n\n        for (int index = n - 1; index >= 0; --index) {\n         \
    \   int vertex = order[index];\n            for (int child : children[vertex])\
    \ {\n                subtree_size[vertex] += subtree_size[child];\n          \
    \      if (\n                    heavy_child[vertex] == -1 ||\n              \
    \      subtree_size[heavy_child[vertex]] < subtree_size[child]\n             \
    \   ) {\n                    heavy_child[vertex] = child;\n                }\n\
    \            }\n            tout[vertex] = tin[vertex] + subtree_size[vertex];\n\
    \        }\n    }\n\n    int size() const {\n        return n;\n    }\n\n    bool\
    \ empty() const {\n        return n == 0;\n    }\n\n    std::pair<int, int> subtree_range(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < n);\n        return\
    \ {tin[vertex], tout[vertex]};\n    }\n\n    // Runs DSU on tree. `add(v)` inserts\
    \ one vertex into the maintained state,\n    // `remove(v)` erases it, and `answer(v)`\
    \ observes the state for subtree(v).\n    template <class Add, class Remove, class\
    \ Answer>\n    void run(Add add, Remove remove, Answer answer) const {\n     \
    \   if (n == 0) return;\n\n        enum ActionType {\n            Process,\n \
    \           AddSubtree,\n            AddVertex,\n            AnswerVertex,\n \
    \           RemoveSubtree,\n        };\n        struct Action {\n            ActionType\
    \ type;\n            int vertex;\n            bool keep;\n        };\n\n     \
    \   std::vector<Action> actions;\n        actions.reserve(3 * std::size_t(n));\n\
    \        actions.push_back(Action{Process, root, true});\n\n        while (!actions.empty())\
    \ {\n            Action action = actions.back();\n            actions.pop_back();\n\
    \            int vertex = action.vertex;\n\n            if (action.type == AddSubtree)\
    \ {\n                for (int index = tin[vertex]; index < tout[vertex]; ++index)\
    \ {\n                    add(order[index]);\n                }\n            }\
    \ else if (action.type == AddVertex) {\n                add(vertex);\n       \
    \     } else if (action.type == AnswerVertex) {\n                answer(vertex);\n\
    \            } else if (action.type == RemoveSubtree) {\n                for (int\
    \ index = tin[vertex]; index < tout[vertex]; ++index) {\n                    remove(order[index]);\n\
    \                }\n            } else {\n                if (!action.keep) {\n\
    \                    actions.push_back(Action{\n                        RemoveSubtree,\n\
    \                        vertex,\n                        false,\n           \
    \         });\n                }\n                actions.push_back(Action{AnswerVertex,\
    \ vertex, false});\n                actions.push_back(Action{AddVertex, vertex,\
    \ false});\n\n                for (int child : children[vertex]) {\n         \
    \           if (child != heavy_child[vertex]) {\n                        actions.push_back(Action{\n\
    \                            AddSubtree,\n                            child,\n\
    \                            false,\n                        });\n           \
    \         }\n                }\n                if (heavy_child[vertex] != -1)\
    \ {\n                    actions.push_back(Action{\n                        Process,\n\
    \                        heavy_child[vertex],\n                        true,\n\
    \                    });\n                }\n                for (int child :\
    \ children[vertex]) {\n                    if (child != heavy_child[vertex]) {\n\
    \                        actions.push_back(Action{Process, child, false});\n \
    \                   }\n                }\n            }\n        }\n    }\n};\n\
    \n}  // namespace tree\n}  // namespace m1une\n\n#endif  // M1UNE_TREE_DSU_ON_TREE_HPP\n"
  dependsOn:
  - graph/graph.hpp
  isVerificationFile: false
  path: tree/dsu_on_tree.hpp
  requiredBy:
  - tree/all.hpp
  timestamp: '2026-06-23 02:14:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/tree/tree_algorithms.test.cpp
  - verify/tree/dsu_on_tree.test.cpp
documentation_of: tree/dsu_on_tree.hpp
layout: document
title: DSU on Tree
---

## Overview

`DsuOnTree<T>` implements the small-to-large subtree technique also known as
sack. It answers one query for every rooted subtree while maintaining a
user-defined data structure.

For each vertex, light-child data is discarded after processing, while the
largest child's data is kept and reused. If inserting and removing one vertex
cost $O(F)$, all callbacks together take $O(N\log N\cdot F)$ time.

The implementation uses an explicit action stack rather than recursion, so it
is safe on a path-shaped tree with many vertices.

## Complexity Notation

* `N` is the number of vertices.
* `F` is the cost of one user callback.

## Construction

```cpp
DsuOnTree(const Graph<T>& graph, int root = 0);
void build(const Graph<T>& graph, int root = 0);
```

The graph must be a connected undirected tree built with `add_edge`. Inactive
edges are ignored. The chosen root determines every queried subtree.

Construction takes $O(N)$ time and memory.

## Methods and Metadata

The object exposes:

| Member | Description |
| --- | --- |
| `n`, `root` | Number of vertices and chosen root. |
| `parent`, `parent_edge`, `depth` | Rooted-tree metadata. |
| `subtree_size` | Number of vertices in each subtree. |
| `heavy_child` | Largest child, or `-1` for a leaf. |
| `children` | Children in the rooted tree. |
| `tin`, `tout`, `order` | Preorder Euler intervals; subtree `v` is `order[tin[v]..tout[v])`. |

`size()`, `empty()`, and `subtree_range(v)` provide the corresponding basic
queries.

## Running the Algorithm

```cpp
dsu.run(add, remove, answer);
```

The callbacks receive a vertex index:

* `add(v)` inserts vertex `v` into the maintained state.
* `remove(v)` erases vertex `v`.
* `answer(v)` is called when the state contains exactly the vertices in the
  subtree of `v`.

The structure may call `add` and `remove` for the same vertex several times.
They must therefore be mutually inverse operations. After `run` finishes, the
state contains the whole tree because the root's sack is retained.

## Example

This computes the number of distinct colors in every subtree:

```cpp
#include "graph/graph.hpp"
#include "tree/dsu_on_tree.hpp"

#include <vector>

int main() {
    m1une::graph::Graph<int> graph(4);
    graph.add_edge(0, 1);
    graph.add_edge(0, 2);
    graph.add_edge(1, 3);

    std::vector<int> color = {0, 1, 0, 2};
    std::vector<int> frequency(3);
    std::vector<int> answer(4);
    int distinct = 0;

    m1une::tree::DsuOnTree dsu(graph, 0);
    dsu.run(
        [&](int vertex) {
            if (frequency[color[vertex]]++ == 0) distinct++;
        },
        [&](int vertex) {
            if (--frequency[color[vertex]] == 0) distinct--;
        },
        [&](int vertex) {
            answer[vertex] = distinct;
        }
    );
}
```
