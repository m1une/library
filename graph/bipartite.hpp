#ifndef M1UNE_GRAPH_BIPARTITE_HPP
#define M1UNE_GRAPH_BIPARTITE_HPP 1

#include <queue>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

struct BipartiteResult {
    bool is_bipartite;
    std::vector<int> color;
};

template <class T>
BipartiteResult bipartite(const Graph<T>& g) {
    int n = g.size();
    BipartiteResult result;
    result.is_bipartite = true;
    result.color.assign(n, -1);

    std::vector<std::vector<int>> adjacency(n);
    for (const auto& e : g.edges()) {
        adjacency[e.from].push_back(e.to);
        adjacency[e.to].push_back(e.from);
    }

    std::queue<int> que;
    for (int s = 0; s < n; s++) {
        if (result.color[s] != -1) continue;
        result.color[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop();
            for (int to : adjacency[v]) {
                if (result.color[to] == -1) {
                    result.color[to] = result.color[v] ^ 1;
                    que.push(to);
                } else if (result.color[to] == result.color[v]) {
                    result.is_bipartite = false;
                    return result;
                }
            }
        }
    }

    return result;
}

template <class T>
bool is_bipartite(const Graph<T>& g) {
    return bipartite(g).is_bipartite;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_BIPARTITE_HPP
