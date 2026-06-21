---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: string/trie.hpp
    title: Trie
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
  bundledCode: "#line 1 \"verify/string/trie.test.cpp\"\n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C\"\
    \n\n#line 1 \"string/trie.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\n// A multiset trie for a contiguous character alphabet.\n\
    template <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct Trie {\n  \
    \  static_assert(0 < AlphabetSize);\n\n   private:\n    struct Node {\n      \
    \  std::array<int, AlphabetSize> child;\n        int subtree_count;\n        int\
    \ terminal_count;\n\n        Node() : subtree_count(0), terminal_count(0) {\n\
    \            child.fill(-1);\n        }\n    };\n\n    std::vector<Node> _nodes;\n\
    \    int _distinct_size;\n\n    template <class Symbol>\n    static int symbol_index(const\
    \ Symbol& symbol) {\n        int index = int(symbol) - FirstCharacter;\n     \
    \   assert(0 <= index && index < AlphabetSize);\n        return index;\n    }\n\
    \n    int new_node() {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    template <class Sequence>\n    int find_node(const Sequence& sequence) const\
    \ {\n        int node = 0;\n        for (const auto& symbol : sequence) {\n  \
    \          node = _nodes[node].child[symbol_index(symbol)];\n            if (node\
    \ == -1 || _nodes[node].subtree_count == 0) return -1;\n        }\n        return\
    \ node;\n    }\n\n   public:\n    Trie() : _nodes(1), _distinct_size(0) {}\n\n\
    \    int size() const {\n        return _nodes[0].subtree_count;\n    }\n\n  \
    \  int distinct_size() const {\n        return _distinct_size;\n    }\n\n    bool\
    \ empty() const {\n        return size() == 0;\n    }\n\n    std::size_t node_count()\
    \ const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n       \
    \ _distinct_size = 0;\n    }\n\n    template <class Sequence>\n    void insert(const\
    \ Sequence& sequence, int multiplicity = 1) {\n        assert(0 < multiplicity);\n\
    \        int node = 0;\n        _nodes[node].subtree_count += multiplicity;\n\
    \        for (const auto& symbol : sequence) {\n            int index = symbol_index(symbol);\n\
    \            int child = _nodes[node].child[index];\n            if (child ==\
    \ -1) {\n                child = new_node();\n                _nodes[node].child[index]\
    \ = child;\n            }\n            node = child;\n            _nodes[node].subtree_count\
    \ += multiplicity;\n        }\n        if (_nodes[node].terminal_count == 0) _distinct_size++;\n\
    \        _nodes[node].terminal_count += multiplicity;\n    }\n\n    template <class\
    \ Sequence>\n    int count(const Sequence& sequence) const {\n        int node\
    \ = find_node(sequence);\n        return node == -1 ? 0 : _nodes[node].terminal_count;\n\
    \    }\n\n    template <class Sequence>\n    bool contains(const Sequence& sequence)\
    \ const {\n        return count(sequence) != 0;\n    }\n\n    // Returns the number\
    \ of stored strings beginning with prefix.\n    template <class Sequence>\n  \
    \  int prefix_count(const Sequence& prefix) const {\n        int node = find_node(prefix);\n\
    \        return node == -1 ? 0 : _nodes[node].subtree_count;\n    }\n\n    template\
    \ <class Sequence>\n    bool starts_with(const Sequence& prefix) const {\n   \
    \     return prefix_count(prefix) != 0;\n    }\n\n    template <class Sequence>\n\
    \    bool erase_one(const Sequence& sequence) {\n        int terminal = find_node(sequence);\n\
    \        if (terminal == -1 || _nodes[terminal].terminal_count == 0) return false;\n\
    \n        int node = 0;\n        _nodes[node].subtree_count--;\n        for (const\
    \ auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            _nodes[node].subtree_count--;\n        }\n        _nodes[node].terminal_count--;\n\
    \        if (_nodes[node].terminal_count == 0) _distinct_size--;\n        return\
    \ true;\n    }\n\n    template <class Sequence>\n    bool erase(const Sequence&\
    \ sequence) {\n        return erase_one(sequence);\n    }\n\n    template <class\
    \ Sequence>\n    int erase_all(const Sequence& sequence) {\n        int multiplicity\
    \ = count(sequence);\n        if (multiplicity == 0) return 0;\n\n        int\
    \ node = 0;\n        _nodes[node].subtree_count -= multiplicity;\n        for\
    \ (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            _nodes[node].subtree_count -= multiplicity;\n        }\n        _nodes[node].terminal_count\
    \ = 0;\n        _distinct_size--;\n        return multiplicity;\n    }\n\n   \
    \ // Calls callback(length, multiplicity) for every stored prefix.\n    // The\
    \ empty prefix is reported with length 0 when it is stored.\n    template <class\
    \ Sequence, class Callback>\n    void for_each_prefix(const Sequence& sequence,\
    \ Callback callback) const {\n        int node = 0;\n        if (_nodes[node].terminal_count\
    \ != 0) {\n            callback(0, _nodes[node].terminal_count);\n        }\n\n\
    \        int length = 0;\n        for (const auto& symbol : sequence) {\n    \
    \        node = _nodes[node].child[symbol_index(symbol)];\n            if (node\
    \ == -1 || _nodes[node].subtree_count == 0) return;\n            length++;\n \
    \           if (_nodes[node].terminal_count != 0) {\n                callback(length,\
    \ _nodes[node].terminal_count);\n            }\n        }\n    }\n\n    // Returns\
    \ the length of the longest stored string that is a prefix.\n    // Returns -1\
    \ when no stored prefix exists.\n    template <class Sequence>\n    int longest_prefix(const\
    \ Sequence& sequence) const {\n        int result = _nodes[0].terminal_count ==\
    \ 0 ? -1 : 0;\n        for_each_prefix(sequence, [&result](int length, int) {\n\
    \            result = length;\n        });\n        return result;\n    }\n};\n\
    \n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/trie.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/string/trie.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <map>\n#include <string>\n#line 12 \"verify/string/trie.test.cpp\"\
    \n\nnamespace {\n\nvoid test_features() {\n    m1une::string::Trie<> trie;\n \
    \   assert(trie.empty());\n    assert(trie.node_count() == 1);\n    trie.reserve(128);\n\
    \n    trie.insert(std::string());\n    trie.insert(std::string(\"app\"), 2);\n\
    \    trie.insert(std::string(\"apple\"));\n    trie.insert(std::string(\"apt\"\
    ));\n\n    assert(trie.size() == 5);\n    assert(trie.distinct_size() == 4);\n\
    \    assert(trie.count(std::string(\"app\")) == 2);\n    assert(trie.prefix_count(std::string(\"\
    ap\")) == 4);\n    assert(trie.prefix_count(std::string()) == 5);\n    assert(trie.starts_with(std::string(\"\
    appl\")));\n    assert(!trie.starts_with(std::string(\"b\")));\n    assert(trie.longest_prefix(std::string(\"\
    apples\")) == 5);\n    assert(trie.longest_prefix(std::string(\"banana\")) ==\
    \ 0);\n\n    std::vector<std::pair<int, int>> prefixes;\n    trie.for_each_prefix(std::string(\"\
    applepie\"), [&prefixes](int length, int count) {\n        prefixes.emplace_back(length,\
    \ count);\n    });\n    std::vector<std::pair<int, int>> expected;\n    expected.emplace_back(0,\
    \ 1);\n    expected.emplace_back(3, 2);\n    expected.emplace_back(5, 1);\n  \
    \  assert(prefixes == expected);\n\n    assert(trie.erase_one(std::string(\"app\"\
    )));\n    assert(trie.count(std::string(\"app\")) == 1);\n    assert(trie.erase_all(std::string(\"\
    app\")) == 1);\n    assert(!trie.contains(std::string(\"app\")));\n    assert(!trie.erase(std::string(\"\
    app\")));\n    assert(trie.distinct_size() == 3);\n\n    m1une::string::Trie<10,\
    \ '0'> digits;\n    digits.insert(std::string(\"012\"));\n    assert(digits.contains(std::string(\"\
    012\")));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 37;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    m1une::string::Trie<4, 'a'> trie;\n\
    \    std::map<std::string, int> expected;\n\n    for (int step = 0; step < 10000;\
    \ step++) {\n        int length = int(random() % 9);\n        std::string word(length,\
    \ 'a');\n        for (char& character : word) character = char('a' + random()\
    \ % 4);\n        int type = int(random() % 6);\n\n        if (type == 0) {\n \
    \           int multiplicity = int(random() % 3) + 1;\n            trie.insert(word,\
    \ multiplicity);\n            expected[word] += multiplicity;\n        } else\
    \ if (type == 1) {\n            [[maybe_unused]] bool erased = trie.erase_one(word);\n\
    \            bool expected_erased = expected[word] != 0;\n            assert(erased\
    \ == expected_erased);\n            if (expected_erased) expected[word]--;\n \
    \       } else if (type == 2) {\n            [[maybe_unused]] int erased = trie.erase_all(word);\n\
    \            assert(erased == expected[word]);\n            expected[word] = 0;\n\
    \        } else {\n            assert(trie.count(word) == expected[word]);\n \
    \           [[maybe_unused]] int prefix_count = 0;\n            for (const auto&\
    \ entry : expected) {\n                if (\n                    entry.first.size()\
    \ >= word.size() &&\n                    entry.first.compare(0, word.size(), word)\
    \ == 0\n                ) {\n                    prefix_count += entry.second;\n\
    \                }\n            }\n            assert(trie.prefix_count(word)\
    \ == prefix_count);\n\n            int longest = -1;\n            for (const auto&\
    \ entry : expected) {\n                if (\n                    entry.second\
    \ != 0 &&\n                    entry.first.size() <= word.size() &&\n        \
    \            word.compare(0, entry.first.size(), entry.first) == 0\n         \
    \       ) {\n                    longest = std::max(longest, int(entry.first.size()));\n\
    \                }\n            }\n            assert(trie.longest_prefix(word)\
    \ == longest);\n        }\n\n        [[maybe_unused]] int size = 0;\n        [[maybe_unused]]\
    \ int distinct = 0;\n        for (const auto& entry : expected) {\n          \
    \  size += entry.second;\n            if (entry.second != 0) distinct++;\n   \
    \     }\n        assert(trie.size() == size);\n        assert(trie.distinct_size()\
    \ == distinct);\n    }\n\n    trie.clear();\n    assert(trie.empty());\n    assert(trie.distinct_size()\
    \ == 0);\n    assert(trie.node_count() == 1);\n}\n\n}  // namespace\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ test_features();\n    test_randomized();\n\n    int q;\n    std::cin >> q;\n\
    \    m1une::string::Trie<> trie;\n    while (q--) {\n        std::string command;\n\
    \        std::string word;\n        std::cin >> command >> word;\n        if (command\
    \ == \"insert\") {\n            trie.insert(word);\n        } else {\n       \
    \     std::cout << (trie.contains(word) ? \"yes\" : \"no\") << '\\n';\n      \
    \  }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C\"\
    \n\n#include \"../../string/trie.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <cstdint>\n#include <iostream>\n#include <map>\n#include <string>\n#include\
    \ <vector>\n\nnamespace {\n\nvoid test_features() {\n    m1une::string::Trie<>\
    \ trie;\n    assert(trie.empty());\n    assert(trie.node_count() == 1);\n    trie.reserve(128);\n\
    \n    trie.insert(std::string());\n    trie.insert(std::string(\"app\"), 2);\n\
    \    trie.insert(std::string(\"apple\"));\n    trie.insert(std::string(\"apt\"\
    ));\n\n    assert(trie.size() == 5);\n    assert(trie.distinct_size() == 4);\n\
    \    assert(trie.count(std::string(\"app\")) == 2);\n    assert(trie.prefix_count(std::string(\"\
    ap\")) == 4);\n    assert(trie.prefix_count(std::string()) == 5);\n    assert(trie.starts_with(std::string(\"\
    appl\")));\n    assert(!trie.starts_with(std::string(\"b\")));\n    assert(trie.longest_prefix(std::string(\"\
    apples\")) == 5);\n    assert(trie.longest_prefix(std::string(\"banana\")) ==\
    \ 0);\n\n    std::vector<std::pair<int, int>> prefixes;\n    trie.for_each_prefix(std::string(\"\
    applepie\"), [&prefixes](int length, int count) {\n        prefixes.emplace_back(length,\
    \ count);\n    });\n    std::vector<std::pair<int, int>> expected;\n    expected.emplace_back(0,\
    \ 1);\n    expected.emplace_back(3, 2);\n    expected.emplace_back(5, 1);\n  \
    \  assert(prefixes == expected);\n\n    assert(trie.erase_one(std::string(\"app\"\
    )));\n    assert(trie.count(std::string(\"app\")) == 1);\n    assert(trie.erase_all(std::string(\"\
    app\")) == 1);\n    assert(!trie.contains(std::string(\"app\")));\n    assert(!trie.erase(std::string(\"\
    app\")));\n    assert(trie.distinct_size() == 3);\n\n    m1une::string::Trie<10,\
    \ '0'> digits;\n    digits.insert(std::string(\"012\"));\n    assert(digits.contains(std::string(\"\
    012\")));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 37;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    m1une::string::Trie<4, 'a'> trie;\n\
    \    std::map<std::string, int> expected;\n\n    for (int step = 0; step < 10000;\
    \ step++) {\n        int length = int(random() % 9);\n        std::string word(length,\
    \ 'a');\n        for (char& character : word) character = char('a' + random()\
    \ % 4);\n        int type = int(random() % 6);\n\n        if (type == 0) {\n \
    \           int multiplicity = int(random() % 3) + 1;\n            trie.insert(word,\
    \ multiplicity);\n            expected[word] += multiplicity;\n        } else\
    \ if (type == 1) {\n            [[maybe_unused]] bool erased = trie.erase_one(word);\n\
    \            bool expected_erased = expected[word] != 0;\n            assert(erased\
    \ == expected_erased);\n            if (expected_erased) expected[word]--;\n \
    \       } else if (type == 2) {\n            [[maybe_unused]] int erased = trie.erase_all(word);\n\
    \            assert(erased == expected[word]);\n            expected[word] = 0;\n\
    \        } else {\n            assert(trie.count(word) == expected[word]);\n \
    \           [[maybe_unused]] int prefix_count = 0;\n            for (const auto&\
    \ entry : expected) {\n                if (\n                    entry.first.size()\
    \ >= word.size() &&\n                    entry.first.compare(0, word.size(), word)\
    \ == 0\n                ) {\n                    prefix_count += entry.second;\n\
    \                }\n            }\n            assert(trie.prefix_count(word)\
    \ == prefix_count);\n\n            int longest = -1;\n            for (const auto&\
    \ entry : expected) {\n                if (\n                    entry.second\
    \ != 0 &&\n                    entry.first.size() <= word.size() &&\n        \
    \            word.compare(0, entry.first.size(), entry.first) == 0\n         \
    \       ) {\n                    longest = std::max(longest, int(entry.first.size()));\n\
    \                }\n            }\n            assert(trie.longest_prefix(word)\
    \ == longest);\n        }\n\n        [[maybe_unused]] int size = 0;\n        [[maybe_unused]]\
    \ int distinct = 0;\n        for (const auto& entry : expected) {\n          \
    \  size += entry.second;\n            if (entry.second != 0) distinct++;\n   \
    \     }\n        assert(trie.size() == size);\n        assert(trie.distinct_size()\
    \ == distinct);\n    }\n\n    trie.clear();\n    assert(trie.empty());\n    assert(trie.distinct_size()\
    \ == 0);\n    assert(trie.node_count() == 1);\n}\n\n}  // namespace\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\n   \
    \ test_features();\n    test_randomized();\n\n    int q;\n    std::cin >> q;\n\
    \    m1une::string::Trie<> trie;\n    while (q--) {\n        std::string command;\n\
    \        std::string word;\n        std::cin >> command >> word;\n        if (command\
    \ == \"insert\") {\n            trie.insert(word);\n        } else {\n       \
    \     std::cout << (trie.contains(word) ? \"yes\" : \"no\") << '\\n';\n      \
    \  }\n    }\n}\n"
  dependsOn:
  - string/trie.hpp
  isVerificationFile: true
  path: verify/string/trie.test.cpp
  requiredBy: []
  timestamp: '2026-06-21 04:34:53+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/string/trie.test.cpp
layout: document
redirect_from:
- /verify/verify/string/trie.test.cpp
- /verify/verify/string/trie.test.cpp.html
title: verify/string/trie.test.cpp
---
