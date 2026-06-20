#ifndef M1UNE_DYNAMIC_LAZY_MONOID_ARRAY_HPP
#define M1UNE_DYNAMIC_LAZY_MONOID_ARRAY_HPP 1

#include <cassert>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <utility>
#include <vector>

#include "../../acted_monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct DynamicLazyMonoidArray {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    struct Node {
        T val;
        T prod;
        T rprod;
        F lazy;
        int priority;
        int count;
        int l, r;
        bool rev;
        bool has_lazy;

        Node()
            : val(ActedMonoid::id()),
              prod(ActedMonoid::id()),
              rprod(ActedMonoid::id()),
              lazy(ActedMonoid::op_id()),
              priority(0),
              count(0),
              l(0),
              r(0),
              rev(false),
              has_lazy(false) {}

        Node(T value, int node_priority)
            : val(std::move(value)),
              prod(val),
              rprod(val),
              lazy(ActedMonoid::op_id()),
              priority(node_priority),
              count(1),
              l(0),
              r(0),
              rev(false),
              has_lazy(false) {}
    };

    std::vector<Node> pool;
    int root;
    std::uint32_t rng_state;

    template <typename U>
    static T make_value(const U& value) {
        if constexpr (requires(U x) { ActedMonoid::make(x); }) {
            return ActedMonoid::make(value);
        } else {
            return static_cast<T>(value);
        }
    }

    static T mapping_at(const F& f, const T& value, long long ord) {
        if constexpr (requires(F g, T x, long long i) { ActedMonoid::mapping(g, x, i); }) {
            return ActedMonoid::mapping(f, value, ord);
        } else {
            return ActedMonoid::mapping(f, value);
        }
    }

    static F shift_operator(const F& f, long long ord) {
        if constexpr (requires(F g, long long i) { ActedMonoid::op_shift(g, i); }) {
            return ActedMonoid::op_shift(f, ord);
        } else {
            return f;
        }
    }

    static F reverse_operator(const F& f, long long size) {
        if constexpr (requires(F g, long long n) { ActedMonoid::op_reverse(g, n); }) {
            return ActedMonoid::op_reverse(f, size);
        } else {
            return f;
        }
    }

    int new_node(T value) {
        pool.push_back(Node(std::move(value), next_priority()));
        return int(pool.size()) - 1;
    }

    int next_priority() {
        rng_state ^= rng_state << 13;
        rng_state ^= rng_state >> 17;
        rng_state ^= rng_state << 5;
        return int(rng_state);
    }

    void update(int t) {
        if (!t) return;
        int l = pool[t].l;
        int r = pool[t].r;
        pool[t].count = 1 + pool[l].count + pool[r].count;
        pool[t].prod = ActedMonoid::op(ActedMonoid::op(pool[l].prod, pool[t].val), pool[r].prod);
        pool[t].rprod = ActedMonoid::op(ActedMonoid::op(pool[r].rprod, pool[t].val), pool[l].rprod);
    }

    void all_apply(int t, const F& f) {
        if (!t) return;
        int left_count = pool[t].rev ? pool[pool[t].r].count : pool[pool[t].l].count;
        pool[t].val = mapping_at(f, pool[t].val, left_count);
        pool[t].prod = mapping_at(f, pool[t].prod, 0);
        pool[t].rprod = mapping_at(reverse_operator(f, pool[t].count), pool[t].rprod, 0);
        pool[t].lazy = ActedMonoid::op_comp(f, pool[t].lazy);
        pool[t].has_lazy = true;
    }

    void apply_reverse(int t) {
        if (!t) return;
        pool[t].rev = !pool[t].rev;
        std::swap(pool[t].prod, pool[t].rprod);
        if (pool[t].has_lazy) {
            pool[t].lazy = reverse_operator(pool[t].lazy, pool[t].count);
        }
    }

    void push(int t) {
        if (!t) return;
        if (pool[t].rev) {
            std::swap(pool[t].l, pool[t].r);
            apply_reverse(pool[t].l);
            apply_reverse(pool[t].r);
            pool[t].rev = false;
        }
        if (pool[t].has_lazy) {
            all_apply(pool[t].l, pool[t].lazy);
            all_apply(pool[t].r, shift_operator(pool[t].lazy, pool[pool[t].l].count + 1));
            pool[t].lazy = ActedMonoid::op_id();
            pool[t].has_lazy = false;
        }
    }

    void split(int t, int pos, int& l, int& r) {
        if (!t) {
            l = r = 0;
            return;
        }
        if (pos == 0) {
            l = 0;
            r = t;
            return;
        }
        if (pos == pool[t].count) {
            l = t;
            r = 0;
            return;
        }
        push(t);
        int left_count = pool[pool[t].l].count;
        if (pos == left_count) {
            l = pool[t].l;
            pool[t].l = 0;
            update(t);
            r = t;
            return;
        }
        if (pos == left_count + 1) {
            r = pool[t].r;
            pool[t].r = 0;
            update(t);
            l = t;
            return;
        }
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
        if (pool[l].priority > pool[r].priority) {
            push(l);
            if (pool[l].r) {
                pool[l].r = merge(pool[l].r, r);
            } else {
                pool[l].r = r;
            }
            update(l);
            return l;
        } else {
            push(r);
            if (pool[r].l) {
                pool[r].l = merge(l, pool[r].l);
            } else {
                pool[r].l = l;
            }
            update(r);
            return r;
        }
    }

    int insert_node(int t, int pos, int node) {
        if (!t) return node;
        if (pool[node].priority > pool[t].priority) {
            split(t, pos, pool[node].l, pool[node].r);
            update(node);
            return node;
        }
        push(t);
        int left_count = pool[pool[t].l].count;
        if (pos <= left_count) {
            pool[t].l = insert_node(pool[t].l, pos, node);
        } else {
            pool[t].r = insert_node(pool[t].r, pos - left_count - 1, node);
        }
        update(t);
        return t;
    }

    int erase_node(int t, int pos) {
        push(t);
        int left_count = pool[pool[t].l].count;
        if (pos < left_count) {
            pool[t].l = erase_node(pool[t].l, pos);
            update(t);
            return t;
        }
        if (pos == left_count) {
            return merge(pool[t].l, pool[t].r);
        }
        pool[t].r = erase_node(pool[t].r, pos - left_count - 1);
        update(t);
        return t;
    }

    void set_node(int t, int pos, T value) {
        push(t);
        int left_count = pool[pool[t].l].count;
        if (pos < left_count) {
            set_node(pool[t].l, pos, std::move(value));
        } else if (pos == left_count) {
            pool[t].val = std::move(value);
        } else {
            set_node(pool[t].r, pos - left_count - 1, std::move(value));
        }
        update(t);
    }

    void apply_node(int t, int pos, const F& f) {
        push(t);
        int left_count = pool[pool[t].l].count;
        if (pos < left_count) {
            apply_node(pool[t].l, pos, f);
        } else if (pos == left_count) {
            pool[t].val = mapping_at(f, pool[t].val, 0);
        } else {
            apply_node(pool[t].r, pos - left_count - 1, f);
        }
        update(t);
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

    void dump_dfs(int t, std::vector<T>& res) {
        if (!t) return;
        push(t);
        dump_dfs(pool[t].l, res);
        res.push_back(pool[t].val);
        dump_dfs(pool[t].r, res);
        update(t);
    }

    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>& res) {
        if (!t || qr <= offset || offset + pool[t].count <= ql) return;
        push(t);
        int left_count = pool[pool[t].l].count;
        int node_pos = offset + left_count;
        dump_range_dfs(pool[t].l, ql, qr, offset, res);
        if (ql <= node_pos && node_pos < qr) {
            res.push_back(pool[t].val);
        }
        dump_range_dfs(pool[t].r, ql, qr, node_pos + 1, res);
        update(t);
    }

    int clone_subtree_from(const DynamicLazyMonoidArray& other, int t) {
        if (!t) return 0;
        int res = int(pool.size());
        pool.push_back(other.pool[t]);
        pool[res].l = clone_subtree_from(other, other.pool[t].l);
        pool[res].r = clone_subtree_from(other, other.pool[t].r);
        return res;
    }

    void update_dfs(int t) {
        if (!t) return;
        update_dfs(pool[t].l);
        update_dfs(pool[t].r);
        update(t);
    }

    int build_cartesian(int first, int last) {
        if (first == last) return 0;
        std::vector<int> stack;
        stack.reserve(last - first);
        for (int i = first; i < last; i++) {
            int left_child = 0;
            while (!stack.empty() && pool[stack.back()].priority < pool[i].priority) {
                left_child = stack.back();
                stack.pop_back();
            }
            pool[i].l = left_child;
            if (!stack.empty()) {
                pool[stack.back()].r = i;
            }
            stack.push_back(i);
        }
        int res = stack.front();
        update_dfs(res);
        return res;
    }

    int build_from_vector(const std::vector<T>& v) {
        int first = int(pool.size());
        pool.reserve(pool.size() + v.size());
        for (const T& x : v) {
            new_node(x);
        }
        return build_cartesian(first, int(pool.size()));
    }

    int build_from_vector(std::vector<T>&& v) {
        int first = int(pool.size());
        pool.reserve(pool.size() + v.size());
        for (T& x : v) {
            new_node(std::move(x));
        }
        return build_cartesian(first, int(pool.size()));
    }

    template <typename U>
    int build_from_values(const std::vector<U>& v) {
        int first = int(pool.size());
        pool.reserve(pool.size() + v.size());
        for (const U& x : v) {
            new_node(make_value(x));
        }
        return build_cartesian(first, int(pool.size()));
    }

    void reset_to_empty() {
        pool.clear();
        pool.push_back(Node());
        root = 0;
    }

   public:
    DynamicLazyMonoidArray()
        : root(0), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())) {
        pool.push_back(Node());
        if (rng_state == 0) rng_state = 1;
    }

    DynamicLazyMonoidArray(const DynamicLazyMonoidArray& other)
        : pool(other.pool), root(other.root), rng_state(other.rng_state) {}

    DynamicLazyMonoidArray(DynamicLazyMonoidArray&& other) noexcept
        : pool(std::move(other.pool)), root(other.root), rng_state(other.rng_state) {
        other.reset_to_empty();
    }

    DynamicLazyMonoidArray& operator=(const DynamicLazyMonoidArray& other) {
        if (this != &other) {
            pool = other.pool;
            root = other.root;
            rng_state = other.rng_state;
        }
        return *this;
    }

    DynamicLazyMonoidArray& operator=(DynamicLazyMonoidArray&& other) noexcept {
        if (this != &other) {
            pool = std::move(other.pool);
            root = other.root;
            rng_state = other.rng_state;
            other.reset_to_empty();
        }
        return *this;
    }

    explicit DynamicLazyMonoidArray(int n) : DynamicLazyMonoidArray(n, ActedMonoid::id()) {}

    DynamicLazyMonoidArray(int n, const T& value) : DynamicLazyMonoidArray() {
        assert(0 <= n);
        pool.reserve(n + 1);
        int first = int(pool.size());
        for (int i = 0; i < n; i++) {
            new_node(value);
        }
        root = build_cartesian(first, int(pool.size()));
    }

    explicit DynamicLazyMonoidArray(const std::vector<T>& v) : DynamicLazyMonoidArray() {
        pool.reserve(v.size() + 1);
        root = build_from_vector(v);
    }

    explicit DynamicLazyMonoidArray(std::vector<T>&& v) : DynamicLazyMonoidArray() {
        pool.reserve(v.size() + 1);
        root = build_from_vector(std::move(v));
    }

    template <typename U>
        requires(!std::same_as<U, T>) && (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)
    explicit DynamicLazyMonoidArray(const std::vector<U>& v) : DynamicLazyMonoidArray() {
        pool.reserve(v.size() + 1);
        root = build_from_values(v);
    }

    DynamicLazyMonoidArray(std::initializer_list<T> init) : DynamicLazyMonoidArray() {
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
        root = insert_node(root, pos, new_node(std::move(value)));
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

    void insert(int pos, const DynamicLazyMonoidArray& other) {
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

    void append(const DynamicLazyMonoidArray& other) {
        insert(size(), other);
    }

    void erase(int pos) {
        assert(0 <= pos && pos < size());
        root = erase_node(root, pos);
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

    T get(int pos) {
        assert(0 <= pos && pos < size());
        int t = find_node(root, pos);
        return pool[t].val;
    }

    T operator[](int pos) {
        return get(pos);
    }

    T front() {
        assert(!empty());
        return get(0);
    }

    T back() {
        assert(!empty());
        return get(size() - 1);
    }

    void set(int pos, T value) {
        assert(0 <= pos && pos < size());
        set_node(root, pos, std::move(value));
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

    void apply(int pos, const F& f) {
        assert(0 <= pos && pos < size());
        apply_node(root, pos, f);
    }

    void apply(int l, int r, const F& f) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return;
        int a, b, c;
        split(root, l, a, b);
        split(b, r - l, b, c);
        all_apply(b, f);
        root = merge(merge(a, b), c);
    }

    T prod(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return ActedMonoid::id();
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

    std::vector<T> to_vector() {
        std::vector<T> res;
        res.reserve(size());
        dump_dfs(root, res);
        return res;
    }

    std::vector<T> to_vector(int l, int r) {
        assert(0 <= l && l <= r && r <= size());
        std::vector<T> res;
        res.reserve(r - l);
        dump_range_dfs(root, l, r, 0, res);
        return res;
    }

    DynamicLazyMonoidArray split_off(int pos) {
        assert(0 <= pos && pos <= size());
        int l, r;
        split(root, pos, l, r);
        root = l;

        DynamicLazyMonoidArray res;
        res.pool.reserve(pool[r].count + 1);
        res.root = res.clone_subtree_from(*this, r);
        return res;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DYNAMIC_LAZY_MONOID_ARRAY_HPP
