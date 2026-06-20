#ifndef M1UNE_GRAPH_ZERO_ONE_BFS_HPP
#define M1UNE_GRAPH_ZERO_ONE_BFS_HPP 1

#include <algorithm>
#include <cassert>
#include <deque>
#include <limits>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct ZeroOneBfsResult {
    std::vector<int> dist;
    std::vector<int> parent;
    std::vector<int> parent_edge;
    int inf;

    bool reachable(int v) const {
        assert(0 <= v && v < int(dist.size()));
        return dist[v] != inf;
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
ZeroOneBfsResult zero_one_bfs(const Graph<T>& g, const std::vector<int>& sources,
                              int inf = std::numeric_limits<int>::max() / 2) {
    int n = g.size();
    ZeroOneBfsResult result;
    result.dist.assign(n, inf);
    result.parent.assign(n, -1);
    result.parent_edge.assign(n, -1);
    result.inf = inf;

    std::deque<int> deq;
    for (int s : sources) {
        assert(0 <= s && s < n);
        if (result.dist[s] == 0) continue;
        result.dist[s] = 0;
        deq.push_back(s);
    }

    while (!deq.empty()) {
        int v = deq.front();
        deq.pop_front();
        for (const auto& e : g[v]) {
            if (!e.alive) continue;
            int w;
            if (e.cost == T(0)) {
                w = 0;
            } else {
                assert(e.cost == T(1));
                w = 1;
            }
            int nd = result.dist[v] + w;
            if (result.dist[e.to] <= nd) continue;
            result.dist[e.to] = nd;
            result.parent[e.to] = v;
            result.parent_edge[e.to] = e.id;
            if (w == 0) {
                deq.push_front(e.to);
            } else {
                deq.push_back(e.to);
            }
        }
    }

    return result;
}

template <class T>
ZeroOneBfsResult zero_one_bfs(const Graph<T>& g, int s, int inf = std::numeric_limits<int>::max() / 2) {
    return zero_one_bfs(g, std::vector<int>{s}, inf);
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_ZERO_ONE_BFS_HPP
