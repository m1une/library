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
    path: tree/tree_hash.hpp
    title: Hash of Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification
    links:
    - https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification
  bundledCode: "#line 1 \"verify/tree/rooted_tree_isomorphism_classification.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <iostream>\n#include <numeric>\n#include <random>\n#include <string>\n#include\
    \ <vector>\n\n#line 1 \"graph/graph.hpp\"\n\n\n\n#line 5 \"graph/graph.hpp\"\n\
    #include <utility>\n#line 7 \"graph/graph.hpp\"\n\nnamespace m1une {\nnamespace\
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
    \ m1une\n\n\n#line 1 \"tree/tree_hash.hpp\"\n\n\n\n#line 5 \"tree/tree_hash.hpp\"\
    \n#include <array>\n#line 7 \"tree/tree_hash.hpp\"\n#include <cstdint>\n#line\
    \ 9 \"tree/tree_hash.hpp\"\n\n#line 11 \"tree/tree_hash.hpp\"\n\nnamespace m1une\
    \ {\nnamespace tree {\n\nusing TreeHashValue = std::array<std::uint64_t, 2>;\n\
    \nclass TreeHasher {\n   private:\n    static constexpr std::uint64_t mod = (std::uint64_t(1)\
    \ << 61) - 1;\n    std::uint64_t _seed;\n\n    static std::uint64_t splitmix64(std::uint64_t\
    \ x) {\n        x += 0x9e3779b97f4a7c15ULL;\n        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;\n\
    \        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;\n        return x ^ (x >>\
    \ 31);\n    }\n\n    static std::uint64_t mul_mod(std::uint64_t a, std::uint64_t\
    \ b) {\n        __uint128_t product = static_cast<__uint128_t>(a) * b;\n     \
    \   std::uint64_t result = std::uint64_t(product & mod) + std::uint64_t(product\
    \ >> 61);\n        if (mod <= result) result -= mod;\n        return result;\n\
    \    }\n\n    static std::uint64_t add_mod(std::uint64_t a, std::uint64_t b) {\n\
    \        std::uint64_t result = a + b;\n        if (mod <= result) result -= mod;\n\
    \        return result;\n    }\n\n    TreeHashValue salt(int height) const {\n\
    \        std::uint64_t x = static_cast<std::uint64_t>(height);\n        std::uint64_t\
    \ first = splitmix64(_seed ^ (x + 0x243f6a8885a308d3ULL));\n        std::uint64_t\
    \ second = splitmix64(_seed ^ (x + 0x13198a2e03707344ULL));\n        return {first\
    \ % (mod - 1) + 1, second % (mod - 1) + 1};\n    }\n\n    template <class T>\n\
    \    static std::vector<int> tree_centers(const m1une::graph::Graph<T>& g) {\n\
    \        int n = g.size();\n        if (n == 0) return {};\n\n        std::vector<int>\
    \ degree(n, 0);\n        std::vector<int> queue;\n        queue.reserve(n);\n\
    \        long long active_arcs = 0;\n        for (int v = 0; v < n; v++) {\n \
    \           for (const auto& e : g[v]) {\n                if (!e.alive) continue;\n\
    \                degree[v]++;\n                active_arcs++;\n            }\n\
    \            if (degree[v] <= 1) queue.push_back(v);\n        }\n        assert(active_arcs\
    \ == 2LL * (n - 1));\n\n        std::vector<char> removed(n, false);\n       \
    \ int remaining = n;\n        int head = 0;\n        while (2 < remaining) {\n\
    \            int layer_end = int(queue.size());\n            assert(head < layer_end);\n\
    \            remaining -= layer_end - head;\n            while (head < layer_end)\
    \ {\n                int v = queue[head++];\n                removed[v] = true;\n\
    \                for (const auto& e : g[v]) {\n                    if (!e.alive\
    \ || removed[e.to]) continue;\n                    if (--degree[e.to] == 1) queue.push_back(e.to);\n\
    \                }\n            }\n        }\n\n        std::vector<int> centers;\n\
    \        for (int v = 0; v < n; v++) {\n            if (!removed[v]) centers.push_back(v);\n\
    \        }\n        assert(1 <= int(centers.size()) && int(centers.size()) <=\
    \ 2);\n        return centers;\n    }\n\n   public:\n    explicit TreeHasher(std::uint64_t\
    \ seed = 0x6a09e667f3bcc909ULL) : _seed(seed) {}\n\n    std::uint64_t seed() const\
    \ {\n        return _seed;\n    }\n\n    template <class T>\n    std::vector<TreeHashValue>\
    \ hash_subtrees(const m1une::graph::Graph<T>& g, int root = 0) const {\n     \
    \   int n = g.size();\n        if (n == 0) return {};\n        assert(0 <= root\
    \ && root < n);\n\n        std::vector<int> parent(n, -1);\n        std::vector<int>\
    \ order;\n        order.reserve(n);\n        parent[root] = root;\n        order.push_back(root);\n\
    \        long long active_arcs = 0;\n        for (int v = 0; v < n; v++) {\n \
    \           for (const auto& e : g[v]) active_arcs += e.alive;\n        }\n  \
    \      assert(active_arcs == 2LL * (n - 1));\n\n        for (int i = 0; i < int(order.size());\
    \ i++) {\n            int v = order[i];\n            for (const auto& e : g[v])\
    \ {\n                if (!e.alive || parent[e.to] != -1) continue;\n         \
    \       parent[e.to] = v;\n                order.push_back(e.to);\n          \
    \  }\n        }\n        assert(int(order.size()) == n);\n\n        std::vector<int>\
    \ height(n, 0);\n        std::vector<TreeHashValue> result(n, TreeHashValue{1,\
    \ 1});\n        for (int i = n - 1; i >= 0; i--) {\n            int v = order[i];\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive || parent[e.to]\
    \ != v) continue;\n                height[v] = std::max(height[v], height[e.to]\
    \ + 1);\n            }\n            TreeHashValue random = salt(height[v]);\n\
    \            for (const auto& e : g[v]) {\n                if (!e.alive || parent[e.to]\
    \ != v) continue;\n                result[v][0] = mul_mod(result[v][0], add_mod(result[e.to][0],\
    \ random[0]));\n                result[v][1] = mul_mod(result[v][1], add_mod(result[e.to][1],\
    \ random[1]));\n            }\n        }\n        return result;\n    }\n\n  \
    \  template <class T>\n    TreeHashValue hash_rooted(const m1une::graph::Graph<T>&\
    \ g, int root = 0) const {\n        if (g.empty()) return {0, 0};\n        return\
    \ hash_subtrees(g, root)[root];\n    }\n\n    template <class T>\n    std::vector<TreeHashValue>\
    \ hash_unrooted(const m1une::graph::Graph<T>& g) const {\n        std::vector<int>\
    \ centers = tree_centers(g);\n        std::vector<TreeHashValue> result;\n   \
    \     result.reserve(centers.size());\n        for (int center : centers) result.push_back(hash_rooted(g,\
    \ center));\n        std::sort(result.begin(), result.end());\n        return\
    \ result;\n    }\n};\n\n}  // namespace tree\n}  // namespace m1une\n\n\n#line\
    \ 14 \"verify/tree/rooted_tree_isomorphism_classification.test.cpp\"\n\nusing\
    \ m1une::graph::Graph;\nusing m1une::tree::TreeHasher;\n\nvoid randomized_test()\
    \ {\n    std::mt19937 random(123456789);\n    TreeHasher hasher(987654321);\n\
    \    for (int test = 0; test < 200; test++) {\n        int n = 1 + random() %\
    \ 30;\n        Graph<int> g(n);\n        std::vector<std::vector<int>> children(n);\n\
    \        std::vector<int> parent(n, -1);\n        for (int v = 1; v < n; v++)\
    \ {\n            int p = random() % v;\n            parent[v] = p;\n         \
    \   g.add_edge(p, v);\n            children[p].push_back(v);\n        }\n\n  \
    \      std::vector<std::string> canonical(n);\n        std::function<std::string(int)>\
    \ encode = [&](int v) {\n            std::vector<std::string> parts;\n       \
    \     for (int child : children[v]) parts.push_back(encode(child));\n        \
    \    std::sort(parts.begin(), parts.end());\n            std::string result =\
    \ \"(\";\n            for (const auto& part : parts) result += part;\n       \
    \     result += \")\";\n            return canonical[v] = result;\n        };\n\
    \        encode(0);\n\n        auto hash = hasher.hash_subtrees(g, 0);\n     \
    \   for (int u = 0; u < n; u++) {\n            for (int v = 0; v < n; v++) {\n\
    \                assert((hash[u] == hash[v]) == (canonical[u] == canonical[v]));\n\
    \            }\n        }\n\n        std::vector<int> permutation(n);\n      \
    \  std::iota(permutation.begin(), permutation.end(), 0);\n        std::shuffle(permutation.begin(),\
    \ permutation.end(), random);\n        Graph<int> relabeled(n);\n        for (int\
    \ v = 1; v < n; v++) {\n            relabeled.add_edge(permutation[parent[v]],\
    \ permutation[v]);\n        }\n        assert(hasher.hash_rooted(g, 0) == hasher.hash_rooted(relabeled,\
    \ permutation[0]));\n        assert(hasher.hash_unrooted(g) == hasher.hash_unrooted(relabeled));\n\
    \    }\n}\n\nint main() {\n    randomized_test();\n\n    int n;\n    std::cin\
    \ >> n;\n    Graph<int> g(n);\n    for (int v = 1; v < n; v++) {\n        int\
    \ parent;\n        std::cin >> parent;\n        g.add_edge(parent, v);\n    }\n\
    \n    auto hash = TreeHasher().hash_subtrees(g, 0);\n    std::vector<int> order(n);\n\
    \    std::iota(order.begin(), order.end(), 0);\n    std::sort(order.begin(), order.end(),\
    \ [&](int u, int v) {\n        return hash[u] < hash[v];\n    });\n\n    int classes\
    \ = 0;\n    std::vector<int> label(n);\n    for (int i = 0; i < n; i++) {\n  \
    \      if (i == 0 || hash[order[i - 1]] != hash[order[i]]) classes++;\n      \
    \  label[order[i]] = classes - 1;\n    }\n\n    std::cout << classes << '\\n';\n\
    \    for (int v = 0; v < n; v++) {\n        if (v != 0) std::cout << ' ';\n  \
    \      std::cout << label[v];\n    }\n    std::cout << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n#include\
    \ <iostream>\n#include <numeric>\n#include <random>\n#include <string>\n#include\
    \ <vector>\n\n#include \"../../graph/graph.hpp\"\n#include \"../../tree/tree_hash.hpp\"\
    \n\nusing m1une::graph::Graph;\nusing m1une::tree::TreeHasher;\n\nvoid randomized_test()\
    \ {\n    std::mt19937 random(123456789);\n    TreeHasher hasher(987654321);\n\
    \    for (int test = 0; test < 200; test++) {\n        int n = 1 + random() %\
    \ 30;\n        Graph<int> g(n);\n        std::vector<std::vector<int>> children(n);\n\
    \        std::vector<int> parent(n, -1);\n        for (int v = 1; v < n; v++)\
    \ {\n            int p = random() % v;\n            parent[v] = p;\n         \
    \   g.add_edge(p, v);\n            children[p].push_back(v);\n        }\n\n  \
    \      std::vector<std::string> canonical(n);\n        std::function<std::string(int)>\
    \ encode = [&](int v) {\n            std::vector<std::string> parts;\n       \
    \     for (int child : children[v]) parts.push_back(encode(child));\n        \
    \    std::sort(parts.begin(), parts.end());\n            std::string result =\
    \ \"(\";\n            for (const auto& part : parts) result += part;\n       \
    \     result += \")\";\n            return canonical[v] = result;\n        };\n\
    \        encode(0);\n\n        auto hash = hasher.hash_subtrees(g, 0);\n     \
    \   for (int u = 0; u < n; u++) {\n            for (int v = 0; v < n; v++) {\n\
    \                assert((hash[u] == hash[v]) == (canonical[u] == canonical[v]));\n\
    \            }\n        }\n\n        std::vector<int> permutation(n);\n      \
    \  std::iota(permutation.begin(), permutation.end(), 0);\n        std::shuffle(permutation.begin(),\
    \ permutation.end(), random);\n        Graph<int> relabeled(n);\n        for (int\
    \ v = 1; v < n; v++) {\n            relabeled.add_edge(permutation[parent[v]],\
    \ permutation[v]);\n        }\n        assert(hasher.hash_rooted(g, 0) == hasher.hash_rooted(relabeled,\
    \ permutation[0]));\n        assert(hasher.hash_unrooted(g) == hasher.hash_unrooted(relabeled));\n\
    \    }\n}\n\nint main() {\n    randomized_test();\n\n    int n;\n    std::cin\
    \ >> n;\n    Graph<int> g(n);\n    for (int v = 1; v < n; v++) {\n        int\
    \ parent;\n        std::cin >> parent;\n        g.add_edge(parent, v);\n    }\n\
    \n    auto hash = TreeHasher().hash_subtrees(g, 0);\n    std::vector<int> order(n);\n\
    \    std::iota(order.begin(), order.end(), 0);\n    std::sort(order.begin(), order.end(),\
    \ [&](int u, int v) {\n        return hash[u] < hash[v];\n    });\n\n    int classes\
    \ = 0;\n    std::vector<int> label(n);\n    for (int i = 0; i < n; i++) {\n  \
    \      if (i == 0 || hash[order[i - 1]] != hash[order[i]]) classes++;\n      \
    \  label[order[i]] = classes - 1;\n    }\n\n    std::cout << classes << '\\n';\n\
    \    for (int v = 0; v < n; v++) {\n        if (v != 0) std::cout << ' ';\n  \
    \      std::cout << label[v];\n    }\n    std::cout << '\\n';\n}\n"
  dependsOn:
  - graph/graph.hpp
  - tree/tree_hash.hpp
  - graph/graph.hpp
  isVerificationFile: true
  path: verify/tree/rooted_tree_isomorphism_classification.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 13:39:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/tree/rooted_tree_isomorphism_classification.test.cpp
layout: document
redirect_from:
- /verify/verify/tree/rooted_tree_isomorphism_classification.test.cpp
- /verify/verify/tree/rooted_tree_isomorphism_classification.test.cpp.html
title: verify/tree/rooted_tree_isomorphism_classification.test.cpp
---
