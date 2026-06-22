---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/ordered_set/binary_trie_monoid.test.cpp
    title: verify/ds/ordered_set/binary_trie_monoid.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/ordered_set/binary_trie_monoid.hpp\"\n\n\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <initializer_list>\n#include <limits>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\n#line 1 \"monoid/concept.hpp\"\
    \n\n\n\n#include <concepts>\n\nnamespace m1une {\nnamespace monoid {\n\n// Concept\
    \ to check if a type satisfies the requirements of a Monoid.\n// A Monoid must\
    \ have a `value_type`, an identity element `id()`, and an associative binary operation\
    \ `op()`.\ntemplate <typename M>\nconcept IsMonoid = requires(typename M::value_type\
    \ a, typename M::value_type b) {\n    // 1. Must define `value_type`\n    typename\
    \ M::value_type;\n\n    // 2. Must have a static method `id()` returning `value_type`\n\
    \    { M::id() } -> std::same_as<typename M::value_type>;\n\n    // 3. Must have\
    \ a static method `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
    \ M::value_type>;\n};\n\n// Concept for commutative group monoids.\n// A type\
    \ satisfying this concept must also obey commutativity and inverse laws.\ntemplate\
    \ <typename M>\nconcept IsCommutativeGroup = IsMonoid<M> && requires(typename\
    \ M::value_type a) {\n    { M::inv(a) } -> std::same_as<typename M::value_type>;\n\
    };\n\n}  // namespace monoid\n}  // namespace m1une\n\n\n#line 13 \"ds/ordered_set/binary_trie_monoid.hpp\"\
    \n\nnamespace m1une {\nnamespace ds {\n\ntemplate <m1une::monoid::IsMonoid Monoid,\n\
    \          typename UInt = std::uint32_t,\n          int BitWidth = std::numeric_limits<UInt>::digits>\n\
    struct BinaryTrieMonoid {\n    using T = typename Monoid::value_type;\n\n    static_assert(std::is_integral_v<UInt>);\n\
    \    static_assert(std::is_unsigned_v<UInt>);\n    static_assert(!std::is_same_v<UInt,\
    \ bool>);\n    static_assert(0 < BitWidth);\n    static_assert(BitWidth <= std::numeric_limits<UInt>::digits);\n\
    \n    using node_id = int;\n    static constexpr node_id null_node = -1;\n\n \
    \   struct Node {\n        node_id child[2];\n        int count;\n        T prod;\n\
    \n        Node() : child{null_node, null_node}, count(0), prod(Monoid::id()) {}\n\
    \    };\n\n   private:\n    struct Aggregate {\n        int count;\n        T\
    \ prod;\n    };\n\n    std::vector<Node> nodes;\n    UInt lazy_xor;\n\n    static\
    \ constexpr int bit(UInt value, int position) {\n        return int((value >>\
    \ position) & UInt(1));\n    }\n\n    static constexpr UInt value_mask() {\n \
    \       if constexpr (BitWidth == std::numeric_limits<UInt>::digits) {\n     \
    \       return std::numeric_limits<UInt>::max();\n        } else {\n         \
    \   return (UInt(1) << BitWidth) - UInt(1);\n        }\n    }\n\n    static constexpr\
    \ bool valid_value(UInt value) {\n        return (value & ~value_mask()) == UInt(0);\n\
    \    }\n\n    node_id new_node() {\n        nodes.emplace_back();\n        return\
    \ int(nodes.size()) - 1;\n    }\n\n    int subtree_size(node_id node) const {\n\
    \        return node == null_node ? 0 : nodes[node].count;\n    }\n\n    T subtree_prod(node_id\
    \ node) const {\n        return node == null_node ? Monoid::id() : nodes[node].prod;\n\
    \    }\n\n    void update(int node) {\n        nodes[node].count =\n         \
    \   subtree_size(nodes[node].child[0]) +\n            subtree_size(nodes[node].child[1]);\n\
    \        nodes[node].prod =\n            Monoid::op(subtree_prod(nodes[node].child[0]),\n\
    \                       subtree_prod(nodes[node].child[1]));\n    }\n\n    node_id\
    \ find_node(UInt key) const {\n        key ^= lazy_xor;\n        node_id node\
    \ = 0;\n        for (int position = BitWidth - 1; position >= 0; --position) {\n\
    \            node = nodes[node].child[bit(key, position)];\n            if (node\
    \ == null_node || nodes[node].count == 0) {\n                return null_node;\n\
    \            }\n        }\n        return node;\n    }\n\n    static int extend_comparison(int\
    \ relation,\n                                 int digit,\n                   \
    \              int bound_digit) {\n        if (relation != 0) return relation;\n\
    \        if (digit < bound_digit) return -1;\n        if (digit > bound_digit)\
    \ return 1;\n        return 0;\n    }\n\n    Aggregate xor_range_impl(int node,\n\
    \                             int position,\n                             UInt\
    \ effective_xor,\n                             UInt lower,\n                 \
    \            UInt upper,\n                             int lower_relation,\n \
    \                            int upper_relation) const {\n        if (node ==\
    \ -1 || nodes[node].count == 0 ||\n            lower_relation < 0 || upper_relation\
    \ > 0) {\n            return {0, Monoid::id()};\n        }\n        if (lower_relation\
    \ > 0 && upper_relation < 0) {\n            return {nodes[node].count, nodes[node].prod};\n\
    \        }\n        if (position < 0) {\n            if (lower_relation >= 0 &&\
    \ upper_relation < 0) {\n                return {nodes[node].count, nodes[node].prod};\n\
    \            }\n            return {0, Monoid::id()};\n        }\n\n        Aggregate\
    \ result{0, Monoid::id()};\n        const int xor_digit = bit(effective_xor, position);\n\
    \        const int lower_digit = bit(lower, position);\n        const int upper_digit\
    \ = bit(upper, position);\n        for (int xor_result_digit = 0;\n          \
    \   xor_result_digit < 2;\n             ++xor_result_digit) {\n            const\
    \ int direction = xor_result_digit ^ xor_digit;\n            Aggregate part =\
    \ xor_range_impl(\n                nodes[node].child[direction],\n           \
    \     position - 1,\n                effective_xor,\n                lower,\n\
    \                upper,\n                extend_comparison(lower_relation,\n \
    \                                 xor_result_digit,\n                        \
    \          lower_digit),\n                extend_comparison(upper_relation,\n\
    \                                  xor_result_digit,\n                       \
    \           upper_digit));\n            result.count += part.count;\n        \
    \    result.prod = Monoid::op(result.prod, part.prod);\n        }\n        return\
    \ result;\n    }\n\n    T prod_xor_greater_equal_impl(UInt value, UInt lower)\
    \ const {\n        const UInt effective_xor = lazy_xor ^ value;\n        T result\
    \ = Monoid::id();\n        int node = 0;\n        for (int position = BitWidth\
    \ - 1;\n             position >= 0 && node != -1;\n             --position) {\n\
    \            const int zero = bit(effective_xor, position);\n            if (bit(lower,\
    \ position) == 0) {\n                result =\n                    Monoid::op(result,\n\
    \                               subtree_prod(nodes[node].child[zero ^ 1]));\n\
    \                node = nodes[node].child[zero];\n            } else {\n     \
    \           node = nodes[node].child[zero ^ 1];\n            }\n        }\n  \
    \      return Monoid::op(result, subtree_prod(node));\n    }\n\n   public:\n \
    \   BinaryTrieMonoid() : nodes(1), lazy_xor(0) {}\n\n    BinaryTrieMonoid(\n \
    \       std::initializer_list<std::pair<UInt, T>> init)\n        : BinaryTrieMonoid()\
    \ {\n        for (const auto& entry : init) {\n            insert(entry.first,\
    \ entry.second);\n        }\n    }\n\n    template <typename Iterator>\n    BinaryTrieMonoid(Iterator\
    \ first, Iterator last)\n        : BinaryTrieMonoid() {\n        while (first\
    \ != last) {\n            insert(first->first, first->second);\n            ++first;\n\
    \        }\n    }\n\n    BinaryTrieMonoid(const std::vector<UInt>& keys,\n   \
    \                  const std::vector<T>& values)\n        : BinaryTrieMonoid()\
    \ {\n        assert(keys.size() == values.size());\n        for (int i = 0; i\
    \ < int(keys.size()); ++i) {\n            insert(keys[i], values[i]);\n      \
    \  }\n    }\n\n    int size() const {\n        return nodes[0].count;\n    }\n\
    \n    bool empty() const {\n        return size() == 0;\n    }\n\n    node_id\
    \ root() const {\n        return 0;\n    }\n\n    const Node& node(node_id id)\
    \ const {\n        assert(0 <= id && std::size_t(id) < nodes.size());\n      \
    \  return nodes[id];\n    }\n\n    node_id find(UInt key) const {\n        assert(valid_value(key));\n\
    \        return find_node(key);\n    }\n\n    std::size_t node_count() const {\n\
    \        return nodes.size();\n    }\n\n    void reserve(std::size_t node_capacity)\
    \ {\n        nodes.reserve(node_capacity);\n    }\n\n    UInt xor_mask() const\
    \ {\n        return lazy_xor;\n    }\n\n    void clear() {\n        nodes.clear();\n\
    \        nodes.emplace_back();\n        lazy_xor = 0;\n    }\n\n    node_id insert(UInt\
    \ key, const T& value) {\n        assert(valid_value(key));\n        key ^= lazy_xor;\n\
    \        node_id node = 0;\n        ++nodes[node].count;\n        nodes[node].prod\
    \ = Monoid::op(nodes[node].prod, value);\n        for (int position = BitWidth\
    \ - 1; position >= 0; --position) {\n            const int direction = bit(key,\
    \ position);\n            if (nodes[node].child[direction] == null_node) {\n \
    \               const node_id child = new_node();\n                nodes[node].child[direction]\
    \ = child;\n            }\n            node = nodes[node].child[direction];\n\
    \            ++nodes[node].count;\n            nodes[node].prod = Monoid::op(nodes[node].prod,\
    \ value);\n        }\n        return node;\n    }\n\n    int count(UInt key) const\
    \ {\n        assert(valid_value(key));\n        const node_id node = find_node(key);\n\
    \        return node == null_node ? 0 : nodes[node].count;\n    }\n\n    bool\
    \ contains(UInt key) const {\n        return count(key) > 0;\n    }\n\n    T prod(UInt\
    \ key) const {\n        assert(valid_value(key));\n        const node_id node\
    \ = find_node(key);\n        return node == null_node ? Monoid::id() : nodes[node].prod;\n\
    \    }\n\n    T all_prod() const {\n        return nodes[0].prod;\n    }\n\n \
    \   int erase_all(UInt key) {\n        assert(valid_value(key));\n        key\
    \ ^= lazy_xor;\n\n        int path[BitWidth + 1];\n        path[0] = 0;\n    \
    \    int node = 0;\n        for (int position = BitWidth - 1, depth = 1;\n   \
    \          position >= 0;\n             --position, ++depth) {\n            node\
    \ = nodes[node].child[bit(key, position)];\n            if (node == -1 || nodes[node].count\
    \ == 0) return 0;\n            path[depth] = node;\n        }\n\n        const\
    \ int erased = nodes[node].count;\n        nodes[node].count = 0;\n        nodes[node].prod\
    \ = Monoid::id();\n        for (int depth = BitWidth - 1; depth >= 0; --depth)\
    \ {\n            update(path[depth]);\n        }\n        return erased;\n   \
    \ }\n\n    void xor_all(UInt value) {\n        assert(valid_value(value));\n \
    \       lazy_xor ^= value;\n    }\n\n    UInt kth_xor(int k, UInt value) const\
    \ {\n        assert(0 <= k && k < size());\n        assert(valid_value(value));\n\
    \        const UInt effective_xor = lazy_xor ^ value;\n        UInt result = 0;\n\
    \        int node = 0;\n        for (int position = BitWidth - 1; position >=\
    \ 0; --position) {\n            const int preferred = bit(effective_xor, position);\n\
    \            const int preferred_size =\n                subtree_size(nodes[node].child[preferred]);\n\
    \            if (k < preferred_size) {\n                node = nodes[node].child[preferred];\n\
    \            } else {\n                k -= preferred_size;\n                node\
    \ = nodes[node].child[preferred ^ 1];\n                result |= UInt(1) << position;\n\
    \            }\n        }\n        return result;\n    }\n\n    UInt kth(int k)\
    \ const {\n        return kth_xor(k, 0);\n    }\n\n    UInt min() const {\n  \
    \      return kth(0);\n    }\n\n    UInt max() const {\n        return kth(size()\
    \ - 1);\n    }\n\n    UInt min_xor(UInt value) const {\n        return kth_xor(0,\
    \ value);\n    }\n\n    UInt max_xor(UInt value) const {\n        return kth_xor(size()\
    \ - 1, value);\n    }\n\n    int count_xor_equal(UInt value, UInt target) const\
    \ {\n        assert(valid_value(value));\n        assert(valid_value(target));\n\
    \        return count(value ^ target);\n    }\n\n    int count_xor_less(UInt value,\
    \ UInt upper) const {\n        assert(valid_value(value));\n        if (!valid_value(upper))\
    \ return size();\n\n        const UInt effective_xor = lazy_xor ^ value;\n   \
    \     int result = 0;\n        int node = 0;\n        for (int position = BitWidth\
    \ - 1;\n             position >= 0 && node != -1;\n             --position) {\n\
    \            const int zero = bit(effective_xor, position);\n            if (bit(upper,\
    \ position) == 1) {\n                result += subtree_size(nodes[node].child[zero]);\n\
    \                node = nodes[node].child[zero ^ 1];\n            } else {\n \
    \               node = nodes[node].child[zero];\n            }\n        }\n  \
    \      return result;\n    }\n\n    int count_less_xor(UInt value, UInt upper)\
    \ const {\n        return count_xor_less(value, upper);\n    }\n\n    int count_xor_less_equal(UInt\
    \ value, UInt upper) const {\n        assert(valid_value(value));\n        assert(valid_value(upper));\n\
    \        if (upper == value_mask()) return size();\n        return count_xor_less(value,\
    \ upper + UInt(1));\n    }\n\n    int count_xor_greater(UInt value, UInt lower)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        return size() - count_xor_less_equal(value, lower);\n    }\n\n    int\
    \ count_xor_greater_equal(UInt value, UInt lower) const {\n        assert(valid_value(value));\n\
    \        assert(valid_value(lower));\n        return size() - count_xor_less(value,\
    \ lower);\n    }\n\n    int count_xor_range(UInt value, UInt lower, UInt upper)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        assert(lower <= upper);\n        return count_xor_less(value, upper)\
    \ -\n               count_xor_less(value, lower);\n    }\n\n    int order_of_key(UInt\
    \ key) const {\n        return count_xor_less(0, key);\n    }\n\n    int count_less(UInt\
    \ key) const {\n        return order_of_key(key);\n    }\n\n    int count_less_equal(UInt\
    \ key) const {\n        return count_xor_less_equal(0, key);\n    }\n\n    int\
    \ count_greater(UInt key) const {\n        return count_xor_greater(0, key);\n\
    \    }\n\n    int count_greater_equal(UInt key) const {\n        return count_xor_greater_equal(0,\
    \ key);\n    }\n\n    int count_range(UInt lower, UInt upper) const {\n      \
    \  return count_xor_range(0, lower, upper);\n    }\n\n    T prod_xor_equal(UInt\
    \ value, UInt target) const {\n        assert(valid_value(value));\n        assert(valid_value(target));\n\
    \        return prod(value ^ target);\n    }\n\n    T prod_xor_less(UInt value,\
    \ UInt upper) const {\n        assert(valid_value(value));\n        if (!valid_value(upper))\
    \ return all_prod();\n\n        const UInt effective_xor = lazy_xor ^ value;\n\
    \        T result = Monoid::id();\n        int node = 0;\n        for (int position\
    \ = BitWidth - 1;\n             position >= 0 && node != -1;\n             --position)\
    \ {\n            const int zero = bit(effective_xor, position);\n            if\
    \ (bit(upper, position) == 1) {\n                result =\n                  \
    \  Monoid::op(result,\n                               subtree_prod(nodes[node].child[zero]));\n\
    \                node = nodes[node].child[zero ^ 1];\n            } else {\n \
    \               node = nodes[node].child[zero];\n            }\n        }\n  \
    \      return result;\n    }\n\n    T prod_xor_less_equal(UInt value, UInt upper)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(upper));\n\
    \        if (upper == value_mask()) return all_prod();\n        return prod_xor_less(value,\
    \ upper + UInt(1));\n    }\n\n    T prod_xor_greater(UInt value, UInt lower) const\
    \ {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        if (lower == value_mask()) return Monoid::id();\n        return prod_xor_greater_equal_impl(value,\
    \ lower + UInt(1));\n    }\n\n    T prod_xor_greater_equal(UInt value, UInt lower)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        return prod_xor_greater_equal_impl(value, lower);\n    }\n\n    T prod_xor_range(UInt\
    \ value, UInt lower, UInt upper) const {\n        assert(valid_value(value));\n\
    \        assert(valid_value(lower));\n        assert(lower <= upper);\n      \
    \  if (lower == upper) return Monoid::id();\n        if (!valid_value(upper))\
    \ {\n            return prod_xor_greater_equal(value, lower);\n        }\n   \
    \     return xor_range_impl(0,\n                              BitWidth - 1,\n\
    \                              lazy_xor ^ value,\n                           \
    \   lower,\n                              upper,\n                           \
    \   0,\n                              0)\n            .prod;\n    }\n\n    T prod_less(UInt\
    \ key) const {\n        return prod_xor_less(0, key);\n    }\n\n    T prod_less_equal(UInt\
    \ key) const {\n        return prod_xor_less_equal(0, key);\n    }\n\n    T prod_greater(UInt\
    \ key) const {\n        return prod_xor_greater(0, key);\n    }\n\n    T prod_greater_equal(UInt\
    \ key) const {\n        return prod_xor_greater_equal(0, key);\n    }\n\n    T\
    \ prod_range(UInt lower, UInt upper) const {\n        return prod_xor_range(0,\
    \ lower, upper);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_DS_BINARY_TRIE_MONOID_HPP\n#define M1UNE_DS_BINARY_TRIE_MONOID_HPP\
    \ 1\n\n#include <cassert>\n#include <cstdint>\n#include <initializer_list>\n#include\
    \ <limits>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\n\
    #include \"../../monoid/concept.hpp\"\n\nnamespace m1une {\nnamespace ds {\n\n\
    template <m1une::monoid::IsMonoid Monoid,\n          typename UInt = std::uint32_t,\n\
    \          int BitWidth = std::numeric_limits<UInt>::digits>\nstruct BinaryTrieMonoid\
    \ {\n    using T = typename Monoid::value_type;\n\n    static_assert(std::is_integral_v<UInt>);\n\
    \    static_assert(std::is_unsigned_v<UInt>);\n    static_assert(!std::is_same_v<UInt,\
    \ bool>);\n    static_assert(0 < BitWidth);\n    static_assert(BitWidth <= std::numeric_limits<UInt>::digits);\n\
    \n    using node_id = int;\n    static constexpr node_id null_node = -1;\n\n \
    \   struct Node {\n        node_id child[2];\n        int count;\n        T prod;\n\
    \n        Node() : child{null_node, null_node}, count(0), prod(Monoid::id()) {}\n\
    \    };\n\n   private:\n    struct Aggregate {\n        int count;\n        T\
    \ prod;\n    };\n\n    std::vector<Node> nodes;\n    UInt lazy_xor;\n\n    static\
    \ constexpr int bit(UInt value, int position) {\n        return int((value >>\
    \ position) & UInt(1));\n    }\n\n    static constexpr UInt value_mask() {\n \
    \       if constexpr (BitWidth == std::numeric_limits<UInt>::digits) {\n     \
    \       return std::numeric_limits<UInt>::max();\n        } else {\n         \
    \   return (UInt(1) << BitWidth) - UInt(1);\n        }\n    }\n\n    static constexpr\
    \ bool valid_value(UInt value) {\n        return (value & ~value_mask()) == UInt(0);\n\
    \    }\n\n    node_id new_node() {\n        nodes.emplace_back();\n        return\
    \ int(nodes.size()) - 1;\n    }\n\n    int subtree_size(node_id node) const {\n\
    \        return node == null_node ? 0 : nodes[node].count;\n    }\n\n    T subtree_prod(node_id\
    \ node) const {\n        return node == null_node ? Monoid::id() : nodes[node].prod;\n\
    \    }\n\n    void update(int node) {\n        nodes[node].count =\n         \
    \   subtree_size(nodes[node].child[0]) +\n            subtree_size(nodes[node].child[1]);\n\
    \        nodes[node].prod =\n            Monoid::op(subtree_prod(nodes[node].child[0]),\n\
    \                       subtree_prod(nodes[node].child[1]));\n    }\n\n    node_id\
    \ find_node(UInt key) const {\n        key ^= lazy_xor;\n        node_id node\
    \ = 0;\n        for (int position = BitWidth - 1; position >= 0; --position) {\n\
    \            node = nodes[node].child[bit(key, position)];\n            if (node\
    \ == null_node || nodes[node].count == 0) {\n                return null_node;\n\
    \            }\n        }\n        return node;\n    }\n\n    static int extend_comparison(int\
    \ relation,\n                                 int digit,\n                   \
    \              int bound_digit) {\n        if (relation != 0) return relation;\n\
    \        if (digit < bound_digit) return -1;\n        if (digit > bound_digit)\
    \ return 1;\n        return 0;\n    }\n\n    Aggregate xor_range_impl(int node,\n\
    \                             int position,\n                             UInt\
    \ effective_xor,\n                             UInt lower,\n                 \
    \            UInt upper,\n                             int lower_relation,\n \
    \                            int upper_relation) const {\n        if (node ==\
    \ -1 || nodes[node].count == 0 ||\n            lower_relation < 0 || upper_relation\
    \ > 0) {\n            return {0, Monoid::id()};\n        }\n        if (lower_relation\
    \ > 0 && upper_relation < 0) {\n            return {nodes[node].count, nodes[node].prod};\n\
    \        }\n        if (position < 0) {\n            if (lower_relation >= 0 &&\
    \ upper_relation < 0) {\n                return {nodes[node].count, nodes[node].prod};\n\
    \            }\n            return {0, Monoid::id()};\n        }\n\n        Aggregate\
    \ result{0, Monoid::id()};\n        const int xor_digit = bit(effective_xor, position);\n\
    \        const int lower_digit = bit(lower, position);\n        const int upper_digit\
    \ = bit(upper, position);\n        for (int xor_result_digit = 0;\n          \
    \   xor_result_digit < 2;\n             ++xor_result_digit) {\n            const\
    \ int direction = xor_result_digit ^ xor_digit;\n            Aggregate part =\
    \ xor_range_impl(\n                nodes[node].child[direction],\n           \
    \     position - 1,\n                effective_xor,\n                lower,\n\
    \                upper,\n                extend_comparison(lower_relation,\n \
    \                                 xor_result_digit,\n                        \
    \          lower_digit),\n                extend_comparison(upper_relation,\n\
    \                                  xor_result_digit,\n                       \
    \           upper_digit));\n            result.count += part.count;\n        \
    \    result.prod = Monoid::op(result.prod, part.prod);\n        }\n        return\
    \ result;\n    }\n\n    T prod_xor_greater_equal_impl(UInt value, UInt lower)\
    \ const {\n        const UInt effective_xor = lazy_xor ^ value;\n        T result\
    \ = Monoid::id();\n        int node = 0;\n        for (int position = BitWidth\
    \ - 1;\n             position >= 0 && node != -1;\n             --position) {\n\
    \            const int zero = bit(effective_xor, position);\n            if (bit(lower,\
    \ position) == 0) {\n                result =\n                    Monoid::op(result,\n\
    \                               subtree_prod(nodes[node].child[zero ^ 1]));\n\
    \                node = nodes[node].child[zero];\n            } else {\n     \
    \           node = nodes[node].child[zero ^ 1];\n            }\n        }\n  \
    \      return Monoid::op(result, subtree_prod(node));\n    }\n\n   public:\n \
    \   BinaryTrieMonoid() : nodes(1), lazy_xor(0) {}\n\n    BinaryTrieMonoid(\n \
    \       std::initializer_list<std::pair<UInt, T>> init)\n        : BinaryTrieMonoid()\
    \ {\n        for (const auto& entry : init) {\n            insert(entry.first,\
    \ entry.second);\n        }\n    }\n\n    template <typename Iterator>\n    BinaryTrieMonoid(Iterator\
    \ first, Iterator last)\n        : BinaryTrieMonoid() {\n        while (first\
    \ != last) {\n            insert(first->first, first->second);\n            ++first;\n\
    \        }\n    }\n\n    BinaryTrieMonoid(const std::vector<UInt>& keys,\n   \
    \                  const std::vector<T>& values)\n        : BinaryTrieMonoid()\
    \ {\n        assert(keys.size() == values.size());\n        for (int i = 0; i\
    \ < int(keys.size()); ++i) {\n            insert(keys[i], values[i]);\n      \
    \  }\n    }\n\n    int size() const {\n        return nodes[0].count;\n    }\n\
    \n    bool empty() const {\n        return size() == 0;\n    }\n\n    node_id\
    \ root() const {\n        return 0;\n    }\n\n    const Node& node(node_id id)\
    \ const {\n        assert(0 <= id && std::size_t(id) < nodes.size());\n      \
    \  return nodes[id];\n    }\n\n    node_id find(UInt key) const {\n        assert(valid_value(key));\n\
    \        return find_node(key);\n    }\n\n    std::size_t node_count() const {\n\
    \        return nodes.size();\n    }\n\n    void reserve(std::size_t node_capacity)\
    \ {\n        nodes.reserve(node_capacity);\n    }\n\n    UInt xor_mask() const\
    \ {\n        return lazy_xor;\n    }\n\n    void clear() {\n        nodes.clear();\n\
    \        nodes.emplace_back();\n        lazy_xor = 0;\n    }\n\n    node_id insert(UInt\
    \ key, const T& value) {\n        assert(valid_value(key));\n        key ^= lazy_xor;\n\
    \        node_id node = 0;\n        ++nodes[node].count;\n        nodes[node].prod\
    \ = Monoid::op(nodes[node].prod, value);\n        for (int position = BitWidth\
    \ - 1; position >= 0; --position) {\n            const int direction = bit(key,\
    \ position);\n            if (nodes[node].child[direction] == null_node) {\n \
    \               const node_id child = new_node();\n                nodes[node].child[direction]\
    \ = child;\n            }\n            node = nodes[node].child[direction];\n\
    \            ++nodes[node].count;\n            nodes[node].prod = Monoid::op(nodes[node].prod,\
    \ value);\n        }\n        return node;\n    }\n\n    int count(UInt key) const\
    \ {\n        assert(valid_value(key));\n        const node_id node = find_node(key);\n\
    \        return node == null_node ? 0 : nodes[node].count;\n    }\n\n    bool\
    \ contains(UInt key) const {\n        return count(key) > 0;\n    }\n\n    T prod(UInt\
    \ key) const {\n        assert(valid_value(key));\n        const node_id node\
    \ = find_node(key);\n        return node == null_node ? Monoid::id() : nodes[node].prod;\n\
    \    }\n\n    T all_prod() const {\n        return nodes[0].prod;\n    }\n\n \
    \   int erase_all(UInt key) {\n        assert(valid_value(key));\n        key\
    \ ^= lazy_xor;\n\n        int path[BitWidth + 1];\n        path[0] = 0;\n    \
    \    int node = 0;\n        for (int position = BitWidth - 1, depth = 1;\n   \
    \          position >= 0;\n             --position, ++depth) {\n            node\
    \ = nodes[node].child[bit(key, position)];\n            if (node == -1 || nodes[node].count\
    \ == 0) return 0;\n            path[depth] = node;\n        }\n\n        const\
    \ int erased = nodes[node].count;\n        nodes[node].count = 0;\n        nodes[node].prod\
    \ = Monoid::id();\n        for (int depth = BitWidth - 1; depth >= 0; --depth)\
    \ {\n            update(path[depth]);\n        }\n        return erased;\n   \
    \ }\n\n    void xor_all(UInt value) {\n        assert(valid_value(value));\n \
    \       lazy_xor ^= value;\n    }\n\n    UInt kth_xor(int k, UInt value) const\
    \ {\n        assert(0 <= k && k < size());\n        assert(valid_value(value));\n\
    \        const UInt effective_xor = lazy_xor ^ value;\n        UInt result = 0;\n\
    \        int node = 0;\n        for (int position = BitWidth - 1; position >=\
    \ 0; --position) {\n            const int preferred = bit(effective_xor, position);\n\
    \            const int preferred_size =\n                subtree_size(nodes[node].child[preferred]);\n\
    \            if (k < preferred_size) {\n                node = nodes[node].child[preferred];\n\
    \            } else {\n                k -= preferred_size;\n                node\
    \ = nodes[node].child[preferred ^ 1];\n                result |= UInt(1) << position;\n\
    \            }\n        }\n        return result;\n    }\n\n    UInt kth(int k)\
    \ const {\n        return kth_xor(k, 0);\n    }\n\n    UInt min() const {\n  \
    \      return kth(0);\n    }\n\n    UInt max() const {\n        return kth(size()\
    \ - 1);\n    }\n\n    UInt min_xor(UInt value) const {\n        return kth_xor(0,\
    \ value);\n    }\n\n    UInt max_xor(UInt value) const {\n        return kth_xor(size()\
    \ - 1, value);\n    }\n\n    int count_xor_equal(UInt value, UInt target) const\
    \ {\n        assert(valid_value(value));\n        assert(valid_value(target));\n\
    \        return count(value ^ target);\n    }\n\n    int count_xor_less(UInt value,\
    \ UInt upper) const {\n        assert(valid_value(value));\n        if (!valid_value(upper))\
    \ return size();\n\n        const UInt effective_xor = lazy_xor ^ value;\n   \
    \     int result = 0;\n        int node = 0;\n        for (int position = BitWidth\
    \ - 1;\n             position >= 0 && node != -1;\n             --position) {\n\
    \            const int zero = bit(effective_xor, position);\n            if (bit(upper,\
    \ position) == 1) {\n                result += subtree_size(nodes[node].child[zero]);\n\
    \                node = nodes[node].child[zero ^ 1];\n            } else {\n \
    \               node = nodes[node].child[zero];\n            }\n        }\n  \
    \      return result;\n    }\n\n    int count_less_xor(UInt value, UInt upper)\
    \ const {\n        return count_xor_less(value, upper);\n    }\n\n    int count_xor_less_equal(UInt\
    \ value, UInt upper) const {\n        assert(valid_value(value));\n        assert(valid_value(upper));\n\
    \        if (upper == value_mask()) return size();\n        return count_xor_less(value,\
    \ upper + UInt(1));\n    }\n\n    int count_xor_greater(UInt value, UInt lower)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        return size() - count_xor_less_equal(value, lower);\n    }\n\n    int\
    \ count_xor_greater_equal(UInt value, UInt lower) const {\n        assert(valid_value(value));\n\
    \        assert(valid_value(lower));\n        return size() - count_xor_less(value,\
    \ lower);\n    }\n\n    int count_xor_range(UInt value, UInt lower, UInt upper)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        assert(lower <= upper);\n        return count_xor_less(value, upper)\
    \ -\n               count_xor_less(value, lower);\n    }\n\n    int order_of_key(UInt\
    \ key) const {\n        return count_xor_less(0, key);\n    }\n\n    int count_less(UInt\
    \ key) const {\n        return order_of_key(key);\n    }\n\n    int count_less_equal(UInt\
    \ key) const {\n        return count_xor_less_equal(0, key);\n    }\n\n    int\
    \ count_greater(UInt key) const {\n        return count_xor_greater(0, key);\n\
    \    }\n\n    int count_greater_equal(UInt key) const {\n        return count_xor_greater_equal(0,\
    \ key);\n    }\n\n    int count_range(UInt lower, UInt upper) const {\n      \
    \  return count_xor_range(0, lower, upper);\n    }\n\n    T prod_xor_equal(UInt\
    \ value, UInt target) const {\n        assert(valid_value(value));\n        assert(valid_value(target));\n\
    \        return prod(value ^ target);\n    }\n\n    T prod_xor_less(UInt value,\
    \ UInt upper) const {\n        assert(valid_value(value));\n        if (!valid_value(upper))\
    \ return all_prod();\n\n        const UInt effective_xor = lazy_xor ^ value;\n\
    \        T result = Monoid::id();\n        int node = 0;\n        for (int position\
    \ = BitWidth - 1;\n             position >= 0 && node != -1;\n             --position)\
    \ {\n            const int zero = bit(effective_xor, position);\n            if\
    \ (bit(upper, position) == 1) {\n                result =\n                  \
    \  Monoid::op(result,\n                               subtree_prod(nodes[node].child[zero]));\n\
    \                node = nodes[node].child[zero ^ 1];\n            } else {\n \
    \               node = nodes[node].child[zero];\n            }\n        }\n  \
    \      return result;\n    }\n\n    T prod_xor_less_equal(UInt value, UInt upper)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(upper));\n\
    \        if (upper == value_mask()) return all_prod();\n        return prod_xor_less(value,\
    \ upper + UInt(1));\n    }\n\n    T prod_xor_greater(UInt value, UInt lower) const\
    \ {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        if (lower == value_mask()) return Monoid::id();\n        return prod_xor_greater_equal_impl(value,\
    \ lower + UInt(1));\n    }\n\n    T prod_xor_greater_equal(UInt value, UInt lower)\
    \ const {\n        assert(valid_value(value));\n        assert(valid_value(lower));\n\
    \        return prod_xor_greater_equal_impl(value, lower);\n    }\n\n    T prod_xor_range(UInt\
    \ value, UInt lower, UInt upper) const {\n        assert(valid_value(value));\n\
    \        assert(valid_value(lower));\n        assert(lower <= upper);\n      \
    \  if (lower == upper) return Monoid::id();\n        if (!valid_value(upper))\
    \ {\n            return prod_xor_greater_equal(value, lower);\n        }\n   \
    \     return xor_range_impl(0,\n                              BitWidth - 1,\n\
    \                              lazy_xor ^ value,\n                           \
    \   lower,\n                              upper,\n                           \
    \   0,\n                              0)\n            .prod;\n    }\n\n    T prod_less(UInt\
    \ key) const {\n        return prod_xor_less(0, key);\n    }\n\n    T prod_less_equal(UInt\
    \ key) const {\n        return prod_xor_less_equal(0, key);\n    }\n\n    T prod_greater(UInt\
    \ key) const {\n        return prod_xor_greater(0, key);\n    }\n\n    T prod_greater_equal(UInt\
    \ key) const {\n        return prod_xor_greater_equal(0, key);\n    }\n\n    T\
    \ prod_range(UInt lower, UInt upper) const {\n        return prod_xor_range(0,\
    \ lower, upper);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif\
    \  // M1UNE_DS_BINARY_TRIE_MONOID_HPP\n"
  dependsOn:
  - monoid/concept.hpp
  isVerificationFile: false
  path: ds/ordered_set/binary_trie_monoid.hpp
  requiredBy: []
  timestamp: '2026-06-22 15:33:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/ordered_set/binary_trie_monoid.test.cpp
documentation_of: ds/ordered_set/binary_trie_monoid.hpp
layout: document
title: Binary Trie with Monoid
---

## Overview

`BinaryTrieMonoid` stores pairs `(key, value)`. For a query `(x, upper)`, it
returns the monoid product of every stored value whose key satisfies
`(key ^ x) < upper`.

This directly supports queries of the form

```text
prod(B_i) for every i such that (A_i ^ x) < a
```

by inserting each pair with `insert(A_i, B_i)` and calling
`prod_xor_less(x, a)`.

The monoid operation must be commutative because the selected entries do not
have an intrinsic order. Addition, multiplication, minimum, maximum, gcd, and
bitwise xor are suitable examples.

## Template Parameters

* `Monoid`: A monoid satisfying `m1une::monoid::IsMonoid`. Its operation must
  also be commutative.
* `UInt`: An unsigned integer type used for keys. Defaults to `std::uint32_t`.
* `BitWidth`: The number of low key bits used by the trie. Defaults to all bits
  of `UInt`. Keys and xor operands must fit in these bits.

An exclusive `upper` bound may be larger than the largest representable
`BitWidth`-bit key when that value fits in `UInt`. For example, with
`BitWidth == 30`, passing `1U << 30` includes every possible key.

## Methods

Let $B$ be `BitWidth`.

| Method | Description | Complexity |
| --- | --- | --- |
| `BinaryTrieMonoid()` | Constructs an empty trie. | $O(1)$ |
| `BinaryTrieMonoid(init)` | Constructs from `(key, value)` pairs. | $O(NB)$ |
| `BinaryTrieMonoid(first, last)` | Constructs from a range of `(key, value)` pairs. | $O(NB)$ |
| `BinaryTrieMonoid(keys, values)` | Constructs from parallel key and value vectors. | $O(NB)$ |
| `int size() const` | Returns the number of inserted pairs. | $O(1)$ |
| `bool empty() const` | Returns whether the trie is empty. | $O(1)$ |
| `node_id root() const` | Returns the root node handle. | $O(1)$ |
| `node_id find(UInt key) const` | Returns the leaf handle for `key`, or `null_node` if absent. | $O(B)$ |
| `const Node& node(node_id id) const` | Returns a read-only view of a node. | $O(1)$ |
| `size_t node_count() const` | Returns allocated nodes, including the root. | $O(1)$ |
| `void reserve(size_t n)` | Reserves storage for approximately `n` nodes. | $O(K)$ |
| `UInt xor_mask() const` | Returns the current lazy xor mask. | $O(1)$ |
| `void clear()` | Removes every pair and resets the lazy xor. | $O(1)$ |
| `node_id insert(UInt key, const T& value)` | Inserts one pair and returns its leaf handle. Duplicate keys are allowed. | $O(B)$ |
| `int count(UInt key) const` | Returns the number of pairs with this key. | $O(B)$ |
| `bool contains(UInt key) const` | Returns whether this key exists. | $O(B)$ |
| `T prod(UInt key) const` | Returns the product of values with exactly this key. | $O(B)$ |
| `T all_prod() const` | Returns the product of all stored values. | $O(1)$ |
| `int erase_all(UInt key)` | Removes all pairs with this key and returns their count. | $O(B)$ |
| `void xor_all(UInt value)` | Applies xor with `value` to every stored key. | $O(1)$ |

`node_id` is an integer handle and `null_node` is its invalid value. A `Node`
exposes `child[2]`, `count`, and `prod`. Handles remain valid across insertions
and erasures and can index user-owned metadata; `clear()` invalidates every old
handle except the root. References returned by `node()` may be invalidated by
insertion, `reserve()`, or `clear()`.

The child links describe the physically stored bit paths. After `xor_all`,
logical keys differ by `xor_mask()`; `find(key)` accounts for this mask
automatically. Here $K$ is the allocated node count. Erasing does not reclaim
nodes.

### XOR order statistics

| Method | Description | Complexity |
| --- | --- | --- |
| `UInt kth_xor(int k, UInt x) const` | Returns the 0-indexed `k`-th smallest result among `key ^ x`, including duplicate keys. | $O(B)$ |
| `UInt kth(int k) const` | Returns the 0-indexed `k`-th smallest key. | $O(B)$ |
| `UInt min() const`, `UInt max() const` | Returns the smallest or largest key. Requires a nonempty trie. | $O(B)$ |
| `UInt min_xor(UInt x) const`, `UInt max_xor(UInt x) const` | Returns the minimum or maximum result among `key ^ x`. Requires a nonempty trie. | $O(B)$ |

### XOR counts

| Method | Description | Complexity |
| --- | --- | --- |
| `int count_xor_equal(UInt x, UInt target) const` | Counts pairs satisfying `(key ^ x) == target`. | $O(B)$ |
| `int count_xor_less(UInt x, UInt upper) const` | Counts pairs satisfying `(key ^ x) < upper`. | $O(B)$ |
| `int count_xor_less_equal(UInt x, UInt upper) const` | Counts pairs satisfying `(key ^ x) <= upper`. | $O(B)$ |
| `int count_xor_greater(UInt x, UInt lower) const` | Counts pairs satisfying `(key ^ x) > lower`. | $O(B)$ |
| `int count_xor_greater_equal(UInt x, UInt lower) const` | Counts pairs satisfying `(key ^ x) >= lower`. | $O(B)$ |
| `int count_xor_range(UInt x, UInt lower, UInt upper) const` | Counts pairs satisfying `lower <= (key ^ x) < upper`. | $O(B)$ |

`count_less_xor(x, upper)` is a compatibility alias for
`count_xor_less(x, upper)`. The methods `order_of_key`, `count_less`,
`count_less_equal`, `count_greater`, `count_greater_equal`, and `count_range`
provide the same comparisons without an xor operand.

### XOR products

| Method | Description | Complexity |
| --- | --- | --- |
| `T prod_xor_equal(UInt x, UInt target) const` | Returns the product for pairs satisfying `(key ^ x) == target`. | $O(B)$ |
| `T prod_xor_less(UInt x, UInt upper) const` | Returns the product for pairs satisfying `(key ^ x) < upper`. | $O(B)$ |
| `T prod_xor_less_equal(UInt x, UInt upper) const` | Returns the product for pairs satisfying `(key ^ x) <= upper`. | $O(B)$ |
| `T prod_xor_greater(UInt x, UInt lower) const` | Returns the product for pairs satisfying `(key ^ x) > lower`. | $O(B)$ |
| `T prod_xor_greater_equal(UInt x, UInt lower) const` | Returns the product for pairs satisfying `(key ^ x) >= lower`. | $O(B)$ |
| `T prod_xor_range(UInt x, UInt lower, UInt upper) const` | Returns the product for pairs satisfying `lower <= (key ^ x) < upper`. | $O(B)$ |

When no pair satisfies a product query, it returns `Monoid::id()`.
The methods `prod_less`, `prod_less_equal`, `prod_greater`,
`prod_greater_equal`, and `prod_range` provide the same comparisons without an
xor operand.

## Example

```cpp
#include "ds/ordered_set/binary_trie_monoid.hpp"
#include "monoid/mul.hpp"

#include <cstdint>
#include <iostream>
#include <vector>

int main() {
    std::vector<std::uint32_t> A = {1, 2, 7, 7};
    std::vector<long long> B = {2, 3, 5, 11};

    using Product = m1une::monoid::Mul<long long>;
    m1une::ds::BinaryTrieMonoid<Product, std::uint32_t, 30> trie(A, B);

    std::uint32_t x = 3;
    std::uint32_t a = 4;

    // 1 ^ 3 = 2 and 2 ^ 3 = 1 are less than 4.
    // The answer is B[0] * B[1] = 2 * 3 = 6.
    std::cout << trie.prod_xor_less(x, a) << "\n";

    // Product for 1 <= (A[i] ^ x) < 5.
    std::cout << trie.prod_xor_range(x, 1, 5) << "\n";
}
```
