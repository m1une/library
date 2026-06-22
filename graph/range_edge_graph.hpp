#ifndef M1UNE_GRAPH_RANGE_EDGE_GRAPH_HPP
#define M1UNE_GRAPH_RANGE_EDGE_GRAPH_HPP 1

#include <cassert>
#include <vector>

#include "graph.hpp"

namespace m1une {
namespace graph {

struct RangeEdgeNode {
    int vertex;
    int left;
    int right;
};

template <class T>
class RangeEdgeGraph {
    struct SegmentNode {
        int left = 0;
        int right = 0;
        int from_vertex = -1;
        int to_vertex = -1;
    };

    int _n;
    Graph<T> _graph;
    std::vector<SegmentNode> _segment;

    void assert_point(int point) const {
        (void)point;
        assert(0 <= point && point < _n);
    }

    void assert_range(int left, int right) const {
        (void)left;
        (void)right;
        assert(0 <= left && left <= right && right <= _n);
    }

    void build(int node, int left, int right) {
        _segment[node].left = left;
        _segment[node].right = right;
        if (right - left == 1) {
            _segment[node].from_vertex = left;
            _segment[node].to_vertex = left;
            return;
        }

        int middle = (left + right) / 2;
        build(node * 2, left, middle);
        build(node * 2 + 1, middle, right);

        int from_vertex = _graph.add_vertex();
        int to_vertex = _graph.add_vertex();
        _segment[node].from_vertex = from_vertex;
        _segment[node].to_vertex = to_vertex;

        _graph.add_directed_edge(_segment[node * 2].from_vertex, from_vertex, T());
        _graph.add_directed_edge(_segment[node * 2 + 1].from_vertex, from_vertex, T());
        _graph.add_directed_edge(to_vertex, _segment[node * 2].to_vertex, T());
        _graph.add_directed_edge(to_vertex, _segment[node * 2 + 1].to_vertex, T());
    }

    void collect(int node, int left, int right, bool from_side,
                 std::vector<RangeEdgeNode>& result) const {
        const auto& current = _segment[node];
        if (right <= current.left || current.right <= left) return;
        if (left <= current.left && current.right <= right) {
            int vertex = from_side ? current.from_vertex : current.to_vertex;
            result.push_back(RangeEdgeNode{vertex, current.left, current.right});
            return;
        }
        collect(node * 2, left, right, from_side, result);
        collect(node * 2 + 1, left, right, from_side, result);
    }

   public:
    RangeEdgeGraph() : RangeEdgeGraph(0) {}

    explicit RangeEdgeGraph(int point_count)
        : _n(point_count),
          _graph(point_count),
          _segment(point_count == 0 ? 1 : point_count * 4) {
        assert(point_count >= 0);
        if (point_count != 0) build(1, 0, point_count);
    }

    int size() const {
        return _n;
    }

    int point_vertex(int point) const {
        assert_point(point);
        return point;
    }

    int add_vertex() {
        return _graph.add_vertex();
    }

    Graph<T>& graph() {
        return _graph;
    }

    const Graph<T>& graph() const {
        return _graph;
    }

    std::vector<RangeEdgeNode> from_range_nodes(int left, int right) const {
        assert_range(left, right);
        std::vector<RangeEdgeNode> result;
        if (left != right) collect(1, left, right, true, result);
        return result;
    }

    std::vector<RangeEdgeNode> to_range_nodes(int left, int right) const {
        assert_range(left, right);
        std::vector<RangeEdgeNode> result;
        if (left != right) collect(1, left, right, false, result);
        return result;
    }

    int add_point_to_point(int from, int to, T cost) {
        assert_point(from);
        assert_point(to);
        return _graph.add_directed_edge(from, to, cost);
    }

    void add_point_to_range(int from, int left, int right, T cost) {
        assert_point(from);
        for (const auto& node : to_range_nodes(left, right)) {
            _graph.add_directed_edge(from, node.vertex, cost);
        }
    }

    void add_range_to_point(int left, int right, int to, T cost) {
        assert_point(to);
        for (const auto& node : from_range_nodes(left, right)) {
            _graph.add_directed_edge(node.vertex, to, cost);
        }
    }

    int add_range_to_range(int from_left, int from_right, int to_left, int to_right,
                           T cost) {
        assert_range(from_left, from_right);
        assert_range(to_left, to_right);
        if (from_left == from_right || to_left == to_right) return -1;

        int auxiliary = add_vertex();
        for (const auto& node : from_range_nodes(from_left, from_right)) {
            _graph.add_directed_edge(node.vertex, auxiliary, cost);
        }
        for (const auto& node : to_range_nodes(to_left, to_right)) {
            _graph.add_directed_edge(auxiliary, node.vertex, T());
        }
        return auxiliary;
    }
};

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_RANGE_EDGE_GRAPH_HPP
