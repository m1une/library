#ifndef M1UNE_GRAPH_BFS_HPP
#define M1UNE_GRAPH_BFS_HPP 1

#include <algorithm>
#include <cassert>
#include <queue>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

struct BfsResult {
    std::vector<int> dist;
    std::vector<int> parent;
    std::vector<int> parent_edge;

    bool reachable(int v) const {
        assert(0 <= v && v < int(dist.size()));
        return dist[v] != -1;
    }

    std::vector<int> path(int t) const {
        assert(reachable(t));
        std::vector<int> result;
        for (int v = t; v != -1; v = parent[v]) result.push_back(v);
        std::reverse(result.begin(), result.end());
        return result;
    }
};

template <class T>
BfsResult bfs(const Graph<T>& g, const std::vector<int>& sources) {
    int n = g.size();
    BfsResult result;
    result.dist.assign(n, -1);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);

    std::queue<int> que;
    for (int s : sources) {
        assert(0 <= s && s < n);
        if (result.dist[s] != -1) continue;
        result.dist[s] = 0;
        que.push(s);
    }

    while (!que.empty()) {
        int v = que.front();
        que.pop();
        for (const auto& e : g[v]) {
            if (result.dist[e.to] != -1) continue;
            result.dist[e.to] = result.dist[v] + 1;
            result.parent[e.to] = v;
            result.parent_edge[e.to] = e.id;
            que.push(e.to);
        }
    }

    return result;
}

template <class T>
BfsResult bfs(const Graph<T>& g, int s) {
    return bfs(g, std::vector<int>{s});
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_BFS_HPP
