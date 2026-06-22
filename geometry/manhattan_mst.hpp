#ifndef M1UNE_GEOMETRY_MANHATTAN_MST_HPP
#define M1UNE_GEOMETRY_MANHATTAN_MST_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <limits>
#include <map>
#include <numeric>
#include <utility>
#include <vector>

#include "../ds/dsu/dsu.hpp"
#include "point.hpp"

namespace m1une {
namespace geometry {

template <class T>
struct ManhattanMstEdge {
    int from;
    int to;
    T cost;
};

template <class T>
struct ManhattanMst {
    T cost;
    std::vector<ManhattanMstEdge<T>> edges;
};

// Returns O(n) edges containing a Manhattan minimum spanning tree.
template <std::integral T>
std::vector<ManhattanMstEdge<wide_type<T>>> manhattan_mst_edges(const std::vector<Point<T>>& points) {
    using W = wide_type<T>;
    assert(points.size() <= std::size_t(std::numeric_limits<int>::max()));
    int n = int(points.size());
    std::vector<Point<W>> transformed;
    transformed.reserve(points.size());
    for (const auto& point : points) {
        transformed.emplace_back(W(point.x), W(point.y));
    }

    std::vector<int> order(n);
    std::iota(order.begin(), order.end(), 0);
    std::vector<ManhattanMstEdge<W>> edges;
    edges.reserve(std::size_t(4) * points.size());

    for (int direction = 0; direction < 4; direction++) {
        std::sort(order.begin(), order.end(), [&transformed](int i, int j) {
            W first = transformed[i].x + transformed[i].y;
            W second = transformed[j].x + transformed[j].y;
            if (first != second) return first < second;
            if (transformed[i].x != transformed[j].x) {
                return transformed[i].x < transformed[j].x;
            }
            return i < j;
        });

        std::map<W, int> sweep;
        for (int i : order) {
            auto it = sweep.lower_bound(-transformed[i].y);
            while (it != sweep.end()) {
                int j = it->second;
                if (transformed[i].x - transformed[j].x < transformed[i].y - transformed[j].y) {
                    break;
                }

                W dx = W(points[i].x) - W(points[j].x);
                W dy = W(points[i].y) - W(points[j].y);
                if (dx < 0) dx = -dx;
                if (dy < 0) dy = -dy;
                edges.push_back(ManhattanMstEdge<W>{i, j, dx + dy});
                it = sweep.erase(it);
            }
            sweep[-transformed[i].y] = i;
        }

        for (auto& point : transformed) {
            if (direction & 1) {
                point.x = -point.x;
            } else {
                std::swap(point.x, point.y);
            }
        }
    }
    return edges;
}

// Returns a Manhattan minimum spanning tree.
template <std::integral T>
ManhattanMst<wide_type<T>> manhattan_mst(const std::vector<Point<T>>& points) {
    using W = wide_type<T>;
    auto candidates = manhattan_mst_edges(points);
    std::sort(candidates.begin(), candidates.end(), [](const auto& a, const auto& b) { return a.cost < b.cost; });

    m1une::ds::Dsu dsu(int(points.size()));
    ManhattanMst<W> result;
    result.cost = W(0);
    result.edges.reserve(points.empty() ? 0 : points.size() - 1);
    for (const auto& edge : candidates) {
        if (dsu.same(edge.from, edge.to)) continue;
        dsu.merge(edge.from, edge.to);
        result.cost += edge.cost;
        result.edges.push_back(edge);
        if (result.edges.size() + 1 == points.size()) break;
    }
    assert(points.empty() || result.edges.size() + 1 == points.size());
    return result;
}

}  // namespace geometry
}  // namespace m1une

#endif  // M1UNE_GEOMETRY_MANHATTAN_MST_HPP
