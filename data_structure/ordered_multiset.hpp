#ifndef M1UNE_ORDERED_MULTISET_HPP
#define M1UNE_ORDERED_MULTISET_HPP 1

#include <cassert>
#include <chrono>
#include <cstdint>
#include <functional>
#include <initializer_list>
#include <utility>
#include <vector>

namespace m1une {
namespace data_structure {

template <typename T, typename Compare = std::less<T>>
struct OrderedMultiset {
   private:
    struct Node {
        T key;
        int priority;
        int count;
        int size;
        int distinct_size;
        int l, r;

        Node(T value, int node_priority, int multiplicity)
            : key(std::move(value)),
              priority(node_priority),
              count(multiplicity),
              size(multiplicity),
              distinct_size(1),
              l(-1),
              r(-1) {}
    };

    std::vector<Node> pool;
    int root;
    std::uint32_t rng_state;
    Compare comp;

    bool equal(const T& a, const T& b) const {
        return !comp(a, b) && !comp(b, a);
    }

    int subtree_size(int t) const {
        return t == -1 ? 0 : pool[t].size;
    }

    int subtree_distinct_size(int t) const {
        return t == -1 ? 0 : pool[t].distinct_size;
    }

    int next_priority() {
        rng_state ^= rng_state << 13;
        rng_state ^= rng_state >> 17;
        rng_state ^= rng_state << 5;
        return int(rng_state);
    }

    int new_node(T key, int multiplicity) {
        pool.emplace_back(std::move(key), next_priority(), multiplicity);
        return int(pool.size()) - 1;
    }

    void update(int t) {
        if (t == -1) return;
        pool[t].size = pool[t].count + subtree_size(pool[t].l) + subtree_size(pool[t].r);
        pool[t].distinct_size = 1 + subtree_distinct_size(pool[t].l) + subtree_distinct_size(pool[t].r);
    }

    int merge(int l, int r) {
        if (l == -1 || r == -1) return l == -1 ? r : l;
        if (pool[l].priority > pool[r].priority) {
            pool[l].r = merge(pool[l].r, r);
            update(l);
            return l;
        }
        pool[r].l = merge(l, pool[r].l);
        update(r);
        return r;
    }

    void rotate_right(int& t) {
        int s = pool[t].l;
        pool[t].l = pool[s].r;
        pool[s].r = t;
        update(t);
        update(s);
        t = s;
    }

    void rotate_left(int& t) {
        int s = pool[t].r;
        pool[t].r = pool[s].l;
        pool[s].l = t;
        update(t);
        update(s);
        t = s;
    }

    int insert_impl(int t, T& key, int multiplicity) {
        if (t == -1) {
            return new_node(std::move(key), multiplicity);
        }
        if (equal(key, pool[t].key)) {
            pool[t].count += multiplicity;
            update(t);
            return t;
        }
        if (comp(key, pool[t].key)) {
            int l = insert_impl(pool[t].l, key, multiplicity);
            pool[t].l = l;
            if (pool[pool[t].l].priority > pool[t].priority) rotate_right(t);
        } else {
            int r = insert_impl(pool[t].r, key, multiplicity);
            pool[t].r = r;
            if (pool[pool[t].r].priority > pool[t].priority) rotate_left(t);
        }
        update(t);
        return t;
    }

    bool erase_one_impl(int& t, const T& key) {
        if (t == -1) return false;
        bool erased = false;
        if (equal(key, pool[t].key)) {
            erased = true;
            if (pool[t].count > 1) {
                pool[t].count--;
            } else {
                t = merge(pool[t].l, pool[t].r);
                return true;
            }
        } else if (comp(key, pool[t].key)) {
            erased = erase_one_impl(pool[t].l, key);
        } else {
            erased = erase_one_impl(pool[t].r, key);
        }
        update(t);
        return erased;
    }

    int erase_all_impl(int& t, const T& key) {
        if (t == -1) return 0;
        int erased = 0;
        if (equal(key, pool[t].key)) {
            erased = pool[t].count;
            t = merge(pool[t].l, pool[t].r);
            return erased;
        }
        if (comp(key, pool[t].key)) {
            erased = erase_all_impl(pool[t].l, key);
        } else {
            erased = erase_all_impl(pool[t].r, key);
        }
        update(t);
        return erased;
    }

    const T* kth_impl(int t, int k) const {
        while (t != -1) {
            int left_size = subtree_size(pool[t].l);
            if (k < left_size) {
                t = pool[t].l;
            } else if (k < left_size + pool[t].count) {
                return &pool[t].key;
            } else {
                k -= left_size + pool[t].count;
                t = pool[t].r;
            }
        }
        return nullptr;
    }

    int count_impl(int t, const T& key) const {
        while (t != -1) {
            if (equal(key, pool[t].key)) return pool[t].count;
            t = comp(key, pool[t].key) ? pool[t].l : pool[t].r;
        }
        return 0;
    }

    int order_of_key_impl(int t, const T& key) const {
        int res = 0;
        while (t != -1) {
            if (comp(pool[t].key, key)) {
                res += subtree_size(pool[t].l) + pool[t].count;
                t = pool[t].r;
            } else {
                t = pool[t].l;
            }
        }
        return res;
    }

    int order_of_key_upper_impl(int t, const T& key) const {
        int res = 0;
        while (t != -1) {
            if (!comp(key, pool[t].key)) {
                res += subtree_size(pool[t].l) + pool[t].count;
                t = pool[t].r;
            } else {
                t = pool[t].l;
            }
        }
        return res;
    }

    const T* lower_bound_impl(int t, const T& key) const {
        const T* res = nullptr;
        while (t != -1) {
            if (!comp(pool[t].key, key)) {
                res = &pool[t].key;
                t = pool[t].l;
            } else {
                t = pool[t].r;
            }
        }
        return res;
    }

    const T* upper_bound_impl(int t, const T& key) const {
        const T* res = nullptr;
        while (t != -1) {
            if (comp(key, pool[t].key)) {
                res = &pool[t].key;
                t = pool[t].l;
            } else {
                t = pool[t].r;
            }
        }
        return res;
    }

    const T* max_less_impl(int t, const T& key, bool strict) const {
        const T* res = nullptr;
        while (t != -1) {
            bool ok = strict ? comp(pool[t].key, key) : !comp(key, pool[t].key);
            if (ok) {
                res = &pool[t].key;
                t = pool[t].r;
            } else {
                t = pool[t].l;
            }
        }
        return res;
    }

    void dump_impl(int t, std::vector<T>& res) const {
        if (t == -1) return;
        dump_impl(pool[t].l, res);
        for (int i = 0; i < pool[t].count; i++) {
            res.push_back(pool[t].key);
        }
        dump_impl(pool[t].r, res);
    }

   public:
    explicit OrderedMultiset(Compare compare)
        : root(-1),
          rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count())),
          comp(std::move(compare)) {
        if (rng_state == 0) rng_state = 1;
    }

    OrderedMultiset() : OrderedMultiset(Compare()) {}

    OrderedMultiset(std::initializer_list<T> init, Compare compare = Compare()) : OrderedMultiset(std::move(compare)) {
        for (const T& x : init) insert(x);
    }

    template <typename Iterator>
    OrderedMultiset(Iterator first, Iterator last, Compare compare = Compare()) : OrderedMultiset(std::move(compare)) {
        while (first != last) {
            insert(*first);
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

    void clear() {
        pool.clear();
        root = -1;
    }

    void insert(T key, int multiplicity = 1) {
        assert(multiplicity > 0);
        root = insert_impl(root, key, multiplicity);
    }

    bool erase_one(const T& key) {
        return erase_one_impl(root, key);
    }

    bool erase(const T& key) {
        return erase_one(key);
    }

    int erase_all(const T& key) {
        return erase_all_impl(root, key);
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

#endif  // M1UNE_ORDERED_MULTISET_HPP
