#ifndef M1UNE_GRAPH_DOMINATOR_TREE_HPP
#define M1UNE_GRAPH_DOMINATOR_TREE_HPP 1

#include <cassert>
#include <utility>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct DominatorTree {
    int root;
    std::vector<int> immediate_dominator;
    std::vector<std::vector<int>> children;
    std::vector<int> dfs_order;
    std::vector<int> tin;
    std::vector<int> tout;

    int size() const {
        return int(immediate_dominator.size());
    }

    bool reachable(int vertex) const {
        assert(0 <= vertex && vertex < size());
        return immediate_dominator[vertex] != -1;
    }

    bool dominates(int ancestor, int vertex) const {
        assert(0 <= ancestor && ancestor < size());
        assert(0 <= vertex && vertex < size());
        return
            reachable(ancestor) &&
            reachable(vertex) &&
            tin[ancestor] <= tin[vertex] &&
            tin[vertex] < tout[ancestor];
    }
};

// Lengauer-Tarjan immediate dominators from one start vertex.
template <class T>
DominatorTree dominator_tree(const Graph<T>& graph, int root) {
    int n = graph.size();
    assert(0 <= root && root < n);

    std::vector<int> dfs_index(n, -1);
    std::vector<int> vertex;
    std::vector<int> parent_vertex(n, -1);
    std::vector<std::pair<int, int>> stack;
    dfs_index[root] = 0;
    vertex.push_back(root);
    stack.emplace_back(root, 0);

    while (!stack.empty()) {
        int current = stack.back().first;
        int& edge_index = stack.back().second;
        if (edge_index == int(graph[current].size())) {
            stack.pop_back();
            continue;
        }
        const auto& edge = graph[current][edge_index++];
        if (!edge.alive || dfs_index[edge.to] != -1) continue;
        parent_vertex[edge.to] = current;
        dfs_index[edge.to] = int(vertex.size());
        vertex.push_back(edge.to);
        stack.emplace_back(edge.to, 0);
    }

    int reachable_count = int(vertex.size());
    std::vector<std::vector<int>> predecessor(reachable_count);
    for (int from : vertex) {
        for (const auto& edge : graph[from]) {
            if (!edge.alive || dfs_index[edge.to] == -1) continue;
            predecessor[dfs_index[edge.to]].push_back(dfs_index[from]);
        }
    }

    std::vector<int> parent(reachable_count, -1);
    for (int index = 1; index < reachable_count; ++index) {
        parent[index] = dfs_index[parent_vertex[vertex[index]]];
    }

    std::vector<int> semi(reachable_count);
    std::vector<int> idom(reachable_count, -1);
    std::vector<int> ancestor(reachable_count, -1);
    std::vector<int> label(reachable_count);
    std::vector<std::vector<int>> bucket(reachable_count);
    for (int index = 0; index < reachable_count; ++index) {
        semi[index] = index;
        label[index] = index;
    }

    auto compress = [&](int start) {
        std::vector<int> path;
        int current = start;
        while (
            ancestor[current] != -1 &&
            ancestor[ancestor[current]] != -1
        ) {
            path.push_back(current);
            current = ancestor[current];
        }
        for (int index = int(path.size()) - 1; index >= 0; --index) {
            int node = path[index];
            int parent_node = ancestor[node];
            if (semi[label[parent_node]] < semi[label[node]]) {
                label[node] = label[parent_node];
            }
            ancestor[node] = ancestor[parent_node];
        }
    };

    auto eval = [&](int node) {
        if (ancestor[node] == -1) return label[node];
        compress(node);
        int parent_node = ancestor[node];
        if (semi[label[parent_node]] < semi[label[node]]) {
            return label[parent_node];
        }
        return label[node];
    };

    for (int current = reachable_count - 1; current >= 1; --current) {
        for (int previous : predecessor[current]) {
            semi[current] = std::min(semi[current], semi[eval(previous)]);
        }
        bucket[semi[current]].push_back(current);
        ancestor[current] = parent[current];

        int parent_node = parent[current];
        for (int node : bucket[parent_node]) {
            int best = eval(node);
            idom[node] =
                semi[best] < semi[node] ? best : parent_node;
        }
        bucket[parent_node].clear();
    }

    for (int current = 1; current < reachable_count; ++current) {
        if (idom[current] != semi[current]) {
            idom[current] = idom[idom[current]];
        }
    }
    idom[0] = 0;

    DominatorTree result;
    result.root = root;
    result.immediate_dominator.assign(n, -1);
    result.children.assign(n, {});
    result.dfs_order = vertex;
    for (int index = 0; index < reachable_count; ++index) {
        int current = vertex[index];
        int dominator = vertex[idom[index]];
        result.immediate_dominator[current] = dominator;
        if (current != root) result.children[dominator].push_back(current);
    }

    result.tin.assign(n, -1);
    result.tout.assign(n, -1);
    int timer = 0;
    std::vector<std::pair<int, int>> tree_stack;
    tree_stack.emplace_back(root, 0);
    result.tin[root] = timer++;
    while (!tree_stack.empty()) {
        int current = tree_stack.back().first;
        int& child_index = tree_stack.back().second;
        if (child_index == int(result.children[current].size())) {
            result.tout[current] = timer;
            tree_stack.pop_back();
            continue;
        }
        int child = result.children[current][child_index++];
        result.tin[child] = timer++;
        tree_stack.emplace_back(child, 0);
    }
    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_DOMINATOR_TREE_HPP
