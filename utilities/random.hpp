#ifndef M1UNE_RANDOM_HPP
#define M1UNE_RANDOM_HPP 1

#include <algorithm>
#include <cassert>
#include <chrono>
#include <concepts>
#include <cstdint>
#include <functional>
#include <numeric>
#include <queue>
#include <random>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>

namespace m1une {
namespace utilities {

struct RandomGraphOptions {
    bool directed = false;
    bool allow_self_loops = false;
    bool allow_parallel_edges = false;
};

struct Random {
   private:
    std::mt19937_64 _engine;

    static unsigned long long chrono_seed() {
        return static_cast<unsigned long long>(
            std::chrono::steady_clock::now().time_since_epoch().count());
    }

    static std::uint64_t graph_edge_count(int vertex_count,
                                          const RandomGraphOptions& options) {
        std::uint64_t n = static_cast<unsigned int>(vertex_count);
        if (options.directed) {
            return options.allow_self_loops ? n * n : n * (n - 1);
        }
        return options.allow_self_loops ? n * (n + 1) / 2 : n * (n - 1) / 2;
    }

    static std::pair<int, int> decode_graph_edge(
        std::uint64_t index, int vertex_count,
        const RandomGraphOptions& options) {
        std::uint64_t n = static_cast<unsigned int>(vertex_count);
        if (options.directed) {
            std::uint64_t width = options.allow_self_loops ? n : n - 1;
            int from = int(index / width);
            int offset = int(index % width);
            int to = options.allow_self_loops || offset < from ? offset : offset + 1;
            return {from, to};
        }

        auto prefix = [&](std::uint64_t vertex) {
            if (options.allow_self_loops) {
                return vertex * (2 * n - vertex + 1) / 2;
            }
            return vertex * (2 * n - vertex - 1) / 2;
        };
        std::uint64_t low = 0;
        std::uint64_t high = n;
        while (low + 1 < high) {
            std::uint64_t middle = (low + high) / 2;
            if (prefix(middle) <= index) {
                low = middle;
            } else {
                high = middle;
            }
        }
        int from = int(low);
        int to = from + int(index - prefix(low)) +
                 (options.allow_self_loops ? 0 : 1);
        return {from, to};
    }

   public:
    Random() : _engine(chrono_seed()) {}
    explicit Random(unsigned long long seed) : _engine(seed) {}

    void seed(unsigned long long value) {
        _engine.seed(value);
    }

    std::mt19937_64& engine() {
        return _engine;
    }

    unsigned long long operator()() {
        return _engine();
    }

    long long uniform(long long l, long long r) {
        return std::uniform_int_distribution<long long>(l, r)(_engine);
    }

    unsigned long long uniform_unsigned(unsigned long long l, unsigned long long r) {
        return std::uniform_int_distribution<unsigned long long>(l, r)(_engine);
    }

    double real(double l = 0.0, double r = 1.0) {
        return std::uniform_real_distribution<double>(l, r)(_engine);
    }

    template <std::integral T>
    requires(!std::same_as<std::remove_cv_t<T>, bool>)
    std::vector<T> sequence(int size, T lower, T upper) {
        assert(0 <= size);
        assert(lower <= upper);
        if (size < 0 || upper < lower) return {};
        std::vector<T> result(size);
        if constexpr (std::signed_integral<T>) {
            std::uniform_int_distribution<long long> distribution(
                static_cast<long long>(lower), static_cast<long long>(upper));
            for (T& value : result) value = static_cast<T>(distribution(_engine));
        } else {
            std::uniform_int_distribution<unsigned long long> distribution(
                static_cast<unsigned long long>(lower),
                static_cast<unsigned long long>(upper));
            for (T& value : result) value = static_cast<T>(distribution(_engine));
        }
        return result;
    }

    std::string string(
        int length,
        std::string_view alphabet = "abcdefghijklmnopqrstuvwxyz") {
        assert(0 <= length);
        assert(length == 0 || !alphabet.empty());
        if (length < 0 || (0 < length && alphabet.empty())) return {};
        std::string result(length, '\0');
        for (char& character : result) {
            character = alphabet[uniform(0, int(alphabet.size()) - 1)];
        }
        return result;
    }

    std::vector<int> permutation(int size, int first = 0) {
        assert(0 <= size);
        if (size < 0) return {};
        std::vector<int> result(size);
        std::iota(result.begin(), result.end(), first);
        shuffle(result);
        return result;
    }

    // Returns the edges of a uniformly random labeled tree on [0, size).
    std::vector<std::pair<int, int>> tree(int size) {
        assert(0 <= size);
        if (size <= 1) return {};

        std::vector<int> prufer = sequence(size - 2, 0, size - 1);
        std::vector<int> degree(size, 1);
        for (int vertex : prufer) degree[vertex]++;
        std::priority_queue<int, std::vector<int>, std::greater<int>> leaves;
        for (int vertex = 0; vertex < size; vertex++) {
            if (degree[vertex] == 1) leaves.push(vertex);
        }

        std::vector<std::pair<int, int>> edges;
        edges.reserve(size - 1);
        for (int vertex : prufer) {
            int leaf = leaves.top();
            leaves.pop();
            edges.emplace_back(leaf, vertex);
            if (--degree[vertex] == 1) leaves.push(vertex);
        }
        int first = leaves.top();
        leaves.pop();
        edges.emplace_back(first, leaves.top());

        shuffle(edges);
        for (auto& [from, to] : edges) {
            if (uniform(0, 1)) std::swap(from, to);
        }
        return edges;
    }

    // Returns m random edges on [0, vertex_count). By default the result is
    // a simple undirected graph without self-loops.
    std::vector<std::pair<int, int>> graph(
        int vertex_count, int edge_count,
        RandomGraphOptions options = {}) {
        assert(0 <= vertex_count);
        assert(0 <= edge_count);
        if (vertex_count < 0 || edge_count < 0) return {};
        if (edge_count == 0) return {};
        assert(0 < vertex_count);
        if (vertex_count == 0) return {};
        if (!options.allow_self_loops) {
            assert(2 <= vertex_count || edge_count == 0);
            if (vertex_count < 2) return {};
        }

        std::vector<std::pair<int, int>> edges;
        edges.reserve(edge_count);
        if (options.allow_parallel_edges) {
            for (int edge = 0; edge < edge_count; edge++) {
                int from = int(uniform(0, vertex_count - 1));
                int to;
                if (options.allow_self_loops) {
                    to = int(uniform(0, vertex_count - 1));
                } else {
                    to = int(uniform(0, vertex_count - 2));
                    if (from <= to) to++;
                }
                if (!options.directed && to < from) std::swap(from, to);
                edges.emplace_back(from, to);
            }
            return edges;
        }

        std::uint64_t maximum = graph_edge_count(vertex_count, options);
        assert(static_cast<std::uint64_t>(edge_count) <= maximum);
        if (maximum < static_cast<std::uint64_t>(edge_count)) return {};

        std::unordered_set<std::uint64_t> selected;
        selected.reserve(static_cast<std::size_t>(edge_count) * 2 + 1);
        std::vector<std::uint64_t> indices;
        indices.reserve(edge_count);
        for (std::uint64_t current = maximum - edge_count;
             current < maximum; current++) {
            std::uint64_t candidate = uniform_unsigned(0, current);
            if (selected.contains(candidate)) candidate = current;
            selected.insert(candidate);
            indices.push_back(candidate);
        }
        for (std::uint64_t index : indices) {
            edges.push_back(decode_graph_edge(index, vertex_count, options));
        }
        return edges;
    }

    std::vector<std::pair<int, int>> directed_graph(
        int vertex_count, int edge_count,
        bool allow_self_loops = false) {
        RandomGraphOptions options;
        options.allow_self_loops = allow_self_loops;
        return directed_graph(vertex_count, edge_count, options);
    }

    std::vector<std::pair<int, int>> directed_graph(
        int vertex_count, int edge_count, RandomGraphOptions options) {
        options.directed = true;
        return graph(vertex_count, edge_count, options);
    }

    // Returns a directed acyclic graph. Vertices are randomly permuted before
    // every sampled edge is directed forward in that topological order.
    std::vector<std::pair<int, int>> dag(
        int vertex_count, int edge_count,
        RandomGraphOptions options = {}) {
        options.directed = false;
        options.allow_self_loops = false;
        std::vector<std::pair<int, int>> edges =
            graph(vertex_count, edge_count, options);
        std::vector<int> order = permutation(vertex_count);
        for (auto& [from, to] : edges) {
            from = order[from];
            to = order[to];
        }
        return edges;
    }

    template <std::integral Weight>
    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)
    std::vector<std::tuple<int, int, Weight>> weighted_tree(
        int size, Weight lower, Weight upper) {
        std::vector<std::pair<int, int>> edges = tree(size);
        std::vector<Weight> weights = sequence(int(edges.size()), lower, upper);
        std::vector<std::tuple<int, int, Weight>> result;
        result.reserve(edges.size());
        for (int index = 0; index < int(edges.size()); index++) {
            result.emplace_back(edges[index].first, edges[index].second,
                                weights[index]);
        }
        return result;
    }

    template <std::integral Weight>
    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)
    std::vector<std::tuple<int, int, Weight>> weighted_graph(
        int vertex_count, int edge_count, Weight lower, Weight upper,
        RandomGraphOptions options = {}) {
        std::vector<std::pair<int, int>> edges =
            graph(vertex_count, edge_count, options);
        std::vector<Weight> weights = sequence(int(edges.size()), lower, upper);
        std::vector<std::tuple<int, int, Weight>> result;
        result.reserve(edges.size());
        for (int index = 0; index < int(edges.size()); index++) {
            result.emplace_back(edges[index].first, edges[index].second,
                                weights[index]);
        }
        return result;
    }

    template <std::integral Weight>
    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)
    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(
        int vertex_count, int edge_count, Weight lower, Weight upper,
        bool allow_self_loops = false) {
        RandomGraphOptions options;
        options.allow_self_loops = allow_self_loops;
        return weighted_directed_graph(vertex_count, edge_count, lower, upper,
                                       options);
    }

    template <std::integral Weight>
    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)
    std::vector<std::tuple<int, int, Weight>> weighted_directed_graph(
        int vertex_count, int edge_count, Weight lower, Weight upper,
        RandomGraphOptions options) {
        options.directed = true;
        return weighted_graph(vertex_count, edge_count, lower, upper, options);
    }

    template <std::integral Weight>
    requires(!std::same_as<std::remove_cv_t<Weight>, bool>)
    std::vector<std::tuple<int, int, Weight>> weighted_dag(
        int vertex_count, int edge_count, Weight lower, Weight upper,
        RandomGraphOptions options = {}) {
        std::vector<std::pair<int, int>> edges =
            dag(vertex_count, edge_count, options);
        std::vector<Weight> weights = sequence(int(edges.size()), lower, upper);
        std::vector<std::tuple<int, int, Weight>> result;
        result.reserve(edges.size());
        for (int index = 0; index < int(edges.size()); index++) {
            result.emplace_back(edges[index].first, edges[index].second,
                                weights[index]);
        }
        return result;
    }

    template <typename T>
    void shuffle(std::vector<T>& v) {
        std::shuffle(v.begin(), v.end(), _engine);
    }

    template <typename Iterator>
    void shuffle(Iterator first, Iterator last) {
        std::shuffle(first, last, _engine);
    }

    template <typename T>
    const T& choice(const std::vector<T>& v) {
        return v[uniform(0, static_cast<long long>(v.size()) - 1)];
    }
};

}  // namespace utilities
}  // namespace m1une

#endif  // M1UNE_RANDOM_HPP
