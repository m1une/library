#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include <cassert>
#include <cstdint>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

#include "../../math/modint.hpp"
#include "../../matroid/all.hpp"

using mint = m1une::math::modint998244353;

void test_uniform_matroid() {
    m1une::matroid::UniformMatroid matroid(5, 2);
    assert(matroid.size() == 5);
    assert(matroid.rank() == 2);
    assert(matroid(std::vector<int>{1, 4}));
    assert(!matroid(std::vector<int>{0, 2, 3}));
}

void test_partition_matroid() {
    std::vector<int> group = {0, 0, 1, 1, 1};
    std::vector<int> capacity = {1, 2};
    m1une::matroid::PartitionMatroid matroid(group, capacity);
    assert(matroid.size() == 5);
    assert(matroid.group_count() == 2);
    assert(matroid.groups() == group);
    assert(matroid.capacities() == capacity);
    assert(matroid(std::vector<int>{0, 2, 4}));
    assert(!matroid(std::vector<int>{0, 1}));
    assert(!matroid(std::vector<int>{2, 3, 4}));
}

void test_graphic_matroid() {
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 3}
    };
    m1une::matroid::GraphicMatroid matroid(4, edges);
    assert(matroid.size() == 5);
    assert(matroid.vertex_count() == 4);
    assert(matroid.edges() == edges);
    assert(matroid(std::vector<int>{0, 1, 3}));
    assert(!matroid(std::vector<int>{0, 1, 2}));
    assert(!matroid(std::vector<int>{4}));
}

void test_linear_matroids() {
    std::vector<std::vector<mint>> vectors(4);
    vectors[0] = {1, 0, 0};
    vectors[1] = {0, 1, 0};
    vectors[2] = {1, 1, 0};
    vectors[3] = {0, 0, 1};
    m1une::matroid::LinearMatroid<mint> linear(vectors);
    assert(linear.size() == 4);
    assert(linear.dimension() == 3);
    assert(linear.vectors() == vectors);
    assert(linear(std::vector<int>{0, 1, 3}));
    assert(!linear(std::vector<int>{0, 1, 2}));

    std::vector<std::uint64_t> binary_vectors = {1, 2, 3, 4};
    m1une::matroid::BinaryLinearMatroid binary(binary_vectors);
    assert(binary.size() == 4);
    assert(binary.dimension() == 64);
    assert(binary.vectors() == binary_vectors);
    assert(binary(std::vector<int>{0, 1, 3}));
    assert(!binary(std::vector<int>{0, 1, 2}));

    std::mt19937 random(123456789);
    for (int test = 0; test < 100; test++) {
        const int n = 8;
        const int dimension = 6;
        using binary_mint = m1une::math::ModInt<2>;
        std::vector<std::uint64_t> bits(n);
        std::vector<std::vector<binary_mint>> field_vectors(
            n, std::vector<binary_mint>(dimension));
        for (int i = 0; i < n; i++) {
            bits[i] = random() % (1 << dimension);
            for (int bit = 0; bit < dimension; bit++) {
                field_vectors[i][bit] = binary_mint(int(bits[i] >> bit & 1));
            }
        }
        m1une::matroid::BinaryLinearMatroid binary_random(bits);
        m1une::matroid::LinearMatroid<binary_mint> field_random(field_vectors);
        for (int mask = 0; mask < (1 << n); mask++) {
            std::vector<int> subset;
            for (int i = 0; i < n; i++) {
                if (mask >> i & 1) subset.push_back(i);
            }
            assert(binary_random(subset) == field_random(subset));
        }
    }
}

int main() {
    test_uniform_matroid();
    test_partition_matroid();
    test_graphic_matroid();
    test_linear_matroids();

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
