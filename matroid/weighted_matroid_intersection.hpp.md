---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: matroid/all.hpp
    title: Matroid All
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/matroid/matroids.test.cpp
    title: verify/matroid/matroids.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/matroid/weighted_matroid_intersection.test.cpp
    title: verify/matroid/weighted_matroid_intersection.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"matroid/weighted_matroid_intersection.hpp\"\n\n\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <queue>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace matroid\
    \ {\n\ntemplate <class Weight>\nstruct WeightedMatroidIntersectionResult {\n \
    \   Weight total_weight = Weight(0);\n    std::vector<int> elements;\n\n    int\
    \ size() const {\n        return int(elements.size());\n    }\n\n    bool empty()\
    \ const {\n        return elements.empty();\n    }\n};\n\nnamespace weighted_intersection_detail\
    \ {\n\ntemplate <class Weight>\nstruct QueueGreater {\n    bool operator()(const\
    \ std::pair<Weight, int>& lhs,\n                    const std::pair<Weight, int>&\
    \ rhs) const {\n        if (rhs.first < lhs.first) return true;\n        if (lhs.first\
    \ < rhs.first) return false;\n        return lhs.second > rhs.second;\n    }\n\
    };\n\ntemplate <bool Maximize, class Weight>\nWeight objective_cost(const Weight&\
    \ change) {\n    if constexpr (Maximize) {\n        return Weight(0) - change;\n\
    \    } else {\n        return change;\n    }\n}\n\ntemplate <bool Maximize, class\
    \ Weight, class IndependenceOracle1, class IndependenceOracle2,\n          class\
    \ OnSolution>\nWeightedMatroidIntersectionResult<Weight> solve(\n    int ground_size,\
    \ const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2\
    \ oracle2, OnSolution on_solution) {\n    static_assert(!std::is_arithmetic_v<Weight>\
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
    \n\n"
  code: "#ifndef M1UNE_MATROID_WEIGHTED_MATROID_INTERSECTION_HPP\n#define M1UNE_MATROID_WEIGHTED_MATROID_INTERSECTION_HPP\
    \ 1\n\n#include <algorithm>\n#include <cassert>\n#include <queue>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\nnamespace m1une {\nnamespace matroid\
    \ {\n\ntemplate <class Weight>\nstruct WeightedMatroidIntersectionResult {\n \
    \   Weight total_weight = Weight(0);\n    std::vector<int> elements;\n\n    int\
    \ size() const {\n        return int(elements.size());\n    }\n\n    bool empty()\
    \ const {\n        return elements.empty();\n    }\n};\n\nnamespace weighted_intersection_detail\
    \ {\n\ntemplate <class Weight>\nstruct QueueGreater {\n    bool operator()(const\
    \ std::pair<Weight, int>& lhs,\n                    const std::pair<Weight, int>&\
    \ rhs) const {\n        if (rhs.first < lhs.first) return true;\n        if (lhs.first\
    \ < rhs.first) return false;\n        return lhs.second > rhs.second;\n    }\n\
    };\n\ntemplate <bool Maximize, class Weight>\nWeight objective_cost(const Weight&\
    \ change) {\n    if constexpr (Maximize) {\n        return Weight(0) - change;\n\
    \    } else {\n        return change;\n    }\n}\n\ntemplate <bool Maximize, class\
    \ Weight, class IndependenceOracle1, class IndependenceOracle2,\n          class\
    \ OnSolution>\nWeightedMatroidIntersectionResult<Weight> solve(\n    int ground_size,\
    \ const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2\
    \ oracle2, OnSolution on_solution) {\n    static_assert(!std::is_arithmetic_v<Weight>\
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
    \n#endif  // M1UNE_MATROID_WEIGHTED_MATROID_INTERSECTION_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: matroid/weighted_matroid_intersection.hpp
  requiredBy:
  - matroid/all.hpp
  timestamp: '2026-07-01 14:47:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/matroid/matroids.test.cpp
  - verify/matroid/weighted_matroid_intersection.test.cpp
documentation_of: matroid/weighted_matroid_intersection.hpp
layout: document
title: Weighted Matroid Intersection
---

## Overview

Weighted matroid intersection finds a maximum-cardinality subset that is
independent in two matroids, then optimizes its total element weight.

This header provides both objectives:

- `weighted_matroid_intersection_max` maximizes total weight;
- `weighted_matroid_intersection_min` minimizes total weight.

`weighted_matroid_intersection` is an alias for the maximizing version.

The `_each` variants report the optimal solution for every feasible
cardinality without retaining all selected sets. If the maximum
common-independent-set size is $R$, the callback runs for
$k=0,1,\ldots,R$.

Cardinality is always the primary objective. Consequently, a negative-weight
element may still be selected when it is needed to reach maximum cardinality.
This differs from asking for the maximum-weight common independent set over all
cardinalities, where the empty set could win.

## Oracle Interface

The ground set is `{0, 1, ..., ground_size - 1}`. Both matroids are supplied as
independence oracles:

```cpp
bool oracle(const std::vector<int>& subset);
```

The standard matroids in this directory provide this interface directly. A
custom oracle must ignore element order and consistently describe a fixed
matroid. The received vector contains distinct valid indices and is only valid
during the call.

## Result

```cpp
template <class Weight>
struct WeightedMatroidIntersectionResult {
    Weight total_weight;
    std::vector<int> elements;

    int size() const;
    bool empty() const;
};
```

`elements` is the optimal maximum-cardinality set in increasing order, and
`total_weight` is its weight. Ordinary min/max calls retain only this final
solution.

| Result operation | Description | Complexity |
| --- | --- | --- |
| `result.size()`, `result.empty()` | Queries the final solution. | $O(1)$ |

## Functions

```cpp
template <class Weight, class IndependenceOracle1, class IndependenceOracle2>
WeightedMatroidIntersectionResult<Weight>
weighted_matroid_intersection_max(
    int ground_size,
    const std::vector<Weight>& weight,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2);

template <class Weight, class IndependenceOracle1, class IndependenceOracle2>
WeightedMatroidIntersectionResult<Weight>
weighted_matroid_intersection_min(
    int ground_size,
    const std::vector<Weight>& weight,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2);

template <class Weight, class IndependenceOracle1,
          class IndependenceOracle2, class OnSolution>
WeightedMatroidIntersectionResult<Weight>
weighted_matroid_intersection_max_each(
    int ground_size,
    const std::vector<Weight>& weight,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2,
    OnSolution on_solution);

template <class Weight, class IndependenceOracle1,
          class IndependenceOracle2, class OnSolution>
WeightedMatroidIntersectionResult<Weight>
weighted_matroid_intersection_min_each(
    int ground_size,
    const std::vector<Weight>& weight,
    IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2,
    OnSolution on_solution);
```

The callback signature is:

```cpp
void on_solution(
    int cardinality,
    const Weight& total_weight,
    const std::vector<int>& elements);
```

It receives the optimum containing exactly `cardinality` elements. The
`elements` reference is valid only during the callback. Store a copy only when
the actual set is needed later; storing just `total_weight` for every
cardinality uses $O(R)$ memory.

The `weight` vector must contain exactly `ground_size` values. `Weight` should
be a signed, exactly ordered additive type supporting `0`, addition,
subtraction, and `<`; `long long` is the usual choice. Intermediate path costs
and the final total must fit in `Weight`.

| Function | Objective after maximizing cardinality | Complexity |
| --- | --- | --- |
| `weighted_matroid_intersection_max` | Maximum total weight. | $O(NR^2(C_1+C_2+\log N))$ |
| `weighted_matroid_intersection_min` | Minimum total weight. | $O(NR^2(C_1+C_2+\log N))$ |
| `weighted_matroid_intersection` | Alias for the maximum version. | $O(NR^2(C_1+C_2+\log N))$ |
| `weighted_matroid_intersection_max_each` | Maximum weight for every cardinality through a callback. | $O(NR^2(C_1+C_2+\log N))$ |
| `weighted_matroid_intersection_min_each` | Minimum weight for every cardinality through a callback. | $O(NR^2(C_1+C_2+\log N))$ |

Here $N$ is the ground-set size, $R$ is the maximum common-independent-set
size, and $C_i$ is the cost of oracle `i`. Additional memory is $O(NR)$ for the
exchange graph. The ordinary functions and streaming variants do not retain
the intermediate sets.

## Algorithm

Starting with the empty set, the algorithm maintains a minimum- or
maximum-weight common independent set of the current cardinality. It builds the
matroid exchange graph and finds a best augmenting path with Dijkstra's
algorithm.

Potentials keep every reduced edge length nonnegative, even though the original
exchange-edge lengths may be negative. After an augmentation, the potentials
of the toggled elements are adjusted for their new inside/outside roles. This
lets the next iteration use Dijkstra again although its exchange graph has
changed.

After Dijkstra updates the potentials, a breadth-first search in the graph of
zero reduced-length edges chooses the fewest-edge path among all best-weight
augmenting paths. This tie rule is required by the weighted augmentation
theorem. Each successful augmentation increases the cardinality by one.

## Example

```cpp
#include "matroid/partition_matroid.hpp"
#include "matroid/weighted_matroid_intersection.hpp"
#include <iostream>
#include <vector>

int main() {
    // Choose edges of a bipartite matching: one per left and right endpoint.
    std::vector<int> left = {0, 0, 1};
    std::vector<int> right = {0, 1, 0};
    std::vector<long long> weight = {100, 60, 70};

    m1une::matroid::PartitionMatroid by_left(left);
    m1une::matroid::PartitionMatroid by_right(right);
    std::vector<long long> best_weight;
    auto result = m1une::matroid::weighted_matroid_intersection_max_each(
        3, weight, by_left, by_right,
        [&](int cardinality, const long long& total,
            const std::vector<int>&) {
            // Callbacks arrive in cardinality order, starting with zero.
            best_weight.push_back(total);
        });

    // Elements 1 and 2 form the only size-two solution, with weight 130.
    std::cout << result.size() << " " << result.total_weight << "\n";

    // Best weights for cardinalities zero, one, and two: 0, 100, 130.
    for (long long value : best_weight) std::cout << value << " ";
    std::cout << "\n";
}
```
