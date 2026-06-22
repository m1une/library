#ifndef M1UNE_GRAPH_COW_GAME_HPP
#define M1UNE_GRAPH_COW_GAME_HPP 1

#include <cassert>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

namespace m1une {
namespace graph {

template <class T>
struct CowGameConstraint {
    int from;
    int to;
    T upper_bound;
};

template <class T>
struct CowGameSolution {
    bool feasible = false;
    std::vector<T> value;

    bool is_feasible() const {
        return feasible;
    }
};

template <class T>
struct CowGameUpperBounds {
    bool feasible;
    std::vector<T> upper_bound;
    T inf;

    bool is_feasible() const {
        return feasible;
    }

    bool bounded(int variable) const {
        assert(0 <= variable && variable < int(upper_bound.size()));
        return feasible && upper_bound[variable] != inf;
    }
};

template <class T>
struct CowGameDifferenceBounds {
    bool feasible;
    std::optional<T> lower_bound;
    std::optional<T> upper_bound;

    bool is_feasible() const {
        return feasible;
    }

    bool bounded_below() const {
        return feasible && lower_bound.has_value();
    }

    bool bounded_above() const {
        return feasible && upper_bound.has_value();
    }
};

template <class T>
class CowGame {
    static_assert(std::is_arithmetic_v<T> && std::is_signed_v<T>);

    struct RelaxationResult {
        bool has_negative_cycle;
        std::vector<T> dist;
    };

    int _n;
    std::vector<CowGameConstraint<T>> _constraints;
    mutable bool _solution_cached = false;
    mutable CowGameSolution<T> _cached_solution;

    void assert_variable(int variable) const {
        (void)variable;
        assert(0 <= variable && variable < _n);
    }

    T negate(T value) const {
        assert(value != std::numeric_limits<T>::lowest());
        return -value;
    }

    RelaxationResult relax(std::vector<T> dist, T inf, bool skip_unreachable) const {
        for (int iteration = 0; iteration < _n; iteration++) {
            bool updated = false;
            for (const auto& constraint : _constraints) {
                if (skip_unreachable && dist[constraint.from] == inf) continue;
                T candidate = dist[constraint.from] + constraint.upper_bound;
                if (dist[constraint.to] <= candidate) continue;
                dist[constraint.to] = candidate;
                updated = true;
                if (iteration == _n - 1) return RelaxationResult{true, std::move(dist)};
            }
            if (!updated) break;
        }
        return RelaxationResult{false, std::move(dist)};
    }

    RelaxationResult check_feasibility() const {
        return relax(std::vector<T>(_n, T()), T(), false);
    }

    RelaxationResult shortest_paths(int source, T inf) const {
        std::vector<T> dist(_n, inf);
        dist[source] = T();
        return relax(std::move(dist), inf, true);
    }

   public:
    CowGame() : CowGame(0) {}

    explicit CowGame(int variable_count) : _n(variable_count) {
        assert(variable_count >= 0);
    }

    int size() const {
        return _n;
    }

    int constraint_count() const {
        return int(_constraints.size());
    }

    const CowGameConstraint<T>& get_constraint(int id) const {
        assert(0 <= id && id < int(_constraints.size()));
        return _constraints[id];
    }

    const std::vector<CowGameConstraint<T>>& constraints() const {
        return _constraints;
    }

    int add_upper_bound(int from, int to, T upper_bound) {
        assert_variable(from);
        assert_variable(to);
        int id = int(_constraints.size());
        _constraints.push_back(CowGameConstraint<T>{from, to, upper_bound});
        _solution_cached = false;
        return id;
    }

    int add_constraint(int from, int to, T upper_bound) {
        return add_upper_bound(from, to, upper_bound);
    }

    int add_lower_bound(int from, int to, T lower_bound) {
        return add_upper_bound(to, from, negate(lower_bound));
    }

    void add_bounds(int from, int to, T lower_bound, T upper_bound) {
        assert(lower_bound <= upper_bound);
        add_lower_bound(from, to, lower_bound);
        add_upper_bound(from, to, upper_bound);
    }

    void add_equality(int from, int to, T difference) {
        add_bounds(from, to, difference, difference);
    }

    CowGameSolution<T> solve() const {
        if (_solution_cached) return _cached_solution;

        auto result = check_feasibility();
        _cached_solution.feasible = !result.has_negative_cycle;
        _cached_solution.value.clear();
        if (_cached_solution.feasible) _cached_solution.value = std::move(result.dist);
        _solution_cached = true;
        return _cached_solution;
    }

    bool is_feasible() const {
        if (!_solution_cached) (void)solve();
        return _cached_solution.feasible;
    }

    CowGameUpperBounds<T> tightest_upper_bounds(int source) const {
        assert_variable(source);
        T inf = std::numeric_limits<T>::max() / T(4);
        CowGameUpperBounds<T> result;
        result.feasible = is_feasible();
        result.inf = inf;
        result.upper_bound.assign(_n, inf);
        if (!result.feasible) return result;

        result.upper_bound = shortest_paths(source, inf).dist;
        return result;
    }

    CowGameDifferenceBounds<T> difference_bounds(int from, int to) const {
        assert_variable(from);
        assert_variable(to);
        T inf = std::numeric_limits<T>::max() / T(4);
        CowGameDifferenceBounds<T> result;
        result.feasible = is_feasible();
        if (!result.feasible) return result;

        auto forward = shortest_paths(from, inf);
        if (forward.dist[to] != inf) result.upper_bound = forward.dist[to];

        auto backward = shortest_paths(to, inf);
        if (backward.dist[from] != inf) result.lower_bound = negate(backward.dist[from]);
        return result;
    }
};

template <class T>
using DifferenceConstraints = CowGame<T>;

}  // namespace graph
}  // namespace m1une

#endif  // M1UNE_GRAPH_COW_GAME_HPP
