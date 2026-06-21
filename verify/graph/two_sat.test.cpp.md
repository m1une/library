---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/two_sat.hpp
    title: Two-Satisfiability
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/two_sat
    links:
    - https://judge.yosupo.jp/problem/two_sat
  bundledCode: "#line 1 \"verify/graph/two_sat.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\
    \n\n#line 1 \"graph/two_sat.hpp\"\n\n\n\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace graph {\n\n// A 2-SAT solver using iterative strongly connected components.\n\
    struct TwoSat {\n   private:\n    struct Csr {\n        std::vector<int> start;\n\
    \        std::vector<int> to;\n    };\n\n    int _n;\n    std::vector<std::pair<int,\
    \ int>> _edges;\n    bool _solved;\n    bool _satisfiable;\n    std::vector<bool>\
    \ _answer;\n\n    int node(int variable, bool value) const {\n        assert(0\
    \ <= variable && variable < _n);\n        return 2 * variable + int(value);\n\
    \    }\n\n    void add_edge(int from, int to) {\n        _edges.emplace_back(from,\
    \ to);\n        _solved = false;\n        _answer.clear();\n    }\n\n    Csr build_csr(bool\
    \ reverse) const {\n        int vertices = 2 * _n;\n        Csr graph;\n     \
    \   graph.start.assign(vertices + 1, 0);\n        graph.to.resize(_edges.size());\n\
    \n        for (auto [from, to] : _edges) {\n            int source = reverse ?\
    \ to : from;\n            graph.start[source + 1]++;\n        }\n        for (int\
    \ v = 0; v < vertices; v++) {\n            graph.start[v + 1] += graph.start[v];\n\
    \        }\n\n        std::vector<int> cursor = graph.start;\n        for (auto\
    \ [from, to] : _edges) {\n            int source = reverse ? to : from;\n    \
    \        int target = reverse ? from : to;\n            graph.to[cursor[source]++]\
    \ = target;\n        }\n        return graph;\n    }\n\n   public:\n    TwoSat()\
    \ : TwoSat(0) {}\n\n    explicit TwoSat(int n)\n        : _n(n), _solved(false),\
    \ _satisfiable(false) {\n        assert(0 <= n);\n        assert(n <= std::numeric_limits<int>::max()\
    \ / 2);\n    }\n\n    int size() const {\n        return _n;\n    }\n\n    bool\
    \ empty() const {\n        return _n == 0;\n    }\n\n    // Reserves space for\
    \ approximately `clause_count` two-literal clauses.\n    void reserve(std::size_t\
    \ clause_count) {\n        assert(clause_count <= std::size_t(std::numeric_limits<int>::max())\
    \ / 2);\n        _edges.reserve(2 * clause_count);\n    }\n\n    // Adds (variable\
    \ i == f) OR (variable j == g).\n    void add_clause(int i, bool f, int j, bool\
    \ g) {\n        int a = node(i, f);\n        int b = node(j, g);\n        add_edge(a\
    \ ^ 1, b);\n        add_edge(b ^ 1, a);\n    }\n\n    // Adds (variable i == f)\
    \ => (variable j == g).\n    void add_implication(int i, bool f, int j, bool g)\
    \ {\n        add_clause(i, !f, j, g);\n    }\n\n    // Forces variable i to equal\
    \ value.\n    void set_value(int i, bool value) {\n        add_clause(i, value,\
    \ i, value);\n    }\n\n    // Forces variables i and j to have equal values.\n\
    \    void add_equal(int i, int j) {\n        add_clause(i, false, j, true);\n\
    \        add_clause(i, true, j, false);\n    }\n\n    // Forces variables i and\
    \ j to have different values.\n    void add_not_equal(int i, int j) {\n      \
    \  add_clause(i, true, j, true);\n        add_clause(i, false, j, false);\n  \
    \  }\n\n    bool satisfiable() {\n        if (_solved) return _satisfiable;\n\
    \        assert(_edges.size() <= std::size_t(std::numeric_limits<int>::max()));\n\
    \n        int vertices = 2 * _n;\n        Csr graph = build_csr(false);\n    \
    \    Csr reverse_graph = build_csr(true);\n\n        std::vector<char> seen(vertices,\
    \ false);\n        std::vector<int> order;\n        order.reserve(vertices);\n\
    \        std::vector<std::pair<int, int>> stack;\n        stack.reserve(vertices);\n\
    \n        for (int start = 0; start < vertices; start++) {\n            if (seen[start])\
    \ continue;\n            seen[start] = true;\n            stack.emplace_back(start,\
    \ graph.start[start]);\n\n            while (!stack.empty()) {\n             \
    \   int v = stack.back().first;\n                int& edge = stack.back().second;\n\
    \                if (edge == graph.start[v + 1]) {\n                    order.push_back(v);\n\
    \                    stack.pop_back();\n                    continue;\n      \
    \          }\n\n                int to = graph.to[edge++];\n                if\
    \ (!seen[to]) {\n                    seen[to] = true;\n                    stack.emplace_back(to,\
    \ graph.start[to]);\n                }\n            }\n        }\n\n        std::vector<int>\
    \ component(vertices, -1);\n        std::vector<int> vertices_stack;\n       \
    \ vertices_stack.reserve(vertices);\n        int component_count = 0;\n      \
    \  for (int index = vertices - 1; index >= 0; index--) {\n            int start\
    \ = order[index];\n            if (component[start] != -1) continue;\n\n     \
    \       component[start] = component_count;\n            vertices_stack.push_back(start);\n\
    \            while (!vertices_stack.empty()) {\n                int v = vertices_stack.back();\n\
    \                vertices_stack.pop_back();\n                for (int edge = reverse_graph.start[v];\n\
    \                     edge < reverse_graph.start[v + 1];\n                   \
    \  edge++) {\n                    int to = reverse_graph.to[edge];\n         \
    \           if (component[to] == -1) {\n                        component[to]\
    \ = component_count;\n                        vertices_stack.push_back(to);\n\
    \                    }\n                }\n            }\n            component_count++;\n\
    \        }\n\n        _answer.assign(_n, false);\n        _satisfiable = true;\n\
    \        for (int i = 0; i < _n; i++) {\n            if (component[2 * i] == component[2\
    \ * i + 1]) {\n                _satisfiable = false;\n                _answer.clear();\n\
    \                break;\n            }\n            _answer[i] = component[2 *\
    \ i] < component[2 * i + 1];\n        }\n        _solved = true;\n        return\
    \ _satisfiable;\n    }\n\n    const std::vector<bool>& answer() const {\n    \
    \    assert(_solved && _satisfiable);\n        return _answer;\n    }\n\n    bool\
    \ value(int variable) const {\n        assert(_solved && _satisfiable);\n    \
    \    assert(0 <= variable && variable < _n);\n        return _answer[variable];\n\
    \    }\n};\n\n}  // namespace graph\n}  // namespace m1une\n\n\n#line 4 \"verify/graph/two_sat.test.cpp\"\
    \n\n#line 6 \"verify/graph/two_sat.test.cpp\"\n#include <cstdint>\n#include <cstdlib>\n\
    #include <iostream>\n#include <tuple>\n#line 11 \"verify/graph/two_sat.test.cpp\"\
    \n\nnamespace {\n\nstruct Clause {\n    int i;\n    bool f;\n    int j;\n    bool\
    \ g;\n};\n\nbool satisfies(const std::vector<bool>& assignment, const Clause&\
    \ clause) {\n    return assignment[clause.i] == clause.f ||\n           assignment[clause.j]\
    \ == clause.g;\n}\n\nvoid test_helpers() {\n    m1une::graph::TwoSat sat(4);\n\
    \    assert(sat.size() == 4);\n    assert(!sat.empty());\n    sat.reserve(8);\n\
    \n    sat.set_value(0, true);\n    sat.add_implication(0, true, 1, false);\n \
    \   sat.add_equal(1, 2);\n    sat.add_not_equal(2, 3);\n    assert(sat.satisfiable());\n\
    \    assert(sat.satisfiable());\n    assert(sat.value(0));\n    assert(!sat.value(1));\n\
    \    assert(!sat.value(2));\n    assert(sat.value(3));\n\n    sat.set_value(3,\
    \ false);\n    assert(!sat.satisfiable());\n\n    m1une::graph::TwoSat empty;\n\
    \    assert(empty.empty());\n    assert(empty.satisfiable());\n    assert(empty.answer().empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 29;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int trial = 0; trial < 3000; trial++)\
    \ {\n        int n = int(random() % 8);\n        int m = n == 0 ? 0 : int(random()\
    \ % 24);\n        m1une::graph::TwoSat sat(n);\n        sat.reserve(std::size_t(m));\n\
    \        std::vector<Clause> clauses;\n\n        for (int edge = 0; edge < m;\
    \ edge++) {\n            Clause clause;\n            clause.i = int(random() %\
    \ std::uint64_t(n));\n            clause.f = bool(random() & 1);\n           \
    \ clause.j = int(random() % std::uint64_t(n));\n            clause.g = bool(random()\
    \ & 1);\n            clauses.push_back(clause);\n            sat.add_clause(clause.i,\
    \ clause.f, clause.j, clause.g);\n        }\n\n        bool expected = false;\n\
    \        for (int mask = 0; mask < (1 << n); mask++) {\n            std::vector<bool>\
    \ assignment(n);\n            for (int i = 0; i < n; i++) assignment[i] = (mask\
    \ >> i) & 1;\n\n            bool valid = true;\n            for (const Clause&\
    \ clause : clauses) {\n                if (!satisfies(assignment, clause)) {\n\
    \                    valid = false;\n                    break;\n            \
    \    }\n            }\n            if (valid) {\n                expected = true;\n\
    \                break;\n            }\n        }\n\n        assert(sat.satisfiable()\
    \ == expected);\n        if (expected) {\n            [[maybe_unused]] const std::vector<bool>&\
    \ assignment = sat.answer();\n            assert(int(assignment.size()) == n);\n\
    \            for ([[maybe_unused]] const Clause& clause : clauses) {\n       \
    \         assert(satisfies(assignment, clause));\n            }\n        }\n \
    \   }\n}\n\n}  // namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    test_helpers();\n    test_randomized();\n\n\
    \    char p;\n    std::string cnf;\n    int n, m;\n    std::cin >> p >> cnf >>\
    \ n >> m;\n\n    m1une::graph::TwoSat sat(n);\n    sat.reserve(std::size_t(m));\n\
    \    for (int clause = 0; clause < m; clause++) {\n        int a, b, zero;\n \
    \       std::cin >> a >> b >> zero;\n        assert(zero == 0);\n        sat.add_clause(std::abs(a)\
    \ - 1, 0 < a, std::abs(b) - 1, 0 < b);\n    }\n\n    if (!sat.satisfiable()) {\n\
    \        std::cout << \"s UNSATISFIABLE\\n\";\n        return 0;\n    }\n\n  \
    \  std::cout << \"s SATISFIABLE\\n\";\n    std::cout << \"v\";\n    const std::vector<bool>&\
    \ answer = sat.answer();\n    for (int i = 0; i < n; i++) {\n        std::cout\
    \ << \" \" << (answer[i] ? i + 1 : -(i + 1));\n    }\n    std::cout << \" 0\\\
    n\";\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\n\n#include \"\
    ../../graph/two_sat.hpp\"\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ <cstdlib>\n#include <iostream>\n#include <tuple>\n#include <vector>\n\nnamespace\
    \ {\n\nstruct Clause {\n    int i;\n    bool f;\n    int j;\n    bool g;\n};\n\
    \nbool satisfies(const std::vector<bool>& assignment, const Clause& clause) {\n\
    \    return assignment[clause.i] == clause.f ||\n           assignment[clause.j]\
    \ == clause.g;\n}\n\nvoid test_helpers() {\n    m1une::graph::TwoSat sat(4);\n\
    \    assert(sat.size() == 4);\n    assert(!sat.empty());\n    sat.reserve(8);\n\
    \n    sat.set_value(0, true);\n    sat.add_implication(0, true, 1, false);\n \
    \   sat.add_equal(1, 2);\n    sat.add_not_equal(2, 3);\n    assert(sat.satisfiable());\n\
    \    assert(sat.satisfiable());\n    assert(sat.value(0));\n    assert(!sat.value(1));\n\
    \    assert(!sat.value(2));\n    assert(sat.value(3));\n\n    sat.set_value(3,\
    \ false);\n    assert(!sat.satisfiable());\n\n    m1une::graph::TwoSat empty;\n\
    \    assert(empty.empty());\n    assert(empty.satisfiable());\n    assert(empty.answer().empty());\n\
    }\n\nvoid test_randomized() {\n    std::uint64_t state = 29;\n    auto random\
    \ = [&state]() {\n        state ^= state << 7;\n        state ^= state >> 9;\n\
    \        return state;\n    };\n\n    for (int trial = 0; trial < 3000; trial++)\
    \ {\n        int n = int(random() % 8);\n        int m = n == 0 ? 0 : int(random()\
    \ % 24);\n        m1une::graph::TwoSat sat(n);\n        sat.reserve(std::size_t(m));\n\
    \        std::vector<Clause> clauses;\n\n        for (int edge = 0; edge < m;\
    \ edge++) {\n            Clause clause;\n            clause.i = int(random() %\
    \ std::uint64_t(n));\n            clause.f = bool(random() & 1);\n           \
    \ clause.j = int(random() % std::uint64_t(n));\n            clause.g = bool(random()\
    \ & 1);\n            clauses.push_back(clause);\n            sat.add_clause(clause.i,\
    \ clause.f, clause.j, clause.g);\n        }\n\n        bool expected = false;\n\
    \        for (int mask = 0; mask < (1 << n); mask++) {\n            std::vector<bool>\
    \ assignment(n);\n            for (int i = 0; i < n; i++) assignment[i] = (mask\
    \ >> i) & 1;\n\n            bool valid = true;\n            for (const Clause&\
    \ clause : clauses) {\n                if (!satisfies(assignment, clause)) {\n\
    \                    valid = false;\n                    break;\n            \
    \    }\n            }\n            if (valid) {\n                expected = true;\n\
    \                break;\n            }\n        }\n\n        assert(sat.satisfiable()\
    \ == expected);\n        if (expected) {\n            [[maybe_unused]] const std::vector<bool>&\
    \ assignment = sat.answer();\n            assert(int(assignment.size()) == n);\n\
    \            for ([[maybe_unused]] const Clause& clause : clauses) {\n       \
    \         assert(satisfies(assignment, clause));\n            }\n        }\n \
    \   }\n}\n\n}  // namespace\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    test_helpers();\n    test_randomized();\n\n\
    \    char p;\n    std::string cnf;\n    int n, m;\n    std::cin >> p >> cnf >>\
    \ n >> m;\n\n    m1une::graph::TwoSat sat(n);\n    sat.reserve(std::size_t(m));\n\
    \    for (int clause = 0; clause < m; clause++) {\n        int a, b, zero;\n \
    \       std::cin >> a >> b >> zero;\n        assert(zero == 0);\n        sat.add_clause(std::abs(a)\
    \ - 1, 0 < a, std::abs(b) - 1, 0 < b);\n    }\n\n    if (!sat.satisfiable()) {\n\
    \        std::cout << \"s UNSATISFIABLE\\n\";\n        return 0;\n    }\n\n  \
    \  std::cout << \"s SATISFIABLE\\n\";\n    std::cout << \"v\";\n    const std::vector<bool>&\
    \ answer = sat.answer();\n    for (int i = 0; i < n; i++) {\n        std::cout\
    \ << \" \" << (answer[i] ? i + 1 : -(i + 1));\n    }\n    std::cout << \" 0\\\
    n\";\n}\n"
  dependsOn:
  - graph/two_sat.hpp
  isVerificationFile: true
  path: verify/graph/two_sat.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/graph/two_sat.test.cpp
layout: document
redirect_from:
- /verify/verify/graph/two_sat.test.cpp
- /verify/verify/graph/two_sat.test.cpp.html
title: verify/graph/two_sat.test.cpp
---
