#ifndef M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP
#define M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP 1

#include <cassert>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid>
struct PersistentDynamicMonoidArray {
    using T = typename Monoid::value_type;

   private:
    struct Node {
        T val, prod, rprod;
        int priority;
        int count;
        int l, r;
        bool rev;

        Node(T value, T product, T reverse_product, int node_priority, int node_count, int left, int right,
             bool reversed)
            : val(std::move(value)),
              prod(std::move(product)),
              rprod(std::move(reverse_product)),
              priority(node_priority),
              count(node_count),
              l(left),
              r(right),
              rev(reversed) {}
    };

    struct BuildNode {
        T val;
        int priority;
        int l, r;

        BuildNode(T value, int node_priority) : val(std::move(value)), priority(node_priority), l(-1), r(-1) {}
    };

    int root;
    std::uint32_t rng_state;
    std::shared_ptr<std::vector<Node>> pool;

    int subtree_size(int t) const {
        return t == -1 ? 0 : (*pool)[t].count;
    }

    T node_prod(int t) const {
        return t == -1 ? Monoid::id() : (*pool)[t].prod;
    }

    T node_rprod(int t) const {
        return t == -1 ? Monoid::id() : (*pool)[t].rprod;
    }

    static std::uint32_t next_state(std::uint32_t state) {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state == 0 ? 1 : state;
    }

    static int next_priority(std::uint32_t& state) {
        state = next_state(state);
        return int(state);
    }

    template <typename U>
    static T make_value(const U& value) {
        if constexpr (requires(U x) { Monoid::make(x); }) {
            return Monoid::make(value);
        } else {
            return static_cast<T>(value);
        }
    }

    int make_node(T val, int priority, bool rev, int l, int r) const {
        T prod = Monoid::op(Monoid::op(node_prod(l), val), node_prod(r));
        T rprod = Monoid::op(Monoid::op(node_rprod(r), val), node_rprod(l));
        if (rev) std::swap(prod, rprod);
        int count = 1 + subtree_size(l) + subtree_size(r);
        pool->emplace_back(std::move(val), std::move(prod), std::move(rprod), priority, count, l, r, rev);
        return int(pool->size()) - 1;
    }

    int reversed_node(int t) const {
        if (t == -1) return -1;
        Node node = (*pool)[t];
        return make_node(std::move(node.val), node.priority, !node.rev, node.l, node.r);
    }

    int push(int t) const {
        if (t == -1 || !(*pool)[t].rev) return t;
        Node node = (*pool)[t];
        int l = reversed_node(node.r);
        int r = reversed_node(node.l);
        return make_node(std::move(node.val), node.priority, false, l, r);
    }

    int merge(int l, int r) const {
        if (l == -1 || r == -1) return l == -1 ? r : l;
        if ((*pool)[l].priority > (*pool)[r].priority) {
            Node node = (*pool)[push(l)];
            int right = merge(node.r, r);
            return make_node(std::move(node.val), node.priority, false, node.l, right);
        }
        Node node = (*pool)[push(r)];
        int left = merge(l, node.l);
        return make_node(std::move(node.val), node.priority, false, left, node.r);
    }

    std::pair<int, int> split_node(int t, int pos) const {
        if (t == -1) return {-1, -1};
        Node node = (*pool)[push(t)];
        int left_count = subtree_size(node.l);
        if (pos <= left_count) {
            auto [a, b] = split_node(node.l, pos);
            return {a, make_node(std::move(node.val), node.priority, false, b, node.r)};
        }
        auto [a, b] = split_node(node.r, pos - left_count - 1);
        return {make_node(std::move(node.val), node.priority, false, node.l, a), b};
    }

    int set_node(int t, int pos, T val) const {
        Node node = (*pool)[push(t)];
        int left_count = subtree_size(node.l);
        if (pos < left_count) {
            int l = set_node(node.l, pos, std::move(val));
            return make_node(std::move(node.val), node.priority, false, l, node.r);
        }
        if (pos == left_count) {
            return make_node(std::move(val), node.priority, false, node.l, node.r);
        }
        int r = set_node(node.r, pos - left_count - 1, std::move(val));
        return make_node(std::move(node.val), node.priority, false, node.l, r);
    }

    int find_node(int t, int pos) const {
        bool reversed = false;
        while (t != -1) {
            const Node& node = (*pool)[t];
            bool cur_reversed = reversed ^ node.rev;
            int l = cur_reversed ? node.r : node.l;
            int r = cur_reversed ? node.l : node.r;
            int left_count = subtree_size(l);
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
        return -1;
    }

    T prod_dfs(int t, int ql, int qr, int offset, bool reversed = false) const {
        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return Monoid::id();
        const Node& node = (*pool)[t];
        if (ql <= offset && offset + node.count <= qr) return reversed ? node.rprod : node.prod;
        bool cur_reversed = reversed ^ node.rev;
        int l = cur_reversed ? node.r : node.l;
        int r = cur_reversed ? node.l : node.r;
        int left_count = subtree_size(l);
        int node_pos = offset + left_count;
        T res = prod_dfs(l, ql, qr, offset, cur_reversed);
        if (ql <= node_pos && node_pos < qr) res = Monoid::op(res, node.val);
        return Monoid::op(res, prod_dfs(r, ql, qr, node_pos + 1, cur_reversed));
    }

    void dump_dfs(int t, std::vector<T>& res, bool reversed = false) const {
        if (t == -1) return;
        const Node& node = (*pool)[t];
        bool cur_reversed = reversed ^ node.rev;
        int l = cur_reversed ? node.r : node.l;
        int r = cur_reversed ? node.l : node.r;
        dump_dfs(l, res, cur_reversed);
        res.push_back(node.val);
        dump_dfs(r, res, cur_reversed);
    }

    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>& res, bool reversed = false) const {
        if (t == -1 || qr <= offset || offset + (*pool)[t].count <= ql) return;
        const Node& node = (*pool)[t];
        bool cur_reversed = reversed ^ node.rev;
        int l = cur_reversed ? node.r : node.l;
        int r = cur_reversed ? node.l : node.r;
        int left_count = subtree_size(l);
        int node_pos = offset + left_count;
        dump_range_dfs(l, ql, qr, offset, res, cur_reversed);
        if (ql <= node_pos && node_pos < qr) res.push_back(node.val);
        dump_range_dfs(r, ql, qr, node_pos + 1, res, cur_reversed);
    }

    int build_from_nodes(std::vector<BuildNode>& nodes, int t) const {
        if (t == -1) return -1;
        int l = build_from_nodes(nodes, nodes[t].l);
        int r = build_from_nodes(nodes, nodes[t].r);
        return make_node(std::move(nodes[t].val), nodes[t].priority, false, l, r);
    }

    int build_cartesian(std::vector<BuildNode>& nodes) const {
        if (nodes.empty()) return -1;
        std::vector<int> stack;
        stack.reserve(nodes.size());
        for (int i = 0; i < int(nodes.size()); i++) {
            int left_child = -1;
            while (!stack.empty() && nodes[stack.back()].priority < nodes[i].priority) {
                left_child = stack.back();
                stack.pop_back();
            }
            nodes[i].l = left_child;
            if (!stack.empty()) nodes[stack.back()].r = i;
            stack.push_back(i);
        }
        return build_from_nodes(nodes, stack.front());
    }

    int build_from_vector(const std::vector<T>& v, std::uint32_t& state) const {
        std::vector<BuildNode> nodes;
        nodes.reserve(v.size());
        for (const T& x : v) nodes.emplace_back(x, next_priority(state));
        return build_cartesian(nodes);
    }

    int build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {
        std::vector<BuildNode> nodes;
        nodes.reserve(v.size());
        for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));
        return build_cartesian(nodes);
    }

    template <typename U>
    int build_from_values(const std::vector<U>& v, std::uint32_t& state) const {
        std::vector<BuildNode> nodes;
        nodes.reserve(v.size());
        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));
        return build_cartesian(nodes);
    }

    int import_node(const PersistentDynamicMonoidArray& other, int t) const {
        if (t == -1) return -1;
        if (pool == other.pool) return t;
        const Node& node = (*other.pool)[t];
        int l = import_node(other, node.l);
        int r = import_node(other, node.r);
        return make_node(node.val, node.priority, node.rev, l, r);
    }

    explicit PersistentDynamicMonoidArray(int node, std::uint32_t state,
                                          std::shared_ptr<std::vector<Node>> node_pool)
        : root(node), rng_state(state), pool(std::move(node_pool)) {}

   public:
    PersistentDynamicMonoidArray()
        : root(-1),
          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),
          pool(std::make_shared<std::vector<Node>>()) {
        if (rng_state == 0) rng_state = 1;
    }

    explicit PersistentDynamicMonoidArray(int n) : PersistentDynamicMonoidArray(n, Monoid::id()) {}

    PersistentDynamicMonoidArray(int n, const T& value) : PersistentDynamicMonoidArray() {
        assert(0 <= n);
        pool->reserve(n);
        std::vector<T> v(n, value);
        root = build_from_vector(std::move(v), rng_state);
    }

    explicit PersistentDynamicMonoidArray(const std::vector<T>& v) : PersistentDynamicMonoidArray() {
        pool->reserve(v.size());
        root = build_from_vector(v, rng_state);
    }

    explicit PersistentDynamicMonoidArray(std::vector<T>&& v) : PersistentDynamicMonoidArray() {
        pool->reserve(v.size());
        root = build_from_vector(std::move(v), rng_state);
    }

    template <typename U>
        requires(!std::same_as<U, T>) && (requires(U x) { Monoid::make(x); } || std::convertible_to<U, T>)
    explicit PersistentDynamicMonoidArray(const std::vector<U>& v) : PersistentDynamicMonoidArray() {
        pool->reserve(v.size());
        root = build_from_values(v, rng_state);
    }

    PersistentDynamicMonoidArray(std::initializer_list<T> init)
        : PersistentDynamicMonoidArray(std::vector<T>(init)) {}

    int size() const {
        return subtree_size(root);
    }

    bool empty() const {
        return size() == 0;
    }

    PersistentDynamicMonoidArray clear() const {
        return PersistentDynamicMonoidArray(-1, rng_state, pool);
    }

    PersistentDynamicMonoidArray insert(int pos, T value) const {
        assert(0 <= pos && pos <= size());
        std::uint32_t next = next_state(rng_state);
        int node = make_node(std::move(value), int(next), false, -1, -1);
        auto [l, r] = split_node(root, pos);
        return PersistentDynamicMonoidArray(merge(merge(l, node), r), next, pool);
    }

    PersistentDynamicMonoidArray insert(int pos, const std::vector<T>& v) const {
        assert(0 <= pos && pos <= size());
        if (v.empty()) return *this;
        std::uint32_t next = rng_state;
        int mid = build_from_vector(v, next);
        auto [l, r] = split_node(root, pos);
        return PersistentDynamicMonoidArray(merge(merge(l, mid), r), next, pool);
    }

    PersistentDynamicMonoidArray insert(int pos, std::vector<T>&& v) const {
        assert(0 <= pos && pos <= size());
        if (v.empty()) return *this;
        std::uint32_t next = rng_state;
        int mid = build_from_vector(std::move(v), next);
        auto [l, r] = split_node(root, pos);
        return PersistentDynamicMonoidArray(merge(merge(l, mid), r), next, pool);
    }

    PersistentDynamicMonoidArray insert(int pos, std::initializer_list<T> init) const {
        return insert(pos, std::vector<T>(init));
    }

    PersistentDynamicMonoidArray insert(int pos, const PersistentDynamicMonoidArray& other) const {
        assert(0 <= pos && pos <= size());
        if (other.empty()) return *this;
        int mid = import_node(other, other.root);
        auto [l, r] = split_node(root, pos);
        return PersistentDynamicMonoidArray(merge(merge(l, mid), r), rng_state, pool);
    }

    PersistentDynamicMonoidArray push_back(T value) const {
        return insert(size(), std::move(value));
    }

    PersistentDynamicMonoidArray push_front(T value) const {
        return insert(0, std::move(value));
    }

    PersistentDynamicMonoidArray append(const std::vector<T>& v) const {
        return insert(size(), v);
    }

    PersistentDynamicMonoidArray append(std::vector<T>&& v) const {
        return insert(size(), std::move(v));
    }

    PersistentDynamicMonoidArray append(const PersistentDynamicMonoidArray& other) const {
        return insert(size(), other);
    }

    PersistentDynamicMonoidArray erase(int pos) const {
        assert(0 <= pos && pos < size());
        auto [a, b] = split_node(root, pos);
        auto [mid, c] = split_node(b, 1);
        (void)mid;
        return PersistentDynamicMonoidArray(merge(a, c), rng_state, pool);
    }

    PersistentDynamicMonoidArray erase(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return *this;
        auto [a, b] = split_node(root, l);
        auto [mid, c] = split_node(b, r - l);
        (void)mid;
        return PersistentDynamicMonoidArray(merge(a, c), rng_state, pool);
    }

    PersistentDynamicMonoidArray pop_back() const {
        assert(!empty());
        return erase(size() - 1);
    }

    PersistentDynamicMonoidArray pop_front() const {
        assert(!empty());
        return erase(0);
    }

    T get(int pos) const {
        assert(0 <= pos && pos < size());
        return (*pool)[find_node(root, pos)].val;
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

    PersistentDynamicMonoidArray set(int pos, T value) const {
        assert(0 <= pos && pos < size());
        return PersistentDynamicMonoidArray(set_node(root, pos, std::move(value)), rng_state, pool);
    }

    PersistentDynamicMonoidArray reverse(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return *this;
        auto [a, b] = split_node(root, l);
        auto [mid, c] = split_node(b, r - l);
        return PersistentDynamicMonoidArray(merge(merge(a, reversed_node(mid)), c), rng_state, pool);
    }

    PersistentDynamicMonoidArray reverse() const {
        return PersistentDynamicMonoidArray(reversed_node(root), rng_state, pool);
    }

    PersistentDynamicMonoidArray rotate(int l, int m, int r) const {
        assert(0 <= l && l <= m && m <= r && r <= size());
        if (l == m || m == r) return *this;
        auto [a, b] = split_node(root, l);
        auto [c, d] = split_node(b, m - l);
        auto [e, f] = split_node(d, r - m);
        return PersistentDynamicMonoidArray(merge(merge(a, e), merge(c, f)), rng_state, pool);
    }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return Monoid::id();
        return prod_dfs(root, l, r, 0);
    }

    T all_prod() const {
        return root == -1 ? Monoid::id() : (*pool)[root].prod;
    }

    std::pair<PersistentDynamicMonoidArray, PersistentDynamicMonoidArray> split(int pos) const {
        assert(0 <= pos && pos <= size());
        auto [l, r] = split_node(root, pos);
        return {PersistentDynamicMonoidArray(l, rng_state, pool),
                PersistentDynamicMonoidArray(r, rng_state, pool)};
    }

    PersistentDynamicMonoidArray split_off(int pos) const {
        assert(0 <= pos && pos <= size());
        return PersistentDynamicMonoidArray(split_node(root, pos).second, rng_state, pool);
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
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DYNAMIC_MONOID_ARRAY_HPP
