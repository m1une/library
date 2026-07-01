---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: matroid/graphic_matroid.hpp
    title: Graphic Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/partition_matroid.hpp
    title: Partition Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/weighted_matroid_intersection.hpp
    title: Weighted Matroid Intersection
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
  bundledCode: "#line 1 \"verify/matroid/weighted_matroid_intersection.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\n#line 1 \"matroid/graphic_matroid.hpp\"\n\n\n\n#line 5 \"\
    matroid/graphic_matroid.hpp\"\n#include <numeric>\n#line 8 \"matroid/graphic_matroid.hpp\"\
    \n\nnamespace m1une {\nnamespace matroid {\n\nclass GraphicMatroid {\n   private:\n\
    \    int _vertex_count;\n    std::vector<std::pair<int, int>> _edges;\n\n   public:\n\
    \    GraphicMatroid() : _vertex_count(0) {}\n\n    GraphicMatroid(int vertex_count,\
    \ std::vector<std::pair<int, int>> edges)\n        : _vertex_count(vertex_count),\
    \ _edges(std::move(edges)) {\n        assert(0 <= vertex_count);\n#ifndef NDEBUG\n\
    \        for (auto [u, v] : _edges) {\n            assert(0 <= u && u < _vertex_count);\n\
    \            assert(0 <= v && v < _vertex_count);\n        }\n#endif\n    }\n\n\
    \    int size() const {\n        return int(_edges.size());\n    }\n\n    int\
    \ vertex_count() const {\n        return _vertex_count;\n    }\n\n    const std::vector<std::pair<int,\
    \ int>>& edges() const {\n        return _edges;\n    }\n\n    bool independent(const\
    \ std::vector<int>& subset) const {\n        std::vector<int> parent_or_size(_vertex_count,\
    \ -1);\n        auto leader = [&](auto&& self, int v) -> int {\n            if\
    \ (parent_or_size[v] < 0) return v;\n            return parent_or_size[v] = self(self,\
    \ parent_or_size[v]);\n        };\n\n        for (int element : subset) {\n  \
    \          assert(0 <= element && element < int(_edges.size()));\n           \
    \ auto [u, v] = _edges[element];\n            u = leader(leader, u);\n       \
    \     v = leader(leader, v);\n            if (u == v) return false;\n        \
    \    if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);\n         \
    \   parent_or_size[u] += parent_or_size[v];\n            parent_or_size[v] = u;\n\
    \        }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\n}  // namespace\
    \ matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/partition_matroid.hpp\"\
    \n\n\n\n#line 8 \"matroid/partition_matroid.hpp\"\n\nnamespace m1une {\nnamespace\
    \ matroid {\n\nclass PartitionMatroid {\n   private:\n    std::vector<int> _group;\n\
    \    std::vector<int> _capacity;\n\n    void validate() const {\n#ifndef NDEBUG\n\
    \        for (int capacity : _capacity) assert(0 <= capacity);\n        for (int\
    \ group : _group) assert(0 <= group && group < int(_capacity.size()));\n#endif\n\
    \    }\n\n   public:\n    PartitionMatroid() = default;\n\n    explicit PartitionMatroid(std::vector<int>\
    \ group) : _group(std::move(group)) {\n        int group_count = 0;\n        for\
    \ (int value : _group) {\n            assert(0 <= value);\n            group_count\
    \ = std::max(group_count, value + 1);\n        }\n        _capacity.assign(group_count,\
    \ 1);\n    }\n\n    PartitionMatroid(std::vector<int> group, std::vector<int>\
    \ capacity)\n        : _group(std::move(group)), _capacity(std::move(capacity))\
    \ {\n        validate();\n    }\n\n    int size() const {\n        return int(_group.size());\n\
    \    }\n\n    int group_count() const {\n        return int(_capacity.size());\n\
    \    }\n\n    const std::vector<int>& groups() const {\n        return _group;\n\
    \    }\n\n    const std::vector<int>& capacities() const {\n        return _capacity;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   std::vector<int> count(_capacity.size(), 0);\n        for (int element : subset)\
    \ {\n            assert(0 <= element && element < int(_group.size()));\n     \
    \       int group = _group[element];\n            if (++count[group] > _capacity[group])\
    \ return false;\n        }\n        return true;\n    }\n\n    bool operator()(const\
    \ std::vector<int>& subset) const {\n        return independent(subset);\n   \
    \ }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/weighted_matroid_intersection.hpp\"\
    \n\n\n\n#line 6 \"matroid/weighted_matroid_intersection.hpp\"\n#include <queue>\n\
    #include <type_traits>\n#line 10 \"matroid/weighted_matroid_intersection.hpp\"\
    \n\nnamespace m1une {\nnamespace matroid {\n\ntemplate <class Weight>\nstruct\
    \ WeightedMatroidIntersectionResult {\n    Weight total_weight = Weight(0);\n\
    \    std::vector<int> elements;\n\n    int size() const {\n        return int(elements.size());\n\
    \    }\n\n    bool empty() const {\n        return elements.empty();\n    }\n\
    };\n\nnamespace weighted_intersection_detail {\n\ntemplate <class Weight>\nstruct\
    \ QueueGreater {\n    bool operator()(const std::pair<Weight, int>& lhs,\n   \
    \                 const std::pair<Weight, int>& rhs) const {\n        if (rhs.first\
    \ < lhs.first) return true;\n        if (lhs.first < rhs.first) return false;\n\
    \        return lhs.second > rhs.second;\n    }\n};\n\ntemplate <bool Maximize,\
    \ class Weight>\nWeight objective_cost(const Weight& change) {\n    if constexpr\
    \ (Maximize) {\n        return Weight(0) - change;\n    } else {\n        return\
    \ change;\n    }\n}\n\ntemplate <bool Maximize, class Weight, class IndependenceOracle1,\
    \ class IndependenceOracle2,\n          class OnSolution>\nWeightedMatroidIntersectionResult<Weight>\
    \ solve(\n    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1\
    \ oracle1,\n    IndependenceOracle2 oracle2, OnSolution on_solution) {\n    static_assert(!std::is_arithmetic_v<Weight>\
    \ || std::is_signed_v<Weight>,\n                  \"Weight must support negative\
    \ intermediate values\");\n    assert(0 <= ground_size);\n    assert(int(weight.size())\
    \ == ground_size);\n\n    const int source_vertex = ground_size;\n    const int\
    \ sink_vertex = ground_size + 1;\n    const int vertex_count = ground_size + 2;\n\
    \    std::vector<char> selected(ground_size, false);\n    std::vector<int> elements;\n\
    \    std::vector<int> position(ground_size, -1);\n    std::vector<Weight> potential(vertex_count,\
    \ Weight(0));\n    Weight total_weight = Weight(0);\n    on_solution(0, total_weight,\
    \ elements);\n\n    while (true) {\n        std::vector<std::vector<int>> adjacency(vertex_count);\n\
    \        std::vector<int> sink_predecessors;\n\n        for (int x = 0; x < ground_size;\
    \ x++) {\n            if (selected[x]) continue;\n            elements.push_back(x);\n\
    \            bool source = oracle1(elements);\n            bool sink = oracle2(elements);\n\
    \            elements.pop_back();\n            if (source) adjacency[source_vertex].push_back(x);\n\
    \            if (sink) {\n                adjacency[x].push_back(sink_vertex);\n\
    \                sink_predecessors.push_back(x);\n            }\n        }\n\n\
    \        for (int y : elements) {\n            int index = position[y];\n    \
    \        assert(index != -1 && elements[index] == y);\n            for (int x\
    \ = 0; x < ground_size; x++) {\n                if (selected[x]) continue;\n \
    \               elements[index] = x;\n                if (oracle1(elements)) adjacency[y].push_back(x);\n\
    \                if (oracle2(elements)) adjacency[x].push_back(y);\n         \
    \       elements[index] = y;\n            }\n        }\n\n        if (adjacency[source_vertex].empty()\
    \ || sink_predecessors.empty()) break;\n\n        auto vertex_length = [&](int\
    \ vertex) {\n            if (vertex >= ground_size) return Weight(0);\n      \
    \      Weight change = selected[vertex] ? Weight(0) - weight[vertex] : weight[vertex];\n\
    \            return objective_cost<Maximize>(change);\n        };\n        auto\
    \ reduced_length = [&](int from, int to) {\n            return vertex_length(to)\
    \ - potential[to] + potential[from];\n        };\n\n        int first_source =\
    \ adjacency[source_vertex].front();\n        potential[source_vertex] = potential[first_source]\
    \ - vertex_length(first_source);\n        for (int x : adjacency[source_vertex])\
    \ {\n            Weight candidate = potential[x] - vertex_length(x);\n       \
    \     if (potential[source_vertex] < candidate) potential[source_vertex] = candidate;\n\
    \        }\n        potential[sink_vertex] = potential[sink_predecessors.front()];\n\
    \        for (int x : sink_predecessors) {\n            if (potential[x] < potential[sink_vertex])\
    \ potential[sink_vertex] = potential[x];\n        }\n        Weight source_potential\
    \ = potential[source_vertex];\n        for (Weight& value : potential) value =\
    \ value - source_potential;\n\n#ifndef NDEBUG\n        for (int from = 0; from\
    \ < vertex_count; from++) {\n            for (int to : adjacency[from]) assert(!(reduced_length(from,\
    \ to) < Weight(0)));\n        }\n#endif\n\n        // Dijkstra is performed lazily:\
    \ fixed_distance is added to every\n        // not-yet-fixed potential at once,\
    \ then materialized when a vertex is fixed.\n        using QueueEntry = std::pair<Weight,\
    \ int>;\n        std::priority_queue<QueueEntry, std::vector<QueueEntry>, QueueGreater<Weight>>\
    \ heap;\n        std::vector<char> fixed(vertex_count, false);\n        std::vector<char>\
    \ has_distance(vertex_count, false);\n        std::vector<Weight> distance(vertex_count,\
    \ Weight(0));\n        std::vector<int> previous(vertex_count, -1);\n        heap.push({Weight(0),\
    \ source_vertex});\n        has_distance[source_vertex] = true;\n\n        Weight\
    \ fixed_distance = Weight(0);\n        bool reached_sink = false;\n        std::vector<int>\
    \ tight_stack;\n        tight_stack.reserve(vertex_count);\n        while (!heap.empty()\
    \ && !reached_sink) {\n            int start = heap.top().second;\n          \
    \  heap.pop();\n            if (fixed[start]) continue;\n            if (start\
    \ != source_vertex) {\n                assert(previous[start] != -1);\n      \
    \          fixed_distance = reduced_length(previous[start], start);\n        \
    \    }\n\n            tight_stack.clear();\n            fixed[start] = true;\n\
    \            potential[start] = potential[start] + fixed_distance;\n         \
    \   tight_stack.push_back(start);\n\n            while (!tight_stack.empty() &&\
    \ !reached_sink) {\n                int current = tight_stack.back();\n      \
    \          tight_stack.pop_back();\n                if (current == sink_vertex)\
    \ {\n                    reached_sink = true;\n                    break;\n  \
    \              }\n                for (int next : adjacency[current]) {\n    \
    \                if (fixed[next]) continue;\n                    Weight slack\
    \ = reduced_length(current, next) - fixed_distance;\n                    assert(!(slack\
    \ < Weight(0)));\n                    if (!(Weight(0) < slack)) {\n          \
    \              previous[next] = current;\n                        fixed[next]\
    \ = true;\n                        potential[next] = potential[next] + fixed_distance;\n\
    \                        tight_stack.push_back(next);\n                    } else\
    \ {\n                        Weight candidate = fixed_distance + slack;\n    \
    \                    if (!has_distance[next] || candidate < distance[next]) {\n\
    \                            has_distance[next] = true;\n                    \
    \        distance[next] = candidate;\n                            previous[next]\
    \ = current;\n                            heap.push({candidate, next});\n    \
    \                    }\n                    }\n                }\n           \
    \ }\n        }\n\n        for (int vertex = 0; vertex < vertex_count; vertex++)\
    \ {\n            if (!fixed[vertex]) potential[vertex] = potential[vertex] + fixed_distance;\n\
    \        }\n        if (!reached_sink) break;\n\n        std::fill(previous.begin(),\
    \ previous.end(), -1);\n        std::vector<char> reached(vertex_count, false);\n\
    \        std::vector<int> queue;\n        queue.reserve(vertex_count);\n     \
    \   reached[source_vertex] = true;\n        queue.push_back(source_vertex);\n\
    \        for (int head = 0; head < int(queue.size()) && !reached[sink_vertex];\
    \ head++) {\n            int current = queue[head];\n            for (int next\
    \ : adjacency[current]) {\n                if (reached[next]) continue;\n    \
    \            Weight length = reduced_length(current, next);\n                assert(!(length\
    \ < Weight(0)));\n                if (Weight(0) < length) continue;\n        \
    \        reached[next] = true;\n                previous[next] = current;\n  \
    \              queue.push_back(next);\n            }\n        }\n        assert(reached[sink_vertex]);\n\
    \        if (!reached[sink_vertex]) break;\n\n        // A shortest tight path\
    \ with the fewest edges preserves the potential invariant\n        // after its\
    \ elements switch between the inside and outside of the solution.\n        for\
    \ (int v = sink_vertex; v != source_vertex; v = previous[v]) {\n            assert(v\
    \ != -1);\n            if (v < ground_size) {\n                potential[v] =\
    \ potential[v] - vertex_length(v);\n                if (selected[v]) {\n     \
    \               total_weight = total_weight - weight[v];\n                } else\
    \ {\n                    total_weight = total_weight + weight[v];\n          \
    \      }\n                selected[v] = !selected[v];\n            }\n       \
    \ }\n\n        elements.clear();\n        std::fill(position.begin(), position.end(),\
    \ -1);\n        for (int x = 0; x < ground_size; x++) {\n            if (!selected[x])\
    \ continue;\n            position[x] = int(elements.size());\n            elements.push_back(x);\n\
    \        }\n\n#ifndef NDEBUG\n        assert(oracle1(elements));\n        assert(oracle2(elements));\n\
    #endif\n        on_solution(int(elements.size()), total_weight, elements);\n \
    \   }\n\n    WeightedMatroidIntersectionResult<Weight> result;\n    result.elements\
    \ = elements;\n    result.total_weight = total_weight;\n    return result;\n}\n\
    \n}  // namespace weighted_intersection_detail\n\ntemplate <class Weight, class\
    \ IndependenceOracle1, class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_max(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2) {\n \
    \   auto ignore = [](int, const Weight&, const std::vector<int>&) {};\n    return\
    \ weighted_intersection_detail::solve<true>(ground_size, weight, oracle1, oracle2,\n\
    \                                                      ignore);\n}\n\ntemplate\
    \ <class Weight, class IndependenceOracle1, class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_min(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2) {\n \
    \   auto ignore = [](int, const Weight&, const std::vector<int>&) {};\n    return\
    \ weighted_intersection_detail::solve<false>(ground_size, weight, oracle1, oracle2,\n\
    \                                                       ignore);\n}\n\ntemplate\
    \ <class Weight, class IndependenceOracle1, class IndependenceOracle2, class OnSolution>\n\
    WeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection_max_each(\n\
    \    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n\
    \    IndependenceOracle2 oracle2, OnSolution on_solution) {\n    return weighted_intersection_detail::solve<true>(ground_size,\
    \ weight, oracle1, oracle2,\n                                                \
    \      on_solution);\n}\n\ntemplate <class Weight, class IndependenceOracle1,\
    \ class IndependenceOracle2, class OnSolution>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_min_each(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2, OnSolution\
    \ on_solution) {\n    return weighted_intersection_detail::solve<false>(ground_size,\
    \ weight, oracle1, oracle2,\n                                                \
    \       on_solution);\n}\n\ntemplate <class Weight, class IndependenceOracle1,\
    \ class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection(\n\
    \    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n\
    \    IndependenceOracle2 oracle2) {\n    return weighted_matroid_intersection_max(ground_size,\
    \ weight, oracle1, oracle2);\n}\n\n}  // namespace matroid\n}  // namespace m1une\n\
    \n\n#line 13 \"verify/matroid/weighted_matroid_intersection.test.cpp\"\n\nstruct\
    \ BruteResult {\n    int cardinality = -1;\n    std::vector<long long> minimum_weight;\n\
    \    std::vector<long long> maximum_weight;\n    std::vector<char> exists;\n};\n\
    \ntemplate <class Oracle1, class Oracle2>\nBruteResult brute_force(const std::vector<long\
    \ long>& weight, const Oracle1& oracle1,\n                        const Oracle2&\
    \ oracle2) {\n    int n = int(weight.size());\n    BruteResult result;\n    result.minimum_weight.resize(n\
    \ + 1);\n    result.maximum_weight.resize(n + 1);\n    result.exists.assign(n\
    \ + 1, false);\n    for (int mask = 0; mask < (1 << n); mask++) {\n        std::vector<int>\
    \ subset;\n        long long sum = 0;\n        for (int i = 0; i < n; i++) {\n\
    \            if (mask >> i & 1) {\n                subset.push_back(i);\n    \
    \            sum += weight[i];\n            }\n        }\n        if (!oracle1(subset)\
    \ || !oracle2(subset)) continue;\n        int cardinality = int(subset.size());\n\
    \        result.cardinality = std::max(result.cardinality, cardinality);\n   \
    \     if (!result.exists[cardinality]) {\n            result.exists[cardinality]\
    \ = true;\n            result.minimum_weight[cardinality] = sum;\n           \
    \ result.maximum_weight[cardinality] = sum;\n        } else {\n            result.minimum_weight[cardinality]\
    \ =\n                std::min(result.minimum_weight[cardinality], sum);\n    \
    \        result.maximum_weight[cardinality] =\n                std::max(result.maximum_weight[cardinality],\
    \ sum);\n        }\n    }\n    return result;\n}\n\ntemplate <class Oracle1, class\
    \ Oracle2>\nvoid check(const std::vector<long long>& weight, const Oracle1& oracle1,\n\
    \           const Oracle2& oracle2) {\n    int n = int(weight.size());\n    BruteResult\
    \ expected = brute_force(weight, oracle1, oracle2);\n    auto maximum =\n    \
    \    m1une::matroid::weighted_matroid_intersection_max(n, weight, oracle1, oracle2);\n\
    \    auto minimum =\n        m1une::matroid::weighted_matroid_intersection_min(n,\
    \ weight, oracle1, oracle2);\n    auto default_result =\n        m1une::matroid::weighted_matroid_intersection(n,\
    \ weight, oracle1, oracle2);\n\n    std::vector<long long> maximum_by_cardinality;\n\
    \    std::vector<long long> minimum_by_cardinality;\n    auto streamed_maximum\
    \ = m1une::matroid::weighted_matroid_intersection_max_each(\n        n, weight,\
    \ oracle1, oracle2,\n        [&](int cardinality, const long long& total_weight,\n\
    \            const std::vector<int>& elements) {\n            assert(cardinality\
    \ == int(maximum_by_cardinality.size()));\n            assert(int(elements.size())\
    \ == cardinality);\n            assert(oracle1(elements) && oracle2(elements));\n\
    \            assert(std::is_sorted(elements.begin(), elements.end()));\n     \
    \       long long sum = 0;\n            for (int element : elements) sum += weight[element];\n\
    \            (void)cardinality;\n            (void)sum;\n            assert(sum\
    \ == total_weight);\n            assert(total_weight == expected.maximum_weight[cardinality]);\n\
    \            maximum_by_cardinality.push_back(total_weight);\n        });\n  \
    \  auto streamed_minimum = m1une::matroid::weighted_matroid_intersection_min_each(\n\
    \        n, weight, oracle1, oracle2,\n        [&](int cardinality, const long\
    \ long& total_weight,\n            const std::vector<int>& elements) {\n     \
    \       assert(cardinality == int(minimum_by_cardinality.size()));\n         \
    \   assert(int(elements.size()) == cardinality);\n            assert(oracle1(elements)\
    \ && oracle2(elements));\n            assert(std::is_sorted(elements.begin(),\
    \ elements.end()));\n            long long sum = 0;\n            for (int element\
    \ : elements) sum += weight[element];\n            (void)cardinality;\n      \
    \      (void)sum;\n            assert(sum == total_weight);\n            assert(total_weight\
    \ == expected.minimum_weight[cardinality]);\n            minimum_by_cardinality.push_back(total_weight);\n\
    \        });\n\n    assert(maximum.size() == expected.cardinality);\n    assert(minimum.size()\
    \ == expected.cardinality);\n    assert(maximum.total_weight == expected.maximum_weight[expected.cardinality]);\n\
    \    assert(minimum.total_weight == expected.minimum_weight[expected.cardinality]);\n\
    \    assert(default_result.total_weight == maximum.total_weight);\n    assert(default_result.elements\
    \ == maximum.elements);\n    assert(streamed_maximum.total_weight == maximum.total_weight);\n\
    \    assert(streamed_maximum.elements == maximum.elements);\n    assert(streamed_minimum.total_weight\
    \ == minimum.total_weight);\n    assert(streamed_minimum.elements == minimum.elements);\n\
    \    assert(oracle1(maximum.elements) && oracle2(maximum.elements));\n    assert(oracle1(minimum.elements)\
    \ && oracle2(minimum.elements));\n    assert(std::is_sorted(maximum.elements.begin(),\
    \ maximum.elements.end()));\n    assert(std::is_sorted(minimum.elements.begin(),\
    \ minimum.elements.end()));\n\n    assert(int(maximum_by_cardinality.size()) ==\
    \ expected.cardinality + 1);\n    assert(int(minimum_by_cardinality.size()) ==\
    \ expected.cardinality + 1);\n    for (int cardinality = 0; cardinality <= expected.cardinality;\
    \ cardinality++) {\n        assert(expected.exists[cardinality]);\n        assert(maximum_by_cardinality[cardinality]\
    \ == expected.maximum_weight[cardinality]);\n        assert(minimum_by_cardinality[cardinality]\
    \ == expected.minimum_weight[cardinality]);\n    }\n}\n\nvoid test_weighted_exchange()\
    \ {\n    m1une::matroid::PartitionMatroid left(std::vector<int>{0, 0, 1});\n \
    \   m1une::matroid::PartitionMatroid right(std::vector<int>{0, 1, 0});\n    std::vector<long\
    \ long> weight = {100, 60, 70};\n    auto result = m1une::matroid::weighted_matroid_intersection_max(3,\
    \ weight, left, right);\n    assert((result.elements == std::vector<int>{1, 2}));\n\
    \    assert(result.total_weight == 130);\n\n    std::vector<long long> best_weight;\n\
    \    auto streamed = m1une::matroid::weighted_matroid_intersection_max_each(\n\
    \        3, weight, left, right,\n        [&](int, const long long& total_weight,\
    \ const std::vector<int>&) {\n            best_weight.push_back(total_weight);\n\
    \        });\n    assert((best_weight == std::vector<long long>{0, 100, 130}));\n\
    \    assert(streamed.elements == result.elements);\n    assert(streamed.total_weight\
    \ == result.total_weight);\n\n    weight = {-1, -100, -200};\n    result = m1une::matroid::weighted_matroid_intersection_max(3,\
    \ weight, left, right);\n    assert(result.size() == 2);\n    assert(result.total_weight\
    \ == -300);\n}\n\nvoid test_equal_weights() {\n    m1une::matroid::PartitionMatroid\
    \ first(std::vector<int>{0, 0, 1, 1, 2, 2});\n    m1une::matroid::PartitionMatroid\
    \ second(std::vector<int>{0, 1, 1, 2, 2, 0});\n    check(std::vector<long long>(6,\
    \ 0), first, second);\n    check(std::vector<long long>(6, 7), first, second);\n\
    }\n\nvoid test_random_weighted_matroids() {\n    std::mt19937 random(987654321);\n\
    \    for (int test = 0; test < 300; test++) {\n        int n = random() % 10;\n\
    \        std::vector<long long> weight(n);\n        for (long long& value : weight)\
    \ value = int(random() % 41) - 20;\n\n        int group_count = 1 + random() %\
    \ 5;\n        std::vector<int> group(n);\n        for (int& value : group) value\
    \ = random() % group_count;\n        m1une::matroid::PartitionMatroid partition(group);\n\
    \n        int vertex_count = 1 + random() % 6;\n        std::vector<std::pair<int,\
    \ int>> edges(n);\n        for (auto& [u, v] : edges) {\n            u = random()\
    \ % vertex_count;\n            v = random() % vertex_count;\n        }\n     \
    \   m1une::matroid::GraphicMatroid graphic(vertex_count, edges);\n        check(weight,\
    \ partition, graphic);\n\n        int second_group_count = 1 + random() % 5;\n\
    \        std::vector<int> second_group(n);\n        for (int& value : second_group)\
    \ value = random() % second_group_count;\n        m1une::matroid::PartitionMatroid\
    \ second_partition(second_group);\n        check(weight, partition, second_partition);\n\
    \    }\n}\n\nint main() {\n    test_weighted_exchange();\n    test_equal_weights();\n\
    \    test_random_weighted_matroids();\n\n    long long a, b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iostream>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../matroid/graphic_matroid.hpp\"\n#include\
    \ \"../../matroid/partition_matroid.hpp\"\n#include \"../../matroid/weighted_matroid_intersection.hpp\"\
    \n\nstruct BruteResult {\n    int cardinality = -1;\n    std::vector<long long>\
    \ minimum_weight;\n    std::vector<long long> maximum_weight;\n    std::vector<char>\
    \ exists;\n};\n\ntemplate <class Oracle1, class Oracle2>\nBruteResult brute_force(const\
    \ std::vector<long long>& weight, const Oracle1& oracle1,\n                  \
    \      const Oracle2& oracle2) {\n    int n = int(weight.size());\n    BruteResult\
    \ result;\n    result.minimum_weight.resize(n + 1);\n    result.maximum_weight.resize(n\
    \ + 1);\n    result.exists.assign(n + 1, false);\n    for (int mask = 0; mask\
    \ < (1 << n); mask++) {\n        std::vector<int> subset;\n        long long sum\
    \ = 0;\n        for (int i = 0; i < n; i++) {\n            if (mask >> i & 1)\
    \ {\n                subset.push_back(i);\n                sum += weight[i];\n\
    \            }\n        }\n        if (!oracle1(subset) || !oracle2(subset)) continue;\n\
    \        int cardinality = int(subset.size());\n        result.cardinality = std::max(result.cardinality,\
    \ cardinality);\n        if (!result.exists[cardinality]) {\n            result.exists[cardinality]\
    \ = true;\n            result.minimum_weight[cardinality] = sum;\n           \
    \ result.maximum_weight[cardinality] = sum;\n        } else {\n            result.minimum_weight[cardinality]\
    \ =\n                std::min(result.minimum_weight[cardinality], sum);\n    \
    \        result.maximum_weight[cardinality] =\n                std::max(result.maximum_weight[cardinality],\
    \ sum);\n        }\n    }\n    return result;\n}\n\ntemplate <class Oracle1, class\
    \ Oracle2>\nvoid check(const std::vector<long long>& weight, const Oracle1& oracle1,\n\
    \           const Oracle2& oracle2) {\n    int n = int(weight.size());\n    BruteResult\
    \ expected = brute_force(weight, oracle1, oracle2);\n    auto maximum =\n    \
    \    m1une::matroid::weighted_matroid_intersection_max(n, weight, oracle1, oracle2);\n\
    \    auto minimum =\n        m1une::matroid::weighted_matroid_intersection_min(n,\
    \ weight, oracle1, oracle2);\n    auto default_result =\n        m1une::matroid::weighted_matroid_intersection(n,\
    \ weight, oracle1, oracle2);\n\n    std::vector<long long> maximum_by_cardinality;\n\
    \    std::vector<long long> minimum_by_cardinality;\n    auto streamed_maximum\
    \ = m1une::matroid::weighted_matroid_intersection_max_each(\n        n, weight,\
    \ oracle1, oracle2,\n        [&](int cardinality, const long long& total_weight,\n\
    \            const std::vector<int>& elements) {\n            assert(cardinality\
    \ == int(maximum_by_cardinality.size()));\n            assert(int(elements.size())\
    \ == cardinality);\n            assert(oracle1(elements) && oracle2(elements));\n\
    \            assert(std::is_sorted(elements.begin(), elements.end()));\n     \
    \       long long sum = 0;\n            for (int element : elements) sum += weight[element];\n\
    \            (void)cardinality;\n            (void)sum;\n            assert(sum\
    \ == total_weight);\n            assert(total_weight == expected.maximum_weight[cardinality]);\n\
    \            maximum_by_cardinality.push_back(total_weight);\n        });\n  \
    \  auto streamed_minimum = m1une::matroid::weighted_matroid_intersection_min_each(\n\
    \        n, weight, oracle1, oracle2,\n        [&](int cardinality, const long\
    \ long& total_weight,\n            const std::vector<int>& elements) {\n     \
    \       assert(cardinality == int(minimum_by_cardinality.size()));\n         \
    \   assert(int(elements.size()) == cardinality);\n            assert(oracle1(elements)\
    \ && oracle2(elements));\n            assert(std::is_sorted(elements.begin(),\
    \ elements.end()));\n            long long sum = 0;\n            for (int element\
    \ : elements) sum += weight[element];\n            (void)cardinality;\n      \
    \      (void)sum;\n            assert(sum == total_weight);\n            assert(total_weight\
    \ == expected.minimum_weight[cardinality]);\n            minimum_by_cardinality.push_back(total_weight);\n\
    \        });\n\n    assert(maximum.size() == expected.cardinality);\n    assert(minimum.size()\
    \ == expected.cardinality);\n    assert(maximum.total_weight == expected.maximum_weight[expected.cardinality]);\n\
    \    assert(minimum.total_weight == expected.minimum_weight[expected.cardinality]);\n\
    \    assert(default_result.total_weight == maximum.total_weight);\n    assert(default_result.elements\
    \ == maximum.elements);\n    assert(streamed_maximum.total_weight == maximum.total_weight);\n\
    \    assert(streamed_maximum.elements == maximum.elements);\n    assert(streamed_minimum.total_weight\
    \ == minimum.total_weight);\n    assert(streamed_minimum.elements == minimum.elements);\n\
    \    assert(oracle1(maximum.elements) && oracle2(maximum.elements));\n    assert(oracle1(minimum.elements)\
    \ && oracle2(minimum.elements));\n    assert(std::is_sorted(maximum.elements.begin(),\
    \ maximum.elements.end()));\n    assert(std::is_sorted(minimum.elements.begin(),\
    \ minimum.elements.end()));\n\n    assert(int(maximum_by_cardinality.size()) ==\
    \ expected.cardinality + 1);\n    assert(int(minimum_by_cardinality.size()) ==\
    \ expected.cardinality + 1);\n    for (int cardinality = 0; cardinality <= expected.cardinality;\
    \ cardinality++) {\n        assert(expected.exists[cardinality]);\n        assert(maximum_by_cardinality[cardinality]\
    \ == expected.maximum_weight[cardinality]);\n        assert(minimum_by_cardinality[cardinality]\
    \ == expected.minimum_weight[cardinality]);\n    }\n}\n\nvoid test_weighted_exchange()\
    \ {\n    m1une::matroid::PartitionMatroid left(std::vector<int>{0, 0, 1});\n \
    \   m1une::matroid::PartitionMatroid right(std::vector<int>{0, 1, 0});\n    std::vector<long\
    \ long> weight = {100, 60, 70};\n    auto result = m1une::matroid::weighted_matroid_intersection_max(3,\
    \ weight, left, right);\n    assert((result.elements == std::vector<int>{1, 2}));\n\
    \    assert(result.total_weight == 130);\n\n    std::vector<long long> best_weight;\n\
    \    auto streamed = m1une::matroid::weighted_matroid_intersection_max_each(\n\
    \        3, weight, left, right,\n        [&](int, const long long& total_weight,\
    \ const std::vector<int>&) {\n            best_weight.push_back(total_weight);\n\
    \        });\n    assert((best_weight == std::vector<long long>{0, 100, 130}));\n\
    \    assert(streamed.elements == result.elements);\n    assert(streamed.total_weight\
    \ == result.total_weight);\n\n    weight = {-1, -100, -200};\n    result = m1une::matroid::weighted_matroid_intersection_max(3,\
    \ weight, left, right);\n    assert(result.size() == 2);\n    assert(result.total_weight\
    \ == -300);\n}\n\nvoid test_equal_weights() {\n    m1une::matroid::PartitionMatroid\
    \ first(std::vector<int>{0, 0, 1, 1, 2, 2});\n    m1une::matroid::PartitionMatroid\
    \ second(std::vector<int>{0, 1, 1, 2, 2, 0});\n    check(std::vector<long long>(6,\
    \ 0), first, second);\n    check(std::vector<long long>(6, 7), first, second);\n\
    }\n\nvoid test_random_weighted_matroids() {\n    std::mt19937 random(987654321);\n\
    \    for (int test = 0; test < 300; test++) {\n        int n = random() % 10;\n\
    \        std::vector<long long> weight(n);\n        for (long long& value : weight)\
    \ value = int(random() % 41) - 20;\n\n        int group_count = 1 + random() %\
    \ 5;\n        std::vector<int> group(n);\n        for (int& value : group) value\
    \ = random() % group_count;\n        m1une::matroid::PartitionMatroid partition(group);\n\
    \n        int vertex_count = 1 + random() % 6;\n        std::vector<std::pair<int,\
    \ int>> edges(n);\n        for (auto& [u, v] : edges) {\n            u = random()\
    \ % vertex_count;\n            v = random() % vertex_count;\n        }\n     \
    \   m1une::matroid::GraphicMatroid graphic(vertex_count, edges);\n        check(weight,\
    \ partition, graphic);\n\n        int second_group_count = 1 + random() % 5;\n\
    \        std::vector<int> second_group(n);\n        for (int& value : second_group)\
    \ value = random() % second_group_count;\n        m1une::matroid::PartitionMatroid\
    \ second_partition(second_group);\n        check(weight, partition, second_partition);\n\
    \    }\n}\n\nint main() {\n    test_weighted_exchange();\n    test_equal_weights();\n\
    \    test_random_weighted_matroids();\n\n    long long a, b;\n    std::cin >>\
    \ a >> b;\n    std::cout << a + b << '\\n';\n}\n"
  dependsOn:
  - matroid/graphic_matroid.hpp
  - matroid/partition_matroid.hpp
  - matroid/weighted_matroid_intersection.hpp
  isVerificationFile: true
  path: verify/matroid/weighted_matroid_intersection.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:47:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/matroid/weighted_matroid_intersection.test.cpp
layout: document
redirect_from:
- /verify/verify/matroid/weighted_matroid_intersection.test.cpp
- /verify/verify/matroid/weighted_matroid_intersection.test.cpp.html
title: verify/matroid/weighted_matroid_intersection.test.cpp
---
