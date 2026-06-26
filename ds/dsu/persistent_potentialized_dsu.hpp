#ifndef M1UNE_PERSISTENT_POTENTIALIZED_DSU_HPP
#define M1UNE_PERSISTENT_POTENTIALIZED_DSU_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsCommutativeGroup Group>
    requires std::equality_comparable<typename Group::value_type>
struct PersistentPotentializedDsu {
    using T = typename Group::value_type;

    struct Value {
        int parent_or_size;
        T diff_to_parent;

        Value() : parent_or_size(0), diff_to_parent(Group::id()) {}
        Value(int parent_or_size_, const T& diff_to_parent_)
            : parent_or_size(parent_or_size_), diff_to_parent(diff_to_parent_) {}
        Value(int parent_or_size_, T&& diff_to_parent_)
            : parent_or_size(parent_or_size_), diff_to_parent(std::move(diff_to_parent_)) {}
    };

   private:
    struct Node {
        Value val;
        int l, r;

        Node() : val(), l(0), r(0) {}
        explicit Node(const Value& value) : val(value), l(0), r(0) {}
        explicit Node(Value&& value) : val(std::move(value)), l(0), r(0) {}
        Node(const Value& value, int left, int right) : val(value), l(left), r(right) {}
        Node(Value&& value, int left, int right) : val(std::move(value)), l(left), r(right) {}
    };

    int _n;
    int _root;
    std::shared_ptr<std::vector<Node>> _pool;

    explicit PersistentPotentializedDsu(int n, int root, std::shared_ptr<std::vector<Node>> pool)
        : _n(n), _root(root), _pool(std::move(pool)) {}

    int new_node(const Node& node) const {
        _pool->push_back(node);
        return int(_pool->size()) - 1;
    }

    int new_node(Node&& node) const {
        _pool->push_back(std::move(node));
        return int(_pool->size()) - 1;
    }

    int build(int l, int r) const {
        if (l == r) return 0;
        if (r - l == 1) return new_node(Node(Value(-1, Group::id())));
        int m = (l + r) >> 1;
        int left = build(l, m);
        int right = build(m, r);
        return new_node(Node(Value(), left, right));
    }

    int set_node(int t, int l, int r, int p, Value value) const {
        if (r - l == 1) return new_node(Node(std::move(value)));
        int m = (l + r) >> 1;
        int left = (*_pool)[t].l;
        int right = (*_pool)[t].r;
        if (p < m) {
            left = set_node(left, l, m, p, std::move(value));
        } else {
            right = set_node(right, m, r, p, std::move(value));
        }
        return new_node(Node(Value(), left, right));
    }

    Value get_value(int t, int l, int r, int p) const {
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (p < m) {
                t = (*_pool)[t].l;
                r = m;
            } else {
                t = (*_pool)[t].r;
                l = m;
            }
        }
        return (*_pool)[t].val;
    }

    std::pair<int, T> leader_and_potential(int a) const {
        T res = Group::id();
        while (true) {
            Value cur = get(a);
            if (cur.parent_or_size < 0) return {a, res};
            res = Group::op(cur.diff_to_parent, res);
            a = cur.parent_or_size;
        }
    }

   public:
    PersistentPotentializedDsu() : PersistentPotentializedDsu(0) {}

    explicit PersistentPotentializedDsu(int n) : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        assert(0 <= n);
        _pool->reserve(n * 4 + 1);
        _pool->push_back(Node());
        if (_n > 0) _root = build(0, _n);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int leader(int a) const {
        assert(0 <= a && a < _n);
        return leader_and_potential(a).first;
    }

    bool same(int a, int b) const {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int group_size(int a) const {
        assert(0 <= a && a < _n);
        return -get(leader(a)).parent_or_size;
    }

    int size(int a) const {
        return group_size(a);
    }

    T potential(int a) const {
        assert(0 <= a && a < _n);
        return leader_and_potential(a).second;
    }

    T diff(int a, int b) const {
        assert(same(a, b));
        return Group::op(Group::inv(potential(a)), potential(b));
    }

    Value get(int p) const {
        assert(0 <= p && p < _n);
        return get_value(_root, 0, _n, p);
    }

    int parent_or_size(int p) const {
        return get(p).parent_or_size;
    }

    std::pair<PersistentPotentializedDsu, bool> merge(int a, int b, const T& w) const {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        auto [x, pa] = leader_and_potential(a);
        auto [y, pb] = leader_and_potential(b);
        if (x == y) return {*this, Group::op(Group::inv(pa), pb) == w};

        int sx = -get(x).parent_or_size;
        int sy = -get(y).parent_or_size;
        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));
        if (sx < sy) {
            std::swap(x, y);
            std::swap(sx, sy);
            y_from_x = Group::inv(y_from_x);
        }
        int root = set_node(_root, 0, _n, x, Value(-(sx + sy), Group::id()));
        root = set_node(root, 0, _n, y, Value(x, std::move(y_from_x)));
        return {PersistentPotentializedDsu(_n, root, _pool), true};
    }

    std::vector<std::vector<int>> groups() const {
        std::vector<int> leader_buf(_n), group_size(_n);
        for (int i = 0; i < _n; i++) {
            leader_buf[i] = leader(i);
            group_size[leader_buf[i]]++;
        }
        std::vector<std::vector<int>> result(_n);
        for (int i = 0; i < _n; i++) {
            result[i].reserve(group_size[i]);
        }
        for (int i = 0; i < _n; i++) {
            result[leader_buf[i]].push_back(i);
        }
        result.erase(std::remove_if(result.begin(), result.end(), [&](const std::vector<int>& v) { return v.empty(); }),
                     result.end());
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_POTENTIALIZED_DSU_HPP
