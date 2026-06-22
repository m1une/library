---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/heap/meldable_heap.hpp
    title: Meldable Heap
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/ds/heap/meldable_heap.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/heap/meldable_heap.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstddef>\n#include <functional>\n#include\
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
    \n#line 4 \"verify/ds/heap/meldable_heap.test.cpp\"\n\n#line 6 \"verify/ds/heap/meldable_heap.test.cpp\"\
    \n#include <cstdint>\n#line 8 \"verify/ds/heap/meldable_heap.test.cpp\"\n#include\
    \ <iostream>\n#line 10 \"verify/ds/heap/meldable_heap.test.cpp\"\n#include <queue>\n\
    #line 13 \"verify/ds/heap/meldable_heap.test.cpp\"\n\nnamespace {\n\nvoid test_fixed()\
    \ {\n    m1une::ds::MeldableHeap<int> first = {3, 1, 7, 7};\n    m1une::ds::MeldableHeap<int>\
    \ second = {4, 6, 2};\n    first.meld(std::move(second));\n    assert(second.empty());\n\
    \    assert(first.size() == 7);\n\n    std::vector<int> expected = {7, 7, 6, 4,\
    \ 3, 2, 1};\n    for ([[maybe_unused]] int value : expected) {\n        assert(first.top()\
    \ == value);\n        first.pop();\n    }\n    assert(first.empty());\n\n    m1une::ds::PairingHeap<int,\
    \ std::greater<int>> minimum;\n    minimum.push(5);\n    minimum.emplace(2);\n\
    \    minimum.push(9);\n    assert(minimum.top() == 2);\n    minimum.pop();\n \
    \   assert(minimum.top() == 5);\n\n    m1une::ds::MeldableHeap<std::unique_ptr<int>,\
    \ std::function<bool(\n        const std::unique_ptr<int>&,\n        const std::unique_ptr<int>&\n\
    \    )>> move_only([](const auto& left, const auto& right) {\n        return *left\
    \ < *right;\n    });\n    move_only.push(std::make_unique<int>(3));\n    move_only.emplace(std::make_unique<int>(8));\n\
    \    assert(*move_only.top() == 8);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 907;\n    auto random = [&state]() {\n        state ^= state << 7;\n\
    \        state ^= state >> 9;\n        return state;\n    };\n\n    constexpr\
    \ int heap_count = 20;\n    std::vector<m1une::ds::MeldableHeap<int>> heaps(heap_count);\n\
    \    std::vector<std::priority_queue<int>> expected(heap_count);\n\n    for (int\
    \ operation = 0; operation < 100000; ++operation) {\n        int heap = int(random()\
    \ % heap_count);\n        int type = int(random() % 4);\n        if (type <= 1\
    \ || expected[heap].empty()) {\n            int value = int(random() % 1000);\n\
    \            heaps[heap].push(value);\n            expected[heap].push(value);\n\
    \        } else if (type == 2) {\n            assert(heaps[heap].top() == expected[heap].top());\n\
    \            heaps[heap].pop();\n            expected[heap].pop();\n        }\
    \ else {\n            int other = int(random() % heap_count);\n            if\
    \ (other == heap) continue;\n            heaps[heap].meld(std::move(heaps[other]));\n\
    \            while (!expected[other].empty()) {\n                expected[heap].push(expected[other].top());\n\
    \                expected[other].pop();\n            }\n        }\n\n        for\
    \ (int index = 0; index < heap_count; ++index) {\n            assert(heaps[index].size()\
    \ == expected[index].size());\n            assert(heaps[index].empty() == expected[index].empty());\n\
    \            if (!expected[index].empty()) {\n                assert(heaps[index].top()\
    \ == expected[index].top());\n            }\n        }\n    }\n}\n\nvoid test_long_chain()\
    \ {\n    constexpr int size = 200000;\n    m1une::ds::MeldableHeap<int> heap;\n\
    \    for (int value = 0; value < size; ++value) heap.push(value);\n    assert(heap.top()\
    \ == size - 1);\n    heap.clear();\n    assert(heap.empty());\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n    test_long_chain();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/heap/meldable_heap.hpp\"\n\n#include <cassert>\n#include <cstdint>\n\
    #include <functional>\n#include <iostream>\n#include <memory>\n#include <queue>\n\
    #include <utility>\n#include <vector>\n\nnamespace {\n\nvoid test_fixed() {\n\
    \    m1une::ds::MeldableHeap<int> first = {3, 1, 7, 7};\n    m1une::ds::MeldableHeap<int>\
    \ second = {4, 6, 2};\n    first.meld(std::move(second));\n    assert(second.empty());\n\
    \    assert(first.size() == 7);\n\n    std::vector<int> expected = {7, 7, 6, 4,\
    \ 3, 2, 1};\n    for ([[maybe_unused]] int value : expected) {\n        assert(first.top()\
    \ == value);\n        first.pop();\n    }\n    assert(first.empty());\n\n    m1une::ds::PairingHeap<int,\
    \ std::greater<int>> minimum;\n    minimum.push(5);\n    minimum.emplace(2);\n\
    \    minimum.push(9);\n    assert(minimum.top() == 2);\n    minimum.pop();\n \
    \   assert(minimum.top() == 5);\n\n    m1une::ds::MeldableHeap<std::unique_ptr<int>,\
    \ std::function<bool(\n        const std::unique_ptr<int>&,\n        const std::unique_ptr<int>&\n\
    \    )>> move_only([](const auto& left, const auto& right) {\n        return *left\
    \ < *right;\n    });\n    move_only.push(std::make_unique<int>(3));\n    move_only.emplace(std::make_unique<int>(8));\n\
    \    assert(*move_only.top() == 8);\n}\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 907;\n    auto random = [&state]() {\n        state ^= state << 7;\n\
    \        state ^= state >> 9;\n        return state;\n    };\n\n    constexpr\
    \ int heap_count = 20;\n    std::vector<m1une::ds::MeldableHeap<int>> heaps(heap_count);\n\
    \    std::vector<std::priority_queue<int>> expected(heap_count);\n\n    for (int\
    \ operation = 0; operation < 100000; ++operation) {\n        int heap = int(random()\
    \ % heap_count);\n        int type = int(random() % 4);\n        if (type <= 1\
    \ || expected[heap].empty()) {\n            int value = int(random() % 1000);\n\
    \            heaps[heap].push(value);\n            expected[heap].push(value);\n\
    \        } else if (type == 2) {\n            assert(heaps[heap].top() == expected[heap].top());\n\
    \            heaps[heap].pop();\n            expected[heap].pop();\n        }\
    \ else {\n            int other = int(random() % heap_count);\n            if\
    \ (other == heap) continue;\n            heaps[heap].meld(std::move(heaps[other]));\n\
    \            while (!expected[other].empty()) {\n                expected[heap].push(expected[other].top());\n\
    \                expected[other].pop();\n            }\n        }\n\n        for\
    \ (int index = 0; index < heap_count; ++index) {\n            assert(heaps[index].size()\
    \ == expected[index].size());\n            assert(heaps[index].empty() == expected[index].empty());\n\
    \            if (!expected[index].empty()) {\n                assert(heaps[index].top()\
    \ == expected[index].top());\n            }\n        }\n    }\n}\n\nvoid test_long_chain()\
    \ {\n    constexpr int size = 200000;\n    m1une::ds::MeldableHeap<int> heap;\n\
    \    for (int value = 0; value < size; ++value) heap.push(value);\n    assert(heap.top()\
    \ == size - 1);\n    heap.clear();\n    assert(heap.empty());\n}\n\n}  // namespace\n\
    \nint main() {\n    test_fixed();\n    test_randomized();\n    test_long_chain();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - ds/heap/meldable_heap.hpp
  isVerificationFile: true
  path: verify/ds/heap/meldable_heap.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:41:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/heap/meldable_heap.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/heap/meldable_heap.test.cpp
- /verify/verify/ds/heap/meldable_heap.test.cpp.html
title: verify/ds/heap/meldable_heap.test.cpp
---
