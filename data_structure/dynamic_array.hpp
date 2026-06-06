#ifndef M1UNE_DYNAMIC_ARRAY_HPP
#define M1UNE_DYNAMIC_ARRAY_HPP 1

#include <vector>
#include <random>
#include <chrono>
#include <cassert>
#include <initializer_list>
#include <utility> // for std::move

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
        
        Node() : val(T()), priority(0), count(0), l(0), r(0) {} 
        Node(T val, int priority) : val(std::move(val)), priority(priority), count(1), l(0), r(0) {}
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

    void split(int t, int pos, int& l, int& r) {
        if (!t) {
            l = r = 0;
            return;
        }
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

    void dump_dfs(int t, std::vector<T>& res) const {
        if (!t) return;
        dump_dfs(pool[t].l, res);
        res.push_back(pool[t].val);
        dump_dfs(pool[t].r, res);
    }

   public:
    // 1. Default Constructor
    DynamicArray() : root(0), rng(std::chrono::steady_clock::now().time_since_epoch().count()) {
        pool.push_back(Node());
    }

    // 2. Copy Constructor (const lvalue reference)
    DynamicArray(const DynamicArray& other) 
        : pool(other.pool), root(other.root), rng(other.rng) {}

    // 3. Move Constructor (rvalue reference)
    DynamicArray(DynamicArray&& other) noexcept 
        : pool(std::move(other.pool)), root(other.root), rng(std::move(other.rng)) {
        other.root = 0;
    }

    // 4. Copy Assignment Operator
    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            pool = other.pool;
            root = other.root;
            rng = other.rng;
        }
        return *this;
    }

    // 5. Move Assignment Operator
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this != &other) {
            pool = std::move(other.pool);
            root = other.root;
            rng = std::move(other.rng);
            other.root = 0;
        }
        return *this;
    }

    // 6. Constructor from const std::vector (Copies elements)
    explicit DynamicArray(const std::vector<T>& v) : DynamicArray() {
        pool.reserve(v.size() + 1);
        for (const T& x : v) push_back(x);
    }

    // 7. Constructor from std::vector&& (Moves elements)
    explicit DynamicArray(std::vector<T>&& v) : DynamicArray() {
        pool.reserve(v.size() + 1);
        for (T& x : v) push_back(std::move(x));
    }

    // 8. Constructor from initializer list
    DynamicArray(std::initializer_list<T> init) : DynamicArray() {
        pool.reserve(init.size() + 1);
        for (const T& x : init) push_back(x);
    }

    int size() const {
        return pool[root].count;
    }

    void insert(int pos, T val) {
        assert(0 <= pos && pos <= size());
        int l, r;
        split(root, pos, l, r);
        root = merge(merge(l, new_node(std::move(val))), r);
    }

    void push_back(T val) {
        insert(size(), std::move(val));
    }

    void erase(int pos) {
        assert(0 <= pos && pos < size());
        int l, mid, r;
        split(root, pos, l, mid);
        split(mid, 1, mid, r);
        root = merge(l, r);
    }

    T get(int pos) const {
        assert(0 <= pos && pos < size());
        int t = root;
        while (t) {
            int left_count = pool[pool[t].l].count;
            if (pos < left_count) {
                t = pool[t].l;
            } else if (pos == left_count) {
                return pool[t].val;
            } else {
                pos -= left_count + 1;
                t = pool[t].r;
            }
        }
        return T();
    }

    void set(int pos, T val) {
        assert(0 <= pos && pos < size());
        int t = root;
        while (t) {
            int left_count = pool[pool[t].l].count;
            if (pos < left_count) {
                t = pool[t].l;
            } else if (pos == left_count) {
                pool[t].val = std::move(val);
                return;
            } else {
                pos -= left_count + 1;
                t = pool[t].r;
            }
        }
    }

    std::vector<T> to_vector() const {
        std::vector<T> res;
        res.reserve(size());
        dump_dfs(root, res);
        return res;
    }
};

}  // namespace data_structure
}  // namespace m1une

#endif  // M1UNE_DYNAMIC_ARRAY_HPP
