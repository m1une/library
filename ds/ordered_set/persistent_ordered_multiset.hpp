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
namespace ds {

template <typename T, typename Compare = std::less<T>>
struct PersistentOrderedMultiset {
   private:
    struct Node {
        T key;
        int priority;
        int count;
        int size;
        int distinct_size;
        int l, r;

        Node(T value, int node_priority, int multiplicity, int subtree_count, int unique_count, int left,
             int right)
            : key(std::move(value)),
              priority(node_priority),
              count(multiplicity),
              size(subtree_count),
              distinct_size(unique_count),
              l(left),
              r(right) {}
    };

    static constexpr int pool_block_bits = 16;
    static constexpr int pool_block_size = 1 << pool_block_bits;
    static constexpr int pool_block_mask = pool_block_size - 1;

    struct Pool {
        std::vector<std::vector<Node>> blocks;
        int node_count = 0;

        Node& operator[](int index) {
            return blocks[index >> pool_block_bits][index & pool_block_mask];
        }

        const Node& operator[](int index) const {
            return blocks[index >> pool_block_bits][index & pool_block_mask];
        }

        template <class... Args>
        int emplace_back(Args&&... args) {
            if ((node_count & pool_block_mask) == 0) {
                blocks.emplace_back();
                blocks.back().reserve(pool_block_size);
            }
            blocks.back().emplace_back(std::forward<Args>(args)...);
            return node_count++;
        }
    };

    int root;
    std::uint32_t rng_state;
    Compare comp;
    std::shared_ptr<Pool> pool;

    int subtree_size(int t) const {
        return t == -1 ? 0 : (*pool)[t].size;
    }

    int subtree_distinct_size(int t) const {
        return t == -1 ? 0 : (*pool)[t].distinct_size;
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

    int make_node(T key, int priority, int count, int l, int r) const {
        int size = count + subtree_size(l) + subtree_size(r);
        int distinct_size = 1 + subtree_distinct_size(l) + subtree_distinct_size(r);
        return pool->emplace_back(std::move(key), priority, count, size, distinct_size, l, r);
    }

    int merge(int l, int r) const {
        if (l == -1 || r == -1) return l == -1 ? r : l;
        if ((*pool)[l].priority > (*pool)[r].priority) {
            const Node& node = (*pool)[l];
            int right = merge(node.r, r);
            return make_node(node.key, node.priority, node.count, node.l, right);
        }
        const Node& node = (*pool)[r];
        int left = merge(l, node.l);
        return make_node(node.key, node.priority, node.count, left, node.r);
    }

    int rotate_right(int t) const {
        const Node& node = (*pool)[t];
        const Node& child = (*pool)[node.l];
        int new_t = make_node(node.key, node.priority, node.count, child.r, node.r);
        return make_node(child.key, child.priority, child.count, child.l, new_t);
    }

    int rotate_left(int t) const {
        const Node& node = (*pool)[t];
        const Node& child = (*pool)[node.r];
        int new_t = make_node(node.key, node.priority, node.count, node.l, child.l);
        return make_node(child.key, child.priority, child.count, new_t, child.r);
    }

    int insert_impl(int t, T& key, int multiplicity, int priority) const {
        if (t == -1) return make_node(std::move(key), priority, multiplicity, -1, -1);
        const Node& node = (*pool)[t];
        if (equal(key, node.key)) {
            return make_node(node.key, node.priority, node.count + multiplicity, node.l, node.r);
        }
        if (comp(key, node.key)) {
            int l = insert_impl(node.l, key, multiplicity, priority);
            int res = make_node(node.key, node.priority, node.count, l, node.r);
            return (*pool)[l].priority > (*pool)[res].priority ? rotate_right(res) : res;
        }
        int r = insert_impl(node.r, key, multiplicity, priority);
        int res = make_node(node.key, node.priority, node.count, node.l, r);
        return (*pool)[r].priority > (*pool)[res].priority ? rotate_left(res) : res;
    }

    int erase_one_impl(int t, const T& key, bool& erased) const {
        if (t == -1) return -1;
        const Node& node = (*pool)[t];
        if (equal(key, node.key)) {
            erased = true;
            if (node.count > 1) {
                return make_node(node.key, node.priority, node.count - 1, node.l, node.r);
            }
            return merge(node.l, node.r);
        }
        if (comp(key, node.key)) {
            int l = erase_one_impl(node.l, key, erased);
            return erased ? make_node(node.key, node.priority, node.count, l, node.r) : t;
        }
        int r = erase_one_impl(node.r, key, erased);
        return erased ? make_node(node.key, node.priority, node.count, node.l, r) : t;
    }

    int erase_all_impl(int t, const T& key, int& erased) const {
        if (t == -1) return -1;
        const Node& node = (*pool)[t];
        if (equal(key, node.key)) {
            erased = node.count;
            return merge(node.l, node.r);
        }
        if (comp(key, node.key)) {
            int l = erase_all_impl(node.l, key, erased);
            return erased ? make_node(node.key, node.priority, node.count, l, node.r) : t;
        }
        int r = erase_all_impl(node.r, key, erased);
        return erased ? make_node(node.key, node.priority, node.count, node.l, r) : t;
    }

    const T* kth_impl(int t, int k) const {
        while (t != -1) {
            const Node& node = (*pool)[t];
            int left_size = subtree_size(node.l);
            if (k < left_size) {
                t = node.l;
            } else if (k < left_size + node.count) {
                return &node.key;
            } else {
                k -= left_size + node.count;
                t = node.r;
            }
        }
        return nullptr;
    }

    int count_impl(int t, const T& key) const {
        while (t != -1) {
            const Node& node = (*pool)[t];
            if (equal(key, node.key)) return node.count;
            t = comp(key, node.key) ? node.l : node.r;
        }
        return 0;
    }

    int order_of_key_impl(int t, const T& key) const {
        int res = 0;
        while (t != -1) {
            const Node& node = (*pool)[t];
            if (comp(node.key, key)) {
                res += subtree_size(node.l) + node.count;
                t = node.r;
            } else {
                t = node.l;
            }
        }
        return res;
    }

    int order_of_key_upper_impl(int t, const T& key) const {
        int res = 0;
        while (t != -1) {
            const Node& node = (*pool)[t];
            if (!comp(key, node.key)) {
                res += subtree_size(node.l) + node.count;
                t = node.r;
            } else {
                t = node.l;
            }
        }
        return res;
    }

    const T* lower_bound_impl(int t, const T& key) const {
        const T* res = nullptr;
        while (t != -1) {
            const Node& node = (*pool)[t];
            if (!comp(node.key, key)) {
                res = &node.key;
                t = node.l;
            } else {
                t = node.r;
            }
        }
        return res;
    }

    const T* upper_bound_impl(int t, const T& key) const {
        const T* res = nullptr;
        while (t != -1) {
            const Node& node = (*pool)[t];
            if (comp(key, node.key)) {
                res = &node.key;
                t = node.l;
            } else {
                t = node.r;
            }
        }
        return res;
    }

    const T* max_less_impl(int t, const T& key, bool strict) const {
        const T* res = nullptr;
        while (t != -1) {
            const Node& node = (*pool)[t];
            bool ok = strict ? comp(node.key, key) : !comp(key, node.key);
            if (ok) {
                res = &node.key;
                t = node.r;
            } else {
                t = node.l;
            }
        }
        return res;
    }

    void dump_impl(int t, std::vector<T>& res) const {
        if (t == -1) return;
        const Node& node = (*pool)[t];
        dump_impl(node.l, res);
        for (int i = 0; i < node.count; i++) res.push_back(node.key);
        dump_impl(node.r, res);
    }

    PersistentOrderedMultiset(
        int node,
        std::uint32_t state,
        Compare compare,
        std::shared_ptr<Pool> node_pool
    )
        : root(node), rng_state(state), comp(std::move(compare)), pool(std::move(node_pool)) {}

   public:
    explicit PersistentOrderedMultiset(Compare compare)
        : root(-1),
          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),
          comp(std::move(compare)),
          pool(std::make_shared<Pool>()) {
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
        return PersistentOrderedMultiset(-1, rng_state, comp, pool);
    }

    PersistentOrderedMultiset insert(T key, int multiplicity = 1) const {
        assert(multiplicity > 0);
        std::uint32_t next = next_state(rng_state);
        return PersistentOrderedMultiset(insert_impl(root, key, multiplicity, int(next)), next, comp, pool);
    }

    PersistentOrderedMultiset erase_one(const T& key) const {
        bool erased = false;
        int next_root = erase_one_impl(root, key, erased);
        return erased ? PersistentOrderedMultiset(next_root, rng_state, comp, pool) : *this;
    }

    PersistentOrderedMultiset erase(const T& key) const {
        return erase_one(key);
    }

    PersistentOrderedMultiset erase_all(const T& key) const {
        int erased = 0;
        int next_root = erase_all_impl(root, key, erased);
        return erased ? PersistentOrderedMultiset(next_root, rng_state, comp, pool) : *this;
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

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_PERSISTENT_ORDERED_MULTISET_HPP
