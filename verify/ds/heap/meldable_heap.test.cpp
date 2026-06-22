#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../../ds/heap/meldable_heap.hpp"

#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

namespace {

void test_fixed() {
    m1une::ds::MeldableHeap<int> first = {3, 1, 7, 7};
    m1une::ds::MeldableHeap<int> second = {4, 6, 2};
    first.meld(std::move(second));
    assert(second.empty());
    assert(first.size() == 7);

    std::vector<int> expected = {7, 7, 6, 4, 3, 2, 1};
    for ([[maybe_unused]] int value : expected) {
        assert(first.top() == value);
        first.pop();
    }
    assert(first.empty());

    m1une::ds::PairingHeap<int, std::greater<int>> minimum;
    minimum.push(5);
    minimum.emplace(2);
    minimum.push(9);
    assert(minimum.top() == 2);
    minimum.pop();
    assert(minimum.top() == 5);

    m1une::ds::MeldableHeap<std::unique_ptr<int>, std::function<bool(
        const std::unique_ptr<int>&,
        const std::unique_ptr<int>&
    )>> move_only([](const auto& left, const auto& right) {
        return *left < *right;
    });
    move_only.push(std::make_unique<int>(3));
    move_only.emplace(std::make_unique<int>(8));
    assert(*move_only.top() == 8);
}

void test_randomized() {
    std::uint64_t state = 907;
    auto random = [&state]() {
        state ^= state << 7;
        state ^= state >> 9;
        return state;
    };

    constexpr int heap_count = 20;
    std::vector<m1une::ds::MeldableHeap<int>> heaps(heap_count);
    std::vector<std::priority_queue<int>> expected(heap_count);

    for (int operation = 0; operation < 100000; ++operation) {
        int heap = int(random() % heap_count);
        int type = int(random() % 4);
        if (type <= 1 || expected[heap].empty()) {
            int value = int(random() % 1000);
            heaps[heap].push(value);
            expected[heap].push(value);
        } else if (type == 2) {
            assert(heaps[heap].top() == expected[heap].top());
            heaps[heap].pop();
            expected[heap].pop();
        } else {
            int other = int(random() % heap_count);
            if (other == heap) continue;
            heaps[heap].meld(std::move(heaps[other]));
            while (!expected[other].empty()) {
                expected[heap].push(expected[other].top());
                expected[other].pop();
            }
        }

        for (int index = 0; index < heap_count; ++index) {
            assert(heaps[index].size() == expected[index].size());
            assert(heaps[index].empty() == expected[index].empty());
            if (!expected[index].empty()) {
                assert(heaps[index].top() == expected[index].top());
            }
        }
    }
}

void test_long_chain() {
    constexpr int size = 200000;
    m1une::ds::MeldableHeap<int> heap;
    for (int value = 0; value < size; ++value) heap.push(value);
    assert(heap.top() == size - 1);
    heap.clear();
    assert(heap.empty());
}

}  // namespace

int main() {
    test_fixed();
    test_randomized();
    test_long_chain();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
