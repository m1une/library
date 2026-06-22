---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: graph/graph.hpp
    title: Graph
  - icon: ':heavy_check_mark:'
    path: tree/dsu_on_tree.hpp
    title: DSU on Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/tree/dsu_on_tree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#line 1 \"tree/dsu_on_tree.hpp\"\n\n\n\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 7 \"graph/graph.hpp\"\
    \n\nnamespace m1une {\nnamespace graph {\n\ntemplate <class T = int>\nstruct Edge\
    \ {\n    using cost_type = T;\n\n    int from;\n    int to;\n    T cost;\n   \
    \ int id;\n    bool alive;\n\n    Edge() : from(-1), to(-1), cost(T()), id(-1),\
    \ alive(true) {}\n    Edge(int from_, int to_, T cost_ = T(1), int id_ = -1, bool\
    \ alive_ = true)\n        : from(from_), to(to_), cost(cost_), id(id_), alive(alive_)\
    \ {}\n\n    int other(int v) const {\n        assert(v == from || v == to);\n\
    \        return from ^ to ^ v;\n    }\n};\n\ntemplate <class T = int>\nstruct\
    \ Graph {\n    using edge_type = Edge<T>;\n    using cost_type = T;\n\n   private:\n\
    \    int _n;\n    int _edge_count;\n    std::vector<std::vector<edge_type>> _g;\n\
    \    std::vector<std::vector<std::pair<int, int>>> _edge_positions;\n\n   public:\n\
    \    Graph() : _n(0), _edge_count(0) {}\n    explicit Graph(int n) : _n(n), _edge_count(0),\
    \ _g(n) {\n        assert(0 <= n);\n    }\n\n    int size() const {\n        return\
    \ _n;\n    }\n\n    bool empty() const {\n        return _n == 0;\n    }\n\n \
    \   int edge_count() const {\n        return _edge_count;\n    }\n\n    int add_vertex()\
    \ {\n        _g.emplace_back();\n        return _n++;\n    }\n\n    int add_directed_edge(int\
    \ from, int to, T cost = T(1)) {\n        assert(0 <= from && from < _n);\n  \
    \      assert(0 <= to && to < _n);\n        int id = _edge_count++;\n        int\
    \ idx = int(_g[from].size());\n        _g[from].push_back(edge_type(from, to,\
    \ cost, id));\n        _edge_positions.emplace_back();\n        _edge_positions.back().push_back({from,\
    \ idx});\n        return id;\n    }\n\n    int add_edge(int u, int v, T cost =\
    \ T(1)) {\n        assert(0 <= u && u < _n);\n        assert(0 <= v && v < _n);\n\
    \        int id = _edge_count++;\n        int u_idx = int(_g[u].size());\n   \
    \     int v_idx = int(_g[v].size());\n        _g[u].push_back(edge_type(u, v,\
    \ cost, id));\n        _g[v].push_back(edge_type(v, u, cost, id));\n        _edge_positions.emplace_back();\n\
    \        _edge_positions.back().push_back({u, u_idx});\n        _edge_positions.back().push_back({v,\
    \ v_idx});\n        return id;\n    }\n\n    void set_edge_alive(int id, bool\
    \ alive) {\n        assert(0 <= id && id < _edge_count);\n        for (auto [v,\
    \ idx] : _edge_positions[id]) {\n            _g[v][idx].alive = alive;\n     \
    \   }\n    }\n\n    void erase_edge(int id) {\n        set_edge_alive(id, false);\n\
    \    }\n\n    void revive_edge(int id) {\n        set_edge_alive(id, true);\n\
    \    }\n\n    bool is_edge_alive(int id) const {\n        assert(0 <= id && id\
    \ < _edge_count);\n        assert(!_edge_positions[id].empty());\n        auto\
    \ [v, idx] = _edge_positions[id][0];\n        return _g[v][idx].alive;\n    }\n\
    \n    const std::vector<edge_type>& operator[](int v) const {\n        assert(0\
    \ <= v && v < _n);\n        return _g[v];\n    }\n\n    std::vector<edge_type>&\
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
    \n}  // namespace tree\n}  // namespace m1une\n\n\n#line 4 \"verify/tree/dsu_on_tree.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/tree/dsu_on_tree.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#include <set>\n#line 11 \"verify/tree/dsu_on_tree.test.cpp\"\
    \n\n#line 13 \"verify/tree/dsu_on_tree.test.cpp\"\n\nnamespace {\n\nvoid check(\n\
    \    const m1une::graph::Graph<int>& graph,\n    const std::vector<int>& color,\n\
    \    int root\n) {\n    int n = graph.size();\n    m1une::tree::DsuOnTree<int>\
    \ dsu(graph, root);\n    assert(dsu.size() == n);\n    assert(dsu.root == root);\n\
    \n    std::vector<int> frequency(12, 0);\n    std::vector<int> answer(n, 0);\n\
    \    std::vector<int> active(n, 0);\n    int distinct = 0;\n\n    dsu.run(\n \
    \       [&](int vertex) {\n            assert(active[vertex] == 0);\n        \
    \    active[vertex] = 1;\n            if (frequency[color[vertex]]++ == 0) distinct++;\n\
    \        },\n        [&](int vertex) {\n            assert(active[vertex] == 1);\n\
    \            active[vertex] = 0;\n            if (--frequency[color[vertex]] ==\
    \ 0) distinct--;\n        },\n        [&](int vertex) {\n            answer[vertex]\
    \ = distinct;\n            for (int index = 0; index < n; ++index) {\n       \
    \         [[maybe_unused]] bool in_subtree =\n                    dsu.tin[vertex]\
    \ <= dsu.tin[index]\n                    && dsu.tin[index] < dsu.tout[vertex];\n\
    \                assert(bool(active[index]) == in_subtree);\n            }\n \
    \       }\n    );\n\n    for (int vertex = 0; vertex < n; ++vertex) {\n      \
    \  std::set<int> expected;\n        for (\n            int index = dsu.tin[vertex];\n\
    \            index < dsu.tout[vertex];\n            ++index\n        ) {\n   \
    \         expected.insert(color[dsu.order[index]]);\n        }\n        assert(answer[vertex]\
    \ == int(expected.size()));\n        assert(dsu.tout[vertex] - dsu.tin[vertex]\
    \ == dsu.subtree_size[vertex]);\n        if (dsu.heavy_child[vertex] != -1) {\n\
    \            for ([[maybe_unused]] int child : dsu.children[vertex]) {\n     \
    \           assert(\n                    dsu.subtree_size[child]\n           \
    \         <= dsu.subtree_size[dsu.heavy_child[vertex]]\n                );\n \
    \           }\n        }\n    }\n}\n\nvoid test_empty() {\n    m1une::graph::Graph<int>\
    \ graph(0);\n    m1une::tree::DsuOnTree<int> dsu(graph);\n    assert(dsu.empty());\n\
    \    dsu.run(\n        [](int) { assert(false); },\n        [](int) { assert(false);\
    \ },\n        [](int) { assert(false); }\n    );\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 401;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2500; ++trial) {\n        int n = 1 + int(random()\
    \ % 60);\n        m1une::graph::Graph<int> graph(n);\n        for (int vertex\
    \ = 1; vertex < n; ++vertex) {\n            graph.add_edge(vertex, int(random()\
    \ % vertex));\n        }\n        std::vector<int> color(n);\n        for (int&\
    \ value : color) value = int(random() % 12);\n        check(graph, color, int(random()\
    \ % n));\n    }\n}\n\nvoid test_long_path() {\n    constexpr int n = 200000;\n\
    \    m1une::graph::Graph<int> graph(n);\n    for (int vertex = 1; vertex < n;\
    \ ++vertex) {\n        graph.add_edge(vertex - 1, vertex);\n    }\n\n    m1une::tree::DsuOnTree<int>\
    \ dsu(graph);\n    int count = 0;\n    std::vector<int> answer(n);\n    dsu.run(\n\
    \        [&](int) { count++; },\n        [&](int) { count--; },\n        [&](int\
    \ vertex) { answer[vertex] = count; }\n    );\n    assert(answer[0] == n);\n \
    \   assert(answer[n - 1] == 1);\n}\n\n}  // namespace\n\nint main() {\n    test_empty();\n\
    \    test_randomized();\n    test_long_path();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../tree/dsu_on_tree.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <set>\n#include <vector>\n\n#include\
    \ \"../../graph/graph.hpp\"\n\nnamespace {\n\nvoid check(\n    const m1une::graph::Graph<int>&\
    \ graph,\n    const std::vector<int>& color,\n    int root\n) {\n    int n = graph.size();\n\
    \    m1une::tree::DsuOnTree<int> dsu(graph, root);\n    assert(dsu.size() == n);\n\
    \    assert(dsu.root == root);\n\n    std::vector<int> frequency(12, 0);\n   \
    \ std::vector<int> answer(n, 0);\n    std::vector<int> active(n, 0);\n    int\
    \ distinct = 0;\n\n    dsu.run(\n        [&](int vertex) {\n            assert(active[vertex]\
    \ == 0);\n            active[vertex] = 1;\n            if (frequency[color[vertex]]++\
    \ == 0) distinct++;\n        },\n        [&](int vertex) {\n            assert(active[vertex]\
    \ == 1);\n            active[vertex] = 0;\n            if (--frequency[color[vertex]]\
    \ == 0) distinct--;\n        },\n        [&](int vertex) {\n            answer[vertex]\
    \ = distinct;\n            for (int index = 0; index < n; ++index) {\n       \
    \         [[maybe_unused]] bool in_subtree =\n                    dsu.tin[vertex]\
    \ <= dsu.tin[index]\n                    && dsu.tin[index] < dsu.tout[vertex];\n\
    \                assert(bool(active[index]) == in_subtree);\n            }\n \
    \       }\n    );\n\n    for (int vertex = 0; vertex < n; ++vertex) {\n      \
    \  std::set<int> expected;\n        for (\n            int index = dsu.tin[vertex];\n\
    \            index < dsu.tout[vertex];\n            ++index\n        ) {\n   \
    \         expected.insert(color[dsu.order[index]]);\n        }\n        assert(answer[vertex]\
    \ == int(expected.size()));\n        assert(dsu.tout[vertex] - dsu.tin[vertex]\
    \ == dsu.subtree_size[vertex]);\n        if (dsu.heavy_child[vertex] != -1) {\n\
    \            for ([[maybe_unused]] int child : dsu.children[vertex]) {\n     \
    \           assert(\n                    dsu.subtree_size[child]\n           \
    \         <= dsu.subtree_size[dsu.heavy_child[vertex]]\n                );\n \
    \           }\n        }\n    }\n}\n\nvoid test_empty() {\n    m1une::graph::Graph<int>\
    \ graph(0);\n    m1une::tree::DsuOnTree<int> dsu(graph);\n    assert(dsu.empty());\n\
    \    dsu.run(\n        [](int) { assert(false); },\n        [](int) { assert(false);\
    \ },\n        [](int) { assert(false); }\n    );\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 401;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2500; ++trial) {\n        int n = 1 + int(random()\
    \ % 60);\n        m1une::graph::Graph<int> graph(n);\n        for (int vertex\
    \ = 1; vertex < n; ++vertex) {\n            graph.add_edge(vertex, int(random()\
    \ % vertex));\n        }\n        std::vector<int> color(n);\n        for (int&\
    \ value : color) value = int(random() % 12);\n        check(graph, color, int(random()\
    \ % n));\n    }\n}\n\nvoid test_long_path() {\n    constexpr int n = 200000;\n\
    \    m1une::graph::Graph<int> graph(n);\n    for (int vertex = 1; vertex < n;\
    \ ++vertex) {\n        graph.add_edge(vertex - 1, vertex);\n    }\n\n    m1une::tree::DsuOnTree<int>\
    \ dsu(graph);\n    int count = 0;\n    std::vector<int> answer(n);\n    dsu.run(\n\
    \        [&](int) { count++; },\n        [&](int) { count--; },\n        [&](int\
    \ vertex) { answer[vertex] = count; }\n    );\n    assert(answer[0] == n);\n \
    \   assert(answer[n - 1] == 1);\n}\n\n}  // namespace\n\nint main() {\n    test_empty();\n\
    \    test_randomized();\n    test_long_path();\n\n    long long a, b;\n    std::cin\
    \ >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - tree/dsu_on_tree.hpp
  - graph/graph.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/tree/dsu_on_tree.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:14:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/tree/dsu_on_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/tree/dsu_on_tree.test.cpp
- /verify/verify/tree/dsu_on_tree.test.cpp.html
title: verify/tree/dsu_on_tree.test.cpp
---
