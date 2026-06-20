#ifndef M1UNE_GRAPH_CONNECTED_COMPONENTS_HPP
#define M1UNE_GRAPH_CONNECTED_COMPONENTS_HPP 1

#include <cassert>
#include <vector>

#include "../ds/dsu/dsu.hpp"
#include "graph.hpp"

namespace m1une {
namespace graph {

struct ConnectedComponents {
    int count;
    std::vector<int> comp;
    std::vector<std::vector<int>> groups;

    bool same(int u, int v) const {
        assert(0 <= u && u < int(comp.size()));
        assert(0 <= v && v < int(comp.size()));
        return comp[u] == comp[v];
    }
};

template <class T>
ConnectedComponents connected_components(const Graph<T>& g) {
    int n = g.size();
    m1une::ds::Dsu dsu(n);
    for (const auto& e : g.edges()) dsu.merge(e.from, e.to);

    ConnectedComponents result;
    result.comp.assign(n, 0);
    std::vector<int> leader_to_comp(n, -1);
    for (int v = 0; v < n; v++) {
        int leader = dsu.leader(v);
        if (leader_to_comp[leader] == -1) {
            leader_to_comp[leader] = int(result.groups.size());
            result.groups.push_back({});
        }
        int c = leader_to_comp[leader];
        result.comp[v] = c;
        result.groups[c].push_back(v);
    }
    result.count = int(result.groups.size());

    return result;
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_CONNECTED_COMPONENTS_HPP
