#ifndef M1UNE_DSU_MONOID_HPP
#define M1UNE_DSU_MONOID_HPP 1

#include <algorithm>
#include <cassert>
#include <concepts>
#include <initializer_list>
#include <utility>
#include <vector>

#include "monoid/concept.hpp"

namespace m1une {
namespace data_structure {

template <m1une::monoid::IsMonoid Monoid>
struct DsuMonoid {
    using T = typename Monoid::value_type;

   private:
    int _n;
    std::vector<int> parent_or_size;
    std::vector<T> _prod;

    static int check_size(int n) {
        assert(0 <= n);
        return n;
    }

    template <typename U>
    static T make_value(const U& value, int index) {
        if constexpr (requires(U x) { Monoid::make(x); }) {
            return Monoid::make(value);
        } else if constexpr (requires(U x, int i) { Monoid::make(x, i); }) {
            return Monoid::make(value, index);
        } else {
            return static_cast<T>(value);
        }
    }

   public:
    DsuMonoid() : DsuMonoid(0) {}

    explicit DsuMonoid(int n) : DsuMonoid(n, Monoid::id()) {}

    DsuMonoid(int n, const T& value) : _n(check_size(n)), parent_or_size(_n, -1), _prod(_n, value) {}

    explicit DsuMonoid(const std::vector<T>& v) : _n(int(v.size())), parent_or_size(_n, -1), _prod(v) {}

    explicit DsuMonoid(std::vector<T>&& v) : _n(int(v.size())), parent_or_size(_n, -1), _prod(std::move(v)) {}

    template <typename U>
    requires (!std::same_as<U, T>) && (
        requires(U x) { Monoid::make(x); } ||
        requires(U x, int i) { Monoid::make(x, i); } ||
        std::convertible_to<U, T>
    )
    explicit DsuMonoid(const std::vector<U>& v) : _n(int(v.size())), parent_or_size(_n, -1), _prod(_n, Monoid::id()) {
        for (int i = 0; i < _n; i++) _prod[i] = make_value(v[i], i);
    }

    DsuMonoid(std::initializer_list<T> init) : DsuMonoid(std::vector<T>(init)) {}

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    int merge(int a, int b) {
        assert(0 <= a && a < _n);
        assert(0 <= b && b < _n);
        int x = leader(a), y = leader(b);
        if (x == y) return x;
        T merged = Monoid::op(_prod[x], _prod[y]);
        if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
        parent_or_size[x] += parent_or_size[y];
        parent_or_size[y] = x;
        _prod[x] = std::move(merged);
        return x;
    }

    bool same(int a, int b) {
        return leader(a) == leader(b);
    }

    bool same(int a, int b) const {
        return leader(a) == leader(b);
    }

    int leader(int a) {
        assert(0 <= a && a < _n);
        if (parent_or_size[a] < 0) return a;
        return parent_or_size[a] = leader(parent_or_size[a]);
    }

    int leader(int a) const {
        assert(0 <= a && a < _n);
        while (parent_or_size[a] >= 0) a = parent_or_size[a];
        return a;
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

    T prod(int a) {
        return _prod[leader(a)];
    }

    T prod(int a) const {
        return _prod[leader(a)];
    }

    T get(int a) {
        return prod(a);
    }

    T get(int a) const {
        return prod(a);
    }

    void set(int a, T value) {
        _prod[leader(a)] = std::move(value);
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

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_DSU_MONOID_HPP
