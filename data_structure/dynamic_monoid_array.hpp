#ifndef M1UNE_DYNAMIC_MONOID_ARRAY_HPP
#define M1UNE_DYNAMIC_MONOID_ARRAY_HPP 1

#include <cassert>
#include <chrono>
#include <concepts>
#include <initializer_list>
#include <random>
#include <utility>
#include <vector>

#include "monoid/concept.hpp"

namespace m1une {
namespace data_structure {

template <m1une::monoid::IsMonoid Monoid>
struct DynamicMonoidArray {
    using T = typename Monoid::value_type;

   private:
    struct Node {
        T val;
        T prod;
        T rprod;
        int priority;
        int count;
        int l, r;
        bool rev;

        Node()
            : val(Monoid::id()),
              prod(Monoid::id()),
              rprod(Monoid::id()),
              priority(0),
              count(0),
              l(0),
              r(0),
              rev(false) {}

        Node(T value, int node_priority)
            : val(std::move(value)), prod(val), rprod(val), priority(node_priority), count(1), l(0), r(0), rev(false) {}
    };

    std::vector<Node> pool;
    int root;
    std::mt19937 rng;

    template <typename U>
    static T make_value(const U& value) {
        if constexpr (requires(U x) { Monoid::make(x); }) {
            return Monoid::make(value);
        } else {
            return static_cast<T>(value);
        }
    }

    int new_node(T value) {
        pool.push_back(Node(std::move(value), rng()));
        return int(pool.size()) - 1;
    }

    void update(int t) {
        if (!t) return;
        int l = pool[t].l;
        int r = pool[t].r;
        pool[t].count = 1 + pool[l].count + pool[r].count;
        pool[t].prod = Monoid::op(Monoid::op(pool[l].prod, pool[t].val), pool[r].prod);
        pool[t].rprod = Monoid::op(Monoid::op(pool[r].rprod, pool[t].val), pool[l].rprod);
    }

    void apply_reverse(int t) {
        if (!t) return;
        pool[t].rev = !pool[t].rev;
        std::swap(pool[t].prod, pool[t].rprod);
    }

    void push(int t) {
        if (!t || !pool[t].rev) return;
        std::swap(pool[t].l, pool[t].r);
        apply_reverse(pool[t].l);
        apply_reverse(pool[t].r);
        pool[t].rev = false;
    }

    void split(int t, int pos, int& l, int& r) {
        if (!t) {
            l = r = 0;
            return;
        }
        push(t);
        int left_count = pool[pool[t].l].count;
        if (pos <= left_count) {
            split(pool[t].l, pos, l, pool[t].l);
            r = t;
        } else {
            split(pool[t].r, pos - left_count - 1, pool[t].r, r);
            l = t;
        }
        update(t);
    }

    int merge(int l, int r) {
        if (!l || !r) return l ? l : r;
        push(l);
        push(r);
        if (pool[l].priority > pool[r].priority) {
            pool[l].r = merge(pool[l].r, r);
            update(l);
            return l;
        } else {
            pool[r].l = merge(l, pool[r].l);
            update(r);
            return r;
        }
    }

    int find_node(int t, int pos) {
        while (t) {
            push(t);
            int left_count = pool[pool[t].l].count;
            if (pos < left_count) {
                t = pool[t].l;
            } else if (pos == left_count) {
                return t;
            } else {
                pos -= left_count + 1;
                t = pool[t].r;
            }
        }
        return 0;
    }

    int find_node(int t, int pos, bool reversed) const {
        while (t) {
            bool cur_reversed = reversed ^ pool[t].rev;
            int l = cur_reversed ? pool[t].r : pool[t].l;
            int r = cur_reversed ? pool[t].l : pool[t].r;
            int left_count = pool[l].count;
            if (pos < left_count) {
                t = l;
                reversed = cur_reversed;
            } else if (pos == left_count) {
                return t;
            } else {
                pos -= left_count + 1;
                t = r;
                reversed = cur_reversed;
            }
        }
        return 0;
    }

    void dump_dfs(int t, std::vector<T>& res, bool reversed = false) const {
        if (!t) return;
        bool cur_reversed = reversed ^ pool[t].rev;
        int l = cur_reversed ? pool[t].r : pool[t].l;
        int r = cur_reversed ? pool[t].l : pool[t].r;
        dump_dfs(l, res, cur_reversed);
        res.push_back(pool[t].val);
        dump_dfs(r, res, cur_reversed);
    }

    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>& res, bool reversed = false) const {
        if (!t || qr <= offset || offset + pool[t].count <= ql) return;
        bool cur_reversed = reversed ^ pool[t].rev;
        int l = cur_reversed ? pool[t].r : pool[t].l;
        int r = cur_reversed ? pool[t].l : pool[t].r;
        int left_count = pool[l].count;
        int node_pos = offset + left_count;
        dump_range_dfs(l, ql, qr, offset, res, cur_reversed);
        if (ql <= node_pos && node_pos < qr) {
            res.push_back(pool[t].val);
        }
        dump_range_dfs(r, ql, qr, node_pos + 1, res, cur_reversed);
    }

    int clone_subtree_from(const DynamicMonoidArray& other, int t) {
        if (!t) return 0;
        int res = int(pool.size());
        pool.push_back(other.pool[t]);
        pool[res].l = clone_subtree_from(other, other.pool[t].l);
        pool[res].r = clone_subtree_from(other, other.pool[t].r);
        return res;
    }

    int build_from_vector(const std::vector<T>& v) {
        int res = 0;
        for (const T& x : v) {
            res = merge(res, new_node(x));
        }
        return res;
    }

    int build_from_vector(std::vector<T>&& v) {
        int res = 0;
        for (T& x : v) {
            res = merge(res, new_node(std::move(x)));
        }
        return res;
    }

    template <typename U>
    int build_from_values(const std::vector<U>& v) {
        int res = 0;
        for (const U& x : v) {
            res = merge(res, new_node(make_value(x)));
        }
        return res;
    }

    void reset_to_empty() {
        pool.clear();
        pool.push_back(Node());
        root = 0;
    }

   public:
    DynamicMonoidArray() : root(0), rng(std::chrono::steady_clock::now().time_since_epoch().count()) {
        pool.push_back(Node());
    }

    DynamicMonoidArray(const DynamicMonoidArray& other) : pool(other.pool), root(other.root), rng(other.rng) {}

    DynamicMonoidArray(DynamicMonoidArray&& other) noexcept
        : pool(std::move(other.pool)), root(other.root), rng(std::move(other.rng)) {
        other.reset_to_empty();
    }

    DynamicMonoidArray& operator=(const DynamicMonoidArray& other) {
        if (this != &other) {
            pool = other.pool;
            root = other.root;
            rng = other.rng;
        }
        return *this;
    }

    DynamicMonoidArray& operator=(DynamicMonoidArray&& other) noexcept {
        if (this != &other) {
            pool = std::move(other.pool);
            root = other.root;
            rng = std::move(other.rng);
            other.reset_to_empty();
        }
        return *this;
    }

    explicit DynamicMonoidArray(int n) : DynamicMonoidArray(n, Monoid::id()) {}

    DynamicMonoidArray(int n, const T& value) : DynamicMonoidArray() {
        assert(0 <= n);
        pool.reserve(n + 1);
        for (int i = 0; i < n; i++) {
            root = merge(root, new_node(value));
        }
    }

    explicit DynamicMonoidArray(const std::vector<T>& v) : DynamicMonoidArray() {
        pool.reserve(v.size() + 1);
        root = build_from_vector(v);
    }

    explicit DynamicMonoidArray(std::vector<T>&& v) : DynamicMonoidArray() {
        pool.reserve(v.size() + 1);
        root = build_from_vector(std::move(v));
    }

    template <typename U>
        requires(!std::same_as<U, T>) && (requires(U x) { Monoid::make(x); } || std::convertible_to<U, T>)
    explicit DynamicMonoidArray(const std::vector<U>& v) : DynamicMonoidArray() {
        pool.reserve(v.size() + 1);
        root = build_from_values(v);
    }

    DynamicMonoidArray(std::initializer_list<T> init) : DynamicMonoidArray() {
        pool.reserve(init.size() + 1);
        for (const T& x : init) push_back(x);
    }

    int size() const {
        return pool[root].count;
    }

    bool empty() const {
        return size() == 0;
    }

    void clear() {
        reset_to_empty();
    }

    void insert(int pos, T value) {
        assert(0 <= pos && pos <= size());
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, new_node(std::move(value))), r);
    }

    void insert(int pos, const std::vector<T>& v) {
        assert(0 <= pos && pos <= size());
        pool.reserve(pool.size() + v.size());
        int mid = build_from_vector(v);
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, mid), r);
    }

    void insert(int pos, std::vector<T>&& v) {
        assert(0 <= pos && pos <= size());
        pool.reserve(pool.size() + v.size());
        int mid = build_from_vector(std::move(v));
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, mid), r);
    }

    void insert(int pos, std::initializer_list<T> init) {
        insert(pos, std::vector<T>(init));
    }

    void insert(int pos, const DynamicMonoidArray& other) {
        assert(0 <= pos && pos <= size());
        if (other.empty()) return;
        pool.reserve(pool.size() + other.size());
        int mid = clone_subtree_from(other, other.root);
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, mid), r);
    }

    void push_back(T value) {
        insert(size(), std::move(value));
    }

    void push_front(T value) {
        insert(0, std::move(value));
    }

    void append(const std::vector<T>& v) {
        insert(size(), v);
    }

    void append(std::vector<T>&& v) {
        insert(size(), std::move(v));
    }

    void append(const DynamicMonoidArray& other) {
        insert(size(), other);
    }

    void erase(int pos) {
        assert(0 <= pos && pos < size());
        erase(pos, pos + 1);
    }

    void erase(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return;
        int a, b, c;
        split(root, l, a, b);
        split(b, r - l, b, c);
        root = merge(a, c);
    }

    void pop_back() {
        assert(!empty());
        erase(size() - 1);
    }

    void pop_front() {
        assert(!empty());
        erase(0);
    }

    T get(int pos) const {
        assert(0 <= pos && pos < size());
        return pool[find_node(root, pos, false)].val;
    }

    T operator[](int pos) const {
        return get(pos);
    }

    T front() const {
        assert(!empty());
        return get(0);
    }

    T back() const {
        assert(!empty());
        return get(size() - 1);
    }

    void set(int pos, T value) {
        assert(0 <= pos && pos < size());
        int a, b, c;
        split(root, pos, a, b);
        split(b, 1, b, c);
        pool[b].val = std::move(value);
        update(b);
        root = merge(merge(a, b), c);
    }

    void reverse(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return;
        int a, b, c;
        split(root, l, a, b);
        split(b, r - l, b, c);
        apply_reverse(b);
        root = merge(merge(a, b), c);
    }

    void reverse() {
        apply_reverse(root);
    }

    void rotate(int l, int m, int r) {
        assert(0 <= l && l <= m && m <= r && r <= size());
        if (l == m || m == r) return;
        int a, b, c, d;
        split(root, l, a, b);
        split(b, m - l, b, c);
        split(c, r - m, c, d);
        root = merge(merge(a, c), merge(b, d));
    }

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return Monoid::id();
        int a, b, c;
        split(root, l, a, b);
        split(b, r - l, b, c);
        T res = pool[b].prod;
        root = merge(merge(a, b), c);
        return res;
    }

    T all_prod() const {
        return pool[root].prod;
    }

    std::vector<T> to_vector() const {
        std::vector<T> res;
        res.reserve(size());
        dump_dfs(root, res);
        return res;
    }

    std::vector<T> to_vector(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        std::vector<T> res;
        res.reserve(r - l);
        dump_range_dfs(root, l, r, 0, res);
        return res;
    }

    DynamicMonoidArray split_off(int pos) {
        assert(0 <= pos && pos <= size());
        int l, r;
        split(root, pos, l, r);
        root = l;

        DynamicMonoidArray res;
        res.pool.reserve(pool[r].count + 1);
        res.root = res.clone_subtree_from(*this, r);
        return res;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_DYNAMIC_MONOID_ARRAY_HPP
