---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/random.hpp
    title: Random
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/random_testing.test.cpp
    title: verify/utilities/random_testing.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/random_testing.hpp\"\n\n\n\n#include <cassert>\n\
    #include <concepts>\n#include <cstdint>\n#include <cstdlib>\n#include <functional>\n\
    #include <iostream>\n#include <iterator>\n#include <type_traits>\n#include <utility>\n\
    \n#line 1 \"utilities/random.hpp\"\n\n\n\n#include <algorithm>\n#line 6 \"utilities/random.hpp\"\
    \n#include <chrono>\n#line 10 \"utilities/random.hpp\"\n#include <numeric>\n#include\
    \ <queue>\n#include <random>\n#include <string>\n#include <string_view>\n#include\
    \ <tuple>\n#line 17 \"utilities/random.hpp\"\n#include <unordered_set>\n#line\
    \ 19 \"utilities/random.hpp\"\n#include <vector>\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\nstruct RandomGraphOptions {\n    bool directed = false;\n   \
    \ bool allow_self_loops = false;\n    bool allow_parallel_edges = false;\n};\n\
    \nstruct Random {\n   private:\n    std::mt19937_64 _engine;\n\n    static unsigned\
    \ long long chrono_seed() {\n        return static_cast<unsigned long long>(\n\
    \            std::chrono::steady_clock::now().time_since_epoch().count());\n \
    \   }\n\n    static std::uint64_t graph_edge_count(int vertex_count,\n       \
    \                                   const RandomGraphOptions& options) {\n   \
    \     std::uint64_t n = static_cast<unsigned int>(vertex_count);\n        if (options.directed)\
    \ {\n            return options.allow_self_loops ? n * n : n * (n - 1);\n    \
    \    }\n        return options.allow_self_loops ? n * (n + 1) / 2 : n * (n - 1)\
    \ / 2;\n    }\n\n    static std::pair<int, int> decode_graph_edge(\n        std::uint64_t\
    \ index, int vertex_count,\n        const RandomGraphOptions& options) {\n   \
    \     std::uint64_t n = static_cast<unsigned int>(vertex_count);\n        if (options.directed)\
    \ {\n            std::uint64_t width = options.allow_self_loops ? n : n - 1;\n\
    \            int from = int(index / width);\n            int offset = int(index\
    \ % width);\n            int to = options.allow_self_loops || offset < from ?\
    \ offset : offset + 1;\n            return {from, to};\n        }\n\n        auto\
    \ prefix = [&](std::uint64_t vertex) {\n            if (options.allow_self_loops)\
    \ {\n                return vertex * (2 * n - vertex + 1) / 2;\n            }\n\
    \            return vertex * (2 * n - vertex - 1) / 2;\n        };\n        std::uint64_t\
    \ low = 0;\n        std::uint64_t high = n;\n        while (low + 1 < high) {\n\
    \            std::uint64_t middle = (low + high) / 2;\n            if (prefix(middle)\
    \ <= index) {\n                low = middle;\n            } else {\n         \
    \       high = middle;\n            }\n        }\n        int from = int(low);\n\
    \        int to = from + int(index - prefix(low)) +\n                 (options.allow_self_loops\
    \ ? 0 : 1);\n        return {from, to};\n    }\n\n   public:\n    Random() : _engine(chrono_seed())\
    \ {}\n    explicit Random(unsigned long long seed) : _engine(seed) {}\n\n    void\
    \ seed(unsigned long long value) {\n        _engine.seed(value);\n    }\n\n  \
    \  std::mt19937_64& engine() {\n        return _engine;\n    }\n\n    unsigned\
    \ long long operator()() {\n        return _engine();\n    }\n\n    long long\
    \ uniform(long long l, long long r) {\n        return std::uniform_int_distribution<long\
    \ long>(l, r)(_engine);\n    }\n\n    unsigned long long uniform_unsigned(unsigned\
    \ long long l, unsigned long long r) {\n        return std::uniform_int_distribution<unsigned\
    \ long long>(l, r)(_engine);\n    }\n\n    double real(double l = 0.0, double\
    \ r = 1.0) {\n        return std::uniform_real_distribution<double>(l, r)(_engine);\n\
    \    }\n\n    template <std::integral T>\n    requires(!std::same_as<std::remove_cv_t<T>,\
    \ bool>)\n    std::vector<T> sequence(int size, T lower, T upper) {\n        assert(0\
    \ <= size);\n        assert(lower <= upper);\n        if (size < 0 || upper <\
    \ lower) return {};\n        std::vector<T> result(size);\n        if constexpr\
    \ (std::signed_integral<T>) {\n            std::uniform_int_distribution<long\
    \ long> distribution(\n                static_cast<long long>(lower), static_cast<long\
    \ long>(upper));\n            for (T& value : result) value = static_cast<T>(distribution(_engine));\n\
    \        } else {\n            std::uniform_int_distribution<unsigned long long>\
    \ distribution(\n                static_cast<unsigned long long>(lower),\n   \
    \             static_cast<unsigned long long>(upper));\n            for (T& value\
    \ : result) value = static_cast<T>(distribution(_engine));\n        }\n      \
    \  return result;\n    }\n\n    std::string string(\n        int length,\n   \
    \     std::string_view alphabet = \"abcdefghijklmnopqrstuvwxyz\") {\n        assert(0\
    \ <= length);\n        assert(length == 0 || !alphabet.empty());\n        if (length\
    \ < 0 || (0 < length && alphabet.empty())) return {};\n        std::string result(length,\
    \ '\\0');\n        for (char& character : result) {\n            character = alphabet[uniform(0,\
    \ int(alphabet.size()) - 1)];\n        }\n        return result;\n    }\n\n  \
    \  std::vector<int> permutation(int size, int first = 0) {\n        assert(0 <=\
    \ size);\n        if (size < 0) return {};\n        std::vector<int> result(size);\n\
    \        std::iota(result.begin(), result.end(), first);\n        shuffle(result);\n\
    \        return result;\n    }\n\n    // Returns the edges of a uniformly random\
    \ labeled tree on [0, size).\n    std::vector<std::pair<int, int>> tree(int size)\
    \ {\n        assert(0 <= size);\n        if (size <= 1) return {};\n\n       \
    \ std::vector<int> prufer = sequence(size - 2, 0, size - 1);\n        std::vector<int>\
    \ degree(size, 1);\n        for (int vertex : prufer) degree[vertex]++;\n    \
    \    std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;\n \
    \       for (int vertex = 0; vertex < size; vertex++) {\n            if (degree[vertex]\
    \ == 1) leaves.push(vertex);\n        }\n\n        std::vector<std::pair<int,\
    \ int>> edges;\n        edges.reserve(size - 1);\n        for (int vertex : prufer)\
    \ {\n            int leaf = leaves.top();\n            leaves.pop();\n       \
    \     edges.emplace_back(leaf, vertex);\n            if (--degree[vertex] == 1)\
    \ leaves.push(vertex);\n        }\n        int first = leaves.top();\n       \
    \ leaves.pop();\n        edges.emplace_back(first, leaves.top());\n\n        shuffle(edges);\n\
    \        for (auto& [from, to] : edges) {\n            if (uniform(0, 1)) std::swap(from,\
    \ to);\n        }\n        return edges;\n    }\n\n    // Returns m random edges\
    \ on [0, vertex_count). By default the result is\n    // a simple undirected graph\
    \ without self-loops.\n    std::vector<std::pair<int, int>> graph(\n        int\
    \ vertex_count, int edge_count,\n        RandomGraphOptions options = {}) {\n\
    \        assert(0 <= vertex_count);\n        assert(0 <= edge_count);\n      \
    \  if (vertex_count < 0 || edge_count < 0) return {};\n        if (edge_count\
    \ == 0) return {};\n        assert(0 < vertex_count);\n        if (vertex_count\
    \ == 0) return {};\n        if (!options.allow_self_loops) {\n            assert(2\
    \ <= vertex_count || edge_count == 0);\n            if (vertex_count < 2) return\
    \ {};\n        }\n\n        std::vector<std::pair<int, int>> edges;\n        edges.reserve(edge_count);\n\
    \        if (options.allow_parallel_edges) {\n            for (int edge = 0; edge\
    \ < edge_count; edge++) {\n                int from = int(uniform(0, vertex_count\
    \ - 1));\n                int to;\n                if (options.allow_self_loops)\
    \ {\n                    to = int(uniform(0, vertex_count - 1));\n           \
    \     } else {\n                    to = int(uniform(0, vertex_count - 2));\n\
    \                    if (from <= to) to++;\n                }\n              \
    \  if (!options.directed && to < from) std::swap(from, to);\n                edges.emplace_back(from,\
    \ to);\n            }\n            return edges;\n        }\n\n        std::uint64_t\
    \ maximum = graph_edge_count(vertex_count, options);\n        assert(static_cast<std::uint64_t>(edge_count)\
    \ <= maximum);\n        if (maximum < static_cast<std::uint64_t>(edge_count))\
    \ return {};\n\n        std::unordered_set<std::uint64_t> selected;\n        selected.reserve(static_cast<std::size_t>(edge_count)\
    \ * 2 + 1);\n        std::vector<std::uint64_t> indices;\n        indices.reserve(edge_count);\n\
    \        for (std::uint64_t current = maximum - edge_count;\n             current\
    \ < maximum; current++) {\n            std::uint64_t candidate = uniform_unsigned(0,\
    \ current);\n            if (selected.contains(candidate)) candidate = current;\n\
    \            selected.insert(candidate);\n            indices.push_back(candidate);\n\
    \        }\n        for (std::uint64_t index : indices) {\n            edges.push_back(decode_graph_edge(index,\
    \ vertex_count, options));\n        }\n        return edges;\n    }\n\n    std::vector<std::pair<int,\
    \ int>> directed_graph(\n        int vertex_count, int edge_count,\n        bool\
    \ allow_self_loops = false) {\n        RandomGraphOptions options;\n        options.allow_self_loops\
    \ = allow_self_loops;\n        return directed_graph(vertex_count, edge_count,\
    \ options);\n    }\n\n    std::vector<std::pair<int, int>> directed_graph(\n \
    \       int vertex_count, int edge_count, RandomGraphOptions options) {\n    \
    \    options.directed = true;\n        return graph(vertex_count, edge_count,\
    \ options);\n    }\n\n    // Returns a directed acyclic graph. Vertices are randomly\
    \ permuted before\n    // every sampled edge is directed forward in that topological\
    \ order.\n    std::vector<std::pair<int, int>> dag(\n        int vertex_count,\
    \ int edge_count,\n        RandomGraphOptions options = {}) {\n        options.directed\
    \ = false;\n        options.allow_self_loops = false;\n        std::vector<std::pair<int,\
    \ int>> edges =\n            graph(vertex_count, edge_count, options);\n     \
    \   std::vector<int> order = permutation(vertex_count);\n        for (auto& [from,\
    \ to] : edges) {\n            from = order[from];\n            to = order[to];\n\
    \        }\n        return edges;\n    }\n\n    template <std::integral Weight>\n\
    \    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)\n    std::vector<std::tuple<int,\
    \ int, Weight>> weighted_tree(\n        int size, Weight lower, Weight upper)\
    \ {\n        std::vector<std::pair<int, int>> edges = tree(size);\n        std::vector<Weight>\
    \ weights = sequence(int(edges.size()), lower, upper);\n        std::vector<std::tuple<int,\
    \ int, Weight>> result;\n        result.reserve(edges.size());\n        for (int\
    \ index = 0; index < int(edges.size()); index++) {\n            result.emplace_back(edges[index].first,\
    \ edges[index].second,\n                                weights[index]);\n   \
    \     }\n        return result;\n    }\n\n    template <std::integral Weight>\n\
    \    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)\n    std::vector<std::tuple<int,\
    \ int, Weight>> weighted_graph(\n        int vertex_count, int edge_count, Weight\
    \ lower, Weight upper,\n        RandomGraphOptions options = {}) {\n        std::vector<std::pair<int,\
    \ int>> edges =\n            graph(vertex_count, edge_count, options);\n     \
    \   std::vector<Weight> weights = sequence(int(edges.size()), lower, upper);\n\
    \        std::vector<std::tuple<int, int, Weight>> result;\n        result.reserve(edges.size());\n\
    \        for (int index = 0; index < int(edges.size()); index++) {\n         \
    \   result.emplace_back(edges[index].first, edges[index].second,\n           \
    \                     weights[index]);\n        }\n        return result;\n  \
    \  }\n\n    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(\n\
    \        int vertex_count, int edge_count, Weight lower, Weight upper,\n     \
    \   bool allow_self_loops = false) {\n        RandomGraphOptions options;\n  \
    \      options.allow_self_loops = allow_self_loops;\n        return weighted_directed_graph(vertex_count,\
    \ edge_count, lower, upper,\n                                       options);\n\
    \    }\n\n    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(\n\
    \        int vertex_count, int edge_count, Weight lower, Weight upper,\n     \
    \   RandomGraphOptions options) {\n        options.directed = true;\n        return\
    \ weighted_graph(vertex_count, edge_count, lower, upper, options);\n    }\n\n\
    \    template <std::integral Weight>\n    requires(!std::same_as<std::remove_cv_t<Weight>,\
    \ bool>)\n    std::vector<std::tuple<int, int, Weight>> weighted_dag(\n      \
    \  int vertex_count, int edge_count, Weight lower, Weight upper,\n        RandomGraphOptions\
    \ options = {}) {\n        std::vector<std::pair<int, int>> edges =\n        \
    \    dag(vertex_count, edge_count, options);\n        std::vector<Weight> weights\
    \ = sequence(int(edges.size()), lower, upper);\n        std::vector<std::tuple<int,\
    \ int, Weight>> result;\n        result.reserve(edges.size());\n        for (int\
    \ index = 0; index < int(edges.size()); index++) {\n            result.emplace_back(edges[index].first,\
    \ edges[index].second,\n                                weights[index]);\n   \
    \     }\n        return result;\n    }\n\n    template <typename T>\n    void\
    \ shuffle(std::vector<T>& v) {\n        std::shuffle(v.begin(), v.end(), _engine);\n\
    \    }\n\n    template <typename Iterator>\n    void shuffle(Iterator first, Iterator\
    \ last) {\n        std::shuffle(first, last, _engine);\n    }\n\n    template\
    \ <typename T>\n    const T& choice(const std::vector<T>& v) {\n        return\
    \ v[uniform(0, static_cast<long long>(v.size()) - 1)];\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n#line 15 \"utilities/random_testing.hpp\"\
    \n\nnamespace m1une {\nnamespace utilities {\n\ninline constexpr std::uint64_t\
    \ default_random_test_seed =\n    0x243f6a8885a308d3ULL;\n\nstruct RandomTestConfig\
    \ {\n    int trials = 1000;\n    std::uint64_t seed = default_random_test_seed;\n\
    };\n\nstruct RandomTestResult {\n    std::uint64_t seed = 0;\n    int requested_trials\
    \ = 0;\n    int completed_trials = 0;\n    int failed_trial = -1;\n\n    bool\
    \ passed() const {\n        return failed_trial == -1;\n    }\n\n    explicit\
    \ operator bool() const {\n        return passed();\n    }\n};\n\nstruct IgnoreRandomTestFailure\
    \ {\n    template <class... Args>\n    void operator()(Args&&...) const {}\n};\n\
    \nnamespace random_testing_detail {\n\ntemplate <class T>\nvoid print_value(std::ostream&\
    \ output, const T& value) {\n    if constexpr (requires { output << value; })\
    \ {\n        output << value;\n    } else if constexpr (requires { std::begin(value);\
    \ std::end(value); }) {\n        output << '[';\n        bool first = true;\n\
    \        for (const auto& element : value) {\n            if (!first) output <<\
    \ \", \";\n            first = false;\n            print_value(output, element);\n\
    \        }\n        output << ']';\n    } else {\n        output << \"<unprintable>\"\
    ;\n    }\n}\n\ntemplate <class Function>\ndecltype(auto) invoke_with_trial(Function&\
    \ function, Random& random, int trial) {\n    if constexpr (std::invocable<Function&,\
    \ Random&, int>) {\n        return std::invoke(function, random, trial);\n   \
    \ } else {\n        static_assert(std::invocable<Function&, Random&>);\n     \
    \   return std::invoke(function, random);\n    }\n}\n\ninline RandomTestResult\
    \ success_result(const RandomTestConfig& config) {\n    RandomTestResult result;\n\
    \    result.seed = config.seed;\n    result.requested_trials = config.trials;\n\
    \    result.completed_trials = config.trials;\n    return result;\n}\n\ninline\
    \ RandomTestResult failure_result(const RandomTestConfig& config,\n          \
    \                             int failed_trial) {\n    RandomTestResult result;\n\
    \    result.seed = config.seed;\n    result.requested_trials = config.trials;\n\
    \    result.completed_trials = failed_trial;\n    result.failed_trial = failed_trial;\n\
    \    return result;\n}\n\n}  // namespace random_testing_detail\n\nstruct PrintRandomTestFailure\
    \ {\n    template <class Case, class Expected, class Actual>\n    void operator()(const\
    \ Case& test_case, const Expected& expected,\n                    const Actual&\
    \ actual, int trial,\n                    std::uint64_t seed) const {\n      \
    \  std::cerr << \"random test failed: seed=\" << seed\n                  << \"\
    \ trial=\" << trial << '\\n';\n        std::cerr << \"input: \";\n        random_testing_detail::print_value(std::cerr,\
    \ test_case);\n        std::cerr << \"\\nexpected: \";\n        random_testing_detail::print_value(std::cerr,\
    \ expected);\n        std::cerr << \"\\nactual: \";\n        random_testing_detail::print_value(std::cerr,\
    \ actual);\n        std::cerr << '\\n';\n    }\n};\n\n// Runs a property returning\
    \ bool for every generated trial.\n// The property may accept (Random&) or (Random&,\
    \ int trial).\ntemplate <class Property>\nRandomTestResult random_test(RandomTestConfig\
    \ config, Property property) {\n    assert(0 <= config.trials);\n    if (config.trials\
    \ < 0) config.trials = 0;\n    Random random(config.seed);\n    for (int trial\
    \ = 0; trial < config.trials; trial++) {\n        static_assert(std::convertible_to<\n\
    \                      decltype(random_testing_detail::invoke_with_trial(\n  \
    \                        property, random, trial)),\n                      bool>);\n\
    \        bool passed = bool(\n            random_testing_detail::invoke_with_trial(property,\
    \ random, trial));\n        if (!passed) {\n            return random_testing_detail::failure_result(config,\
    \ trial);\n        }\n    }\n    return random_testing_detail::success_result(config);\n\
    }\n\ntemplate <class Property>\nRandomTestResult random_test(Property property)\
    \ {\n    return random_test(RandomTestConfig(), std::move(property));\n}\n\n//\
    \ Generates a case, runs an optimized solver and an oracle on separate copies,\n\
    // and compares their results. Stops at the first mismatch.\n//\n// generator:\
    \ (Random&) or (Random&, int trial) -> Case\n// solver/oracle: (Case&) -> result\n\
    // on_failure: (case, expected, actual, trial, seed) -> void\ntemplate <class\
    \ Generator, class Solver, class Oracle,\n          class OnFailure = IgnoreRandomTestFailure,\n\
    \          class Equal = std::equal_to<>>\nRandomTestResult compare_randomly(RandomTestConfig\
    \ config, Generator generator,\n                                  Solver solver,\
    \ Oracle oracle,\n                                  OnFailure on_failure = {},\
    \ Equal equal = {}) {\n    assert(0 <= config.trials);\n    if (config.trials\
    \ < 0) config.trials = 0;\n    Random random(config.seed);\n\n    for (int trial\
    \ = 0; trial < config.trials; trial++) {\n        auto test_case =\n         \
    \   random_testing_detail::invoke_with_trial(generator, random, trial);\n    \
    \    using Case = std::remove_cvref_t<decltype(test_case)>;\n        static_assert(std::copy_constructible<Case>);\n\
    \n        Case actual_input = test_case;\n        Case expected_input = test_case;\n\
    \        decltype(auto) actual = std::invoke(solver, actual_input);\n        decltype(auto)\
    \ expected = std::invoke(oracle, expected_input);\n        if (!bool(std::invoke(equal,\
    \ actual, expected))) {\n            std::invoke(on_failure, test_case, expected,\
    \ actual, trial,\n                        config.seed);\n            return random_testing_detail::failure_result(config,\
    \ trial);\n        }\n    }\n    return random_testing_detail::success_result(config);\n\
    }\n\ntemplate <class Generator, class Solver, class Oracle>\nRandomTestResult\
    \ compare_randomly(Generator generator, Solver solver,\n                     \
    \             Oracle oracle) {\n    return compare_randomly(RandomTestConfig(),\
    \ std::move(generator),\n                            std::move(solver), std::move(oracle));\n\
    }\n\n// Short contest interface. Prints failure metadata and terminates on failure.\n\
    template <class Property>\nRandomTestResult stress_test(Property property, int\
    \ trials = 1000,\n                             std::uint64_t seed = default_random_test_seed)\
    \ {\n    RandomTestConfig config;\n    config.trials = trials;\n    config.seed\
    \ = seed;\n    RandomTestResult result = random_test(config, std::move(property));\n\
    \    if (!result) {\n        std::cerr << \"random test failed: seed=\" << result.seed\n\
    \                  << \" trial=\" << result.failed_trial << '\\n';\n        std::abort();\n\
    \    }\n    return result;\n}\n\n// Short optimized-versus-brute-force interface.\n\
    template <class Generator, class Solver, class Oracle>\nrequires(!std::integral<std::remove_cvref_t<Solver>>\
    \ &&\n         !std::integral<std::remove_cvref_t<Oracle>>)\nRandomTestResult\
    \ stress_test(Generator generator, Solver solver, Oracle oracle,\n           \
    \                  int trials = 1000,\n                             std::uint64_t\
    \ seed = default_random_test_seed) {\n    RandomTestConfig config;\n    config.trials\
    \ = trials;\n    config.seed = seed;\n    RandomTestResult result = compare_randomly(\n\
    \        config, std::move(generator), std::move(solver), std::move(oracle),\n\
    \        PrintRandomTestFailure());\n    if (!result) std::abort();\n    return\
    \ result;\n}\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_RANDOM_TESTING_HPP\n#define M1UNE_RANDOM_TESTING_HPP 1\n\n\
    #include <cassert>\n#include <concepts>\n#include <cstdint>\n#include <cstdlib>\n\
    #include <functional>\n#include <iostream>\n#include <iterator>\n#include <type_traits>\n\
    #include <utility>\n\n#include \"random.hpp\"\n\nnamespace m1une {\nnamespace\
    \ utilities {\n\ninline constexpr std::uint64_t default_random_test_seed =\n \
    \   0x243f6a8885a308d3ULL;\n\nstruct RandomTestConfig {\n    int trials = 1000;\n\
    \    std::uint64_t seed = default_random_test_seed;\n};\n\nstruct RandomTestResult\
    \ {\n    std::uint64_t seed = 0;\n    int requested_trials = 0;\n    int completed_trials\
    \ = 0;\n    int failed_trial = -1;\n\n    bool passed() const {\n        return\
    \ failed_trial == -1;\n    }\n\n    explicit operator bool() const {\n       \
    \ return passed();\n    }\n};\n\nstruct IgnoreRandomTestFailure {\n    template\
    \ <class... Args>\n    void operator()(Args&&...) const {}\n};\n\nnamespace random_testing_detail\
    \ {\n\ntemplate <class T>\nvoid print_value(std::ostream& output, const T& value)\
    \ {\n    if constexpr (requires { output << value; }) {\n        output << value;\n\
    \    } else if constexpr (requires { std::begin(value); std::end(value); }) {\n\
    \        output << '[';\n        bool first = true;\n        for (const auto&\
    \ element : value) {\n            if (!first) output << \", \";\n            first\
    \ = false;\n            print_value(output, element);\n        }\n        output\
    \ << ']';\n    } else {\n        output << \"<unprintable>\";\n    }\n}\n\ntemplate\
    \ <class Function>\ndecltype(auto) invoke_with_trial(Function& function, Random&\
    \ random, int trial) {\n    if constexpr (std::invocable<Function&, Random&, int>)\
    \ {\n        return std::invoke(function, random, trial);\n    } else {\n    \
    \    static_assert(std::invocable<Function&, Random&>);\n        return std::invoke(function,\
    \ random);\n    }\n}\n\ninline RandomTestResult success_result(const RandomTestConfig&\
    \ config) {\n    RandomTestResult result;\n    result.seed = config.seed;\n  \
    \  result.requested_trials = config.trials;\n    result.completed_trials = config.trials;\n\
    \    return result;\n}\n\ninline RandomTestResult failure_result(const RandomTestConfig&\
    \ config,\n                                       int failed_trial) {\n    RandomTestResult\
    \ result;\n    result.seed = config.seed;\n    result.requested_trials = config.trials;\n\
    \    result.completed_trials = failed_trial;\n    result.failed_trial = failed_trial;\n\
    \    return result;\n}\n\n}  // namespace random_testing_detail\n\nstruct PrintRandomTestFailure\
    \ {\n    template <class Case, class Expected, class Actual>\n    void operator()(const\
    \ Case& test_case, const Expected& expected,\n                    const Actual&\
    \ actual, int trial,\n                    std::uint64_t seed) const {\n      \
    \  std::cerr << \"random test failed: seed=\" << seed\n                  << \"\
    \ trial=\" << trial << '\\n';\n        std::cerr << \"input: \";\n        random_testing_detail::print_value(std::cerr,\
    \ test_case);\n        std::cerr << \"\\nexpected: \";\n        random_testing_detail::print_value(std::cerr,\
    \ expected);\n        std::cerr << \"\\nactual: \";\n        random_testing_detail::print_value(std::cerr,\
    \ actual);\n        std::cerr << '\\n';\n    }\n};\n\n// Runs a property returning\
    \ bool for every generated trial.\n// The property may accept (Random&) or (Random&,\
    \ int trial).\ntemplate <class Property>\nRandomTestResult random_test(RandomTestConfig\
    \ config, Property property) {\n    assert(0 <= config.trials);\n    if (config.trials\
    \ < 0) config.trials = 0;\n    Random random(config.seed);\n    for (int trial\
    \ = 0; trial < config.trials; trial++) {\n        static_assert(std::convertible_to<\n\
    \                      decltype(random_testing_detail::invoke_with_trial(\n  \
    \                        property, random, trial)),\n                      bool>);\n\
    \        bool passed = bool(\n            random_testing_detail::invoke_with_trial(property,\
    \ random, trial));\n        if (!passed) {\n            return random_testing_detail::failure_result(config,\
    \ trial);\n        }\n    }\n    return random_testing_detail::success_result(config);\n\
    }\n\ntemplate <class Property>\nRandomTestResult random_test(Property property)\
    \ {\n    return random_test(RandomTestConfig(), std::move(property));\n}\n\n//\
    \ Generates a case, runs an optimized solver and an oracle on separate copies,\n\
    // and compares their results. Stops at the first mismatch.\n//\n// generator:\
    \ (Random&) or (Random&, int trial) -> Case\n// solver/oracle: (Case&) -> result\n\
    // on_failure: (case, expected, actual, trial, seed) -> void\ntemplate <class\
    \ Generator, class Solver, class Oracle,\n          class OnFailure = IgnoreRandomTestFailure,\n\
    \          class Equal = std::equal_to<>>\nRandomTestResult compare_randomly(RandomTestConfig\
    \ config, Generator generator,\n                                  Solver solver,\
    \ Oracle oracle,\n                                  OnFailure on_failure = {},\
    \ Equal equal = {}) {\n    assert(0 <= config.trials);\n    if (config.trials\
    \ < 0) config.trials = 0;\n    Random random(config.seed);\n\n    for (int trial\
    \ = 0; trial < config.trials; trial++) {\n        auto test_case =\n         \
    \   random_testing_detail::invoke_with_trial(generator, random, trial);\n    \
    \    using Case = std::remove_cvref_t<decltype(test_case)>;\n        static_assert(std::copy_constructible<Case>);\n\
    \n        Case actual_input = test_case;\n        Case expected_input = test_case;\n\
    \        decltype(auto) actual = std::invoke(solver, actual_input);\n        decltype(auto)\
    \ expected = std::invoke(oracle, expected_input);\n        if (!bool(std::invoke(equal,\
    \ actual, expected))) {\n            std::invoke(on_failure, test_case, expected,\
    \ actual, trial,\n                        config.seed);\n            return random_testing_detail::failure_result(config,\
    \ trial);\n        }\n    }\n    return random_testing_detail::success_result(config);\n\
    }\n\ntemplate <class Generator, class Solver, class Oracle>\nRandomTestResult\
    \ compare_randomly(Generator generator, Solver solver,\n                     \
    \             Oracle oracle) {\n    return compare_randomly(RandomTestConfig(),\
    \ std::move(generator),\n                            std::move(solver), std::move(oracle));\n\
    }\n\n// Short contest interface. Prints failure metadata and terminates on failure.\n\
    template <class Property>\nRandomTestResult stress_test(Property property, int\
    \ trials = 1000,\n                             std::uint64_t seed = default_random_test_seed)\
    \ {\n    RandomTestConfig config;\n    config.trials = trials;\n    config.seed\
    \ = seed;\n    RandomTestResult result = random_test(config, std::move(property));\n\
    \    if (!result) {\n        std::cerr << \"random test failed: seed=\" << result.seed\n\
    \                  << \" trial=\" << result.failed_trial << '\\n';\n        std::abort();\n\
    \    }\n    return result;\n}\n\n// Short optimized-versus-brute-force interface.\n\
    template <class Generator, class Solver, class Oracle>\nrequires(!std::integral<std::remove_cvref_t<Solver>>\
    \ &&\n         !std::integral<std::remove_cvref_t<Oracle>>)\nRandomTestResult\
    \ stress_test(Generator generator, Solver solver, Oracle oracle,\n           \
    \                  int trials = 1000,\n                             std::uint64_t\
    \ seed = default_random_test_seed) {\n    RandomTestConfig config;\n    config.trials\
    \ = trials;\n    config.seed = seed;\n    RandomTestResult result = compare_randomly(\n\
    \        config, std::move(generator), std::move(solver), std::move(oracle),\n\
    \        PrintRandomTestFailure());\n    if (!result) std::abort();\n    return\
    \ result;\n}\n\n}  // namespace utilities\n}  // namespace m1une\n\n#endif  //\
    \ M1UNE_RANDOM_TESTING_HPP\n"
  dependsOn:
  - utilities/random.hpp
  isVerificationFile: false
  path: utilities/random_testing.hpp
  requiredBy: []
  timestamp: '2026-07-01 22:42:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/random_testing.test.cpp
documentation_of: utilities/random_testing.hpp
layout: document
title: Random Testing
---

## Overview

This header removes the repetitive loop around competitive-programming stress
tests. It supports two workflows:

* `random_test` repeatedly checks a Boolean property;
* `compare_randomly` generates small cases and compares an optimized solver
  against a brute-force oracle.

Testing stops at the first failure. The returned seed and zero-based trial make
the failure reproducible.

## Quick Use During a Contest

```cpp
template <class Property>
RandomTestResult stress_test(
    Property property,
    int trials = 1000,
    std::uint64_t seed = default_random_test_seed);

template <class Generator, class Solver, class Oracle>
RandomTestResult stress_test(
    Generator generator,
    Solver solver,
    Oracle oracle,
    int trials = 1000,
    std::uint64_t seed = default_random_test_seed);
```

The shortest interface needs only one lambda:

```cpp
stress_test([](Random& random) {
    auto input = generate_small_case(random);
    return solve(input) == brute(input);
});
```

Or keep generation and the two solutions separate:

```cpp
stress_test(generate_small_case, solve, brute);
```

The included `Random` helpers keep generators short:

```cpp
stress_test([](Random& rng) {
    auto values = rng.sequence(20, -10, 10);
    auto text = rng.string(20, "abc");
    auto tree = rng.tree(20);
    auto graph = rng.graph(20, 30);
    auto weighted_graph = rng.weighted_graph(20, 30, -10, 10);
    auto dag = rng.dag(20, 30);
    return check(values, text, tree, graph, weighted_graph, dag);
});
```

Both forms run 1000 trials with a fixed default seed. Optional trailing
arguments select the trial count and seed:

```cpp
stress_test(generate_small_case, solve, brute, 10000, 123456789);
```

`stress_test` returns normally after every test passes. On failure, it prints
the seed and trial and then calls `std::abort`. The three-function form also
prints the input, expected result, and actual result when they are streamable
or iterable. This means the call does not need an `assert` or result check.

## Configuration and Result

```cpp
struct RandomTestConfig {
    int trials = 1000;
    std::uint64_t seed = default_random_test_seed;
};

struct RandomTestResult {
    std::uint64_t seed;
    int requested_trials;
    int completed_trials;
    int failed_trial;

    bool passed() const;
    explicit operator bool() const;
};
```

The fixed default seed makes ordinary runs deterministic. Supply a different
seed when exploring more cases. On success, `completed_trials` equals
`requested_trials` and `failed_trial` is `-1`. On failure,
`completed_trials == failed_trial` is the number of earlier successful trials.

## Property Tests

```cpp
template <class Property>
RandomTestResult random_test(
    RandomTestConfig config,
    Property property);
```

`random_test(property)` is shorthand using the default configuration.

The property may have either signature and must return something convertible
to `bool`:

```cpp
bool property(Random& random);
bool property(Random& random, int trial);
```

Each call advances the same seeded `Random` generator.

## Optimized Solver Against Brute Force

```cpp
template <class Generator, class Solver, class Oracle,
          class OnFailure = IgnoreRandomTestFailure,
          class Equal = std::equal_to<>>
RandomTestResult compare_randomly(
    RandomTestConfig config,
    Generator generator,
    Solver solver,
    Oracle oracle,
    OnFailure on_failure = {},
    Equal equal = {});
```

`compare_randomly(generator, solver, oracle)` is shorthand using the default
configuration. Unlike `stress_test`, the lower-level functions return a failed
result instead of terminating the program.

`generator` receives `Random&` and optionally the trial number. Its result must
be copyable. The harness gives separate copies to `solver` and `oracle`, so
either function may mutate its input. Results are compared with `equal`.

On a mismatch, `on_failure` is called as follows before testing stops:

```cpp
on_failure(test_case, expected, actual, trial, seed);
```

The callback is optional. Use it to print the counterexample in the format most
helpful for the current problem.

If a failure reports seed `S` and trial `T`, rerun with the same seed and at
least `T + 1` trials. Generation is deterministic as long as the generator
makes the same sequence of random calls.

## Example

```cpp
#include "utilities/random_testing.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
    using namespace m1une::utilities;
    RandomTestConfig config;
    config.trials = 10000;
    config.seed = 123456789;

    auto result = compare_randomly(
        config,
        [](Random& random) {
            int n = int(random.uniform(0, 10));
            std::vector<int> values(n);
            for (int& value : values) value = int(random.uniform(-5, 5));
            return values;
        },
        [](std::vector<int>& values) {
            std::sort(values.begin(), values.end());
            return values;
        },
        [](std::vector<int>& values) {
            // Replace this with a deliberately simple oracle for the problem.
            for (int i = 0; i < int(values.size()); i++) {
                for (int j = i + 1; j < int(values.size()); j++) {
                    if (values[j] < values[i]) std::swap(values[i], values[j]);
                }
            }
            return values;
        },
        [](const auto& input, const auto& expected, const auto& actual,
           int trial, std::uint64_t seed) {
            std::cerr << "mismatch: seed=" << seed << " trial=" << trial
                      << " size=" << input.size() << "\n";
            (void)expected;
            (void)actual;
        });

    return result ? 0 : 1;
}
```

The harness adds only $O(1)$ work around each trial, excluding case copies and
the supplied generator, solvers, comparison, and failure callback.
