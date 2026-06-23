#ifndef M1UNE_STRING_SUFFIX_AUTOMATON_HPP
#define M1UNE_STRING_SUFFIX_AUTOMATON_HPP 1

#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace string {

template <int AlphabetSize = 26, int FirstCharacter = 'a'>
struct SuffixAutomaton {
    static_assert(0 < AlphabetSize);

    using state_id = int;
    static constexpr state_id root_state = 0;
    static constexpr state_id null_state = -1;

    struct State {
        std::array<state_id, AlphabetSize> next;
        state_id suffix_link;
        int length;
        int first_end;
        int direct_occurrences;
        bool clone;

        State(int length_value = 0)
            : suffix_link(null_state),
              length(length_value),
              first_end(0),
              direct_occurrences(0),
              clone(false) {
            next.fill(null_state);
        }
    };

   private:
    std::vector<State> _states;
    state_id _last;
    int _text_length;

    template <class Symbol>
    static int symbol_index(const Symbol& symbol) {
        int index = int(symbol) - FirstCharacter;
        assert(0 <= index && index < AlphabetSize);
        return index;
    }

    state_id new_state(int length) {
        assert(_states.size() < std::size_t(std::numeric_limits<int>::max()));
        _states.emplace_back(length);
        return int(_states.size()) - 1;
    }

   public:
    SuffixAutomaton() {
        clear();
    }

    template <class Sequence>
    explicit SuffixAutomaton(const Sequence& sequence) {
        clear();
        build(sequence);
    }

    int state_count() const {
        return int(_states.size());
    }

    int size() const {
        return state_count();
    }

    bool empty() const {
        return _text_length == 0;
    }

    int text_length() const {
        return _text_length;
    }

    state_id root() const {
        return root_state;
    }

    state_id last() const {
        return _last;
    }

    const State& state(state_id id) const {
        assert(0 <= id && id < state_count());
        return _states[id];
    }

    const std::vector<State>& states() const {
        return _states;
    }

    int minimum_length(state_id id) const {
        assert(0 <= id && id < state_count());
        return id == root_state ? 0 : _states[_states[id].suffix_link].length + 1;
    }

    template <class Symbol>
    state_id transition(state_id id, const Symbol& symbol) const {
        assert(0 <= id && id < state_count());
        return _states[id].next[symbol_index(symbol)];
    }

    void reserve(std::size_t text_capacity) {
        _states.reserve(2 * text_capacity);
    }

    void clear() {
        _states.clear();
        _states.emplace_back();
        _last = root_state;
        _text_length = 0;
    }

    template <class Symbol>
    state_id add(const Symbol& value) {
        int symbol = symbol_index(value);
        assert(_text_length < std::numeric_limits<int>::max());
        _text_length++;

        state_id current = new_state(_states[_last].length + 1);
        _states[current].first_end = _text_length;
        _states[current].direct_occurrences = 1;

        state_id p = _last;
        while (p != null_state && _states[p].next[symbol] == null_state) {
            _states[p].next[symbol] = current;
            p = _states[p].suffix_link;
        }

        if (p == null_state) {
            _states[current].suffix_link = root_state;
        } else {
            state_id q = _states[p].next[symbol];
            if (_states[p].length + 1 == _states[q].length) {
                _states[current].suffix_link = q;
            } else {
                state_id clone = new_state(_states[p].length + 1);
                _states[clone] = _states[q];
                _states[clone].length = _states[p].length + 1;
                _states[clone].direct_occurrences = 0;
                _states[clone].clone = true;

                while (p != null_state && _states[p].next[symbol] == q) {
                    _states[p].next[symbol] = clone;
                    p = _states[p].suffix_link;
                }
                _states[q].suffix_link = clone;
                _states[current].suffix_link = clone;
            }
        }

        _last = current;
        return current;
    }

    template <class Sequence>
    void build(const Sequence& sequence) {
        for (const auto& symbol : sequence) add(symbol);
    }

    template <class Sequence>
    state_id find(const Sequence& sequence) const {
        state_id current = root_state;
        for (const auto& symbol : sequence) {
            current = transition(current, symbol);
            if (current == null_state) return null_state;
        }
        return current;
    }

    template <class Sequence>
    bool contains(const Sequence& sequence) const {
        return find(sequence) != null_state;
    }

    std::vector<state_id> length_order() const {
        std::vector<int> count(_text_length + 1, 0);
        for (const State& current : _states) count[current.length]++;
        for (int length = 1; length <= _text_length; length++) count[length] += count[length - 1];

        std::vector<state_id> order(state_count());
        for (state_id id = state_count() - 1; id >= 0; id--) {
            order[--count[_states[id].length]] = id;
        }
        return order;
    }

    std::vector<long long> occurrence_counts() const {
        std::vector<long long> result(state_count(), 0);
        for (state_id id = 0; id < state_count(); id++) {
            result[id] = _states[id].direct_occurrences;
        }
        std::vector<state_id> order = length_order();
        for (int i = int(order.size()) - 1; i > 0; i--) {
            state_id id = order[i];
            result[_states[id].suffix_link] += result[id];
        }
        return result;
    }

    std::vector<bool> terminal_states() const {
        std::vector<bool> result(state_count(), false);
        for (state_id id = _last; id != null_state; id = _states[id].suffix_link) {
            result[id] = true;
        }
        return result;
    }

    long long distinct_substring_count() const {
        long long result = 0;
        for (state_id id = 1; id < state_count(); id++) {
            result += _states[id].length - _states[_states[id].suffix_link].length;
        }
        return result;
    }

    std::pair<int, int> longest_representative(state_id id) const {
        assert(0 <= id && id < state_count());
        int end = _states[id].first_end;
        return {end - _states[id].length, end};
    }

    template <class Sequence>
    std::pair<int, int> representative_occurrence(const Sequence& sequence) const {
        state_id id = root_state;
        int length = 0;
        for (const auto& symbol : sequence) {
            id = transition(id, symbol);
            if (id == null_state) return {-1, -1};
            length++;
        }
        int end = _states[id].first_end;
        return {end - length, end};
    }

    template <class Sequence>
    std::pair<int, int> longest_common_substring(const Sequence& sequence) const {
        state_id current = root_state;
        int current_length = 0;
        int best_length = 0;
        int best_end = 0;
        int end = 0;

        for (const auto& value : sequence) {
            int symbol = symbol_index(value);
            while (current != root_state && _states[current].next[symbol] == null_state) {
                current = _states[current].suffix_link;
                current_length = std::min(current_length, _states[current].length);
            }
            state_id next = _states[current].next[symbol];
            if (next == null_state) {
                current = root_state;
                current_length = 0;
            } else {
                current = next;
                current_length++;
            }
            end++;
            if (best_length < current_length) {
                best_length = current_length;
                best_end = end;
            }
        }
        return {best_end - best_length, best_end};
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_SUFFIX_AUTOMATON_HPP
