---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/modint.hpp
    title: ModInt
  - icon: ':heavy_check_mark:'
    path: matroid/all.hpp
    title: Matroid All
  - icon: ':heavy_check_mark:'
    path: matroid/graphic_matroid.hpp
    title: Graphic Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/linear_matroid.hpp
    title: Linear Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/matroid_intersection.hpp
    title: Matroid Intersection
  - icon: ':heavy_check_mark:'
    path: matroid/partition_matroid.hpp
    title: Partition Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/uniform_matroid.hpp
    title: Uniform Matroid
  - icon: ':heavy_check_mark:'
    path: matroid/weighted_matroid_intersection.hpp
    title: Weighted Matroid Intersection
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
  bundledCode: "#line 1 \"verify/matroid/matroids.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\
    \n\n#include <cassert>\n#include <cstdint>\n#include <iostream>\n#include <random>\n\
    #include <utility>\n#include <vector>\n\n#line 1 \"math/modint.hpp\"\n\n\n\n#line\
    \ 6 \"math/modint.hpp\"\n#include <type_traits>\n#line 8 \"math/modint.hpp\"\n\
    \nnamespace m1une {\nnamespace math {\n\ntemplate <uint32_t Modulus>\nstruct ModInt\
    \ {\n    static_assert(0 < Modulus, \"Modulus must be positive\");\n\n   private:\n\
    \    uint32_t _v;\n\n   public:\n    static constexpr uint32_t mod() {\n     \
    \   return Modulus;\n    }\n\n    static constexpr ModInt raw(uint32_t v) noexcept\
    \ {\n        ModInt x;\n        x._v = v;\n        return x;\n    }\n\n    constexpr\
    \ ModInt() noexcept : _v(0) {}\n\n    template <class Integer, std::enable_if_t<std::is_integral_v<Integer>,\
    \ int> = 0>\n    constexpr ModInt(Integer v) noexcept {\n        if constexpr\
    \ (std::is_signed_v<Integer>) {\n            int64_t x = static_cast<int64_t>(v)\
    \ % static_cast<int64_t>(Modulus);\n            if (x < 0) x += Modulus;\n   \
    \         _v = static_cast<uint32_t>(x);\n        } else {\n            _v = static_cast<uint32_t>(static_cast<uint64_t>(v)\
    \ % Modulus);\n        }\n    }\n\n    constexpr uint32_t val() const noexcept\
    \ {\n        return _v;\n    }\n\n    constexpr ModInt& operator++() noexcept\
    \ {\n        _v++;\n        if (_v == Modulus) _v = 0;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator--() noexcept {\n        if (_v == 0)\
    \ _v = Modulus;\n        _v--;\n        return *this;\n    }\n\n    constexpr\
    \ ModInt operator++(int) noexcept {\n        ModInt res = *this;\n        ++*this;\n\
    \        return res;\n    }\n\n    constexpr ModInt operator--(int) noexcept {\n\
    \        ModInt res = *this;\n        --*this;\n        return res;\n    }\n\n\
    \    constexpr ModInt& operator+=(const ModInt& rhs) noexcept {\n        _v +=\
    \ rhs._v;\n        if (_v >= Modulus) _v -= Modulus;\n        return *this;\n\
    \    }\n\n    constexpr ModInt& operator-=(const ModInt& rhs) noexcept {\n   \
    \     _v -= rhs._v;\n        if (_v >= Modulus) _v += Modulus;\n        return\
    \ *this;\n    }\n\n    constexpr ModInt& operator*=(const ModInt& rhs) noexcept\
    \ {\n        uint64_t z = _v;\n        z *= rhs._v;\n        _v = static_cast<uint32_t>(z\
    \ % Modulus);\n        return *this;\n    }\n\n    constexpr ModInt& operator/=(const\
    \ ModInt& rhs) noexcept {\n        return *this *= rhs.inv();\n    }\n\n    constexpr\
    \ ModInt operator+(const ModInt& rhs) const noexcept {\n        return ModInt(*this)\
    \ += rhs;\n    }\n    constexpr ModInt operator-(const ModInt& rhs) const noexcept\
    \ {\n        return ModInt(*this) -= rhs;\n    }\n    constexpr ModInt operator*(const\
    \ ModInt& rhs) const noexcept {\n        return ModInt(*this) *= rhs;\n    }\n\
    \    constexpr ModInt operator/(const ModInt& rhs) const noexcept {\n        return\
    \ ModInt(*this) /= rhs;\n    }\n\n    constexpr bool operator==(const ModInt&\
    \ rhs) const noexcept {\n        return _v == rhs._v;\n    }\n    constexpr bool\
    \ operator!=(const ModInt& rhs) const noexcept {\n        return _v != rhs._v;\n\
    \    }\n\n    constexpr ModInt pow(long long n) const noexcept {\n        ModInt\
    \ res = raw(1), x = *this;\n        while (n > 0) {\n            if (n & 1) res\
    \ *= x;\n            x *= x;\n            n >>= 1;\n        }\n        return\
    \ res;\n    }\n\n    constexpr ModInt inv() const noexcept {\n        int64_t\
    \ a = _v, b = Modulus, u = 1, v = 0;\n        while (b) {\n            int64_t\
    \ t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n        \
    \    u -= t * v;\n            std::swap(u, v);\n        }\n        if (u < 0)\
    \ u += Modulus;\n        return raw(static_cast<uint32_t>(u));\n    }\n\n    friend\
    \ std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {\n        return\
    \ os << rhs._v;\n    }\n\n    friend std::istream& operator>>(std::istream& is,\
    \ ModInt& rhs) {\n        long long v;\n        is >> v;\n        rhs = ModInt(v);\n\
    \        return is;\n    }\n};\n\nusing modint998244353 = ModInt<998244353>;\n\
    using modint1000000007 = ModInt<1000000007>;\n\n}  // namespace math\n}  // namespace\
    \ m1une\n\n\n#line 1 \"matroid/all.hpp\"\n\n\n\n#line 1 \"matroid/graphic_matroid.hpp\"\
    \n\n\n\n#line 5 \"matroid/graphic_matroid.hpp\"\n#include <numeric>\n#line 8 \"\
    matroid/graphic_matroid.hpp\"\n\nnamespace m1une {\nnamespace matroid {\n\nclass\
    \ GraphicMatroid {\n   private:\n    int _vertex_count;\n    std::vector<std::pair<int,\
    \ int>> _edges;\n\n   public:\n    GraphicMatroid() : _vertex_count(0) {}\n\n\
    \    GraphicMatroid(int vertex_count, std::vector<std::pair<int, int>> edges)\n\
    \        : _vertex_count(vertex_count), _edges(std::move(edges)) {\n        assert(0\
    \ <= vertex_count);\n#ifndef NDEBUG\n        for (auto [u, v] : _edges) {\n  \
    \          assert(0 <= u && u < _vertex_count);\n            assert(0 <= v &&\
    \ v < _vertex_count);\n        }\n#endif\n    }\n\n    int size() const {\n  \
    \      return int(_edges.size());\n    }\n\n    int vertex_count() const {\n \
    \       return _vertex_count;\n    }\n\n    const std::vector<std::pair<int, int>>&\
    \ edges() const {\n        return _edges;\n    }\n\n    bool independent(const\
    \ std::vector<int>& subset) const {\n        std::vector<int> parent_or_size(_vertex_count,\
    \ -1);\n        auto leader = [&](auto&& self, int v) -> int {\n            if\
    \ (parent_or_size[v] < 0) return v;\n            return parent_or_size[v] = self(self,\
    \ parent_or_size[v]);\n        };\n\n        for (int element : subset) {\n  \
    \          assert(0 <= element && element < int(_edges.size()));\n           \
    \ auto [u, v] = _edges[element];\n            u = leader(leader, u);\n       \
    \     v = leader(leader, v);\n            if (u == v) return false;\n        \
    \    if (-parent_or_size[u] < -parent_or_size[v]) std::swap(u, v);\n         \
    \   parent_or_size[u] += parent_or_size[v];\n            parent_or_size[v] = u;\n\
    \        }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\n}  // namespace\
    \ matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/linear_matroid.hpp\"\n\
    \n\n\n#include <array>\n#line 9 \"matroid/linear_matroid.hpp\"\n\nnamespace m1une\
    \ {\nnamespace matroid {\n\ntemplate <class Field>\nclass LinearMatroid {\n  \
    \ private:\n    int _dimension;\n    std::vector<std::vector<Field>> _vectors;\n\
    \n   public:\n    LinearMatroid() : _dimension(0) {}\n\n    explicit LinearMatroid(std::vector<std::vector<Field>>\
    \ vectors)\n        : _dimension(vectors.empty() ? 0 : int(vectors[0].size())),\n\
    \          _vectors(std::move(vectors)) {\n#ifndef NDEBUG\n        for (const\
    \ auto& vector : _vectors) assert(int(vector.size()) == _dimension);\n#endif\n\
    \    }\n\n    int size() const {\n        return int(_vectors.size());\n    }\n\
    \n    int dimension() const {\n        return _dimension;\n    }\n\n    const\
    \ std::vector<std::vector<Field>>& vectors() const {\n        return _vectors;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   if (int(subset.size()) > _dimension) return false;\n\n        std::vector<std::vector<Field>>\
    \ basis(_dimension);\n        std::vector<char> has_pivot(_dimension, false);\n\
    \        for (int element : subset) {\n            assert(0 <= element && element\
    \ < int(_vectors.size()));\n            std::vector<Field> vector = _vectors[element];\n\
    \            bool inserted = false;\n            for (int column = 0; column <\
    \ _dimension; column++) {\n                if (vector[column] == Field(0)) continue;\n\
    \                if (!has_pivot[column]) {\n                    Field inverse\
    \ = Field(1) / vector[column];\n                    for (int j = column; j < _dimension;\
    \ j++) vector[j] *= inverse;\n                    basis[column] = std::move(vector);\n\
    \                    has_pivot[column] = true;\n                    inserted =\
    \ true;\n                    break;\n                }\n                Field\
    \ factor = vector[column];\n                for (int j = column; j < _dimension;\
    \ j++) {\n                    vector[j] -= factor * basis[column][j];\n      \
    \          }\n            }\n            if (!inserted) return false;\n      \
    \  }\n        return true;\n    }\n\n    bool operator()(const std::vector<int>&\
    \ subset) const {\n        return independent(subset);\n    }\n};\n\nclass BinaryLinearMatroid\
    \ {\n   private:\n    std::vector<std::uint64_t> _vectors;\n\n   public:\n   \
    \ BinaryLinearMatroid() = default;\n    explicit BinaryLinearMatroid(std::vector<std::uint64_t>\
    \ vectors)\n        : _vectors(std::move(vectors)) {}\n\n    int size() const\
    \ {\n        return int(_vectors.size());\n    }\n\n    int dimension() const\
    \ {\n        return 64;\n    }\n\n    const std::vector<std::uint64_t>& vectors()\
    \ const {\n        return _vectors;\n    }\n\n    bool independent(const std::vector<int>&\
    \ subset) const {\n        if (subset.size() > 64) return false;\n\n        std::array<std::uint64_t,\
    \ 64> basis = {};\n        for (int element : subset) {\n            assert(0\
    \ <= element && element < int(_vectors.size()));\n            std::uint64_t value\
    \ = _vectors[element];\n            for (int bit = 63; bit >= 0; bit--) {\n  \
    \              if ((value >> bit & 1) == 0) continue;\n                if (basis[bit]\
    \ == 0) {\n                    basis[bit] = value;\n                    break;\n\
    \                }\n                value ^= basis[bit];\n            }\n    \
    \        if (value == 0) return false;\n        }\n        return true;\n    }\n\
    \n    bool operator()(const std::vector<int>& subset) const {\n        return\
    \ independent(subset);\n    }\n};\n\n}  // namespace matroid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"matroid/matroid_intersection.hpp\"\n\n\n\n#include <algorithm>\n\
    #line 7 \"matroid/matroid_intersection.hpp\"\n\nnamespace m1une {\nnamespace matroid\
    \ {\n\ntemplate <class IndependenceOracle1, class IndependenceOracle2>\nstd::vector<int>\
    \ matroid_intersection(int ground_size, IndependenceOracle1 oracle1,\n       \
    \                               IndependenceOracle2 oracle2) {\n    assert(0 <=\
    \ ground_size);\n\n    std::vector<char> selected(ground_size, false);\n    std::vector<int>\
    \ elements;\n    std::vector<int> position(ground_size, -1);\n\n    while (true)\
    \ {\n        std::vector<char> source(ground_size, false);\n        std::vector<char>\
    \ sink(ground_size, false);\n        std::vector<int> distance(ground_size, -1);\n\
    \        std::vector<int> previous(ground_size, -1);\n        std::vector<int>\
    \ queue;\n        queue.reserve(ground_size);\n\n        for (int x = 0; x < ground_size;\
    \ x++) {\n            if (selected[x]) continue;\n            elements.push_back(x);\n\
    \            source[x] = oracle1(elements);\n            sink[x] = oracle2(elements);\n\
    \            elements.pop_back();\n            if (source[x]) {\n            \
    \    distance[x] = 0;\n                queue.push_back(x);\n            }\n  \
    \      }\n\n        int target = -1;\n        for (int head = 0; head < int(queue.size())\
    \ && target == -1; head++) {\n            int v = queue[head];\n            if\
    \ (!selected[v] && sink[v]) {\n                target = v;\n                break;\n\
    \            }\n\n            if (selected[v]) {\n                int index =\
    \ position[v];\n                assert(index != -1 && elements[index] == v);\n\
    \                for (int x = 0; x < ground_size; x++) {\n                   \
    \ if (selected[x] || distance[x] != -1) continue;\n                    elements[index]\
    \ = x;\n                    bool independent = oracle1(elements);\n          \
    \          elements[index] = v;\n                    if (!independent) continue;\n\
    \                    distance[x] = distance[v] + 1;\n                    previous[x]\
    \ = v;\n                    queue.push_back(x);\n                }\n         \
    \   } else {\n                for (int y : elements) {\n                    if\
    \ (distance[y] != -1) continue;\n                    int index = position[y];\n\
    \                    assert(index != -1 && elements[index] == y);\n          \
    \          elements[index] = v;\n                    bool independent = oracle2(elements);\n\
    \                    elements[index] = y;\n                    if (!independent)\
    \ continue;\n                    distance[y] = distance[v] + 1;\n            \
    \        previous[y] = v;\n                    queue.push_back(y);\n         \
    \       }\n            }\n        }\n\n        if (target == -1) break;\n    \
    \    for (int v = target; v != -1; v = previous[v]) selected[v] = !selected[v];\n\
    \n        elements.clear();\n        std::fill(position.begin(), position.end(),\
    \ -1);\n        for (int x = 0; x < ground_size; x++) {\n            if (!selected[x])\
    \ continue;\n            position[x] = int(elements.size());\n            elements.push_back(x);\n\
    \        }\n\n#ifndef NDEBUG\n        assert(oracle1(elements));\n        assert(oracle2(elements));\n\
    #endif\n    }\n\n    return elements;\n}\n\n}  // namespace matroid\n}  // namespace\
    \ m1une\n\n\n#line 1 \"matroid/partition_matroid.hpp\"\n\n\n\n#line 8 \"matroid/partition_matroid.hpp\"\
    \n\nnamespace m1une {\nnamespace matroid {\n\nclass PartitionMatroid {\n   private:\n\
    \    std::vector<int> _group;\n    std::vector<int> _capacity;\n\n    void validate()\
    \ const {\n#ifndef NDEBUG\n        for (int capacity : _capacity) assert(0 <=\
    \ capacity);\n        for (int group : _group) assert(0 <= group && group < int(_capacity.size()));\n\
    #endif\n    }\n\n   public:\n    PartitionMatroid() = default;\n\n    explicit\
    \ PartitionMatroid(std::vector<int> group) : _group(std::move(group)) {\n    \
    \    int group_count = 0;\n        for (int value : _group) {\n            assert(0\
    \ <= value);\n            group_count = std::max(group_count, value + 1);\n  \
    \      }\n        _capacity.assign(group_count, 1);\n    }\n\n    PartitionMatroid(std::vector<int>\
    \ group, std::vector<int> capacity)\n        : _group(std::move(group)), _capacity(std::move(capacity))\
    \ {\n        validate();\n    }\n\n    int size() const {\n        return int(_group.size());\n\
    \    }\n\n    int group_count() const {\n        return int(_capacity.size());\n\
    \    }\n\n    const std::vector<int>& groups() const {\n        return _group;\n\
    \    }\n\n    const std::vector<int>& capacities() const {\n        return _capacity;\n\
    \    }\n\n    bool independent(const std::vector<int>& subset) const {\n     \
    \   std::vector<int> count(_capacity.size(), 0);\n        for (int element : subset)\
    \ {\n            assert(0 <= element && element < int(_group.size()));\n     \
    \       int group = _group[element];\n            if (++count[group] > _capacity[group])\
    \ return false;\n        }\n        return true;\n    }\n\n    bool operator()(const\
    \ std::vector<int>& subset) const {\n        return independent(subset);\n   \
    \ }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/uniform_matroid.hpp\"\
    \n\n\n\n#line 6 \"matroid/uniform_matroid.hpp\"\n\nnamespace m1une {\nnamespace\
    \ matroid {\n\nclass UniformMatroid {\n   private:\n    int _ground_size;\n  \
    \  int _rank;\n\n   public:\n    UniformMatroid() : _ground_size(0), _rank(0)\
    \ {}\n    UniformMatroid(int ground_size, int rank) : _ground_size(ground_size),\
    \ _rank(rank) {\n        assert(0 <= rank && rank <= ground_size);\n    }\n\n\
    \    int size() const {\n        return _ground_size;\n    }\n\n    int rank()\
    \ const {\n        return _rank;\n    }\n\n    bool independent(const std::vector<int>&\
    \ subset) const {\n        return int(subset.size()) <= _rank;\n    }\n\n    bool\
    \ operator()(const std::vector<int>& subset) const {\n        return independent(subset);\n\
    \    }\n};\n\n}  // namespace matroid\n}  // namespace m1une\n\n\n#line 1 \"matroid/weighted_matroid_intersection.hpp\"\
    \n\n\n\n#line 6 \"matroid/weighted_matroid_intersection.hpp\"\n#include <queue>\n\
    #line 10 \"matroid/weighted_matroid_intersection.hpp\"\n\nnamespace m1une {\n\
    namespace matroid {\n\ntemplate <class Weight>\nstruct WeightedMatroidIntersectionResult\
    \ {\n    Weight total_weight = Weight(0);\n    std::vector<int> elements;\n\n\
    \    int size() const {\n        return int(elements.size());\n    }\n\n    bool\
    \ empty() const {\n        return elements.empty();\n    }\n};\n\nnamespace weighted_intersection_detail\
    \ {\n\ntemplate <class Weight>\nstruct QueueGreater {\n    bool operator()(const\
    \ std::pair<Weight, int>& lhs,\n                    const std::pair<Weight, int>&\
    \ rhs) const {\n        if (rhs.first < lhs.first) return true;\n        if (lhs.first\
    \ < rhs.first) return false;\n        return lhs.second > rhs.second;\n    }\n\
    };\n\ntemplate <bool Maximize, class Weight>\nWeight objective_cost(const Weight&\
    \ change) {\n    if constexpr (Maximize) {\n        return Weight(0) - change;\n\
    \    } else {\n        return change;\n    }\n}\n\ntemplate <bool Maximize, class\
    \ Weight, class IndependenceOracle1, class IndependenceOracle2,\n          class\
    \ OnSolution>\nWeightedMatroidIntersectionResult<Weight> solve(\n    int ground_size,\
    \ const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2\
    \ oracle2, OnSolution on_solution) {\n    static_assert(!std::is_arithmetic_v<Weight>\
    \ || std::is_signed_v<Weight>,\n                  \"Weight must support negative\
    \ intermediate values\");\n    assert(0 <= ground_size);\n    assert(int(weight.size())\
    \ == ground_size);\n\n    const int source_vertex = ground_size;\n    const int\
    \ sink_vertex = ground_size + 1;\n    const int vertex_count = ground_size + 2;\n\
    \    std::vector<char> selected(ground_size, false);\n    std::vector<int> elements;\n\
    \    std::vector<int> position(ground_size, -1);\n    std::vector<Weight> potential(vertex_count,\
    \ Weight(0));\n    Weight total_weight = Weight(0);\n    on_solution(0, total_weight,\
    \ elements);\n\n    while (true) {\n        std::vector<std::vector<int>> adjacency(vertex_count);\n\
    \        std::vector<int> sink_predecessors;\n\n        for (int x = 0; x < ground_size;\
    \ x++) {\n            if (selected[x]) continue;\n            elements.push_back(x);\n\
    \            bool source = oracle1(elements);\n            bool sink = oracle2(elements);\n\
    \            elements.pop_back();\n            if (source) adjacency[source_vertex].push_back(x);\n\
    \            if (sink) {\n                adjacency[x].push_back(sink_vertex);\n\
    \                sink_predecessors.push_back(x);\n            }\n        }\n\n\
    \        for (int y : elements) {\n            int index = position[y];\n    \
    \        assert(index != -1 && elements[index] == y);\n            for (int x\
    \ = 0; x < ground_size; x++) {\n                if (selected[x]) continue;\n \
    \               elements[index] = x;\n                if (oracle1(elements)) adjacency[y].push_back(x);\n\
    \                if (oracle2(elements)) adjacency[x].push_back(y);\n         \
    \       elements[index] = y;\n            }\n        }\n\n        if (adjacency[source_vertex].empty()\
    \ || sink_predecessors.empty()) break;\n\n        auto vertex_length = [&](int\
    \ vertex) {\n            if (vertex >= ground_size) return Weight(0);\n      \
    \      Weight change = selected[vertex] ? Weight(0) - weight[vertex] : weight[vertex];\n\
    \            return objective_cost<Maximize>(change);\n        };\n        auto\
    \ reduced_length = [&](int from, int to) {\n            return vertex_length(to)\
    \ - potential[to] + potential[from];\n        };\n\n        int first_source =\
    \ adjacency[source_vertex].front();\n        potential[source_vertex] = potential[first_source]\
    \ - vertex_length(first_source);\n        for (int x : adjacency[source_vertex])\
    \ {\n            Weight candidate = potential[x] - vertex_length(x);\n       \
    \     if (potential[source_vertex] < candidate) potential[source_vertex] = candidate;\n\
    \        }\n        potential[sink_vertex] = potential[sink_predecessors.front()];\n\
    \        for (int x : sink_predecessors) {\n            if (potential[x] < potential[sink_vertex])\
    \ potential[sink_vertex] = potential[x];\n        }\n        Weight source_potential\
    \ = potential[source_vertex];\n        for (Weight& value : potential) value =\
    \ value - source_potential;\n\n#ifndef NDEBUG\n        for (int from = 0; from\
    \ < vertex_count; from++) {\n            for (int to : adjacency[from]) assert(!(reduced_length(from,\
    \ to) < Weight(0)));\n        }\n#endif\n\n        // Dijkstra is performed lazily:\
    \ fixed_distance is added to every\n        // not-yet-fixed potential at once,\
    \ then materialized when a vertex is fixed.\n        using QueueEntry = std::pair<Weight,\
    \ int>;\n        std::priority_queue<QueueEntry, std::vector<QueueEntry>, QueueGreater<Weight>>\
    \ heap;\n        std::vector<char> fixed(vertex_count, false);\n        std::vector<char>\
    \ has_distance(vertex_count, false);\n        std::vector<Weight> distance(vertex_count,\
    \ Weight(0));\n        std::vector<int> previous(vertex_count, -1);\n        heap.push({Weight(0),\
    \ source_vertex});\n        has_distance[source_vertex] = true;\n\n        Weight\
    \ fixed_distance = Weight(0);\n        bool reached_sink = false;\n        std::vector<int>\
    \ tight_stack;\n        tight_stack.reserve(vertex_count);\n        while (!heap.empty()\
    \ && !reached_sink) {\n            int start = heap.top().second;\n          \
    \  heap.pop();\n            if (fixed[start]) continue;\n            if (start\
    \ != source_vertex) {\n                assert(previous[start] != -1);\n      \
    \          fixed_distance = reduced_length(previous[start], start);\n        \
    \    }\n\n            tight_stack.clear();\n            fixed[start] = true;\n\
    \            potential[start] = potential[start] + fixed_distance;\n         \
    \   tight_stack.push_back(start);\n\n            while (!tight_stack.empty() &&\
    \ !reached_sink) {\n                int current = tight_stack.back();\n      \
    \          tight_stack.pop_back();\n                if (current == sink_vertex)\
    \ {\n                    reached_sink = true;\n                    break;\n  \
    \              }\n                for (int next : adjacency[current]) {\n    \
    \                if (fixed[next]) continue;\n                    Weight slack\
    \ = reduced_length(current, next) - fixed_distance;\n                    assert(!(slack\
    \ < Weight(0)));\n                    if (!(Weight(0) < slack)) {\n          \
    \              previous[next] = current;\n                        fixed[next]\
    \ = true;\n                        potential[next] = potential[next] + fixed_distance;\n\
    \                        tight_stack.push_back(next);\n                    } else\
    \ {\n                        Weight candidate = fixed_distance + slack;\n    \
    \                    if (!has_distance[next] || candidate < distance[next]) {\n\
    \                            has_distance[next] = true;\n                    \
    \        distance[next] = candidate;\n                            previous[next]\
    \ = current;\n                            heap.push({candidate, next});\n    \
    \                    }\n                    }\n                }\n           \
    \ }\n        }\n\n        for (int vertex = 0; vertex < vertex_count; vertex++)\
    \ {\n            if (!fixed[vertex]) potential[vertex] = potential[vertex] + fixed_distance;\n\
    \        }\n        if (!reached_sink) break;\n\n        std::fill(previous.begin(),\
    \ previous.end(), -1);\n        std::vector<char> reached(vertex_count, false);\n\
    \        std::vector<int> queue;\n        queue.reserve(vertex_count);\n     \
    \   reached[source_vertex] = true;\n        queue.push_back(source_vertex);\n\
    \        for (int head = 0; head < int(queue.size()) && !reached[sink_vertex];\
    \ head++) {\n            int current = queue[head];\n            for (int next\
    \ : adjacency[current]) {\n                if (reached[next]) continue;\n    \
    \            Weight length = reduced_length(current, next);\n                assert(!(length\
    \ < Weight(0)));\n                if (Weight(0) < length) continue;\n        \
    \        reached[next] = true;\n                previous[next] = current;\n  \
    \              queue.push_back(next);\n            }\n        }\n        assert(reached[sink_vertex]);\n\
    \        if (!reached[sink_vertex]) break;\n\n        // A shortest tight path\
    \ with the fewest edges preserves the potential invariant\n        // after its\
    \ elements switch between the inside and outside of the solution.\n        for\
    \ (int v = sink_vertex; v != source_vertex; v = previous[v]) {\n            assert(v\
    \ != -1);\n            if (v < ground_size) {\n                potential[v] =\
    \ potential[v] - vertex_length(v);\n                if (selected[v]) {\n     \
    \               total_weight = total_weight - weight[v];\n                } else\
    \ {\n                    total_weight = total_weight + weight[v];\n          \
    \      }\n                selected[v] = !selected[v];\n            }\n       \
    \ }\n\n        elements.clear();\n        std::fill(position.begin(), position.end(),\
    \ -1);\n        for (int x = 0; x < ground_size; x++) {\n            if (!selected[x])\
    \ continue;\n            position[x] = int(elements.size());\n            elements.push_back(x);\n\
    \        }\n\n#ifndef NDEBUG\n        assert(oracle1(elements));\n        assert(oracle2(elements));\n\
    #endif\n        on_solution(int(elements.size()), total_weight, elements);\n \
    \   }\n\n    WeightedMatroidIntersectionResult<Weight> result;\n    result.elements\
    \ = elements;\n    result.total_weight = total_weight;\n    return result;\n}\n\
    \n}  // namespace weighted_intersection_detail\n\ntemplate <class Weight, class\
    \ IndependenceOracle1, class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_max(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2) {\n \
    \   auto ignore = [](int, const Weight&, const std::vector<int>&) {};\n    return\
    \ weighted_intersection_detail::solve<true>(ground_size, weight, oracle1, oracle2,\n\
    \                                                      ignore);\n}\n\ntemplate\
    \ <class Weight, class IndependenceOracle1, class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_min(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2) {\n \
    \   auto ignore = [](int, const Weight&, const std::vector<int>&) {};\n    return\
    \ weighted_intersection_detail::solve<false>(ground_size, weight, oracle1, oracle2,\n\
    \                                                       ignore);\n}\n\ntemplate\
    \ <class Weight, class IndependenceOracle1, class IndependenceOracle2, class OnSolution>\n\
    WeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection_max_each(\n\
    \    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n\
    \    IndependenceOracle2 oracle2, OnSolution on_solution) {\n    return weighted_intersection_detail::solve<true>(ground_size,\
    \ weight, oracle1, oracle2,\n                                                \
    \      on_solution);\n}\n\ntemplate <class Weight, class IndependenceOracle1,\
    \ class IndependenceOracle2, class OnSolution>\nWeightedMatroidIntersectionResult<Weight>\
    \ weighted_matroid_intersection_min_each(\n    int ground_size, const std::vector<Weight>&\
    \ weight, IndependenceOracle1 oracle1,\n    IndependenceOracle2 oracle2, OnSolution\
    \ on_solution) {\n    return weighted_intersection_detail::solve<false>(ground_size,\
    \ weight, oracle1, oracle2,\n                                                \
    \       on_solution);\n}\n\ntemplate <class Weight, class IndependenceOracle1,\
    \ class IndependenceOracle2>\nWeightedMatroidIntersectionResult<Weight> weighted_matroid_intersection(\n\
    \    int ground_size, const std::vector<Weight>& weight, IndependenceOracle1 oracle1,\n\
    \    IndependenceOracle2 oracle2) {\n    return weighted_matroid_intersection_max(ground_size,\
    \ weight, oracle1, oracle2);\n}\n\n}  // namespace matroid\n}  // namespace m1une\n\
    \n\n#line 10 \"matroid/all.hpp\"\n\n\n#line 12 \"verify/matroid/matroids.test.cpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\nvoid test_uniform_matroid()\
    \ {\n    m1une::matroid::UniformMatroid matroid(5, 2);\n    assert(matroid.size()\
    \ == 5);\n    assert(matroid.rank() == 2);\n    assert(matroid(std::vector<int>{1,\
    \ 4}));\n    assert(!matroid(std::vector<int>{0, 2, 3}));\n}\n\nvoid test_partition_matroid()\
    \ {\n    std::vector<int> group = {0, 0, 1, 1, 1};\n    std::vector<int> capacity\
    \ = {1, 2};\n    m1une::matroid::PartitionMatroid matroid(group, capacity);\n\
    \    assert(matroid.size() == 5);\n    assert(matroid.group_count() == 2);\n \
    \   assert(matroid.groups() == group);\n    assert(matroid.capacities() == capacity);\n\
    \    assert(matroid(std::vector<int>{0, 2, 4}));\n    assert(!matroid(std::vector<int>{0,\
    \ 1}));\n    assert(!matroid(std::vector<int>{2, 3, 4}));\n}\n\nvoid test_graphic_matroid()\
    \ {\n    std::vector<std::pair<int, int>> edges = {\n        {0, 1}, {1, 2}, {2,\
    \ 0}, {2, 3}, {3, 3}\n    };\n    m1une::matroid::GraphicMatroid matroid(4, edges);\n\
    \    assert(matroid.size() == 5);\n    assert(matroid.vertex_count() == 4);\n\
    \    assert(matroid.edges() == edges);\n    assert(matroid(std::vector<int>{0,\
    \ 1, 3}));\n    assert(!matroid(std::vector<int>{0, 1, 2}));\n    assert(!matroid(std::vector<int>{4}));\n\
    }\n\nvoid test_linear_matroids() {\n    std::vector<std::vector<mint>> vectors(4);\n\
    \    vectors[0] = {1, 0, 0};\n    vectors[1] = {0, 1, 0};\n    vectors[2] = {1,\
    \ 1, 0};\n    vectors[3] = {0, 0, 1};\n    m1une::matroid::LinearMatroid<mint>\
    \ linear(vectors);\n    assert(linear.size() == 4);\n    assert(linear.dimension()\
    \ == 3);\n    assert(linear.vectors() == vectors);\n    assert(linear(std::vector<int>{0,\
    \ 1, 3}));\n    assert(!linear(std::vector<int>{0, 1, 2}));\n\n    std::vector<std::uint64_t>\
    \ binary_vectors = {1, 2, 3, 4};\n    m1une::matroid::BinaryLinearMatroid binary(binary_vectors);\n\
    \    assert(binary.size() == 4);\n    assert(binary.dimension() == 64);\n    assert(binary.vectors()\
    \ == binary_vectors);\n    assert(binary(std::vector<int>{0, 1, 3}));\n    assert(!binary(std::vector<int>{0,\
    \ 1, 2}));\n\n    std::mt19937 random(123456789);\n    for (int test = 0; test\
    \ < 100; test++) {\n        const int n = 8;\n        const int dimension = 6;\n\
    \        using binary_mint = m1une::math::ModInt<2>;\n        std::vector<std::uint64_t>\
    \ bits(n);\n        std::vector<std::vector<binary_mint>> field_vectors(\n   \
    \         n, std::vector<binary_mint>(dimension));\n        for (int i = 0; i\
    \ < n; i++) {\n            bits[i] = random() % (1 << dimension);\n          \
    \  for (int bit = 0; bit < dimension; bit++) {\n                field_vectors[i][bit]\
    \ = binary_mint(int(bits[i] >> bit & 1));\n            }\n        }\n        m1une::matroid::BinaryLinearMatroid\
    \ binary_random(bits);\n        m1une::matroid::LinearMatroid<binary_mint> field_random(field_vectors);\n\
    \        for (int mask = 0; mask < (1 << n); mask++) {\n            std::vector<int>\
    \ subset;\n            for (int i = 0; i < n; i++) {\n                if (mask\
    \ >> i & 1) subset.push_back(i);\n            }\n            assert(binary_random(subset)\
    \ == field_random(subset));\n        }\n    }\n}\n\nint main() {\n    test_uniform_matroid();\n\
    \    test_partition_matroid();\n    test_graphic_matroid();\n    test_linear_matroids();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <random>\n#include <utility>\n\
    #include <vector>\n\n#include \"../../math/modint.hpp\"\n#include \"../../matroid/all.hpp\"\
    \n\nusing mint = m1une::math::modint998244353;\n\nvoid test_uniform_matroid()\
    \ {\n    m1une::matroid::UniformMatroid matroid(5, 2);\n    assert(matroid.size()\
    \ == 5);\n    assert(matroid.rank() == 2);\n    assert(matroid(std::vector<int>{1,\
    \ 4}));\n    assert(!matroid(std::vector<int>{0, 2, 3}));\n}\n\nvoid test_partition_matroid()\
    \ {\n    std::vector<int> group = {0, 0, 1, 1, 1};\n    std::vector<int> capacity\
    \ = {1, 2};\n    m1une::matroid::PartitionMatroid matroid(group, capacity);\n\
    \    assert(matroid.size() == 5);\n    assert(matroid.group_count() == 2);\n \
    \   assert(matroid.groups() == group);\n    assert(matroid.capacities() == capacity);\n\
    \    assert(matroid(std::vector<int>{0, 2, 4}));\n    assert(!matroid(std::vector<int>{0,\
    \ 1}));\n    assert(!matroid(std::vector<int>{2, 3, 4}));\n}\n\nvoid test_graphic_matroid()\
    \ {\n    std::vector<std::pair<int, int>> edges = {\n        {0, 1}, {1, 2}, {2,\
    \ 0}, {2, 3}, {3, 3}\n    };\n    m1une::matroid::GraphicMatroid matroid(4, edges);\n\
    \    assert(matroid.size() == 5);\n    assert(matroid.vertex_count() == 4);\n\
    \    assert(matroid.edges() == edges);\n    assert(matroid(std::vector<int>{0,\
    \ 1, 3}));\n    assert(!matroid(std::vector<int>{0, 1, 2}));\n    assert(!matroid(std::vector<int>{4}));\n\
    }\n\nvoid test_linear_matroids() {\n    std::vector<std::vector<mint>> vectors(4);\n\
    \    vectors[0] = {1, 0, 0};\n    vectors[1] = {0, 1, 0};\n    vectors[2] = {1,\
    \ 1, 0};\n    vectors[3] = {0, 0, 1};\n    m1une::matroid::LinearMatroid<mint>\
    \ linear(vectors);\n    assert(linear.size() == 4);\n    assert(linear.dimension()\
    \ == 3);\n    assert(linear.vectors() == vectors);\n    assert(linear(std::vector<int>{0,\
    \ 1, 3}));\n    assert(!linear(std::vector<int>{0, 1, 2}));\n\n    std::vector<std::uint64_t>\
    \ binary_vectors = {1, 2, 3, 4};\n    m1une::matroid::BinaryLinearMatroid binary(binary_vectors);\n\
    \    assert(binary.size() == 4);\n    assert(binary.dimension() == 64);\n    assert(binary.vectors()\
    \ == binary_vectors);\n    assert(binary(std::vector<int>{0, 1, 3}));\n    assert(!binary(std::vector<int>{0,\
    \ 1, 2}));\n\n    std::mt19937 random(123456789);\n    for (int test = 0; test\
    \ < 100; test++) {\n        const int n = 8;\n        const int dimension = 6;\n\
    \        using binary_mint = m1une::math::ModInt<2>;\n        std::vector<std::uint64_t>\
    \ bits(n);\n        std::vector<std::vector<binary_mint>> field_vectors(\n   \
    \         n, std::vector<binary_mint>(dimension));\n        for (int i = 0; i\
    \ < n; i++) {\n            bits[i] = random() % (1 << dimension);\n          \
    \  for (int bit = 0; bit < dimension; bit++) {\n                field_vectors[i][bit]\
    \ = binary_mint(int(bits[i] >> bit & 1));\n            }\n        }\n        m1une::matroid::BinaryLinearMatroid\
    \ binary_random(bits);\n        m1une::matroid::LinearMatroid<binary_mint> field_random(field_vectors);\n\
    \        for (int mask = 0; mask < (1 << n); mask++) {\n            std::vector<int>\
    \ subset;\n            for (int i = 0; i < n; i++) {\n                if (mask\
    \ >> i & 1) subset.push_back(i);\n            }\n            assert(binary_random(subset)\
    \ == field_random(subset));\n        }\n    }\n}\n\nint main() {\n    test_uniform_matroid();\n\
    \    test_partition_matroid();\n    test_graphic_matroid();\n    test_linear_matroids();\n\
    \n    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\\
    n';\n}\n"
  dependsOn:
  - math/modint.hpp
  - matroid/all.hpp
  - matroid/graphic_matroid.hpp
  - matroid/linear_matroid.hpp
  - matroid/matroid_intersection.hpp
  - matroid/partition_matroid.hpp
  - matroid/uniform_matroid.hpp
  - matroid/weighted_matroid_intersection.hpp
  isVerificationFile: true
  path: verify/matroid/matroids.test.cpp
  requiredBy: []
  timestamp: '2026-07-01 14:47:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/matroid/matroids.test.cpp
layout: document
redirect_from:
- /verify/verify/matroid/matroids.test.cpp
- /verify/verify/matroid/matroids.test.cpp.html
title: verify/matroid/matroids.test.cpp
---
