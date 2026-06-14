#ifndef M1UNE_PERSISTENT_DYNAMIC_LAZY_MONOID_ARRAY_HPP
#define M1UNE_PERSISTENT_DYNAMIC_LAZY_MONOID_ARRAY_HPP 1

#include <cassert>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

#include "acted_monoid/concept.hpp"

namespace m1une {
namespace data_structure {

template <m1une::acted_monoid::IsActedMonoid ActedMonoid>
struct PersistentDynamicLazyMonoidArray {
    using T = typename ActedMonoid::value_type;
    using F = typename ActedMonoid::operator_type;

   private:
    struct Node;
    using NodePtr = std::shared_ptr<const Node>;

    struct Node {
        T val, prod, rprod;
        F lazy;
        int priority;
        int count;
        bool rev;
        bool has_lazy;
        NodePtr l, r;

        Node(T value, int node_priority, bool reversed, NodePtr left, NodePtr right)
            : val(std::move(value)),
              prod(ActedMonoid::op(ActedMonoid::op(node_prod(left), val), node_prod(right))),
              rprod(ActedMonoid::op(ActedMonoid::op(node_rprod(right), val), node_rprod(left))),
              lazy(ActedMonoid::op_id()),
              priority(node_priority),
              count(1 + subtree_size(left) + subtree_size(right)),
              rev(reversed),
              has_lazy(false),
              l(std::move(left)),
              r(std::move(right)) {
            if (rev) std::swap(prod, rprod);
        }

        Node(T value, T product, T reverse_product, F lazy_value, int node_priority, int node_count, bool reversed,
             bool lazy_flag, NodePtr left, NodePtr right)
            : val(std::move(value)),
              prod(std::move(product)),
              rprod(std::move(reverse_product)),
              lazy(std::move(lazy_value)),
              priority(node_priority),
              count(node_count),
              rev(reversed),
              has_lazy(lazy_flag),
              l(std::move(left)),
              r(std::move(right)) {}
    };

    struct BuildNode {
        T val;
        int priority;
        int l, r;

        BuildNode(T value, int node_priority) : val(std::move(value)), priority(node_priority), l(-1), r(-1) {}
    };

    NodePtr root;
    std::uint32_t rng_state;

    static int subtree_size(const NodePtr& t) {
        return t ? t->count : 0;
    }

    static T node_prod(const NodePtr& t) {
        return t ? t->prod : ActedMonoid::id();
    }

    static T node_rprod(const NodePtr& t) {
        return t ? t->rprod : ActedMonoid::id();
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

    static F compose_for_child(const F& inherited, const NodePtr& t, long long ord) {
        F shifted = shift_operator(inherited, ord);
        if (!t->has_lazy) return shifted;
        return ActedMonoid::op_comp(shifted, shift_operator(t->lazy, ord));
    }

    NodePtr make_node(T val, int priority, bool rev, NodePtr l, NodePtr r) const {
        return std::make_shared<Node>(std::move(val), priority, rev, std::move(l), std::move(r));
    }

    NodePtr make_raw_node(T val, T prod, T rprod, F lazy, int priority, int count, bool rev, bool has_lazy,
                          NodePtr l, NodePtr r) const {
        return std::make_shared<Node>(std::move(val), std::move(prod), std::move(rprod), std::move(lazy), priority,
                                      count, rev, has_lazy, std::move(l), std::move(r));
    }

    NodePtr reversed_node(const NodePtr& t) const {
        if (!t) return nullptr;
        F lazy = t->has_lazy ? reverse_operator(t->lazy, t->count) : t->lazy;
        return make_raw_node(t->val, t->rprod, t->prod, lazy, t->priority, t->count, !t->rev, t->has_lazy, t->l,
                             t->r);
    }

    NodePtr all_apply(const NodePtr& t, const F& f) const {
        if (!t) return nullptr;
        int left_count = t->rev ? subtree_size(t->r) : subtree_size(t->l);
        return make_raw_node(mapping_at(f, t->val, left_count), mapping_at(f, t->prod, 0),
                             mapping_at(reverse_operator(f, t->count), t->rprod, 0),
                             ActedMonoid::op_comp(f, t->lazy), t->priority, t->count, t->rev, true, t->l, t->r);
    }

    NodePtr push(const NodePtr& t) const {
        if (!t) return nullptr;
        if (!t->rev && !t->has_lazy) return t;
        NodePtr l = t->l;
        NodePtr r = t->r;
        if (t->rev) {
            std::swap(l, r);
            l = reversed_node(l);
            r = reversed_node(r);
        }
        if (t->has_lazy) {
            l = all_apply(l, t->lazy);
            r = all_apply(r, shift_operator(t->lazy, subtree_size(l) + 1));
        }
        return make_node(t->val, t->priority, false, std::move(l), std::move(r));
    }

    NodePtr merge(const NodePtr& l, const NodePtr& r) const {
        if (!l || !r) return l ? l : r;
        if (l->priority > r->priority) {
            NodePtr t = push(l);
            return make_node(t->val, t->priority, false, t->l, merge(t->r, r));
        }
        NodePtr t = push(r);
        return make_node(t->val, t->priority, false, merge(l, t->l), t->r);
    }

    std::pair<NodePtr, NodePtr> split(const NodePtr& t, int pos) const {
        if (!t) return {nullptr, nullptr};
        NodePtr u = push(t);
        int left_count = subtree_size(u->l);
        if (pos <= left_count) {
            auto [a, b] = split(u->l, pos);
            return {a, make_node(u->val, u->priority, false, b, u->r)};
        }
        auto [a, b] = split(u->r, pos - left_count - 1);
        return {make_node(u->val, u->priority, false, u->l, a), b};
    }

    NodePtr set_node(const NodePtr& t, int pos, T val) const {
        NodePtr u = push(t);
        int left_count = subtree_size(u->l);
        if (pos < left_count) {
            return make_node(u->val, u->priority, false, set_node(u->l, pos, std::move(val)), u->r);
        }
        if (pos == left_count) {
            return make_node(std::move(val), u->priority, false, u->l, u->r);
        }
        return make_node(u->val, u->priority, false, u->l, set_node(u->r, pos - left_count - 1, std::move(val)));
    }

    T get_value(NodePtr t, int pos, F inherited, bool reversed = false) const {
        while (t) {
            bool cur_reversed = reversed ^ t->rev;
            NodePtr l = cur_reversed ? t->r : t->l;
            NodePtr r = cur_reversed ? t->l : t->r;
            int left_count = subtree_size(l);
            if (pos < left_count) {
                inherited = compose_for_child(inherited, t, 0);
                t = std::move(l);
                reversed = cur_reversed;
            } else if (pos == left_count) {
                return mapping_at(inherited, t->val, left_count);
            } else {
                pos -= left_count + 1;
                inherited = compose_for_child(inherited, t, left_count + 1);
                t = std::move(r);
                reversed = cur_reversed;
            }
        }
        return ActedMonoid::id();
    }

    T prod_dfs(const NodePtr& t, int ql, int qr, int offset, const F& inherited, bool reversed = false) const {
        if (!t || qr <= offset || offset + t->count <= ql) return ActedMonoid::id();
        bool cur_reversed = reversed ^ t->rev;
        if (ql <= offset && offset + t->count <= qr) {
            return mapping_at(inherited, reversed ? t->rprod : t->prod, 0);
        }
        const NodePtr& l = cur_reversed ? t->r : t->l;
        const NodePtr& r = cur_reversed ? t->l : t->r;
        int left_count = subtree_size(l);
        int node_pos = offset + left_count;
        T res = prod_dfs(l, ql, qr, offset, compose_for_child(inherited, t, 0), cur_reversed);
        if (ql <= node_pos && node_pos < qr) res = ActedMonoid::op(res, mapping_at(inherited, t->val, left_count));
        return ActedMonoid::op(
            res, prod_dfs(r, ql, qr, node_pos + 1, compose_for_child(inherited, t, left_count + 1), cur_reversed));
    }

    void dump_dfs(const NodePtr& t, std::vector<T>& res, const F& inherited, bool reversed = false) const {
        if (!t) return;
        bool cur_reversed = reversed ^ t->rev;
        const NodePtr& l = cur_reversed ? t->r : t->l;
        const NodePtr& r = cur_reversed ? t->l : t->r;
        int left_count = subtree_size(l);
        dump_dfs(l, res, compose_for_child(inherited, t, 0), cur_reversed);
        res.push_back(mapping_at(inherited, t->val, left_count));
        dump_dfs(r, res, compose_for_child(inherited, t, left_count + 1), cur_reversed);
    }

    void dump_range_dfs(const NodePtr& t, int ql, int qr, int offset, std::vector<T>& res, const F& inherited,
                        bool reversed = false) const {
        if (!t || qr <= offset || offset + t->count <= ql) return;
        bool cur_reversed = reversed ^ t->rev;
        const NodePtr& l = cur_reversed ? t->r : t->l;
        const NodePtr& r = cur_reversed ? t->l : t->r;
        int left_count = subtree_size(l);
        int node_pos = offset + left_count;
        dump_range_dfs(l, ql, qr, offset, res, compose_for_child(inherited, t, 0), cur_reversed);
        if (ql <= node_pos && node_pos < qr) res.push_back(mapping_at(inherited, t->val, left_count));
        dump_range_dfs(r, ql, qr, node_pos + 1, res, compose_for_child(inherited, t, left_count + 1),
                       cur_reversed);
    }

    NodePtr build_from_nodes(std::vector<BuildNode>& nodes, int t) const {
        if (t == -1) return nullptr;
        NodePtr l = build_from_nodes(nodes, nodes[t].l);
        NodePtr r = build_from_nodes(nodes, nodes[t].r);
        return make_node(std::move(nodes[t].val), nodes[t].priority, false, std::move(l), std::move(r));
    }

    NodePtr build_cartesian(std::vector<BuildNode>& nodes) const {
        if (nodes.empty()) return nullptr;
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

    NodePtr build_from_vector(const std::vector<T>& v, std::uint32_t& state) const {
        std::vector<BuildNode> nodes;
        nodes.reserve(v.size());
        for (const T& x : v) nodes.emplace_back(x, next_priority(state));
        return build_cartesian(nodes);
    }

    NodePtr build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {
        std::vector<BuildNode> nodes;
        nodes.reserve(v.size());
        for (T& x : v) nodes.emplace_back(std::move(x), next_priority(state));
        return build_cartesian(nodes);
    }

    template <typename U>
    NodePtr build_from_values(const std::vector<U>& v, std::uint32_t& state) const {
        std::vector<BuildNode> nodes;
        nodes.reserve(v.size());
        for (const U& x : v) nodes.emplace_back(make_value(x), next_priority(state));
        return build_cartesian(nodes);
    }

    explicit PersistentDynamicLazyMonoidArray(NodePtr node, std::uint32_t state)
        : root(std::move(node)), rng_state(state) {}

   public:
    PersistentDynamicLazyMonoidArray()
        : root(nullptr), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())) {
        if (rng_state == 0) rng_state = 1;
    }

    explicit PersistentDynamicLazyMonoidArray(int n) : PersistentDynamicLazyMonoidArray(n, ActedMonoid::id()) {}

    PersistentDynamicLazyMonoidArray(int n, const T& value) : PersistentDynamicLazyMonoidArray() {
        assert(0 <= n);
        std::vector<T> v(n, value);
        root = build_from_vector(std::move(v), rng_state);
    }

    explicit PersistentDynamicLazyMonoidArray(const std::vector<T>& v) : PersistentDynamicLazyMonoidArray() {
        root = build_from_vector(v, rng_state);
    }

    explicit PersistentDynamicLazyMonoidArray(std::vector<T>&& v) : PersistentDynamicLazyMonoidArray() {
        root = build_from_vector(std::move(v), rng_state);
    }

    template <typename U>
        requires(!std::same_as<U, T>) && (requires(U x) { ActedMonoid::make(x); } || std::convertible_to<U, T>)
    explicit PersistentDynamicLazyMonoidArray(const std::vector<U>& v) : PersistentDynamicLazyMonoidArray() {
        root = build_from_values(v, rng_state);
    }

    PersistentDynamicLazyMonoidArray(std::initializer_list<T> init)
        : PersistentDynamicLazyMonoidArray(std::vector<T>(init)) {}

    int size() const {
        return subtree_size(root);
    }

    bool empty() const {
        return size() == 0;
    }

    PersistentDynamicLazyMonoidArray clear() const {
        return PersistentDynamicLazyMonoidArray(nullptr, rng_state);
    }

    PersistentDynamicLazyMonoidArray insert(int pos, T value) const {
        assert(0 <= pos && pos <= size());
        std::uint32_t next = next_state(rng_state);
        NodePtr node = make_node(std::move(value), int(next), false, nullptr, nullptr);
        auto [l, r] = split(root, pos);
        return PersistentDynamicLazyMonoidArray(merge(merge(l, node), r), next);
    }

    PersistentDynamicLazyMonoidArray insert(int pos, const std::vector<T>& v) const {
        assert(0 <= pos && pos <= size());
        if (v.empty()) return *this;
        std::uint32_t next = rng_state;
        NodePtr mid = build_from_vector(v, next);
        auto [l, r] = split(root, pos);
        return PersistentDynamicLazyMonoidArray(merge(merge(l, mid), r), next);
    }

    PersistentDynamicLazyMonoidArray insert(int pos, std::vector<T>&& v) const {
        assert(0 <= pos && pos <= size());
        if (v.empty()) return *this;
        std::uint32_t next = rng_state;
        NodePtr mid = build_from_vector(std::move(v), next);
        auto [l, r] = split(root, pos);
        return PersistentDynamicLazyMonoidArray(merge(merge(l, mid), r), next);
    }

    PersistentDynamicLazyMonoidArray insert(int pos, std::initializer_list<T> init) const {
        return insert(pos, std::vector<T>(init));
    }

    PersistentDynamicLazyMonoidArray insert(int pos, const PersistentDynamicLazyMonoidArray& other) const {
        assert(0 <= pos && pos <= size());
        if (other.empty()) return *this;
        auto [l, r] = split(root, pos);
        return PersistentDynamicLazyMonoidArray(merge(merge(l, other.root), r), rng_state);
    }

    PersistentDynamicLazyMonoidArray push_back(T value) const {
        return insert(size(), std::move(value));
    }

    PersistentDynamicLazyMonoidArray push_front(T value) const {
        return insert(0, std::move(value));
    }

    PersistentDynamicLazyMonoidArray append(const std::vector<T>& v) const {
        return insert(size(), v);
    }

    PersistentDynamicLazyMonoidArray append(std::vector<T>&& v) const {
        return insert(size(), std::move(v));
    }

    PersistentDynamicLazyMonoidArray append(const PersistentDynamicLazyMonoidArray& other) const {
        return insert(size(), other);
    }

    PersistentDynamicLazyMonoidArray erase(int pos) const {
        assert(0 <= pos && pos < size());
        auto [a, b] = split(root, pos);
        auto [mid, c] = split(b, 1);
        (void)mid;
        return PersistentDynamicLazyMonoidArray(merge(a, c), rng_state);
    }

    PersistentDynamicLazyMonoidArray erase(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return *this;
        auto [a, b] = split(root, l);
        auto [mid, c] = split(b, r - l);
        (void)mid;
        return PersistentDynamicLazyMonoidArray(merge(a, c), rng_state);
    }

    PersistentDynamicLazyMonoidArray pop_back() const {
        assert(!empty());
        return erase(size() - 1);
    }

    PersistentDynamicLazyMonoidArray pop_front() const {
        assert(!empty());
        return erase(0);
    }

    T get(int pos) const {
        assert(0 <= pos && pos < size());
        return get_value(root, pos, ActedMonoid::op_id());
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

    PersistentDynamicLazyMonoidArray set(int pos, T value) const {
        assert(0 <= pos && pos < size());
        return PersistentDynamicLazyMonoidArray(set_node(root, pos, std::move(value)), rng_state);
    }

    PersistentDynamicLazyMonoidArray reverse(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return *this;
        auto [a, b] = split(root, l);
        auto [mid, c] = split(b, r - l);
        return PersistentDynamicLazyMonoidArray(merge(merge(a, reversed_node(mid)), c), rng_state);
    }

    PersistentDynamicLazyMonoidArray reverse() const {
        return PersistentDynamicLazyMonoidArray(reversed_node(root), rng_state);
    }

    PersistentDynamicLazyMonoidArray rotate(int l, int m, int r) const {
        assert(0 <= l && l <= m && m <= r && r <= size());
        if (l == m || m == r) return *this;
        auto [a, b] = split(root, l);
        auto [c, d] = split(b, m - l);
        auto [e, f] = split(d, r - m);
        return PersistentDynamicLazyMonoidArray(merge(merge(a, e), merge(c, f)), rng_state);
    }

    PersistentDynamicLazyMonoidArray apply(int pos, const F& f) const {
        assert(0 <= pos && pos < size());
        return apply(pos, pos + 1, f);
    }

    PersistentDynamicLazyMonoidArray apply(int l, int r, const F& f) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return *this;
        auto [a, b] = split(root, l);
        auto [mid, c] = split(b, r - l);
        return PersistentDynamicLazyMonoidArray(merge(merge(a, all_apply(mid, f)), c), rng_state);
    }

    T prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return ActedMonoid::id();
        return prod_dfs(root, l, r, 0, ActedMonoid::op_id());
    }

    T all_prod() const {
        return root ? root->prod : ActedMonoid::id();
    }

    std::pair<PersistentDynamicLazyMonoidArray, PersistentDynamicLazyMonoidArray> split(int pos) const {
        assert(0 <= pos && pos <= size());
        auto [l, r] = split(root, pos);
        return {PersistentDynamicLazyMonoidArray(l, rng_state), PersistentDynamicLazyMonoidArray(r, rng_state)};
    }

    PersistentDynamicLazyMonoidArray split_off(int pos) const {
        assert(0 <= pos && pos <= size());
        return PersistentDynamicLazyMonoidArray(split(root, pos).second, rng_state);
    }

    std::vector<T> to_vector() const {
        std::vector<T> res;
        res.reserve(size());
        dump_dfs(root, res, ActedMonoid::op_id());
        return res;
    }

    std::vector<T> to_vector(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        std::vector<T> res;
        res.reserve(r - l);
        dump_range_dfs(root, l, r, 0, res, ActedMonoid::op_id());
        return res;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DYNAMIC_LAZY_MONOID_ARRAY_HPP
