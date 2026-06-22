---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/ordered_set/binary_trie_monoid.hpp
    title: Binary Trie with Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/add.hpp
    title: Add Monoid
  - icon: ':heavy_check_mark:'
    path: monoid/concept.hpp
    title: Monoid Concept
  - icon: ':heavy_check_mark:'
    path: monoid/mul.hpp
    title: Multiply Monoid
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"verify/ds/ordered_set/binary_trie_monoid.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"ds/ordered_set/binary_trie_monoid.hpp\"\
    \n\n\n\n#include <cassert>\n#include <cstdint>\n#include <initializer_list>\n\
    #include <limits>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \n#line 1 \"monoid/concept.hpp\"\n\n\n\n#include <concepts>\n\nnamespace m1une\
    \ {\nnamespace monoid {\n\n// Concept to check if a type satisfies the requirements\
    \ of a Monoid.\n// A Monoid must have a `value_type`, an identity element `id()`,\
    \ and an associative binary operation `op()`.\ntemplate <typename M>\nconcept\
    \ IsMonoid = requires(typename M::value_type a, typename M::value_type b) {\n\
    \    // 1. Must define `value_type`\n    typename M::value_type;\n\n    // 2.\
    \ Must have a static method `id()` returning `value_type`\n    { M::id() } ->\
    \ std::same_as<typename M::value_type>;\n\n    // 3. Must have a static method\
    \ `op(a, b)` returning `value_type`\n    { M::op(a, b) } -> std::same_as<typename\
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
    \ lower, upper);\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n\
    #line 1 \"monoid/add.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n//\
    \ Monoid for addition (Range Sum).\ntemplate <typename T>\nstruct Add {\n    using\
    \ value_type = T;\n\n    // Returns the identity element for addition, which is\
    \ 0.\n    static constexpr T id() {\n        return T(0);\n    }\n\n    // Returns\
    \ the sum of a and b.\n    static constexpr T op(const T& a, const T& b) {\n \
    \       return a + b;\n    }\n\n    static constexpr T inv(const T& x) {\n   \
    \     return -x;\n    }\n};\n\n}  // namespace monoid\n}  // namespace m1une\n\
    \n\n#line 1 \"monoid/mul.hpp\"\n\n\n\nnamespace m1une {\nnamespace monoid {\n\n\
    // Monoid for multiplication (Range Product).\ntemplate <typename T>\nstruct Mul\
    \ {\n    using value_type = T;\n\n    // Returns the identity element for multiplication,\
    \ which is 1.\n    static constexpr T id() {\n        return T(1);\n    }\n\n\
    \    // Returns the product of a and b.\n    static constexpr T op(const T& a,\
    \ const T& b) {\n        return a * b;\n    }\n};\n\n}  // namespace monoid\n\
    }  // namespace m1une\n\n\n#line 6 \"verify/ds/ordered_set/binary_trie_monoid.test.cpp\"\
    \n\n#include <algorithm>\n#line 10 \"verify/ds/ordered_set/binary_trie_monoid.test.cpp\"\
    \n#include <iostream>\n#line 13 \"verify/ds/ordered_set/binary_trie_monoid.test.cpp\"\
    \n\nvoid basic_test() {\n    using Product = m1une::monoid::Mul<long long>;\n\
    \    using ProductTrie =\n        m1une::ds::BinaryTrieMonoid<Product, std::uint32_t,\
    \ 10>;\n\n    ProductTrie product;\n    product.reserve(64);\n    const auto one_node\
    \ = product.insert(1, 2);\n    product.insert(2, 3);\n    product.insert(7, 5);\n\
    \    const auto seven_node = product.insert(7, 11);\n\n    assert(product.root()\
    \ == 0);\n    assert(product.find(1) == one_node);\n    assert(product.find(7)\
    \ == seven_node);\n    assert(product.find(6) == ProductTrie::null_node);\n  \
    \  assert(product.node(product.root()).count == 4);\n    assert(product.node(product.root()).prod\
    \ == 330);\n    assert(product.node(seven_node).count == 2);\n    assert(product.node(seven_node).prod\
    \ == 55);\n    assert(product.node_count() == 1 + 10 + 2 + 3);\n    assert(product.size()\
    \ == 4);\n    assert(product.count(7) == 2);\n    assert(product.prod(7) == 55);\n\
    \    assert(product.kth(0) == 1);\n    assert(product.kth(2) == 7);\n    assert(product.min()\
    \ == 1);\n    assert(product.max() == 7);\n    assert(product.kth_xor(0, 3) ==\
    \ 1);\n    assert(product.kth_xor(2, 3) == 4);\n    assert(product.min_xor(3)\
    \ == 1);\n    assert(product.max_xor(3) == 4);\n    assert(product.count_xor_equal(3,\
    \ 4) == 2);\n    assert(product.prod_xor_less(3, 4) == 6);\n    assert(product.count_xor_less(3,\
    \ 4) == 2);\n    assert(product.count_less_xor(3, 4) == 2);\n    assert(product.count_xor_less_equal(3,\
    \ 4) == 4);\n    assert(product.count_xor_greater(3, 2) == 2);\n    assert(product.count_xor_greater_equal(3,\
    \ 2) == 3);\n    assert(product.count_xor_range(3, 2, 5) == 3);\n    assert(product.prod_xor_equal(3,\
    \ 4) == 55);\n    assert(product.prod_xor_less_equal(3, 4) == 330);\n    assert(product.prod_xor_greater(3,\
    \ 2) == 55);\n    assert(product.prod_xor_greater_equal(3, 2) == 110);\n    assert(product.prod_xor_range(3,\
    \ 2, 5) == 110);\n    assert(product.prod_xor_less(3, 0) == 1);\n    assert(product.prod_xor_less(0,\
    \ 1024) == 330);\n    assert(product.prod_xor_range(3, 2, 1024) == 110);\n   \
    \ assert(product.order_of_key(7) == 2);\n    assert(product.count_less(7) == 2);\n\
    \    assert(product.count_less_equal(7) == 4);\n    assert(product.count_greater(2)\
    \ == 2);\n    assert(product.count_greater_equal(2) == 3);\n    assert(product.count_range(2,\
    \ 7) == 1);\n    assert(product.prod_less(7) == 6);\n    assert(product.prod_less_equal(7)\
    \ == 330);\n    assert(product.prod_greater(2) == 55);\n    assert(product.prod_greater_equal(2)\
    \ == 165);\n    assert(product.prod_range(2, 7) == 3);\n\n    product.xor_all(6);\n\
    \    assert(product.xor_mask() == 6);\n    assert(product.find(7 ^ 6) == seven_node);\n\
    \    assert(product.prod(7 ^ 6) == 55);\n    assert(product.prod_xor_less(5, 4)\
    \ == 6);\n    assert(product.erase_all(7 ^ 6) == 2);\n    assert(product.all_prod()\
    \ == 6);\n    product.clear();\n    assert(product.empty());\n    assert(product.node_count()\
    \ == 1);\n    assert(product.xor_mask() == 0);\n\n    std::vector<std::pair<std::uint32_t,\
    \ long long>> entries;\n    entries.emplace_back(4, 2);\n    entries.emplace_back(9,\
    \ 3);\n    ProductTrie from_range(entries.begin(), entries.end());\n    assert(from_range.all_prod()\
    \ == 6);\n}\n\nvoid randomized_test() {\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    using SumTrie =\n        m1une::ds::BinaryTrieMonoid<Sum, std::uint32_t,\
    \ 10>;\n\n    SumTrie trie;\n    std::vector<std::pair<std::uint32_t, long long>>\
    \ entries;\n    std::uint64_t seed = 123456789;\n\n    for (int query = 0; query\
    \ < 10000; ++query) {\n        seed = seed * 6364136223846793005ULL +\n      \
    \         1442695040888963407ULL;\n        const std::uint32_t key = std::uint32_t(seed\
    \ >> 32) & 1023U;\n        const std::uint32_t value = std::uint32_t(seed) & 1023U;\n\
    \        const int type = int(seed % 6);\n\n        if (type <= 1) {\n       \
    \     trie.insert(key, value);\n            entries.emplace_back(key, value);\n\
    \        } else if (type == 2) {\n            trie.xor_all(key);\n           \
    \ for (auto& entry : entries) entry.first ^= key;\n        } else if (type ==\
    \ 3) {\n            int expected_erased = 0;\n            for (const auto& entry\
    \ : entries) {\n                if (entry.first == key) ++expected_erased;\n \
    \           }\n            assert(trie.erase_all(key) == expected_erased);\n \
    \           entries.erase(\n                std::remove_if(\n                \
    \    entries.begin(), entries.end(),\n                    [&](const auto& entry)\
    \ {\n                        return entry.first == key;\n                    }),\n\
    \                entries.end());\n        } else if (type == 4) {\n          \
    \  int expected_count = 0;\n            long long expected_prod = 0;\n       \
    \     for (const auto& entry : entries) {\n                if (entry.first ==\
    \ key) {\n                    ++expected_count;\n                    expected_prod\
    \ += entry.second;\n                }\n            }\n            assert(trie.count(key)\
    \ == expected_count);\n            assert(trie.prod(key) == expected_prod);\n\
    \        } else {\n            const std::uint32_t upper = std::uint32_t(seed\
    \ >> 20) & 1023U;\n            const std::uint32_t target = std::uint32_t(seed\
    \ >> 12) & 1023U;\n            const std::uint32_t other = std::uint32_t(seed\
    \ >> 4) & 1023U;\n            const std::uint32_t lower = std::min(upper, other);\n\
    \            const std::uint32_t range_upper =\n                std::max(upper,\
    \ other) + 1;\n            int expected_count = 0;\n            long long expected_prod\
    \ = 0;\n            int expected_equal_count = 0;\n            long long expected_equal_prod\
    \ = 0;\n            int expected_less_equal_count = 0;\n            long long\
    \ expected_less_equal_prod = 0;\n            int expected_greater_count = 0;\n\
    \            long long expected_greater_prod = 0;\n            int expected_greater_equal_count\
    \ = 0;\n            long long expected_greater_equal_prod = 0;\n            int\
    \ expected_range_count = 0;\n            long long expected_range_prod = 0;\n\
    \            std::vector<std::uint32_t> xor_values;\n            xor_values.reserve(entries.size());\n\
    \            for (const auto& entry : entries) {\n                const std::uint32_t\
    \ xor_value = entry.first ^ key;\n                xor_values.push_back(xor_value);\n\
    \                if (xor_value == target) {\n                    ++expected_equal_count;\n\
    \                    expected_equal_prod += entry.second;\n                }\n\
    \                if (xor_value < upper) {\n                    ++expected_count;\n\
    \                    expected_prod += entry.second;\n                }\n     \
    \           if (xor_value <= upper) {\n                    ++expected_less_equal_count;\n\
    \                    expected_less_equal_prod += entry.second;\n             \
    \   }\n                if (xor_value > upper) {\n                    ++expected_greater_count;\n\
    \                    expected_greater_prod += entry.second;\n                }\n\
    \                if (xor_value >= upper) {\n                    ++expected_greater_equal_count;\n\
    \                    expected_greater_equal_prod += entry.second;\n          \
    \      }\n                if (lower <= xor_value && xor_value < range_upper) {\n\
    \                    ++expected_range_count;\n                    expected_range_prod\
    \ += entry.second;\n                }\n            }\n            std::sort(xor_values.begin(),\
    \ xor_values.end());\n\n            assert(trie.count_xor_equal(key, target) ==\n\
    \                   expected_equal_count);\n            assert(trie.prod_xor_equal(key,\
    \ target) ==\n                   expected_equal_prod);\n            assert(trie.count_xor_less(key,\
    \ upper) == expected_count);\n            assert(trie.count_less_xor(key, upper)\
    \ == expected_count);\n            assert(trie.prod_xor_less(key, upper) == expected_prod);\n\
    \            assert(trie.count_xor_less_equal(key, upper) ==\n               \
    \    expected_less_equal_count);\n            assert(trie.prod_xor_less_equal(key,\
    \ upper) ==\n                   expected_less_equal_prod);\n            assert(trie.count_xor_greater(key,\
    \ upper) ==\n                   expected_greater_count);\n            assert(trie.prod_xor_greater(key,\
    \ upper) ==\n                   expected_greater_prod);\n            assert(trie.count_xor_greater_equal(key,\
    \ upper) ==\n                   expected_greater_equal_count);\n            assert(trie.prod_xor_greater_equal(key,\
    \ upper) ==\n                   expected_greater_equal_prod);\n            assert(trie.count_xor_range(key,\
    \ lower, range_upper) ==\n                   expected_range_count);\n        \
    \    assert(trie.prod_xor_range(key, lower, range_upper) ==\n                \
    \   expected_range_prod);\n\n            if (!xor_values.empty()) {\n        \
    \        const int k = int(seed % xor_values.size());\n                assert(trie.kth_xor(k,\
    \ key) == xor_values[k]);\n                assert(trie.min_xor(key) == xor_values.front());\n\
    \                assert(trie.max_xor(key) == xor_values.back());\n           \
    \ }\n        }\n\n        assert(trie.size() == int(entries.size()));\n      \
    \  long long expected_all_prod = 0;\n        for (const auto& entry : entries)\
    \ {\n            expected_all_prod += entry.second;\n        }\n        assert(trie.all_prod()\
    \ == expected_all_prod);\n    }\n}\n\nint main() {\n    basic_test();\n    randomized_test();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../../ds/ordered_set/binary_trie_monoid.hpp\"\n#include \"../../../monoid/add.hpp\"\
    \n#include \"../../../monoid/mul.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <utility>\n#include <vector>\n\
    \nvoid basic_test() {\n    using Product = m1une::monoid::Mul<long long>;\n  \
    \  using ProductTrie =\n        m1une::ds::BinaryTrieMonoid<Product, std::uint32_t,\
    \ 10>;\n\n    ProductTrie product;\n    product.reserve(64);\n    const auto one_node\
    \ = product.insert(1, 2);\n    product.insert(2, 3);\n    product.insert(7, 5);\n\
    \    const auto seven_node = product.insert(7, 11);\n\n    assert(product.root()\
    \ == 0);\n    assert(product.find(1) == one_node);\n    assert(product.find(7)\
    \ == seven_node);\n    assert(product.find(6) == ProductTrie::null_node);\n  \
    \  assert(product.node(product.root()).count == 4);\n    assert(product.node(product.root()).prod\
    \ == 330);\n    assert(product.node(seven_node).count == 2);\n    assert(product.node(seven_node).prod\
    \ == 55);\n    assert(product.node_count() == 1 + 10 + 2 + 3);\n    assert(product.size()\
    \ == 4);\n    assert(product.count(7) == 2);\n    assert(product.prod(7) == 55);\n\
    \    assert(product.kth(0) == 1);\n    assert(product.kth(2) == 7);\n    assert(product.min()\
    \ == 1);\n    assert(product.max() == 7);\n    assert(product.kth_xor(0, 3) ==\
    \ 1);\n    assert(product.kth_xor(2, 3) == 4);\n    assert(product.min_xor(3)\
    \ == 1);\n    assert(product.max_xor(3) == 4);\n    assert(product.count_xor_equal(3,\
    \ 4) == 2);\n    assert(product.prod_xor_less(3, 4) == 6);\n    assert(product.count_xor_less(3,\
    \ 4) == 2);\n    assert(product.count_less_xor(3, 4) == 2);\n    assert(product.count_xor_less_equal(3,\
    \ 4) == 4);\n    assert(product.count_xor_greater(3, 2) == 2);\n    assert(product.count_xor_greater_equal(3,\
    \ 2) == 3);\n    assert(product.count_xor_range(3, 2, 5) == 3);\n    assert(product.prod_xor_equal(3,\
    \ 4) == 55);\n    assert(product.prod_xor_less_equal(3, 4) == 330);\n    assert(product.prod_xor_greater(3,\
    \ 2) == 55);\n    assert(product.prod_xor_greater_equal(3, 2) == 110);\n    assert(product.prod_xor_range(3,\
    \ 2, 5) == 110);\n    assert(product.prod_xor_less(3, 0) == 1);\n    assert(product.prod_xor_less(0,\
    \ 1024) == 330);\n    assert(product.prod_xor_range(3, 2, 1024) == 110);\n   \
    \ assert(product.order_of_key(7) == 2);\n    assert(product.count_less(7) == 2);\n\
    \    assert(product.count_less_equal(7) == 4);\n    assert(product.count_greater(2)\
    \ == 2);\n    assert(product.count_greater_equal(2) == 3);\n    assert(product.count_range(2,\
    \ 7) == 1);\n    assert(product.prod_less(7) == 6);\n    assert(product.prod_less_equal(7)\
    \ == 330);\n    assert(product.prod_greater(2) == 55);\n    assert(product.prod_greater_equal(2)\
    \ == 165);\n    assert(product.prod_range(2, 7) == 3);\n\n    product.xor_all(6);\n\
    \    assert(product.xor_mask() == 6);\n    assert(product.find(7 ^ 6) == seven_node);\n\
    \    assert(product.prod(7 ^ 6) == 55);\n    assert(product.prod_xor_less(5, 4)\
    \ == 6);\n    assert(product.erase_all(7 ^ 6) == 2);\n    assert(product.all_prod()\
    \ == 6);\n    product.clear();\n    assert(product.empty());\n    assert(product.node_count()\
    \ == 1);\n    assert(product.xor_mask() == 0);\n\n    std::vector<std::pair<std::uint32_t,\
    \ long long>> entries;\n    entries.emplace_back(4, 2);\n    entries.emplace_back(9,\
    \ 3);\n    ProductTrie from_range(entries.begin(), entries.end());\n    assert(from_range.all_prod()\
    \ == 6);\n}\n\nvoid randomized_test() {\n    using Sum = m1une::monoid::Add<long\
    \ long>;\n    using SumTrie =\n        m1une::ds::BinaryTrieMonoid<Sum, std::uint32_t,\
    \ 10>;\n\n    SumTrie trie;\n    std::vector<std::pair<std::uint32_t, long long>>\
    \ entries;\n    std::uint64_t seed = 123456789;\n\n    for (int query = 0; query\
    \ < 10000; ++query) {\n        seed = seed * 6364136223846793005ULL +\n      \
    \         1442695040888963407ULL;\n        const std::uint32_t key = std::uint32_t(seed\
    \ >> 32) & 1023U;\n        const std::uint32_t value = std::uint32_t(seed) & 1023U;\n\
    \        const int type = int(seed % 6);\n\n        if (type <= 1) {\n       \
    \     trie.insert(key, value);\n            entries.emplace_back(key, value);\n\
    \        } else if (type == 2) {\n            trie.xor_all(key);\n           \
    \ for (auto& entry : entries) entry.first ^= key;\n        } else if (type ==\
    \ 3) {\n            int expected_erased = 0;\n            for (const auto& entry\
    \ : entries) {\n                if (entry.first == key) ++expected_erased;\n \
    \           }\n            assert(trie.erase_all(key) == expected_erased);\n \
    \           entries.erase(\n                std::remove_if(\n                \
    \    entries.begin(), entries.end(),\n                    [&](const auto& entry)\
    \ {\n                        return entry.first == key;\n                    }),\n\
    \                entries.end());\n        } else if (type == 4) {\n          \
    \  int expected_count = 0;\n            long long expected_prod = 0;\n       \
    \     for (const auto& entry : entries) {\n                if (entry.first ==\
    \ key) {\n                    ++expected_count;\n                    expected_prod\
    \ += entry.second;\n                }\n            }\n            assert(trie.count(key)\
    \ == expected_count);\n            assert(trie.prod(key) == expected_prod);\n\
    \        } else {\n            const std::uint32_t upper = std::uint32_t(seed\
    \ >> 20) & 1023U;\n            const std::uint32_t target = std::uint32_t(seed\
    \ >> 12) & 1023U;\n            const std::uint32_t other = std::uint32_t(seed\
    \ >> 4) & 1023U;\n            const std::uint32_t lower = std::min(upper, other);\n\
    \            const std::uint32_t range_upper =\n                std::max(upper,\
    \ other) + 1;\n            int expected_count = 0;\n            long long expected_prod\
    \ = 0;\n            int expected_equal_count = 0;\n            long long expected_equal_prod\
    \ = 0;\n            int expected_less_equal_count = 0;\n            long long\
    \ expected_less_equal_prod = 0;\n            int expected_greater_count = 0;\n\
    \            long long expected_greater_prod = 0;\n            int expected_greater_equal_count\
    \ = 0;\n            long long expected_greater_equal_prod = 0;\n            int\
    \ expected_range_count = 0;\n            long long expected_range_prod = 0;\n\
    \            std::vector<std::uint32_t> xor_values;\n            xor_values.reserve(entries.size());\n\
    \            for (const auto& entry : entries) {\n                const std::uint32_t\
    \ xor_value = entry.first ^ key;\n                xor_values.push_back(xor_value);\n\
    \                if (xor_value == target) {\n                    ++expected_equal_count;\n\
    \                    expected_equal_prod += entry.second;\n                }\n\
    \                if (xor_value < upper) {\n                    ++expected_count;\n\
    \                    expected_prod += entry.second;\n                }\n     \
    \           if (xor_value <= upper) {\n                    ++expected_less_equal_count;\n\
    \                    expected_less_equal_prod += entry.second;\n             \
    \   }\n                if (xor_value > upper) {\n                    ++expected_greater_count;\n\
    \                    expected_greater_prod += entry.second;\n                }\n\
    \                if (xor_value >= upper) {\n                    ++expected_greater_equal_count;\n\
    \                    expected_greater_equal_prod += entry.second;\n          \
    \      }\n                if (lower <= xor_value && xor_value < range_upper) {\n\
    \                    ++expected_range_count;\n                    expected_range_prod\
    \ += entry.second;\n                }\n            }\n            std::sort(xor_values.begin(),\
    \ xor_values.end());\n\n            assert(trie.count_xor_equal(key, target) ==\n\
    \                   expected_equal_count);\n            assert(trie.prod_xor_equal(key,\
    \ target) ==\n                   expected_equal_prod);\n            assert(trie.count_xor_less(key,\
    \ upper) == expected_count);\n            assert(trie.count_less_xor(key, upper)\
    \ == expected_count);\n            assert(trie.prod_xor_less(key, upper) == expected_prod);\n\
    \            assert(trie.count_xor_less_equal(key, upper) ==\n               \
    \    expected_less_equal_count);\n            assert(trie.prod_xor_less_equal(key,\
    \ upper) ==\n                   expected_less_equal_prod);\n            assert(trie.count_xor_greater(key,\
    \ upper) ==\n                   expected_greater_count);\n            assert(trie.prod_xor_greater(key,\
    \ upper) ==\n                   expected_greater_prod);\n            assert(trie.count_xor_greater_equal(key,\
    \ upper) ==\n                   expected_greater_equal_count);\n            assert(trie.prod_xor_greater_equal(key,\
    \ upper) ==\n                   expected_greater_equal_prod);\n            assert(trie.count_xor_range(key,\
    \ lower, range_upper) ==\n                   expected_range_count);\n        \
    \    assert(trie.prod_xor_range(key, lower, range_upper) ==\n                \
    \   expected_range_prod);\n\n            if (!xor_values.empty()) {\n        \
    \        const int k = int(seed % xor_values.size());\n                assert(trie.kth_xor(k,\
    \ key) == xor_values[k]);\n                assert(trie.min_xor(key) == xor_values.front());\n\
    \                assert(trie.max_xor(key) == xor_values.back());\n           \
    \ }\n        }\n\n        assert(trie.size() == int(entries.size()));\n      \
    \  long long expected_all_prod = 0;\n        for (const auto& entry : entries)\
    \ {\n            expected_all_prod += entry.second;\n        }\n        assert(trie.all_prod()\
    \ == expected_all_prod);\n    }\n}\n\nint main() {\n    basic_test();\n    randomized_test();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - ds/ordered_set/binary_trie_monoid.hpp
  - monoid/concept.hpp
  - monoid/add.hpp
  - monoid/mul.hpp
  isVerificationFile: true
  path: verify/ds/ordered_set/binary_trie_monoid.test.cpp
  requiredBy: []
  timestamp: '2026-06-22 15:33:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/ordered_set/binary_trie_monoid.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/ordered_set/binary_trie_monoid.test.cpp
- /verify/verify/ds/ordered_set/binary_trie_monoid.test.cpp.html
title: verify/ds/ordered_set/binary_trie_monoid.test.cpp
---
