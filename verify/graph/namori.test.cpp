#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../graph/namori.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <utility>
#include <vector>

namespace {

void test_features() {
    m1une::graph::Graph<long long> graph(7);
    int e01 = graph.add_edge(0, 1, 2);
    int e12 = graph.add_edge(1, 2, 3);
    int e20 = graph.add_edge(2, 0, 4);
    graph.add_edge(1, 3, 5);
    graph.add_edge(3, 4, 6);
    int loop = graph.add_edge(5, 5, 7);
    graph.add_edge(5, 6, 8);

    auto optional = m1une::graph::namori_decomposition(graph);
    assert(optional.has_value());
    const auto& result = *optional;
    assert(result.component_count == 2);
    assert(result.cycles.size() == 2);
    assert(result.on_cycle[0]);
    assert(result.on_cycle[1]);
    assert(result.on_cycle[2]);
    assert(!result.on_cycle[3]);
    assert(!result.on_cycle[4]);
    assert(result.on_cycle[5]);
    assert(!result.on_cycle[6]);
    assert(result.same_component(0, 4));
    assert(!result.same_component(0, 5));
    assert(result.same_tree(1, 4));
    assert(!result.same_tree(0, 4));
    assert(result.cycle_root[4] == 1);
    assert(result.parent[4] == 3);
    assert(result.parent[3] == 1);
    assert(result.depth[4] == 2);
    assert(result.dist_to_cycle[4] == 11);
    assert(result.cycle_root[6] == 5);
    assert(result.dist_to_cycle[6] == 8);

    std::set<int> first_cycle_edges;
    for (int id : result.cycle_edge_ids[result.component[0]]) first_cycle_edges.insert(id);
    assert((first_cycle_edges == std::set<int>{e01, e12, e20}));
    int loop_component = result.component[5];
    assert(result.cycles[loop_component] == std::vector<int>({5}));
    assert(result.cycle_edge_ids[loop_component] == std::vector<int>({loop}));

    m1une::graph::Graph<int> parallel(2);
    int first = parallel.add_edge(0, 1);
    int second = parallel.add_edge(0, 1);
    auto two_cycle = m1une::graph::decompose_namori(parallel);
    assert(two_cycle.has_value());
    assert(two_cycle->cycles[0].size() == 2);
    std::set<int> parallel_ids(
        two_cycle->cycle_edge_ids[0].begin(),
        two_cycle->cycle_edge_ids[0].end()
    );
    assert((parallel_ids == std::set<int>{first, second}));

    m1une::graph::Graph<int> tree(3);
    tree.add_edge(0, 1);
    tree.add_edge(1, 2);
    assert(!m1une::graph::namori_decomposition(tree).has_value());

    m1une::graph::Graph<int> bicyclic(5);
    bicyclic.add_edge(0, 1);
    bicyclic.add_edge(1, 2);
    bicyclic.add_edge(2, 0);
    bicyclic.add_edge(2, 3);
    bicyclic.add_edge(3, 4);
    int removable = bicyclic.add_edge(4, 2);
    assert(!m1une::graph::namori_decomposition(bicyclic).has_value());
    bicyclic.erase_edge(removable);
    auto inactive_ignored = m1une::graph::namori_decomposition(bicyclic);
    assert(inactive_ignored.has_value());
    assert(inactive_ignored->component_count == 1);

    m1une::graph::Graph<int> empty;
    auto empty_result = m1une::graph::namori_decomposition(empty);
    assert(empty_result.has_value());
    assert(empty_result->component_count == 0);
}

void test_randomized() {
    std::uint64_t state = 123456789;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    for (int trial = 0; trial < 1000; trial++) {
        int n = 1 + int(random() % 150);
        int component_count = 1 + int(random() % std::min(n, 10));
        std::vector<int> component_size(component_count, 1);
        for (int i = component_count; i < n; i++) component_size[random() % component_count]++;

        m1une::graph::Graph<long long> graph(n);
        std::vector<int> expected_component(n, -1);
        int offset = 0;
        for (int component = 0; component < component_count; component++) {
            int size = component_size[component];
            int cycle_size = 1 + int(random() % size);
            for (int i = 0; i < size; i++) expected_component[offset + i] = component;

            if (cycle_size == 1) {
                graph.add_edge(offset, offset, 1 + random() % 1000);
            } else if (cycle_size == 2) {
                graph.add_edge(offset, offset + 1, 1 + random() % 1000);
                graph.add_edge(offset, offset + 1, 1 + random() % 1000);
            } else {
                for (int i = 0; i < cycle_size; i++) {
                    graph.add_edge(
                        offset + i,
                        offset + (i + 1) % cycle_size,
                        1 + random() % 1000
                    );
                }
            }
            for (int i = cycle_size; i < size; i++) {
                int parent = int(random() % i);
                graph.add_edge(offset + i, offset + parent, 1 + random() % 1000);
            }
            offset += size;
        }

        auto optional = m1une::graph::namori_decomposition(graph);
        assert(optional.has_value());
        const auto& result = *optional;
        assert(result.component_count == component_count);

        int cycle_vertex_count = 0;
        for (int component = 0; component < result.component_count; component++) {
            const auto& cycle = result.cycles[component];
            const auto& edge_ids = result.cycle_edge_ids[component];
            const auto& edge_costs = result.cycle_edge_costs[component];
            assert(!cycle.empty());
            assert(cycle.size() == edge_ids.size());
            assert(cycle.size() == edge_costs.size());
            cycle_vertex_count += int(cycle.size());
            for (int i = 0; i < int(cycle.size()); i++) {
                int from = cycle[i];
                int to = cycle[(i + 1) % cycle.size()];
                bool found = false;
                for (const auto& edge : graph[from]) {
                    if (edge.id == edge_ids[i] && edge.to == to && edge.cost == edge_costs[i]) {
                        found = true;
                        break;
                    }
                }
                assert(found);
            }
        }

        int counted_cycle_vertices = 0;
        for (int v = 0; v < n; v++) {
            assert(0 <= result.component[v] && result.component[v] < component_count);
            assert(expected_component[v] == expected_component[result.cycle_root[v]]);
            assert(result.cycles[result.component[v]][result.cycle_position[v]] == result.cycle_root[v]);
            if (result.on_cycle[v]) {
                counted_cycle_vertices++;
                assert(result.cycle_root[v] == v);
                assert(result.parent[v] == -1);
                assert(result.parent_edge[v] == -1);
                assert(result.depth[v] == 0);
                assert(result.dist_to_cycle[v] == 0);
            } else {
                int parent = result.parent[v];
                assert(parent != -1);
                assert(result.depth[parent] + 1 == result.depth[v]);
                assert(result.cycle_root[parent] == result.cycle_root[v]);
                bool found = false;
                for (const auto& edge : graph[v]) {
                    if (edge.id == result.parent_edge[v] && edge.to == parent) {
                        assert(result.dist_to_cycle[v] == result.dist_to_cycle[parent] + edge.cost);
                        found = true;
                    }
                }
                assert(found);
            }
        }
        assert(counted_cycle_vertices == cycle_vertex_count);

        std::vector<int> child_count(n, 0);
        for (int v = 0; v < n; v++) {
            for (int child : result.children[v]) {
                assert(result.parent[child] == v);
                child_count[child]++;
            }
        }
        for (int v = 0; v < n; v++) {
            assert(child_count[v] == int(!result.on_cycle[v]));
        }
    }
}

}  // namespace

int main() {
    test_features();
    test_randomized();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
