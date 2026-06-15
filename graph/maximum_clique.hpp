#ifndef M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP
#define M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP 1

#include <algorithm>
#include <cassert>
#include <vector>

#include "graph/graph.hpp"

namespace m1une {
namespace graph {

struct MaximumCliqueResult {
    std::vector<int> vertices;

    int size() const {
        return int(vertices.size());
    }

    bool empty() const {
        return vertices.empty();
    }
};

struct MaximumIndependentSetResult {
    std::vector<int> vertices;

    int size() const {
        return int(vertices.size());
    }

    bool empty() const {
        return vertices.empty();
    }
};

namespace detail {

struct MaximumCliqueBranchAndBound {
    using Word = unsigned long long;

    int n;
    int word_count;
    std::vector<std::vector<Word>> adjacent;
    std::vector<int> current;
    std::vector<int> best;

    explicit MaximumCliqueBranchAndBound(int n_)
        : n(n_), word_count((n_ + 63) / 64), adjacent(n_, std::vector<Word>(word_count, Word(0))) {}

    static int lowbit_index(Word x) {
        return __builtin_ctzll(x);
    }

    bool empty_bits(const std::vector<Word>& bits) const {
        for (Word x : bits) {
            if (x != Word(0)) return false;
        }
        return true;
    }

    int first_vertex(const std::vector<Word>& bits) const {
        for (int i = 0; i < word_count; i++) {
            if (bits[i] != Word(0)) return i * 64 + lowbit_index(bits[i]);
        }
        return -1;
    }

    void set_bit(std::vector<Word>& bits, int v) const {
        bits[v >> 6] |= Word(1) << (v & 63);
    }

    void clear_bit(std::vector<Word>& bits, int v) const {
        bits[v >> 6] &= ~(Word(1) << (v & 63));
    }

    bool test_bit(const std::vector<Word>& bits, int v) const {
        return (bits[v >> 6] >> (v & 63)) & Word(1);
    }

    void add_edge(int u, int v) {
        assert(0 <= u && u < n);
        assert(0 <= v && v < n);
        assert(u != v);
        adjacent[u][v >> 6] |= Word(1) << (v & 63);
        adjacent[v][u >> 6] |= Word(1) << (u & 63);
    }

    std::vector<Word> intersect(const std::vector<Word>& a, const std::vector<Word>& b) const {
        std::vector<Word> result(word_count);
        for (int i = 0; i < word_count; i++) result[i] = a[i] & b[i];
        return result;
    }

    void greedy_color(const std::vector<Word>& candidates, std::vector<int>& order, std::vector<int>& color) const {
        order.clear();
        color.clear();

        std::vector<Word> remaining = candidates;
        int color_count = 0;
        while (!empty_bits(remaining)) {
            color_count++;
            std::vector<Word> available = remaining;
            while (!empty_bits(available)) {
                int v = first_vertex(available);
                order.push_back(v);
                color.push_back(color_count);

                clear_bit(remaining, v);
                clear_bit(available, v);
                for (int i = 0; i < word_count; i++) available[i] &= ~adjacent[v][i];
            }
        }
    }

    void expand(std::vector<Word> candidates) {
        if (empty_bits(candidates)) {
            if (current.size() > best.size()) best = current;
            return;
        }

        std::vector<int> order, color;
        greedy_color(candidates, order, color);

        for (int i = int(order.size()) - 1; i >= 0; i--) {
            if (int(current.size()) + color[i] <= int(best.size())) return;

            int v = order[i];
            if (!test_bit(candidates, v)) continue;

            current.push_back(v);
            auto next = intersect(candidates, adjacent[v]);
            expand(next);
            current.pop_back();

            clear_bit(candidates, v);
        }
    }

    std::vector<int> solve() {
        std::vector<Word> candidates(word_count, Word(0));
        for (int v = 0; v < n; v++) set_bit(candidates, v);
        expand(candidates);
        std::sort(best.begin(), best.end());
        return best;
    }
};

template <class T>
std::vector<std::vector<char>> undirected_adjacency_matrix(const Graph<T>& g) {
    int n = g.size();
    std::vector<std::vector<char>> adjacent(n, std::vector<char>(n, false));
    for (const auto& e : g.edges()) {
        if (e.from == e.to) continue;
        adjacent[e.from][e.to] = true;
        adjacent[e.to][e.from] = true;
    }
    return adjacent;
}

}  // namespace detail

template <class T>
bool is_clique(const Graph<T>& g, const std::vector<int>& vertices) {
    auto adjacent = detail::undirected_adjacency_matrix(g);
    for (int v : vertices) {
        assert(0 <= v && v < g.size());
    }
    for (int i = 0; i < int(vertices.size()); i++) {
        for (int j = i + 1; j < int(vertices.size()); j++) {
            if (!adjacent[vertices[i]][vertices[j]]) return false;
        }
    }
    return true;
}

template <class T>
bool is_independent_set(const Graph<T>& g, const std::vector<int>& vertices) {
    auto adjacent = detail::undirected_adjacency_matrix(g);
    for (int v : vertices) {
        assert(0 <= v && v < g.size());
    }
    for (int i = 0; i < int(vertices.size()); i++) {
        for (int j = i + 1; j < int(vertices.size()); j++) {
            if (adjacent[vertices[i]][vertices[j]]) return false;
        }
    }
    return true;
}

template <class T>
MaximumCliqueResult maximum_clique(const Graph<T>& g) {
    auto adjacent = detail::undirected_adjacency_matrix(g);
    detail::MaximumCliqueBranchAndBound solver(g.size());
    for (int i = 0; i < g.size(); i++) {
        for (int j = i + 1; j < g.size(); j++) {
            if (adjacent[i][j]) solver.add_edge(i, j);
        }
    }
    return MaximumCliqueResult{solver.solve()};
}

template <class T>
int maximum_clique_size(const Graph<T>& g) {
    return maximum_clique(g).size();
}

template <class T>
MaximumIndependentSetResult maximum_independent_set(const Graph<T>& g) {
    auto adjacent = detail::undirected_adjacency_matrix(g);
    detail::MaximumCliqueBranchAndBound solver(g.size());
    for (int i = 0; i < g.size(); i++) {
        for (int j = i + 1; j < g.size(); j++) {
            if (!adjacent[i][j]) solver.add_edge(i, j);
        }
    }
    return MaximumIndependentSetResult{solver.solve()};
}

template <class T>
int maximum_independent_set_size(const Graph<T>& g) {
    return maximum_independent_set(g).size();
}

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_MAXIMUM_CLIQUE_HPP
