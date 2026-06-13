#ifndef M1UNE_DYNAMIC_ARRAY_HPP
#define M1UNE_DYNAMIC_ARRAY_HPP 1

#include <cassert>
#include <chrono>
#include <initializer_list>
#include <random>
#include <utility>
#include <vector>

namespace m1une {
namespace data_structure {

template <typename T>
struct DynamicArray {
   private:
    struct Node {
        T val;
        int priority;
        int count;
        int l, r;
        bool rev;

        Node() : val(T()), priority(0), count(0), l(0), r(0), rev(false) {}
        Node(T val, int priority) : val(std::move(val)), priority(priority), count(1), l(0), r(0), rev(false) {}
    };

    std::vector<Node> pool;
    int root;
    std::mt19937 rng;

    int new_node(T val) {
        pool.push_back(Node(std::move(val), rng()));
        return pool.size() - 1;
    }

    void update(int t) {
        if (t) {
            pool[t].count = 1 + pool[pool[t].l].count + pool[pool[t].r].count;
        }
    }

    void apply_reverse(int t) {
        if (t) {
            pool[t].rev = !pool[t].rev;
        }
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
            int left = cur_reversed ? pool[t].r : pool[t].l;
            int right = cur_reversed ? pool[t].l : pool[t].r;
            int left_count = pool[left].count;
            if (pos < left_count) {
                t = left;
                reversed = cur_reversed;
            } else if (pos == left_count) {
                return t;
            } else {
                pos -= left_count + 1;
                t = right;
                reversed = cur_reversed;
            }
        }
        return 0;
    }

    void dump_dfs(int t, std::vector<T>& res, bool reversed = false) const {
        if (!t) return;
        bool cur_reversed = reversed ^ pool[t].rev;
        int left = cur_reversed ? pool[t].r : pool[t].l;
        int right = cur_reversed ? pool[t].l : pool[t].r;
        dump_dfs(left, res, cur_reversed);
        res.push_back(pool[t].val);
        dump_dfs(right, res, cur_reversed);
    }

    void dump_range_dfs(int t, int ql, int qr, int offset, std::vector<T>& res, bool reversed = false) const {
        if (!t || qr <= offset || offset + pool[t].count <= ql) return;
        bool cur_reversed = reversed ^ pool[t].rev;
        int left = cur_reversed ? pool[t].r : pool[t].l;
        int right = cur_reversed ? pool[t].l : pool[t].r;
        int left_count = pool[left].count;
        int node_pos = offset + left_count;
        dump_range_dfs(left, ql, qr, offset, res, cur_reversed);
        if (ql <= node_pos && node_pos < qr) {
            res.push_back(pool[t].val);
        }
        dump_range_dfs(right, ql, qr, node_pos + 1, res, cur_reversed);
    }

    int clone_subtree_from(const DynamicArray& other, int t) {
        if (!t) return 0;
        int res = static_cast<int>(pool.size());
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

    void reset_to_empty() {
        pool.clear();
        pool.push_back(Node());
        root = 0;
    }

   public:
    DynamicArray() : root(0), rng(std::chrono::steady_clock::now().time_since_epoch().count()) {
        pool.push_back(Node());
    }

    DynamicArray(const DynamicArray& other) : pool(other.pool), root(other.root), rng(other.rng) {}

    DynamicArray(DynamicArray&& other) noexcept
        : pool(std::move(other.pool)), root(other.root), rng(std::move(other.rng)) {
        other.reset_to_empty();
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            pool = other.pool;
            root = other.root;
            rng = other.rng;
        }
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            pool = std::move(other.pool);
            root = other.root;
            rng = std::move(other.rng);
            other.reset_to_empty();
        }
        return *this;
    }

    explicit DynamicArray(const std::vector<T>& v) : DynamicArray() {
        pool.reserve(v.size() + 1);
        root = build_from_vector(v);
    }

    explicit DynamicArray(std::vector<T>&& v) : DynamicArray() {
        pool.reserve(v.size() + 1);
        root = build_from_vector(std::move(v));
    }

    DynamicArray(std::initializer_list<T> init) : DynamicArray() {
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

    void insert(int pos, T val) {
        assert(0 <= pos && pos <= size());
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, new_node(std::move(val))), r);
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

    void insert(int pos, const DynamicArray& other) {
        assert(0 <= pos && pos <= size());
        if (other.empty()) return;
        pool.reserve(pool.size() + other.size());
        int mid = clone_subtree_from(other, other.root);
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, mid), r);
    }

    void push_back(T val) {
        insert(size(), std::move(val));
    }

    void push_front(T val) {
        insert(0, std::move(val));
    }

    void append(const std::vector<T>& v) {
        insert(size(), v);
    }

    void append(std::vector<T>&& v) {
        insert(size(), std::move(v));
    }

    void append(const DynamicArray& other) {
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

    T& at(int pos) {
        assert(0 <= pos && pos < size());
        return pool[find_node(root, pos)].val;
    }

    const T& at(int pos) const {
        assert(0 <= pos && pos < size());
        return pool[find_node(root, pos, false)].val;
    }

    T& operator[](int pos) {
        return at(pos);
    }

    const T& operator[](int pos) const {
        return at(pos);
    }

    T& front() {
        assert(!empty());
        return at(0);
    }

    const T& front() const {
        assert(!empty());
        return at(0);
    }

    T& back() {
        assert(!empty());
        return at(size() - 1);
    }

    const T& back() const {
        assert(!empty());
        return at(size() - 1);
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

    T get(int pos) const {
        return at(pos);
    }

    void set(int pos, T val) {
        at(pos) = std::move(val);
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

    DynamicArray split_off(int pos) {
        assert(0 <= pos && pos <= size());
        int l, r;
        split(root, pos, l, r);
        root = l;

        DynamicArray res;
        res.pool.reserve(pool[r].count + 1);
        res.root = res.clone_subtree_from(*this, r);
        return res;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_DYNAMIC_ARRAY_HPP
