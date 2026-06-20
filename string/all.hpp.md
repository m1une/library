---
data:
  _extendedDependsOn:
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
    path: string/suffix_array.hpp
    title: Suffix Array and LCP Array
  - icon: ':question:'
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
  bundledCode: "#line 1 \"string/all.hpp\"\n\n\n\n#line 1 \"string/manacher.hpp\"\n\
    \n\n\n#include <algorithm>\n#include <cassert>\n#include <vector>\n\nnamespace\
    \ m1une {\nnamespace string {\n\nstruct ManacherResult {\n    // odd[i] is the\
    \ radius including center i.\n    // The palindrome is [i - odd[i] + 1, i + odd[i]).\n\
    \    std::vector<int> odd;\n\n    // even[i] is the radius centered between i\
    \ - 1 and i.\n    // The palindrome is [i - even[i], i + even[i]).\n    std::vector<int>\
    \ even;\n\n    int size() const {\n        return int(odd.size());\n    }\n\n\
    \    bool empty() const {\n        return odd.empty();\n    }\n\n    bool is_palindrome(int\
    \ left, int right) const {\n        int n = size();\n        assert(0 <= left\
    \ && left <= right && right <= n);\n        int length = right - left;\n     \
    \   if (length == 0) return true;\n        if (length & 1) {\n            int\
    \ center = (left + right) / 2;\n            return length / 2 + 1 <= odd[center];\n\
    \        }\n        int center = (left + right) / 2;\n        return length /\
    \ 2 <= even[center];\n    }\n\n    int longest_length() const {\n        int result\
    \ = 0;\n        for (int radius : odd) result = std::max(result, 2 * radius -\
    \ 1);\n        for (int radius : even) result = std::max(result, 2 * radius);\n\
    \        return result;\n    }\n};\n\ntemplate <class Sequence>\nManacherResult\
    \ manacher(const Sequence& sequence) {\n    int n = int(sequence.size());\n  \
    \  ManacherResult result;\n    result.odd.assign(n, 0);\n    result.even.assign(n,\
    \ 0);\n\n    int left = 0;\n    int right = -1;\n    for (int i = 0; i < n; i++)\
    \ {\n        int radius = i > right ? 1 : std::min(result.odd[left + right - i],\
    \ right - i + 1);\n        while (\n            0 <= i - radius &&\n         \
    \   i + radius < n &&\n            sequence[i - radius] == sequence[i + radius]\n\
    \        ) {\n            radius++;\n        }\n        result.odd[i] = radius;\n\
    \        if (right < i + radius - 1) {\n            left = i - radius + 1;\n \
    \           right = i + radius - 1;\n        }\n    }\n\n    left = 0;\n    right\
    \ = -1;\n    for (int i = 0; i < n; i++) {\n        int radius = i > right ? 0\
    \ : std::min(result.even[left + right - i + 1], right - i + 1);\n        while\
    \ (\n            0 <= i - radius - 1 &&\n            i + radius < n &&\n     \
    \       sequence[i - radius - 1] == sequence[i + radius]\n        ) {\n      \
    \      radius++;\n        }\n        result.even[i] = radius;\n        if (right\
    \ < i + radius - 1) {\n            left = i - radius;\n            right = i +\
    \ radius - 1;\n        }\n    }\n    return result;\n}\n\n}  // namespace string\n\
    }  // namespace m1une\n\n\n#line 1 \"string/prefix_function.hpp\"\n\n\n\n#line\
    \ 5 \"string/prefix_function.hpp\"\n\nnamespace m1une {\nnamespace string {\n\n\
    // Returns the KMP prefix function.\ntemplate <class Sequence>\nstd::vector<int>\
    \ prefix_function(const Sequence& sequence) {\n    int n = int(sequence.size());\n\
    \    std::vector<int> prefix(n);\n    for (int i = 1; i < n; i++) {\n        int\
    \ j = prefix[i - 1];\n        while (j > 0 && sequence[i] != sequence[j]) {\n\
    \            j = prefix[j - 1];\n        }\n        if (sequence[i] == sequence[j])\
    \ j++;\n        prefix[i] = j;\n    }\n    return prefix;\n}\n\n// Returns every\
    \ starting position where pattern occurs in text.\n// An empty pattern occurs\
    \ at every position from 0 through text.size().\ntemplate <class Text, class Pattern>\n\
    std::vector<int> kmp_search(const Text& text, const Pattern& pattern) {\n    int\
    \ n = int(text.size());\n    int m = int(pattern.size());\n    if (m == 0) {\n\
    \        std::vector<int> occurrences(n + 1);\n        for (int i = 0; i <= n;\
    \ i++) occurrences[i] = i;\n        return occurrences;\n    }\n\n    std::vector<int>\
    \ prefix = prefix_function(pattern);\n    std::vector<int> occurrences;\n    int\
    \ matched = 0;\n    for (int i = 0; i < n; i++) {\n        while (matched > 0\
    \ && text[i] != pattern[matched]) {\n            matched = prefix[matched - 1];\n\
    \        }\n        if (text[i] == pattern[matched]) matched++;\n        if (matched\
    \ == m) {\n            occurrences.push_back(i - m + 1);\n            matched\
    \ = prefix[matched - 1];\n        }\n    }\n    return occurrences;\n}\n\n}  //\
    \ namespace string\n}  // namespace m1une\n\n\n#line 1 \"string/rolling_hash.hpp\"\
    \n\n\n\n#line 5 \"string/rolling_hash.hpp\"\n#include <string>\n#include <utility>\n\
    #line 8 \"string/rolling_hash.hpp\"\n\nnamespace m1une {\nnamespace string {\n\
    \n// Standard Rolling Hash for static strings.\n// Precomputes hashes to answer\
    \ substring queries in O(1).\n// Provides advanced operations like LCP, lexicographical\
    \ comparison, and string repetition in O(log N).\ntemplate <long long Base = 10007,\
    \ long long Mod = (1LL << 61) - 1>\nstruct RollingHash {\n    std::string s;\n\
    \    std::vector<long long> hash;\n    std::vector<long long> power;\n\n    RollingHash()\
    \ = default;\n\n    // Constructs the rolling hash table for the given string.\n\
    \    explicit RollingHash(const std::string& str) : s(str) {\n        int n =\
    \ s.size();\n        hash.assign(n + 1, 0);\n        power.assign(n + 1, 1);\n\
    \        for (int i = 0; i < n; ++i) {\n            // Use __int128_t to prevent\
    \ overflow during multiplication\n            hash[i + 1] = (static_cast<__int128_t>(hash[i])\
    \ * Base + s[i]) % Mod;\n            power[i + 1] = (static_cast<__int128_t>(power[i])\
    \ * Base) % Mod;\n        }\n    }\n\n    // Returns the hash of the substring\
    \ S[l..r) in O(1).\n    long long get(int l, int r) const {\n        long long\
    \ res = hash[r] - (static_cast<__int128_t>(hash[l]) * power[r - l]) % Mod;\n \
    \       if (res < 0) res += Mod;\n        return res;\n    }\n\n    // Returns\
    \ the hash of the concatenated substrings S[l1..r1) and S[l2..r2).\n    long long\
    \ concat(int l1, int r1, int l2, int r2) const {\n        long long h1 = get(l1,\
    \ r1);\n        long long h2 = get(l2, r2);\n        return combine(h1, h2, power[r2\
    \ - l2]);\n    }\n\n    // Calculates the Longest Common Prefix (LCP) length of\
    \ S[l1..r1) and S[l2..r2) in O(log N).\n    int lcp(int l1, int r1, int l2, int\
    \ r2) const {\n        int len = std::min(r1 - l1, r2 - l2);\n        int low\
    \ = 0, high = len + 1;\n        while (high - low > 1) {\n            int mid\
    \ = low + (high - low) / 2;\n            if (get(l1, l1 + mid) == get(l2, l2 +\
    \ mid)) {\n                low = mid;\n            } else {\n                high\
    \ = mid;\n            }\n        }\n        return low;\n    }\n\n    // Lexicographically\
    \ compares S[l1..r1) and S[l2..r2) in O(log N).\n    // Returns -1 if S[l1..r1)\
    \ < S[l2..r2), 0 if equal, and 1 if S[l1..r1) > S[l2..r2).\n    int compare(int\
    \ l1, int r1, int l2, int r2) const {\n        int l = lcp(l1, r1, l2, r2);\n\
    \        bool end1 = (l1 + l == r1);\n        bool end2 = (l2 + l == r2);\n  \
    \      if (end1 && end2) return 0;\n        if (end1) return -1;\n        if (end2)\
    \ return 1;\n        return s[l1 + l] < s[l2 + l] ? -1 : 1;\n    }\n\n    // Returns\
    \ the hash of the substring S[l..r) repeated 'k' times.\n    long long repeat(int\
    \ l, int r, long long k) const {\n        long long h = get(l, r);\n        long\
    \ long p = power[r - l];\n        return repeat_hash(h, p, k);\n    }\n\n    //\
    \ --- Static Helpers for dynamic processing and Monoid integration ---\n\n   \
    \ // Computes the hash of a single string in O(N) time and O(1) space.\n    static\
    \ long long compute_hash(const std::string& str) {\n        long long h = 0;\n\
    \        for (char c : str) {\n            h = (static_cast<__int128_t>(h) * Base\
    \ + c) % Mod;\n        }\n        return h;\n    }\n\n    // Combines two hashes.\
    \ Equivalent to concatenating string 'b' to the right of string 'a'.\n    static\
    \ constexpr long long combine(long long h1, long long h2, long long base_power2)\
    \ {\n        return (static_cast<__int128_t>(h1) * base_power2 + h2) % Mod;\n\
    \    }\n\n    // Returns the hash of a string (with hash 'h' and base_power 'p')\
    \ repeated 'k' times.\n    static constexpr long long repeat_hash(long long h,\
    \ long long p, long long k) {\n        long long res_h = 0;\n        long long\
    \ res_p = 1;\n        long long cur_h = h;\n        long long cur_p = p;\n   \
    \     while (k > 0) {\n            if (k & 1) {\n                res_h = combine(res_h,\
    \ cur_h, cur_p);\n                res_p = (static_cast<__int128_t>(res_p) * cur_p)\
    \ % Mod;\n            }\n            cur_h = combine(cur_h, cur_h, cur_p);\n \
    \           cur_p = (static_cast<__int128_t>(cur_p) * cur_p) % Mod;\n        \
    \    k >>= 1;\n        }\n        return res_h;\n    }\n\n    // Creates the state\
    \ pair {hash_value, base_power} for a single character.\n    static constexpr\
    \ std::pair<long long, long long> make_single(long long c) {\n        return {c\
    \ % Mod, Base % Mod};\n    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\
    \n\n#line 1 \"string/suffix_array.hpp\"\n\n\n\n#line 6 \"string/suffix_array.hpp\"\
    \n#include <numeric>\n#line 8 \"string/suffix_array.hpp\"\n#include <type_traits>\n\
    #line 10 \"string/suffix_array.hpp\"\n\nnamespace m1une {\nnamespace string {\n\
    namespace detail {\n\ntemplate <class Sequence>\nstd::vector<int> suffix_array_impl(const\
    \ Sequence& sequence) {\n    int n = int(sequence.size());\n    if (n == 0) return\
    \ {};\n\n    using Value = std::remove_cv_t<std::remove_reference_t<decltype(sequence[0])>>;\n\
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
    }  // namespace m1une\n\n\n#line 1 \"string/trie.hpp\"\n\n\n\n#include <array>\n\
    #line 6 \"string/trie.hpp\"\n#include <cstddef>\n#include <limits>\n#line 9 \"\
    string/trie.hpp\"\n\nnamespace m1une {\nnamespace string {\n\n// A multiset trie\
    \ for a contiguous character alphabet.\ntemplate <int AlphabetSize = 26, int FirstCharacter\
    \ = 'a'>\nstruct Trie {\n    static_assert(0 < AlphabetSize);\n\n   private:\n\
    \    struct Node {\n        std::array<int, AlphabetSize> child;\n        int\
    \ subtree_count;\n        int terminal_count;\n\n        Node() : subtree_count(0),\
    \ terminal_count(0) {\n            child.fill(-1);\n        }\n    };\n\n    std::vector<Node>\
    \ _nodes;\n    int _distinct_size;\n\n    template <class Symbol>\n    static\
    \ int symbol_index(const Symbol& symbol) {\n        int index = int(symbol) -\
    \ FirstCharacter;\n        assert(0 <= index && index < AlphabetSize);\n     \
    \   return index;\n    }\n\n    int new_node() {\n        assert(_nodes.size()\
    \ < std::size_t(std::numeric_limits<int>::max()));\n        _nodes.emplace_back();\n\
    \        return int(_nodes.size()) - 1;\n    }\n\n    template <class Sequence>\n\
    \    int find_node(const Sequence& sequence) const {\n        int node = 0;\n\
    \        for (const auto& symbol : sequence) {\n            node = _nodes[node].child[symbol_index(symbol)];\n\
    \            if (node == -1 || _nodes[node].subtree_count == 0) return -1;\n \
    \       }\n        return node;\n    }\n\n   public:\n    Trie() : _nodes(1),\
    \ _distinct_size(0) {}\n\n    int size() const {\n        return _nodes[0].subtree_count;\n\
    \    }\n\n    int distinct_size() const {\n        return _distinct_size;\n  \
    \  }\n\n    bool empty() const {\n        return size() == 0;\n    }\n\n    std::size_t\
    \ node_count() const {\n        return _nodes.size();\n    }\n\n    void reserve(std::size_t\
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
    }  // namespace m1une\n\n\n#line 10 \"string/all.hpp\"\n\n\n"
  code: '#ifndef M1UNE_STRING_ALL_HPP

    #define M1UNE_STRING_ALL_HPP 1


    #include "string/manacher.hpp"

    #include "string/prefix_function.hpp"

    #include "string/rolling_hash.hpp"

    #include "string/suffix_array.hpp"

    #include "string/trie.hpp"

    #include "string/z_algorithm.hpp"


    #endif  // M1UNE_STRING_ALL_HPP

    '
  dependsOn:
  - string/manacher.hpp
  - string/prefix_function.hpp
  - string/rolling_hash.hpp
  - string/suffix_array.hpp
  - string/trie.hpp
  - string/z_algorithm.hpp
  isVerificationFile: false
  path: string/all.hpp
  requiredBy: []
  timestamp: '2026-06-21 02:49:46+09:00'
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
| `string/z_algorithm.hpp` | Linear-time Z array. |
| `string/prefix_function.hpp` | Prefix function and KMP occurrence search. |
| `string/manacher.hpp` | Odd/even palindrome radii and substring checks. |
| `string/suffix_array.hpp` | Suffix array and LCP array. |
| `string/trie.hpp` | Contiguous-alphabet multiset trie with prefix queries. |
| `string/rolling_hash.hpp` | Static substring hashing, LCP, and comparison. |
