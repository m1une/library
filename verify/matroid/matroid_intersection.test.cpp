#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "../../matroid/graphic_matroid.hpp"
#include "../../matroid/linear_matroid.hpp"
#include "../../matroid/matroid_intersection.hpp"
#include "../../matroid/partition_matroid.hpp"

template <class Oracle1, class Oracle2>
int brute_force(int ground_size, const Oracle1& oracle1, const Oracle2& oracle2) {
    int best = 0;
    for (int mask = 0; mask < (1 << ground_size); mask++) {
        std::vector<int> subset;
        for (int i = 0; i < ground_size; i++) {
            if (mask >> i & 1) subset.push_back(i);
        }
        if (oracle1(subset) && oracle2(subset)) best = std::max(best, int(subset.size()));
    }
    return best;
}

template <class Oracle1, class Oracle2>
void check(int ground_size, const Oracle1& oracle1, const Oracle2& oracle2) {
    auto result = m1une::matroid::matroid_intersection(ground_size, oracle1, oracle2);
    assert(std::is_sorted(result.begin(), result.end()));
    assert(std::adjacent_find(result.begin(), result.end()) == result.end());
    assert(oracle1(result));
    assert(oracle2(result));
    assert(int(result.size()) == brute_force(ground_size, oracle1, oracle2));
}

void test_augmenting_exchange() {
    m1une::matroid::PartitionMatroid left(std::vector<int>{0, 0, 1});
    m1une::matroid::PartitionMatroid right(std::vector<int>{0, 1, 0});
    auto result = m1une::matroid::matroid_intersection(3, left, right);
    assert((result == std::vector<int>{1, 2}));
}

void test_random_matroids() {
    std::mt19937 random(123456789);
    for (int test = 0; test < 300; test++) {
        int ground_size = random() % 11;
        int group_count = 1 + random() % 5;
        std::vector<int> group(ground_size);
        for (int& value : group) value = random() % group_count;
        std::vector<int> capacity(group_count, 1);
        m1une::matroid::PartitionMatroid partition(group, capacity);

        int vertex_count = 1 + random() % 6;
        std::vector<std::pair<int, int>> edge(ground_size);
        for (auto& [u, v] : edge) {
            u = random() % vertex_count;
            v = random() % vertex_count;
        }
        m1une::matroid::GraphicMatroid graphic(vertex_count, edge);
        check(ground_size, partition, graphic);

        int second_group_count = 1 + random() % 5;
        std::vector<int> second_group(ground_size);
        for (int& value : second_group) value = random() % second_group_count;
        m1une::matroid::PartitionMatroid second_partition(second_group);
        check(ground_size, partition, second_partition);

        std::vector<std::uint64_t> vector1(ground_size), vector2(ground_size);
        for (int i = 0; i < ground_size; i++) {
            vector1[i] = random() % 64;
            vector2[i] = random() % 64;
        }
        m1une::matroid::BinaryLinearMatroid linear1(vector1), linear2(vector2);
        check(ground_size, linear1, linear2);
    }
}

int main() {
    test_augmenting_exchange();
    test_random_matroids();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
