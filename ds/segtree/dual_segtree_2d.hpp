#ifndef M1UNE_DUAL_SEGTREE_2D_HPP
#define M1UNE_DUAL_SEGTREE_2D_HPP 1

#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

#include "../../math/bit_ceil.hpp"
#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

// A static compressed 2D dual segment tree.
// It supports rectangle monoid updates and point queries on registered points.
// Monoid::op must be commutative.
template <class Monoid, class X = int, class Y = X>
requires m1une::monoid::IsMonoid<Monoid>
struct DualSegtree2D {
    using T = typename Monoid::value_type;
    using point_type = std::pair<X, Y>;
    using weighted_point_type = std::tuple<X, Y, T>;

private:
    int _n;
    int _size;
    int _point_count;
    std::vector<X> _xs;
    std::vector<std::vector<Y>> _ys;
    std::vector<std::vector<T>> _lazy;
    std::vector<std::vector<T>> _values;

    static std::vector<point_type> normalize_points(std::vector<point_type> points) {
        std::sort(points.begin(), points.end());
        points.erase(std::unique(points.begin(), points.end()), points.end());
        return points;
    }

    int x_index(const X& x) const {
        auto it = std::lower_bound(_xs.begin(), _xs.end(), x);
        if (it == _xs.end() || *it != x) return -1;
        return int(it - _xs.begin());
    }

    int y_index(int node, const Y& y) const {
        const auto& ys = _ys[node];
        auto it = std::lower_bound(ys.begin(), ys.end(), y);
        if (it == ys.end() || *it != y) return -1;
        return int(it - ys.begin());
    }

    void apply_y(int node, const Y& lower, const Y& upper, const T& value) {
        const auto& ys = _ys[node];
        if (ys.empty()) return;
        int left = int(std::lower_bound(ys.begin(), ys.end(), lower) - ys.begin());
        int right = int(std::lower_bound(ys.begin(), ys.end(), upper) - ys.begin());
        int size = int(ys.size());
        left += size;
        right += size;
        while (left < right) {
            if (left & 1) {
                _lazy[node][left] = Monoid::op(value, _lazy[node][left]);
                left++;
            }
            if (right & 1) {
                --right;
                _lazy[node][right] = Monoid::op(value, _lazy[node][right]);
            }
            left >>= 1;
            right >>= 1;
        }
    }

    T get_y(int node, const Y& y) const {
        int position = y_index(node, y);
        assert(position != -1);
        int size = int(_ys[node].size());
        T result = Monoid::id();
        for (int index = size + position; index; index >>= 1) {
            result = Monoid::op(_lazy[node][index], result);
        }
        return result;
    }

public:
    DualSegtree2D()
        : _n(0), _size(1), _point_count(0), _ys(2), _lazy(2) {}

    explicit DualSegtree2D(const std::vector<point_type>& points) {
        build(points);
    }

    explicit DualSegtree2D(std::vector<point_type>&& points) {
        build(std::move(points));
    }

    explicit DualSegtree2D(const std::vector<weighted_point_type>& points) {
        std::vector<point_type> coordinates;
        coordinates.reserve(points.size());
        for (const auto& [x, y, value] : points) {
            (void)value;
            coordinates.emplace_back(x, y);
        }
        build(std::move(coordinates));
        for (const auto& [x, y, value] : points) apply(x, y, value);
    }

    void build(std::vector<point_type> points) {
        points = normalize_points(std::move(points));
        _point_count = int(points.size());

        _xs.clear();
        _xs.reserve(points.size());
        for (const auto& [x, y] : points) {
            (void)y;
            if (_xs.empty() || _xs.back() != x) _xs.push_back(x);
        }

        _n = int(_xs.size());
        _size = int(m1une::math::bit_ceil((unsigned int)std::max(1, _n)));
        _ys.assign(2 * _size, {});
        _lazy.assign(2 * _size, {});

        for (const auto& [x, y] : points) {
            int x_position =
                int(std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin());
            for (int node = x_position + _size; node; node >>= 1) {
                _ys[node].push_back(y);
            }
        }

        for (int node = 1; node < 2 * _size; node++) {
            auto& ys = _ys[node];
            std::sort(ys.begin(), ys.end());
            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
            _lazy[node].assign(2 * ys.size(), Monoid::id());
        }

        _values.resize(_n);
        for (int x_position = 0; x_position < _n; x_position++) {
            _values[x_position].assign(_ys[x_position + _size].size(), Monoid::id());
        }
    }

    int size() const {
        return _point_count;
    }

    bool empty() const {
        return _point_count == 0;
    }

    int x_size() const {
        return _n;
    }

    const std::vector<X>& xs() const {
        return _xs;
    }

    bool contains_point(const X& x, const Y& y) const {
        int x_position = x_index(x);
        if (x_position == -1) return false;
        return y_index(x_position + _size, y) != -1;
    }

    void apply(const X& x, const Y& y, const T& value) {
        int x_position = x_index(x);
        assert(x_position != -1);
        int y_position = y_index(x_position + _size, y);
        assert(y_position != -1);
        _values[x_position][y_position] =
            Monoid::op(value, _values[x_position][y_position]);
    }

    void apply(const X& x_lower, const X& x_upper, const Y& y_lower,
               const Y& y_upper, const T& value) {
        assert(x_lower <= x_upper);
        assert(y_lower <= y_upper);
        if (x_lower == x_upper || y_lower == y_upper || empty()) return;

        int left = int(std::lower_bound(_xs.begin(), _xs.end(), x_lower) - _xs.begin());
        int right = int(std::lower_bound(_xs.begin(), _xs.end(), x_upper) - _xs.begin());
        left += _size;
        right += _size;
        while (left < right) {
            if (left & 1) apply_y(left++, y_lower, y_upper, value);
            if (right & 1) apply_y(--right, y_lower, y_upper, value);
            left >>= 1;
            right >>= 1;
        }
    }

    T get(const X& x, const Y& y) const {
        int x_position = x_index(x);
        if (x_position == -1) return Monoid::id();
        int leaf = x_position + _size;
        int y_position = y_index(leaf, y);
        if (y_position == -1) return Monoid::id();

        T result = _values[x_position][y_position];
        for (int node = leaf; node; node >>= 1) {
            result = Monoid::op(get_y(node, y), result);
        }
        return result;
    }

    T operator()(const X& x, const Y& y) const {
        return get(x, y);
    }

    std::vector<weighted_point_type> to_vector() const {
        std::vector<weighted_point_type> result;
        result.reserve(_point_count);
        for (int x_position = 0; x_position < _n; x_position++) {
            int leaf = x_position + _size;
            for (const Y& y : _ys[leaf]) {
                result.emplace_back(_xs[x_position], y, get(_xs[x_position], y));
            }
        }
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DUAL_SEGTREE_2D_HPP
