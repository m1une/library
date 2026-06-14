---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/dynamic_monoid_array.test.cpp
    title: verify/data_structure/dynamic_monoid_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/dynamic_monoid_array.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n#include\
    \ <initializer_list>\n#include <utility>\n#include <vector>\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#line 5 \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace monoid\
    \ {\n\n// Concept to check if a type satisfies the requirements of a Monoid.\n\
    // A Monoid must have a `value_type`, an identity element `id()`, and an associative\
    \ binary operation `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename\
    \ M::value_type a, typename M::value_type b) {\n    // 1. Must define `value_type`\n\
    \    typename M::value_type;\n\n    // 2. Must have a static method `id()` returning\
    \ `value_type`\n    { M::id() } -> std::same_as<typename M::value_type>;\n\n \
    \   // 3. Must have a static method `op(a, b)` returning `value_type`\n    { M::op(a,\
    \ b) } -> std::same_as<typename M::value_type>;\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 13 \"data_structure/dynamic_monoid_array.hpp\"\
    \n\nnamespace m1une {\nnamespace data_structure {\n\ntemplate <m1une::monoid::IsMonoid\
    \ Monoid>\nstruct DynamicMonoidArray {\n    using T = typename Monoid::value_type;\n\
    \n   private:\n    struct Node {\n        T val;\n        T prod;\n        T rprod;\n\
    \        int priority;\n        int count;\n        int l, r;\n        bool rev;\n\
    \n        Node()\n            : val(Monoid::id()),\n              prod(Monoid::id()),\n\
    \              rprod(Monoid::id()),\n              priority(0),\n            \
    \  count(0),\n              l(0),\n              r(0),\n              rev(false)\
    \ {}\n\n        Node(T value, int node_priority)\n            : val(std::move(value)),\
    \ prod(val), rprod(val), priority(node_priority), count(1), l(0), r(0), rev(false)\
    \ {}\n    };\n\n    std::vector<Node> pool;\n    int root;\n    std::uint32_t\
    \ rng_state;\n\n    template <typename U>\n    static T make_value(const U& value)\
    \ {\n        if constexpr (requires(U x) { Monoid::make(x); }) {\n           \
    \ return Monoid::make(value);\n        } else {\n            return static_cast<T>(value);\n\
    \        }\n    }\n\n    int new_node(T value) {\n        pool.push_back(Node(std::move(value),\
    \ next_priority()));\n        return int(pool.size()) - 1;\n    }\n\n    int next_priority()\
    \ {\n        rng_state ^= rng_state << 13;\n        rng_state ^= rng_state >>\
    \ 17;\n        rng_state ^= rng_state << 5;\n        return int(rng_state);\n\
    \    }\n\n    void update(int t) {\n        if (!t) return;\n        int l = pool[t].l;\n\
    \        int r = pool[t].r;\n        pool[t].count = 1 + pool[l].count + pool[r].count;\n\
    \        pool[t].prod = Monoid::op(Monoid::op(pool[l].prod, pool[t].val), pool[r].prod);\n\
    \        pool[t].rprod = Monoid::op(Monoid::op(pool[r].rprod, pool[t].val), pool[l].rprod);\n\
    \    }\n\n    void apply_reverse(int t) {\n        if (!t) return;\n        pool[t].rev\
    \ = !pool[t].rev;\n        std::swap(pool[t].prod, pool[t].rprod);\n    }\n\n\
    \    void push(int t) {\n        if (!t || !pool[t].rev) return;\n        std::swap(pool[t].l,\
    \ pool[t].r);\n        apply_reverse(pool[t].l);\n        apply_reverse(pool[t].r);\n\
    \        pool[t].rev = false;\n    }\n\n    void split(int t, int pos, int& l,\
    \ int& r) {\n        if (!t) {\n            l = r = 0;\n            return;\n\
    \        }\n        if (pos == 0) {\n            l = 0;\n            r = t;\n\
    \            return;\n        }\n        if (pos == pool[t].count) {\n       \
    \     l = t;\n            r = 0;\n            return;\n        }\n        push(t);\n\
    \        int left_count = pool[pool[t].l].count;\n        if (pos == left_count)\
    \ {\n            l = pool[t].l;\n            pool[t].l = 0;\n            update(t);\n\
    \            r = t;\n            return;\n        }\n        if (pos == left_count\
    \ + 1) {\n            r = pool[t].r;\n            pool[t].r = 0;\n           \
    \ update(t);\n            l = t;\n            return;\n        }\n        if (pos\
    \ <= left_count) {\n            split(pool[t].l, pos, l, pool[t].l);\n       \
    \     r = t;\n        } else {\n            split(pool[t].r, pos - left_count\
    \ - 1, pool[t].r, r);\n            l = t;\n        }\n        update(t);\n   \
    \ }\n\n    int merge(int l, int r) {\n        if (!l || !r) return l ? l : r;\n\
    \        if (pool[l].priority > pool[r].priority) {\n            push(l);\n  \
    \          if (pool[l].r) {\n                pool[l].r = merge(pool[l].r, r);\n\
    \            } else {\n                pool[l].r = r;\n            }\n       \
    \     update(l);\n            return l;\n        } else {\n            push(r);\n\
    \            if (pool[r].l) {\n                pool[r].l = merge(l, pool[r].l);\n\
    \            } else {\n                pool[r].l = l;\n            }\n       \
    \     update(r);\n            return r;\n        }\n    }\n\n    int insert_node(int\
    \ t, int pos, int node) {\n        if (!t) return node;\n        if (pool[node].priority\
    \ > pool[t].priority) {\n            split(t, pos, pool[node].l, pool[node].r);\n\
    \            update(node);\n            return node;\n        }\n        push(t);\n\
    \        int left_count = pool[pool[t].l].count;\n        if (pos <= left_count)\
    \ {\n            pool[t].l = insert_node(pool[t].l, pos, node);\n        } else\
    \ {\n            pool[t].r = insert_node(pool[t].r, pos - left_count - 1, node);\n\
    \        }\n        update(t);\n        return t;\n    }\n\n    int erase_node(int\
    \ t, int pos) {\n        push(t);\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos < left_count) {\n            pool[t].l = erase_node(pool[t].l,\
    \ pos);\n            update(t);\n            return t;\n        }\n        if\
    \ (pos == left_count) {\n            return merge(pool[t].l, pool[t].r);\n   \
    \     }\n        pool[t].r = erase_node(pool[t].r, pos - left_count - 1);\n  \
    \      update(t);\n        return t;\n    }\n\n    void set_node(int t, int pos,\
    \ T value) {\n        push(t);\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos < left_count) {\n            set_node(pool[t].l, pos, std::move(value));\n\
    \        } else if (pos == left_count) {\n            pool[t].val = std::move(value);\n\
    \        } else {\n            set_node(pool[t].r, pos - left_count - 1, std::move(value));\n\
    \        }\n        update(t);\n    }\n\n    int find_node(int t, int pos) {\n\
    \        while (t) {\n            push(t);\n            int left_count = pool[pool[t].l].count;\n\
    \            if (pos < left_count) {\n                t = pool[t].l;\n       \
    \     } else if (pos == left_count) {\n                return t;\n           \
    \ } else {\n                pos -= left_count + 1;\n                t = pool[t].r;\n\
    \            }\n        }\n        return 0;\n    }\n\n    int find_node(int t,\
    \ int pos, bool reversed) const {\n        while (t) {\n            bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n            int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \            int r = cur_reversed ? pool[t].l : pool[t].r;\n            int left_count\
    \ = pool[l].count;\n            if (pos < left_count) {\n                t = l;\n\
    \                reversed = cur_reversed;\n            } else if (pos == left_count)\
    \ {\n                return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = r;\n                reversed = cur_reversed;\n   \
    \         }\n        }\n        return 0;\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (!t) return;\n        bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n        int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \        int r = cur_reversed ? pool[t].l : pool[t].r;\n        dump_dfs(l, res,\
    \ cur_reversed);\n        res.push_back(pool[t].val);\n        dump_dfs(r, res,\
    \ cur_reversed);\n    }\n\n    void dump_range_dfs(int t, int ql, int qr, int\
    \ offset, std::vector<T>& res, bool reversed = false) const {\n        if (!t\
    \ || qr <= offset || offset + pool[t].count <= ql) return;\n        bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n        int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \        int r = cur_reversed ? pool[t].l : pool[t].r;\n        int left_count\
    \ = pool[l].count;\n        int node_pos = offset + left_count;\n        dump_range_dfs(l,\
    \ ql, qr, offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos\
    \ < qr) {\n            res.push_back(pool[t].val);\n        }\n        dump_range_dfs(r,\
    \ ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n    int clone_subtree_from(const\
    \ DynamicMonoidArray& other, int t) {\n        if (!t) return 0;\n        int\
    \ res = int(pool.size());\n        pool.push_back(other.pool[t]);\n        pool[res].l\
    \ = clone_subtree_from(other, other.pool[t].l);\n        pool[res].r = clone_subtree_from(other,\
    \ other.pool[t].r);\n        return res;\n    }\n\n    void update_dfs(int t)\
    \ {\n        if (!t) return;\n        update_dfs(pool[t].l);\n        update_dfs(pool[t].r);\n\
    \        update(t);\n    }\n\n    int build_cartesian(int first, int last) {\n\
    \        if (first == last) return 0;\n        std::vector<int> stack;\n     \
    \   stack.reserve(last - first);\n        for (int i = first; i < last; i++) {\n\
    \            int left_child = 0;\n            while (!stack.empty() && pool[stack.back()].priority\
    \ < pool[i].priority) {\n                left_child = stack.back();\n        \
    \        stack.pop_back();\n            }\n            pool[i].l = left_child;\n\
    \            if (!stack.empty()) {\n                pool[stack.back()].r = i;\n\
    \            }\n            stack.push_back(i);\n        }\n        int res =\
    \ stack.front();\n        update_dfs(res);\n        return res;\n    }\n\n   \
    \ int build_from_vector(const std::vector<T>& v) {\n        int first = int(pool.size());\n\
    \        pool.reserve(pool.size() + v.size());\n        for (const T& x : v) {\n\
    \            new_node(x);\n        }\n        return build_cartesian(first, int(pool.size()));\n\
    \    }\n\n    int build_from_vector(std::vector<T>&& v) {\n        int first =\
    \ int(pool.size());\n        pool.reserve(pool.size() + v.size());\n        for\
    \ (T& x : v) {\n            new_node(std::move(x));\n        }\n        return\
    \ build_cartesian(first, int(pool.size()));\n    }\n\n    template <typename U>\n\
    \    int build_from_values(const std::vector<U>& v) {\n        int first = int(pool.size());\n\
    \        pool.reserve(pool.size() + v.size());\n        for (const U& x : v) {\n\
    \            new_node(make_value(x));\n        }\n        return build_cartesian(first,\
    \ int(pool.size()));\n    }\n\n    void reset_to_empty() {\n        pool.clear();\n\
    \        pool.push_back(Node());\n        root = 0;\n    }\n\n   public:\n   \
    \ DynamicMonoidArray()\n        : root(0), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        pool.push_back(Node());\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    DynamicMonoidArray(const DynamicMonoidArray& other)\n     \
    \   : pool(other.pool), root(other.root), rng_state(other.rng_state) {}\n\n  \
    \  DynamicMonoidArray(DynamicMonoidArray&& other) noexcept\n        : pool(std::move(other.pool)),\
    \ root(other.root), rng_state(other.rng_state) {\n        other.reset_to_empty();\n\
    \    }\n\n    DynamicMonoidArray& operator=(const DynamicMonoidArray& other) {\n\
    \        if (this != &other) {\n            pool = other.pool;\n            root\
    \ = other.root;\n            rng_state = other.rng_state;\n        }\n       \
    \ return *this;\n    }\n\n    DynamicMonoidArray& operator=(DynamicMonoidArray&&\
    \ other) noexcept {\n        if (this != &other) {\n            pool = std::move(other.pool);\n\
    \            root = other.root;\n            rng_state = other.rng_state;\n  \
    \          other.reset_to_empty();\n        }\n        return *this;\n    }\n\n\
    \    explicit DynamicMonoidArray(int n) : DynamicMonoidArray(n, Monoid::id())\
    \ {}\n\n    DynamicMonoidArray(int n, const T& value) : DynamicMonoidArray() {\n\
    \        assert(0 <= n);\n        pool.reserve(n + 1);\n        int first = int(pool.size());\n\
    \        for (int i = 0; i < n; i++) {\n            new_node(value);\n       \
    \ }\n        root = build_cartesian(first, int(pool.size()));\n    }\n\n    explicit\
    \ DynamicMonoidArray(const std::vector<T>& v) : DynamicMonoidArray() {\n     \
    \   pool.reserve(v.size() + 1);\n        root = build_from_vector(v);\n    }\n\
    \n    explicit DynamicMonoidArray(std::vector<T>&& v) : DynamicMonoidArray() {\n\
    \        pool.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\
    \ (requires(U x) { Monoid::make(x); } || std::convertible_to<U, T>)\n    explicit\
    \ DynamicMonoidArray(const std::vector<U>& v) : DynamicMonoidArray() {\n     \
    \   pool.reserve(v.size() + 1);\n        root = build_from_values(v);\n    }\n\
    \n    DynamicMonoidArray(std::initializer_list<T> init) : DynamicMonoidArray()\
    \ {\n        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return pool[root].count;\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void clear()\
    \ {\n        reset_to_empty();\n    }\n\n    void insert(int pos, T value) {\n\
    \        assert(0 <= pos && pos <= size());\n        root = insert_node(root,\
    \ pos, new_node(std::move(value)));\n    }\n\n    void insert(int pos, const std::vector<T>&\
    \ v) {\n        assert(0 <= pos && pos <= size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        int mid = build_from_vector(v);\n        int l, r;\n \
    \       split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n   \
    \ }\n\n    void insert(int pos, std::vector<T>&& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        pool.reserve(pool.size() + v.size());\n        int\
    \ mid = build_from_vector(std::move(v));\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const DynamicMonoidArray& other) {\n      \
    \  assert(0 <= pos && pos <= size());\n        if (other.empty()) return;\n  \
    \      pool.reserve(pool.size() + other.size());\n        int mid = clone_subtree_from(other,\
    \ other.root);\n        int l, r;\n        split(root, pos, l, r);\n        root\
    \ = merge(merge(l, mid), r);\n    }\n\n    void push_back(T value) {\n       \
    \ insert(size(), std::move(value));\n    }\n\n    void push_front(T value) {\n\
    \        insert(0, std::move(value));\n    }\n\n    void append(const std::vector<T>&\
    \ v) {\n        insert(size(), v);\n    }\n\n    void append(std::vector<T>&&\
    \ v) {\n        insert(size(), std::move(v));\n    }\n\n    void append(const\
    \ DynamicMonoidArray& other) {\n        insert(size(), other);\n    }\n\n    void\
    \ erase(int pos) {\n        assert(0 <= pos && pos < size());\n        root =\
    \ erase_node(root, pos);\n    }\n\n    void erase(int l, int r) {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return;\n        int a,\
    \ b, c;\n        split(root, l, a, b);\n        split(b, r - l, b, c);\n     \
    \   root = merge(a, c);\n    }\n\n    void pop_back() {\n        assert(!empty());\n\
    \        erase(size() - 1);\n    }\n\n    void pop_front() {\n        assert(!empty());\n\
    \        erase(0);\n    }\n\n    T get(int pos) const {\n        assert(0 <= pos\
    \ && pos < size());\n        return pool[find_node(root, pos, false)].val;\n \
    \   }\n\n    T operator[](int pos) const {\n        return get(pos);\n    }\n\n\
    \    T front() const {\n        assert(!empty());\n        return get(0);\n  \
    \  }\n\n    T back() const {\n        assert(!empty());\n        return get(size()\
    \ - 1);\n    }\n\n    void set(int pos, T value) {\n        assert(0 <= pos &&\
    \ pos < size());\n        set_node(root, pos, std::move(value));\n    }\n\n  \
    \  void reverse(int l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return;\n        int a, b, c;\n        split(root, l, a,\
    \ b);\n        split(b, r - l, b, c);\n        apply_reverse(b);\n        root\
    \ = merge(merge(a, b), c);\n    }\n\n    void reverse() {\n        apply_reverse(root);\n\
    \    }\n\n    void rotate(int l, int m, int r) {\n        assert(0 <= l && l <=\
    \ m && m <= r && r <= size());\n        if (l == m || m == r) return;\n      \
    \  int a, b, c, d;\n        split(root, l, a, b);\n        split(b, m - l, b,\
    \ c);\n        split(c, r - m, c, d);\n        root = merge(merge(a, c), merge(b,\
    \ d));\n    }\n\n    T prod(int l, int r) {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return Monoid::id();\n        int a, b, c;\n\
    \        split(root, l, a, b);\n        split(b, r - l, b, c);\n        T res\
    \ = pool[b].prod;\n        root = merge(merge(a, b), c);\n        return res;\n\
    \    }\n\n    T all_prod() const {\n        return pool[root].prod;\n    }\n\n\
    \    std::vector<T> to_vector() const {\n        std::vector<T> res;\n       \
    \ res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n  \
    \  }\n\n    std::vector<T> to_vector(int l, int r) const {\n        assert(0 <=\
    \ l && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    DynamicMonoidArray split_off(int pos) {\n        assert(0 <= pos &&\
    \ pos <= size());\n        int l, r;\n        split(root, pos, l, r);\n      \
    \  root = l;\n\n        DynamicMonoidArray res;\n        res.pool.reserve(pool[r].count\
    \ + 1);\n        res.root = res.clone_subtree_from(*this, r);\n        return\
    \ res;\n    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_DYNAMIC_MONOID_ARRAY_HPP\n#define M1UNE_DYNAMIC_MONOID_ARRAY_HPP\
    \ 1\n\n#include <cassert>\n#include <chrono>\n#include <concepts>\n#include <cstdint>\n\
    #include <initializer_list>\n#include <utility>\n#include <vector>\n\n#include\
    \ \"monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace data_structure {\n\n\
    template <m1une::monoid::IsMonoid Monoid>\nstruct DynamicMonoidArray {\n    using\
    \ T = typename Monoid::value_type;\n\n   private:\n    struct Node {\n       \
    \ T val;\n        T prod;\n        T rprod;\n        int priority;\n        int\
    \ count;\n        int l, r;\n        bool rev;\n\n        Node()\n           \
    \ : val(Monoid::id()),\n              prod(Monoid::id()),\n              rprod(Monoid::id()),\n\
    \              priority(0),\n              count(0),\n              l(0),\n  \
    \            r(0),\n              rev(false) {}\n\n        Node(T value, int node_priority)\n\
    \            : val(std::move(value)), prod(val), rprod(val), priority(node_priority),\
    \ count(1), l(0), r(0), rev(false) {}\n    };\n\n    std::vector<Node> pool;\n\
    \    int root;\n    std::uint32_t rng_state;\n\n    template <typename U>\n  \
    \  static T make_value(const U& value) {\n        if constexpr (requires(U x)\
    \ { Monoid::make(x); }) {\n            return Monoid::make(value);\n        }\
    \ else {\n            return static_cast<T>(value);\n        }\n    }\n\n    int\
    \ new_node(T value) {\n        pool.push_back(Node(std::move(value), next_priority()));\n\
    \        return int(pool.size()) - 1;\n    }\n\n    int next_priority() {\n  \
    \      rng_state ^= rng_state << 13;\n        rng_state ^= rng_state >> 17;\n\
    \        rng_state ^= rng_state << 5;\n        return int(rng_state);\n    }\n\
    \n    void update(int t) {\n        if (!t) return;\n        int l = pool[t].l;\n\
    \        int r = pool[t].r;\n        pool[t].count = 1 + pool[l].count + pool[r].count;\n\
    \        pool[t].prod = Monoid::op(Monoid::op(pool[l].prod, pool[t].val), pool[r].prod);\n\
    \        pool[t].rprod = Monoid::op(Monoid::op(pool[r].rprod, pool[t].val), pool[l].rprod);\n\
    \    }\n\n    void apply_reverse(int t) {\n        if (!t) return;\n        pool[t].rev\
    \ = !pool[t].rev;\n        std::swap(pool[t].prod, pool[t].rprod);\n    }\n\n\
    \    void push(int t) {\n        if (!t || !pool[t].rev) return;\n        std::swap(pool[t].l,\
    \ pool[t].r);\n        apply_reverse(pool[t].l);\n        apply_reverse(pool[t].r);\n\
    \        pool[t].rev = false;\n    }\n\n    void split(int t, int pos, int& l,\
    \ int& r) {\n        if (!t) {\n            l = r = 0;\n            return;\n\
    \        }\n        if (pos == 0) {\n            l = 0;\n            r = t;\n\
    \            return;\n        }\n        if (pos == pool[t].count) {\n       \
    \     l = t;\n            r = 0;\n            return;\n        }\n        push(t);\n\
    \        int left_count = pool[pool[t].l].count;\n        if (pos == left_count)\
    \ {\n            l = pool[t].l;\n            pool[t].l = 0;\n            update(t);\n\
    \            r = t;\n            return;\n        }\n        if (pos == left_count\
    \ + 1) {\n            r = pool[t].r;\n            pool[t].r = 0;\n           \
    \ update(t);\n            l = t;\n            return;\n        }\n        if (pos\
    \ <= left_count) {\n            split(pool[t].l, pos, l, pool[t].l);\n       \
    \     r = t;\n        } else {\n            split(pool[t].r, pos - left_count\
    \ - 1, pool[t].r, r);\n            l = t;\n        }\n        update(t);\n   \
    \ }\n\n    int merge(int l, int r) {\n        if (!l || !r) return l ? l : r;\n\
    \        if (pool[l].priority > pool[r].priority) {\n            push(l);\n  \
    \          if (pool[l].r) {\n                pool[l].r = merge(pool[l].r, r);\n\
    \            } else {\n                pool[l].r = r;\n            }\n       \
    \     update(l);\n            return l;\n        } else {\n            push(r);\n\
    \            if (pool[r].l) {\n                pool[r].l = merge(l, pool[r].l);\n\
    \            } else {\n                pool[r].l = l;\n            }\n       \
    \     update(r);\n            return r;\n        }\n    }\n\n    int insert_node(int\
    \ t, int pos, int node) {\n        if (!t) return node;\n        if (pool[node].priority\
    \ > pool[t].priority) {\n            split(t, pos, pool[node].l, pool[node].r);\n\
    \            update(node);\n            return node;\n        }\n        push(t);\n\
    \        int left_count = pool[pool[t].l].count;\n        if (pos <= left_count)\
    \ {\n            pool[t].l = insert_node(pool[t].l, pos, node);\n        } else\
    \ {\n            pool[t].r = insert_node(pool[t].r, pos - left_count - 1, node);\n\
    \        }\n        update(t);\n        return t;\n    }\n\n    int erase_node(int\
    \ t, int pos) {\n        push(t);\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos < left_count) {\n            pool[t].l = erase_node(pool[t].l,\
    \ pos);\n            update(t);\n            return t;\n        }\n        if\
    \ (pos == left_count) {\n            return merge(pool[t].l, pool[t].r);\n   \
    \     }\n        pool[t].r = erase_node(pool[t].r, pos - left_count - 1);\n  \
    \      update(t);\n        return t;\n    }\n\n    void set_node(int t, int pos,\
    \ T value) {\n        push(t);\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos < left_count) {\n            set_node(pool[t].l, pos, std::move(value));\n\
    \        } else if (pos == left_count) {\n            pool[t].val = std::move(value);\n\
    \        } else {\n            set_node(pool[t].r, pos - left_count - 1, std::move(value));\n\
    \        }\n        update(t);\n    }\n\n    int find_node(int t, int pos) {\n\
    \        while (t) {\n            push(t);\n            int left_count = pool[pool[t].l].count;\n\
    \            if (pos < left_count) {\n                t = pool[t].l;\n       \
    \     } else if (pos == left_count) {\n                return t;\n           \
    \ } else {\n                pos -= left_count + 1;\n                t = pool[t].r;\n\
    \            }\n        }\n        return 0;\n    }\n\n    int find_node(int t,\
    \ int pos, bool reversed) const {\n        while (t) {\n            bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n            int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \            int r = cur_reversed ? pool[t].l : pool[t].r;\n            int left_count\
    \ = pool[l].count;\n            if (pos < left_count) {\n                t = l;\n\
    \                reversed = cur_reversed;\n            } else if (pos == left_count)\
    \ {\n                return t;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = r;\n                reversed = cur_reversed;\n   \
    \         }\n        }\n        return 0;\n    }\n\n    void dump_dfs(int t, std::vector<T>&\
    \ res, bool reversed = false) const {\n        if (!t) return;\n        bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n        int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \        int r = cur_reversed ? pool[t].l : pool[t].r;\n        dump_dfs(l, res,\
    \ cur_reversed);\n        res.push_back(pool[t].val);\n        dump_dfs(r, res,\
    \ cur_reversed);\n    }\n\n    void dump_range_dfs(int t, int ql, int qr, int\
    \ offset, std::vector<T>& res, bool reversed = false) const {\n        if (!t\
    \ || qr <= offset || offset + pool[t].count <= ql) return;\n        bool cur_reversed\
    \ = reversed ^ pool[t].rev;\n        int l = cur_reversed ? pool[t].r : pool[t].l;\n\
    \        int r = cur_reversed ? pool[t].l : pool[t].r;\n        int left_count\
    \ = pool[l].count;\n        int node_pos = offset + left_count;\n        dump_range_dfs(l,\
    \ ql, qr, offset, res, cur_reversed);\n        if (ql <= node_pos && node_pos\
    \ < qr) {\n            res.push_back(pool[t].val);\n        }\n        dump_range_dfs(r,\
    \ ql, qr, node_pos + 1, res, cur_reversed);\n    }\n\n    int clone_subtree_from(const\
    \ DynamicMonoidArray& other, int t) {\n        if (!t) return 0;\n        int\
    \ res = int(pool.size());\n        pool.push_back(other.pool[t]);\n        pool[res].l\
    \ = clone_subtree_from(other, other.pool[t].l);\n        pool[res].r = clone_subtree_from(other,\
    \ other.pool[t].r);\n        return res;\n    }\n\n    void update_dfs(int t)\
    \ {\n        if (!t) return;\n        update_dfs(pool[t].l);\n        update_dfs(pool[t].r);\n\
    \        update(t);\n    }\n\n    int build_cartesian(int first, int last) {\n\
    \        if (first == last) return 0;\n        std::vector<int> stack;\n     \
    \   stack.reserve(last - first);\n        for (int i = first; i < last; i++) {\n\
    \            int left_child = 0;\n            while (!stack.empty() && pool[stack.back()].priority\
    \ < pool[i].priority) {\n                left_child = stack.back();\n        \
    \        stack.pop_back();\n            }\n            pool[i].l = left_child;\n\
    \            if (!stack.empty()) {\n                pool[stack.back()].r = i;\n\
    \            }\n            stack.push_back(i);\n        }\n        int res =\
    \ stack.front();\n        update_dfs(res);\n        return res;\n    }\n\n   \
    \ int build_from_vector(const std::vector<T>& v) {\n        int first = int(pool.size());\n\
    \        pool.reserve(pool.size() + v.size());\n        for (const T& x : v) {\n\
    \            new_node(x);\n        }\n        return build_cartesian(first, int(pool.size()));\n\
    \    }\n\n    int build_from_vector(std::vector<T>&& v) {\n        int first =\
    \ int(pool.size());\n        pool.reserve(pool.size() + v.size());\n        for\
    \ (T& x : v) {\n            new_node(std::move(x));\n        }\n        return\
    \ build_cartesian(first, int(pool.size()));\n    }\n\n    template <typename U>\n\
    \    int build_from_values(const std::vector<U>& v) {\n        int first = int(pool.size());\n\
    \        pool.reserve(pool.size() + v.size());\n        for (const U& x : v) {\n\
    \            new_node(make_value(x));\n        }\n        return build_cartesian(first,\
    \ int(pool.size()));\n    }\n\n    void reset_to_empty() {\n        pool.clear();\n\
    \        pool.push_back(Node());\n        root = 0;\n    }\n\n   public:\n   \
    \ DynamicMonoidArray()\n        : root(0), rng_state(std::uint32_t(std::chrono::steady_clock::now().time_since_epoch().count()))\
    \ {\n        pool.push_back(Node());\n        if (rng_state == 0) rng_state =\
    \ 1;\n    }\n\n    DynamicMonoidArray(const DynamicMonoidArray& other)\n     \
    \   : pool(other.pool), root(other.root), rng_state(other.rng_state) {}\n\n  \
    \  DynamicMonoidArray(DynamicMonoidArray&& other) noexcept\n        : pool(std::move(other.pool)),\
    \ root(other.root), rng_state(other.rng_state) {\n        other.reset_to_empty();\n\
    \    }\n\n    DynamicMonoidArray& operator=(const DynamicMonoidArray& other) {\n\
    \        if (this != &other) {\n            pool = other.pool;\n            root\
    \ = other.root;\n            rng_state = other.rng_state;\n        }\n       \
    \ return *this;\n    }\n\n    DynamicMonoidArray& operator=(DynamicMonoidArray&&\
    \ other) noexcept {\n        if (this != &other) {\n            pool = std::move(other.pool);\n\
    \            root = other.root;\n            rng_state = other.rng_state;\n  \
    \          other.reset_to_empty();\n        }\n        return *this;\n    }\n\n\
    \    explicit DynamicMonoidArray(int n) : DynamicMonoidArray(n, Monoid::id())\
    \ {}\n\n    DynamicMonoidArray(int n, const T& value) : DynamicMonoidArray() {\n\
    \        assert(0 <= n);\n        pool.reserve(n + 1);\n        int first = int(pool.size());\n\
    \        for (int i = 0; i < n; i++) {\n            new_node(value);\n       \
    \ }\n        root = build_cartesian(first, int(pool.size()));\n    }\n\n    explicit\
    \ DynamicMonoidArray(const std::vector<T>& v) : DynamicMonoidArray() {\n     \
    \   pool.reserve(v.size() + 1);\n        root = build_from_vector(v);\n    }\n\
    \n    explicit DynamicMonoidArray(std::vector<T>&& v) : DynamicMonoidArray() {\n\
    \        pool.reserve(v.size() + 1);\n        root = build_from_vector(std::move(v));\n\
    \    }\n\n    template <typename U>\n        requires(!std::same_as<U, T>) &&\
    \ (requires(U x) { Monoid::make(x); } || std::convertible_to<U, T>)\n    explicit\
    \ DynamicMonoidArray(const std::vector<U>& v) : DynamicMonoidArray() {\n     \
    \   pool.reserve(v.size() + 1);\n        root = build_from_values(v);\n    }\n\
    \n    DynamicMonoidArray(std::initializer_list<T> init) : DynamicMonoidArray()\
    \ {\n        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return pool[root].count;\n    }\n\n\
    \    bool empty() const {\n        return size() == 0;\n    }\n\n    void clear()\
    \ {\n        reset_to_empty();\n    }\n\n    void insert(int pos, T value) {\n\
    \        assert(0 <= pos && pos <= size());\n        root = insert_node(root,\
    \ pos, new_node(std::move(value)));\n    }\n\n    void insert(int pos, const std::vector<T>&\
    \ v) {\n        assert(0 <= pos && pos <= size());\n        pool.reserve(pool.size()\
    \ + v.size());\n        int mid = build_from_vector(v);\n        int l, r;\n \
    \       split(root, pos, l, r);\n        root = merge(merge(l, mid), r);\n   \
    \ }\n\n    void insert(int pos, std::vector<T>&& v) {\n        assert(0 <= pos\
    \ && pos <= size());\n        pool.reserve(pool.size() + v.size());\n        int\
    \ mid = build_from_vector(std::move(v));\n        int l, r;\n        split(root,\
    \ pos, l, r);\n        root = merge(merge(l, mid), r);\n    }\n\n    void insert(int\
    \ pos, std::initializer_list<T> init) {\n        insert(pos, std::vector<T>(init));\n\
    \    }\n\n    void insert(int pos, const DynamicMonoidArray& other) {\n      \
    \  assert(0 <= pos && pos <= size());\n        if (other.empty()) return;\n  \
    \      pool.reserve(pool.size() + other.size());\n        int mid = clone_subtree_from(other,\
    \ other.root);\n        int l, r;\n        split(root, pos, l, r);\n        root\
    \ = merge(merge(l, mid), r);\n    }\n\n    void push_back(T value) {\n       \
    \ insert(size(), std::move(value));\n    }\n\n    void push_front(T value) {\n\
    \        insert(0, std::move(value));\n    }\n\n    void append(const std::vector<T>&\
    \ v) {\n        insert(size(), v);\n    }\n\n    void append(std::vector<T>&&\
    \ v) {\n        insert(size(), std::move(v));\n    }\n\n    void append(const\
    \ DynamicMonoidArray& other) {\n        insert(size(), other);\n    }\n\n    void\
    \ erase(int pos) {\n        assert(0 <= pos && pos < size());\n        root =\
    \ erase_node(root, pos);\n    }\n\n    void erase(int l, int r) {\n        assert(0\
    \ <= l && l <= r && r <= size());\n        if (l == r) return;\n        int a,\
    \ b, c;\n        split(root, l, a, b);\n        split(b, r - l, b, c);\n     \
    \   root = merge(a, c);\n    }\n\n    void pop_back() {\n        assert(!empty());\n\
    \        erase(size() - 1);\n    }\n\n    void pop_front() {\n        assert(!empty());\n\
    \        erase(0);\n    }\n\n    T get(int pos) const {\n        assert(0 <= pos\
    \ && pos < size());\n        return pool[find_node(root, pos, false)].val;\n \
    \   }\n\n    T operator[](int pos) const {\n        return get(pos);\n    }\n\n\
    \    T front() const {\n        assert(!empty());\n        return get(0);\n  \
    \  }\n\n    T back() const {\n        assert(!empty());\n        return get(size()\
    \ - 1);\n    }\n\n    void set(int pos, T value) {\n        assert(0 <= pos &&\
    \ pos < size());\n        set_node(root, pos, std::move(value));\n    }\n\n  \
    \  void reverse(int l, int r) {\n        assert(0 <= l && l <= r && r <= size());\n\
    \        if (l == r) return;\n        int a, b, c;\n        split(root, l, a,\
    \ b);\n        split(b, r - l, b, c);\n        apply_reverse(b);\n        root\
    \ = merge(merge(a, b), c);\n    }\n\n    void reverse() {\n        apply_reverse(root);\n\
    \    }\n\n    void rotate(int l, int m, int r) {\n        assert(0 <= l && l <=\
    \ m && m <= r && r <= size());\n        if (l == m || m == r) return;\n      \
    \  int a, b, c, d;\n        split(root, l, a, b);\n        split(b, m - l, b,\
    \ c);\n        split(c, r - m, c, d);\n        root = merge(merge(a, c), merge(b,\
    \ d));\n    }\n\n    T prod(int l, int r) {\n        assert(0 <= l && l <= r &&\
    \ r <= size());\n        if (l == r) return Monoid::id();\n        int a, b, c;\n\
    \        split(root, l, a, b);\n        split(b, r - l, b, c);\n        T res\
    \ = pool[b].prod;\n        root = merge(merge(a, b), c);\n        return res;\n\
    \    }\n\n    T all_prod() const {\n        return pool[root].prod;\n    }\n\n\
    \    std::vector<T> to_vector() const {\n        std::vector<T> res;\n       \
    \ res.reserve(size());\n        dump_dfs(root, res);\n        return res;\n  \
    \  }\n\n    std::vector<T> to_vector(int l, int r) const {\n        assert(0 <=\
    \ l && l <= r && r <= size());\n        std::vector<T> res;\n        res.reserve(r\
    \ - l);\n        dump_range_dfs(root, l, r, 0, res);\n        return res;\n  \
    \  }\n\n    DynamicMonoidArray split_off(int pos) {\n        assert(0 <= pos &&\
    \ pos <= size());\n        int l, r;\n        split(root, pos, l, r);\n      \
    \  root = l;\n\n        DynamicMonoidArray res;\n        res.pool.reserve(pool[r].count\
    \ + 1);\n        res.root = res.clone_subtree_from(*this, r);\n        return\
    \ res;\n    }\n};\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\
    #endif  // M1UNE_DYNAMIC_MONOID_ARRAY_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: data_structure/dynamic_monoid_array.hpp
  requiredBy: []
  timestamp: '2026-06-14 04:44:05+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/dynamic_monoid_array.test.cpp
documentation_of: data_structure/dynamic_monoid_array.hpp
layout: document
title: Dynamic Monoid Array
---

## Overview

`DynamicMonoidArray` is an implicit treap for dynamic sequences with range product queries. It supports indexed insertion, deletion, reversal, rotation, splitting, concatenation, and monoid products over half-open ranges.

Each node stores both forward and reversed products, so `reverse(l, r)` works correctly even when the monoid operation is not commutative.

## Complexity Notation

In this document:

* `N` is the current number of elements in the sequence.
* `M` is the number of elements inserted or appended from another container.
* `K` is the number of elements returned or moved into a newly returned sequence.

## Template Parameters

* `Monoid`: A monoid satisfying `m1une::monoid::IsMonoid`.

## Constructors

* `DynamicMonoidArray()`
  Constructs an empty sequence. ($O(1)$)

* `DynamicMonoidArray(int n)`
  Constructs a sequence with `n` copies of `Monoid::id()`. ($O(N)$)

* `DynamicMonoidArray(int n, const T& value)`
  Constructs a sequence with `n` copies of `value`, like `std::vector<T>(n, value)`. ($O(N)$)

* `DynamicMonoidArray(const std::vector<T>& v)`
  Constructs the sequence from monoid values. ($O(N)$)

* `DynamicMonoidArray(std::vector<T>&& v)`
  Constructs the sequence by moving monoid values. ($O(N)$)

* `DynamicMonoidArray(const std::vector<U>& v)`
  Constructs the sequence from another type using `Monoid::make(x)` if available, otherwise `static_cast<T>(x)`. ($O(N)$)

* `DynamicMonoidArray(std::initializer_list<T> init)`
  Constructs the sequence from an initializer list of monoid values. ($O(N \log N)$)

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of elements. | $O(1)$ |
| `bool empty() const` | Returns whether the sequence is empty. | $O(1)$ |
| `void clear()` | Removes all elements. | $O(1)$ |
| `void insert(int pos, T value)` | Inserts `value` before index `pos`. | $O(\log N)$ |
| `void insert(int pos, const std::vector<T>& v)` | Inserts every value in `v` before index `pos`. | $O(M + \log N)$ |
| `void insert(int pos, const DynamicMonoidArray& other)` | Inserts a copy of `other` before index `pos`. | $O(M + \log N)$ |
| `void push_back(T value)`, `void push_front(T value)` | Inserts one value at the end or beginning. | $O(\log N)$ |
| `void append(const std::vector<T>& v)` | Appends all values in `v`. | $O(M + \log N)$ |
| `void append(const DynamicMonoidArray& other)` | Appends a copy of `other`. | $O(M + \log N)$ |
| `void erase(int pos)` | Removes the value at index `pos`. | $O(\log N)$ |
| `void erase(int l, int r)` | Removes the half-open range `[l, r)`. | $O(\log N)$ |
| `void pop_back()`, `void pop_front()` | Removes one value from the end or beginning. | $O(\log N)$ |
| `T get(int pos) const` | Returns the value at index `pos`. | $O(\log N)$ |
| `void set(int pos, T value)` | Replaces index `pos` and rebuilds affected products. | $O(\log N)$ |
| `void reverse(int l, int r)` | Reverses the half-open range `[l, r)`. | $O(\log N)$ |
| `void reverse()` | Reverses the entire sequence. | $O(1)$ |
| `void rotate(int l, int m, int r)` | Moves `[m, r)` before `[l, m)`, like `std::rotate`. | $O(\log N)$ |
| `T prod(int l, int r)` | Returns the monoid product over `[l, r)`. | $O(\log N)$ |
| `T all_prod() const` | Returns the monoid product over the whole sequence. | $O(1)$ |
| `std::vector<T> to_vector() const` | Dumps the sequence to `std::vector`. | $O(N)$ |
| `std::vector<T> to_vector(int l, int r) const` | Dumps `[l, r)` to `std::vector`, where `K = r - l`. | $O(K + \log N)$ |
| `DynamicMonoidArray split_off(int pos)` | Removes `[pos, N)` and returns it as a new sequence with its own pool, where `K = N - pos`. | $O(K + \log N)$ |

## Notes

Unlike `DynamicArray`, this structure does not expose mutable references to elements. Use `set(pos, value)` to update a value so that stored monoid products remain correct.

Order-aware monoids should store relative order information such as `size` and `ord`, not immutable global indices. For example, `monoid::ArgMin` returns `ord` relative to the queried range, so it remains valid after insertions, deletions, and reversals.

## Example

```cpp
#include "data_structure/dynamic_monoid_array.hpp"
#include "monoid/add.hpp"
#include <iostream>

using Monoid = m1une::monoid::Add<long long>;
using Array = m1une::data_structure::DynamicMonoidArray<Monoid>;

int main() {
    Array a = {1, 2, 3, 4, 5};

    std::cout << a.prod(1, 4) << "\n"; // 2 + 3 + 4 = 9

    a.reverse(1, 5);                   // {1, 5, 4, 3, 2}
    a.set(2, 10);                      // {1, 5, 10, 3, 2}
    a.insert(3, 7);                    // {1, 5, 10, 7, 3, 2}

    std::cout << a.prod(0, 4) << "\n"; // 1 + 5 + 10 + 7 = 23

    return 0;
}
```
