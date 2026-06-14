#ifndef M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP
#define M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP 1

#include <cassert>
#include <chrono>
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

namespace m1une {
namespace data_structure {

template <typename T>
struct PersistentDynamicArray {
   private:
    struct Node;
    using NodePtr = std::shared_ptr<const Node>;

    struct Node {
        T val;
        int priority;
        int count;
        bool rev;
        NodePtr l, r;

        Node(T value, int node_priority, bool reversed, NodePtr left, NodePtr right)
            : val(std::move(value)),
              priority(node_priority),
              count(1 + subtree_size(left) + subtree_size(right)),
              rev(reversed),
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

    NodePtr make_node(T val, int priority, bool rev, NodePtr l, NodePtr r) const {
        return std::make_shared<Node>(std::move(val), priority, rev, std::move(l), std::move(r));
    }

    NodePtr reversed_node(const NodePtr& t) const {
        if (!t) return nullptr;
        return make_node(t->val, t->priority, !t->rev, t->l, t->r);
    }

    NodePtr push(const NodePtr& t) const {
        if (!t || !t->rev) return t;
        return make_node(t->val, t->priority, false, reversed_node(t->r), reversed_node(t->l));
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

    const Node* find_node(NodePtr t, int pos) const {
        bool reversed = false;
        while (t) {
            bool cur_reversed = reversed ^ t->rev;
            NodePtr left = cur_reversed ? t->r : t->l;
            NodePtr right = cur_reversed ? t->l : t->r;
            int left_count = subtree_size(left);
            if (pos < left_count) {
                t = std::move(left);
                reversed = cur_reversed;
            } else if (pos == left_count) {
                return t.get();
            } else {
                pos -= left_count + 1;
                t = std::move(right);
                reversed = cur_reversed;
            }
        }
        return nullptr;
    }

    void dump_dfs(const NodePtr& t, std::vector<T>& res, bool reversed = false) const {
        if (!t) return;
        bool cur_reversed = reversed ^ t->rev;
        const NodePtr& left = cur_reversed ? t->r : t->l;
        const NodePtr& right = cur_reversed ? t->l : t->r;
        dump_dfs(left, res, cur_reversed);
        res.push_back(t->val);
        dump_dfs(right, res, cur_reversed);
    }

    void dump_range_dfs(const NodePtr& t, int ql, int qr, int offset, std::vector<T>& res,
                        bool reversed = false) const {
        if (!t || qr <= offset || offset + t->count <= ql) return;
        bool cur_reversed = reversed ^ t->rev;
        const NodePtr& left = cur_reversed ? t->r : t->l;
        const NodePtr& right = cur_reversed ? t->l : t->r;
        int left_count = subtree_size(left);
        int node_pos = offset + left_count;
        dump_range_dfs(left, ql, qr, offset, res, cur_reversed);
        if (ql <= node_pos && node_pos < qr) {
            res.push_back(t->val);
        }
        dump_range_dfs(right, ql, qr, node_pos + 1, res, cur_reversed);
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
            if (!stack.empty()) {
                nodes[stack.back()].r = i;
            }
            stack.push_back(i);
        }
        return build_from_nodes(nodes, stack.front());
    }

    NodePtr build_from_vector(const std::vector<T>& v, std::uint32_t& state) const {
        std::vector<BuildNode> nodes;
        nodes.reserve(v.size());
        for (const T& x : v) {
            nodes.emplace_back(x, next_priority(state));
        }
        return build_cartesian(nodes);
    }

    NodePtr build_from_vector(std::vector<T>&& v, std::uint32_t& state) const {
        std::vector<BuildNode> nodes;
        nodes.reserve(v.size());
        for (T& x : v) {
            nodes.emplace_back(std::move(x), next_priority(state));
        }
        return build_cartesian(nodes);
    }

    explicit PersistentDynamicArray(NodePtr node, std::uint32_t state) : root(std::move(node)), rng_state(state) {}

   public:
    PersistentDynamicArray()
        : root(nullptr), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())) {
        if (rng_state == 0) rng_state = 1;
    }

    explicit PersistentDynamicArray(int n) : PersistentDynamicArray(n, T()) {}

    PersistentDynamicArray(int n, const T& value) : PersistentDynamicArray() {
        assert(0 <= n);
        std::vector<T> v(n, value);
        root = build_from_vector(std::move(v), rng_state);
    }

    explicit PersistentDynamicArray(const std::vector<T>& v) : PersistentDynamicArray() {
        root = build_from_vector(v, rng_state);
    }

    explicit PersistentDynamicArray(std::vector<T>&& v) : PersistentDynamicArray() {
        root = build_from_vector(std::move(v), rng_state);
    }

    PersistentDynamicArray(std::initializer_list<T> init) : PersistentDynamicArray(std::vector<T>(init)) {}

    int size() const {
        return subtree_size(root);
    }

    bool empty() const {
        return size() == 0;
    }

    PersistentDynamicArray clear() const {
        return PersistentDynamicArray(nullptr, rng_state);
    }

    PersistentDynamicArray insert(int pos, T val) const {
        assert(0 <= pos && pos <= size());
        std::uint32_t next = next_state(rng_state);
        NodePtr node = make_node(std::move(val), int(next), false, nullptr, nullptr);
        auto [l, r] = split(root, pos);
        return PersistentDynamicArray(merge(merge(l, node), r), next);
    }

    PersistentDynamicArray insert(int pos, const std::vector<T>& v) const {
        assert(0 <= pos && pos <= size());
        if (v.empty()) return *this;
        std::uint32_t next = rng_state;
        NodePtr mid = build_from_vector(v, next);
        auto [l, r] = split(root, pos);
        return PersistentDynamicArray(merge(merge(l, mid), r), next);
    }

    PersistentDynamicArray insert(int pos, std::vector<T>&& v) const {
        assert(0 <= pos && pos <= size());
        if (v.empty()) return *this;
        std::uint32_t next = rng_state;
        NodePtr mid = build_from_vector(std::move(v), next);
        auto [l, r] = split(root, pos);
        return PersistentDynamicArray(merge(merge(l, mid), r), next);
    }

    PersistentDynamicArray insert(int pos, std::initializer_list<T> init) const {
        return insert(pos, std::vector<T>(init));
    }

    PersistentDynamicArray insert(int pos, const PersistentDynamicArray& other) const {
        assert(0 <= pos && pos <= size());
        if (other.empty()) return *this;
        auto [l, r] = split(root, pos);
        return PersistentDynamicArray(merge(merge(l, other.root), r), rng_state);
    }

    PersistentDynamicArray push_back(T val) const {
        return insert(size(), std::move(val));
    }

    PersistentDynamicArray push_front(T val) const {
        return insert(0, std::move(val));
    }

    PersistentDynamicArray append(const std::vector<T>& v) const {
        return insert(size(), v);
    }

    PersistentDynamicArray append(std::vector<T>&& v) const {
        return insert(size(), std::move(v));
    }

    PersistentDynamicArray append(const PersistentDynamicArray& other) const {
        return insert(size(), other);
    }

    PersistentDynamicArray erase(int pos) const {
        assert(0 <= pos && pos < size());
        auto [a, b] = split(root, pos);
        auto [mid, c] = split(b, 1);
        (void)mid;
        return PersistentDynamicArray(merge(a, c), rng_state);
    }

    PersistentDynamicArray erase(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return *this;
        auto [a, b] = split(root, l);
        auto [mid, c] = split(b, r - l);
        (void)mid;
        return PersistentDynamicArray(merge(a, c), rng_state);
    }

    PersistentDynamicArray pop_back() const {
        assert(!empty());
        return erase(size() - 1);
    }

    PersistentDynamicArray pop_front() const {
        assert(!empty());
        return erase(0);
    }

    const T& at(int pos) const {
        assert(0 <= pos && pos < size());
        return find_node(root, pos)->val;
    }

    const T& operator[](int pos) const {
        return at(pos);
    }

    const T& front() const {
        assert(!empty());
        return at(0);
    }

    const T& back() const {
        assert(!empty());
        return at(size() - 1);
    }

    T get(int pos) const {
        return at(pos);
    }

    PersistentDynamicArray set(int pos, T val) const {
        assert(0 <= pos && pos < size());
        return PersistentDynamicArray(set_node(root, pos, std::move(val)), rng_state);
    }

    PersistentDynamicArray reverse(int l, int r) const {
        assert(0 <= l && l <= r && r <= size());
        if (l == r) return *this;
        auto [a, b] = split(root, l);
        auto [mid, c] = split(b, r - l);
        return PersistentDynamicArray(merge(merge(a, reversed_node(mid)), c), rng_state);
    }

    PersistentDynamicArray reverse() const {
        return PersistentDynamicArray(reversed_node(root), rng_state);
    }

    PersistentDynamicArray rotate(int l, int m, int r) const {
        assert(0 <= l && l <= m && m <= r && r <= size());
        if (l == m || m == r) return *this;
        auto [a, b] = split(root, l);
        auto [c, d] = split(b, m - l);
        auto [e, f] = split(d, r - m);
        return PersistentDynamicArray(merge(merge(a, e), merge(c, f)), rng_state);
    }

    std::pair<PersistentDynamicArray, PersistentDynamicArray> split(int pos) const {
        assert(0 <= pos && pos <= size());
        auto [l, r] = split(root, pos);
        return {PersistentDynamicArray(l, rng_state), PersistentDynamicArray(r, rng_state)};
    }

    PersistentDynamicArray split_off(int pos) const {
        assert(0 <= pos && pos <= size());
        return PersistentDynamicArray(split(root, pos).second, rng_state);
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

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_DYNAMIC_ARRAY_HPP
