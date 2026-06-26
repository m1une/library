---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: Aho-Corasick
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aho_corasick
    links:
    - https://judge.yosupo.jp/problem/aho_corasick
  bundledCode: "#line 1 \"verify/string/aho_corasick.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aho_corasick\"\n\n#line 1 \"string/aho_corasick.hpp\"\
    \n\n\n\n#include <array>\n#include <cassert>\n#include <cstddef>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\nnamespace m1une {\nnamespace string {\n\
    \n// Aho-Corasick automaton for a contiguous character alphabet.\ntemplate <int\
    \ AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct AhoCorasick {\n    static_assert(0\
    \ < AlphabetSize);\n\n    using node_id = int;\n    static constexpr node_id null_node\
    \ = -1;\n\n    struct Node {\n        // Completed automaton transitions. Valid\
    \ after build().\n        std::array<node_id, AlphabetSize> next;\n        node_id\
    \ failure;\n        node_id output_link;\n        node_id parent;\n        int\
    \ parent_symbol;\n        int depth;\n        std::vector<node_id> children;\n\
    \        std::vector<node_id> failure_children;\n        std::vector<int> pattern_ids;\n\
    \n        Node(\n            node_id parent_value = null_node,\n            int\
    \ parent_symbol_value = -1,\n            int depth_value = 0\n        ) : failure(0),\n\
    \            output_link(null_node),\n            parent(parent_value),\n    \
    \        parent_symbol(parent_symbol_value),\n            depth(depth_value) {\n\
    \            next.fill(null_node);\n        }\n    };\n\n   private:\n    std::vector<Node>\
    \ _nodes;\n    std::vector<int> _pattern_length;\n    std::vector<node_id> _pattern_node;\n\
    \    std::vector<node_id> _bfs_order;\n    bool _built;\n\n    template <class\
    \ Symbol>\n    static int symbol_index(const Symbol& symbol) {\n        int index\
    \ = int(symbol) - FirstCharacter;\n        assert(0 <= index && index < AlphabetSize);\n\
    \        return index;\n    }\n\n    node_id new_node(node_id parent, int parent_symbol)\
    \ {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        assert(_nodes[parent].depth < std::numeric_limits<int>::max());\n   \
    \     _nodes.emplace_back(parent, parent_symbol, _nodes[parent].depth + 1);\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n   public:\n    AhoCorasick()\
    \ : _nodes(1), _built(false) {}\n\n    node_id root() const {\n        return\
    \ 0;\n    }\n\n    bool built() const {\n        return _built;\n    }\n\n   \
    \ int pattern_count() const {\n        return int(_pattern_length.size());\n \
    \   }\n\n    int pattern_length(int pattern_id) const {\n        assert(0 <= pattern_id\
    \ && pattern_id < pattern_count());\n        return _pattern_length[pattern_id];\n\
    \    }\n\n    node_id pattern_node(int pattern_id) const {\n        assert(0 <=\
    \ pattern_id && pattern_id < pattern_count());\n        return _pattern_node[pattern_id];\n\
    \    }\n\n    std::size_t node_count() const {\n        return _nodes.size();\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id &&\
    \ std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n   \
    \ // Returns nodes in failure-link BFS order, beginning with the root.\n    const\
    \ std::vector<node_id>& bfs_order() const {\n        assert(_built);\n       \
    \ return _bfs_order;\n    }\n\n    void reserve(std::size_t node_capacity) {\n\
    \        assert(!_built);\n        _nodes.reserve(node_capacity);\n    }\n\n \
    \   void clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n\
    \        _pattern_length.clear();\n        _pattern_node.clear();\n        _bfs_order.clear();\n\
    \        _built = false;\n    }\n\n    // Inserts a pattern and returns its insertion-order\
    \ ID.\n    template <class Sequence>\n    int insert(const Sequence& pattern)\
    \ {\n        assert(!_built);\n        int pattern_id = pattern_count();\n   \
    \     int length = 0;\n        node_id state = root();\n        for (const auto&\
    \ symbol : pattern) {\n            assert(length < std::numeric_limits<int>::max());\n\
    \            int index = symbol_index(symbol);\n            if (_nodes[state].next[index]\
    \ == null_node) {\n                node_id child = new_node(state, index);\n \
    \               _nodes[state].next[index] = child;\n                _nodes[state].children.push_back(child);\n\
    \            }\n            state = _nodes[state].next[index];\n            length++;\n\
    \        }\n        _nodes[state].pattern_ids.push_back(pattern_id);\n       \
    \ _pattern_length.push_back(length);\n        _pattern_node.push_back(state);\n\
    \        return pattern_id;\n    }\n\n    // Builds failure links and completes\
    \ every automaton transition.\n    void build() {\n        assert(!_built);\n\
    \        std::queue<node_id> queue;\n        _bfs_order.clear();\n        _bfs_order.reserve(_nodes.size());\n\
    \        _bfs_order.push_back(root());\n\n        for (int symbol = 0; symbol\
    \ < AlphabetSize; ++symbol) {\n            node_id child = _nodes[root()].next[symbol];\n\
    \            if (child == null_node) {\n                _nodes[root()].next[symbol]\
    \ = root();\n            } else {\n                _nodes[root()].next[symbol]\
    \ = child;\n                _nodes[child].failure = root();\n                _nodes[child].output_link\
    \ =\n                    _nodes[root()].pattern_ids.empty() ? null_node : root();\n\
    \                _nodes[root()].failure_children.push_back(child);\n         \
    \       queue.push(child);\n            }\n        }\n\n        while (!queue.empty())\
    \ {\n            node_id state = queue.front();\n            queue.pop();\n  \
    \          _bfs_order.push_back(state);\n\n            for (int symbol = 0; symbol\
    \ < AlphabetSize; ++symbol) {\n                node_id child = _nodes[state].next[symbol];\n\
    \                if (child == null_node) {\n                    _nodes[state].next[symbol]\
    \ =\n                        _nodes[_nodes[state].failure].next[symbol];\n   \
    \                 continue;\n                }\n\n                _nodes[state].next[symbol]\
    \ = child;\n                node_id failure =\n                    _nodes[_nodes[state].failure].next[symbol];\n\
    \                _nodes[child].failure = failure;\n                _nodes[child].output_link\
    \ =\n                    _nodes[failure].pattern_ids.empty()\n               \
    \         ? _nodes[failure].output_link\n                        : failure;\n\
    \                _nodes[failure].failure_children.push_back(child);\n        \
    \        queue.push(child);\n            }\n        }\n        _built = true;\n\
    \    }\n\n    template <class Symbol>\n    node_id transition(node_id state, const\
    \ Symbol& symbol) const {\n        assert(_built);\n        assert(0 <= state\
    \ && std::size_t(state) < _nodes.size());\n        return _nodes[state].next[symbol_index(symbol)];\n\
    \    }\n\n    // Calls callback(pattern_id) for every pattern ending at `state`.\n\
    \    template <class Callback>\n    void for_each_output(node_id state, Callback\
    \ callback) const {\n        assert(_built);\n        assert(0 <= state && std::size_t(state)\
    \ < _nodes.size());\n        while (state != null_node) {\n            for (int\
    \ pattern_id : _nodes[state].pattern_ids) {\n                callback(pattern_id);\n\
    \            }\n            state = _nodes[state].output_link;\n        }\n  \
    \  }\n\n    // Calls callback(end, pattern_id) for every occurrence. `end` is\
    \ the\n    // exclusive end position. Empty patterns occur at every text boundary.\n\
    \    template <class Sequence, class Callback>\n    void match(const Sequence&\
    \ text, Callback callback) const {\n        assert(_built);\n        node_id state\
    \ = root();\n        for_each_output(state, [&callback](int pattern_id) {\n  \
    \          callback(0, pattern_id);\n        });\n\n        int end = 0;\n   \
    \     for (const auto& symbol : text) {\n            state = transition(state,\
    \ symbol);\n            end++;\n            for_each_output(state, [&callback,\
    \ end](int pattern_id) {\n                callback(end, pattern_id);\n       \
    \     });\n        }\n    }\n\n    // Counts occurrences of every inserted pattern\
    \ in linear time.\n    template <class Sequence>\n    std::vector<long long> count_occurrences(const\
    \ Sequence& text) const {\n        assert(_built);\n        std::vector<long long>\
    \ visits(_nodes.size(), 0);\n        node_id state = root();\n        visits[root()]++;\n\
    \        for (const auto& symbol : text) {\n            state = transition(state,\
    \ symbol);\n            visits[state]++;\n        }\n\n        for (std::size_t\
    \ index = _bfs_order.size(); index-- > 1;) {\n            node_id current = _bfs_order[index];\n\
    \            visits[_nodes[current].failure] += visits[current];\n        }\n\n\
    \        std::vector<long long> result(pattern_count(), 0);\n        for (node_id\
    \ current : _bfs_order) {\n            for (int pattern_id : _nodes[current].pattern_ids)\
    \ {\n                result[pattern_id] = visits[current];\n            }\n  \
    \      }\n        return result;\n    }\n};\n\n}  // namespace string\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/string/aho_corasick.test.cpp\"\n\n#include <algorithm>\n\
    #line 7 \"verify/string/aho_corasick.test.cpp\"\n#include <cstdint>\n#include\
    \ <iostream>\n#include <string>\n#include <tuple>\n#line 12 \"verify/string/aho_corasick.test.cpp\"\
    \n\nnamespace {\n\nvoid check(\n    const std::vector<std::string>& patterns,\n\
    \    const std::string& text\n) {\n    m1une::string::AhoCorasick<4, 'a'> automaton;\n\
    \    std::size_t total_length = 1;\n    for (const std::string& pattern : patterns)\
    \ {\n        total_length += pattern.size();\n    }\n    automaton.reserve(total_length);\n\
    \    for (int id = 0; id < int(patterns.size()); ++id) {\n        assert(automaton.insert(patterns[id])\
    \ == id);\n        assert(automaton.pattern_length(id) == int(patterns[id].size()));\n\
    \    }\n    automaton.build();\n    assert(automaton.built());\n    assert(automaton.pattern_count()\
    \ == int(patterns.size()));\n    assert(automaton.nodes().size() == automaton.node_count());\n\
    \    assert(automaton.bfs_order().size() == automaton.node_count());\n    assert(automaton.bfs_order().front()\
    \ == automaton.root());\n\n    std::vector<int> failure_parent_count(automaton.node_count(),\
    \ 0);\n    for (const auto& node : automaton.nodes()) {\n        for (int child\
    \ : node.failure_children) {\n            failure_parent_count[child]++;\n   \
    \     }\n    }\n    for (int node = 1; node < int(automaton.node_count()); ++node)\
    \ {\n        assert(failure_parent_count[node] == 1);\n        assert(\n     \
    \       automaton.node(automaton.node(node).failure).depth\n            < automaton.node(node).depth\n\
    \        );\n        assert(\n            std::find(\n                automaton.node(automaton.node(node).parent).children.begin(),\n\
    \                automaton.node(automaton.node(node).parent).children.end(),\n\
    \                node\n            ) != automaton.node(automaton.node(node).parent).children.end()\n\
    \        );\n        assert(\n            automaton.node(automaton.node(node).parent)\n\
    \                .next[automaton.node(node).parent_symbol]\n            == node\n\
    \        );\n    }\n    for (int id = 0; id < int(patterns.size()); ++id) {\n\
    \        [[maybe_unused]] int terminal = automaton.pattern_node(id);\n       \
    \ assert(automaton.node(terminal).depth == int(patterns[id].size()));\n      \
    \  assert(\n            std::find(\n                automaton.node(terminal).pattern_ids.begin(),\n\
    \                automaton.node(terminal).pattern_ids.end(),\n               \
    \ id\n            ) != automaton.node(terminal).pattern_ids.end()\n        );\n\
    \    }\n\n    std::vector<std::tuple<int, int>> actual;\n    automaton.match(text,\
    \ [&actual](int end, int pattern_id) {\n        actual.emplace_back(end, pattern_id);\n\
    \    });\n    std::sort(actual.begin(), actual.end());\n\n    std::vector<std::tuple<int,\
    \ int>> expected;\n    std::vector<long long> expected_count(patterns.size(),\
    \ 0);\n    for (int end = 0; end <= int(text.size()); ++end) {\n        for (int\
    \ id = 0; id < int(patterns.size()); ++id) {\n            int length = int(patterns[id].size());\n\
    \            if (\n                length <= end &&\n                text.compare(end\
    \ - length, length, patterns[id]) == 0\n            ) {\n                expected.emplace_back(end,\
    \ id);\n                expected_count[id]++;\n            }\n        }\n    }\n\
    \    std::sort(expected.begin(), expected.end());\n    assert(actual == expected);\n\
    \    assert(automaton.count_occurrences(text) == expected_count);\n}\n\nvoid test_fixed()\
    \ {\n    check({}, \"abacaba\");\n    check({\"\"}, \"\");\n    check({\"\", \"\
    \", \"a\", \"a\", \"aa\", \"ba\"}, \"aaaaba\");\n\n    m1une::string::AhoCorasick<10,\
    \ '0'> digits;\n    [[maybe_unused]] int first = digits.insert(std::string(\"\
    12\"));\n    [[maybe_unused]] int second = digits.insert(std::string(\"2\"));\n\
    \    digits.build();\n    auto count = digits.count_occurrences(std::string(\"\
    1212\"));\n    assert(count[first] == 2);\n    assert(count[second] == 2);\n\n\
    \    digits.clear();\n    assert(!digits.built());\n    assert(digits.pattern_count()\
    \ == 0);\n    assert(digits.node_count() == 1);\n}\n\nvoid test_randomized() {\n\
    \    std::uint64_t state = 313;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 4000; ++trial) {\n        int pattern_count\
    \ = int(random() % 15);\n        std::vector<std::string> patterns;\n        for\
    \ (int id = 0; id < pattern_count; ++id) {\n            int length = int(random()\
    \ % 8);\n            std::string pattern(length, 'a');\n            for (char&\
    \ symbol : pattern) {\n                symbol = char('a' + random() % 4);\n  \
    \          }\n            patterns.push_back(std::move(pattern));\n        }\n\
    \n        int text_length = int(random() % 35);\n        std::string text(text_length,\
    \ 'a');\n        for (char& symbol : text) {\n            symbol = char('a' +\
    \ random() % 4);\n        }\n        check(patterns, text);\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n   \
    \ std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n;\n\
    \    std::cin >> n;\n    m1une::string::AhoCorasick<> automaton;\n    for (int\
    \ i = 0; i < n; i++) {\n        std::string pattern;\n        std::cin >> pattern;\n\
    \        automaton.insert(pattern);\n    }\n    automaton.build();\n\n    int\
    \ node_count = int(automaton.node_count());\n    std::cout << node_count << '\\\
    n';\n    for (int id = 1; id < node_count; id++) {\n        const auto& node =\
    \ automaton.node(id);\n        std::cout << node.parent << ' ' << node.failure\
    \ << '\\n';\n    }\n    for (int i = 0; i < n; i++) {\n        if (i) std::cout\
    \ << ' ';\n        std::cout << automaton.pattern_node(i);\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aho_corasick\"\n\n#include\
    \ \"../../string/aho_corasick.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <string>\n#include <tuple>\n\
    #include <vector>\n\nnamespace {\n\nvoid check(\n    const std::vector<std::string>&\
    \ patterns,\n    const std::string& text\n) {\n    m1une::string::AhoCorasick<4,\
    \ 'a'> automaton;\n    std::size_t total_length = 1;\n    for (const std::string&\
    \ pattern : patterns) {\n        total_length += pattern.size();\n    }\n    automaton.reserve(total_length);\n\
    \    for (int id = 0; id < int(patterns.size()); ++id) {\n        assert(automaton.insert(patterns[id])\
    \ == id);\n        assert(automaton.pattern_length(id) == int(patterns[id].size()));\n\
    \    }\n    automaton.build();\n    assert(automaton.built());\n    assert(automaton.pattern_count()\
    \ == int(patterns.size()));\n    assert(automaton.nodes().size() == automaton.node_count());\n\
    \    assert(automaton.bfs_order().size() == automaton.node_count());\n    assert(automaton.bfs_order().front()\
    \ == automaton.root());\n\n    std::vector<int> failure_parent_count(automaton.node_count(),\
    \ 0);\n    for (const auto& node : automaton.nodes()) {\n        for (int child\
    \ : node.failure_children) {\n            failure_parent_count[child]++;\n   \
    \     }\n    }\n    for (int node = 1; node < int(automaton.node_count()); ++node)\
    \ {\n        assert(failure_parent_count[node] == 1);\n        assert(\n     \
    \       automaton.node(automaton.node(node).failure).depth\n            < automaton.node(node).depth\n\
    \        );\n        assert(\n            std::find(\n                automaton.node(automaton.node(node).parent).children.begin(),\n\
    \                automaton.node(automaton.node(node).parent).children.end(),\n\
    \                node\n            ) != automaton.node(automaton.node(node).parent).children.end()\n\
    \        );\n        assert(\n            automaton.node(automaton.node(node).parent)\n\
    \                .next[automaton.node(node).parent_symbol]\n            == node\n\
    \        );\n    }\n    for (int id = 0; id < int(patterns.size()); ++id) {\n\
    \        [[maybe_unused]] int terminal = automaton.pattern_node(id);\n       \
    \ assert(automaton.node(terminal).depth == int(patterns[id].size()));\n      \
    \  assert(\n            std::find(\n                automaton.node(terminal).pattern_ids.begin(),\n\
    \                automaton.node(terminal).pattern_ids.end(),\n               \
    \ id\n            ) != automaton.node(terminal).pattern_ids.end()\n        );\n\
    \    }\n\n    std::vector<std::tuple<int, int>> actual;\n    automaton.match(text,\
    \ [&actual](int end, int pattern_id) {\n        actual.emplace_back(end, pattern_id);\n\
    \    });\n    std::sort(actual.begin(), actual.end());\n\n    std::vector<std::tuple<int,\
    \ int>> expected;\n    std::vector<long long> expected_count(patterns.size(),\
    \ 0);\n    for (int end = 0; end <= int(text.size()); ++end) {\n        for (int\
    \ id = 0; id < int(patterns.size()); ++id) {\n            int length = int(patterns[id].size());\n\
    \            if (\n                length <= end &&\n                text.compare(end\
    \ - length, length, patterns[id]) == 0\n            ) {\n                expected.emplace_back(end,\
    \ id);\n                expected_count[id]++;\n            }\n        }\n    }\n\
    \    std::sort(expected.begin(), expected.end());\n    assert(actual == expected);\n\
    \    assert(automaton.count_occurrences(text) == expected_count);\n}\n\nvoid test_fixed()\
    \ {\n    check({}, \"abacaba\");\n    check({\"\"}, \"\");\n    check({\"\", \"\
    \", \"a\", \"a\", \"aa\", \"ba\"}, \"aaaaba\");\n\n    m1une::string::AhoCorasick<10,\
    \ '0'> digits;\n    [[maybe_unused]] int first = digits.insert(std::string(\"\
    12\"));\n    [[maybe_unused]] int second = digits.insert(std::string(\"2\"));\n\
    \    digits.build();\n    auto count = digits.count_occurrences(std::string(\"\
    1212\"));\n    assert(count[first] == 2);\n    assert(count[second] == 2);\n\n\
    \    digits.clear();\n    assert(!digits.built());\n    assert(digits.pattern_count()\
    \ == 0);\n    assert(digits.node_count() == 1);\n}\n\nvoid test_randomized() {\n\
    \    std::uint64_t state = 313;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 4000; ++trial) {\n        int pattern_count\
    \ = int(random() % 15);\n        std::vector<std::string> patterns;\n        for\
    \ (int id = 0; id < pattern_count; ++id) {\n            int length = int(random()\
    \ % 8);\n            std::string pattern(length, 'a');\n            for (char&\
    \ symbol : pattern) {\n                symbol = char('a' + random() % 4);\n  \
    \          }\n            patterns.push_back(std::move(pattern));\n        }\n\
    \n        int text_length = int(random() % 35);\n        std::string text(text_length,\
    \ 'a');\n        for (char& symbol : text) {\n            symbol = char('a' +\
    \ random() % 4);\n        }\n        check(patterns, text);\n    }\n}\n\n}  //\
    \ namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n   \
    \ std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n    int n;\n\
    \    std::cin >> n;\n    m1une::string::AhoCorasick<> automaton;\n    for (int\
    \ i = 0; i < n; i++) {\n        std::string pattern;\n        std::cin >> pattern;\n\
    \        automaton.insert(pattern);\n    }\n    automaton.build();\n\n    int\
    \ node_count = int(automaton.node_count());\n    std::cout << node_count << '\\\
    n';\n    for (int id = 1; id < node_count; id++) {\n        const auto& node =\
    \ automaton.node(id);\n        std::cout << node.parent << ' ' << node.failure\
    \ << '\\n';\n    }\n    for (int i = 0; i < n; i++) {\n        if (i) std::cout\
    \ << ' ';\n        std::cout << automaton.pattern_node(i);\n    }\n    std::cout\
    \ << '\\n';\n}\n"
  dependsOn:
  - string/aho_corasick.hpp
  isVerificationFile: true
  path: verify/string/aho_corasick.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 03:13:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/aho_corasick.test.cpp
layout: document
redirect_from:
- /verify/verify/string/aho_corasick.test.cpp
- /verify/verify/string/aho_corasick.test.cpp.html
title: verify/string/aho_corasick.test.cpp
---
