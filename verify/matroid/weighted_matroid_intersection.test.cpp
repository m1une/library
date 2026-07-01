#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "../../matroid/graphic_matroid.hpp"
#include "../../matroid/partition_matroid.hpp"
#include "../../matroid/weighted_matroid_intersection.hpp"

struct BruteResult {
    int cardinality = -1;
    std::vector<long long> minimum_weight;
    std::vector<long long> maximum_weight;
    std::vector<char> exists;
};

template <class Oracle1, class Oracle2>
BruteResult brute_force(const std::vector<long long>& weight, const Oracle1& oracle1,
                        const Oracle2& oracle2) {
    int n = int(weight.size());
    BruteResult result;
    result.minimum_weight.resize(n + 1);
    result.maximum_weight.resize(n + 1);
    result.exists.assign(n + 1, false);
    for (int mask = 0; mask < (1 << n); mask++) {
        std::vector<int> subset;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) {
                subset.push_back(i);
                sum += weight[i];
            }
        }
        if (!oracle1(subset) || !oracle2(subset)) continue;
        int cardinality = int(subset.size());
        result.cardinality = std::max(result.cardinality, cardinality);
        if (!result.exists[cardinality]) {
            result.exists[cardinality] = true;
            result.minimum_weight[cardinality] = sum;
            result.maximum_weight[cardinality] = sum;
        } else {
            result.minimum_weight[cardinality] =
                std::min(result.minimum_weight[cardinality], sum);
            result.maximum_weight[cardinality] =
                std::max(result.maximum_weight[cardinality], sum);
        }
    }
    return result;
}

template <class Oracle1, class Oracle2>
void check(const std::vector<long long>& weight, const Oracle1& oracle1,
           const Oracle2& oracle2) {
    int n = int(weight.size());
    BruteResult expected = brute_force(weight, oracle1, oracle2);
    auto maximum =
        m1une::matroid::weighted_matroid_intersection_max(n, weight, oracle1, oracle2);
    auto minimum =
        m1une::matroid::weighted_matroid_intersection_min(n, weight, oracle1, oracle2);
    auto default_result =
        m1une::matroid::weighted_matroid_intersection(n, weight, oracle1, oracle2);

    std::vector<long long> maximum_by_cardinality;
    std::vector<long long> minimum_by_cardinality;
    auto streamed_maximum = m1une::matroid::weighted_matroid_intersection_max_each(
        n, weight, oracle1, oracle2,
        [&](int cardinality, const long long& total_weight,
            const std::vector<int>& elements) {
            assert(cardinality == int(maximum_by_cardinality.size()));
            assert(int(elements.size()) == cardinality);
            assert(oracle1(elements) && oracle2(elements));
            assert(std::is_sorted(elements.begin(), elements.end()));
            long long sum = 0;
            for (int element : elements) sum += weight[element];
            (void)cardinality;
            (void)sum;
            assert(sum == total_weight);
            assert(total_weight == expected.maximum_weight[cardinality]);
            maximum_by_cardinality.push_back(total_weight);
        });
    auto streamed_minimum = m1une::matroid::weighted_matroid_intersection_min_each(
        n, weight, oracle1, oracle2,
        [&](int cardinality, const long long& total_weight,
            const std::vector<int>& elements) {
            assert(cardinality == int(minimum_by_cardinality.size()));
            assert(int(elements.size()) == cardinality);
            assert(oracle1(elements) && oracle2(elements));
            assert(std::is_sorted(elements.begin(), elements.end()));
            long long sum = 0;
            for (int element : elements) sum += weight[element];
            (void)cardinality;
            (void)sum;
            assert(sum == total_weight);
            assert(total_weight == expected.minimum_weight[cardinality]);
            minimum_by_cardinality.push_back(total_weight);
        });

    assert(maximum.size() == expected.cardinality);
    assert(minimum.size() == expected.cardinality);
    assert(maximum.total_weight == expected.maximum_weight[expected.cardinality]);
    assert(minimum.total_weight == expected.minimum_weight[expected.cardinality]);
    assert(default_result.total_weight == maximum.total_weight);
    assert(default_result.elements == maximum.elements);
    assert(streamed_maximum.total_weight == maximum.total_weight);
    assert(streamed_maximum.elements == maximum.elements);
    assert(streamed_minimum.total_weight == minimum.total_weight);
    assert(streamed_minimum.elements == minimum.elements);
    assert(oracle1(maximum.elements) && oracle2(maximum.elements));
    assert(oracle1(minimum.elements) && oracle2(minimum.elements));
    assert(std::is_sorted(maximum.elements.begin(), maximum.elements.end()));
    assert(std::is_sorted(minimum.elements.begin(), minimum.elements.end()));

    assert(int(maximum_by_cardinality.size()) == expected.cardinality + 1);
    assert(int(minimum_by_cardinality.size()) == expected.cardinality + 1);
    for (int cardinality = 0; cardinality <= expected.cardinality; cardinality++) {
        assert(expected.exists[cardinality]);
        assert(maximum_by_cardinality[cardinality] == expected.maximum_weight[cardinality]);
        assert(minimum_by_cardinality[cardinality] == expected.minimum_weight[cardinality]);
    }
}

void test_weighted_exchange() {
    m1une::matroid::PartitionMatroid left(std::vector<int>{0, 0, 1});
    m1une::matroid::PartitionMatroid right(std::vector<int>{0, 1, 0});
    std::vector<long long> weight = {100, 60, 70};
    auto result = m1une::matroid::weighted_matroid_intersection_max(3, weight, left, right);
    assert((result.elements == std::vector<int>{1, 2}));
    assert(result.total_weight == 130);

    std::vector<long long> best_weight;
    auto streamed = m1une::matroid::weighted_matroid_intersection_max_each(
        3, weight, left, right,
        [&](int, const long long& total_weight, const std::vector<int>&) {
            best_weight.push_back(total_weight);
        });
    assert((best_weight == std::vector<long long>{0, 100, 130}));
    assert(streamed.elements == result.elements);
    assert(streamed.total_weight == result.total_weight);

    weight = {-1, -100, -200};
    result = m1une::matroid::weighted_matroid_intersection_max(3, weight, left, right);
    assert(result.size() == 2);
    assert(result.total_weight == -300);
}

void test_equal_weights() {
    m1une::matroid::PartitionMatroid first(std::vector<int>{0, 0, 1, 1, 2, 2});
    m1une::matroid::PartitionMatroid second(std::vector<int>{0, 1, 1, 2, 2, 0});
    check(std::vector<long long>(6, 0), first, second);
    check(std::vector<long long>(6, 7), first, second);
}

void test_random_weighted_matroids() {
    std::mt19937 random(987654321);
    for (int test = 0; test < 300; test++) {
        int n = random() % 10;
        std::vector<long long> weight(n);
        for (long long& value : weight) value = int(random() % 41) - 20;

        int group_count = 1 + random() % 5;
        std::vector<int> group(n);
        for (int& value : group) value = random() % group_count;
        m1une::matroid::PartitionMatroid partition(group);

        int vertex_count = 1 + random() % 6;
        std::vector<std::pair<int, int>> edges(n);
        for (auto& [u, v] : edges) {
            u = random() % vertex_count;
            v = random() % vertex_count;
        }
        m1une::matroid::GraphicMatroid graphic(vertex_count, edges);
        check(weight, partition, graphic);

        int second_group_count = 1 + random() % 5;
        std::vector<int> second_group(n);
        for (int& value : second_group) value = random() % second_group_count;
        m1une::matroid::PartitionMatroid second_partition(second_group);
        check(weight, partition, second_partition);
    }
}

int main() {
    test_weighted_exchange();
    test_equal_weights();
    test_random_weighted_matroids();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
