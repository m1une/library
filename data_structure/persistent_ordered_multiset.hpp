#ifndef M1UNE_PERSISTENT_ORDERED_MULTISET_HPP
#define M1UNE_PERSISTENT_ORDERED_MULTISET_HPP 1

#include <cassert>
#include <chrono>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <memory>
#include <utility>
#include <vector>

namespace m1une {
namespace data_structure {

template <typename T, typename Compare = std::less<T>>
struct PersistentOrderedMultiset {
   private:
    struct Node;
    using NodePtr = std::shared_ptr<const Node>;

    struct Node {
        T key;
        int priority;
        int count;
        int size;
        int distinct_size;
        NodePtr l, r;

        Node(T value, int node_priority, int multiplicity, NodePtr left, NodePtr right)
            : key(std::move(value)),
              priority(node_priority),
              count(multiplicity),
              size(multiplicity + subtree_size(left) + subtree_size(right)),
              distinct_size(1 + subtree_distinct_size(left) + subtree_distinct_size(right)),
              l(std::move(left)),
              r(std::move(right)) {}
    };

    NodePtr root;
    std::uint32_t rng_state;
    Compare comp;

    static int subtree_size(const NodePtr& t) {
        return t ? t->size : 0;
    }

    static int subtree_distinct_size(const NodePtr& t) {
        return t ? t->distinct_size : 0;
    }

    static std::uint32_t next_state(std::uint32_t state) {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state == 0 ? 1 : state;
    }

    bool equal(const T& a, const T& b) const {
        return !comp(a, b) && !comp(b, a);
    }

    NodePtr make_node(T key, int priority, int count, NodePtr l, NodePtr r) const {
        return std::make_shared<Node>(std::move(key), priority, count, std::move(l), std::move(r));
    }

    NodePtr merge(const NodePtr& l, const NodePtr& r) const {
        if (!l || !r) return l ? l : r;
        if (l->priority > r->priority) {
            return make_node(l->key, l->priority, l->count, l->l, merge(l->r, r));
        }
        return make_node(r->key, r->priority, r->count, merge(l, r->l), r->r);
    }

    NodePtr rotate_right(const NodePtr& t) const {
        NodePtr s = t->l;
        NodePtr new_t = make_node(t->key, t->priority, t->count, s->r, t->r);
        return make_node(s->key, s->priority, s->count, s->l, new_t);
    }

    NodePtr rotate_left(const NodePtr& t) const {
        NodePtr s = t->r;
        NodePtr new_t = make_node(t->key, t->priority, t->count, t->l, s->l);
        return make_node(s->key, s->priority, s->count, new_t, s->r);
    }

    NodePtr insert_impl(const NodePtr& t, T& key, int multiplicity, int priority) const {
        if (!t) return make_node(std::move(key), priority, multiplicity, nullptr, nullptr);
        if (equal(key, t->key)) {
            return make_node(t->key, t->priority, t->count + multiplicity, t->l, t->r);
        }
        if (comp(key, t->key)) {
            NodePtr l = insert_impl(t->l, key, multiplicity, priority);
            NodePtr res = make_node(t->key, t->priority, t->count, l, t->r);
            return l->priority > res->priority ? rotate_right(res) : res;
        }
        NodePtr r = insert_impl(t->r, key, multiplicity, priority);
        NodePtr res = make_node(t->key, t->priority, t->count, t->l, r);
        return r->priority > res->priority ? rotate_left(res) : res;
    }

    NodePtr erase_one_impl(const NodePtr& t, const T& key, bool& erased) const {
        if (!t) return nullptr;
        if (equal(key, t->key)) {
            erased = true;
            if (t->count > 1) return make_node(t->key, t->priority, t->count - 1, t->l, t->r);
            return merge(t->l, t->r);
        }
        if (comp(key, t->key)) {
            NodePtr l = erase_one_impl(t->l, key, erased);
            return erased ? make_node(t->key, t->priority, t->count, l, t->r) : t;
        }
        NodePtr r = erase_one_impl(t->r, key, erased);
        return erased ? make_node(t->key, t->priority, t->count, t->l, r) : t;
    }

    NodePtr erase_all_impl(const NodePtr& t, const T& key, int& erased) const {
        if (!t) return nullptr;
        if (equal(key, t->key)) {
            erased = t->count;
            return merge(t->l, t->r);
        }
        if (comp(key, t->key)) {
            NodePtr l = erase_all_impl(t->l, key, erased);
            return erased ? make_node(t->key, t->priority, t->count, l, t->r) : t;
        }
        NodePtr r = erase_all_impl(t->r, key, erased);
        return erased ? make_node(t->key, t->priority, t->count, t->l, r) : t;
    }

    const T* kth_impl(NodePtr t, int k) const {
        while (t) {
            int left_size = subtree_size(t->l);
            if (k < left_size) {
                t = t->l;
            } else if (k < left_size + t->count) {
                return &t->key;
            } else {
                k -= left_size + t->count;
                t = t->r;
            }
        }
        return nullptr;
    }

    int count_impl(NodePtr t, const T& key) const {
        while (t) {
            if (equal(key, t->key)) return t->count;
            t = comp(key, t->key) ? t->l : t->r;
        }
        return 0;
    }

    int order_of_key_impl(NodePtr t, const T& key) const {
        int res = 0;
        while (t) {
            if (comp(t->key, key)) {
                res += subtree_size(t->l) + t->count;
                t = t->r;
            } else {
                t = t->l;
            }
        }
        return res;
    }

    int order_of_key_upper_impl(NodePtr t, const T& key) const {
        int res = 0;
        while (t) {
            if (!comp(key, t->key)) {
                res += subtree_size(t->l) + t->count;
                t = t->r;
            } else {
                t = t->l;
            }
        }
        return res;
    }

    const T* lower_bound_impl(NodePtr t, const T& key) const {
        const T* res = nullptr;
        while (t) {
            if (!comp(t->key, key)) {
                res = &t->key;
                t = t->l;
            } else {
                t = t->r;
            }
        }
        return res;
    }

    const T* upper_bound_impl(NodePtr t, const T& key) const {
        const T* res = nullptr;
        while (t) {
            if (comp(key, t->key)) {
                res = &t->key;
                t = t->l;
            } else {
                t = t->r;
            }
        }
        return res;
    }

    const T* max_less_impl(NodePtr t, const T& key, bool strict) const {
        const T* res = nullptr;
        while (t) {
            bool ok = strict ? comp(t->key, key) : !comp(key, t->key);
            if (ok) {
                res = &t->key;
                t = t->r;
            } else {
                t = t->l;
            }
        }
        return res;
    }

    void dump_impl(const NodePtr& t, std::vector<T>& res) const {
        if (!t) return;
        dump_impl(t->l, res);
        for (int i = 0; i < t->count; i++) {
            res.push_back(t->key);
        }
        dump_impl(t->r, res);
    }

    PersistentOrderedMultiset(NodePtr node, std::uint32_t state, Compare compare)
        : root(std::move(node)), rng_state(state), comp(std::move(compare)) {}

   public:
    explicit PersistentOrderedMultiset(Compare compare)
        : root(nullptr),
          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),
          comp(std::move(compare)) {
        if (rng_state == 0) rng_state = 1;
    }

    PersistentOrderedMultiset() : PersistentOrderedMultiset(Compare()) {}

    PersistentOrderedMultiset(std::initializer_list<T> init, Compare compare = Compare())
        : PersistentOrderedMultiset(std::move(compare)) {
        for (const T& x : init) *this = insert(x);
    }

    template <typename Iterator>
    PersistentOrderedMultiset(Iterator first, Iterator last, Compare compare = Compare())
        : PersistentOrderedMultiset(std::move(compare)) {
        while (first != last) {
            *this = insert(*first);
            ++first;
        }
    }

    int size() const {
        return subtree_size(root);
    }

    int unique_size() const {
        return subtree_distinct_size(root);
    }

    bool empty() const {
        return size() == 0;
    }

    PersistentOrderedMultiset clear() const {
        return PersistentOrderedMultiset(nullptr, rng_state, comp);
    }

    PersistentOrderedMultiset insert(T key, int multiplicity = 1) const {
        assert(multiplicity > 0);
        std::uint32_t next = next_state(rng_state);
        return PersistentOrderedMultiset(insert_impl(root, key, multiplicity, int(next)), next, comp);
    }

    PersistentOrderedMultiset erase_one(const T& key) const {
        bool erased = false;
        NodePtr next_root = erase_one_impl(root, key, erased);
        return erased ? PersistentOrderedMultiset(next_root, rng_state, comp) : *this;
    }

    PersistentOrderedMultiset erase(const T& key) const {
        return erase_one(key);
    }

    PersistentOrderedMultiset erase_all(const T& key) const {
        int erased = 0;
        NodePtr next_root = erase_all_impl(root, key, erased);
        return erased ? PersistentOrderedMultiset(next_root, rng_state, comp) : *this;
    }

    bool contains(const T& key) const {
        return count(key) > 0;
    }

    int count(const T& key) const {
        return count_impl(root, key);
    }

    const T* find_by_order(int k) const {
        assert(0 <= k && k < size());
        return kth_impl(root, k);
    }

    T kth(int k) const {
        assert(0 <= k && k < size());
        return *kth_impl(root, k);
    }

    int order_of_key(const T& key) const {
        return order_of_key_impl(root, key);
    }

    int count_less(const T& key) const {
        return order_of_key(key);
    }

    int count_less_equal(const T& key) const {
        return order_of_key_upper_impl(root, key);
    }

    int count_greater(const T& key) const {
        return size() - count_less_equal(key);
    }

    int count_greater_equal(const T& key) const {
        return size() - count_less(key);
    }

    const T* lower_bound(const T& key) const {
        return lower_bound_impl(root, key);
    }

    const T* upper_bound(const T& key) const {
        return upper_bound_impl(root, key);
    }

    const T* min_ge(const T& key) const {
        return lower_bound(key);
    }

    const T* min_gt(const T& key) const {
        return upper_bound(key);
    }

    const T* max_le(const T& key) const {
        return max_less_impl(root, key, false);
    }

    const T* max_lt(const T& key) const {
        return max_less_impl(root, key, true);
    }

    const T* min() const {
        return empty() ? nullptr : kth_impl(root, 0);
    }

    const T* max() const {
        return empty() ? nullptr : kth_impl(root, size() - 1);
    }

    std::vector<T> to_vector() const {
        std::vector<T> res;
        res.reserve(size());
        dump_impl(root, res);
        return res;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_ORDERED_MULTISET_HPP
