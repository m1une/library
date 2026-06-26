---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/eertree.hpp
    title: Eertree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/eertree
    links:
    - https://judge.yosupo.jp/problem/eertree
  bundledCode: "#line 1 \"verify/string/eertree.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/eertree\"\
    \n\n#line 1 \"string/eertree.hpp\"\n\n\n\n#include <array>\n#include <cassert>\n\
    #include <cstddef>\n#include <limits>\n#include <utility>\n#include <vector>\n\
    \nnamespace m1une {\nnamespace string {\n\ntemplate <int AlphabetSize = 26, int\
    \ FirstCharacter = 'a'>\nstruct Eertree {\n    static_assert(0 < AlphabetSize);\n\
    \n    using node_id = int;\n    static constexpr node_id even_root = 0;\n    static\
    \ constexpr node_id odd_root = 1;\n    static constexpr node_id null_node = -1;\n\
    \n    struct Node {\n        std::array<node_id, AlphabetSize> next;\n       \
    \ node_id suffix_link;\n        node_id series_link;\n        int length;\n  \
    \      int diff;\n        int suffix_count;\n        int first_end;\n        long\
    \ long suffix_occurrences;\n\n        Node(int length_value = 0, node_id suffix_link_value\
    \ = even_root, node_id series_link_value = even_root)\n            : suffix_link(suffix_link_value),\n\
    \              series_link(series_link_value),\n              length(length_value),\n\
    \              diff(0),\n              suffix_count(0),\n              first_end(0),\n\
    \              suffix_occurrences(0) {\n            next.fill(null_node);\n  \
    \      }\n    };\n\n   private:\n    std::vector<Node> _nodes;\n    std::vector<int>\
    \ _text;\n    std::vector<node_id> _longest_suffix;\n    node_id _last;\n\n  \
    \  template <class Symbol>\n    static int symbol_index(const Symbol& symbol)\
    \ {\n        int index = int(symbol) - FirstCharacter;\n        assert(0 <= index\
    \ && index < AlphabetSize);\n        return index;\n    }\n\n    node_id find_extendable(node_id\
    \ node, int position, int symbol) const {\n        while (true) {\n          \
    \  int length = _nodes[node].length;\n            int left = position - length\
    \ - 1;\n            if (0 <= left && _text[left] == symbol) return node;\n   \
    \         node = _nodes[node].suffix_link;\n        }\n    }\n\n    node_id new_node(int\
    \ length) {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back(length);\n        return int(_nodes.size()) - 1;\n\
    \    }\n\n   public:\n    Eertree() {\n        clear();\n    }\n\n    template\
    \ <class Sequence>\n    explicit Eertree(const Sequence& sequence) {\n       \
    \ clear();\n        build(sequence);\n    }\n\n    int size() const {\n      \
    \  return int(_nodes.size()) - 2;\n    }\n\n    bool empty() const {\n       \
    \ return size() == 0;\n    }\n\n    int node_count() const {\n        return int(_nodes.size());\n\
    \    }\n\n    int text_length() const {\n        return int(_text.size());\n \
    \   }\n\n    node_id last() const {\n        return _last;\n    }\n\n    int longest_suffix_length()\
    \ const {\n        return _nodes[_last].length;\n    }\n\n    const Node& node(node_id\
    \ id) const {\n        assert(0 <= id && id < node_count());\n        return _nodes[id];\n\
    \    }\n\n    const std::vector<Node>& nodes() const {\n        return _nodes;\n\
    \    }\n\n    node_id longest_suffix_node(int prefix_length) const {\n       \
    \ assert(1 <= prefix_length && prefix_length <= text_length());\n        return\
    \ _longest_suffix[prefix_length - 1];\n    }\n\n    const std::vector<node_id>&\
    \ longest_suffix_nodes() const {\n        return _longest_suffix;\n    }\n\n \
    \   template <class Callback>\n    void for_each_suffix(node_id id, Callback callback)\
    \ const {\n        assert(0 <= id && id < node_count());\n        while (id >=\
    \ 2) {\n            callback(id);\n            id = _nodes[id].suffix_link;\n\
    \        }\n    }\n\n    template <class Callback>\n    void for_each_suffix(Callback\
    \ callback) const {\n        for_each_suffix(_last, callback);\n    }\n\n    void\
    \ reserve(std::size_t text_capacity) {\n        _text.reserve(text_capacity);\n\
    \        _longest_suffix.reserve(text_capacity);\n        _nodes.reserve(text_capacity\
    \ + 2);\n    }\n\n    void clear() {\n        _nodes.clear();\n        _nodes.emplace_back(0,\
    \ odd_root, even_root);\n        _nodes.emplace_back(-1, odd_root, odd_root);\n\
    \        _text.clear();\n        _longest_suffix.clear();\n        _last = even_root;\n\
    \    }\n\n    template <class Symbol>\n    node_id add(const Symbol& value) {\n\
    \        int symbol = symbol_index(value);\n        int position = int(_text.size());\n\
    \        _text.push_back(symbol);\n\n        node_id current = find_extendable(_last,\
    \ position, symbol);\n        node_id next = _nodes[current].next[symbol];\n \
    \       if (next == null_node) {\n            int length = _nodes[current].length\
    \ + 2;\n            next = new_node(length);\n            _nodes[current].next[symbol]\
    \ = next;\n\n            node_id suffix_link = even_root;\n            if (length\
    \ != 1) {\n                node_id candidate = find_extendable(_nodes[current].suffix_link,\
    \ position, symbol);\n                suffix_link = _nodes[candidate].next[symbol];\n\
    \                assert(suffix_link != null_node);\n            }\n\n        \
    \    Node& created = _nodes[next];\n            created.suffix_link = suffix_link;\n\
    \            created.diff = created.length - _nodes[suffix_link].length;\n   \
    \         created.series_link =\n                created.diff == _nodes[suffix_link].diff\
    \ ? _nodes[suffix_link].series_link : suffix_link;\n            created.suffix_count\
    \ = _nodes[suffix_link].suffix_count + 1;\n            created.first_end = position\
    \ + 1;\n        }\n\n        _last = next;\n        _nodes[_last].suffix_occurrences++;\n\
    \        _longest_suffix.push_back(_last);\n        return _last;\n    }\n\n \
    \   template <class Sequence>\n    void build(const Sequence& sequence) {\n  \
    \      for (const auto& symbol : sequence) add(symbol);\n    }\n\n    std::vector<long\
    \ long> occurrence_counts() const {\n        std::vector<long long> result(_nodes.size(),\
    \ 0);\n        for (node_id id = 0; id < node_count(); id++) {\n            result[id]\
    \ = _nodes[id].suffix_occurrences;\n        }\n        for (node_id id = node_count()\
    \ - 1; id >= 2; id--) {\n            result[_nodes[id].suffix_link] += result[id];\n\
    \        }\n        return result;\n    }\n\n    std::pair<int, int> first_occurrence(node_id\
    \ id) const {\n        assert(2 <= id && id < node_count());\n        int end\
    \ = _nodes[id].first_end;\n        return {end - _nodes[id].length, end};\n  \
    \  }\n};\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nusing\
    \ PalindromicTree = Eertree<AlphabetSize, FirstCharacter>;\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/eertree.test.cpp\"\
    \n\n#include <algorithm>\n#line 7 \"verify/string/eertree.test.cpp\"\n#include\
    \ <cstdint>\n#include <iostream>\n#include <map>\n#include <set>\n#include <string>\n\
    #line 14 \"verify/string/eertree.test.cpp\"\n\nnamespace {\n\nbool is_palindrome(const\
    \ std::string& text, int left, int right) {\n    while (left < right) {\n    \
    \    right--;\n        if (text[left] != text[right]) return false;\n        left++;\n\
    \    }\n    return true;\n}\n\nvoid test_features() {\n    using Eertree = m1une::string::Eertree<>;\n\
    \    Eertree tree;\n    tree.reserve(16);\n    assert(tree.empty());\n    assert(tree.node_count()\
    \ == 2);\n    assert(tree.node(Eertree::even_root).length == 0);\n    assert(tree.node(Eertree::odd_root).length\
    \ == -1);\n\n    std::string text = \"ababa\";\n    for (char character : text)\
    \ tree.add(character);\n    assert(tree.size() == 5);\n    assert(tree.text_length()\
    \ == 5);\n    assert(tree.longest_suffix_length() == 5);\n    assert(tree.node(tree.last()).suffix_count\
    \ == 3);\n\n    std::vector<int> expected_lengths = {1, 1, 3, 3, 5};\n    std::vector<int>\
    \ actual_lengths;\n    for (int id = 2; id < tree.node_count(); id++) {\n    \
    \    actual_lengths.push_back(tree.node(id).length);\n        auto [left, right]\
    \ = tree.first_occurrence(id);\n        assert(right - left == tree.node(id).length);\n\
    \        assert(is_palindrome(text, left, right));\n    }\n    assert(actual_lengths\
    \ == expected_lengths);\n\n    std::vector<long long> occurrence = tree.occurrence_counts();\n\
    \    std::map<std::string, long long> expected;\n    expected[\"a\"] = 3;\n  \
    \  expected[\"b\"] = 2;\n    expected[\"aba\"] = 2;\n    expected[\"bab\"] = 1;\n\
    \    expected[\"ababa\"] = 1;\n    for (int id = 2; id < tree.node_count(); id++)\
    \ {\n        auto [left, right] = tree.first_occurrence(id);\n        assert(occurrence[id]\
    \ == expected[text.substr(left, right - left)]);\n    }\n\n    assert(tree.node(tree.longest_suffix_node(1)).length\
    \ == 1);\n    assert(tree.node(tree.longest_suffix_node(2)).length == 1);\n  \
    \  assert(tree.node(tree.longest_suffix_node(3)).length == 3);\n    assert(tree.node(tree.longest_suffix_node(4)).length\
    \ == 3);\n    assert(tree.node(tree.longest_suffix_node(5)).length == 5);\n  \
    \  std::vector<int> suffix_lengths;\n    tree.for_each_suffix([&](int id) {\n\
    \        suffix_lengths.push_back(tree.node(id).length);\n    });\n    assert(suffix_lengths\
    \ == std::vector<int>({5, 3, 1}));\n\n    m1une::string::PalindromicTree<10, '0'>\
    \ digits(std::string(\"01210\"));\n    assert(digits.longest_suffix_length() ==\
    \ 5);\n\n    tree.clear();\n    assert(tree.empty());\n    assert(tree.text_length()\
    \ == 0);\n    assert(tree.last() == Eertree::even_root);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 91;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2000; trial++) {\n        int n = int(random()\
    \ % 60);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n\n        m1une::string::Eertree<4, 'a'>\
    \ tree(text);\n        std::map<std::string, long long> expected_count;\n    \
    \    std::vector<int> expected_longest(n, 0);\n        for (int left = 0; left\
    \ < n; left++) {\n            for (int right = left + 1; right <= n; right++)\
    \ {\n                if (!is_palindrome(text, left, right)) continue;\n      \
    \          expected_count[text.substr(left, right - left)]++;\n              \
    \  expected_longest[right - 1] = std::max(expected_longest[right - 1], right -\
    \ left);\n            }\n        }\n\n        assert(tree.size() == int(expected_count.size()));\n\
    \        assert(tree.node_count() <= n + 2);\n        std::vector<long long> occurrence\
    \ = tree.occurrence_counts();\n        std::set<std::string> represented;\n  \
    \      for (int id = 2; id < tree.node_count(); id++) {\n            const auto&\
    \ node = tree.node(id);\n            auto [left, right] = tree.first_occurrence(id);\n\
    \            std::string palindrome = text.substr(left, right - left);\n     \
    \       assert(is_palindrome(text, left, right));\n            assert(node.length\
    \ == int(palindrome.size()));\n            assert(represented.insert(palindrome).second);\n\
    \            assert(occurrence[id] == expected_count[palindrome]);\n         \
    \   assert(tree.node(node.suffix_link).length < node.length);\n            assert(node.diff\
    \ == node.length - tree.node(node.suffix_link).length);\n            assert(node.suffix_count\
    \ == tree.node(node.suffix_link).suffix_count + 1);\n            assert(tree.node(node.series_link).length\
    \ < node.length);\n        }\n        assert(represented.size() == expected_count.size());\n\
    \        for (int prefix = 1; prefix <= n; prefix++) {\n            int id = tree.longest_suffix_node(prefix);\n\
    \            assert(tree.node(id).length == expected_longest[prefix - 1]);\n \
    \       }\n    }\n}\n\nint library_checker_id(int id) {\n    using Eertree = m1une::string::Eertree<>;\n\
    \    if (id == Eertree::odd_root) return 0;\n    if (id == Eertree::even_root)\
    \ return 1;\n    return id;\n}\n\n}  // namespace\n\nint main() {\n    test_features();\n\
    \    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string text;\n    std::cin >> text;\n    m1une::string::Eertree<> tree(text);\n\
    \n    std::vector<int> parent(tree.node_count(), -1);\n    for (int id = 0; id\
    \ < tree.node_count(); id++) {\n        const auto& node = tree.node(id);\n  \
    \      for (int symbol = 0; symbol < 26; symbol++) {\n            int to = node.next[symbol];\n\
    \            if (to != m1une::string::Eertree<>::null_node) parent[to] = id;\n\
    \        }\n    }\n\n    std::cout << tree.size() << '\\n';\n    for (int id =\
    \ 2; id < tree.node_count(); id++) {\n        std::cout << library_checker_id(parent[id])\
    \ - 1 << ' '\n                  << library_checker_id(tree.node(id).suffix_link)\
    \ - 1 << '\\n';\n    }\n    const auto& longest_suffix = tree.longest_suffix_nodes();\n\
    \    for (int i = 0; i < int(longest_suffix.size()); i++) {\n        if (i) std::cout\
    \ << ' ';\n        std::cout << longest_suffix[i] - 1;\n    }\n    std::cout <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/eertree\"\n\n#include \"\
    ../../string/eertree.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include\
    \ <cstdint>\n#include <iostream>\n#include <map>\n#include <set>\n#include <string>\n\
    #include <utility>\n#include <vector>\n\nnamespace {\n\nbool is_palindrome(const\
    \ std::string& text, int left, int right) {\n    while (left < right) {\n    \
    \    right--;\n        if (text[left] != text[right]) return false;\n        left++;\n\
    \    }\n    return true;\n}\n\nvoid test_features() {\n    using Eertree = m1une::string::Eertree<>;\n\
    \    Eertree tree;\n    tree.reserve(16);\n    assert(tree.empty());\n    assert(tree.node_count()\
    \ == 2);\n    assert(tree.node(Eertree::even_root).length == 0);\n    assert(tree.node(Eertree::odd_root).length\
    \ == -1);\n\n    std::string text = \"ababa\";\n    for (char character : text)\
    \ tree.add(character);\n    assert(tree.size() == 5);\n    assert(tree.text_length()\
    \ == 5);\n    assert(tree.longest_suffix_length() == 5);\n    assert(tree.node(tree.last()).suffix_count\
    \ == 3);\n\n    std::vector<int> expected_lengths = {1, 1, 3, 3, 5};\n    std::vector<int>\
    \ actual_lengths;\n    for (int id = 2; id < tree.node_count(); id++) {\n    \
    \    actual_lengths.push_back(tree.node(id).length);\n        auto [left, right]\
    \ = tree.first_occurrence(id);\n        assert(right - left == tree.node(id).length);\n\
    \        assert(is_palindrome(text, left, right));\n    }\n    assert(actual_lengths\
    \ == expected_lengths);\n\n    std::vector<long long> occurrence = tree.occurrence_counts();\n\
    \    std::map<std::string, long long> expected;\n    expected[\"a\"] = 3;\n  \
    \  expected[\"b\"] = 2;\n    expected[\"aba\"] = 2;\n    expected[\"bab\"] = 1;\n\
    \    expected[\"ababa\"] = 1;\n    for (int id = 2; id < tree.node_count(); id++)\
    \ {\n        auto [left, right] = tree.first_occurrence(id);\n        assert(occurrence[id]\
    \ == expected[text.substr(left, right - left)]);\n    }\n\n    assert(tree.node(tree.longest_suffix_node(1)).length\
    \ == 1);\n    assert(tree.node(tree.longest_suffix_node(2)).length == 1);\n  \
    \  assert(tree.node(tree.longest_suffix_node(3)).length == 3);\n    assert(tree.node(tree.longest_suffix_node(4)).length\
    \ == 3);\n    assert(tree.node(tree.longest_suffix_node(5)).length == 5);\n  \
    \  std::vector<int> suffix_lengths;\n    tree.for_each_suffix([&](int id) {\n\
    \        suffix_lengths.push_back(tree.node(id).length);\n    });\n    assert(suffix_lengths\
    \ == std::vector<int>({5, 3, 1}));\n\n    m1une::string::PalindromicTree<10, '0'>\
    \ digits(std::string(\"01210\"));\n    assert(digits.longest_suffix_length() ==\
    \ 5);\n\n    tree.clear();\n    assert(tree.empty());\n    assert(tree.text_length()\
    \ == 0);\n    assert(tree.last() == Eertree::even_root);\n}\n\nvoid test_randomized()\
    \ {\n    std::uint64_t state = 91;\n    auto random = [&state]() {\n        state\
    \ ^= state << 7;\n        state ^= state >> 9;\n        return state;\n    };\n\
    \n    for (int trial = 0; trial < 2000; trial++) {\n        int n = int(random()\
    \ % 60);\n        std::string text(n, 'a');\n        for (char& character : text)\
    \ character = char('a' + random() % 4);\n\n        m1une::string::Eertree<4, 'a'>\
    \ tree(text);\n        std::map<std::string, long long> expected_count;\n    \
    \    std::vector<int> expected_longest(n, 0);\n        for (int left = 0; left\
    \ < n; left++) {\n            for (int right = left + 1; right <= n; right++)\
    \ {\n                if (!is_palindrome(text, left, right)) continue;\n      \
    \          expected_count[text.substr(left, right - left)]++;\n              \
    \  expected_longest[right - 1] = std::max(expected_longest[right - 1], right -\
    \ left);\n            }\n        }\n\n        assert(tree.size() == int(expected_count.size()));\n\
    \        assert(tree.node_count() <= n + 2);\n        std::vector<long long> occurrence\
    \ = tree.occurrence_counts();\n        std::set<std::string> represented;\n  \
    \      for (int id = 2; id < tree.node_count(); id++) {\n            const auto&\
    \ node = tree.node(id);\n            auto [left, right] = tree.first_occurrence(id);\n\
    \            std::string palindrome = text.substr(left, right - left);\n     \
    \       assert(is_palindrome(text, left, right));\n            assert(node.length\
    \ == int(palindrome.size()));\n            assert(represented.insert(palindrome).second);\n\
    \            assert(occurrence[id] == expected_count[palindrome]);\n         \
    \   assert(tree.node(node.suffix_link).length < node.length);\n            assert(node.diff\
    \ == node.length - tree.node(node.suffix_link).length);\n            assert(node.suffix_count\
    \ == tree.node(node.suffix_link).suffix_count + 1);\n            assert(tree.node(node.series_link).length\
    \ < node.length);\n        }\n        assert(represented.size() == expected_count.size());\n\
    \        for (int prefix = 1; prefix <= n; prefix++) {\n            int id = tree.longest_suffix_node(prefix);\n\
    \            assert(tree.node(id).length == expected_longest[prefix - 1]);\n \
    \       }\n    }\n}\n\nint library_checker_id(int id) {\n    using Eertree = m1une::string::Eertree<>;\n\
    \    if (id == Eertree::odd_root) return 0;\n    if (id == Eertree::even_root)\
    \ return 1;\n    return id;\n}\n\n}  // namespace\n\nint main() {\n    test_features();\n\
    \    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string text;\n    std::cin >> text;\n    m1une::string::Eertree<> tree(text);\n\
    \n    std::vector<int> parent(tree.node_count(), -1);\n    for (int id = 0; id\
    \ < tree.node_count(); id++) {\n        const auto& node = tree.node(id);\n  \
    \      for (int symbol = 0; symbol < 26; symbol++) {\n            int to = node.next[symbol];\n\
    \            if (to != m1une::string::Eertree<>::null_node) parent[to] = id;\n\
    \        }\n    }\n\n    std::cout << tree.size() << '\\n';\n    for (int id =\
    \ 2; id < tree.node_count(); id++) {\n        std::cout << library_checker_id(parent[id])\
    \ - 1 << ' '\n                  << library_checker_id(tree.node(id).suffix_link)\
    \ - 1 << '\\n';\n    }\n    const auto& longest_suffix = tree.longest_suffix_nodes();\n\
    \    for (int i = 0; i < int(longest_suffix.size()); i++) {\n        if (i) std::cout\
    \ << ' ';\n        std::cout << longest_suffix[i] - 1;\n    }\n    std::cout <<\
    \ '\\n';\n}\n"
  dependsOn:
  - string/eertree.hpp
  isVerificationFile: true
  path: verify/string/eertree.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 03:13:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/eertree.test.cpp
layout: document
redirect_from:
- /verify/verify/string/eertree.test.cpp
- /verify/verify/string/eertree.test.cpp.html
title: verify/string/eertree.test.cpp
---
