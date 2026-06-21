#ifndef M1UNE_SEGTREE_2D_HPP
#define M1UNE_SEGTREE_2D_HPP 1

#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

#include "../../math/bit_ceil.hpp"
#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

// A static compressed 2D segment tree.
// It supports point assignment on registered points and rectangle product queries.
//
// The query rectangle is [xl, xr) x [yl, yr).
// All points that may be updated must be registered before construction.
template <class Monoid, class X = int, class Y = X>
requires m1une::monoid::IsMonoid<Monoid>
struct Segtree2D {
    using T = typename Monoid::value_type;
    using point_type = std::pair<X, Y>;
    using weighted_point_type = std::tuple<X, Y, T>;

private:
    int _n;
    int _size;
    int _point_count;
    std::vector<X> _xs;
    std::vector<std::vector<Y>> _ys;
    std::vector<std::vector<T>> _d;

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

    int y_index(int k, const Y& y) const {
        const auto& ys = _ys[k];
        auto it = std::lower_bound(ys.begin(), ys.end(), y);
        if (it == ys.end() || *it != y) return -1;
        return int(it - ys.begin());
    }

    T get_exact(int k, const Y& y) const {
        int pos = y_index(k, y);
        if (pos == -1) return Monoid::id();
        int m = int(_ys[k].size());
        return _d[k][m + pos];
    }

    void set_exact(int k, const Y& y, T x) {
        int pos = y_index(k, y);
        assert(pos != -1);

        int m = int(_ys[k].size());
        int p = m + pos;

        _d[k][p] = std::move(x);
        while (1 < p) {
            p >>= 1;
            _d[k][p] = Monoid::op(_d[k][2 * p], _d[k][2 * p + 1]);
        }
    }

    T prod_y(int k, const Y& yl, const Y& yr) const {
        assert(yl <= yr);
        if (yl == yr || _ys[k].empty()) return Monoid::id();

        const auto& ys = _ys[k];
        int l = int(std::lower_bound(ys.begin(), ys.end(), yl) - ys.begin());
        int r = int(std::lower_bound(ys.begin(), ys.end(), yr) - ys.begin());

        int m = int(ys.size());
        l += m;
        r += m;

        T sml = Monoid::id();
        T smr = Monoid::id();

        while (l < r) {
            if (l & 1) sml = Monoid::op(sml, _d[k][l++]);
            if (r & 1) smr = Monoid::op(_d[k][--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return Monoid::op(sml, smr);
    }

public:
    Segtree2D() : _n(0), _size(1), _point_count(0), _ys(2), _d(2) {}

    explicit Segtree2D(const std::vector<point_type>& points) {
        build(points);
    }

    explicit Segtree2D(std::vector<point_type>&& points) {
        build(std::move(points));
    }

    explicit Segtree2D(const std::vector<weighted_point_type>& points) {
        std::vector<point_type> coords;
        coords.reserve(points.size());

        for (const auto& [x, y, value] : points) {
            (void)value;
            coords.emplace_back(x, y);
        }

        build(std::move(coords));

        for (const auto& [x, y, value] : points) {
            set(x, y, value);
        }
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
        _d.assign(2 * _size, {});

        for (const auto& [x, y] : points) {
            int xi = int(std::lower_bound(_xs.begin(), _xs.end(), x) - _xs.begin());
            for (int k = xi + _size; k; k >>= 1) {
                _ys[k].push_back(y);
            }
        }

        for (int k = 1; k < 2 * _size; k++) {
            auto& ys = _ys[k];
            std::sort(ys.begin(), ys.end());
            ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
            _d[k].assign(2 * ys.size(), Monoid::id());
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
        int xi = x_index(x);
        if (xi == -1) return false;
        return y_index(xi + _size, y) != -1;
    }

    void set(const X& x, const Y& y, T value) {
        int xi = x_index(x);
        assert(xi != -1);
        assert(y_index(xi + _size, y) != -1);

        int k = xi + _size;
        set_exact(k, y, std::move(value));

        while (1 < k) {
            k >>= 1;
            set_exact(k, y, Monoid::op(get_exact(2 * k, y), get_exact(2 * k + 1, y)));
        }
    }

    T get(const X& x, const Y& y) const {
        int xi = x_index(x);
        if (xi == -1) return Monoid::id();
        return get_exact(xi + _size, y);
    }

    T operator()(const X& x, const Y& y) const {
        return get(x, y);
    }

    T prod(const X& xl, const X& xr, const Y& yl, const Y& yr) const {
        assert(xl <= xr);
        assert(yl <= yr);

        if (xl == xr || yl == yr || empty()) return Monoid::id();

        int l = int(std::lower_bound(_xs.begin(), _xs.end(), xl) - _xs.begin());
        int r = int(std::lower_bound(_xs.begin(), _xs.end(), xr) - _xs.begin());

        l += _size;
        r += _size;

        T sml = Monoid::id();
        T smr = Monoid::id();

        while (l < r) {
            if (l & 1) sml = Monoid::op(sml, prod_y(l++, yl, yr));
            if (r & 1) smr = Monoid::op(prod_y(--r, yl, yr), smr);
            l >>= 1;
            r >>= 1;
        }

        return Monoid::op(sml, smr);
    }

    T all_prod() const {
        if (empty() || _d[1].empty()) return Monoid::id();
        return _d[1][1];
    }

    std::vector<weighted_point_type> to_vector() const {
        std::vector<weighted_point_type> res;
        res.reserve(_point_count);

        for (int xi = 0; xi < _n; xi++) {
            int k = xi + _size;
            int m = int(_ys[k].size());

            for (int j = 0; j < m; j++) {
                res.emplace_back(_xs[xi], _ys[k][j], _d[k][m + j]);
            }
        }

        return res;
    }
};

} // namespace ds
} // namespace m1une

#endif // M1UNE_SEGTREE_2D_HPP
