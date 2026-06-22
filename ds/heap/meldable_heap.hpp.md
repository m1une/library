---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/heap/meldable_heap.test.cpp
    title: verify/ds/heap/meldable_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/heap/meldable_heap.hpp\"\n\n\n\n#include <cassert>\n\
    #include <cstddef>\n#include <functional>\n#include <initializer_list>\n#include\
    \ <memory>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n\
    namespace m1une {\nnamespace ds {\n\n// Pairing heap with constant-time insertion\
    \ and melding.\ntemplate <class T, class Compare = std::less<T>>\nstruct MeldableHeap\
    \ {\n   private:\n    struct Node {\n        T value;\n        std::unique_ptr<Node>\
    \ child;\n        std::unique_ptr<Node> sibling;\n\n        template <class...\
    \ Args>\n        explicit Node(Args&&... args) : value(std::forward<Args>(args)...)\
    \ {}\n    };\n\n    std::unique_ptr<Node> _root;\n    std::size_t _size;\n   \
    \ [[no_unique_address]] Compare _compare;\n\n    std::unique_ptr<Node> meld_nodes(std::unique_ptr<Node>\
    \ first, std::unique_ptr<Node> second) {\n        if (!first) return second;\n\
    \        if (!second) return first;\n        if (_compare(first->value, second->value))\
    \ {\n            first.swap(second);\n        }\n        second->sibling = std::move(first->child);\n\
    \        first->child = std::move(second);\n        return first;\n    }\n\n \
    \   static void destroy(std::unique_ptr<Node> root) {\n        std::vector<Node*>\
    \ stack;\n        if (root) stack.push_back(root.release());\n        while (!stack.empty())\
    \ {\n            Node* node = stack.back();\n            stack.pop_back();\n \
    \           if (node->child) stack.push_back(node->child.release());\n       \
    \     if (node->sibling) stack.push_back(node->sibling.release());\n         \
    \   delete node;\n        }\n    }\n\n   public:\n    MeldableHeap() : _size(0),\
    \ _compare() {}\n\n    explicit MeldableHeap(Compare compare) : _size(0), _compare(std::move(compare))\
    \ {}\n\n    MeldableHeap(std::initializer_list<T> values, Compare compare = Compare())\
    \ : MeldableHeap(std::move(compare)) {\n        for (const T& value : values)\
    \ push(value);\n    }\n\n    template <class Iterator>\n    MeldableHeap(Iterator\
    \ first, Iterator last, Compare compare = Compare()) : MeldableHeap(std::move(compare))\
    \ {\n        while (first != last) {\n            push(*first);\n            ++first;\n\
    \        }\n    }\n\n    MeldableHeap(const MeldableHeap&) = delete;\n    MeldableHeap&\
    \ operator=(const MeldableHeap&) = delete;\n\n    MeldableHeap(MeldableHeap&&\
    \ other) noexcept(std::is_nothrow_move_constructible_v<Compare>)\n        : _root(std::move(other._root)),\
    \ _size(std::exchange(other._size, 0)), _compare(std::move(other._compare)) {}\n\
    \n    MeldableHeap& operator=(MeldableHeap&& other) noexcept(std::is_nothrow_move_assignable_v<Compare>)\
    \ {\n        if (this == &other) return *this;\n        clear();\n        _root\
    \ = std::move(other._root);\n        _size = std::exchange(other._size, 0);\n\
    \        _compare = std::move(other._compare);\n        return *this;\n    }\n\
    \n    ~MeldableHeap() {\n        clear();\n    }\n\n    std::size_t size() const\
    \ {\n        return _size;\n    }\n\n    bool empty() const {\n        return\
    \ _root == nullptr;\n    }\n\n    const T& top() const {\n        assert(!empty());\n\
    \        return _root->value;\n    }\n\n    void clear() {\n        destroy(std::move(_root));\n\
    \        _size = 0;\n    }\n\n    template <class... Args>\n    void emplace(Args&&...\
    \ args) {\n        auto node = std::make_unique<Node>(std::forward<Args>(args)...);\n\
    \        _root = meld_nodes(std::move(_root), std::move(node));\n        ++_size;\n\
    \    }\n\n    void push(const T& value) {\n        emplace(value);\n    }\n\n\
    \    void push(T&& value) {\n        emplace(std::move(value));\n    }\n\n   \
    \ // Removes the highest-priority element.\n    void pop() {\n        assert(!empty());\n\
    \        std::unique_ptr<Node> children = std::move(_root->child);\n        _root.reset();\n\
    \        --_size;\n\n        std::vector<std::unique_ptr<Node>> pairs;\n     \
    \   while (children) {\n            std::unique_ptr<Node> first = std::move(children);\n\
    \            children = std::move(first->sibling);\n            first->sibling.reset();\n\
    \n            if (children) {\n                std::unique_ptr<Node> second =\
    \ std::move(children);\n                children = std::move(second->sibling);\n\
    \                second->sibling.reset();\n                first = meld_nodes(std::move(first),\
    \ std::move(second));\n            }\n            pairs.push_back(std::move(first));\n\
    \        }\n\n        while (!pairs.empty()) {\n            _root = meld_nodes(std::move(pairs.back()),\
    \ std::move(_root));\n            pairs.pop_back();\n        }\n    }\n\n    //\
    \ Moves every element from `other` into this heap.\n    void meld(MeldableHeap&&\
    \ other) {\n        if (this == &other) return;\n        _root = meld_nodes(std::move(_root),\
    \ std::move(other._root));\n        _size += std::exchange(other._size, 0);\n\
    \    }\n\n    void merge(MeldableHeap&& other) {\n        meld(std::move(other));\n\
    \    }\n\n    const Compare& comparator() const {\n        return _compare;\n\
    \    }\n};\n\ntemplate <class T, class Compare = std::less<T>>\nusing PairingHeap\
    \ = MeldableHeap<T, Compare>;\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    \n"
  code: "#ifndef M1UNE_DS_HEAP_MELDABLE_HEAP_HPP\n#define M1UNE_DS_HEAP_MELDABLE_HEAP_HPP\
    \ 1\n\n#include <cassert>\n#include <cstddef>\n#include <functional>\n#include\
    \ <initializer_list>\n#include <memory>\n#include <type_traits>\n#include <utility>\n\
    #include <vector>\n\nnamespace m1une {\nnamespace ds {\n\n// Pairing heap with\
    \ constant-time insertion and melding.\ntemplate <class T, class Compare = std::less<T>>\n\
    struct MeldableHeap {\n   private:\n    struct Node {\n        T value;\n    \
    \    std::unique_ptr<Node> child;\n        std::unique_ptr<Node> sibling;\n\n\
    \        template <class... Args>\n        explicit Node(Args&&... args) : value(std::forward<Args>(args)...)\
    \ {}\n    };\n\n    std::unique_ptr<Node> _root;\n    std::size_t _size;\n   \
    \ [[no_unique_address]] Compare _compare;\n\n    std::unique_ptr<Node> meld_nodes(std::unique_ptr<Node>\
    \ first, std::unique_ptr<Node> second) {\n        if (!first) return second;\n\
    \        if (!second) return first;\n        if (_compare(first->value, second->value))\
    \ {\n            first.swap(second);\n        }\n        second->sibling = std::move(first->child);\n\
    \        first->child = std::move(second);\n        return first;\n    }\n\n \
    \   static void destroy(std::unique_ptr<Node> root) {\n        std::vector<Node*>\
    \ stack;\n        if (root) stack.push_back(root.release());\n        while (!stack.empty())\
    \ {\n            Node* node = stack.back();\n            stack.pop_back();\n \
    \           if (node->child) stack.push_back(node->child.release());\n       \
    \     if (node->sibling) stack.push_back(node->sibling.release());\n         \
    \   delete node;\n        }\n    }\n\n   public:\n    MeldableHeap() : _size(0),\
    \ _compare() {}\n\n    explicit MeldableHeap(Compare compare) : _size(0), _compare(std::move(compare))\
    \ {}\n\n    MeldableHeap(std::initializer_list<T> values, Compare compare = Compare())\
    \ : MeldableHeap(std::move(compare)) {\n        for (const T& value : values)\
    \ push(value);\n    }\n\n    template <class Iterator>\n    MeldableHeap(Iterator\
    \ first, Iterator last, Compare compare = Compare()) : MeldableHeap(std::move(compare))\
    \ {\n        while (first != last) {\n            push(*first);\n            ++first;\n\
    \        }\n    }\n\n    MeldableHeap(const MeldableHeap&) = delete;\n    MeldableHeap&\
    \ operator=(const MeldableHeap&) = delete;\n\n    MeldableHeap(MeldableHeap&&\
    \ other) noexcept(std::is_nothrow_move_constructible_v<Compare>)\n        : _root(std::move(other._root)),\
    \ _size(std::exchange(other._size, 0)), _compare(std::move(other._compare)) {}\n\
    \n    MeldableHeap& operator=(MeldableHeap&& other) noexcept(std::is_nothrow_move_assignable_v<Compare>)\
    \ {\n        if (this == &other) return *this;\n        clear();\n        _root\
    \ = std::move(other._root);\n        _size = std::exchange(other._size, 0);\n\
    \        _compare = std::move(other._compare);\n        return *this;\n    }\n\
    \n    ~MeldableHeap() {\n        clear();\n    }\n\n    std::size_t size() const\
    \ {\n        return _size;\n    }\n\n    bool empty() const {\n        return\
    \ _root == nullptr;\n    }\n\n    const T& top() const {\n        assert(!empty());\n\
    \        return _root->value;\n    }\n\n    void clear() {\n        destroy(std::move(_root));\n\
    \        _size = 0;\n    }\n\n    template <class... Args>\n    void emplace(Args&&...\
    \ args) {\n        auto node = std::make_unique<Node>(std::forward<Args>(args)...);\n\
    \        _root = meld_nodes(std::move(_root), std::move(node));\n        ++_size;\n\
    \    }\n\n    void push(const T& value) {\n        emplace(value);\n    }\n\n\
    \    void push(T&& value) {\n        emplace(std::move(value));\n    }\n\n   \
    \ // Removes the highest-priority element.\n    void pop() {\n        assert(!empty());\n\
    \        std::unique_ptr<Node> children = std::move(_root->child);\n        _root.reset();\n\
    \        --_size;\n\n        std::vector<std::unique_ptr<Node>> pairs;\n     \
    \   while (children) {\n            std::unique_ptr<Node> first = std::move(children);\n\
    \            children = std::move(first->sibling);\n            first->sibling.reset();\n\
    \n            if (children) {\n                std::unique_ptr<Node> second =\
    \ std::move(children);\n                children = std::move(second->sibling);\n\
    \                second->sibling.reset();\n                first = meld_nodes(std::move(first),\
    \ std::move(second));\n            }\n            pairs.push_back(std::move(first));\n\
    \        }\n\n        while (!pairs.empty()) {\n            _root = meld_nodes(std::move(pairs.back()),\
    \ std::move(_root));\n            pairs.pop_back();\n        }\n    }\n\n    //\
    \ Moves every element from `other` into this heap.\n    void meld(MeldableHeap&&\
    \ other) {\n        if (this == &other) return;\n        _root = meld_nodes(std::move(_root),\
    \ std::move(other._root));\n        _size += std::exchange(other._size, 0);\n\
    \    }\n\n    void merge(MeldableHeap&& other) {\n        meld(std::move(other));\n\
    \    }\n\n    const Compare& comparator() const {\n        return _compare;\n\
    \    }\n};\n\ntemplate <class T, class Compare = std::less<T>>\nusing PairingHeap\
    \ = MeldableHeap<T, Compare>;\n\n}  // namespace ds\n}  // namespace m1une\n\n\
    #endif  // M1UNE_DS_HEAP_MELDABLE_HEAP_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: ds/heap/meldable_heap.hpp
  requiredBy: []
  timestamp: '2026-06-23 02:41:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/heap/meldable_heap.test.cpp
documentation_of: ds/heap/meldable_heap.hpp
layout: document
title: Meldable Heap
---

## Overview

`MeldableHeap<T, Compare>` is a pairing heap. It supports the usual priority
queue operations together with efficient destructive melding.

`PairingHeap<T, Compare>` is an alias of the same type.

## Priority Order

Comparator semantics match `std::priority_queue`:

* `std::less<T>` creates a max-heap.
* `std::greater<T>` creates a min-heap.

For a custom comparator, `top()` returns an element for which no other element
has higher priority according to that comparator.

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `push(value)` | Inserts an element. | $O(1)$ |
| `emplace(args...)` | Constructs and inserts an element. | $O(1)$ |
| `top()` | Returns the highest-priority element. | $O(1)$ |
| `pop()` | Removes the highest-priority element. | Amortized $O(\log N)$ |
| `meld(std::move(other))` | Moves all elements from `other` into this heap. | $O(1)$ |
| `merge(std::move(other))` | Alias of `meld`. | $O(1)$ |
| `size()` | Returns the number of elements. | $O(1)$ |
| `empty()` | Returns whether the heap is empty. | $O(1)$ |
| `clear()` | Removes all elements without recursive destruction. | $O(N)$ |
| `comparator()` | Returns the comparator. | $O(1)$ |

`top` and `pop` require a nonempty heap.

After melding, `other` is empty. Both heaps must use compatible comparator
states; the destination heap's comparator determines the merged ordering.

The heap is movable but not copyable. This makes ownership during melding
explicit and permits move-only element types.

## Example

```cpp
#include "ds/heap/meldable_heap.hpp"

#include <iostream>
#include <utility>

int main() {
    m1une::ds::MeldableHeap<int> first = {3, 1, 7};
    m1une::ds::MeldableHeap<int> second = {4, 6};

    first.meld(std::move(second));
    while (!first.empty()) {
        std::cout << first.top() << "\n";
        first.pop();
    }
}
```
