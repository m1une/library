---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dominator_tree.hpp
    title: Dominator Tree
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dominatortree
    links:
    - https://judge.yosupo.jp/problem/dominatortree
  bundledCode: "#line 1 \"verify/graph/dominator_tree.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/dominatortree\"\n\n#line 1 \"graph/dominator_tree.hpp\"\
    \n\n\n\n#include <cassert>\n#include <utility>\n#include <vector>\n\n#line 1 \"\
    graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\ntemplate <class T = int>\nstruct Edge {\n    using cost_type = T;\n\
    \n    int from;\n    int to;\n    T cost;\n    int id;\n    bool alive;\n\n  \
    \  Edge() : from(-1), to(-1), cost(T()), id(-1), alive(true) {}\n    Edge(int\
    \ from_, int to_, T cost_ = T(1), int id_ = -1, bool alive_ = true)\n        :\
    \ from(from_), to(to_), cost(cost_), id(id_), alive(alive_) {}\n\n    int other(int\
    \ v) const {\n        assert(v == from || v == to);\n        return from ^ to\
    \ ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct Graph {\n    using edge_type\
    \ = Edge<T>;\n    using cost_type = T;\n\n   private:\n    int _n;\n    int _edge_count;\n\
    \    std::vector<std::vector<edge_type>> _g;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> _edge_positions;\n\n   public:\n    Graph() : _n(0), _edge_count(0) {}\n\
    \    explicit Graph(int n) : _n(n), _edge_count(0), _g(n) {\n        assert(0\
    \ <= n);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    int edge_count() const\
    \ {\n        return _edge_count;\n    }\n\n    int add_vertex() {\n        _g.emplace_back();\n\
    \        return _n++;\n    }\n\n    int add_directed_edge(int from, int to, T\
    \ cost = T(1)) {\n        assert(0 <= from && from < _n);\n        assert(0 <=\
    \ to && to < _n);\n        int id = _edge_count++;\n        int idx = int(_g[from].size());\n\
    \        _g[from].push_back(edge_type(from, to, cost, id));\n        _edge_positions.emplace_back();\n\
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
    \ m1une\n\n\n#line 9 \"graph/dominator_tree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ graph {\n\nstruct DominatorTree {\n    int root;\n    std::vector<int> immediate_dominator;\n\
    \    std::vector<std::vector<int>> children;\n    std::vector<int> dfs_order;\n\
    \    std::vector<int> tin;\n    std::vector<int> tout;\n\n    int size() const\
    \ {\n        return int(immediate_dominator.size());\n    }\n\n    bool reachable(int\
    \ vertex) const {\n        assert(0 <= vertex && vertex < size());\n        return\
    \ immediate_dominator[vertex] != -1;\n    }\n\n    bool dominates(int ancestor,\
    \ int vertex) const {\n        assert(0 <= ancestor && ancestor < size());\n \
    \       assert(0 <= vertex && vertex < size());\n        return\n            reachable(ancestor)\
    \ &&\n            reachable(vertex) &&\n            tin[ancestor] <= tin[vertex]\
    \ &&\n            tin[vertex] < tout[ancestor];\n    }\n};\n\n// Lengauer-Tarjan\
    \ immediate dominators from one start vertex.\ntemplate <class T>\nDominatorTree\
    \ dominator_tree(const Graph<T>& graph, int root) {\n    int n = graph.size();\n\
    \    assert(0 <= root && root < n);\n\n    std::vector<int> dfs_index(n, -1);\n\
    \    std::vector<int> vertex;\n    std::vector<int> parent_vertex(n, -1);\n  \
    \  std::vector<std::pair<int, int>> stack;\n    dfs_index[root] = 0;\n    vertex.push_back(root);\n\
    \    stack.emplace_back(root, 0);\n\n    while (!stack.empty()) {\n        int\
    \ current = stack.back().first;\n        int& edge_index = stack.back().second;\n\
    \        if (edge_index == int(graph[current].size())) {\n            stack.pop_back();\n\
    \            continue;\n        }\n        const auto& edge = graph[current][edge_index++];\n\
    \        if (!edge.alive || dfs_index[edge.to] != -1) continue;\n        parent_vertex[edge.to]\
    \ = current;\n        dfs_index[edge.to] = int(vertex.size());\n        vertex.push_back(edge.to);\n\
    \        stack.emplace_back(edge.to, 0);\n    }\n\n    int reachable_count = int(vertex.size());\n\
    \    std::vector<std::vector<int>> predecessor(reachable_count);\n    for (int\
    \ from : vertex) {\n        for (const auto& edge : graph[from]) {\n         \
    \   if (!edge.alive || dfs_index[edge.to] == -1) continue;\n            predecessor[dfs_index[edge.to]].push_back(dfs_index[from]);\n\
    \        }\n    }\n\n    std::vector<int> parent(reachable_count, -1);\n    for\
    \ (int index = 1; index < reachable_count; ++index) {\n        parent[index] =\
    \ dfs_index[parent_vertex[vertex[index]]];\n    }\n\n    std::vector<int> semi(reachable_count);\n\
    \    std::vector<int> idom(reachable_count, -1);\n    std::vector<int> ancestor(reachable_count,\
    \ -1);\n    std::vector<int> label(reachable_count);\n    std::vector<std::vector<int>>\
    \ bucket(reachable_count);\n    for (int index = 0; index < reachable_count; ++index)\
    \ {\n        semi[index] = index;\n        label[index] = index;\n    }\n\n  \
    \  auto compress = [&](int start) {\n        std::vector<int> path;\n        int\
    \ current = start;\n        while (\n            ancestor[current] != -1 &&\n\
    \            ancestor[ancestor[current]] != -1\n        ) {\n            path.push_back(current);\n\
    \            current = ancestor[current];\n        }\n        for (int index =\
    \ int(path.size()) - 1; index >= 0; --index) {\n            int node = path[index];\n\
    \            int parent_node = ancestor[node];\n            if (semi[label[parent_node]]\
    \ < semi[label[node]]) {\n                label[node] = label[parent_node];\n\
    \            }\n            ancestor[node] = ancestor[parent_node];\n        }\n\
    \    };\n\n    auto eval = [&](int node) {\n        if (ancestor[node] == -1)\
    \ return label[node];\n        compress(node);\n        int parent_node = ancestor[node];\n\
    \        if (semi[label[parent_node]] < semi[label[node]]) {\n            return\
    \ label[parent_node];\n        }\n        return label[node];\n    };\n\n    for\
    \ (int current = reachable_count - 1; current >= 1; --current) {\n        for\
    \ (int previous : predecessor[current]) {\n            semi[current] = std::min(semi[current],\
    \ semi[eval(previous)]);\n        }\n        bucket[semi[current]].push_back(current);\n\
    \        ancestor[current] = parent[current];\n\n        int parent_node = parent[current];\n\
    \        for (int node : bucket[parent_node]) {\n            int best = eval(node);\n\
    \            idom[node] =\n                semi[best] < semi[node] ? best : parent_node;\n\
    \        }\n        bucket[parent_node].clear();\n    }\n\n    for (int current\
    \ = 1; current < reachable_count; ++current) {\n        if (idom[current] != semi[current])\
    \ {\n            idom[current] = idom[idom[current]];\n        }\n    }\n    idom[0]\
    \ = 0;\n\n    DominatorTree result;\n    result.root = root;\n    result.immediate_dominator.assign(n,\
    \ -1);\n    result.children.assign(n, {});\n    result.dfs_order = vertex;\n \
    \   for (int index = 0; index < reachable_count; ++index) {\n        int current\
    \ = vertex[index];\n        int dominator = vertex[idom[index]];\n        result.immediate_dominator[current]\
    \ = dominator;\n        if (current != root) result.children[dominator].push_back(current);\n\
    \    }\n\n    result.tin.assign(n, -1);\n    result.tout.assign(n, -1);\n    int\
    \ timer = 0;\n    std::vector<std::pair<int, int>> tree_stack;\n    tree_stack.emplace_back(root,\
    \ 0);\n    result.tin[root] = timer++;\n    while (!tree_stack.empty()) {\n  \
    \      int current = tree_stack.back().first;\n        int& child_index = tree_stack.back().second;\n\
    \        if (child_index == int(result.children[current].size())) {\n        \
    \    result.tout[current] = timer;\n            tree_stack.pop_back();\n     \
    \       continue;\n        }\n        int child = result.children[current][child_index++];\n\
    \        result.tin[child] = timer++;\n        tree_stack.emplace_back(child,\
    \ 0);\n    }\n    return result;\n}\n\n}  // namespace graph\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/graph/dominator_tree.test.cpp\"\n\n#line 6 \"verify/graph/dominator_tree.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#line 9 \"verify/graph/dominator_tree.test.cpp\"\
    \n\n#line 11 \"verify/graph/dominator_tree.test.cpp\"\n\nnamespace {\n\nstd::vector<int>\
    \ brute_idom(\n    const m1une::graph::Graph<>& graph,\n    int root\n) {\n  \
    \  int n = graph.size();\n    std::vector<char> reachable(n, false);\n    std::vector<int>\
    \ stack = {root};\n    reachable[root] = true;\n    while (!stack.empty()) {\n\
    \        int current = stack.back();\n        stack.pop_back();\n        for (const\
    \ auto& edge : graph[current]) {\n            if (!edge.alive || reachable[edge.to])\
    \ continue;\n            reachable[edge.to] = true;\n            stack.push_back(edge.to);\n\
    \        }\n    }\n\n    std::vector<std::vector<char>> dominator(\n        n,\n\
    \        std::vector<char>(n, false)\n    );\n    for (int vertex = 0; vertex\
    \ < n; ++vertex) {\n        if (!reachable[vertex]) continue;\n        if (vertex\
    \ == root) {\n            dominator[vertex][root] = true;\n        } else {\n\
    \            for (int candidate = 0; candidate < n; ++candidate) {\n         \
    \       dominator[vertex][candidate] = reachable[candidate];\n            }\n\
    \        }\n    }\n\n    bool changed = true;\n    while (changed) {\n       \
    \ changed = false;\n        for (int vertex = 0; vertex < n; ++vertex) {\n   \
    \         if (!reachable[vertex] || vertex == root) continue;\n            std::vector<char>\
    \ next(n, true);\n            bool has_predecessor = false;\n            for (int\
    \ from = 0; from < n; ++from) {\n                for (const auto& edge : graph[from])\
    \ {\n                    if (\n                        edge.alive &&\n       \
    \                 edge.to == vertex &&\n                        reachable[from]\n\
    \                    ) {\n                        if (!has_predecessor) {\n  \
    \                          next = dominator[from];\n                         \
    \   has_predecessor = true;\n                        } else {\n              \
    \              for (int candidate = 0; candidate < n; ++candidate) {\n       \
    \                         next[candidate] =\n                                \
    \    next[candidate]\n                                    && dominator[from][candidate];\n\
    \                            }\n                        }\n                  \
    \  }\n                }\n            }\n            next[vertex] = true;\n   \
    \         if (next != dominator[vertex]) {\n                dominator[vertex]\
    \ = std::move(next);\n                changed = true;\n            }\n       \
    \ }\n    }\n\n    std::vector<int> result(n, -1);\n    result[root] = root;\n\
    \    for (int vertex = 0; vertex < n; ++vertex) {\n        if (!reachable[vertex]\
    \ || vertex == root) continue;\n        for (int candidate = 0; candidate < n;\
    \ ++candidate) {\n            if (\n                candidate == vertex ||\n \
    \               !dominator[vertex][candidate]\n            ) {\n             \
    \   continue;\n            }\n            bool immediate = true;\n           \
    \ for (int other = 0; other < n; ++other) {\n                if (\n          \
    \          other == vertex ||\n                    other == candidate ||\n   \
    \                 !dominator[vertex][other]\n                ) {\n           \
    \         continue;\n                }\n                if (dominator[other][candidate])\
    \ {\n                    immediate = false;\n                    break;\n    \
    \            }\n            }\n            if (immediate) {\n                result[vertex]\
    \ = candidate;\n                break;\n            }\n        }\n    }\n    return\
    \ result;\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 1601;\n  \
    \  auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 5000; ++trial) {\n        int n = 1 + int(random() % 12);\n        m1une::graph::Graph<>\
    \ graph(n);\n        for (int from = 0; from < n; ++from) {\n            for (int\
    \ to = 0; to < n; ++to) {\n                if (random() % 5 == 0) {\n        \
    \            graph.add_directed_edge(from, to);\n                }\n         \
    \   }\n        }\n        int root = int(random() % n);\n        auto actual =\
    \ m1une::graph::dominator_tree(graph, root);\n        auto expected = brute_idom(graph,\
    \ root);\n        assert(actual.immediate_dominator == expected);\n\n        for\
    \ (int vertex = 0; vertex < n; ++vertex) {\n            assert(actual.reachable(vertex)\
    \ == (expected[vertex] != -1));\n            for (int ancestor = 0; ancestor <\
    \ n; ++ancestor) {\n                [[maybe_unused]] bool dominates = false;\n\
    \                if (expected[vertex] != -1) {\n                    for (\n  \
    \                      int current = vertex;\n                        current\
    \ != -1;\n                        current = current == root\n                \
    \            ? -1\n                            : expected[current]\n         \
    \           ) {\n                        if (current == ancestor) dominates =\
    \ true;\n                    }\n                }\n                assert(actual.dominates(ancestor,\
    \ vertex) == dominates);\n            }\n        }\n    }\n}\n\nvoid test_long_path()\
    \ {\n    constexpr int n = 200000;\n    m1une::graph::Graph<> graph(n);\n    for\
    \ (int vertex = 1; vertex < n; ++vertex) {\n        graph.add_directed_edge(vertex\
    \ - 1, vertex);\n    }\n    auto result = m1une::graph::dominator_tree(graph,\
    \ 0);\n    assert(result.immediate_dominator[n - 1] == n - 2);\n    assert(result.dominates(0,\
    \ n - 1));\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n   \
    \ test_long_path();\n\n    int n, m, root;\n    std::cin >> n >> m >> root;\n\
    \    m1une::graph::Graph<> graph(n);\n    while (m--) {\n        int from, to;\n\
    \        std::cin >> from >> to;\n        graph.add_directed_edge(from, to);\n\
    \    }\n    auto result = m1une::graph::dominator_tree(graph, root);\n    for\
    \ (int vertex = 0; vertex < n; ++vertex) {\n        if (vertex) std::cout << '\
    \ ';\n        std::cout << result.immediate_dominator[vertex];\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dominatortree\"\n\n#include\
    \ \"../../graph/dominator_tree.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <iostream>\n#include <vector>\n\n#include \"../../graph/graph.hpp\"\n\
    \nnamespace {\n\nstd::vector<int> brute_idom(\n    const m1une::graph::Graph<>&\
    \ graph,\n    int root\n) {\n    int n = graph.size();\n    std::vector<char>\
    \ reachable(n, false);\n    std::vector<int> stack = {root};\n    reachable[root]\
    \ = true;\n    while (!stack.empty()) {\n        int current = stack.back();\n\
    \        stack.pop_back();\n        for (const auto& edge : graph[current]) {\n\
    \            if (!edge.alive || reachable[edge.to]) continue;\n            reachable[edge.to]\
    \ = true;\n            stack.push_back(edge.to);\n        }\n    }\n\n    std::vector<std::vector<char>>\
    \ dominator(\n        n,\n        std::vector<char>(n, false)\n    );\n    for\
    \ (int vertex = 0; vertex < n; ++vertex) {\n        if (!reachable[vertex]) continue;\n\
    \        if (vertex == root) {\n            dominator[vertex][root] = true;\n\
    \        } else {\n            for (int candidate = 0; candidate < n; ++candidate)\
    \ {\n                dominator[vertex][candidate] = reachable[candidate];\n  \
    \          }\n        }\n    }\n\n    bool changed = true;\n    while (changed)\
    \ {\n        changed = false;\n        for (int vertex = 0; vertex < n; ++vertex)\
    \ {\n            if (!reachable[vertex] || vertex == root) continue;\n       \
    \     std::vector<char> next(n, true);\n            bool has_predecessor = false;\n\
    \            for (int from = 0; from < n; ++from) {\n                for (const\
    \ auto& edge : graph[from]) {\n                    if (\n                    \
    \    edge.alive &&\n                        edge.to == vertex &&\n           \
    \             reachable[from]\n                    ) {\n                     \
    \   if (!has_predecessor) {\n                            next = dominator[from];\n\
    \                            has_predecessor = true;\n                       \
    \ } else {\n                            for (int candidate = 0; candidate < n;\
    \ ++candidate) {\n                                next[candidate] =\n        \
    \                            next[candidate]\n                               \
    \     && dominator[from][candidate];\n                            }\n        \
    \                }\n                    }\n                }\n            }\n\
    \            next[vertex] = true;\n            if (next != dominator[vertex])\
    \ {\n                dominator[vertex] = std::move(next);\n                changed\
    \ = true;\n            }\n        }\n    }\n\n    std::vector<int> result(n, -1);\n\
    \    result[root] = root;\n    for (int vertex = 0; vertex < n; ++vertex) {\n\
    \        if (!reachable[vertex] || vertex == root) continue;\n        for (int\
    \ candidate = 0; candidate < n; ++candidate) {\n            if (\n           \
    \     candidate == vertex ||\n                !dominator[vertex][candidate]\n\
    \            ) {\n                continue;\n            }\n            bool immediate\
    \ = true;\n            for (int other = 0; other < n; ++other) {\n           \
    \     if (\n                    other == vertex ||\n                    other\
    \ == candidate ||\n                    !dominator[vertex][other]\n           \
    \     ) {\n                    continue;\n                }\n                if\
    \ (dominator[other][candidate]) {\n                    immediate = false;\n  \
    \                  break;\n                }\n            }\n            if (immediate)\
    \ {\n                result[vertex] = candidate;\n                break;\n   \
    \         }\n        }\n    }\n    return result;\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 1601;\n    auto random = [&state]() {\n       \
    \ state ^= state << 7;\n        state ^= state >> 9;\n        return state;\n\
    \    };\n\n    for (int trial = 0; trial < 5000; ++trial) {\n        int n = 1\
    \ + int(random() % 12);\n        m1une::graph::Graph<> graph(n);\n        for\
    \ (int from = 0; from < n; ++from) {\n            for (int to = 0; to < n; ++to)\
    \ {\n                if (random() % 5 == 0) {\n                    graph.add_directed_edge(from,\
    \ to);\n                }\n            }\n        }\n        int root = int(random()\
    \ % n);\n        auto actual = m1une::graph::dominator_tree(graph, root);\n  \
    \      auto expected = brute_idom(graph, root);\n        assert(actual.immediate_dominator\
    \ == expected);\n\n        for (int vertex = 0; vertex < n; ++vertex) {\n    \
    \        assert(actual.reachable(vertex) == (expected[vertex] != -1));\n     \
    \       for (int ancestor = 0; ancestor < n; ++ancestor) {\n                [[maybe_unused]]\
    \ bool dominates = false;\n                if (expected[vertex] != -1) {\n   \
    \                 for (\n                        int current = vertex;\n     \
    \                   current != -1;\n                        current = current\
    \ == root\n                            ? -1\n                            : expected[current]\n\
    \                    ) {\n                        if (current == ancestor) dominates\
    \ = true;\n                    }\n                }\n                assert(actual.dominates(ancestor,\
    \ vertex) == dominates);\n            }\n        }\n    }\n}\n\nvoid test_long_path()\
    \ {\n    constexpr int n = 200000;\n    m1une::graph::Graph<> graph(n);\n    for\
    \ (int vertex = 1; vertex < n; ++vertex) {\n        graph.add_directed_edge(vertex\
    \ - 1, vertex);\n    }\n    auto result = m1une::graph::dominator_tree(graph,\
    \ 0);\n    assert(result.immediate_dominator[n - 1] == n - 2);\n    assert(result.dominates(0,\
    \ n - 1));\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n   \
    \ test_long_path();\n\n    int n, m, root;\n    std::cin >> n >> m >> root;\n\
    \    m1une::graph::Graph<> graph(n);\n    while (m--) {\n        int from, to;\n\
    \        std::cin >> from >> to;\n        graph.add_directed_edge(from, to);\n\
    \    }\n    auto result = m1une::graph::dominator_tree(graph, root);\n    for\
    \ (int vertex = 0; vertex < n; ++vertex) {\n        if (vertex) std::cout << '\
    \ ';\n        std::cout << result.immediate_dominator[vertex];\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  dependsOn:
  - graph/dominator_tree.hpp
  - graph/graph.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/graph/dominator_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 03:14:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/dominator_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/dominator_tree.test.cpp
- /verify/verify/graph/dominator_tree.test.cpp.html
title: verify/graph/dominator_tree.test.cpp
---
