---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/segtree/segtree_beats.hpp
    title: Segment Tree Beats
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum
  bundledCode: "#line 1 \"verify/ds/segtree/segtree_beats.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\n\n#line\
    \ 1 \"ds/segtree/segtree_beats.hpp\"\n\n\n\n#include <algorithm>\n#include <cassert>\n\
    #include <concepts>\n#include <limits>\n#include <vector>\n\nnamespace m1une {\n\
    namespace ds {\n\n// Segment Tree Beats supporting range chmin/chmax/add and sum/min/max\
    \ queries.\ntemplate <std::signed_integral T = long long>\nstruct SegtreeBeats\
    \ {\n   private:\n    static constexpr T positive_infinity = std::numeric_limits<T>::max();\n\
    \    static constexpr T negative_infinity = std::numeric_limits<T>::lowest();\n\
    \n    struct Node {\n        T sum = 0;\n        T maximum = negative_infinity;\n\
    \        T second_maximum = negative_infinity;\n        T minimum = positive_infinity;\n\
    \        T second_minimum = positive_infinity;\n        T lazy_add = 0;\n    \
    \    int maximum_count = 0;\n        int minimum_count = 0;\n        int length\
    \ = 0;\n    };\n\n    int _n;\n    std::vector<Node> _nodes;\n\n    static Node\
    \ make_leaf(T value) {\n        Node node;\n        node.sum = value;\n      \
    \  node.maximum = value;\n        node.minimum = value;\n        node.maximum_count\
    \ = 1;\n        node.minimum_count = 1;\n        node.length = 1;\n        return\
    \ node;\n    }\n\n    static Node merge_nodes(const Node& left, const Node& right)\
    \ {\n        Node result;\n        result.sum = left.sum + right.sum;\n      \
    \  result.length = left.length + right.length;\n\n        result.maximum = std::max(left.maximum,\
    \ right.maximum);\n        result.maximum_count = 0;\n        result.second_maximum\
    \ = negative_infinity;\n        if (left.maximum == result.maximum) {\n      \
    \      result.maximum_count += left.maximum_count;\n            result.second_maximum\
    \ =\n                std::max(result.second_maximum, left.second_maximum);\n \
    \       } else {\n            result.second_maximum =\n                std::max(result.second_maximum,\
    \ left.maximum);\n        }\n        if (right.maximum == result.maximum) {\n\
    \            result.maximum_count += right.maximum_count;\n            result.second_maximum\
    \ =\n                std::max(result.second_maximum, right.second_maximum);\n\
    \        } else {\n            result.second_maximum =\n                std::max(result.second_maximum,\
    \ right.maximum);\n        }\n\n        result.minimum = std::min(left.minimum,\
    \ right.minimum);\n        result.minimum_count = 0;\n        result.second_minimum\
    \ = positive_infinity;\n        if (left.minimum == result.minimum) {\n      \
    \      result.minimum_count += left.minimum_count;\n            result.second_minimum\
    \ =\n                std::min(result.second_minimum, left.second_minimum);\n \
    \       } else {\n            result.second_minimum =\n                std::min(result.second_minimum,\
    \ left.minimum);\n        }\n        if (right.minimum == result.minimum) {\n\
    \            result.minimum_count += right.minimum_count;\n            result.second_minimum\
    \ =\n                std::min(result.second_minimum, right.second_minimum);\n\
    \        } else {\n            result.second_minimum =\n                std::min(result.second_minimum,\
    \ right.minimum);\n        }\n        return result;\n    }\n\n    void build(int\
    \ node, int left, int right, const std::vector<T>& values) {\n        if (right\
    \ - left == 1) {\n            _nodes[node] = make_leaf(values[left]);\n      \
    \      return;\n        }\n        int middle = left + (right - left) / 2;\n \
    \       build(node * 2, left, middle, values);\n        build(node * 2 + 1, middle,\
    \ right, values);\n        pull(node);\n    }\n\n    void pull(int node) {\n \
    \       _nodes[node] = merge_nodes(\n            _nodes[node * 2],\n         \
    \   _nodes[node * 2 + 1]\n        );\n    }\n\n    void apply_add(int node, T\
    \ value) {\n        Node& current = _nodes[node];\n        current.sum += value\
    \ * T(current.length);\n        current.maximum += value;\n        current.minimum\
    \ += value;\n        if (current.second_maximum != negative_infinity) {\n    \
    \        current.second_maximum += value;\n        }\n        if (current.second_minimum\
    \ != positive_infinity) {\n            current.second_minimum += value;\n    \
    \    }\n        current.lazy_add += value;\n    }\n\n    void apply_chmin(int\
    \ node, T value) {\n        Node& current = _nodes[node];\n        if (current.maximum\
    \ <= value) return;\n        current.sum +=\n            (value - current.maximum)\
    \ * T(current.maximum_count);\n        if (current.minimum == current.maximum)\
    \ {\n            current.minimum = value;\n        } else if (current.second_minimum\
    \ == current.maximum) {\n            current.second_minimum = value;\n       \
    \ }\n        current.maximum = value;\n    }\n\n    void apply_chmax(int node,\
    \ T value) {\n        Node& current = _nodes[node];\n        if (value <= current.minimum)\
    \ return;\n        current.sum +=\n            (value - current.minimum) * T(current.minimum_count);\n\
    \        if (current.maximum == current.minimum) {\n            current.maximum\
    \ = value;\n        } else if (current.second_maximum == current.minimum) {\n\
    \            current.second_maximum = value;\n        }\n        current.minimum\
    \ = value;\n    }\n\n    void push(int node) {\n        Node& current = _nodes[node];\n\
    \        if (current.length == 1) {\n            current.lazy_add = 0;\n     \
    \       return;\n        }\n        if (current.lazy_add != 0) {\n           \
    \ apply_add(node * 2, current.lazy_add);\n            apply_add(node * 2 + 1,\
    \ current.lazy_add);\n            current.lazy_add = 0;\n        }\n        apply_chmin(node\
    \ * 2, current.maximum);\n        apply_chmin(node * 2 + 1, current.maximum);\n\
    \        apply_chmax(node * 2, current.minimum);\n        apply_chmax(node * 2\
    \ + 1, current.minimum);\n    }\n\n    void range_chmin(\n        int node,\n\
    \        int left,\n        int right,\n        int query_left,\n        int query_right,\n\
    \        T value\n    ) {\n        Node& current = _nodes[node];\n        if (\n\
    \            query_right <= left ||\n            right <= query_left ||\n    \
    \        current.maximum <= value\n        ) {\n            return;\n        }\n\
    \        if (\n            query_left <= left &&\n            right <= query_right\
    \ &&\n            current.second_maximum < value\n        ) {\n            apply_chmin(node,\
    \ value);\n            return;\n        }\n        push(node);\n        int middle\
    \ = left + (right - left) / 2;\n        range_chmin(\n            node * 2,\n\
    \            left,\n            middle,\n            query_left,\n           \
    \ query_right,\n            value\n        );\n        range_chmin(\n        \
    \    node * 2 + 1,\n            middle,\n            right,\n            query_left,\n\
    \            query_right,\n            value\n        );\n        pull(node);\n\
    \    }\n\n    void range_chmax(\n        int node,\n        int left,\n      \
    \  int right,\n        int query_left,\n        int query_right,\n        T value\n\
    \    ) {\n        Node& current = _nodes[node];\n        if (\n            query_right\
    \ <= left ||\n            right <= query_left ||\n            value <= current.minimum\n\
    \        ) {\n            return;\n        }\n        if (\n            query_left\
    \ <= left &&\n            right <= query_right &&\n            value < current.second_minimum\n\
    \        ) {\n            apply_chmax(node, value);\n            return;\n   \
    \     }\n        push(node);\n        int middle = left + (right - left) / 2;\n\
    \        range_chmax(\n            node * 2,\n            left,\n            middle,\n\
    \            query_left,\n            query_right,\n            value\n      \
    \  );\n        range_chmax(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            query_left,\n            query_right,\n     \
    \       value\n        );\n        pull(node);\n    }\n\n    void range_add(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right,\n        T value\n    ) {\n        if (query_right <=\
    \ left || right <= query_left) return;\n        if (query_left <= left && right\
    \ <= query_right) {\n            apply_add(node, value);\n            return;\n\
    \        }\n        push(node);\n        int middle = left + (right - left) /\
    \ 2;\n        range_add(\n            node * 2,\n            left,\n         \
    \   middle,\n            query_left,\n            query_right,\n            value\n\
    \        );\n        range_add(\n            node * 2 + 1,\n            middle,\n\
    \            right,\n            query_left,\n            query_right,\n     \
    \       value\n        );\n        pull(node);\n    }\n\n    Node range_query(\n\
    \        int node,\n        int left,\n        int right,\n        int query_left,\n\
    \        int query_right\n    ) {\n        if (query_left <= left && right <=\
    \ query_right) {\n            return _nodes[node];\n        }\n        push(node);\n\
    \        int middle = left + (right - left) / 2;\n        if (query_right <= middle)\
    \ {\n            return range_query(\n                node * 2,\n            \
    \    left,\n                middle,\n                query_left,\n           \
    \     query_right\n            );\n        }\n        if (middle <= query_left)\
    \ {\n            return range_query(\n                node * 2 + 1,\n        \
    \        middle,\n                right,\n                query_left,\n      \
    \          query_right\n            );\n        }\n        return merge_nodes(\n\
    \            range_query(\n                node * 2,\n                left,\n\
    \                middle,\n                query_left,\n                query_right\n\
    \            ),\n            range_query(\n                node * 2 + 1,\n   \
    \             middle,\n                right,\n                query_left,\n \
    \               query_right\n            )\n        );\n    }\n\n   public:\n\
    \    SegtreeBeats() : _n(0) {}\n\n    explicit SegtreeBeats(int n)\n        :\
    \ _n(n) {\n        assert(0 <= n);\n        if (_n != 0) {\n            _nodes.resize(std::size_t(_n)\
    \ * 4);\n            std::vector<T> values(_n, T(0));\n            build(1, 0,\
    \ _n, values);\n        }\n    }\n\n    explicit SegtreeBeats(const std::vector<T>&\
    \ values)\n        : _n(int(values.size())),\n          _nodes(values.empty()\
    \ ? 0 : values.size() * 4) {\n        if (_n != 0) build(1, 0, _n, values);\n\
    \    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool empty()\
    \ const {\n        return _n == 0;\n    }\n\n    void chmin(int left, int right,\
    \ T value) {\n        assert(0 <= left && left <= right && right <= _n);\n   \
    \     if (left != right) {\n            range_chmin(1, 0, _n, left, right, value);\n\
    \        }\n    }\n\n    void chmax(int left, int right, T value) {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        if (left != right) {\n  \
    \          range_chmax(1, 0, _n, left, right, value);\n        }\n    }\n\n  \
    \  void add(int left, int right, T value) {\n        assert(0 <= left && left\
    \ <= right && right <= _n);\n        if (left != right) {\n            range_add(1,\
    \ 0, _n, left, right, value);\n        }\n    }\n\n    void range_chmin(int left,\
    \ int right, T value) {\n        chmin(left, right, value);\n    }\n\n    void\
    \ range_chmax(int left, int right, T value) {\n        chmax(left, right, value);\n\
    \    }\n\n    void range_add(int left, int right, T value) {\n        add(left,\
    \ right, value);\n    }\n\n    T sum(int left, int right) {\n        assert(0\
    \ <= left && left <= right && right <= _n);\n        return left == right\n  \
    \          ? T(0)\n            : range_query(1, 0, _n, left, right).sum;\n   \
    \ }\n\n    T min(int left, int right) {\n        assert(0 <= left && left < right\
    \ && right <= _n);\n        return range_query(1, 0, _n, left, right).minimum;\n\
    \    }\n\n    T max(int left, int right) {\n        assert(0 <= left && left <\
    \ right && right <= _n);\n        return range_query(1, 0, _n, left, right).maximum;\n\
    \    }\n\n    T range_sum(int left, int right) {\n        return sum(left, right);\n\
    \    }\n\n    T range_min(int left, int right) {\n        return min(left, right);\n\
    \    }\n\n    T range_max(int left, int right) {\n        return max(left, right);\n\
    \    }\n\n    T all_sum() const {\n        return _n == 0 ? T(0) : _nodes[1].sum;\n\
    \    }\n\n    T all_min() const {\n        assert(_n != 0);\n        return _nodes[1].minimum;\n\
    \    }\n\n    T all_max() const {\n        assert(_n != 0);\n        return _nodes[1].maximum;\n\
    \    }\n\n    T get(int index) {\n        assert(0 <= index && index < _n);\n\
    \        return sum(index, index + 1);\n    }\n\n    T operator[](int index) {\n\
    \        return get(index);\n    }\n\n    void set(int index, T value) {\n   \
    \     assert(0 <= index && index < _n);\n        T current = get(index);\n   \
    \     add(index, index + 1, value - current);\n    }\n\n    std::vector<T> to_vector()\
    \ {\n        std::vector<T> result(_n);\n        for (int index = 0; index < _n;\
    \ ++index) {\n            result[index] = get(index);\n        }\n        return\
    \ result;\n    }\n};\n\n}  // namespace ds\n}  // namespace m1une\n\n\n#line 4\
    \ \"verify/ds/segtree/segtree_beats.test.cpp\"\n\n#line 7 \"verify/ds/segtree/segtree_beats.test.cpp\"\
    \n#include <cstdint>\n#include <iostream>\n#include <numeric>\n#line 11 \"verify/ds/segtree/segtree_beats.test.cpp\"\
    \n\nnamespace {\n\nvoid test_randomized() {\n    std::uint64_t state = 1201;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 1500; ++trial) {\n        int size = int(random() % 100);\n        std::vector<long\
    \ long> values(size);\n        for (long long& value : values) {\n           \
    \ value = static_cast<long long>(random() % 201) - 100;\n        }\n        m1une::ds::SegtreeBeats<long\
    \ long> seg(values);\n\n        for (int operation = 0; operation < 1000; ++operation)\
    \ {\n            int left = int(random() % (size + 1));\n            int right\
    \ = int(random() % (size + 1));\n            if (right < left) std::swap(left,\
    \ right);\n            int type = int(random() % 8);\n            long long value\
    \ =\n                static_cast<long long>(random() % 101) - 50;\n\n        \
    \    if (type == 0) {\n                seg.chmin(left, right, value);\n      \
    \          for (int index = left; index < right; ++index) {\n                \
    \    values[index] = std::min(values[index], value);\n                }\n    \
    \        } else if (type == 1) {\n                seg.chmax(left, right, value);\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] = std::max(values[index], value);\n                }\n\
    \            } else if (type == 2) {\n                seg.add(left, right, value);\n\
    \                for (int index = left; index < right; ++index) {\n          \
    \          values[index] += value;\n                }\n            } else if (type\
    \ == 3 && left < right) {\n                [[maybe_unused]] long long expected\
    \ =\n                    *std::min_element(\n                        values.begin()\
    \ + left,\n                        values.begin() + right\n                  \
    \  );\n                assert(seg.min(left, right) == expected);\n           \
    \ } else if (type == 4 && left < right) {\n                [[maybe_unused]] long\
    \ long expected =\n                    *std::max_element(\n                  \
    \      values.begin() + left,\n                        values.begin() + right\n\
    \                    );\n                assert(seg.max(left, right) == expected);\n\
    \            } else if (type == 5 && size != 0) {\n                int index =\
    \ int(random() % size);\n                seg.set(index, value);\n            \
    \    values[index] = value;\n            } else {\n                [[maybe_unused]]\
    \ long long expected = std::accumulate(\n                    values.begin() +\
    \ left,\n                    values.begin() + right,\n                    0LL\n\
    \                );\n                assert(seg.sum(left, right) == expected);\n\
    \            }\n\n            assert(seg.to_vector() == values);\n           \
    \ assert(\n                seg.all_sum()\n                == std::accumulate(values.begin(),\
    \ values.end(), 0LL)\n            );\n            if (!values.empty()) {\n   \
    \             assert(\n                    seg.all_min()\n                   \
    \ == *std::min_element(values.begin(), values.end())\n                );\n   \
    \             assert(\n                    seg.all_max()\n                   \
    \ == *std::max_element(values.begin(), values.end())\n                );\n   \
    \         }\n        }\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_randomized();\n\
    \n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long long> values(n);\n\
    \    for (long long& value : values) std::cin >> value;\n    m1une::ds::SegtreeBeats<long\
    \ long> seg(values);\n\n    while (q--) {\n        int type, left, right;\n  \
    \      std::cin >> type >> left >> right;\n        if (type == 0) {\n        \
    \    long long value;\n            std::cin >> value;\n            seg.chmin(left,\
    \ right, value);\n        } else if (type == 1) {\n            long long value;\n\
    \            std::cin >> value;\n            seg.chmax(left, right, value);\n\
    \        } else if (type == 2) {\n            long long value;\n            std::cin\
    \ >> value;\n            seg.add(left, right, value);\n        } else {\n    \
    \        std::cout << seg.sum(left, right) << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum\"\
    \n\n#include \"../../../ds/segtree/segtree_beats.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <numeric>\n\
    #include <vector>\n\nnamespace {\n\nvoid test_randomized() {\n    std::uint64_t\
    \ state = 1201;\n    auto random = [&state]() {\n        state ^= state << 7;\n\
    \        state ^= state >> 9;\n        return state;\n    };\n\n    for (int trial\
    \ = 0; trial < 1500; ++trial) {\n        int size = int(random() % 100);\n   \
    \     std::vector<long long> values(size);\n        for (long long& value : values)\
    \ {\n            value = static_cast<long long>(random() % 201) - 100;\n     \
    \   }\n        m1une::ds::SegtreeBeats<long long> seg(values);\n\n        for\
    \ (int operation = 0; operation < 1000; ++operation) {\n            int left =\
    \ int(random() % (size + 1));\n            int right = int(random() % (size +\
    \ 1));\n            if (right < left) std::swap(left, right);\n            int\
    \ type = int(random() % 8);\n            long long value =\n                static_cast<long\
    \ long>(random() % 101) - 50;\n\n            if (type == 0) {\n              \
    \  seg.chmin(left, right, value);\n                for (int index = left; index\
    \ < right; ++index) {\n                    values[index] = std::min(values[index],\
    \ value);\n                }\n            } else if (type == 1) {\n          \
    \      seg.chmax(left, right, value);\n                for (int index = left;\
    \ index < right; ++index) {\n                    values[index] = std::max(values[index],\
    \ value);\n                }\n            } else if (type == 2) {\n          \
    \      seg.add(left, right, value);\n                for (int index = left; index\
    \ < right; ++index) {\n                    values[index] += value;\n         \
    \       }\n            } else if (type == 3 && left < right) {\n             \
    \   [[maybe_unused]] long long expected =\n                    *std::min_element(\n\
    \                        values.begin() + left,\n                        values.begin()\
    \ + right\n                    );\n                assert(seg.min(left, right)\
    \ == expected);\n            } else if (type == 4 && left < right) {\n       \
    \         [[maybe_unused]] long long expected =\n                    *std::max_element(\n\
    \                        values.begin() + left,\n                        values.begin()\
    \ + right\n                    );\n                assert(seg.max(left, right)\
    \ == expected);\n            } else if (type == 5 && size != 0) {\n          \
    \      int index = int(random() % size);\n                seg.set(index, value);\n\
    \                values[index] = value;\n            } else {\n              \
    \  [[maybe_unused]] long long expected = std::accumulate(\n                  \
    \  values.begin() + left,\n                    values.begin() + right,\n     \
    \               0LL\n                );\n                assert(seg.sum(left,\
    \ right) == expected);\n            }\n\n            assert(seg.to_vector() ==\
    \ values);\n            assert(\n                seg.all_sum()\n             \
    \   == std::accumulate(values.begin(), values.end(), 0LL)\n            );\n  \
    \          if (!values.empty()) {\n                assert(\n                 \
    \   seg.all_min()\n                    == *std::min_element(values.begin(), values.end())\n\
    \                );\n                assert(\n                    seg.all_max()\n\
    \                    == *std::max_element(values.begin(), values.end())\n    \
    \            );\n            }\n        }\n    }\n}\n\n}  // namespace\n\nint\
    \ main() {\n    test_randomized();\n\n    int n, q;\n    std::cin >> n >> q;\n\
    \    std::vector<long long> values(n);\n    for (long long& value : values) std::cin\
    \ >> value;\n    m1une::ds::SegtreeBeats<long long> seg(values);\n\n    while\
    \ (q--) {\n        int type, left, right;\n        std::cin >> type >> left >>\
    \ right;\n        if (type == 0) {\n            long long value;\n           \
    \ std::cin >> value;\n            seg.chmin(left, right, value);\n        } else\
    \ if (type == 1) {\n            long long value;\n            std::cin >> value;\n\
    \            seg.chmax(left, right, value);\n        } else if (type == 2) {\n\
    \            long long value;\n            std::cin >> value;\n            seg.add(left,\
    \ right, value);\n        } else {\n            std::cout << seg.sum(left, right)\
    \ << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - ds/segtree/segtree_beats.hpp
  isVerificationFile: true
  path: verify/ds/segtree/segtree_beats.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:55:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/segtree/segtree_beats.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/segtree/segtree_beats.test.cpp
- /verify/verify/ds/segtree/segtree_beats.test.cpp.html
title: verify/ds/segtree/segtree_beats.test.cpp
---
