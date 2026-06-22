#ifndef M1UNE_DS_SEGTREE_BEATS_HPP
#define M1UNE_DS_SEGTREE_BEATS_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <limits>
#include <vector>

namespace m1une {
namespace ds {

// Segment Tree Beats supporting range chmin/chmax/add and sum/min/max queries.
template <std::signed_integral T = long long>
struct SegtreeBeats {
   private:
    static constexpr T positive_infinity = std::numeric_limits<T>::max();
    static constexpr T negative_infinity = std::numeric_limits<T>::lowest();

    struct Node {
        T sum = 0;
        T maximum = negative_infinity;
        T second_maximum = negative_infinity;
        T minimum = positive_infinity;
        T second_minimum = positive_infinity;
        T lazy_add = 0;
        int maximum_count = 0;
        int minimum_count = 0;
        int length = 0;
    };

    int _n;
    std::vector<Node> _nodes;

    static Node make_leaf(T value) {
        Node node;
        node.sum = value;
        node.maximum = value;
        node.minimum = value;
        node.maximum_count = 1;
        node.minimum_count = 1;
        node.length = 1;
        return node;
    }

    static Node merge_nodes(const Node& left, const Node& right) {
        Node result;
        result.sum = left.sum + right.sum;
        result.length = left.length + right.length;

        result.maximum = std::max(left.maximum, right.maximum);
        result.maximum_count = 0;
        result.second_maximum = negative_infinity;
        if (left.maximum == result.maximum) {
            result.maximum_count += left.maximum_count;
            result.second_maximum =
                std::max(result.second_maximum, left.second_maximum);
        } else {
            result.second_maximum =
                std::max(result.second_maximum, left.maximum);
        }
        if (right.maximum == result.maximum) {
            result.maximum_count += right.maximum_count;
            result.second_maximum =
                std::max(result.second_maximum, right.second_maximum);
        } else {
            result.second_maximum =
                std::max(result.second_maximum, right.maximum);
        }

        result.minimum = std::min(left.minimum, right.minimum);
        result.minimum_count = 0;
        result.second_minimum = positive_infinity;
        if (left.minimum == result.minimum) {
            result.minimum_count += left.minimum_count;
            result.second_minimum =
                std::min(result.second_minimum, left.second_minimum);
        } else {
            result.second_minimum =
                std::min(result.second_minimum, left.minimum);
        }
        if (right.minimum == result.minimum) {
            result.minimum_count += right.minimum_count;
            result.second_minimum =
                std::min(result.second_minimum, right.second_minimum);
        } else {
            result.second_minimum =
                std::min(result.second_minimum, right.minimum);
        }
        return result;
    }

    void build(int node, int left, int right, const std::vector<T>& values) {
        if (right - left == 1) {
            _nodes[node] = make_leaf(values[left]);
            return;
        }
        int middle = left + (right - left) / 2;
        build(node * 2, left, middle, values);
        build(node * 2 + 1, middle, right, values);
        pull(node);
    }

    void pull(int node) {
        _nodes[node] = merge_nodes(
            _nodes[node * 2],
            _nodes[node * 2 + 1]
        );
    }

    void apply_add(int node, T value) {
        Node& current = _nodes[node];
        current.sum += value * T(current.length);
        current.maximum += value;
        current.minimum += value;
        if (current.second_maximum != negative_infinity) {
            current.second_maximum += value;
        }
        if (current.second_minimum != positive_infinity) {
            current.second_minimum += value;
        }
        current.lazy_add += value;
    }

    void apply_chmin(int node, T value) {
        Node& current = _nodes[node];
        if (current.maximum <= value) return;
        current.sum +=
            (value - current.maximum) * T(current.maximum_count);
        if (current.minimum == current.maximum) {
            current.minimum = value;
        } else if (current.second_minimum == current.maximum) {
            current.second_minimum = value;
        }
        current.maximum = value;
    }

    void apply_chmax(int node, T value) {
        Node& current = _nodes[node];
        if (value <= current.minimum) return;
        current.sum +=
            (value - current.minimum) * T(current.minimum_count);
        if (current.maximum == current.minimum) {
            current.maximum = value;
        } else if (current.second_maximum == current.minimum) {
            current.second_maximum = value;
        }
        current.minimum = value;
    }

    void push(int node) {
        Node& current = _nodes[node];
        if (current.length == 1) {
            current.lazy_add = 0;
            return;
        }
        if (current.lazy_add != 0) {
            apply_add(node * 2, current.lazy_add);
            apply_add(node * 2 + 1, current.lazy_add);
            current.lazy_add = 0;
        }
        apply_chmin(node * 2, current.maximum);
        apply_chmin(node * 2 + 1, current.maximum);
        apply_chmax(node * 2, current.minimum);
        apply_chmax(node * 2 + 1, current.minimum);
    }

    void range_chmin(
        int node,
        int left,
        int right,
        int query_left,
        int query_right,
        T value
    ) {
        Node& current = _nodes[node];
        if (
            query_right <= left ||
            right <= query_left ||
            current.maximum <= value
        ) {
            return;
        }
        if (
            query_left <= left &&
            right <= query_right &&
            current.second_maximum < value
        ) {
            apply_chmin(node, value);
            return;
        }
        push(node);
        int middle = left + (right - left) / 2;
        range_chmin(
            node * 2,
            left,
            middle,
            query_left,
            query_right,
            value
        );
        range_chmin(
            node * 2 + 1,
            middle,
            right,
            query_left,
            query_right,
            value
        );
        pull(node);
    }

    void range_chmax(
        int node,
        int left,
        int right,
        int query_left,
        int query_right,
        T value
    ) {
        Node& current = _nodes[node];
        if (
            query_right <= left ||
            right <= query_left ||
            value <= current.minimum
        ) {
            return;
        }
        if (
            query_left <= left &&
            right <= query_right &&
            value < current.second_minimum
        ) {
            apply_chmax(node, value);
            return;
        }
        push(node);
        int middle = left + (right - left) / 2;
        range_chmax(
            node * 2,
            left,
            middle,
            query_left,
            query_right,
            value
        );
        range_chmax(
            node * 2 + 1,
            middle,
            right,
            query_left,
            query_right,
            value
        );
        pull(node);
    }

    void range_add(
        int node,
        int left,
        int right,
        int query_left,
        int query_right,
        T value
    ) {
        if (query_right <= left || right <= query_left) return;
        if (query_left <= left && right <= query_right) {
            apply_add(node, value);
            return;
        }
        push(node);
        int middle = left + (right - left) / 2;
        range_add(
            node * 2,
            left,
            middle,
            query_left,
            query_right,
            value
        );
        range_add(
            node * 2 + 1,
            middle,
            right,
            query_left,
            query_right,
            value
        );
        pull(node);
    }

    Node range_query(
        int node,
        int left,
        int right,
        int query_left,
        int query_right
    ) {
        if (query_left <= left && right <= query_right) {
            return _nodes[node];
        }
        push(node);
        int middle = left + (right - left) / 2;
        if (query_right <= middle) {
            return range_query(
                node * 2,
                left,
                middle,
                query_left,
                query_right
            );
        }
        if (middle <= query_left) {
            return range_query(
                node * 2 + 1,
                middle,
                right,
                query_left,
                query_right
            );
        }
        return merge_nodes(
            range_query(
                node * 2,
                left,
                middle,
                query_left,
                query_right
            ),
            range_query(
                node * 2 + 1,
                middle,
                right,
                query_left,
                query_right
            )
        );
    }

   public:
    SegtreeBeats() : _n(0) {}

    explicit SegtreeBeats(int n)
        : _n(n) {
        assert(0 <= n);
        if (_n != 0) {
            _nodes.resize(std::size_t(_n) * 4);
            std::vector<T> values(_n, T(0));
            build(1, 0, _n, values);
        }
    }

    explicit SegtreeBeats(const std::vector<T>& values)
        : _n(int(values.size())),
          _nodes(values.empty() ? 0 : values.size() * 4) {
        if (_n != 0) build(1, 0, _n, values);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    void chmin(int left, int right, T value) {
        assert(0 <= left && left <= right && right <= _n);
        if (left != right) {
            range_chmin(1, 0, _n, left, right, value);
        }
    }

    void chmax(int left, int right, T value) {
        assert(0 <= left && left <= right && right <= _n);
        if (left != right) {
            range_chmax(1, 0, _n, left, right, value);
        }
    }

    void add(int left, int right, T value) {
        assert(0 <= left && left <= right && right <= _n);
        if (left != right) {
            range_add(1, 0, _n, left, right, value);
        }
    }

    void range_chmin(int left, int right, T value) {
        chmin(left, right, value);
    }

    void range_chmax(int left, int right, T value) {
        chmax(left, right, value);
    }

    void range_add(int left, int right, T value) {
        add(left, right, value);
    }

    T sum(int left, int right) {
        assert(0 <= left && left <= right && right <= _n);
        return left == right
            ? T(0)
            : range_query(1, 0, _n, left, right).sum;
    }

    T min(int left, int right) {
        assert(0 <= left && left < right && right <= _n);
        return range_query(1, 0, _n, left, right).minimum;
    }

    T max(int left, int right) {
        assert(0 <= left && left < right && right <= _n);
        return range_query(1, 0, _n, left, right).maximum;
    }

    T range_sum(int left, int right) {
        return sum(left, right);
    }

    T range_min(int left, int right) {
        return min(left, right);
    }

    T range_max(int left, int right) {
        return max(left, right);
    }

    T all_sum() const {
        return _n == 0 ? T(0) : _nodes[1].sum;
    }

    T all_min() const {
        assert(_n != 0);
        return _nodes[1].minimum;
    }

    T all_max() const {
        assert(_n != 0);
        return _nodes[1].maximum;
    }

    T get(int index) {
        assert(0 <= index && index < _n);
        return sum(index, index + 1);
    }

    T operator[](int index) {
        return get(index);
    }

    void set(int index, T value) {
        assert(0 <= index && index < _n);
        T current = get(index);
        add(index, index + 1, value - current);
    }

    std::vector<T> to_vector() {
        std::vector<T> result(_n);
        for (int index = 0; index < _n; ++index) {
            result[index] = get(index);
        }
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_SEGTREE_BEATS_HPP
