#ifndef M1UNE_OPTIMIZATION_PROJECT_SELECTION_HPP
#define M1UNE_OPTIMIZATION_PROJECT_SELECTION_HPP 1

#include <cassert>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

#include "../flow/max_flow.hpp"

namespace m1une {
namespace optimization {

template <class T>
struct ProjectSelectionResult {
    bool feasible;
    T max_gain;
    std::vector<bool> selected;

    bool is_feasible() const {
        return feasible;
    }
};

template <class T>
class ProjectSelection {
    static_assert(std::is_integral_v<T> && std::is_signed_v<T>);

    struct Arc {
        int from;
        int to;
        T cap;
    };

    static constexpr int source = -1;
    static constexpr int sink = -2;

    int _project_count;
    int _vertex_count;
    T _offset = T();
    T _finite_cap_sum = T();
    std::vector<Arc> _arcs;
    std::vector<std::pair<int, int>> _hard_arcs;

    void assert_project(int project) const {
        (void)project;
        assert(0 <= project && project < _project_count);
    }

    void assert_vertex(int vertex) const {
        (void)vertex;
        assert(0 <= vertex && vertex < _vertex_count);
    }

    void add_offset(T value) {
        if (value > T()) {
            assert(_offset <= std::numeric_limits<T>::max() - value);
        } else if (value < T()) {
            assert(_offset >= std::numeric_limits<T>::lowest() - value);
        }
        _offset += value;
    }

    T nonnegative_difference(T large, T small) const {
        assert(small <= large);
        if (small < T()) {
            assert(large <= std::numeric_limits<T>::max() + small);
        }
        return large - small;
    }

    void add_arc(int from, int to, T cap) {
        assert(cap >= T());
        if (from == to) return;
        assert(cap <= std::numeric_limits<T>::max() - _finite_cap_sum);
        _finite_cap_sum += cap;
        _arcs.push_back(Arc{from, to, cap});
    }

    void add_hard_arc(int from, int to) {
        if (from == to) return;
        _hard_arcs.emplace_back(from, to);
    }

    void add_vertex_gain(int vertex, T gain_if_selected, T gain_if_unselected) {
        assert_vertex(vertex);
        if (gain_if_selected >= gain_if_unselected) {
            add_offset(gain_if_selected);
            add_arc(source, vertex,
                    nonnegative_difference(gain_if_selected, gain_if_unselected));
        } else {
            add_offset(gain_if_unselected);
            add_arc(vertex, sink,
                    nonnegative_difference(gain_if_unselected, gain_if_selected));
        }
    }

    int add_auxiliary_vertex() {
        return _vertex_count++;
    }

   public:
    ProjectSelection() : ProjectSelection(0) {}

    explicit ProjectSelection(int project_count)
        : _project_count(project_count), _vertex_count(project_count) {
        assert(project_count >= 0);
    }

    int size() const {
        return _project_count;
    }

    void add_gain(int project, T gain_if_selected) {
        add_gain(project, gain_if_selected, T());
    }

    void add_gain(int project, T gain_if_selected, T gain_if_unselected) {
        assert_project(project);
        add_vertex_gain(project, gain_if_selected, gain_if_unselected);
    }

    void add_penalty(int selected_project, int unselected_project, T penalty) {
        assert_project(selected_project);
        assert_project(unselected_project);
        add_arc(selected_project, unselected_project, penalty);
    }

    void add_penalty_if_different(int project_a, int project_b, T penalty) {
        assert_project(project_a);
        assert_project(project_b);
        add_arc(project_a, project_b, penalty);
        add_arc(project_b, project_a, penalty);
    }

    void add_gain_if_same(int project_a, int project_b, T gain) {
        assert(gain >= T());
        add_offset(gain);
        add_penalty_if_different(project_a, project_b, gain);
    }

    void add_hard_implication(int selected_project, int required_project) {
        assert_project(selected_project);
        assert_project(required_project);
        add_hard_arc(selected_project, required_project);
    }

    void force_selected(int project) {
        assert_project(project);
        add_hard_arc(source, project);
    }

    void force_unselected(int project) {
        assert_project(project);
        add_hard_arc(project, sink);
    }

    void add_gain_if_all_selected(const std::vector<int>& projects, T gain) {
        assert(gain >= T());
        for (int project : projects) assert_project(project);
        if (projects.empty()) {
            add_offset(gain);
            return;
        }
        if (projects.size() == 1) {
            add_vertex_gain(projects[0], gain, T());
            return;
        }
        if (projects.size() == 2) {
            add_vertex_gain(projects[0], gain, T());
            add_arc(projects[0], projects[1], gain);
            return;
        }

        int auxiliary = add_auxiliary_vertex();
        add_vertex_gain(auxiliary, gain, T());
        for (int project : projects) add_hard_arc(auxiliary, project);
    }

    void add_gain_if_all_unselected(const std::vector<int>& projects, T gain) {
        assert(gain >= T());
        for (int project : projects) assert_project(project);
        if (projects.empty()) {
            add_offset(gain);
            return;
        }
        if (projects.size() == 1) {
            add_vertex_gain(projects[0], T(), gain);
            return;
        }
        if (projects.size() == 2) {
            add_vertex_gain(projects[0], T(), gain);
            add_arc(projects[1], projects[0], gain);
            return;
        }

        int auxiliary = add_auxiliary_vertex();
        add_vertex_gain(auxiliary, T(), gain);
        for (int project : projects) add_hard_arc(project, auxiliary);
    }

    ProjectSelectionResult<T> solve() const {
        int s = _vertex_count;
        int t = s + 1;
        flow::MaxFlow<T> max_flow(_vertex_count + 2);

        auto vertex_id = [&](int vertex) {
            if (vertex == source) return s;
            if (vertex == sink) return t;
            return vertex;
        };

        for (const auto& arc : _arcs) {
            max_flow.add_edge(vertex_id(arc.from), vertex_id(arc.to), arc.cap);
        }

        T hard_cap = T();
        if (!_hard_arcs.empty()) {
            assert(_finite_cap_sum < std::numeric_limits<T>::max());
            hard_cap = _finite_cap_sum + T(1);
            for (auto [from, to] : _hard_arcs) {
                max_flow.add_edge(vertex_id(from), vertex_id(to), hard_cap);
            }
        }

        T cut_cost =
            _hard_arcs.empty() ? max_flow.max_flow(s, t) : max_flow.max_flow(s, t, hard_cap);
        ProjectSelectionResult<T> result;
        result.feasible = _hard_arcs.empty() || cut_cost < hard_cap;
        result.max_gain = T();
        result.selected.assign(_project_count, false);
        if (!result.feasible) return result;

        assert(_offset >= std::numeric_limits<T>::lowest() + cut_cost);
        result.max_gain = _offset - cut_cost;
        auto source_side = max_flow.min_cut(s);
        for (int project = 0; project < _project_count; project++) {
            result.selected[project] = source_side[project];
        }
        return result;
    }
};

}  // namespace optimization
}  // namespace m1une

#endif  // M1UNE_OPTIMIZATION_PROJECT_SELECTION_HPP
