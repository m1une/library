#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "../../utilities/random_testing.hpp"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

#ifndef NDEBUG
void test_properties() {
    using namespace m1une::utilities;

    RandomTestConfig config;
    config.trials = 100;
    config.seed = 12345;
    RandomTestResult success = random_test(config, [](Random& random) {
        long long value = random.uniform(-1000, 1000);
        return value * value >= 0;
    });
    assert(success.passed());
    assert(bool(success));
    assert(success.completed_trials == 100);
    assert(success.failed_trial == -1);
    assert(success.seed == config.seed);

    RandomTestResult failure = random_test(
        config, [](Random&, int trial) { return trial != 17; });
    assert(!failure.passed());
    assert(!bool(failure));
    assert(failure.completed_trials == 17);
    assert(failure.failed_trial == 17);

    auto shorthand = random_test([](Random&, int trial) { return trial < 1000; });
    assert(shorthand.passed());
    auto required = stress_test(
        [](Random&, int trial) { return trial < 25; }, 25, 777);
    assert(required.passed());
    assert(required.seed == 777);
}

void test_comparison() {
    using namespace m1une::utilities;

    RandomTestConfig config;
    config.trials = 500;
    config.seed = 67890;
    auto success = compare_randomly(
        config,
        [](Random& random) {
            int size = int(random.uniform(0, 20));
            std::vector<int> values(size);
            for (int& value : values) value = int(random.uniform(-20, 20));
            return values;
        },
        [](std::vector<int>& values) {
            std::sort(values.begin(), values.end());
            return values;
        },
        [](std::vector<int>& values) {
            for (int i = 0; i < int(values.size()); i++) {
                for (int j = i + 1; j < int(values.size()); j++) {
                    if (values[j] < values[i]) std::swap(values[i], values[j]);
                }
            }
            return values;
        });
    assert(success.passed());

    auto mutation_isolated = compare_randomly(
        config,
        [](Random& random) {
            int size = int(random.uniform(0, 20));
            std::vector<int> values(size);
            for (int& value : values) value = int(random.uniform(-20, 20));
            return values;
        },
        [](std::vector<int>& values) {
            int sum = std::accumulate(values.begin(), values.end(), 0);
            values.clear();
            return sum;
        },
        [](std::vector<int>& values) {
            return std::accumulate(values.begin(), values.end(), 0);
        });
    assert(mutation_isolated.passed());

    auto quick = stress_test(
        [](Random& random) { return int(random.uniform(-10, 10)); },
        [](int& value) { return value * value; },
        [](int& value) {
            int magnitude = value < 0 ? -value : value;
            int result = 0;
            for (int i = 0; i < magnitude; i++) result += magnitude;
            return result;
        },
        50, 999);
    assert(quick.passed());

    int callback_count = 0;
    int callback_trial = -1;
    int callback_case = -1;
    int callback_expected = -1;
    int callback_actual = -1;
    std::uint64_t callback_seed = 0;
    auto failure = compare_randomly(
        config,
        [](Random&, int trial) { return trial; },
        [](int& value) { return value == 23 ? value + 1 : value; },
        [](int& value) { return value; },
        [&](int input, int expected, int actual, int trial,
            std::uint64_t seed) {
            callback_count++;
            callback_trial = trial;
            callback_case = input;
            callback_expected = expected;
            callback_actual = actual;
            callback_seed = seed;
        });
    assert(failure.failed_trial == 23);
    assert(callback_count == 1);
    assert(callback_trial == 23);
    assert(callback_case == 23);
    assert(callback_expected == 23);
    assert(callback_actual == 24);
    assert(callback_seed == config.seed);

    RandomTestConfig empty_config;
    empty_config.trials = 0;
    auto empty = random_test(empty_config, [](Random&) { return false; });
    assert(empty.passed());
    assert(empty.completed_trials == 0);
}
#endif

int main() {
#ifndef NDEBUG
    test_properties();
    test_comparison();
#endif

    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b << '\n';
}
