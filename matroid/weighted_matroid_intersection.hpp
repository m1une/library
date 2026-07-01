#ifndef M1UNE_MATROID_WEIGHTED_MATROID_INTERSECTION_HPP
#define M1UNE_MATROID_WEIGHTED_MATROID_INTERSECTION_HPP 1

#include <algorithm>
#include <cassert>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace matroid {

template <class Weight>
struct WeightedMatroidIntersectionResult {
    Weight total_weight = Weight(0);
    std::vector<int> elements;

    int size() const {
        return int(elements.size());
    }

    bool empty() const {
        return elements.empty();
    }
};

namespace weighted_intersection_detail {

template <class Weight>
struct QueueGreater {
    bool operator()(const std::pair<Weight, int>& lhs,
                    const std::pair<Weight, int>& rhs) const {
        if (rhs.first < lhs.first) return true;
        if (lhs.first < rhs.first) return false;
        return lhs.second > rhs.second;
    }
};

template <bool Maximize, class Weight>
Weight objective_cost(const Weight& change) {
    if constexpr (Maximize) {
        return Weight(0) - change;
    } else {
        return change;
    }
}

template <bool Maximize, class Weight, class IndependenceOracle1, class IndependenceOracle2,
          class OnSolution>
WeightedMatroidIntersectionResult<Weight> solve(
    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2, OnSolution on_solution) {
    static_assert(!std::is_arithmetic_v<Weight> || std::is_signed_v<Weight>,
                  "Weight must support negative intermediate values");
    assert(0 <= ground_size);
    assert(int(weight.size()) == ground_size);

    const int source_vertex = ground_size;
    const int sink_vertex = ground_size + 1;
    const int vertex_count = ground_size + 2;
    std::vector<char> selected(ground_size, false);
    std::vector<int> elements;
    std::vector<int> position(ground_size, -1);
    std::vector<Weight> potential(vertex_count, Weight(0));
    Weight total_weight = Weight(0);
    on_solution(0, total_weight, elements);

    while (true) {
        std::vector<std::vector<int>> adjacency(vertex_count);
        std::vector<int> sink_predecessors;

        for (int x = 0; x < ground_size; x++) {
            if (selected[x]) continue;
            elements.push_back(x);
            bool source = oracle1(elements);
            bool sink = oracle2(elements);
            elements.pop_back();
            if (source) adjacency[source_vertex].push_back(x);
            if (sink) {
                adjacency[x].push_back(sink_vertex);
                sink_predecessors.push_back(x);
            }
        }

        for (int y : elements) {
            int index = position[y];
            assert(index != -1 && elements[index] == y);
            for (int x = 0; x < ground_size; x++) {
                if (selected[x]) continue;
                elements[index] = x;
                if (oracle1(elements)) adjacency[y].push_back(x);
                if (oracle2(elements)) adjacency[x].push_back(y);
                elements[index] = y;
            }
        }

        if (adjacency[source_vertex].empty() || sink_predecessors.empty()) break;

        auto vertex_length = [&](int vertex) {
            if (vertex >= ground_size) return Weight(0);
            Weight change = selected[vertex] ? Weight(0) - weight[vertex] : weight[vertex];
            return objective_cost<Maximize>(change);
        };
        auto reduced_length = [&](int from, int to) {
            return vertex_length(to) - potential[to] + potential[from];
        };

        int first_source = adjacency[source_vertex].front();
        potential[source_vertex] = potential[first_source] - vertex_length(first_source);
        for (int x : adjacency[source_vertex]) {
            Weight candidate = potential[x] - vertex_length(x);
            if (potential[source_vertex] < candidate) potential[source_vertex] = candidate;
        }
        potential[sink_vertex] = potential[sink_predecessors.front()];
        for (int x : sink_predecessors) {
            if (potential[x] < potential[sink_vertex]) potential[sink_vertex] = potential[x];
        }
        Weight source_potential = potential[source_vertex];
        for (Weight& value : potential) value = value - source_potential;

#ifndef NDEBUG
        for (int from = 0; from < vertex_count; from++) {
            for (int to : adjacency[from]) assert(!(reduced_length(from, to) < Weight(0)));
        }
#endif

        // Dijkstra is performed lazily: fixed_distance is added to every
        // not-yet-fixed potential at once, then materialized when a vertex is fixed.
        using QueueEntry = std::pair<Weight, int>;
        std::priority_queue<QueueEntry, std::vector<QueueEntry>, QueueGreater<Weight>> heap;
        std::vector<char> fixed(vertex_count, false);
        std::vector<char> has_distance(vertex_count, false);
        std::vector<Weight> distance(vertex_count, Weight(0));
        std::vector<int> previous(vertex_count, -1);
        heap.push({Weight(0), source_vertex});
        has_distance[source_vertex] = true;

        Weight fixed_distance = Weight(0);
        bool reached_sink = false;
        std::vector<int> tight_stack;
        tight_stack.reserve(vertex_count);
        while (!heap.empty() && !reached_sink) {
            int start = heap.top().second;
            heap.pop();
            if (fixed[start]) continue;
            if (start != source_vertex) {
                assert(previous[start] != -1);
                fixed_distance = reduced_length(previous[start], start);
            }

            tight_stack.clear();
            fixed[start] = true;
            potential[start] = potential[start] + fixed_distance;
            tight_stack.push_back(start);

            while (!tight_stack.empty() && !reached_sink) {
                int current = tight_stack.back();
                tight_stack.pop_back();
                if (current == sink_vertex) {
                    reached_sink = true;
                    break;
                }
                for (int next : adjacency[current]) {
                    if (fixed[next]) continue;
                    Weight slack = reduced_length(current, next) - fixed_distance;
                    assert(!(slack < Weight(0)));
                    if (!(Weight(0) < slack)) {
                        previous[next] = current;
                        fixed[next] = true;
                        potential[next] = potential[next] + fixed_distance;
                        tight_stack.push_back(next);
                    } else {
                        Weight candidate = fixed_distance + slack;
                        if (!has_distance[next] || candidate < distance[next]) {
                            has_distance[next] = true;
                            distance[next] = candidate;
                            previous[next] = current;
                            heap.push({candidate, next});
                        }
                    }
                }
            }
        }

        for (int vertex = 0; vertex < vertex_count; vertex++) {
            if (!fixed[vertex]) potential[vertex] = potential[vertex] + fixed_distance;
        }
        if (!reached_sink) break;

        std::fill(previous.begin(), previous.end(), -1);
        std::vector<char> reached(vertex_count, false);
        std::vector<int> queue;
        queue.reserve(vertex_count);
        reached[source_vertex] = true;
        queue.push_back(source_vertex);
        for (int head = 0; head < int(queue.size()) && !reached[sink_vertex]; head++) {
            int current = queue[head];
            for (int next : adjacency[current]) {
                if (reached[next]) continue;
                Weight length = reduced_length(current, next);
                assert(!(length < Weight(0)));
                if (Weight(0) < length) continue;
                reached[next] = true;
                previous[next] = current;
                queue.push_back(next);
            }
        }
        assert(reached[sink_vertex]);
        if (!reached[sink_vertex]) break;

        // A shortest tight path with the fewest edges preserves the potential invariant
        // after its elements switch between the inside and outside of the solution.
        for (int v = sink_vertex; v != source_vertex; v = previous[v]) {
            assert(v != -1);
            if (v < ground_size) {
                potential[v] = potential[v] - vertex_length(v);
                if (selected[v]) {
                    total_weight = total_weight - weight[v];
                } else {
                    total_weight = total_weight + weight[v];
                }
                selected[v] = !selected[v];
            }
        }

        elements.clear();
        std::fill(position.begin(), position.end(), -1);
        for (int x = 0; x < ground_size; x++) {
            if (!selected[x]) continue;
            position[x] = int(elements.size());
            elements.push_back(x);
        }

#ifndef NDEBUG
        assert(oracle1(elements));
        assert(oracle2(elements));
#endif
        on_solution(int(elements.size()), total_weight, elements);
    }

    WeightedMatroidIntersectionResult<Weight> result;
    result.elements = elements;
    result.total_weight = total_weight;
    return result;
}

}  // namespace weighted_intersection_detail

template <class Weight, class IndependenceOracle1, class IndependenceOracle2>
WeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection_max(
    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2) {
    auto ignore = [](int, const Weight&, const std::vector<int>&) {};
    return weighted_intersection_detail::solve<true>(ground_size, weight, oracle1, oracle2,
                                                      ignore);
}

template <class Weight, class IndependenceOracle1, class IndependenceOracle2>
WeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection_min(
    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2) {
    auto ignore = [](int, const Weight&, const std::vector<int>&) {};
    return weighted_intersection_detail::solve<false>(ground_size, weight, oracle1, oracle2,
                                                       ignore);
}

template <class Weight, class IndependenceOracle1, class IndependenceOracle2, class OnSolution>
WeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection_max_each(
    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2, OnSolution on_solution) {
    return weighted_intersection_detail::solve<true>(ground_size, weight, oracle1, oracle2,
                                                      on_solution);
}

template <class Weight, class IndependenceOracle1, class IndependenceOracle2, class OnSolution>
WeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection_min_each(
    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2, OnSolution on_solution) {
    return weighted_intersection_detail::solve<false>(ground_size, weight, oracle1, oracle2,
                                                       on_solution);
}

template <class Weight, class IndependenceOracle1, class IndependenceOracle2>
WeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection(
    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,
    IndependenceOracle2 oracle2) {
    return weighted_matroid_intersection_max(ground_size, weight, oracle1, oracle2);
}

}  // namespace matroid
}  // namespace m1une

#endif  // M1UNE_MATROID_WEIGHTED_MATROID_INTERSECTION_HPP
