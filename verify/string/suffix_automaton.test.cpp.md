---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/suffix_automaton.hpp
    title: Suffix Automaton
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/number_of_substrings
    links:
    - https://judge.yosupo.jp/problem/number_of_substrings
  bundledCode: "#line 1 \"verify/string/suffix_automaton.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\n#line 1 \"string/suffix_automaton.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <cstddef>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\nnamespace m1une {\n\
    namespace string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\n\
    struct SuffixAutomaton {\n    static_assert(0 < AlphabetSize);\n\n    using state_id\
    \ = int;\n    static constexpr state_id root_state = 0;\n    static constexpr\
    \ state_id null_state = -1;\n\n    struct State {\n        std::array<state_id,\
    \ AlphabetSize> next;\n        state_id suffix_link;\n        int length;\n  \
    \      int first_end;\n        int direct_occurrences;\n        bool clone;\n\n\
    \        State(int length_value = 0)\n            : suffix_link(null_state),\n\
    \              length(length_value),\n              first_end(0),\n          \
    \    direct_occurrences(0),\n              clone(false) {\n            next.fill(null_state);\n\
    \        }\n    };\n\n   private:\n    std::vector<State> _states;\n    state_id\
    \ _last;\n    int _text_length;\n\n    template <class Symbol>\n    static int\
    \ symbol_index(const Symbol& symbol) {\n        int index = int(symbol) - FirstCharacter;\n\
    \        assert(0 <= index && index < AlphabetSize);\n        return index;\n\
    \    }\n\n    state_id new_state(int length) {\n        assert(_states.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _states.emplace_back(length);\n\
    \        return int(_states.size()) - 1;\n    }\n\n   public:\n    SuffixAutomaton()\
    \ {\n        clear();\n    }\n\n    template <class Sequence>\n    explicit SuffixAutomaton(const\
    \ Sequence& sequence) {\n        clear();\n        build(sequence);\n    }\n\n\
    \    int state_count() const {\n        return int(_states.size());\n    }\n\n\
    \    int size() const {\n        return state_count();\n    }\n\n    bool empty()\
    \ const {\n        return _text_length == 0;\n    }\n\n    int text_length() const\
    \ {\n        return _text_length;\n    }\n\n    state_id root() const {\n    \
    \    return root_state;\n    }\n\n    state_id last() const {\n        return\
    \ _last;\n    }\n\n    const State& state(state_id id) const {\n        assert(0\
    \ <= id && id < state_count());\n        return _states[id];\n    }\n\n    const\
    \ std::vector<State>& states() const {\n        return _states;\n    }\n\n   \
    \ int minimum_length(state_id id) const {\n        assert(0 <= id && id < state_count());\n\
    \        return id == root_state ? 0 : _states[_states[id].suffix_link].length\
    \ + 1;\n    }\n\n    template <class Symbol>\n    state_id transition(state_id\
    \ id, const Symbol& symbol) const {\n        assert(0 <= id && id < state_count());\n\
    \        return _states[id].next[symbol_index(symbol)];\n    }\n\n    void reserve(std::size_t\
    \ text_capacity) {\n        _states.reserve(2 * text_capacity);\n    }\n\n   \
    \ void clear() {\n        _states.clear();\n        _states.emplace_back();\n\
    \        _last = root_state;\n        _text_length = 0;\n    }\n\n    template\
    \ <class Symbol>\n    state_id add(const Symbol& value) {\n        int symbol\
    \ = symbol_index(value);\n        assert(_text_length < std::numeric_limits<int>::max());\n\
    \        _text_length++;\n\n        state_id current = new_state(_states[_last].length\
    \ + 1);\n        _states[current].first_end = _text_length;\n        _states[current].direct_occurrences\
    \ = 1;\n\n        state_id p = _last;\n        while (p != null_state && _states[p].next[symbol]\
    \ == null_state) {\n            _states[p].next[symbol] = current;\n         \
    \   p = _states[p].suffix_link;\n        }\n\n        if (p == null_state) {\n\
    \            _states[current].suffix_link = root_state;\n        } else {\n  \
    \          state_id q = _states[p].next[symbol];\n            if (_states[p].length\
    \ + 1 == _states[q].length) {\n                _states[current].suffix_link =\
    \ q;\n            } else {\n                state_id clone = new_state(_states[p].length\
    \ + 1);\n                _states[clone] = _states[q];\n                _states[clone].length\
    \ = _states[p].length + 1;\n                _states[clone].direct_occurrences\
    \ = 0;\n                _states[clone].clone = true;\n\n                while\
    \ (p != null_state && _states[p].next[symbol] == q) {\n                    _states[p].next[symbol]\
    \ = clone;\n                    p = _states[p].suffix_link;\n                }\n\
    \                _states[q].suffix_link = clone;\n                _states[current].suffix_link\
    \ = clone;\n            }\n        }\n\n        _last = current;\n        return\
    \ current;\n    }\n\n    template <class Sequence>\n    void build(const Sequence&\
    \ sequence) {\n        for (const auto& symbol : sequence) add(symbol);\n    }\n\
    \n    template <class Sequence>\n    state_id find(const Sequence& sequence) const\
    \ {\n        state_id current = root_state;\n        for (const auto& symbol :\
    \ sequence) {\n            current = transition(current, symbol);\n          \
    \  if (current == null_state) return null_state;\n        }\n        return current;\n\
    \    }\n\n    template <class Sequence>\n    bool contains(const Sequence& sequence)\
    \ const {\n        return find(sequence) != null_state;\n    }\n\n    std::vector<state_id>\
    \ length_order() const {\n        std::vector<int> count(_text_length + 1, 0);\n\
    \        for (const State& current : _states) count[current.length]++;\n     \
    \   for (int length = 1; length <= _text_length; length++) count[length] += count[length\
    \ - 1];\n\n        std::vector<state_id> order(state_count());\n        for (state_id\
    \ id = state_count() - 1; id >= 0; id--) {\n            order[--count[_states[id].length]]\
    \ = id;\n        }\n        return order;\n    }\n\n    std::vector<long long>\
    \ occurrence_counts() const {\n        std::vector<long long> result(state_count(),\
    \ 0);\n        for (state_id id = 0; id < state_count(); id++) {\n           \
    \ result[id] = _states[id].direct_occurrences;\n        }\n        std::vector<state_id>\
    \ order = length_order();\n        for (int i = int(order.size()) - 1; i > 0;\
    \ i--) {\n            state_id id = order[i];\n            result[_states[id].suffix_link]\
    \ += result[id];\n        }\n        return result;\n    }\n\n    std::vector<bool>\
    \ terminal_states() const {\n        std::vector<bool> result(state_count(), false);\n\
    \        for (state_id id = _last; id != null_state; id = _states[id].suffix_link)\
    \ {\n            result[id] = true;\n        }\n        return result;\n    }\n\
    \n    long long distinct_substring_count() const {\n        long long result =\
    \ 0;\n        for (state_id id = 1; id < state_count(); id++) {\n            result\
    \ += _states[id].length - _states[_states[id].suffix_link].length;\n        }\n\
    \        return result;\n    }\n\n    std::pair<int, int> longest_representative(state_id\
    \ id) const {\n        assert(0 <= id && id < state_count());\n        int end\
    \ = _states[id].first_end;\n        return {end - _states[id].length, end};\n\
    \    }\n\n    template <class Sequence>\n    std::pair<int, int> representative_occurrence(const\
    \ Sequence& sequence) const {\n        state_id id = root_state;\n        int\
    \ length = 0;\n        for (const auto& symbol : sequence) {\n            id =\
    \ transition(id, symbol);\n            if (id == null_state) return {-1, -1};\n\
    \            length++;\n        }\n        int end = _states[id].first_end;\n\
    \        return {end - length, end};\n    }\n\n    template <class Sequence>\n\
    \    std::pair<int, int> longest_common_substring(const Sequence& sequence) const\
    \ {\n        state_id current = root_state;\n        int current_length = 0;\n\
    \        int best_length = 0;\n        int best_end = 0;\n        int end = 0;\n\
    \n        for (const auto& value : sequence) {\n            int symbol = symbol_index(value);\n\
    \            while (current != root_state && _states[current].next[symbol] ==\
    \ null_state) {\n                current = _states[current].suffix_link;\n   \
    \             current_length = std::min(current_length, _states[current].length);\n\
    \            }\n            state_id next = _states[current].next[symbol];\n \
    \           if (next == null_state) {\n                current = root_state;\n\
    \                current_length = 0;\n            } else {\n                current\
    \ = next;\n                current_length++;\n            }\n            end++;\n\
    \            if (best_length < current_length) {\n                best_length\
    \ = current_length;\n                best_end = end;\n            }\n        }\n\
    \        return {best_end - best_length, best_end};\n    }\n};\n\n}  // namespace\
    \ string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/suffix_automaton.test.cpp\"\
    \n\n#line 7 \"verify/string/suffix_automaton.test.cpp\"\n#include <cstdint>\n\
    #include <iostream>\n#include <map>\n#include <set>\n#include <string>\n#line\
    \ 14 \"verify/string/suffix_automaton.test.cpp\"\n\nnamespace {\n\nvoid test_features()\
    \ {\n    using Automaton = m1une::string::SuffixAutomaton<>;\n    Automaton automaton;\n\
    \    automaton.reserve(16);\n    assert(automaton.empty());\n    assert(automaton.state_count()\
    \ == 1);\n    assert(automaton.root() == Automaton::root_state);\n    assert(automaton.last()\
    \ == automaton.root());\n\n    std::string text = \"ababa\";\n    for (char character\
    \ : text) automaton.add(character);\n    assert(!automaton.empty());\n    assert(automaton.text_length()\
    \ == 5);\n    assert(automaton.state(automaton.last()).length == 5);\n    assert(automaton.contains(std::string(\"\
    bab\")));\n    assert(!automaton.contains(std::string(\"abb\")));\n    assert(automaton.contains(std::string()));\n\
    \    assert(automaton.transition(automaton.root(), 'a') == automaton.find(std::string(\"\
    a\")));\n    assert(automaton.distinct_substring_count() == 9);\n\n    std::vector<long\
    \ long> count = automaton.occurrence_counts();\n    assert(count[automaton.root()]\
    \ == 5);\n    assert(count[automaton.find(std::string(\"a\"))] == 3);\n    assert(count[automaton.find(std::string(\"\
    b\"))] == 2);\n    assert(count[automaton.find(std::string(\"aba\"))] == 2);\n\
    \    assert(count[automaton.find(std::string(\"ababa\"))] == 1);\n\n    auto occurrence\
    \ = automaton.representative_occurrence(std::string(\"bab\"));\n    assert(text.substr(occurrence.first,\
    \ occurrence.second - occurrence.first) == \"bab\");\n    assert((automaton.representative_occurrence(std::string(\"\
    x\")) == std::pair<int, int>({-1, -1})));\n\n    std::vector<bool> terminal =\
    \ automaton.terminal_states();\n    assert(terminal[automaton.root()]);\n    for\
    \ (int length = 1; length <= int(text.size()); length++) {\n        int id = automaton.find(text.substr(text.size()\
    \ - length));\n        assert(terminal[id]);\n    }\n\n    std::string other =\
    \ \"zzbababx\";\n    auto common = automaton.longest_common_substring(other);\n\
    \    assert(other.substr(common.first, common.second - common.first) == \"baba\"\
    );\n\n    std::vector<int> order = automaton.length_order();\n    for (int i =\
    \ 1; i < int(order.size()); i++) {\n        assert(automaton.state(order[i - 1]).length\
    \ <= automaton.state(order[i]).length);\n    }\n\n    m1une::string::SuffixAutomaton<10,\
    \ '0'> digits(std::string(\"012012\"));\n    assert(digits.contains(std::string(\"\
    201\")));\n\n    automaton.clear();\n    assert(automaton.empty());\n    assert(automaton.state_count()\
    \ == 1);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 117;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 2000;\
    \ trial++) {\n        int n = int(random() % 55);\n        std::string text(n,\
    \ 'a');\n        for (char& character : text) character = char('a' + random()\
    \ % 4);\n        m1une::string::SuffixAutomaton<4, 'a'> automaton(text);\n\n \
    \       assert(automaton.state_count() <= std::max(1, 2 * n));\n        std::map<std::string,\
    \ int> expected_count;\n        for (int left = 0; left < n; left++) {\n     \
    \       for (int right = left + 1; right <= n; right++) {\n                expected_count[text.substr(left,\
    \ right - left)]++;\n            }\n        }\n        assert(automaton.distinct_substring_count()\
    \ == int(expected_count.size()));\n\n        std::vector<long long> occurrence\
    \ = automaton.occurrence_counts();\n        for (const auto& [substring, expected]\
    \ : expected_count) {\n            int id = automaton.find(substring);\n     \
    \       assert(id != automaton.null_state);\n            assert(occurrence[id]\
    \ == expected);\n            auto [left, right] = automaton.representative_occurrence(substring);\n\
    \            assert(text.substr(left, right - left) == substring);\n        }\n\
    \n        for (int id = 1; id < automaton.state_count(); id++) {\n           \
    \ const auto& current = automaton.state(id);\n            assert(0 <= current.suffix_link\
    \ && current.suffix_link < automaton.state_count());\n            assert(automaton.state(current.suffix_link).length\
    \ < current.length);\n            assert(automaton.minimum_length(id) == automaton.state(current.suffix_link).length\
    \ + 1);\n            auto [left, right] = automaton.longest_representative(id);\n\
    \            assert(0 <= left && left < right && right <= n);\n            std::string\
    \ represented = text.substr(left, right - left);\n            assert(int(represented.size())\
    \ == current.length);\n            assert(automaton.find(represented) == id);\n\
    \        }\n\n        std::vector<bool> expected_terminal(automaton.state_count(),\
    \ false);\n        expected_terminal[automaton.root()] = true;\n        for (int\
    \ left = 0; left < n; left++) {\n            expected_terminal[automaton.find(text.substr(left))]\
    \ = true;\n        }\n        assert(automaton.terminal_states() == expected_terminal);\n\
    \n        int m = int(random() % 55);\n        std::string query(m, 'a');\n  \
    \      for (char& character : query) character = char('a' + random() % 4);\n \
    \       int expected_lcs = 0;\n        for (int left = 0; left < m; left++) {\n\
    \            for (int right = left + 1; right <= m; right++) {\n             \
    \   if (automaton.contains(query.substr(left, right - left))) {\n            \
    \        expected_lcs = std::max(expected_lcs, right - left);\n              \
    \  }\n            }\n        }\n        auto [left, right] = automaton.longest_common_substring(query);\n\
    \        assert(right - left == expected_lcs);\n        assert(automaton.contains(query.substr(left,\
    \ right - left)));\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_features();\n\
    \    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string text;\n    std::cin >> text;\n    m1une::string::SuffixAutomaton<>\
    \ automaton(text);\n    std::cout << automaton.distinct_substring_count() << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/number_of_substrings\"\n\
    \n#include \"../../string/suffix_automaton.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <iostream>\n#include <map>\n#include\
    \ <set>\n#include <string>\n#include <utility>\n#include <vector>\n\nnamespace\
    \ {\n\nvoid test_features() {\n    using Automaton = m1une::string::SuffixAutomaton<>;\n\
    \    Automaton automaton;\n    automaton.reserve(16);\n    assert(automaton.empty());\n\
    \    assert(automaton.state_count() == 1);\n    assert(automaton.root() == Automaton::root_state);\n\
    \    assert(automaton.last() == automaton.root());\n\n    std::string text = \"\
    ababa\";\n    for (char character : text) automaton.add(character);\n    assert(!automaton.empty());\n\
    \    assert(automaton.text_length() == 5);\n    assert(automaton.state(automaton.last()).length\
    \ == 5);\n    assert(automaton.contains(std::string(\"bab\")));\n    assert(!automaton.contains(std::string(\"\
    abb\")));\n    assert(automaton.contains(std::string()));\n    assert(automaton.transition(automaton.root(),\
    \ 'a') == automaton.find(std::string(\"a\")));\n    assert(automaton.distinct_substring_count()\
    \ == 9);\n\n    std::vector<long long> count = automaton.occurrence_counts();\n\
    \    assert(count[automaton.root()] == 5);\n    assert(count[automaton.find(std::string(\"\
    a\"))] == 3);\n    assert(count[automaton.find(std::string(\"b\"))] == 2);\n \
    \   assert(count[automaton.find(std::string(\"aba\"))] == 2);\n    assert(count[automaton.find(std::string(\"\
    ababa\"))] == 1);\n\n    auto occurrence = automaton.representative_occurrence(std::string(\"\
    bab\"));\n    assert(text.substr(occurrence.first, occurrence.second - occurrence.first)\
    \ == \"bab\");\n    assert((automaton.representative_occurrence(std::string(\"\
    x\")) == std::pair<int, int>({-1, -1})));\n\n    std::vector<bool> terminal =\
    \ automaton.terminal_states();\n    assert(terminal[automaton.root()]);\n    for\
    \ (int length = 1; length <= int(text.size()); length++) {\n        int id = automaton.find(text.substr(text.size()\
    \ - length));\n        assert(terminal[id]);\n    }\n\n    std::string other =\
    \ \"zzbababx\";\n    auto common = automaton.longest_common_substring(other);\n\
    \    assert(other.substr(common.first, common.second - common.first) == \"baba\"\
    );\n\n    std::vector<int> order = automaton.length_order();\n    for (int i =\
    \ 1; i < int(order.size()); i++) {\n        assert(automaton.state(order[i - 1]).length\
    \ <= automaton.state(order[i]).length);\n    }\n\n    m1une::string::SuffixAutomaton<10,\
    \ '0'> digits(std::string(\"012012\"));\n    assert(digits.contains(std::string(\"\
    201\")));\n\n    automaton.clear();\n    assert(automaton.empty());\n    assert(automaton.state_count()\
    \ == 1);\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 117;\n    auto\
    \ random = [&state]() {\n        state ^= state << 7;\n        state ^= state\
    \ >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial < 2000;\
    \ trial++) {\n        int n = int(random() % 55);\n        std::string text(n,\
    \ 'a');\n        for (char& character : text) character = char('a' + random()\
    \ % 4);\n        m1une::string::SuffixAutomaton<4, 'a'> automaton(text);\n\n \
    \       assert(automaton.state_count() <= std::max(1, 2 * n));\n        std::map<std::string,\
    \ int> expected_count;\n        for (int left = 0; left < n; left++) {\n     \
    \       for (int right = left + 1; right <= n; right++) {\n                expected_count[text.substr(left,\
    \ right - left)]++;\n            }\n        }\n        assert(automaton.distinct_substring_count()\
    \ == int(expected_count.size()));\n\n        std::vector<long long> occurrence\
    \ = automaton.occurrence_counts();\n        for (const auto& [substring, expected]\
    \ : expected_count) {\n            int id = automaton.find(substring);\n     \
    \       assert(id != automaton.null_state);\n            assert(occurrence[id]\
    \ == expected);\n            auto [left, right] = automaton.representative_occurrence(substring);\n\
    \            assert(text.substr(left, right - left) == substring);\n        }\n\
    \n        for (int id = 1; id < automaton.state_count(); id++) {\n           \
    \ const auto& current = automaton.state(id);\n            assert(0 <= current.suffix_link\
    \ && current.suffix_link < automaton.state_count());\n            assert(automaton.state(current.suffix_link).length\
    \ < current.length);\n            assert(automaton.minimum_length(id) == automaton.state(current.suffix_link).length\
    \ + 1);\n            auto [left, right] = automaton.longest_representative(id);\n\
    \            assert(0 <= left && left < right && right <= n);\n            std::string\
    \ represented = text.substr(left, right - left);\n            assert(int(represented.size())\
    \ == current.length);\n            assert(automaton.find(represented) == id);\n\
    \        }\n\n        std::vector<bool> expected_terminal(automaton.state_count(),\
    \ false);\n        expected_terminal[automaton.root()] = true;\n        for (int\
    \ left = 0; left < n; left++) {\n            expected_terminal[automaton.find(text.substr(left))]\
    \ = true;\n        }\n        assert(automaton.terminal_states() == expected_terminal);\n\
    \n        int m = int(random() % 55);\n        std::string query(m, 'a');\n  \
    \      for (char& character : query) character = char('a' + random() % 4);\n \
    \       int expected_lcs = 0;\n        for (int left = 0; left < m; left++) {\n\
    \            for (int right = left + 1; right <= m; right++) {\n             \
    \   if (automaton.contains(query.substr(left, right - left))) {\n            \
    \        expected_lcs = std::max(expected_lcs, right - left);\n              \
    \  }\n            }\n        }\n        auto [left, right] = automaton.longest_common_substring(query);\n\
    \        assert(right - left == expected_lcs);\n        assert(automaton.contains(query.substr(left,\
    \ right - left)));\n    }\n}\n\n}  // namespace\n\nint main() {\n    test_features();\n\
    \    test_randomized();\n\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \n    std::string text;\n    std::cin >> text;\n    m1une::string::SuffixAutomaton<>\
    \ automaton(text);\n    std::cout << automaton.distinct_substring_count() << '\\\
    n';\n}\n"
  dependsOn:
  - string/suffix_automaton.hpp
  isVerificationFile: true
  path: verify/string/suffix_automaton.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 03:13:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/suffix_automaton.test.cpp
layout: document
redirect_from:
- /verify/verify/string/suffix_automaton.test.cpp
- /verify/verify/string/suffix_automaton.test.cpp.html
title: verify/string/suffix_automaton.test.cpp
---
