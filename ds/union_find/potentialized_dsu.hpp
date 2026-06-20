#ifndef M1UNE_POTENTIALIZED_DSU_HPP
#define M1UNE_POTENTIALIZED_DSU_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <utility>
#include <vector>

#include "monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsCommutativeGroup Group>
requires std::equality_comparable<typename Group::value_type>
struct PotentializedDsu {
    using T = typename Group::value_type;

   private:
    int _n;
    std::vector<int> parent_or_size;
    std::vector<T> diff_to_parent;

    static int check_size(int n) {
        assert(0 <= n);
        return n;
    }

   public:
    PotentializedDsu() : PotentializedDsu(0) {}

    explicit PotentializedDsu(int n) : _n(check_size(n)), parent_or_size(_n, -1), diff_to_parent(_n, Group::id()) {}

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        int p = parent_or_size[a];
        int r = leader(p);
        diff_to_parent[a] = Group::op(diff_to_parent[p], diff_to_parent[a]);
        return parent_or_size[a] = r;
    }

    int leader(int a) const {
        assert(0 <= a && a < _n);
        while (parent_or_size[a] >= 0) a = parent_or_size[a];
        return a;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    bool same(int a, int b) const {
        return leader(a) == leader(b);
    }

    int group_size(int a) {
        return -parent_or_size[leader(a)];
    }

    int group_size(int a) const {
        return -parent_or_size[leader(a)];
    }

    int size(int a) {
        return group_size(a);
    }

    int size(int a) const {
        return group_size(a);
    }

    T potential(int a) {
        leader(a);
        return diff_to_parent[a];
    }

    T potential(int a) const {
        assert(0 <= a && a < _n);
        T res = Group::id();
        while (parent_or_size[a] >= 0) {
            res = Group::op(diff_to_parent[a], res);
            a = parent_or_size[a];
        }
        return res;
    }

    T diff(int a, int b) {
        assert(same(a, b));
        return Group::op(Group::inv(potential(a)), potential(b));
    }

    T diff(int a, int b) const {
        assert(same(a, b));
        return Group::op(Group::inv(potential(a)), potential(b));
    }

    bool merge(int a, int b, const T& w) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a);
        int y = leader(b);
        T pa = diff_to_parent[a], pb = diff_to_parent[b];
        if (x == y) return Group::op(Group::inv(pa), pb) == w;

        T y_from_x = Group::op(Group::op(pa, w), Group::inv(pb));
        if (-parent_or_size[x] < -parent_or_size[y]) {
            std::swap(x, y);
            y_from_x = Group::inv(y_from_x);
        }
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        diff_to_parent[y] = std::move(y_from_x);
        return true;
    }

    std::vector<std::vector<int>> groups() {
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

#endif  // M1UNE_POTENTIALIZED_DSU_HPP
