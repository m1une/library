#ifndef M1UNE_PERSISTENT_DSU_HPP
#define M1UNE_PERSISTENT_DSU_HPP 1

#include <algorithm>
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

namespace m1une {
namespace data_structure {

struct PersistentDsu {
   private:
    struct Node {
        int val;
        int l, r;

        Node() : val(0), l(0), r(0) {}
        explicit Node(int value) : val(value), l(0), r(0) {}
        Node(int value, int left, int right) : val(value), l(left), r(right) {}
    };

    int _n;
    int _root;
    std::shared_ptr<std::vector<Node>> _pool;

    explicit PersistentDsu(int n, int root, std::shared_ptr<std::vector<Node>> pool)
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
        if (r - l == 1) return new_node(Node(-1));
        int m = (l + r) >> 1;
        int left = build(l, m);
        int right = build(m, r);
        return new_node(Node(0, left, right));
    }

    int set_node(int t, int l, int r, int p, int value) const {
        if (r - l == 1) return new_node(Node(value));
        int m = (l + r) >> 1;
        int left = (*_pool)[t].l;
        int right = (*_pool)[t].r;
        if (p < m) {
            left = set_node(left, l, m, p, value);
        } else {
            right = set_node(right, m, r, p, value);
        }
        return new_node(Node(0, left, right));
    }

    int get_node(int t, int l, int r, int p) const {
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

   public:
    PersistentDsu() : PersistentDsu(0) {}

    explicit PersistentDsu(int n) : _n(n), _root(0), _pool(std::make_shared<std::vector<Node>>()) {
        assert(0 <= n);
        _pool->reserve(n * 2 + 1);
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
        int x = a;
        int p = get(x);
        while (p >= 0) {
            x = p;
            p = get(x);
        }
        return x;
    }

    bool same(int a, int b) const {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        return leader(a) == leader(b);
    }

    int group_size(int a) const {
        assert(0 <= a && a < _n);
        return -get(leader(a));
    }

    int size(int a) const {
        return group_size(a);
    }

    int get(int p) const {
        assert(0 <= p && p < _n);
        return get_node(_root, 0, _n, p);
    }

    PersistentDsu merge(int a, int b) const {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return *this;
        int sx = -get(x), sy = -get(y);
        if (sx < sy) {
            std::swap(x, y);
            std::swap(sx, sy);
        }
        int root = set_node(_root, 0, _n, x, -(sx + sy));
        root = set_node(root, 0, _n, y, x);
        return PersistentDsu(_n, root, _pool);
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

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DSU_HPP
