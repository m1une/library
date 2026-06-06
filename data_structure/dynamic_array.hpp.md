---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/dynamic_array.hpp\"\n\n\n\n#include <vector>\n\
    #include <random>\n#include <chrono>\n#include <cassert>\n#include <initializer_list>\n\
    #include <utility> // for std::move\n\nnamespace m1une {\nnamespace data_structure\
    \ {\n\ntemplate <typename T>\nstruct DynamicArray {\n   private:\n    struct Node\
    \ {\n        T val;\n        int priority;\n        int count;\n        int l,\
    \ r;\n        \n        Node() : val(T()), priority(0), count(0), l(0), r(0) {}\
    \ \n        Node(T val, int priority) : val(std::move(val)), priority(priority),\
    \ count(1), l(0), r(0) {}\n    };\n\n    std::vector<Node> pool;\n    int root;\n\
    \    std::mt19937 rng;\n\n    int new_node(T val) {\n        pool.push_back(Node(std::move(val),\
    \ rng()));\n        return pool.size() - 1;\n    }\n\n    void update(int t) {\n\
    \        if (t) {\n            pool[t].count = 1 + pool[pool[t].l].count + pool[pool[t].r].count;\n\
    \        }\n    }\n\n    void split(int t, int pos, int& l, int& r) {\n      \
    \  if (!t) {\n            l = r = 0;\n            return;\n        }\n       \
    \ int left_count = pool[pool[t].l].count;\n        if (pos <= left_count) {\n\
    \            split(pool[t].l, pos, l, pool[t].l);\n            r = t;\n      \
    \  } else {\n            split(pool[t].r, pos - left_count - 1, pool[t].r, r);\n\
    \            l = t;\n        }\n        update(t);\n    }\n\n    int merge(int\
    \ l, int r) {\n        if (!l || !r) return l ? l : r;\n        if (pool[l].priority\
    \ > pool[r].priority) {\n            pool[l].r = merge(pool[l].r, r);\n      \
    \      update(l);\n            return l;\n        } else {\n            pool[r].l\
    \ = merge(l, pool[r].l);\n            update(r);\n            return r;\n    \
    \    }\n    }\n\n    void dump_dfs(int t, std::vector<T>& res) const {\n     \
    \   if (!t) return;\n        dump_dfs(pool[t].l, res);\n        res.push_back(pool[t].val);\n\
    \        dump_dfs(pool[t].r, res);\n    }\n\n   public:\n    // 1. Default Constructor\n\
    \    DynamicArray() : root(0), rng(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {\n        pool.push_back(Node());\n    }\n\n    // 2. Copy Constructor (const\
    \ lvalue reference)\n    DynamicArray(const DynamicArray& other) \n        : pool(other.pool),\
    \ root(other.root), rng(other.rng) {}\n\n    // 3. Move Constructor (rvalue reference)\n\
    \    DynamicArray(DynamicArray&& other) noexcept \n        : pool(std::move(other.pool)),\
    \ root(other.root), rng(std::move(other.rng)) {\n        other.root = 0;\n   \
    \ }\n\n    // 4. Copy Assignment Operator\n    DynamicArray& operator=(const DynamicArray&\
    \ other) {\n        if (this != &other) {\n            pool = other.pool;\n  \
    \          root = other.root;\n            rng = other.rng;\n        }\n     \
    \   return *this;\n    }\n\n    // 5. Move Assignment Operator\n    DynamicArray&\
    \ operator=(DynamicArray&& other) noexcept {\n        if (this != &other) {\n\
    \            pool = std::move(other.pool);\n            root = other.root;\n \
    \           rng = std::move(other.rng);\n            other.root = 0;\n       \
    \ }\n        return *this;\n    }\n\n    // 6. Constructor from const std::vector\
    \ (Copies elements)\n    explicit DynamicArray(const std::vector<T>& v) : DynamicArray()\
    \ {\n        pool.reserve(v.size() + 1);\n        for (const T& x : v) push_back(x);\n\
    \    }\n\n    // 7. Constructor from std::vector&& (Moves elements)\n    explicit\
    \ DynamicArray(std::vector<T>&& v) : DynamicArray() {\n        pool.reserve(v.size()\
    \ + 1);\n        for (T& x : v) push_back(std::move(x));\n    }\n\n    // 8. Constructor\
    \ from initializer list\n    DynamicArray(std::initializer_list<T> init) : DynamicArray()\
    \ {\n        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return pool[root].count;\n    }\n\n\
    \    void insert(int pos, T val) {\n        assert(0 <= pos && pos <= size());\n\
    \        int l, r;\n        split(root, pos, l, r);\n        root = merge(merge(l,\
    \ new_node(std::move(val))), r);\n    }\n\n    void push_back(T val) {\n     \
    \   insert(size(), std::move(val));\n    }\n\n    void erase(int pos) {\n    \
    \    assert(0 <= pos && pos < size());\n        int l, mid, r;\n        split(root,\
    \ pos, l, mid);\n        split(mid, 1, mid, r);\n        root = merge(l, r);\n\
    \    }\n\n    T get(int pos) const {\n        assert(0 <= pos && pos < size());\n\
    \        int t = root;\n        while (t) {\n            int left_count = pool[pool[t].l].count;\n\
    \            if (pos < left_count) {\n                t = pool[t].l;\n       \
    \     } else if (pos == left_count) {\n                return pool[t].val;\n \
    \           } else {\n                pos -= left_count + 1;\n               \
    \ t = pool[t].r;\n            }\n        }\n        return T();\n    }\n\n   \
    \ void set(int pos, T val) {\n        assert(0 <= pos && pos < size());\n    \
    \    int t = root;\n        while (t) {\n            int left_count = pool[pool[t].l].count;\n\
    \            if (pos < left_count) {\n                t = pool[t].l;\n       \
    \     } else if (pos == left_count) {\n                pool[t].val = std::move(val);\n\
    \                return;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = pool[t].r;\n            }\n        }\n    }\n\n  \
    \  std::vector<T> to_vector() const {\n        std::vector<T> res;\n        res.reserve(size());\n\
    \        dump_dfs(root, res);\n        return res;\n    }\n};\n\n}  // namespace\
    \ data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DYNAMIC_ARRAY_HPP\n#define M1UNE_DYNAMIC_ARRAY_HPP 1\n\n#include\
    \ <vector>\n#include <random>\n#include <chrono>\n#include <cassert>\n#include\
    \ <initializer_list>\n#include <utility> // for std::move\n\nnamespace m1une {\n\
    namespace data_structure {\n\ntemplate <typename T>\nstruct DynamicArray {\n \
    \  private:\n    struct Node {\n        T val;\n        int priority;\n      \
    \  int count;\n        int l, r;\n        \n        Node() : val(T()), priority(0),\
    \ count(0), l(0), r(0) {} \n        Node(T val, int priority) : val(std::move(val)),\
    \ priority(priority), count(1), l(0), r(0) {}\n    };\n\n    std::vector<Node>\
    \ pool;\n    int root;\n    std::mt19937 rng;\n\n    int new_node(T val) {\n \
    \       pool.push_back(Node(std::move(val), rng()));\n        return pool.size()\
    \ - 1;\n    }\n\n    void update(int t) {\n        if (t) {\n            pool[t].count\
    \ = 1 + pool[pool[t].l].count + pool[pool[t].r].count;\n        }\n    }\n\n \
    \   void split(int t, int pos, int& l, int& r) {\n        if (!t) {\n        \
    \    l = r = 0;\n            return;\n        }\n        int left_count = pool[pool[t].l].count;\n\
    \        if (pos <= left_count) {\n            split(pool[t].l, pos, l, pool[t].l);\n\
    \            r = t;\n        } else {\n            split(pool[t].r, pos - left_count\
    \ - 1, pool[t].r, r);\n            l = t;\n        }\n        update(t);\n   \
    \ }\n\n    int merge(int l, int r) {\n        if (!l || !r) return l ? l : r;\n\
    \        if (pool[l].priority > pool[r].priority) {\n            pool[l].r = merge(pool[l].r,\
    \ r);\n            update(l);\n            return l;\n        } else {\n     \
    \       pool[r].l = merge(l, pool[r].l);\n            update(r);\n           \
    \ return r;\n        }\n    }\n\n    void dump_dfs(int t, std::vector<T>& res)\
    \ const {\n        if (!t) return;\n        dump_dfs(pool[t].l, res);\n      \
    \  res.push_back(pool[t].val);\n        dump_dfs(pool[t].r, res);\n    }\n\n \
    \  public:\n    // 1. Default Constructor\n    DynamicArray() : root(0), rng(std::chrono::steady_clock::now().time_since_epoch().count())\
    \ {\n        pool.push_back(Node());\n    }\n\n    // 2. Copy Constructor (const\
    \ lvalue reference)\n    DynamicArray(const DynamicArray& other) \n        : pool(other.pool),\
    \ root(other.root), rng(other.rng) {}\n\n    // 3. Move Constructor (rvalue reference)\n\
    \    DynamicArray(DynamicArray&& other) noexcept \n        : pool(std::move(other.pool)),\
    \ root(other.root), rng(std::move(other.rng)) {\n        other.root = 0;\n   \
    \ }\n\n    // 4. Copy Assignment Operator\n    DynamicArray& operator=(const DynamicArray&\
    \ other) {\n        if (this != &other) {\n            pool = other.pool;\n  \
    \          root = other.root;\n            rng = other.rng;\n        }\n     \
    \   return *this;\n    }\n\n    // 5. Move Assignment Operator\n    DynamicArray&\
    \ operator=(DynamicArray&& other) noexcept {\n        if (this != &other) {\n\
    \            pool = std::move(other.pool);\n            root = other.root;\n \
    \           rng = std::move(other.rng);\n            other.root = 0;\n       \
    \ }\n        return *this;\n    }\n\n    // 6. Constructor from const std::vector\
    \ (Copies elements)\n    explicit DynamicArray(const std::vector<T>& v) : DynamicArray()\
    \ {\n        pool.reserve(v.size() + 1);\n        for (const T& x : v) push_back(x);\n\
    \    }\n\n    // 7. Constructor from std::vector&& (Moves elements)\n    explicit\
    \ DynamicArray(std::vector<T>&& v) : DynamicArray() {\n        pool.reserve(v.size()\
    \ + 1);\n        for (T& x : v) push_back(std::move(x));\n    }\n\n    // 8. Constructor\
    \ from initializer list\n    DynamicArray(std::initializer_list<T> init) : DynamicArray()\
    \ {\n        pool.reserve(init.size() + 1);\n        for (const T& x : init) push_back(x);\n\
    \    }\n\n    int size() const {\n        return pool[root].count;\n    }\n\n\
    \    void insert(int pos, T val) {\n        assert(0 <= pos && pos <= size());\n\
    \        int l, r;\n        split(root, pos, l, r);\n        root = merge(merge(l,\
    \ new_node(std::move(val))), r);\n    }\n\n    void push_back(T val) {\n     \
    \   insert(size(), std::move(val));\n    }\n\n    void erase(int pos) {\n    \
    \    assert(0 <= pos && pos < size());\n        int l, mid, r;\n        split(root,\
    \ pos, l, mid);\n        split(mid, 1, mid, r);\n        root = merge(l, r);\n\
    \    }\n\n    T get(int pos) const {\n        assert(0 <= pos && pos < size());\n\
    \        int t = root;\n        while (t) {\n            int left_count = pool[pool[t].l].count;\n\
    \            if (pos < left_count) {\n                t = pool[t].l;\n       \
    \     } else if (pos == left_count) {\n                return pool[t].val;\n \
    \           } else {\n                pos -= left_count + 1;\n               \
    \ t = pool[t].r;\n            }\n        }\n        return T();\n    }\n\n   \
    \ void set(int pos, T val) {\n        assert(0 <= pos && pos < size());\n    \
    \    int t = root;\n        while (t) {\n            int left_count = pool[pool[t].l].count;\n\
    \            if (pos < left_count) {\n                t = pool[t].l;\n       \
    \     } else if (pos == left_count) {\n                pool[t].val = std::move(val);\n\
    \                return;\n            } else {\n                pos -= left_count\
    \ + 1;\n                t = pool[t].r;\n            }\n        }\n    }\n\n  \
    \  std::vector<T> to_vector() const {\n        std::vector<T> res;\n        res.reserve(size());\n\
    \        dump_dfs(root, res);\n        return res;\n    }\n};\n\n}  // namespace\
    \ data_structure\n}  // namespace m1une\n\n#endif  // M1UNE_DYNAMIC_ARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/dynamic_array.hpp
  requiredBy: []
  timestamp: '2026-06-06 20:57:07+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/dynamic_array.hpp
layout: document
title: Dynamic Array (Implicit Treap)
---

## Overview

`DynamicArray` is an optimized implementation of an Implicit Treap, backed by a `std::vector` memory pool. It acts as a highly dynamic array, supporting $O(\log N)$ insertions and deletions at any index.

Because it relies on an array-based memory pool instead of standard pointers, deep copying the data structure via the copy constructor is exceptionally fast and automatically avoids heap fragmentation.

## Template Parameters

* `T`: The underlying data type of the elements.

## Constructors and Assignment Operators

* `DynamicArray()`
  Constructs an empty dynamic array. ($O(1)$)

* `DynamicArray(const DynamicArray& other)`
  Copy constructor. Deep copies the array structure and memory pool. ($O(V)$ where $V$ is the capacity of the memory pool)

* `DynamicArray(DynamicArray&& other)`
  Move constructor. Takes ownership of the other array's memory pool without reallocating. ($O(1)$)

* `DynamicArray(const std::vector<T>& v)`
  Constructs the dynamic array initialized with elements from `v`. ($O(N \log N)$)

* `DynamicArray(std::vector<T>&& v)`
  Constructs the dynamic array by moving elements from an rvalue reference of a `std::vector`. This avoids deep copies of the individual elements, providing a massive performance boost when storing complex objects like strings or nested vectors. ($O(N \log N)$)

* `DynamicArray(std::initializer_list<T> init)`
  Constructs the dynamic array initialized with an initializer list. ($O(N \log N)$)

* `operator=`
  Supports both copy and move assignment.

## Methods

* `int size() const`
  Returns the number of elements currently in the array. ($O(1)$)

* `void push_back(T val)`
  Appends a new element `val` to the end of the array. ($O(\log N)$)

* `void insert(int pos, T val)`
  Inserts a new element `val` at the specified 0-based index `pos`. All subsequent elements shift right. ($O(\log N)$)

* `void erase(int pos)`
  Removes the element at the specified 0-based index `pos`. All subsequent elements shift left. ($O(\log N)$)

* `T get(int pos) const`
  Returns the element at the specified 0-based index `pos`. ($O(\log N)$)

* `void set(int pos, T val)`
  Overwrites the element at index `pos` with `val`. ($O(\log N)$)

* `std::vector<T> to_vector() const`
  Dumps the entire array state into a standard `std::vector`. ($O(N)$)

## Example

```cpp
#include "data_structure/dynamic_array.hpp"
#include <iostream>
#include <vector>

using namespace m1une::data_structure;

int main() {
    // Construct from initializer list
    DynamicArray<int> arr1 = {10, 20, 30};
    
    // Copy Constructor
    DynamicArray<int> arr2 = arr1; 
    arr2.insert(1, 15);

    // Move Assignment
    DynamicArray<int> arr3;
    arr3 = std::move(arr2);
    
    // Print arr3 -> 10 15 20 30
    for(int x : arr3.to_vector()) {
        std::cout << x << " "; 
    }
    std::cout << "\n";

    return 0;
}
```
