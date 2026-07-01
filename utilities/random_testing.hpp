#ifndef M1UNE_RANDOM_TESTING_HPP
#define M1UNE_RANDOM_TESTING_HPP 1

#include <cassert>
#include <concepts>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <utility>

#include "random.hpp"

namespace m1une {
namespace utilities {

inline constexpr std::uint64_t default_random_test_seed =
    0x243f6a8885a308d3ULL;

struct RandomTestConfig {
    int trials = 1000;
    std::uint64_t seed = default_random_test_seed;
};

struct RandomTestResult {
    std::uint64_t seed = 0;
    int requested_trials = 0;
    int completed_trials = 0;
    int failed_trial = -1;

    bool passed() const {
        return failed_trial == -1;
    }

    explicit operator bool() const {
        return passed();
    }
};

struct IgnoreRandomTestFailure {
    template <class... Args>
    void operator()(Args&&...) const {}
};

namespace random_testing_detail {

template <class T>
void print_value(std::ostream& output, const T& value) {
    if constexpr (requires { output << value; }) {
        output << value;
    } else if constexpr (requires { std::begin(value); std::end(value); }) {
        output << '[';
        bool first = true;
        for (const auto& element : value) {
            if (!first) output << ", ";
            first = false;
            print_value(output, element);
        }
        output << ']';
    } else {
        output << "<unprintable>";
    }
}

template <class Function>
decltype(auto) invoke_with_trial(Function& function, Random& random, int trial) {
    if constexpr (std::invocable<Function&, Random&, int>) {
        return std::invoke(function, random, trial);
    } else {
        static_assert(std::invocable<Function&, Random&>);
        return std::invoke(function, random);
    }
}

inline RandomTestResult success_result(const RandomTestConfig& config) {
    RandomTestResult result;
    result.seed = config.seed;
    result.requested_trials = config.trials;
    result.completed_trials = config.trials;
    return result;
}

inline RandomTestResult failure_result(const RandomTestConfig& config,
                                       int failed_trial) {
    RandomTestResult result;
    result.seed = config.seed;
    result.requested_trials = config.trials;
    result.completed_trials = failed_trial;
    result.failed_trial = failed_trial;
    return result;
}

}  // namespace random_testing_detail

struct PrintRandomTestFailure {
    template <class Case, class Expected, class Actual>
    void operator()(const Case& test_case, const Expected& expected,
                    const Actual& actual, int trial,
                    std::uint64_t seed) const {
        std::cerr << "random test failed: seed=" << seed
                  << " trial=" << trial << '\n';
        std::cerr << "input: ";
        random_testing_detail::print_value(std::cerr, test_case);
        std::cerr << "\nexpected: ";
        random_testing_detail::print_value(std::cerr, expected);
        std::cerr << "\nactual: ";
        random_testing_detail::print_value(std::cerr, actual);
        std::cerr << '\n';
    }
};

// Runs a property returning bool for every generated trial.
// The property may accept (Random&) or (Random&, int trial).
template <class Property>
RandomTestResult random_test(RandomTestConfig config, Property property) {
    assert(0 <= config.trials);
    if (config.trials < 0) config.trials = 0;
    Random random(config.seed);
    for (int trial = 0; trial < config.trials; trial++) {
        static_assert(std::convertible_to<
                      decltype(random_testing_detail::invoke_with_trial(
                          property, random, trial)),
                      bool>);
        bool passed = bool(
            random_testing_detail::invoke_with_trial(property, random, trial));
        if (!passed) {
            return random_testing_detail::failure_result(config, trial);
        }
    }
    return random_testing_detail::success_result(config);
}

template <class Property>
RandomTestResult random_test(Property property) {
    return random_test(RandomTestConfig(), std::move(property));
}

// Generates a case, runs an optimized solver and an oracle on separate copies,
// and compares their results. Stops at the first mismatch.
//
// generator: (Random&) or (Random&, int trial) -> Case
// solver/oracle: (Case&) -> result
// on_failure: (case, expected, actual, trial, seed) -> void
template <class Generator, class Solver, class Oracle,
          class OnFailure = IgnoreRandomTestFailure,
          class Equal = std::equal_to<>>
RandomTestResult compare_randomly(RandomTestConfig config, Generator generator,
                                  Solver solver, Oracle oracle,
                                  OnFailure on_failure = {}, Equal equal = {}) {
    assert(0 <= config.trials);
    if (config.trials < 0) config.trials = 0;
    Random random(config.seed);

    for (int trial = 0; trial < config.trials; trial++) {
        auto test_case =
            random_testing_detail::invoke_with_trial(generator, random, trial);
        using Case = std::remove_cvref_t<decltype(test_case)>;
        static_assert(std::copy_constructible<Case>);

        Case actual_input = test_case;
        Case expected_input = test_case;
        decltype(auto) actual = std::invoke(solver, actual_input);
        decltype(auto) expected = std::invoke(oracle, expected_input);
        if (!bool(std::invoke(equal, actual, expected))) {
            std::invoke(on_failure, test_case, expected, actual, trial,
                        config.seed);
            return random_testing_detail::failure_result(config, trial);
        }
    }
    return random_testing_detail::success_result(config);
}

template <class Generator, class Solver, class Oracle>
RandomTestResult compare_randomly(Generator generator, Solver solver,
                                  Oracle oracle) {
    return compare_randomly(RandomTestConfig(), std::move(generator),
                            std::move(solver), std::move(oracle));
}

// Short contest interface. Prints failure metadata and terminates on failure.
template <class Property>
RandomTestResult stress_test(Property property, int trials = 1000,
                             std::uint64_t seed = default_random_test_seed) {
    RandomTestConfig config;
    config.trials = trials;
    config.seed = seed;
    RandomTestResult result = random_test(config, std::move(property));
    if (!result) {
        std::cerr << "random test failed: seed=" << result.seed
                  << " trial=" << result.failed_trial << '\n';
        std::abort();
    }
    return result;
}

// Short optimized-versus-brute-force interface.
template <class Generator, class Solver, class Oracle>
requires(!std::integral<std::remove_cvref_t<Solver>> &&
         !std::integral<std::remove_cvref_t<Oracle>>)
RandomTestResult stress_test(Generator generator, Solver solver, Oracle oracle,
                             int trials = 1000,
                             std::uint64_t seed = default_random_test_seed) {
    RandomTestConfig config;
    config.trials = trials;
    config.seed = seed;
    RandomTestResult result = compare_randomly(
        config, std::move(generator), std::move(solver), std::move(oracle),
        PrintRandomTestFailure());
    if (!result) std::abort();
    return result;
}

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_RANDOM_TESTING_HPP
