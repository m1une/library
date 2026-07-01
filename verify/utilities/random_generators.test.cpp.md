---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/random.hpp
    title: Random
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
  bundledCode: "#line 1 \"verify/utilities/random_generators.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"utilities/random.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <cassert>\n#include <chrono>\n#include\
    \ <concepts>\n#include <cstdint>\n#include <functional>\n#include <numeric>\n\
    #include <queue>\n#include <random>\n#include <string>\n#include <string_view>\n\
    #include <tuple>\n#include <type_traits>\n#include <unordered_set>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\nstruct RandomGraphOptions\
    \ {\n    bool directed = false;\n    bool allow_self_loops = false;\n    bool\
    \ allow_parallel_edges = false;\n};\n\nstruct Random {\n   private:\n    std::mt19937_64\
    \ _engine;\n\n    static unsigned long long chrono_seed() {\n        return static_cast<unsigned\
    \ long long>(\n            std::chrono::steady_clock::now().time_since_epoch().count());\n\
    \    }\n\n    static std::uint64_t graph_edge_count(int vertex_count,\n      \
    \                                    const RandomGraphOptions& options) {\n  \
    \      std::uint64_t n = static_cast<unsigned int>(vertex_count);\n        if\
    \ (options.directed) {\n            return options.allow_self_loops ? n * n :\
    \ n * (n - 1);\n        }\n        return options.allow_self_loops ? n * (n +\
    \ 1) / 2 : n * (n - 1) / 2;\n    }\n\n    static std::pair<int, int> decode_graph_edge(\n\
    \        std::uint64_t index, int vertex_count,\n        const RandomGraphOptions&\
    \ options) {\n        std::uint64_t n = static_cast<unsigned int>(vertex_count);\n\
    \        if (options.directed) {\n            std::uint64_t width = options.allow_self_loops\
    \ ? n : n - 1;\n            int from = int(index / width);\n            int offset\
    \ = int(index % width);\n            int to = options.allow_self_loops || offset\
    \ < from ? offset : offset + 1;\n            return {from, to};\n        }\n\n\
    \        auto prefix = [&](std::uint64_t vertex) {\n            if (options.allow_self_loops)\
    \ {\n                return vertex * (2 * n - vertex + 1) / 2;\n            }\n\
    \            return vertex * (2 * n - vertex - 1) / 2;\n        };\n        std::uint64_t\
    \ low = 0;\n        std::uint64_t high = n;\n        while (low + 1 < high) {\n\
    \            std::uint64_t middle = (low + high) / 2;\n            if (prefix(middle)\
    \ <= index) {\n                low = middle;\n            } else {\n         \
    \       high = middle;\n            }\n        }\n        int from = int(low);\n\
    \        int to = from + int(index - prefix(low)) +\n                 (options.allow_self_loops\
    \ ? 0 : 1);\n        return {from, to};\n    }\n\n   public:\n    Random() : _engine(chrono_seed())\
    \ {}\n    explicit Random(unsigned long long seed) : _engine(seed) {}\n\n    void\
    \ seed(unsigned long long value) {\n        _engine.seed(value);\n    }\n\n  \
    \  std::mt19937_64& engine() {\n        return _engine;\n    }\n\n    unsigned\
    \ long long operator()() {\n        return _engine();\n    }\n\n    long long\
    \ uniform(long long l, long long r) {\n        return std::uniform_int_distribution<long\
    \ long>(l, r)(_engine);\n    }\n\n    unsigned long long uniform_unsigned(unsigned\
    \ long long l, unsigned long long r) {\n        return std::uniform_int_distribution<unsigned\
    \ long long>(l, r)(_engine);\n    }\n\n    double real(double l = 0.0, double\
    \ r = 1.0) {\n        return std::uniform_real_distribution<double>(l, r)(_engine);\n\
    \    }\n\n    template <std::integral T>\n    requires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\n    std::vector<T> sequence(int size, T lower, T upper) {\n        assert(0\
    \ <= size);\n        assert(lower <= upper);\n        if (size < 0 || upper <\
    \ lower) return {};\n        std::vector<T> result(size);\n        if constexpr\
    \ (std::signed_integral<T>) {\n            std::uniform_int_distribution<long\
    \ long> distribution(\n                static_cast<long long>(lower), static_cast<long\
    \ long>(upper));\n            for (T& value : result) value = static_cast<T>(distribution(_engine));\n\
    \        } else {\n            std::uniform_int_distribution<unsigned long long>\
    \ distribution(\n                static_cast<unsigned long long>(lower),\n   \
    \             static_cast<unsigned long long>(upper));\n            for (T& value\
    \ : result) value = static_cast<T>(distribution(_engine));\n        }\n      \
    \  return result;\n    }\n\n    std::string string(\n        int length,\n   \
    \     std::string_view alphabet = \"abcdefghijklmnopqrstuvwxyz\") {\n        assert(0\
    \ <= length);\n        assert(length == 0 || !alphabet.empty());\n        if (length\
    \ < 0 || (0 < length && alphabet.empty())) return {};\n        std::string result(length,\
    \ '\\0');\n        for (char& character : result) {\n            character = alphabet[uniform(0,\
    \ int(alphabet.size()) - 1)];\n        }\n        return result;\n    }\n\n  \
    \  std::vector<int> permutation(int size, int first = 0) {\n        assert(0 <=\
    \ size);\n        if (size < 0) return {};\n        std::vector<int> result(size);\n\
    \        std::iota(result.begin(), result.end(), first);\n        shuffle(result);\n\
    \        return result;\n    }\n\n    // Returns the edges of a uniformly random\
    \ labeled tree on [0, size).\n    std::vector<std::pair<int, int>> tree(int size)\
    \ {\n        assert(0 <= size);\n        if (size <= 1) return {};\n\n       \
    \ std::vector<int> prufer = sequence(size - 2, 0, size - 1);\n        std::vector<int>\
    \ degree(size, 1);\n        for (int vertex : prufer) degree[vertex]++;\n    \
    \    std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;\n \
    \       for (int vertex = 0; vertex < size; vertex++) {\n            if (degree[vertex]\
    \ == 1) leaves.push(vertex);\n        }\n\n        std::vector<std::pair<int,\
    \ int>> edges;\n        edges.reserve(size - 1);\n        for (int vertex : prufer)\
    \ {\n            int leaf = leaves.top();\n            leaves.pop();\n       \
    \     edges.emplace_back(leaf, vertex);\n            if (--degree[vertex] == 1)\
    \ leaves.push(vertex);\n        }\n        int first = leaves.top();\n       \
    \ leaves.pop();\n        edges.emplace_back(first, leaves.top());\n\n        shuffle(edges);\n\
    \        for (auto& [from, to] : edges) {\n            if (uniform(0, 1)) std::swap(from,\
    \ to);\n        }\n        return edges;\n    }\n\n    // Returns m random edges\
    \ on [0, vertex_count). By default the result is\n    // a simple undirected graph\
    \ without self-loops.\n    std::vector<std::pair<int, int>> graph(\n        int\
    \ vertex_count, int edge_count,\n        RandomGraphOptions options = {}) {\n\
    \        assert(0 <= vertex_count);\n        assert(0 <= edge_count);\n      \
    \  if (vertex_count < 0 || edge_count < 0) return {};\n        if (edge_count\
    \ == 0) return {};\n        assert(0 < vertex_count);\n        if (vertex_count\
    \ == 0) return {};\n        if (!options.allow_self_loops) {\n            assert(2\
    \ <= vertex_count || edge_count == 0);\n            if (vertex_count < 2) return\
    \ {};\n        }\n\n        std::vector<std::pair<int, int>> edges;\n        edges.reserve(edge_count);\n\
    \        if (options.allow_parallel_edges) {\n            for (int edge = 0; edge\
    \ < edge_count; edge++) {\n                int from = int(uniform(0, vertex_count\
    \ - 1));\n                int to;\n                if (options.allow_self_loops)\
    \ {\n                    to = int(uniform(0, vertex_count - 1));\n           \
    \     } else {\n                    to = int(uniform(0, vertex_count - 2));\n\
    \                    if (from <= to) to++;\n                }\n              \
    \  if (!options.directed && to < from) std::swap(from, to);\n                edges.emplace_back(from,\
    \ to);\n            }\n            return edges;\n        }\n\n        std::uint64_t\
    \ maximum = graph_edge_count(vertex_count, options);\n        assert(static_cast<std::uint64_t>(edge_count)\
    \ <= maximum);\n        if (maximum < static_cast<std::uint64_t>(edge_count))\
    \ return {};\n\n        std::unordered_set<std::uint64_t> selected;\n        selected.reserve(static_cast<std::size_t>(edge_count)\
    \ * 2 + 1);\n        std::vector<std::uint64_t> indices;\n        indices.reserve(edge_count);\n\
    \        for (std::uint64_t current = maximum - edge_count;\n             current\
    \ < maximum; current++) {\n            std::uint64_t candidate = uniform_unsigned(0,\
    \ current);\n            if (selected.contains(candidate)) candidate = current;\n\
    \            selected.insert(candidate);\n            indices.push_back(candidate);\n\
    \        }\n        for (std::uint64_t index : indices) {\n            edges.push_back(decode_graph_edge(index,\
    \ vertex_count, options));\n        }\n        return edges;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> directed_graph(\n        int vertex_count, int edge_count,\n        bool\
    \ allow_self_loops = false) {\n        RandomGraphOptions options;\n        options.allow_self_loops\
    \ = allow_self_loops;\n        return directed_graph(vertex_count, edge_count,\
    \ options);\n    }\n\n    std::vector<std::pair<int, int>> directed_graph(\n \
    \       int vertex_count, int edge_count, RandomGraphOptions options) {\n    \
    \    options.directed = true;\n        return graph(vertex_count, edge_count,\
    \ options);\n    }\n\n    // Returns a directed acyclic graph. Vertices are randomly\
    \ permuted before\n    // every sampled edge is directed forward in that topological\
    \ order.\n    std::vector<std::pair<int, int>> dag(\n        int vertex_count,\
    \ int edge_count,\n        RandomGraphOptions options = {}) {\n        options.directed\
    \ = false;\n        options.allow_self_loops = false;\n        std::vector<std::pair<int,\
    \ int>> edges =\n            graph(vertex_count, edge_count, options);\n     \
    \   std::vector<int> order = permutation(vertex_count);\n        for (auto& [from,\
    \ to] : edges) {\n            from = order[from];\n            to = order[to];\n\
    \        }\n        return edges;\n    }\n\n    template <std::integral Weight>\n\
    \    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)\n    std::vector<std::tuple<int,\
    \ int, Weight>> weighted_tree(\n        int size, Weight lower, Weight upper)\
    \ {\n        std::vector<std::pair<int, int>> edges = tree(size);\n        std::vector<Weight>\
    \ weights = sequence(int(edges.size()), lower, upper);\n        std::vector<std::tuple<int,\
    \ int, Weight>> result;\n        result.reserve(edges.size());\n        for (int\
    \ index = 0; index < int(edges.size()); index++) {\n            result.emplace_back(edges[index].first,\
    \ edges[index].second,\n                                weights[index]);\n   \
    \     }\n        return result;\n    }\n\n    template <std::integral Weight>\n\
    \    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)\n    std::vector<std::tuple<int,\
    \ int, Weight>> weighted_graph(\n        int vertex_count, int edge_count, Weight\
    \ lower, Weight upper,\n        RandomGraphOptions options = {}) {\n        std::vector<std::pair<int,\
    \ int>> edges =\n            graph(vertex_count, edge_count, options);\n     \
    \   std::vector<Weight> weights = sequence(int(edges.size()), lower, upper);\n\
    \        std::vector<std::tuple<int, int, Weight>> result;\n        result.reserve(edges.size());\n\
    \        for (int index = 0; index < int(edges.size()); index++) {\n         \
    \   result.emplace_back(edges[index].first, edges[index].second,\n           \
    \                     weights[index]);\n        }\n        return result;\n  \
    \  }\n\n    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(\n\
    \        int vertex_count, int edge_count, Weight lower, Weight upper,\n     \
    \   bool allow_self_loops = false) {\n        RandomGraphOptions options;\n  \
    \      options.allow_self_loops = allow_self_loops;\n        return weighted_directed_graph(vertex_count,\
    \ edge_count, lower, upper,\n                                       options);\n\
    \    }\n\n    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(\n\
    \        int vertex_count, int edge_count, Weight lower, Weight upper,\n     \
    \   RandomGraphOptions options) {\n        options.directed = true;\n        return\
    \ weighted_graph(vertex_count, edge_count, lower, upper, options);\n    }\n\n\
    \    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_dag(\n      \
    \  int vertex_count, int edge_count, Weight lower, Weight upper,\n        RandomGraphOptions\
    \ options = {}) {\n        std::vector<std::pair<int, int>> edges =\n        \
    \    dag(vertex_count, edge_count, options);\n        std::vector<Weight> weights\
    \ = sequence(int(edges.size()), lower, upper);\n        std::vector<std::tuple<int,\
    \ int, Weight>> result;\n        result.reserve(edges.size());\n        for (int\
    \ index = 0; index < int(edges.size()); index++) {\n            result.emplace_back(edges[index].first,\
    \ edges[index].second,\n                                weights[index]);\n   \
    \     }\n        return result;\n    }\n\n    template <typename T>\n    void\
    \ shuffle(std::vector<T>& v) {\n        std::shuffle(v.begin(), v.end(), _engine);\n\
    \    }\n\n    template <typename Iterator>\n    void shuffle(Iterator first, Iterator\
    \ last) {\n        std::shuffle(first, last, _engine);\n    }\n\n    template\
    \ <typename T>\n    const T& choice(const std::vector<T>& v) {\n        return\
    \ v[uniform(0, static_cast<long long>(v.size()) - 1)];\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 4 \"verify/utilities/random_generators.test.cpp\"\
    \n\n#line 7 \"verify/utilities/random_generators.test.cpp\"\n#include <iostream>\n\
    #line 9 \"verify/utilities/random_generators.test.cpp\"\n#include <set>\n#line\
    \ 14 \"verify/utilities/random_generators.test.cpp\"\n\n#ifndef NDEBUG\nnamespace\
    \ {\n\nstruct Dsu {\n    std::vector<int> parent;\n\n    explicit Dsu(int size)\
    \ : parent(size, -1) {}\n\n    int leader(int vertex) {\n        if (parent[vertex]\
    \ < 0) return vertex;\n        return parent[vertex] = leader(parent[vertex]);\n\
    \    }\n\n    bool merge(int first, int second) {\n        first = leader(first);\n\
    \        second = leader(second);\n        if (first == second) return false;\n\
    \        if (parent[second] < parent[first]) std::swap(first, second);\n     \
    \   parent[first] += parent[second];\n        parent[second] = first;\n      \
    \  return true;\n    }\n};\n\nvoid test_basic_generators() {\n    m1une::utilities::Random\
    \ first(123456);\n    m1une::utilities::Random second(123456);\n    assert(first.sequence(100,\
    \ -10, 20) == second.sequence(100, -10, 20));\n    assert(first.string(100, \"\
    abc\") == second.string(100, \"abc\"));\n    assert(first.permutation(100) ==\
    \ second.permutation(100));\n    assert(first.tree(100) == second.tree(100));\n\
    \    assert(first.graph(100, 300) == second.graph(100, 300));\n\n    m1une::utilities::Random\
    \ random(998244353);\n    auto sequence = random.sequence(1000, -7LL, 11LL);\n\
    \    assert(sequence.size() == 1000);\n    for (long long value : sequence) assert(-7\
    \ <= value && value <= 11);\n\n    std::string text = random.string(1000, \"xyz\"\
    );\n    assert(text.size() == 1000);\n    for (char character : text) assert(character\
    \ == 'x' || character == 'y' || character == 'z');\n\n    std::vector<int> permutation\
    \ = random.permutation(100, 10);\n    std::sort(permutation.begin(), permutation.end());\n\
    \    for (int i = 0; i < 100; i++) assert(permutation[i] == i + 10);\n}\n\nvoid\
    \ test_trees() {\n    m1une::utilities::Random random(123);\n    assert(random.tree(0).empty());\n\
    \    assert(random.tree(1).empty());\n    for (int size = 2; size <= 200; size++)\
    \ {\n        auto edges = random.tree(size);\n        assert(int(edges.size())\
    \ == size - 1);\n        Dsu dsu(size);\n        for (auto [from, to] : edges)\
    \ {\n            assert(0 <= from && from < size);\n            assert(0 <= to\
    \ && to < size);\n            assert(from != to);\n            assert(dsu.merge(from,\
    \ to));\n        }\n        int root = dsu.leader(0);\n        for (int vertex\
    \ = 1; vertex < size; vertex++) assert(dsu.leader(vertex) == root);\n    }\n}\n\
    \nvoid test_graphs() {\n    m1une::utilities::Random random(456);\n    for (int\
    \ size = 2; size <= 50; size++) {\n        int maximum = size * (size - 1) / 2;\n\
    \        int edge_count = std::min(maximum, size * 3);\n        auto edges = random.graph(size,\
    \ edge_count);\n        assert(int(edges.size()) == edge_count);\n        std::set<std::pair<int,\
    \ int>> unique;\n        for (auto [from, to] : edges) {\n            assert(0\
    \ <= from && from < to && to < size);\n            unique.emplace(from, to);\n\
    \        }\n        assert(int(unique.size()) == edge_count);\n    }\n\n    auto\
    \ complete = random.graph(20, 190);\n    assert(complete.size() == 190);\n   \
    \ std::set<std::pair<int, int>> complete_unique(complete.begin(), complete.end());\n\
    \    assert(complete_unique.size() == 190);\n\n    auto directed = random.directed_graph(20,\
    \ 300);\n    std::set<std::pair<int, int>> directed_unique;\n    for (auto [from,\
    \ to] : directed) {\n        assert(0 <= from && from < 20);\n        assert(0\
    \ <= to && to < 20);\n        assert(from != to);\n        directed_unique.emplace(from,\
    \ to);\n    }\n    assert(directed_unique.size() == directed.size());\n\n    m1une::utilities::RandomGraphOptions\
    \ options;\n    options.allow_self_loops = true;\n    auto looped_complete = random.graph(5,\
    \ 15, options);\n    std::set<std::pair<int, int>> looped_unique;\n    for (auto\
    \ [from, to] : looped_complete) {\n        assert(0 <= from && from <= to && to\
    \ < 5);\n        looped_unique.emplace(from, to);\n    }\n    assert(looped_unique.size()\
    \ == 15);\n\n    options.directed = true;\n    auto directed_looped_complete =\
    \ random.graph(5, 25, options);\n    std::set<std::pair<int, int>> directed_looped_unique(\n\
    \        directed_looped_complete.begin(), directed_looped_complete.end());\n\
    \    assert(directed_looped_unique.size() == 25);\n\n    options.allow_parallel_edges\
    \ = true;\n    auto multigraph = random.graph(3, 1000, options);\n    assert(multigraph.size()\
    \ == 1000);\n    for (auto [from, to] : multigraph) {\n        assert(0 <= from\
    \ && from < 3);\n        assert(0 <= to && to < 3);\n    }\n}\n\nvoid test_weighted_graphs_and_dags()\
    \ {\n    m1une::utilities::Random random(789);\n\n    auto weighted_tree = random.weighted_tree(100,\
    \ -50LL, 70LL);\n    assert(weighted_tree.size() == 99);\n    Dsu dsu(100);\n\
    \    for (auto [from, to, weight] : weighted_tree) {\n        assert(-50 <= weight\
    \ && weight <= 70);\n        assert(dsu.merge(from, to));\n    }\n\n    auto weighted_graph\
    \ = random.weighted_graph(50, 300, -20, 30);\n    assert(weighted_graph.size()\
    \ == 300);\n    std::set<std::pair<int, int>> graph_edges;\n    for (auto [from,\
    \ to, weight] : weighted_graph) {\n        assert(0 <= from && from < to && to\
    \ < 50);\n        assert(-20 <= weight && weight <= 30);\n        graph_edges.emplace(from,\
    \ to);\n    }\n    assert(graph_edges.size() == 300);\n\n    for (int size = 2;\
    \ size <= 80; size++) {\n        int maximum = size * (size - 1) / 2;\n      \
    \  int edge_count = std::min(maximum, size * 4);\n        auto edges = random.dag(size,\
    \ edge_count);\n        assert(int(edges.size()) == edge_count);\n\n        std::vector<std::vector<int>>\
    \ adjacency(size);\n        std::vector<int> indegree(size);\n        std::set<std::pair<int,\
    \ int>> unique;\n        for (auto [from, to] : edges) {\n            assert(0\
    \ <= from && from < size);\n            assert(0 <= to && to < size);\n      \
    \      assert(from != to);\n            adjacency[from].push_back(to);\n     \
    \       indegree[to]++;\n            unique.emplace(from, to);\n        }\n  \
    \      assert(int(unique.size()) == edge_count);\n\n        std::vector<int> queue;\n\
    \        for (int vertex = 0; vertex < size; vertex++) {\n            if (indegree[vertex]\
    \ == 0) queue.push_back(vertex);\n        }\n        for (int head = 0; head <\
    \ int(queue.size()); head++) {\n            for (int next : adjacency[queue[head]])\
    \ {\n                if (--indegree[next] == 0) queue.push_back(next);\n     \
    \       }\n        }\n        assert(int(queue.size()) == size);\n    }\n\n  \
    \  auto weighted_dag = random.weighted_dag(100, 500, 1U, 100U);\n    assert(weighted_dag.size()\
    \ == 500);\n    for (auto [from, to, weight] : weighted_dag) {\n        assert(0\
    \ <= from && from < 100);\n        assert(0 <= to && to < 100);\n        assert(from\
    \ != to);\n        assert(1 <= weight && weight <= 100);\n    }\n\n    m1une::utilities::RandomGraphOptions\
    \ parallel_options;\n    parallel_options.allow_parallel_edges = true;\n    auto\
    \ parallel_dag = random.dag(2, 100, parallel_options);\n    assert(parallel_dag.size()\
    \ == 100);\n    for (auto edge : parallel_dag) assert(edge == parallel_dag.front());\n\
    \n    auto parallel_weighted_dag =\n        random.weighted_dag(2, 100, -3, 7,\
    \ parallel_options);\n    assert(parallel_weighted_dag.size() == 100);\n    for\
    \ (auto [from, to, weight] : parallel_weighted_dag) {\n        assert(from ==\
    \ std::get<0>(parallel_weighted_dag.front()));\n        assert(to == std::get<1>(parallel_weighted_dag.front()));\n\
    \        assert(-3 <= weight && weight <= 7);\n    }\n\n    parallel_options.allow_self_loops\
    \ = true;\n    auto parallel_directed = random.directed_graph(2, 100, parallel_options);\n\
    \    assert(parallel_directed.size() == 100);\n    auto parallel_weighted_directed\
    \ =\n        random.weighted_directed_graph(2, 100, 0LL, 10LL, parallel_options);\n\
    \    assert(parallel_weighted_directed.size() == 100);\n}\n\n}  // namespace\n\
    #endif\n\nint main() {\n#ifndef NDEBUG\n    test_basic_generators();\n    test_trees();\n\
    \    test_graphs();\n    test_weighted_graphs_and_dags();\n#endif\n\n    long\
    \ long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../utilities/random.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <iostream>\n#include <numeric>\n#include <set>\n#include <string>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\n#ifndef NDEBUG\nnamespace\
    \ {\n\nstruct Dsu {\n    std::vector<int> parent;\n\n    explicit Dsu(int size)\
    \ : parent(size, -1) {}\n\n    int leader(int vertex) {\n        if (parent[vertex]\
    \ < 0) return vertex;\n        return parent[vertex] = leader(parent[vertex]);\n\
    \    }\n\n    bool merge(int first, int second) {\n        first = leader(first);\n\
    \        second = leader(second);\n        if (first == second) return false;\n\
    \        if (parent[second] < parent[first]) std::swap(first, second);\n     \
    \   parent[first] += parent[second];\n        parent[second] = first;\n      \
    \  return true;\n    }\n};\n\nvoid test_basic_generators() {\n    m1une::utilities::Random\
    \ first(123456);\n    m1une::utilities::Random second(123456);\n    assert(first.sequence(100,\
    \ -10, 20) == second.sequence(100, -10, 20));\n    assert(first.string(100, \"\
    abc\") == second.string(100, \"abc\"));\n    assert(first.permutation(100) ==\
    \ second.permutation(100));\n    assert(first.tree(100) == second.tree(100));\n\
    \    assert(first.graph(100, 300) == second.graph(100, 300));\n\n    m1une::utilities::Random\
    \ random(998244353);\n    auto sequence = random.sequence(1000, -7LL, 11LL);\n\
    \    assert(sequence.size() == 1000);\n    for (long long value : sequence) assert(-7\
    \ <= value && value <= 11);\n\n    std::string text = random.string(1000, \"xyz\"\
    );\n    assert(text.size() == 1000);\n    for (char character : text) assert(character\
    \ == 'x' || character == 'y' || character == 'z');\n\n    std::vector<int> permutation\
    \ = random.permutation(100, 10);\n    std::sort(permutation.begin(), permutation.end());\n\
    \    for (int i = 0; i < 100; i++) assert(permutation[i] == i + 10);\n}\n\nvoid\
    \ test_trees() {\n    m1une::utilities::Random random(123);\n    assert(random.tree(0).empty());\n\
    \    assert(random.tree(1).empty());\n    for (int size = 2; size <= 200; size++)\
    \ {\n        auto edges = random.tree(size);\n        assert(int(edges.size())\
    \ == size - 1);\n        Dsu dsu(size);\n        for (auto [from, to] : edges)\
    \ {\n            assert(0 <= from && from < size);\n            assert(0 <= to\
    \ && to < size);\n            assert(from != to);\n            assert(dsu.merge(from,\
    \ to));\n        }\n        int root = dsu.leader(0);\n        for (int vertex\
    \ = 1; vertex < size; vertex++) assert(dsu.leader(vertex) == root);\n    }\n}\n\
    \nvoid test_graphs() {\n    m1une::utilities::Random random(456);\n    for (int\
    \ size = 2; size <= 50; size++) {\n        int maximum = size * (size - 1) / 2;\n\
    \        int edge_count = std::min(maximum, size * 3);\n        auto edges = random.graph(size,\
    \ edge_count);\n        assert(int(edges.size()) == edge_count);\n        std::set<std::pair<int,\
    \ int>> unique;\n        for (auto [from, to] : edges) {\n            assert(0\
    \ <= from && from < to && to < size);\n            unique.emplace(from, to);\n\
    \        }\n        assert(int(unique.size()) == edge_count);\n    }\n\n    auto\
    \ complete = random.graph(20, 190);\n    assert(complete.size() == 190);\n   \
    \ std::set<std::pair<int, int>> complete_unique(complete.begin(), complete.end());\n\
    \    assert(complete_unique.size() == 190);\n\n    auto directed = random.directed_graph(20,\
    \ 300);\n    std::set<std::pair<int, int>> directed_unique;\n    for (auto [from,\
    \ to] : directed) {\n        assert(0 <= from && from < 20);\n        assert(0\
    \ <= to && to < 20);\n        assert(from != to);\n        directed_unique.emplace(from,\
    \ to);\n    }\n    assert(directed_unique.size() == directed.size());\n\n    m1une::utilities::RandomGraphOptions\
    \ options;\n    options.allow_self_loops = true;\n    auto looped_complete = random.graph(5,\
    \ 15, options);\n    std::set<std::pair<int, int>> looped_unique;\n    for (auto\
    \ [from, to] : looped_complete) {\n        assert(0 <= from && from <= to && to\
    \ < 5);\n        looped_unique.emplace(from, to);\n    }\n    assert(looped_unique.size()\
    \ == 15);\n\n    options.directed = true;\n    auto directed_looped_complete =\
    \ random.graph(5, 25, options);\n    std::set<std::pair<int, int>> directed_looped_unique(\n\
    \        directed_looped_complete.begin(), directed_looped_complete.end());\n\
    \    assert(directed_looped_unique.size() == 25);\n\n    options.allow_parallel_edges\
    \ = true;\n    auto multigraph = random.graph(3, 1000, options);\n    assert(multigraph.size()\
    \ == 1000);\n    for (auto [from, to] : multigraph) {\n        assert(0 <= from\
    \ && from < 3);\n        assert(0 <= to && to < 3);\n    }\n}\n\nvoid test_weighted_graphs_and_dags()\
    \ {\n    m1une::utilities::Random random(789);\n\n    auto weighted_tree = random.weighted_tree(100,\
    \ -50LL, 70LL);\n    assert(weighted_tree.size() == 99);\n    Dsu dsu(100);\n\
    \    for (auto [from, to, weight] : weighted_tree) {\n        assert(-50 <= weight\
    \ && weight <= 70);\n        assert(dsu.merge(from, to));\n    }\n\n    auto weighted_graph\
    \ = random.weighted_graph(50, 300, -20, 30);\n    assert(weighted_graph.size()\
    \ == 300);\n    std::set<std::pair<int, int>> graph_edges;\n    for (auto [from,\
    \ to, weight] : weighted_graph) {\n        assert(0 <= from && from < to && to\
    \ < 50);\n        assert(-20 <= weight && weight <= 30);\n        graph_edges.emplace(from,\
    \ to);\n    }\n    assert(graph_edges.size() == 300);\n\n    for (int size = 2;\
    \ size <= 80; size++) {\n        int maximum = size * (size - 1) / 2;\n      \
    \  int edge_count = std::min(maximum, size * 4);\n        auto edges = random.dag(size,\
    \ edge_count);\n        assert(int(edges.size()) == edge_count);\n\n        std::vector<std::vector<int>>\
    \ adjacency(size);\n        std::vector<int> indegree(size);\n        std::set<std::pair<int,\
    \ int>> unique;\n        for (auto [from, to] : edges) {\n            assert(0\
    \ <= from && from < size);\n            assert(0 <= to && to < size);\n      \
    \      assert(from != to);\n            adjacency[from].push_back(to);\n     \
    \       indegree[to]++;\n            unique.emplace(from, to);\n        }\n  \
    \      assert(int(unique.size()) == edge_count);\n\n        std::vector<int> queue;\n\
    \        for (int vertex = 0; vertex < size; vertex++) {\n            if (indegree[vertex]\
    \ == 0) queue.push_back(vertex);\n        }\n        for (int head = 0; head <\
    \ int(queue.size()); head++) {\n            for (int next : adjacency[queue[head]])\
    \ {\n                if (--indegree[next] == 0) queue.push_back(next);\n     \
    \       }\n        }\n        assert(int(queue.size()) == size);\n    }\n\n  \
    \  auto weighted_dag = random.weighted_dag(100, 500, 1U, 100U);\n    assert(weighted_dag.size()\
    \ == 500);\n    for (auto [from, to, weight] : weighted_dag) {\n        assert(0\
    \ <= from && from < 100);\n        assert(0 <= to && to < 100);\n        assert(from\
    \ != to);\n        assert(1 <= weight && weight <= 100);\n    }\n\n    m1une::utilities::RandomGraphOptions\
    \ parallel_options;\n    parallel_options.allow_parallel_edges = true;\n    auto\
    \ parallel_dag = random.dag(2, 100, parallel_options);\n    assert(parallel_dag.size()\
    \ == 100);\n    for (auto edge : parallel_dag) assert(edge == parallel_dag.front());\n\
    \n    auto parallel_weighted_dag =\n        random.weighted_dag(2, 100, -3, 7,\
    \ parallel_options);\n    assert(parallel_weighted_dag.size() == 100);\n    for\
    \ (auto [from, to, weight] : parallel_weighted_dag) {\n        assert(from ==\
    \ std::get<0>(parallel_weighted_dag.front()));\n        assert(to == std::get<1>(parallel_weighted_dag.front()));\n\
    \        assert(-3 <= weight && weight <= 7);\n    }\n\n    parallel_options.allow_self_loops\
    \ = true;\n    auto parallel_directed = random.directed_graph(2, 100, parallel_options);\n\
    \    assert(parallel_directed.size() == 100);\n    auto parallel_weighted_directed\
    \ =\n        random.weighted_directed_graph(2, 100, 0LL, 10LL, parallel_options);\n\
    \    assert(parallel_weighted_directed.size() == 100);\n}\n\n}  // namespace\n\
    #endif\n\nint main() {\n#ifndef NDEBUG\n    test_basic_generators();\n    test_trees();\n\
    \    test_graphs();\n    test_weighted_graphs_and_dags();\n#endif\n\n    long\
    \ long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - utilities/random.hpp
  isVerificationFile: true
  path: verify/utilities/random_generators.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 22:42:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/random_generators.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/random_generators.test.cpp
- /verify/verify/utilities/random_generators.test.cpp.html
title: verify/utilities/random_generators.test.cpp
---
