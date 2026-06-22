#ifndef M1UNE_OPTIMIZATION_LI_CHAO_TREE_HPP
#define M1UNE_OPTIMIZATION_LI_CHAO_TREE_HPP 1

#include <cassert>
#include <concepts>
#include <cstddef>
#include <limits>
#include <numeric>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

#include "convex_hull_trick.hpp"

namespace m1une {
namespace optimization {

// Dynamic Li Chao tree over an integral half-open coordinate domain.
template <std::signed_integral T, LineOptimization Objective = LineOptimization::Minimize>
struct LiChaoTree {
    using Line = LinearFunction<T>;
    using value_type = typename Line::value_type;

   private:
    struct Node {
        Line line;
        bool has_line;
        int left;
        int right;

        Node() : has_line(false), left(-1), right(-1) {}

        explicit Node(Line value) : line(std::move(value)), has_line(true), left(-1), right(-1) {}
    };

    T _left;
    T _right;
    int _root;
    std::vector<Node> _nodes;

    static bool better(value_type first, value_type second) {
        if constexpr (Objective == LineOptimization::Minimize) {
            return first < second;
        } else {
            return second < first;
        }
    }

    int new_node() {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back();
        return int(_nodes.size()) - 1;
    }

    int new_node(Line line) {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back(std::move(line));
        return int(_nodes.size()) - 1;
    }

    int add_line_node(int node, T left, T right, Line line) {
        if (node == -1) return new_node(std::move(line));
        if (!_nodes[node].has_line) {
            _nodes[node].line = std::move(line);
            _nodes[node].has_line = true;
            return node;
        }

        T middle = std::midpoint(left, right);
        bool left_better = better(line(left), _nodes[node].line(left));
        bool middle_better = better(line(middle), _nodes[node].line(middle));
        if (middle_better) std::swap(line, _nodes[node].line);
        if (middle == left) return node;

        if (left_better != middle_better) {
            int child = add_line_node(_nodes[node].left, left, middle, std::move(line));
            _nodes[node].left = child;
        } else {
            int child = add_line_node(_nodes[node].right, middle, right, std::move(line));
            _nodes[node].right = child;
        }
        return node;
    }

    int add_segment_node(int node, T left, T right, T query_left, T query_right, const Line& line) {
        if (query_right <= left || right <= query_left) return node;
        if (query_left <= left && right <= query_right) {
            return add_line_node(node, left, right, line);
        }
        if (node == -1) node = new_node();

        T middle = std::midpoint(left, right);
        if (middle == left) return add_line_node(node, left, right, line);
        int left_child = add_segment_node(_nodes[node].left, left, middle, query_left, query_right, line);
        int right_child = add_segment_node(_nodes[node].right, middle, right, query_left, query_right, line);
        _nodes[node].left = left_child;
        _nodes[node].right = right_child;
        return node;
    }

   public:
    LiChaoTree() : _left(0), _right(0), _root(-1) {}

    LiChaoTree(T left, T right) : _left(left), _right(right), _root(-1) {
        assert(left <= right);
    }

    T left_bound() const {
        return _left;
    }

    T right_bound() const {
        return _right;
    }

    bool empty() const {
        return _root == -1;
    }

    std::size_t node_count() const {
        return _nodes.size();
    }

    void reserve(std::size_t node_capacity) {
        _nodes.reserve(node_capacity);
    }

    void clear() {
        _root = -1;
        _nodes.clear();
    }

    void add_line(T slope, T intercept) {
        assert(_left < _right);
        _root = add_line_node(_root, _left, _right, Line(slope, intercept));
    }

    void add_segment(T segment_left, T segment_right, T slope, T intercept) {
        assert(_left <= segment_left && segment_left <= segment_right && segment_right <= _right);
        if (segment_left == segment_right) return;
        _root = add_segment_node(_root, _left, _right, segment_left, segment_right, Line(slope, intercept));
    }

    // Returns nullopt when no inserted line covers x.
    std::optional<value_type> query(T x) const {
        assert(_left <= x && x < _right);
        std::optional<value_type> result;
        int node = _root;
        T left = _left;
        T right = _right;
        while (node != -1) {
            if (_nodes[node].has_line) {
                value_type candidate = _nodes[node].line(x);
                if (!result || better(candidate, *result)) {
                    result = candidate;
                }
            }

            T middle = std::midpoint(left, right);
            if (middle == left) break;
            if (x < middle) {
                node = _nodes[node].left;
                right = middle;
            } else {
                node = _nodes[node].right;
                left = middle;
            }
        }
        return result;
    }

    value_type get(T x) const {
        std::optional<value_type> result = query(x);
        assert(result.has_value());
        return result.value_or(value_type());
    }
};

template <std::signed_integral T>
using MinLiChaoTree = LiChaoTree<T, LineOptimization::Minimize>;

template <std::signed_integral T>
using MaxLiChaoTree = LiChaoTree<T, LineOptimization::Maximize>;

}  // namespace optimization
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_LI_CHAO_TREE_HPP
