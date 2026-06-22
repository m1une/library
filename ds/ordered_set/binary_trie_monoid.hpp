#ifndef M1UNE_DS_BINARY_TRIE_MONOID_HPP
#define M1UNE_DS_BINARY_TRIE_MONOID_HPP 1

#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <type_traits>
#include <utility>
#include <vector>

#include "../../monoid/concept.hpp"

namespace m1une {
namespace ds {

template <m1une::monoid::IsMonoid Monoid,
          typename UInt = std::uint32_t,
          int BitWidth = std::numeric_limits<UInt>::digits>
struct BinaryTrieMonoid {
    using T = typename Monoid::value_type;

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
        T prod;

        Node() : child{null_node, null_node}, count(0), prod(Monoid::id()) {}
    };

   private:
    struct Aggregate {
        int count;
        T prod;
    };

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

    T subtree_prod(node_id node) const {
        return node == null_node ? Monoid::id() : nodes[node].prod;
    }

    void update(int node) {
        nodes[node].count =
            subtree_size(nodes[node].child[0]) +
            subtree_size(nodes[node].child[1]);
        nodes[node].prod =
            Monoid::op(subtree_prod(nodes[node].child[0]),
                       subtree_prod(nodes[node].child[1]));
    }

    node_id find_node(UInt key) const {
        key ^= lazy_xor;
        node_id node = 0;
        for (int position = BitWidth - 1; position >= 0; --position) {
            node = nodes[node].child[bit(key, position)];
            if (node == null_node || nodes[node].count == 0) {
                return null_node;
            }
        }
        return node;
    }

    static int extend_comparison(int relation,
                                 int digit,
                                 int bound_digit) {
        if (relation != 0) return relation;
        if (digit < bound_digit) return -1;
        if (digit > bound_digit) return 1;
        return 0;
    }

    Aggregate xor_range_impl(int node,
                             int position,
                             UInt effective_xor,
                             UInt lower,
                             UInt upper,
                             int lower_relation,
                             int upper_relation) const {
        if (node == -1 || nodes[node].count == 0 ||
            lower_relation < 0 || upper_relation > 0) {
            return {0, Monoid::id()};
        }
        if (lower_relation > 0 && upper_relation < 0) {
            return {nodes[node].count, nodes[node].prod};
        }
        if (position < 0) {
            if (lower_relation >= 0 && upper_relation < 0) {
                return {nodes[node].count, nodes[node].prod};
            }
            return {0, Monoid::id()};
        }

        Aggregate result{0, Monoid::id()};
        const int xor_digit = bit(effective_xor, position);
        const int lower_digit = bit(lower, position);
        const int upper_digit = bit(upper, position);
        for (int xor_result_digit = 0;
             xor_result_digit < 2;
             ++xor_result_digit) {
            const int direction = xor_result_digit ^ xor_digit;
            Aggregate part = xor_range_impl(
                nodes[node].child[direction],
                position - 1,
                effective_xor,
                lower,
                upper,
                extend_comparison(lower_relation,
                                  xor_result_digit,
                                  lower_digit),
                extend_comparison(upper_relation,
                                  xor_result_digit,
                                  upper_digit));
            result.count += part.count;
            result.prod = Monoid::op(result.prod, part.prod);
        }
        return result;
    }

    T prod_xor_greater_equal_impl(UInt value, UInt lower) const {
        const UInt effective_xor = lazy_xor ^ value;
        T result = Monoid::id();
        int node = 0;
        for (int position = BitWidth - 1;
             position >= 0 && node != -1;
             --position) {
            const int zero = bit(effective_xor, position);
            if (bit(lower, position) == 0) {
                result =
                    Monoid::op(result,
                               subtree_prod(nodes[node].child[zero ^ 1]));
                node = nodes[node].child[zero];
            } else {
                node = nodes[node].child[zero ^ 1];
            }
        }
        return Monoid::op(result, subtree_prod(node));
    }

   public:
    BinaryTrieMonoid() : nodes(1), lazy_xor(0) {}

    BinaryTrieMonoid(
        std::initializer_list<std::pair<UInt, T>> init)
        : BinaryTrieMonoid() {
        for (const auto& entry : init) {
            insert(entry.first, entry.second);
        }
    }

    template <typename Iterator>
    BinaryTrieMonoid(Iterator first, Iterator last)
        : BinaryTrieMonoid() {
        while (first != last) {
            insert(first->first, first->second);
            ++first;
        }
    }

    BinaryTrieMonoid(const std::vector<UInt>& keys,
                     const std::vector<T>& values)
        : BinaryTrieMonoid() {
        assert(keys.size() == values.size());
        for (int i = 0; i < int(keys.size()); ++i) {
            insert(keys[i], values[i]);
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

    node_id find(UInt key) const {
        assert(valid_value(key));
        return find_node(key);
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

    node_id insert(UInt key, const T& value) {
        assert(valid_value(key));
        key ^= lazy_xor;
        node_id node = 0;
        ++nodes[node].count;
        nodes[node].prod = Monoid::op(nodes[node].prod, value);
        for (int position = BitWidth - 1; position >= 0; --position) {
            const int direction = bit(key, position);
            if (nodes[node].child[direction] == null_node) {
                const node_id child = new_node();
                nodes[node].child[direction] = child;
            }
            node = nodes[node].child[direction];
            ++nodes[node].count;
            nodes[node].prod = Monoid::op(nodes[node].prod, value);
        }
        return node;
    }

    int count(UInt key) const {
        assert(valid_value(key));
        const node_id node = find_node(key);
        return node == null_node ? 0 : nodes[node].count;
    }

    bool contains(UInt key) const {
        return count(key) > 0;
    }

    T prod(UInt key) const {
        assert(valid_value(key));
        const node_id node = find_node(key);
        return node == null_node ? Monoid::id() : nodes[node].prod;
    }

    T all_prod() const {
        return nodes[0].prod;
    }

    int erase_all(UInt key) {
        assert(valid_value(key));
        key ^= lazy_xor;

        int path[BitWidth + 1];
        path[0] = 0;
        int node = 0;
        for (int position = BitWidth - 1, depth = 1;
             position >= 0;
             --position, ++depth) {
            node = nodes[node].child[bit(key, position)];
            if (node == -1 || nodes[node].count == 0) return 0;
            path[depth] = node;
        }

        const int erased = nodes[node].count;
        nodes[node].count = 0;
        nodes[node].prod = Monoid::id();
        for (int depth = BitWidth - 1; depth >= 0; --depth) {
            update(path[depth]);
        }
        return erased;
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
            const int preferred_size =
                subtree_size(nodes[node].child[preferred]);
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

    int count_xor_equal(UInt value, UInt target) const {
        assert(valid_value(value));
        assert(valid_value(target));
        return count(value ^ target);
    }

    int count_xor_less(UInt value, UInt upper) const {
        assert(valid_value(value));
        if (!valid_value(upper)) return size();

        const UInt effective_xor = lazy_xor ^ value;
        int result = 0;
        int node = 0;
        for (int position = BitWidth - 1;
             position >= 0 && node != -1;
             --position) {
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

    int count_less_xor(UInt value, UInt upper) const {
        return count_xor_less(value, upper);
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

    int order_of_key(UInt key) const {
        return count_xor_less(0, key);
    }

    int count_less(UInt key) const {
        return order_of_key(key);
    }

    int count_less_equal(UInt key) const {
        return count_xor_less_equal(0, key);
    }

    int count_greater(UInt key) const {
        return count_xor_greater(0, key);
    }

    int count_greater_equal(UInt key) const {
        return count_xor_greater_equal(0, key);
    }

    int count_range(UInt lower, UInt upper) const {
        return count_xor_range(0, lower, upper);
    }

    T prod_xor_equal(UInt value, UInt target) const {
        assert(valid_value(value));
        assert(valid_value(target));
        return prod(value ^ target);
    }

    T prod_xor_less(UInt value, UInt upper) const {
        assert(valid_value(value));
        if (!valid_value(upper)) return all_prod();

        const UInt effective_xor = lazy_xor ^ value;
        T result = Monoid::id();
        int node = 0;
        for (int position = BitWidth - 1;
             position >= 0 && node != -1;
             --position) {
            const int zero = bit(effective_xor, position);
            if (bit(upper, position) == 1) {
                result =
                    Monoid::op(result,
                               subtree_prod(nodes[node].child[zero]));
                node = nodes[node].child[zero ^ 1];
            } else {
                node = nodes[node].child[zero];
            }
        }
        return result;
    }

    T prod_xor_less_equal(UInt value, UInt upper) const {
        assert(valid_value(value));
        assert(valid_value(upper));
        if (upper == value_mask()) return all_prod();
        return prod_xor_less(value, upper + UInt(1));
    }

    T prod_xor_greater(UInt value, UInt lower) const {
        assert(valid_value(value));
        assert(valid_value(lower));
        if (lower == value_mask()) return Monoid::id();
        return prod_xor_greater_equal_impl(value, lower + UInt(1));
    }

    T prod_xor_greater_equal(UInt value, UInt lower) const {
        assert(valid_value(value));
        assert(valid_value(lower));
        return prod_xor_greater_equal_impl(value, lower);
    }

    T prod_xor_range(UInt value, UInt lower, UInt upper) const {
        assert(valid_value(value));
        assert(valid_value(lower));
        assert(lower <= upper);
        if (lower == upper) return Monoid::id();
        if (!valid_value(upper)) {
            return prod_xor_greater_equal(value, lower);
        }
        return xor_range_impl(0,
                              BitWidth - 1,
                              lazy_xor ^ value,
                              lower,
                              upper,
                              0,
                              0)
            .prod;
    }

    T prod_less(UInt key) const {
        return prod_xor_less(0, key);
    }

    T prod_less_equal(UInt key) const {
        return prod_xor_less_equal(0, key);
    }

    T prod_greater(UInt key) const {
        return prod_xor_greater(0, key);
    }

    T prod_greater_equal(UInt key) const {
        return prod_xor_greater_equal(0, key);
    }

    T prod_range(UInt lower, UInt upper) const {
        return prod_xor_range(0, lower, upper);
    }
};

}  // namespace ds
}  // namespace m1une

#endif  // M1UNE_DS_BINARY_TRIE_MONOID_HPP
