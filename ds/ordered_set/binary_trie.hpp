#ifndef M1UNE_DS_BINARY_TRIE_HPP
#define M1UNE_DS_BINARY_TRIE_HPP 1

#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <type_traits>
#include <vector>

namespace m1une {
namespace ds {

template <typename UInt = std::uint32_t, int BitWidth = std::numeric_limits<UInt>::digits>
struct BinaryTrie {
    static_assert(std::is_integral_v<UInt>);
    static_assert(std::is_unsigned_v<UInt>);
    static_assert(!std::is_same_v<UInt, bool>);
    static_assert(0 < BitWidth);
    static_assert(BitWidth <= std::numeric_limits<UInt>::digits);

    using node_id = int;
    static constexpr node_id null_node = -1;

    struct Node {
        node_id child[2];
        int count;

        Node() : child{null_node, null_node}, count(0) {}
    };

   private:
    std::vector<Node> nodes;
    UInt lazy_xor;

    static constexpr int bit(UInt value, int position) {
        return int((value >> position) & UInt(1));
    }

    static constexpr UInt value_mask() {
        if constexpr (BitWidth == std::numeric_limits<UInt>::digits) {
            return std::numeric_limits<UInt>::max();
        } else {
            return (UInt(1) << BitWidth) - UInt(1);
        }
    }

    static constexpr bool valid_value(UInt value) {
        return (value & ~value_mask()) == UInt(0);
    }

    node_id new_node() {
        nodes.emplace_back();
        return int(nodes.size()) - 1;
    }

    int subtree_size(node_id node) const {
        return node == null_node ? 0 : nodes[node].count;
    }

    node_id find_node(UInt value) const {
        node_id node = 0;
        value ^= lazy_xor;
        for (int position = BitWidth - 1; position >= 0; --position) {
            node = nodes[node].child[bit(value, position)];
            if (node == null_node || nodes[node].count == 0) {
                return null_node;
            }
        }
        return node;
    }

   public:
    BinaryTrie() : nodes(1), lazy_xor(0) {}

    BinaryTrie(std::initializer_list<UInt> init) : BinaryTrie() {
        for (UInt value : init) insert(value);
    }

    template <typename Iterator>
    BinaryTrie(Iterator first, Iterator last) : BinaryTrie() {
        while (first != last) {
            insert(*first);
            ++first;
        }
    }

    int size() const {
        return nodes[0].count;
    }

    bool empty() const {
        return size() == 0;
    }

    node_id root() const {
        return 0;
    }

    const Node& node(node_id id) const {
        assert(0 <= id && std::size_t(id) < nodes.size());
        return nodes[id];
    }

    node_id find(UInt value) const {
        assert(valid_value(value));
        return find_node(value);
    }

    std::size_t node_count() const {
        return nodes.size();
    }

    void reserve(std::size_t node_capacity) {
        nodes.reserve(node_capacity);
    }

    UInt xor_mask() const {
        return lazy_xor;
    }

    void clear() {
        nodes.clear();
        nodes.emplace_back();
        lazy_xor = 0;
    }

    node_id insert(UInt value, int multiplicity = 1) {
        assert(valid_value(value));
        assert(multiplicity > 0);
        value ^= lazy_xor;
        node_id node = 0;
        nodes[node].count += multiplicity;
        for (int position = BitWidth - 1; position >= 0; --position) {
            const int direction = bit(value, position);
            if (nodes[node].child[direction] == null_node) {
                const node_id child = new_node();
                nodes[node].child[direction] = child;
            }
            node = nodes[node].child[direction];
            nodes[node].count += multiplicity;
        }
        return node;
    }

    int count(UInt value) const {
        assert(valid_value(value));
        const node_id node = find_node(value);
        return node == null_node ? 0 : nodes[node].count;
    }

    bool contains(UInt value) const {
        return count(value) > 0;
    }

    bool erase_one(UInt value) {
        assert(valid_value(value));
        if (!contains(value)) return false;
        value ^= lazy_xor;
        int node = 0;
        --nodes[node].count;
        for (int position = BitWidth - 1; position >= 0; --position) {
            node = nodes[node].child[bit(value, position)];
            --nodes[node].count;
        }
        return true;
    }

    bool erase(UInt value) {
        return erase_one(value);
    }

    int erase_all(UInt value) {
        assert(valid_value(value));
        const int multiplicity = count(value);
        if (multiplicity == 0) return 0;
        value ^= lazy_xor;
        int node = 0;
        nodes[node].count -= multiplicity;
        for (int position = BitWidth - 1; position >= 0; --position) {
            node = nodes[node].child[bit(value, position)];
            nodes[node].count -= multiplicity;
        }
        return multiplicity;
    }

    void xor_all(UInt value) {
        assert(valid_value(value));
        lazy_xor ^= value;
    }

    UInt kth_xor(int k, UInt value) const {
        assert(0 <= k && k < size());
        assert(valid_value(value));
        const UInt effective_xor = lazy_xor ^ value;
        UInt result = 0;
        int node = 0;
        for (int position = BitWidth - 1; position >= 0; --position) {
            const int preferred = bit(effective_xor, position);
            const int preferred_size = subtree_size(nodes[node].child[preferred]);
            if (k < preferred_size) {
                node = nodes[node].child[preferred];
            } else {
                k -= preferred_size;
                node = nodes[node].child[preferred ^ 1];
                result |= UInt(1) << position;
            }
        }
        return result;
    }

    UInt kth(int k) const {
        return kth_xor(k, 0);
    }

    UInt min() const {
        return kth(0);
    }

    UInt max() const {
        return kth(size() - 1);
    }

    UInt min_xor(UInt value) const {
        return kth_xor(0, value);
    }

    UInt max_xor(UInt value) const {
        return kth_xor(size() - 1, value);
    }

    int count_less_xor(UInt value, UInt upper) const {
        assert(valid_value(value));
        if (!valid_value(upper)) return size();
        const UInt effective_xor = lazy_xor ^ value;
        int result = 0;
        int node = 0;
        for (int position = BitWidth - 1; position >= 0 && node != -1; --position) {
            const int zero = bit(effective_xor, position);
            if (bit(upper, position) == 1) {
                result += subtree_size(nodes[node].child[zero]);
                node = nodes[node].child[zero ^ 1];
            } else {
                node = nodes[node].child[zero];
            }
        }
        return result;
    }

    int count_xor_less(UInt value, UInt upper) const {
        return count_less_xor(value, upper);
    }

    int count_xor_less_equal(UInt value, UInt upper) const {
        assert(valid_value(value));
        assert(valid_value(upper));
        if (upper == value_mask()) return size();
        return count_xor_less(value, upper + UInt(1));
    }

    int count_xor_greater(UInt value, UInt lower) const {
        assert(valid_value(value));
        assert(valid_value(lower));
        return size() - count_xor_less_equal(value, lower);
    }

    int count_xor_greater_equal(UInt value, UInt lower) const {
        assert(valid_value(value));
        assert(valid_value(lower));
        return size() - count_xor_less(value, lower);
    }

    int count_xor_range(UInt value, UInt lower, UInt upper) const {
        assert(valid_value(value));
        assert(valid_value(lower));
        assert(lower <= upper);
        return count_xor_less(value, upper) -
               count_xor_less(value, lower);
    }

    int order_of_key(UInt value) const {
        return count_less_xor(0, value);
    }

    int count_less(UInt value) const {
        return order_of_key(value);
    }

    int count_less_equal(UInt value) const {
        assert(valid_value(value));
        if (value == value_mask()) return size();
        return count_less(value + UInt(1));
    }

    int count_greater(UInt value) const {
        return size() - count_less_equal(value);
    }

    int count_greater_equal(UInt value) const {
        return size() - count_less(value);
    }

    std::vector<UInt> to_vector() const {
        std::vector<UInt> result;
        result.reserve(size());
        for (int k = 0; k < size(); ++k) {
            result.push_back(kth(k));
        }
        return result;
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_BINARY_TRIE_HPP
