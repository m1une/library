#ifndef M1UNE_STRING_AHO_CORASICK_HPP
#define M1UNE_STRING_AHO_CORASICK_HPP 1

#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <queue>
#include <vector>

namespace m1une {
namespace string {

// Aho-Corasick automaton for a contiguous character alphabet.
template <int AlphabetSize = 26, int FirstCharacter = 'a'>
struct AhoCorasick {
    static_assert(0 < AlphabetSize);

    using node_id = int;

    struct Node {
        std::array<node_id, AlphabetSize> next;
        node_id failure;
        node_id output_link;
        std::vector<int> pattern_ids;

        Node() : failure(0), output_link(-1) {
            next.fill(-1);
        }
    };

   private:
    std::vector<Node> _nodes;
    std::vector<int> _pattern_length;
    std::vector<node_id> _bfs_order;
    bool _built;

    template <class Symbol>
    static int symbol_index(const Symbol& symbol) {
        int index = int(symbol) - FirstCharacter;
        assert(0 <= index && index < AlphabetSize);
        return index;
    }

    node_id new_node() {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back();
        return int(_nodes.size()) - 1;
    }

   public:
    AhoCorasick() : _nodes(1), _built(false) {}

    node_id root() const {
        return 0;
    }

    bool built() const {
        return _built;
    }

    int pattern_count() const {
        return int(_pattern_length.size());
    }

    int pattern_length(int pattern_id) const {
        assert(0 <= pattern_id && pattern_id < pattern_count());
        return _pattern_length[pattern_id];
    }

    std::size_t node_count() const {
        return _nodes.size();
    }

    const Node& node(node_id id) const {
        assert(0 <= id && std::size_t(id) < _nodes.size());
        return _nodes[id];
    }

    void reserve(std::size_t node_capacity) {
        assert(!_built);
        _nodes.reserve(node_capacity);
    }

    void clear() {
        _nodes.clear();
        _nodes.emplace_back();
        _pattern_length.clear();
        _bfs_order.clear();
        _built = false;
    }

    // Inserts a pattern and returns its insertion-order ID.
    template <class Sequence>
    int insert(const Sequence& pattern) {
        assert(!_built);
        int pattern_id = pattern_count();
        int length = 0;
        node_id state = root();
        for (const auto& symbol : pattern) {
            assert(length < std::numeric_limits<int>::max());
            int index = symbol_index(symbol);
            if (_nodes[state].next[index] == -1) {
                node_id child = new_node();
                _nodes[state].next[index] = child;
            }
            state = _nodes[state].next[index];
            length++;
        }
        _nodes[state].pattern_ids.push_back(pattern_id);
        _pattern_length.push_back(length);
        return pattern_id;
    }

    // Builds failure links and completes every automaton transition.
    void build() {
        assert(!_built);
        std::queue<node_id> queue;
        _bfs_order.clear();
        _bfs_order.reserve(_nodes.size());
        _bfs_order.push_back(root());

        for (int symbol = 0; symbol < AlphabetSize; ++symbol) {
            node_id child = _nodes[root()].next[symbol];
            if (child == -1) {
                _nodes[root()].next[symbol] = root();
            } else {
                _nodes[child].failure = root();
                _nodes[child].output_link =
                    _nodes[root()].pattern_ids.empty() ? -1 : root();
                queue.push(child);
            }
        }

        while (!queue.empty()) {
            node_id state = queue.front();
            queue.pop();
            _bfs_order.push_back(state);

            for (int symbol = 0; symbol < AlphabetSize; ++symbol) {
                node_id child = _nodes[state].next[symbol];
                if (child == -1) {
                    _nodes[state].next[symbol] =
                        _nodes[_nodes[state].failure].next[symbol];
                    continue;
                }

                node_id failure =
                    _nodes[_nodes[state].failure].next[symbol];
                _nodes[child].failure = failure;
                _nodes[child].output_link =
                    _nodes[failure].pattern_ids.empty()
                        ? _nodes[failure].output_link
                        : failure;
                queue.push(child);
            }
        }
        _built = true;
    }

    template <class Symbol>
    node_id transition(node_id state, const Symbol& symbol) const {
        assert(_built);
        assert(0 <= state && std::size_t(state) < _nodes.size());
        return _nodes[state].next[symbol_index(symbol)];
    }

    // Calls callback(pattern_id) for every pattern ending at `state`.
    template <class Callback>
    void for_each_output(node_id state, Callback callback) const {
        assert(_built);
        assert(0 <= state && std::size_t(state) < _nodes.size());
        while (state != -1) {
            for (int pattern_id : _nodes[state].pattern_ids) {
                callback(pattern_id);
            }
            state = _nodes[state].output_link;
        }
    }

    // Calls callback(end, pattern_id) for every occurrence. `end` is the
    // exclusive end position. Empty patterns occur at every text boundary.
    template <class Sequence, class Callback>
    void match(const Sequence& text, Callback callback) const {
        assert(_built);
        node_id state = root();
        for_each_output(state, [&callback](int pattern_id) {
            callback(0, pattern_id);
        });

        int end = 0;
        for (const auto& symbol : text) {
            state = transition(state, symbol);
            end++;
            for_each_output(state, [&callback, end](int pattern_id) {
                callback(end, pattern_id);
            });
        }
    }

    // Counts occurrences of every inserted pattern in linear time.
    template <class Sequence>
    std::vector<long long> count_occurrences(const Sequence& text) const {
        assert(_built);
        std::vector<long long> visits(_nodes.size(), 0);
        node_id state = root();
        visits[root()]++;
        for (const auto& symbol : text) {
            state = transition(state, symbol);
            visits[state]++;
        }

        for (std::size_t index = _bfs_order.size(); index-- > 1;) {
            node_id current = _bfs_order[index];
            visits[_nodes[current].failure] += visits[current];
        }

        std::vector<long long> result(pattern_count(), 0);
        for (node_id current : _bfs_order) {
            for (int pattern_id : _nodes[current].pattern_ids) {
                result[pattern_id] = visits[current];
            }
        }
        return result;
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_AHO_CORASICK_HPP
