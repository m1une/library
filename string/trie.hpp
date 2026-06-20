#ifndef M1UNE_STRING_TRIE_HPP
#define M1UNE_STRING_TRIE_HPP 1

#include <array>
#include <cassert>
#include <cstddef>
#include <limits>
#include <vector>

namespace m1une {
namespace string {

// A multiset trie for a contiguous character alphabet.
template <int AlphabetSize = 26, int FirstCharacter = 'a'>
struct Trie {
    static_assert(0 < AlphabetSize);

   private:
    struct Node {
        std::array<int, AlphabetSize> child;
        int subtree_count;
        int terminal_count;

        Node() : subtree_count(0), terminal_count(0) {
            child.fill(-1);
        }
    };

    std::vector<Node> _nodes;
    int _distinct_size;

    template <class Symbol>
    static int symbol_index(const Symbol& symbol) {
        int index = int(symbol) - FirstCharacter;
        assert(0 <= index && index < AlphabetSize);
        return index;
    }

    int new_node() {
        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));
        _nodes.emplace_back();
        return int(_nodes.size()) - 1;
    }

    template <class Sequence>
    int find_node(const Sequence& sequence) const {
        int node = 0;
        for (const auto& symbol : sequence) {
            node = _nodes[node].child[symbol_index(symbol)];
            if (node == -1 || _nodes[node].subtree_count == 0) return -1;
        }
        return node;
    }

   public:
    Trie() : _nodes(1), _distinct_size(0) {}

    int size() const {
        return _nodes[0].subtree_count;
    }

    int distinct_size() const {
        return _distinct_size;
    }

    bool empty() const {
        return size() == 0;
    }

    std::size_t node_count() const {
        return _nodes.size();
    }

    void reserve(std::size_t node_capacity) {
        _nodes.reserve(node_capacity);
    }

    void clear() {
        _nodes.clear();
        _nodes.emplace_back();
        _distinct_size = 0;
    }

    template <class Sequence>
    void insert(const Sequence& sequence, int multiplicity = 1) {
        assert(0 < multiplicity);
        int node = 0;
        _nodes[node].subtree_count += multiplicity;
        for (const auto& symbol : sequence) {
            int index = symbol_index(symbol);
            int child = _nodes[node].child[index];
            if (child == -1) {
                child = new_node();
                _nodes[node].child[index] = child;
            }
            node = child;
            _nodes[node].subtree_count += multiplicity;
        }
        if (_nodes[node].terminal_count == 0) _distinct_size++;
        _nodes[node].terminal_count += multiplicity;
    }

    template <class Sequence>
    int count(const Sequence& sequence) const {
        int node = find_node(sequence);
        return node == -1 ? 0 : _nodes[node].terminal_count;
    }

    template <class Sequence>
    bool contains(const Sequence& sequence) const {
        return count(sequence) != 0;
    }

    // Returns the number of stored strings beginning with prefix.
    template <class Sequence>
    int prefix_count(const Sequence& prefix) const {
        int node = find_node(prefix);
        return node == -1 ? 0 : _nodes[node].subtree_count;
    }

    template <class Sequence>
    bool starts_with(const Sequence& prefix) const {
        return prefix_count(prefix) != 0;
    }

    template <class Sequence>
    bool erase_one(const Sequence& sequence) {
        int terminal = find_node(sequence);
        if (terminal == -1 || _nodes[terminal].terminal_count == 0) return false;

        int node = 0;
        _nodes[node].subtree_count--;
        for (const auto& symbol : sequence) {
            node = _nodes[node].child[symbol_index(symbol)];
            _nodes[node].subtree_count--;
        }
        _nodes[node].terminal_count--;
        if (_nodes[node].terminal_count == 0) _distinct_size--;
        return true;
    }

    template <class Sequence>
    bool erase(const Sequence& sequence) {
        return erase_one(sequence);
    }

    template <class Sequence>
    int erase_all(const Sequence& sequence) {
        int multiplicity = count(sequence);
        if (multiplicity == 0) return 0;

        int node = 0;
        _nodes[node].subtree_count -= multiplicity;
        for (const auto& symbol : sequence) {
            node = _nodes[node].child[symbol_index(symbol)];
            _nodes[node].subtree_count -= multiplicity;
        }
        _nodes[node].terminal_count = 0;
        _distinct_size--;
        return multiplicity;
    }

    // Calls callback(length, multiplicity) for every stored prefix.
    // The empty prefix is reported with length 0 when it is stored.
    template <class Sequence, class Callback>
    void for_each_prefix(const Sequence& sequence, Callback callback) const {
        int node = 0;
        if (_nodes[node].terminal_count != 0) {
            callback(0, _nodes[node].terminal_count);
        }

        int length = 0;
        for (const auto& symbol : sequence) {
            node = _nodes[node].child[symbol_index(symbol)];
            if (node == -1 || _nodes[node].subtree_count == 0) return;
            length++;
            if (_nodes[node].terminal_count != 0) {
                callback(length, _nodes[node].terminal_count);
            }
        }
    }

    // Returns the length of the longest stored string that is a prefix.
    // Returns -1 when no stored prefix exists.
    template <class Sequence>
    int longest_prefix(const Sequence& sequence) const {
        int result = _nodes[0].terminal_count == 0 ? -1 : 0;
        for_each_prefix(sequence, [&result](int length, int) {
            result = length;
        });
        return result;
    }
};

}  // namespace string
}  // namespace m1une

#endif  // M1UNE_STRING_TRIE_HPP
