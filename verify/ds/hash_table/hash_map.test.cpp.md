---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/hash_table/hash_common.hpp
    title: ds/hash_table/hash_common.hpp
  - icon: ':heavy_check_mark:'
    path: ds/hash_table/hash_map.hpp
    title: Hash Map
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/associative_array
    links:
    - https://judge.yosupo.jp/problem/associative_array
  bundledCode: "#line 1 \"verify/ds/hash_table/hash_map.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/associative_array\"\n\n#line 1 \"ds/hash_table/hash_map.hpp\"\
    \n\n\n\n#line 1 \"ds/hash_table/hash_common.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <chrono>\n#include <cstddef>\n#include <cstdint>\n#include <new>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace ds {\nnamespace\
    \ detail {\n\ninline std::uint64_t splitmix64(std::uint64_t x) {\n    x += 0x9e3779b97f4a7c15;\n\
    \    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n\
    \    return x ^ (x >> 31);\n}\n\ntemplate <typename Key, typename Hash>\nstd::size_t\
    \ mixed_hash(const Key& key, const Hash& hash) {\n    static const std::uint64_t\
    \ fixed_random =\n        std::chrono::steady_clock::now().time_since_epoch().count();\n\
    \    return static_cast<std::size_t>(splitmix64(static_cast<std::uint64_t>(hash(key))\
    \ + fixed_random));\n}\n\ninline std::size_t bit_ceil(std::size_t n) {\n    std::size_t\
    \ result = 1;\n    while (result < n) result <<= 1;\n    return result;\n}\n\n\
    inline std::size_t bucket_count_for(std::size_t expected_size) {\n    return bit_ceil(std::max<std::size_t>(16,\
    \ expected_size * 10 / 7 + 1));\n}\n\ntemplate <typename T>\nstruct Slot {\n \
    \   alignas(T) unsigned char storage[sizeof(T)];\n\n    T* ptr() {\n        return\
    \ std::launder(reinterpret_cast<T*>(storage));\n    }\n\n    const T* ptr() const\
    \ {\n        return std::launder(reinterpret_cast<const T*>(storage));\n    }\n\
    \n    template <typename... Args>\n    void construct(Args&&... args) {\n    \
    \    ::new (static_cast<void*>(storage)) T(std::forward<Args>(args)...);\n   \
    \ }\n\n    void destroy() {\n        if constexpr (!std::is_trivially_destructible_v<T>)\
    \ {\n            ptr()->~T();\n        }\n    }\n};\n\n}  // namespace detail\n\
    }  // namespace ds\n}  // namespace m1une\n\n\n#line 5 \"ds/hash_table/hash_map.hpp\"\
    \n\n#line 8 \"ds/hash_table/hash_map.hpp\"\n#include <functional>\n#include <initializer_list>\n\
    #include <stdexcept>\n#line 12 \"ds/hash_table/hash_map.hpp\"\n#include <vector>\n\
    \nnamespace m1une {\nnamespace ds {\n\ntemplate <typename Key, typename T, typename\
    \ Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>\nstruct HashMap\
    \ {\n   private:\n    struct Node {\n        Key key;\n        T value;\n\n  \
    \      template <typename K, typename V>\n        Node(K&& node_key, V&& node_value)\
    \ : key(std::forward<K>(node_key)), value(std::forward<V>(node_value)) {}\n  \
    \  };\n\n    static constexpr unsigned char EMPTY = 0;\n    static constexpr unsigned\
    \ char DELETED = 1;\n    static constexpr std::size_t npos = static_cast<std::size_t>(-1);\n\
    \n    std::vector<unsigned char> ctrl;\n    std::vector<detail::Slot<Node>> data;\n\
    \    std::size_t _size = 0;\n    std::size_t _deleted = 0;\n    Hash hasher;\n\
    \    KeyEqual key_equal;\n\n    std::size_t mask() const {\n        return ctrl.size()\
    \ - 1;\n    }\n\n    std::size_t make_hash(const Key& key) const {\n        return\
    \ detail::mixed_hash(key, hasher);\n    }\n\n    static unsigned char fingerprint(std::size_t\
    \ h) {\n        return static_cast<unsigned char>(2 + (h >> (sizeof(std::size_t)\
    \ * 8 - 7)));\n    }\n\n    static bool occupied(unsigned char c) {\n        return\
    \ c >= 2;\n    }\n\n    Node* node_at(std::size_t i) {\n        return data[i].ptr();\n\
    \    }\n\n    const Node* node_at(std::size_t i) const {\n        return data[i].ptr();\n\
    \    }\n\n    void destroy_all() {\n        for (std::size_t i = 0; i < ctrl.size();\
    \ i++) {\n            if (occupied(ctrl[i])) data[i].destroy();\n        }\n \
    \   }\n\n    void reset(std::size_t bucket_count) {\n        destroy_all();\n\
    \        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));\n\
    \        ctrl.assign(bucket_count, EMPTY);\n        data.clear();\n        data.resize(bucket_count);\n\
    \        _size = 0;\n        _deleted = 0;\n    }\n\n    std::size_t find_index_with_hash(const\
    \ Key& key, std::size_t h) const {\n        const unsigned char fp = fingerprint(h);\n\
    \        std::size_t i = h & mask();\n        while (true) {\n            const\
    \ unsigned char c = ctrl[i];\n            if (c == EMPTY) return npos;\n     \
    \       if (c == fp && key_equal(node_at(i)->key, key)) return i;\n          \
    \  i = (i + 1) & mask();\n        }\n    }\n\n    std::size_t find_index(const\
    \ Key& key) const {\n        return find_index_with_hash(key, make_hash(key));\n\
    \    }\n\n    void insert_existing(Node&& node, std::size_t h) {\n        std::size_t\
    \ i = h & mask();\n        while (occupied(ctrl[i])) i = (i + 1) & mask();\n \
    \       ctrl[i] = fingerprint(h);\n        data[i].construct(std::move(node));\n\
    \        _size++;\n    }\n\n    void rebuild(std::size_t bucket_count) {\n   \
    \     std::vector<unsigned char> old_ctrl = std::move(ctrl);\n        std::vector<detail::Slot<Node>>\
    \ old_data = std::move(data);\n\n        ctrl.clear();\n        data.clear();\n\
    \        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));\n\
    \        ctrl.assign(bucket_count, EMPTY);\n        data.resize(bucket_count);\n\
    \        _size = 0;\n        _deleted = 0;\n\n        for (std::size_t i = 0;\
    \ i < old_ctrl.size(); i++) {\n            if (occupied(old_ctrl[i])) {\n    \
    \            Node* node = old_data[i].ptr();\n                insert_existing(std::move(*node),\
    \ make_hash(node->key));\n                old_data[i].destroy();\n           \
    \ }\n        }\n    }\n\n    void ensure_for_insert() {\n        const std::size_t\
    \ used = _size + _deleted;\n        if ((used + 1) * 10 >= ctrl.size() * 7) {\n\
    \            rebuild(ctrl.size() * 2);\n        } else if (_deleted > _size &&\
    \ (_size + 1) * 10 < ctrl.size() * 7) {\n            rebuild(ctrl.size());\n \
    \       }\n    }\n\n    template <typename K, typename V>\n    std::pair<T*, bool>\
    \ insert_impl(K&& key, V&& value) {\n        ensure_for_insert();\n\n        const\
    \ std::size_t h = make_hash(key);\n        const unsigned char fp = fingerprint(h);\n\
    \        std::size_t first_deleted = npos;\n        std::size_t i = h & mask();\n\
    \        while (true) {\n            const unsigned char c = ctrl[i];\n      \
    \      if (occupied(c)) {\n                Node* node = node_at(i);\n        \
    \        if (c == fp && key_equal(node->key, key)) return {&node->value, false};\n\
    \            } else if (c == DELETED) {\n                if (first_deleted ==\
    \ npos) first_deleted = i;\n            } else {\n                const std::size_t\
    \ pos = first_deleted == npos ? i : first_deleted;\n                if (first_deleted\
    \ != npos) _deleted--;\n                ctrl[pos] = fp;\n                data[pos].construct(std::forward<K>(key),\
    \ std::forward<V>(value));\n                _size++;\n                return {&node_at(pos)->value,\
    \ true};\n            }\n            i = (i + 1) & mask();\n        }\n    }\n\
    \n   public:\n    HashMap() : hasher(Hash()), key_equal(KeyEqual()) {\n      \
    \  reset(16);\n    }\n\n    explicit HashMap(std::size_t reserve_count, Hash hash_fn\
    \ = Hash(), KeyEqual equal_fn = KeyEqual())\n        : hasher(std::move(hash_fn)),\
    \ key_equal(std::move(equal_fn)) {\n        reset(detail::bucket_count_for(reserve_count));\n\
    \    }\n\n    HashMap(std::initializer_list<std::pair<Key, T>> init, Hash hash_fn\
    \ = Hash(), KeyEqual equal_fn = KeyEqual())\n        : HashMap(init.size(), std::move(hash_fn),\
    \ std::move(equal_fn)) {\n        for (const auto& [key, value] : init) insert(key,\
    \ value);\n    }\n\n    template <typename Iterator>\n    HashMap(Iterator first,\
    \ Iterator last, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())\n    \
    \    : HashMap(0, std::move(hash_fn), std::move(equal_fn)) {\n        while (first\
    \ != last) {\n            insert(first->first, first->second);\n            ++first;\n\
    \        }\n    }\n\n    HashMap(const HashMap& other) : hasher(other.hasher),\
    \ key_equal(other.key_equal) {\n        ctrl.assign(other.ctrl.size(), EMPTY);\n\
    \        data.resize(other.data.size());\n        for (std::size_t i = 0; i <\
    \ other.ctrl.size(); i++) {\n            ctrl[i] = other.ctrl[i];\n          \
    \  if (occupied(other.ctrl[i])) data[i].construct(other.node_at(i)->key, other.node_at(i)->value);\n\
    \        }\n        _size = other._size;\n        _deleted = other._deleted;\n\
    \    }\n\n    HashMap(HashMap&& other) noexcept\n        : ctrl(std::move(other.ctrl)),\n\
    \          data(std::move(other.data)),\n          _size(other._size),\n     \
    \     _deleted(other._deleted),\n          hasher(std::move(other.hasher)),\n\
    \          key_equal(std::move(other.key_equal)) {\n        other.ctrl.clear();\n\
    \        other.data.clear();\n        other._size = 0;\n        other._deleted\
    \ = 0;\n    }\n\n    HashMap& operator=(const HashMap& other) {\n        if (this\
    \ == &other) return *this;\n        HashMap copy(other);\n        *this = std::move(copy);\n\
    \        return *this;\n    }\n\n    HashMap& operator=(HashMap&& other) noexcept\
    \ {\n        if (this == &other) return *this;\n        destroy_all();\n     \
    \   ctrl = std::move(other.ctrl);\n        data = std::move(other.data);\n   \
    \     _size = other._size;\n        _deleted = other._deleted;\n        hasher\
    \ = std::move(other.hasher);\n        key_equal = std::move(other.key_equal);\n\
    \        other.ctrl.clear();\n        other.data.clear();\n        other._size\
    \ = 0;\n        other._deleted = 0;\n        return *this;\n    }\n\n    ~HashMap()\
    \ {\n        destroy_all();\n    }\n\n    int size() const {\n        return static_cast<int>(_size);\n\
    \    }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\n    std::size_t\
    \ bucket_count() const {\n        return ctrl.size();\n    }\n\n    double load_factor()\
    \ const {\n        return static_cast<double>(_size) / static_cast<double>(ctrl.size());\n\
    \    }\n\n    void clear() {\n        reset(ctrl.size());\n    }\n\n    void reserve(std::size_t\
    \ count) {\n        const std::size_t target = detail::bucket_count_for(count);\n\
    \        if (target > ctrl.size() || _deleted > 0) rebuild(std::max(target, ctrl.size()));\n\
    \    }\n\n    std::pair<T*, bool> insert(const Key& key, const T& value) {\n \
    \       return insert_impl(key, value);\n    }\n\n    std::pair<T*, bool> insert(Key&&\
    \ key, T&& value) {\n        return insert_impl(std::move(key), std::move(value));\n\
    \    }\n\n    std::pair<T*, bool> insert(const std::pair<Key, T>& value) {\n \
    \       return insert_impl(value.first, value.second);\n    }\n\n    std::pair<T*,\
    \ bool> insert(std::pair<Key, T>&& value) {\n        return insert_impl(std::move(value.first),\
    \ std::move(value.second));\n    }\n\n    template <typename V>\n    T* insert_or_assign(const\
    \ Key& key, V&& value) {\n        auto result = insert_impl(key, std::forward<V>(value));\n\
    \        if (!result.second) *result.first = std::forward<V>(value);\n       \
    \ return result.first;\n    }\n\n    template <typename V>\n    T* insert_or_assign(Key&&\
    \ key, V&& value) {\n        auto result = insert_impl(std::move(key), std::forward<V>(value));\n\
    \        if (!result.second) *result.first = std::forward<V>(value);\n       \
    \ return result.first;\n    }\n\n    bool erase(const Key& key) {\n        const\
    \ std::size_t h = make_hash(key);\n        const std::size_t i = find_index_with_hash(key,\
    \ h);\n        if (i == npos) return false;\n        data[i].destroy();\n    \
    \    ctrl[i] = DELETED;\n        _size--;\n        _deleted++;\n        return\
    \ true;\n    }\n\n    T* find(const Key& key) {\n        const std::size_t i =\
    \ find_index(key);\n        return i == npos ? nullptr : &node_at(i)->value;\n\
    \    }\n\n    const T* find(const Key& key) const {\n        const std::size_t\
    \ i = find_index(key);\n        return i == npos ? nullptr : &node_at(i)->value;\n\
    \    }\n\n    bool contains(const Key& key) const {\n        return find_index(key)\
    \ != npos;\n    }\n\n    int count(const Key& key) const {\n        return contains(key)\
    \ ? 1 : 0;\n    }\n\n    T& at(const Key& key) {\n        T* p = find(key);\n\
    \        if (p == nullptr) throw std::out_of_range(\"HashMap::at\");\n       \
    \ return *p;\n    }\n\n    const T& at(const Key& key) const {\n        const\
    \ T* p = find(key);\n        if (p == nullptr) throw std::out_of_range(\"HashMap::at\"\
    );\n        return *p;\n    }\n\n    T& operator[](const Key& key) {\n       \
    \ return *insert_impl(key, T()).first;\n    }\n\n    T& operator[](Key&& key)\
    \ {\n        return *insert_impl(std::move(key), T()).first;\n    }\n\n    std::vector<std::pair<Key,\
    \ T>> to_vector() const {\n        std::vector<std::pair<Key, T>> result;\n  \
    \      result.reserve(_size);\n        for (std::size_t i = 0; i < ctrl.size();\
    \ i++) {\n            if (occupied(ctrl[i])) result.emplace_back(node_at(i)->key,\
    \ node_at(i)->value);\n        }\n        return result;\n    }\n};\n\n}  // namespace\
    \ ds\n}  // namespace m1une\n\n\n#line 4 \"verify/ds/hash_table/hash_map.test.cpp\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <string>\n#include <unordered_map>\n\
    \nvoid self_test() {\n    m1une::ds::HashMap<long long, std::string> mp;\n   \
    \ assert(mp.empty());\n    auto inserted = mp.insert(5, std::string(\"five\"));\n\
    \    assert(inserted.second);\n    assert(*inserted.first == \"five\");\n    assert(!mp.insert(5,\
    \ std::string(\"ignored\")).second);\n    assert(mp.insert({6, \"six\"}).second);\n\
    \    assert(mp.at(6) == \"six\");\n    assert(mp.at(5) == \"five\");\n\n    mp[7]\
    \ = \"seven\";\n    mp.insert_or_assign(5, \"FIVE\");\n    assert(mp.at(5) ==\
    \ \"FIVE\");\n    assert(mp.contains(7));\n    assert(mp.erase(7));\n    assert(!mp.contains(7));\n\
    \n    m1une::ds::HashMap<long long, int> large;\n    large.reserve(1000);\n  \
    \  for (int i = 0; i < 1000; i++) large[i * 1000000007LL] = i;\n    for (int i\
    \ = 0; i < 1000; i++) assert(large.at(i * 1000000007LL) == i);\n    for (int i\
    \ = 0; i < 500; i++) assert(large.erase(i * 1000000007LL));\n    for (int i =\
    \ 0; i < 500; i++) assert(!large.contains(i * 1000000007LL));\n    for (int i\
    \ = 500; i < 1000; i++) assert(large.at(i * 1000000007LL) == i);\n    auto copied_large\
    \ = large;\n    auto moved_large = std::move(copied_large);\n    for (int i =\
    \ 500; i < 1000; i++) assert(moved_large.at(i * 1000000007LL) == i);\n\n    m1une::ds::HashMap<int,\
    \ int> tested;\n    std::unordered_map<int, int> expected;\n    unsigned long\
    \ long seed = 987654321;\n    for (int q = 0; q < 10000; q++) {\n        seed\
    \ = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n        int x = static_cast<int>((seed\
    \ >> 32) % 400) - 200;\n        int y = static_cast<int>(seed & 1023);\n     \
    \   int type = static_cast<int>(seed % 5);\n        if (type == 0) {\n       \
    \     auto a = tested.insert(x, y);\n            auto b = expected.insert({x,\
    \ y});\n            assert(a.second == b.second);\n            assert(*a.first\
    \ == b.first->second);\n        } else if (type == 1) {\n            tested.insert_or_assign(x,\
    \ y);\n            expected[x] = y;\n        } else if (type == 2) {\n       \
    \     assert(tested.erase(x) == (expected.erase(x) == 1));\n        } else if\
    \ (type == 3) {\n            assert(tested.contains(x) == (expected.find(x) !=\
    \ expected.end()));\n            assert(tested.count(x) == static_cast<int>(expected.count(x)));\n\
    \        } else {\n            tested[x] += y;\n            expected[x] += y;\n\
    \        }\n        assert(tested.size() == static_cast<int>(expected.size()));\n\
    \        for (const auto& [key, value] : expected) assert(tested.at(key) == value);\n\
    \    }\n}\n\nint main() {\n    self_test();\n\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int q;\n    std::cin >> q;\n    m1une::ds::HashMap<long\
    \ long, long long> map;\n    while (q--) {\n        int type;\n        long long\
    \ key;\n        std::cin >> type >> key;\n        if (type == 0) {\n         \
    \   long long value;\n            std::cin >> value;\n            map[key] = value;\n\
    \        } else {\n            std::cout << map[key] << '\\n';\n        }\n  \
    \  }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/associative_array\"\n\n\
    #include \"../../../ds/hash_table/hash_map.hpp\"\n\n#include <cassert>\n#include\
    \ <iostream>\n#include <string>\n#include <unordered_map>\n\nvoid self_test()\
    \ {\n    m1une::ds::HashMap<long long, std::string> mp;\n    assert(mp.empty());\n\
    \    auto inserted = mp.insert(5, std::string(\"five\"));\n    assert(inserted.second);\n\
    \    assert(*inserted.first == \"five\");\n    assert(!mp.insert(5, std::string(\"\
    ignored\")).second);\n    assert(mp.insert({6, \"six\"}).second);\n    assert(mp.at(6)\
    \ == \"six\");\n    assert(mp.at(5) == \"five\");\n\n    mp[7] = \"seven\";\n\
    \    mp.insert_or_assign(5, \"FIVE\");\n    assert(mp.at(5) == \"FIVE\");\n  \
    \  assert(mp.contains(7));\n    assert(mp.erase(7));\n    assert(!mp.contains(7));\n\
    \n    m1une::ds::HashMap<long long, int> large;\n    large.reserve(1000);\n  \
    \  for (int i = 0; i < 1000; i++) large[i * 1000000007LL] = i;\n    for (int i\
    \ = 0; i < 1000; i++) assert(large.at(i * 1000000007LL) == i);\n    for (int i\
    \ = 0; i < 500; i++) assert(large.erase(i * 1000000007LL));\n    for (int i =\
    \ 0; i < 500; i++) assert(!large.contains(i * 1000000007LL));\n    for (int i\
    \ = 500; i < 1000; i++) assert(large.at(i * 1000000007LL) == i);\n    auto copied_large\
    \ = large;\n    auto moved_large = std::move(copied_large);\n    for (int i =\
    \ 500; i < 1000; i++) assert(moved_large.at(i * 1000000007LL) == i);\n\n    m1une::ds::HashMap<int,\
    \ int> tested;\n    std::unordered_map<int, int> expected;\n    unsigned long\
    \ long seed = 987654321;\n    for (int q = 0; q < 10000; q++) {\n        seed\
    \ = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n        int x = static_cast<int>((seed\
    \ >> 32) % 400) - 200;\n        int y = static_cast<int>(seed & 1023);\n     \
    \   int type = static_cast<int>(seed % 5);\n        if (type == 0) {\n       \
    \     auto a = tested.insert(x, y);\n            auto b = expected.insert({x,\
    \ y});\n            assert(a.second == b.second);\n            assert(*a.first\
    \ == b.first->second);\n        } else if (type == 1) {\n            tested.insert_or_assign(x,\
    \ y);\n            expected[x] = y;\n        } else if (type == 2) {\n       \
    \     assert(tested.erase(x) == (expected.erase(x) == 1));\n        } else if\
    \ (type == 3) {\n            assert(tested.contains(x) == (expected.find(x) !=\
    \ expected.end()));\n            assert(tested.count(x) == static_cast<int>(expected.count(x)));\n\
    \        } else {\n            tested[x] += y;\n            expected[x] += y;\n\
    \        }\n        assert(tested.size() == static_cast<int>(expected.size()));\n\
    \        for (const auto& [key, value] : expected) assert(tested.at(key) == value);\n\
    \    }\n}\n\nint main() {\n    self_test();\n\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    int q;\n    std::cin >> q;\n    m1une::ds::HashMap<long\
    \ long, long long> map;\n    while (q--) {\n        int type;\n        long long\
    \ key;\n        std::cin >> type >> key;\n        if (type == 0) {\n         \
    \   long long value;\n            std::cin >> value;\n            map[key] = value;\n\
    \        } else {\n            std::cout << map[key] << '\\n';\n        }\n  \
    \  }\n}\n"
  dependsOn:
  - ds/hash_table/hash_map.hpp
  - ds/hash_table/hash_common.hpp
  isVerificationFile: true
  path: verify/ds/hash_table/hash_map.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 03:13:10+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/ds/hash_table/hash_map.test.cpp
layout: document
redirect_from:
- /verify/verify/ds/hash_table/hash_map.test.cpp
- /verify/verify/ds/hash_table/hash_map.test.cpp.html
title: verify/ds/hash_table/hash_map.test.cpp
---
