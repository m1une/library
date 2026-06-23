#ifndef M1UNE_STRING_EERTREE_HPP
#define M1UNE_STRING_EERTREE_HPP 1

#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <utility>
#include <vector>

namespace m1une {
namespace string {

template <int AlphabetSize = 26, int FirstCharacter = 'a'>
struct Eertree {
    static_assert(0 < AlphabetSize);

    using node_id = int;
    static constexpr node_id even_root = 0;
    static constexpr node_id odd_root = 1;
    static constexpr node_id null_node = -1;

    struct Node {
        std::array<node_id, AlphabetSize> next;
        node_id suffix_link;
        node_id series_link;
        int length;
        int diff;
        int suffix_count;
        int first_end;
        long long suffix_occurrences;

        Node(int length_value = 0, node_id suffix_link_value = even_root, node_id series_link_value = even_root)
            : suffix_link(suffix_link_value),
              series_link(series_link_value),
              length(length_value),
              diff(0),
              suffix_count(0),
              first_end(0),
              suffix_occurrences(0) {
            next.fill(null_node);
        }
    };

   private:
    std::vector<Node> _nodes;
    std::vector<int> _text;
    std::vector<node_id> _longest_suffix;
    node_id _last;

    template <class Symbol>
    static int symbol_index(const Symbol& symbol) {
        int index = int(symbol) - FirstCharacter;
        assert(0 <= index && index < AlphabetSize);
        return index;
    }

    node_id find_extendable(node_id node, int position, int symbol) const {
        while (true) {
            int length = _nodes[node].length;
            int left = position - length - 1;
            if (0 <= left && _text[left] == symbol) return node;
            node = _nodes[node].suffix_link;
        }
    }

    node_id new_node(int length) {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back(length);
        return int(_nodes.size()) - 1;
    }

   public:
    Eertree() {
        clear();
    }

    template <class Sequence>
    explicit Eertree(const Sequence& sequence) {
        clear();
        build(sequence);
    }

    int size() const {
        return int(_nodes.size()) - 2;
    }

    bool empty() const {
        return size() == 0;
    }

    int node_count() const {
        return int(_nodes.size());
    }

    int text_length() const {
        return int(_text.size());
    }

    node_id last() const {
        return _last;
    }

    int longest_suffix_length() const {
        return _nodes[_last].length;
    }

    const Node& node(node_id id) const {
        assert(0 <= id && id < node_count());
        return _nodes[id];
    }

    const std::vector<Node>& nodes() const {
        return _nodes;
    }

    node_id longest_suffix_node(int prefix_length) const {
        assert(1 <= prefix_length && prefix_length <= text_length());
        return _longest_suffix[prefix_length - 1];
    }

    const std::vector<node_id>& longest_suffix_nodes() const {
        return _longest_suffix;
    }

    template <class Callback>
    void for_each_suffix(node_id id, Callback callback) const {
        assert(0 <= id && id < node_count());
        while (id >= 2) {
            callback(id);
            id = _nodes[id].suffix_link;
        }
    }

    template <class Callback>
    void for_each_suffix(Callback callback) const {
        for_each_suffix(_last, callback);
    }

    void reserve(std::size_t text_capacity) {
        _text.reserve(text_capacity);
        _longest_suffix.reserve(text_capacity);
        _nodes.reserve(text_capacity + 2);
    }

    void clear() {
        _nodes.clear();
        _nodes.emplace_back(0, odd_root, even_root);
        _nodes.emplace_back(-1, odd_root, odd_root);
        _text.clear();
        _longest_suffix.clear();
        _last = even_root;
    }

    template <class Symbol>
    node_id add(const Symbol& value) {
        int symbol = symbol_index(value);
        int position = int(_text.size());
        _text.push_back(symbol);

        node_id current = find_extendable(_last, position, symbol);
        node_id next = _nodes[current].next[symbol];
        if (next == null_node) {
            int length = _nodes[current].length + 2;
            next = new_node(length);
            _nodes[current].next[symbol] = next;

            node_id suffix_link = even_root;
            if (length != 1) {
                node_id candidate = find_extendable(_nodes[current].suffix_link, position, symbol);
                suffix_link = _nodes[candidate].next[symbol];
                assert(suffix_link != null_node);
            }

            Node& created = _nodes[next];
            created.suffix_link = suffix_link;
            created.diff = created.length - _nodes[suffix_link].length;
            created.series_link =
                created.diff == _nodes[suffix_link].diff ? _nodes[suffix_link].series_link : suffix_link;
            created.suffix_count = _nodes[suffix_link].suffix_count + 1;
            created.first_end = position + 1;
        }

        _last = next;
        _nodes[_last].suffix_occurrences++;
        _longest_suffix.push_back(_last);
        return _last;
    }

    template <class Sequence>
    void build(const Sequence& sequence) {
        for (const auto& symbol : sequence) add(symbol);
    }

    std::vector<long long> occurrence_counts() const {
        std::vector<long long> result(_nodes.size(), 0);
        for (node_id id = 0; id < node_count(); id++) {
            result[id] = _nodes[id].suffix_occurrences;
        }
        for (node_id id = node_count() - 1; id >= 2; id--) {
            result[_nodes[id].suffix_link] += result[id];
        }
        return result;
    }

    std::pair<int, int> first_occurrence(node_id id) const {
        assert(2 <= id && id < node_count());
        int end = _nodes[id].first_end;
        return {end - _nodes[id].length, end};
    }
};

template <int AlphabetSize = 26, int FirstCharacter = 'a'>
using PalindromicTree = Eertree<AlphabetSize, FirstCharacter>;

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_EERTREE_HPP
