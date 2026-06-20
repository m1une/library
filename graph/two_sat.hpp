#ifndef M1UNE_GRAPH_TWO_SAT_HPP
#define M1UNE_GRAPH_TWO_SAT_HPP 1

#include <cassert>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace graph {

// A 2-SAT solver using iterative strongly connected components.
struct TwoSat {
   private:
    struct Csr {
        std::vector<int> start;
        std::vector<int> to;
    };

    int _n;
    std::vector<std::pair<int, int>> _edges;
    bool _solved;
    bool _satisfiable;
    std::vector<bool> _answer;

    int node(int variable, bool value) const {
        assert(0 <= variable && variable < _n);
        return 2 * variable + int(value);
    }

    void add_edge(int from, int to) {
        _edges.emplace_back(from, to);
        _solved = false;
        _answer.clear();
    }

    Csr build_csr(bool reverse) const {
        int vertices = 2 * _n;
        Csr graph;
        graph.start.assign(vertices + 1, 0);
        graph.to.resize(_edges.size());

        for (auto [from, to] : _edges) {
            int source = reverse ? to : from;
            graph.start[source + 1]++;
        }
        for (int v = 0; v < vertices; v++) {
            graph.start[v + 1] += graph.start[v];
        }

        std::vector<int> cursor = graph.start;
        for (auto [from, to] : _edges) {
            int source = reverse ? to : from;
            int target = reverse ? from : to;
            graph.to[cursor[source]++] = target;
        }
        return graph;
    }

   public:
    TwoSat() : TwoSat(0) {}

    explicit TwoSat(int n)
        : _n(n), _solved(false), _satisfiable(false) {
        assert(0 <= n);
        assert(n <= std::numeric_limits<int>::max() / 2);
    }

    int size() const {
        return _n;
    }

    bool empty() const {
        return _n == 0;
    }

    // Reserves space for approximately `clause_count` two-literal clauses.
    void reserve(std::size_t clause_count) {
        assert(clause_count <= std::size_t(std::numeric_limits<int>::max()) / 2);
        _edges.reserve(2 * clause_count);
    }

    // Adds (variable i == f) OR (variable j == g).
    void add_clause(int i, bool f, int j, bool g) {
        int a = node(i, f);
        int b = node(j, g);
        add_edge(a ^ 1, b);
        add_edge(b ^ 1, a);
    }

    // Adds (variable i == f) => (variable j == g).
    void add_implication(int i, bool f, int j, bool g) {
        add_clause(i, !f, j, g);
    }

    // Forces variable i to equal value.
    void set_value(int i, bool value) {
        add_clause(i, value, i, value);
    }

    // Forces variables i and j to have equal values.
    void add_equal(int i, int j) {
        add_clause(i, false, j, true);
        add_clause(i, true, j, false);
    }

    // Forces variables i and j to have different values.
    void add_not_equal(int i, int j) {
        add_clause(i, true, j, true);
        add_clause(i, false, j, false);
    }

    bool satisfiable() {
        if (_solved) return _satisfiable;
        assert(_edges.size() <= std::size_t(std::numeric_limits<int>::max()));

        int vertices = 2 * _n;
        Csr graph = build_csr(false);
        Csr reverse_graph = build_csr(true);

        std::vector<char> seen(vertices, false);
        std::vector<int> order;
        order.reserve(vertices);
        std::vector<std::pair<int, int>> stack;
        stack.reserve(vertices);

        for (int start = 0; start < vertices; start++) {
            if (seen[start]) continue;
            seen[start] = true;
            stack.emplace_back(start, graph.start[start]);

            while (!stack.empty()) {
                int v = stack.back().first;
                int& edge = stack.back().second;
                if (edge == graph.start[v + 1]) {
                    order.push_back(v);
                    stack.pop_back();
                    continue;
                }

                int to = graph.to[edge++];
                if (!seen[to]) {
                    seen[to] = true;
                    stack.emplace_back(to, graph.start[to]);
                }
            }
        }

        std::vector<int> component(vertices, -1);
        std::vector<int> vertices_stack;
        vertices_stack.reserve(vertices);
        int component_count = 0;
        for (int index = vertices - 1; index >= 0; index--) {
            int start = order[index];
            if (component[start] != -1) continue;

            component[start] = component_count;
            vertices_stack.push_back(start);
            while (!vertices_stack.empty()) {
                int v = vertices_stack.back();
                vertices_stack.pop_back();
                for (int edge = reverse_graph.start[v];
                     edge < reverse_graph.start[v + 1];
                     edge++) {
                    int to = reverse_graph.to[edge];
                    if (component[to] == -1) {
                        component[to] = component_count;
                        vertices_stack.push_back(to);
                    }
                }
            }
            component_count++;
        }

        _answer.assign(_n, false);
        _satisfiable = true;
        for (int i = 0; i < _n; i++) {
            if (component[2 * i] == component[2 * i + 1]) {
                _satisfiable = false;
                _answer.clear();
                break;
            }
            _answer[i] = component[2 * i] < component[2 * i + 1];
        }
        _solved = true;
        return _satisfiable;
    }

    const std::vector<bool>& answer() const {
        assert(_solved && _satisfiable);
        return _answer;
    }

    bool value(int variable) const {
        assert(_solved && _satisfiable);
        assert(0 <= variable && variable < _n);
        return _answer[variable];
    }
};

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_TWO_SAT_HPP
