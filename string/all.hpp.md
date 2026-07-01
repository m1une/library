---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/aho_corasick.hpp
    title: Aho-Corasick
  - icon: ':heavy_check_mark:'
    path: string/eertree.hpp
    title: Eertree
  - icon: ':heavy_check_mark:'
    path: string/levenshtein_distance.hpp
    title: Levenshtein Distance
  - icon: ':heavy_check_mark:'
    path: string/manacher.hpp
    title: Manacher Algorithm
  - icon: ':heavy_check_mark:'
    path: string/prefix_function.hpp
    title: Prefix Function and KMP
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.hpp
    title: Static Rolling Hash
  - icon: ':heavy_check_mark:'
    path: string/string_hash.hpp
    title: String Hash
  - icon: ':heavy_check_mark:'
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  - icon: ':heavy_check_mark:'
    path: string/suffix_automaton.hpp
    title: Suffix Automaton
  - icon: ':heavy_check_mark:'
    path: string/trie.hpp
    title: Trie
  - icon: ':heavy_check_mark:'
    path: string/z_algorithm.hpp
    title: Z Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/all.hpp\"\n\n\n\n#line 1 \"string/aho_corasick.hpp\"\
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
    \ m1une\n\n\n#line 1 \"string/eertree.hpp\"\n\n\n\n#line 8 \"string/eertree.hpp\"\
    \n#include <utility>\n#line 10 \"string/eertree.hpp\"\n\nnamespace m1une {\nnamespace\
    \ string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct\
    \ Eertree {\n    static_assert(0 < AlphabetSize);\n\n    using node_id = int;\n\
    \    static constexpr node_id even_root = 0;\n    static constexpr node_id odd_root\
    \ = 1;\n    static constexpr node_id null_node = -1;\n\n    struct Node {\n  \
    \      std::array<node_id, AlphabetSize> next;\n        node_id suffix_link;\n\
    \        node_id series_link;\n        int length;\n        int diff;\n      \
    \  int suffix_count;\n        int first_end;\n        long long suffix_occurrences;\n\
    \n        Node(int length_value = 0, node_id suffix_link_value = even_root, node_id\
    \ series_link_value = even_root)\n            : suffix_link(suffix_link_value),\n\
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
    \ string\n}  // namespace m1une\n\n\n#line 1 \"string/levenshtein_distance.hpp\"\
    \n\n\n\n#include <algorithm>\n#line 7 \"string/levenshtein_distance.hpp\"\n\n\
    namespace m1une {\nnamespace string {\n\nnamespace levenshtein_distance_detail\
    \ {\n\ntemplate <class RowSequence, class ColumnSequence>\nint solve(const RowSequence&\
    \ rows, const ColumnSequence& columns) {\n    int row_count = int(rows.size());\n\
    \    int column_count = int(columns.size());\n    std::vector<int> distance(column_count\
    \ + 1);\n    for (int column = 0; column <= column_count; column++) distance[column]\
    \ = column;\n\n    for (int row = 1; row <= row_count; row++) {\n        int diagonal\
    \ = distance[0];\n        distance[0] = row;\n        for (int column = 1; column\
    \ <= column_count; column++) {\n            int above = distance[column];\n  \
    \          int substitution = diagonal + (rows[row - 1] == columns[column - 1]\
    \ ? 0 : 1);\n            distance[column] =\n                std::min({above +\
    \ 1, distance[column - 1] + 1, substitution});\n            diagonal = above;\n\
    \        }\n    }\n    return distance[column_count];\n}\n\ntemplate <class RowSequence,\
    \ class ColumnSequence>\nint solve_bounded(const RowSequence& rows, const ColumnSequence&\
    \ columns,\n                  int max_distance) {\n    int row_count = int(rows.size());\n\
    \    int column_count = int(columns.size());\n    assert(column_count <= row_count);\n\
    \    if (row_count - column_count > max_distance) return max_distance + 1;\n \
    \   if (max_distance >= row_count) return solve(rows, columns);\n\n    int infinity\
    \ = max_distance + 1;\n    int previous_left = 0;\n    int previous_right = std::min(column_count,\
    \ max_distance);\n    std::vector<int> previous(previous_right + 1);\n    for\
    \ (int column = 0; column <= previous_right; column++) previous[column] = column;\n\
    \    std::vector<int> current;\n\n    for (int row = 1; row <= row_count; row++)\
    \ {\n        int current_left = std::max(0, row - max_distance);\n        int\
    \ current_right = int(std::min<long long>(column_count,\n                    \
    \                                static_cast<long long>(row) + max_distance));\n\
    \        current.assign(current_right - current_left + 1, infinity);\n\n     \
    \   for (int column = current_left; column <= current_right; column++) {\n   \
    \         int best = infinity;\n            if (previous_left <= column && column\
    \ <= previous_right) {\n                best = std::min(best, previous[column\
    \ - previous_left] + 1);\n            }\n            if (current_left < column)\
    \ {\n                best = std::min(best, current[column - current_left - 1]\
    \ + 1);\n            }\n            if (0 < column && previous_left <= column\
    \ - 1 && column - 1 <= previous_right) {\n                int substitution = previous[column\
    \ - 1 - previous_left] +\n                                   (rows[row - 1] ==\
    \ columns[column - 1] ? 0 : 1);\n                best = std::min(best, substitution);\n\
    \            }\n            current[column - current_left] = std::min(best, infinity);\n\
    \        }\n\n        previous.swap(current);\n        previous_left = current_left;\n\
    \        previous_right = current_right;\n    }\n    return previous[column_count\
    \ - previous_left];\n}\n\n}  // namespace levenshtein_distance_detail\n\n// Returns\
    \ the minimum number of insertions, deletions, and substitutions\n// needed to\
    \ transform first into second.\ntemplate <class Sequence1, class Sequence2>\n\
    int levenshtein_distance(const Sequence1& first, const Sequence2& second) {\n\
    \    if (first.size() < second.size()) {\n        return levenshtein_distance_detail::solve(second,\
    \ first);\n    }\n    return levenshtein_distance_detail::solve(first, second);\n\
    }\n\n// Returns the exact distance when it is at most max_distance, and\n// max_distance\
    \ + 1 otherwise.\ntemplate <class Sequence1, class Sequence2>\nint levenshtein_distance(const\
    \ Sequence1& first, const Sequence2& second,\n                         int max_distance)\
    \ {\n    assert(0 <= max_distance);\n    if (first.size() < second.size()) {\n\
    \        return levenshtein_distance_detail::solve_bounded(second, first, max_distance);\n\
    \    }\n    return levenshtein_distance_detail::solve_bounded(first, second, max_distance);\n\
    }\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 1 \"string/manacher.hpp\"\
    \n\n\n\n#line 7 \"string/manacher.hpp\"\n\nnamespace m1une {\nnamespace string\
    \ {\n\nstruct ManacherResult {\n    // odd[i] is the radius including center i.\n\
    \    // The palindrome is [i - odd[i] + 1, i + odd[i]).\n    std::vector<int>\
    \ odd;\n\n    // even[i] is the radius centered between i - 1 and i.\n    // The\
    \ palindrome is [i - even[i], i + even[i]).\n    std::vector<int> even;\n\n  \
    \  int size() const {\n        return int(odd.size());\n    }\n\n    bool empty()\
    \ const {\n        return odd.empty();\n    }\n\n    bool is_palindrome(int left,\
    \ int right) const {\n        int n = size();\n        assert(0 <= left && left\
    \ <= right && right <= n);\n        int length = right - left;\n        if (length\
    \ == 0) return true;\n        if (length & 1) {\n            int center = (left\
    \ + right) / 2;\n            return length / 2 + 1 <= odd[center];\n        }\n\
    \        int center = (left + right) / 2;\n        return length / 2 <= even[center];\n\
    \    }\n\n    int longest_length() const {\n        int result = 0;\n        for\
    \ (int radius : odd) result = std::max(result, 2 * radius - 1);\n        for (int\
    \ radius : even) result = std::max(result, 2 * radius);\n        return result;\n\
    \    }\n};\n\ntemplate <class Sequence>\nManacherResult manacher(const Sequence&\
    \ sequence) {\n    int n = int(sequence.size());\n    ManacherResult result;\n\
    \    result.odd.assign(n, 0);\n    result.even.assign(n, 0);\n\n    int left =\
    \ 0;\n    int right = -1;\n    for (int i = 0; i < n; i++) {\n        int radius\
    \ = i > right ? 1 : std::min(result.odd[left + right - i], right - i + 1);\n \
    \       while (\n            0 <= i - radius &&\n            i + radius < n &&\n\
    \            sequence[i - radius] == sequence[i + radius]\n        ) {\n     \
    \       radius++;\n        }\n        result.odd[i] = radius;\n        if (right\
    \ < i + radius - 1) {\n            left = i - radius + 1;\n            right =\
    \ i + radius - 1;\n        }\n    }\n\n    left = 0;\n    right = -1;\n    for\
    \ (int i = 0; i < n; i++) {\n        int radius = i > right ? 0 : std::min(result.even[left\
    \ + right - i + 1], right - i + 1);\n        while (\n            0 <= i - radius\
    \ - 1 &&\n            i + radius < n &&\n            sequence[i - radius - 1]\
    \ == sequence[i + radius]\n        ) {\n            radius++;\n        }\n   \
    \     result.even[i] = radius;\n        if (right < i + radius - 1) {\n      \
    \      left = i - radius;\n            right = i + radius - 1;\n        }\n  \
    \  }\n    return result;\n}\n\n}  // namespace string\n}  // namespace m1une\n\
    \n\n#line 1 \"string/prefix_function.hpp\"\n\n\n\n#line 5 \"string/prefix_function.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\n// Returns the KMP prefix function.\n\
    template <class Sequence>\nstd::vector<int> prefix_function(const Sequence& sequence)\
    \ {\n    int n = int(sequence.size());\n    std::vector<int> prefix(n);\n    for\
    \ (int i = 1; i < n; i++) {\n        int j = prefix[i - 1];\n        while (j\
    \ > 0 && sequence[i] != sequence[j]) {\n            j = prefix[j - 1];\n     \
    \   }\n        if (sequence[i] == sequence[j]) j++;\n        prefix[i] = j;\n\
    \    }\n    return prefix;\n}\n\n// Returns every starting position where pattern\
    \ occurs in text.\n// An empty pattern occurs at every position from 0 through\
    \ text.size().\ntemplate <class Text, class Pattern>\nstd::vector<int> kmp_search(const\
    \ Text& text, const Pattern& pattern) {\n    int n = int(text.size());\n    int\
    \ m = int(pattern.size());\n    if (m == 0) {\n        std::vector<int> occurrences(n\
    \ + 1);\n        for (int i = 0; i <= n; i++) occurrences[i] = i;\n        return\
    \ occurrences;\n    }\n\n    std::vector<int> prefix = prefix_function(pattern);\n\
    \    std::vector<int> occurrences;\n    int matched = 0;\n    for (int i = 0;\
    \ i < n; i++) {\n        while (matched > 0 && text[i] != pattern[matched]) {\n\
    \            matched = prefix[matched - 1];\n        }\n        if (text[i] ==\
    \ pattern[matched]) matched++;\n        if (matched == m) {\n            occurrences.push_back(i\
    \ - m + 1);\n            matched = prefix[matched - 1];\n        }\n    }\n  \
    \  return occurrences;\n}\n\n}  // namespace string\n}  // namespace m1une\n\n\
    \n#line 1 \"string/rolling_hash.hpp\"\n\n\n\n#line 5 \"string/rolling_hash.hpp\"\
    \n#include <string>\n#line 8 \"string/rolling_hash.hpp\"\n\nnamespace m1une {\n\
    namespace string {\n\n// Standard Rolling Hash for static strings.\n// Precomputes\
    \ hashes to answer substring queries in O(1).\n// Provides advanced operations\
    \ like LCP, lexicographical comparison, and string repetition in O(log N).\ntemplate\
    \ <long long Base = 10007, long long Mod = (1LL << 61) - 1>\nstruct RollingHash\
    \ {\n    std::string s;\n    std::vector<long long> hash;\n    std::vector<long\
    \ long> power;\n\n    RollingHash() = default;\n\n    // Constructs the rolling\
    \ hash table for the given string.\n    explicit RollingHash(const std::string&\
    \ str) : s(str) {\n        int n = s.size();\n        hash.assign(n + 1, 0);\n\
    \        power.assign(n + 1, 1);\n        for (int i = 0; i < n; ++i) {\n    \
    \        // Use __int128_t to prevent overflow during multiplication\n       \
    \     hash[i + 1] = (static_cast<__int128_t>(hash[i]) * Base + s[i]) % Mod;\n\
    \            power[i + 1] = (static_cast<__int128_t>(power[i]) * Base) % Mod;\n\
    \        }\n    }\n\n    // Returns the hash of the substring S[l..r) in O(1).\n\
    \    long long get(int l, int r) const {\n        long long res = hash[r] - (static_cast<__int128_t>(hash[l])\
    \ * power[r - l]) % Mod;\n        if (res < 0) res += Mod;\n        return res;\n\
    \    }\n\n    // Returns the hash of the concatenated substrings S[l1..r1) and\
    \ S[l2..r2).\n    long long concat(int l1, int r1, int l2, int r2) const {\n \
    \       long long h1 = get(l1, r1);\n        long long h2 = get(l2, r2);\n   \
    \     return combine(h1, h2, power[r2 - l2]);\n    }\n\n    // Calculates the\
    \ Longest Common Prefix (LCP) length of S[l1..r1) and S[l2..r2) in O(log N).\n\
    \    int lcp(int l1, int r1, int l2, int r2) const {\n        int len = std::min(r1\
    \ - l1, r2 - l2);\n        int low = 0, high = len + 1;\n        while (high -\
    \ low > 1) {\n            int mid = low + (high - low) / 2;\n            if (get(l1,\
    \ l1 + mid) == get(l2, l2 + mid)) {\n                low = mid;\n            }\
    \ else {\n                high = mid;\n            }\n        }\n        return\
    \ low;\n    }\n\n    // Lexicographically compares S[l1..r1) and S[l2..r2) in\
    \ O(log N).\n    // Returns -1 if S[l1..r1) < S[l2..r2), 0 if equal, and 1 if\
    \ S[l1..r1) > S[l2..r2).\n    int compare(int l1, int r1, int l2, int r2) const\
    \ {\n        int l = lcp(l1, r1, l2, r2);\n        bool end1 = (l1 + l == r1);\n\
    \        bool end2 = (l2 + l == r2);\n        if (end1 && end2) return 0;\n  \
    \      if (end1) return -1;\n        if (end2) return 1;\n        return s[l1\
    \ + l] < s[l2 + l] ? -1 : 1;\n    }\n\n    // Returns the hash of the substring\
    \ S[l..r) repeated 'k' times.\n    long long repeat(int l, int r, long long k)\
    \ const {\n        long long h = get(l, r);\n        long long p = power[r - l];\n\
    \        return repeat_hash(h, p, k);\n    }\n\n    // --- Static Helpers for\
    \ dynamic processing and Monoid integration ---\n\n    // Computes the hash of\
    \ a single string in O(N) time and O(1) space.\n    static long long compute_hash(const\
    \ std::string& str) {\n        long long h = 0;\n        for (char c : str) {\n\
    \            h = (static_cast<__int128_t>(h) * Base + c) % Mod;\n        }\n \
    \       return h;\n    }\n\n    // Combines two hashes. Equivalent to concatenating\
    \ string 'b' to the right of string 'a'.\n    static constexpr long long combine(long\
    \ long h1, long long h2, long long base_power2) {\n        return (static_cast<__int128_t>(h1)\
    \ * base_power2 + h2) % Mod;\n    }\n\n    // Returns the hash of a string (with\
    \ hash 'h' and base_power 'p') repeated 'k' times.\n    static constexpr long\
    \ long repeat_hash(long long h, long long p, long long k) {\n        long long\
    \ res_h = 0;\n        long long res_p = 1;\n        long long cur_h = h;\n   \
    \     long long cur_p = p;\n        while (k > 0) {\n            if (k & 1) {\n\
    \                res_h = combine(res_h, cur_h, cur_p);\n                res_p\
    \ = (static_cast<__int128_t>(res_p) * cur_p) % Mod;\n            }\n         \
    \   cur_h = combine(cur_h, cur_h, cur_p);\n            cur_p = (static_cast<__int128_t>(cur_p)\
    \ * cur_p) % Mod;\n            k >>= 1;\n        }\n        return res_h;\n  \
    \  }\n\n    // Creates the state pair {hash_value, base_power} for a single character.\n\
    \    static constexpr std::pair<long long, long long> make_single(long long c)\
    \ {\n        return {c % Mod, Base % Mod};\n    }\n};\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 1 \"string/string_hash.hpp\"\n\n\n\n#line 5 \"\
    string/string_hash.hpp\"\n#include <cstdint>\n#line 7 \"string/string_hash.hpp\"\
    \n#include <string_view>\n\nnamespace m1une {\nnamespace string {\n\nstruct StringHash\
    \ {\n    std::uint32_t first;\n    std::uint32_t second;\n    std::uint32_t first_power;\n\
    \    std::uint32_t second_power;\n    std::size_t length;\n\n    friend constexpr\
    \ bool operator==(const StringHash& left, const StringHash& right) {\n       \
    \ return left.length == right.length && left.first == right.first && left.second\
    \ == right.second;\n    }\n};\n\nnamespace string_hash_detail {\n\ninline constexpr\
    \ std::uint64_t first_mod = 1'000'000'007;\ninline constexpr std::uint64_t second_mod\
    \ = 1'000'000'009;\ninline constexpr std::uint64_t base = 911'382'323;\n\n}  //\
    \ namespace string_hash_detail\n\n// Computes a double polynomial hash. Bytes\
    \ are interpreted as unsigned.\nconstexpr StringHash hash_string(std::string_view\
    \ value) {\n    using namespace string_hash_detail;\n    std::uint64_t first =\
    \ 0;\n    std::uint64_t second = 0;\n    std::uint64_t first_power = 1;\n    std::uint64_t\
    \ second_power = 1;\n    for (char character : value) {\n        std::uint64_t\
    \ symbol = static_cast<unsigned char>(character) + std::uint64_t(1);\n       \
    \ first = (first * base + symbol) % first_mod;\n        second = (second * base\
    \ + symbol) % second_mod;\n        first_power = first_power * base % first_mod;\n\
    \        second_power = second_power * base % second_mod;\n    }\n    return StringHash{\n\
    \        static_cast<std::uint32_t>(first),\n        static_cast<std::uint32_t>(second),\n\
    \        static_cast<std::uint32_t>(first_power),\n        static_cast<std::uint32_t>(second_power),\n\
    \        value.size(),\n    };\n}\n\nconstexpr StringHash hash_string(const std::string&\
    \ value) {\n    return hash_string(std::string_view(value));\n}\n\nconstexpr StringHash\
    \ hash_string(const char* value) {\n    return hash_string(std::string_view(value));\n\
    }\n\n// Returns the hash of the concatenation represented by `left` and `right`.\n\
    constexpr StringHash concat_string_hash(const StringHash& left, const StringHash&\
    \ right) {\n    using namespace string_hash_detail;\n    return StringHash{\n\
    \        static_cast<std::uint32_t>((std::uint64_t(left.first) * right.first_power\
    \ + right.first) % first_mod),\n        static_cast<std::uint32_t>((std::uint64_t(left.second)\
    \ * right.second_power + right.second) % second_mod),\n        static_cast<std::uint32_t>(std::uint64_t(left.first_power)\
    \ * right.first_power % first_mod),\n        static_cast<std::uint32_t>(std::uint64_t(left.second_power)\
    \ * right.second_power % second_mod),\n        left.length + right.length,\n \
    \   };\n}\n\n// Hash adapter for std::unordered_map and std::unordered_set.\n\
    struct StringHasher {\n    using is_transparent = void;\n\n    constexpr std::size_t\
    \ operator()(std::string_view value) const {\n        return operator()(hash_string(value));\n\
    \    }\n\n    constexpr std::size_t operator()(const std::string& value) const\
    \ {\n        return operator()(std::string_view(value));\n    }\n\n    constexpr\
    \ std::size_t operator()(const char* value) const {\n        return operator()(std::string_view(value));\n\
    \    }\n\n    constexpr std::size_t operator()(const StringHash& value) const\
    \ {\n        std::uint64_t combined = (std::uint64_t(value.first) << 32) | value.second;\n\
    \        combined ^= std::uint64_t(value.length) + 0x9e3779b97f4a7c15ULL;\n  \
    \      combined ^= combined >> 30;\n        combined *= 0xbf58476d1ce4e5b9ULL;\n\
    \        combined ^= combined >> 27;\n        combined *= 0x94d049bb133111ebULL;\n\
    \        combined ^= combined >> 31;\n        return static_cast<std::size_t>(combined);\n\
    \    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 1 \"string/suffix_automaton.hpp\"\
    \n\n\n\n#line 11 \"string/suffix_automaton.hpp\"\n\nnamespace m1une {\nnamespace\
    \ string {\n\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\nstruct\
    \ SuffixAutomaton {\n    static_assert(0 < AlphabetSize);\n\n    using state_id\
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
    \ string\n}  // namespace m1une\n\n\n#line 1 \"string/suffix_array.hpp\"\n\n\n\
    \n#line 6 \"string/suffix_array.hpp\"\n#include <numeric>\n#line 8 \"string/suffix_array.hpp\"\
    \n#include <type_traits>\n#line 10 \"string/suffix_array.hpp\"\n\nnamespace m1une\
    \ {\nnamespace string {\nnamespace detail {\n\ntemplate <class Sequence>\nstd::vector<int>\
    \ suffix_array_impl(const Sequence& sequence) {\n    int n = int(sequence.size());\n\
    \    if (n == 0) return {};\n\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n\
    \    std::vector<Value> sorted(sequence.begin(), sequence.end());\n    std::sort(sorted.begin(),\
    \ sorted.end());\n    sorted.erase(std::unique(sorted.begin(), sorted.end()),\
    \ sorted.end());\n\n    int length = n + 1;\n    std::vector<int> order(length);\n\
    \    std::vector<int> rank(length);\n    std::vector<int> key(length);\n    key[n]\
    \ = 0;\n    for (int i = 0; i < n; i++) {\n        key[i] = int(std::lower_bound(sorted.begin(),\
    \ sorted.end(), sequence[i]) - sorted.begin()) + 1;\n    }\n\n    int alphabet\
    \ = int(sorted.size()) + 1;\n    std::vector<int> count(std::max(length, alphabet),\
    \ 0);\n    for (int value : key) count[value]++;\n    for (int i = 1; i < alphabet;\
    \ i++) count[i] += count[i - 1];\n    for (int i = length - 1; i >= 0; i--) order[--count[key[i]]]\
    \ = i;\n\n    int classes = 1;\n    rank[order[0]] = 0;\n    for (int i = 1; i\
    \ < length; i++) {\n        if (key[order[i - 1]] != key[order[i]]) classes++;\n\
    \        rank[order[i]] = classes - 1;\n    }\n\n    std::vector<int> shifted(length);\n\
    \    std::vector<int> next_rank(length);\n    for (long long half = 1; half <\
    \ length; half <<= 1) {\n        for (int i = 0; i < length; i++) {\n        \
    \    long long position = order[i] - half;\n            if (position < 0) position\
    \ += length;\n            shifted[i] = int(position);\n        }\n\n        count.assign(classes,\
    \ 0);\n        for (int position : shifted) count[rank[position]]++;\n       \
    \ for (int i = 1; i < classes; i++) count[i] += count[i - 1];\n        for (int\
    \ i = length - 1; i >= 0; i--) {\n            int position = shifted[i];\n   \
    \         order[--count[rank[position]]] = position;\n        }\n\n        int\
    \ next_classes = 1;\n        next_rank[order[0]] = 0;\n        for (int i = 1;\
    \ i < length; i++) {\n            int current = order[i];\n            int previous\
    \ = order[i - 1];\n            int current_second = int((current + half) % length);\n\
    \            int previous_second = int((previous + half) % length);\n        \
    \    if (\n                rank[current] != rank[previous] ||\n              \
    \  rank[current_second] != rank[previous_second]\n            ) {\n          \
    \      next_classes++;\n            }\n            next_rank[current] = next_classes\
    \ - 1;\n        }\n        rank.swap(next_rank);\n        classes = next_classes;\n\
    \        if (classes == length) break;\n    }\n\n    std::vector<int> suffixes(n);\n\
    \    for (int i = 0; i < n; i++) suffixes[i] = order[i + 1];\n    return suffixes;\n\
    }\n\n}  // namespace detail\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array(const\
    \ Sequence& sequence) {\n    return detail::suffix_array_impl(sequence);\n}\n\n\
    inline std::vector<int> suffix_array(const std::string& text) {\n    std::vector<unsigned\
    \ char> values;\n    values.reserve(text.size());\n    for (unsigned char character\
    \ : text) values.push_back(character);\n    return detail::suffix_array_impl(values);\n\
    }\n\ntemplate <class Sequence>\nstd::vector<int> lcp_array(const Sequence& sequence,\
    \ const std::vector<int>& suffixes) {\n    int n = int(sequence.size());\n   \
    \ assert(int(suffixes.size()) == n);\n    if (n == 0) return {};\n\n    std::vector<int>\
    \ rank(n);\n    for (int i = 0; i < n; i++) {\n        assert(0 <= suffixes[i]\
    \ && suffixes[i] < n);\n        rank[suffixes[i]] = i;\n    }\n\n    std::vector<int>\
    \ lcp(n - 1);\n    int common = 0;\n    for (int i = 0; i < n; i++) {\n      \
    \  int position = rank[i];\n        if (position == n - 1) {\n            common\
    \ = 0;\n            continue;\n        }\n        int j = suffixes[position +\
    \ 1];\n        while (\n            i + common < n &&\n            j + common\
    \ < n &&\n            sequence[i + common] == sequence[j + common]\n        )\
    \ {\n            common++;\n        }\n        lcp[position] = common;\n     \
    \   if (common > 0) common--;\n    }\n    return lcp;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 1 \"string/trie.hpp\"\n\n\n\n#line 9 \"string/trie.hpp\"\
    \n\nnamespace m1une {\nnamespace string {\n\n// A multiset trie for a contiguous\
    \ character alphabet.\ntemplate <int AlphabetSize = 26, int FirstCharacter = 'a'>\n\
    struct Trie {\n    static_assert(0 < AlphabetSize);\n\n    using node_id = int;\n\
    \    static constexpr node_id null_node = -1;\n\n    struct Node {\n        std::array<node_id,\
    \ AlphabetSize> child;\n        int subtree_count;\n        int terminal_count;\n\
    \n        Node() : subtree_count(0), terminal_count(0) {\n            child.fill(null_node);\n\
    \        }\n    };\n\n   private:\n    std::vector<Node> _nodes;\n    int _distinct_size;\n\
    \n    template <class Symbol>\n    static int symbol_index(const Symbol& symbol)\
    \ {\n        int index = int(symbol) - FirstCharacter;\n        assert(0 <= index\
    \ && index < AlphabetSize);\n        return index;\n    }\n\n    node_id new_node()\
    \ {\n        assert(_nodes.size() < std::size_t(std::numeric_limits<int>::max()));\n\
    \        _nodes.emplace_back();\n        return int(_nodes.size()) - 1;\n    }\n\
    \n    template <class Sequence>\n    node_id find_node(const Sequence& sequence)\
    \ const {\n        node_id node = 0;\n        for (const auto& symbol : sequence)\
    \ {\n            node = _nodes[node].child[symbol_index(symbol)];\n          \
    \  if (node == null_node || _nodes[node].subtree_count == 0) {\n             \
    \   return null_node;\n            }\n        }\n        return node;\n    }\n\
    \n   public:\n    Trie() : _nodes(1), _distinct_size(0) {}\n\n    int size() const\
    \ {\n        return _nodes[0].subtree_count;\n    }\n\n    int distinct_size()\
    \ const {\n        return _distinct_size;\n    }\n\n    bool empty() const {\n\
    \        return size() == 0;\n    }\n\n    node_id root() const {\n        return\
    \ 0;\n    }\n\n    const Node& node(node_id id) const {\n        assert(0 <= id\
    \ && std::size_t(id) < _nodes.size());\n        return _nodes[id];\n    }\n\n\
    \    template <class Sequence>\n    node_id find(const Sequence& sequence) const\
    \ {\n        return find_node(sequence);\n    }\n\n    std::size_t node_count()\
    \ const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
    \ node_capacity) {\n        _nodes.reserve(node_capacity);\n    }\n\n    void\
    \ clear() {\n        _nodes.clear();\n        _nodes.emplace_back();\n       \
    \ _distinct_size = 0;\n    }\n\n    template <class Sequence>\n    node_id insert(const\
    \ Sequence& sequence, int multiplicity = 1) {\n        assert(0 < multiplicity);\n\
    \        node_id node = 0;\n        _nodes[node].subtree_count += multiplicity;\n\
    \        for (const auto& symbol : sequence) {\n            int index = symbol_index(symbol);\n\
    \            node_id child = _nodes[node].child[index];\n            if (child\
    \ == null_node) {\n                child = new_node();\n                _nodes[node].child[index]\
    \ = child;\n            }\n            node = child;\n            _nodes[node].subtree_count\
    \ += multiplicity;\n        }\n        if (_nodes[node].terminal_count == 0) _distinct_size++;\n\
    \        _nodes[node].terminal_count += multiplicity;\n        return node;\n\
    \    }\n\n    template <class Sequence>\n    int count(const Sequence& sequence)\
    \ const {\n        node_id node = find_node(sequence);\n        return node ==\
    \ null_node ? 0 : _nodes[node].terminal_count;\n    }\n\n    template <class Sequence>\n\
    \    bool contains(const Sequence& sequence) const {\n        return count(sequence)\
    \ != 0;\n    }\n\n    // Returns the number of stored strings beginning with prefix.\n\
    \    template <class Sequence>\n    int prefix_count(const Sequence& prefix) const\
    \ {\n        node_id node = find_node(prefix);\n        return node == null_node\
    \ ? 0 : _nodes[node].subtree_count;\n    }\n\n    template <class Sequence>\n\
    \    bool starts_with(const Sequence& prefix) const {\n        return prefix_count(prefix)\
    \ != 0;\n    }\n\n    template <class Sequence>\n    bool erase_one(const Sequence&\
    \ sequence) {\n        node_id terminal = find_node(sequence);\n        if (terminal\
    \ == null_node || _nodes[terminal].terminal_count == 0) {\n            return\
    \ false;\n        }\n\n        int node = 0;\n        _nodes[node].subtree_count--;\n\
    \        for (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
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
    \ == null_node || _nodes[node].subtree_count == 0) return;\n            length++;\n\
    \            if (_nodes[node].terminal_count != 0) {\n                callback(length,\
    \ _nodes[node].terminal_count);\n            }\n        }\n    }\n\n    // Returns\
    \ the length of the longest stored string that is a prefix.\n    // Returns -1\
    \ when no stored prefix exists.\n    template <class Sequence>\n    int longest_prefix(const\
    \ Sequence& sequence) const {\n        int result = _nodes[0].terminal_count ==\
    \ 0 ? -1 : 0;\n        for_each_prefix(sequence, [&result](int length, int) {\n\
    \            result = length;\n        });\n        return result;\n    }\n};\n\
    \n}  // namespace string\n}  // namespace m1une\n\n\n#line 1 \"string/z_algorithm.hpp\"\
    \n\n\n\n#line 6 \"string/z_algorithm.hpp\"\n\nnamespace m1une {\nnamespace string\
    \ {\n\n// Returns z[i] = LCP(sequence, sequence[i..]).\ntemplate <class Sequence>\n\
    std::vector<int> z_algorithm(const Sequence& sequence) {\n    int n = int(sequence.size());\n\
    \    if (n == 0) return {};\n\n    std::vector<int> z(n);\n    z[0] = n;\n   \
    \ int left = 0;\n    int right = 0;\n    for (int i = 1; i < n; i++) {\n     \
    \   if (i < right) z[i] = std::min(right - i, z[i - left]);\n        while (i\
    \ + z[i] < n && sequence[z[i]] == sequence[i + z[i]]) {\n            z[i]++;\n\
    \        }\n        if (right < i + z[i]) {\n            left = i;\n         \
    \   right = i + z[i];\n        }\n    }\n    return z;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 15 \"string/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_STRING_ALL_HPP

    #define M1UNE_STRING_ALL_HPP 1


    #include "aho_corasick.hpp"

    #include "eertree.hpp"

    #include "levenshtein_distance.hpp"

    #include "manacher.hpp"

    #include "prefix_function.hpp"

    #include "rolling_hash.hpp"

    #include "string_hash.hpp"

    #include "suffix_automaton.hpp"

    #include "suffix_array.hpp"

    #include "trie.hpp"

    #include "z_algorithm.hpp"


    #endif  // M1UNE_STRING_ALL_HPP

    '
  dependsOn:
  - string/aho_corasick.hpp
  - string/eertree.hpp
  - string/levenshtein_distance.hpp
  - string/manacher.hpp
  - string/prefix_function.hpp
  - string/rolling_hash.hpp
  - string/string_hash.hpp
  - string/suffix_automaton.hpp
  - string/suffix_array.hpp
  - string/trie.hpp
  - string/z_algorithm.hpp
  isVerificationFile: false
  path: string/all.hpp
  requiredBy: []
  timestamp: '2026-07-01 21:56:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_algorithms.test.cpp
documentation_of: string/all.hpp
layout: document
title: String Algorithms Bundle
---

## Overview

`string/all.hpp` includes the reusable string algorithms in this repository.
Use individual headers when compile time matters, or this bundle during a
contest when convenience matters more.

## Included Headers

| Header | Contents |
| --- | --- |
| `string/aho_corasick.hpp` | Multi-pattern matching with failure links and occurrence counting. |
| `string/eertree.hpp` | Online palindromic tree with suffix and series links. |
| `string/levenshtein_distance.hpp` | Unit-cost edit distance in linear auxiliary memory. |
| `string/z_algorithm.hpp` | Linear-time Z array. |
| `string/prefix_function.hpp` | Prefix function and KMP occurrence search. |
| `string/manacher.hpp` | Odd/even palindrome radii and substring checks. |
| `string/suffix_automaton.hpp` | Online suffix automaton for substring queries and occurrence classes. |
| `string/suffix_array.hpp` | Suffix array and LCP array. |
| `string/trie.hpp` | Contiguous-alphabet multiset trie with prefix queries. |
| `string/rolling_hash.hpp` | Static substring hashing, LCP, and comparison. |
| `string/string_hash.hpp` | Double whole-string hashing and constant-time hash concatenation. |
