#ifndef M1UNE_TREE_REROOTING_DP_HPP
#define M1UNE_TREE_REROOTING_DP_HPP 1

#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace tree {

template <class T, class DP, class Merge, class AddVertex, class AddEdge>
std::vector<DP> rerooting_dp(const m1une::graph::Graph<T>& g, DP id, Merge merge, AddVertex add_vertex,
                             AddEdge add_edge) {
    int n = g.size();
    std::vector<int> parent(n, -2), parent_edge(n, -1), order;
    order.reserve(n);
    for (int root = 0; root < n; root++) {
        if (parent[root] != -2) continue;
        parent[root] = -1;
        std::vector<int> stack = {root};
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            order.push_back(v);
            for (const auto& e : g[v]) {
                if (!e.alive) continue;
                if (parent[e.to] != -2) continue;
                parent[e.to] = v;
                parent_edge[e.to] = e.id;
                stack.push_back(e.to);
            }
        }
    }

    std::vector<DP> down(n, id), outside(n, id), answer(n, id);
    for (int i = n - 1; i >= 0; i--) {
        int v = order[i];
        DP acc = id;
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            if (parent[e.to] != v) continue;
            acc = merge(acc, add_edge(down[e.to], e));
        }
        down[v] = add_vertex(acc, v);
    }

    for (int v : order) {
        int d = int(g[v].size());
        std::vector<DP> contrib(d, id);
        for (int i = 0; i < d; i++) {
            const auto& e = g[v][i];
            if (!e.alive) continue;
            if (parent[e.to] == v) {
                contrib[i] = add_edge(down[e.to], e);
            } else if (parent[v] == e.to && parent_edge[v] == e.id) {
                contrib[i] = add_edge(outside[v], e);
            }
        }

        std::vector<DP> pref(d + 1, id), suff(d + 1, id);
        for (int i = 0; i < d; i++) pref[i + 1] = merge(pref[i], contrib[i]);
        for (int i = d - 1; i >= 0; i--) suff[i] = merge(contrib[i], suff[i + 1]);
        answer[v] = add_vertex(pref[d], v);

        for (int i = 0; i < d; i++) {
            const auto& e = g[v][i];
            if (!e.alive) continue;
            if (parent[e.to] != v) continue;
            outside[e.to] = add_vertex(merge(pref[i], suff[i + 1]), v);
        }
    }

    return answer;
}

}  // namespace tree
}  // namespace m1une

#endif  // M1UNE_TREE_REROOTING_DP_HPP
