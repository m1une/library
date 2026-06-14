---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/hash_common.hpp
    title: data_structure/hash_common.hpp
  - icon: ':heavy_check_mark:'
    path: data_structure/hash_set.hpp
    title: Hash Set
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
  bundledCode: "#line 1 \"verify/data_structure/hash_set.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"data_structure/hash_set.hpp\"\
    \n\n\n\n#line 1 \"data_structure/hash_common.hpp\"\n\n\n\n#include <algorithm>\n\
    #include <chrono>\n#include <cstddef>\n#include <cstdint>\n#include <new>\n#include\
    \ <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace data_structure\
    \ {\nnamespace detail {\n\ninline std::uint64_t splitmix64(std::uint64_t x) {\n\
    \    x += 0x9e3779b97f4a7c15;\n    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
    \    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;\n    return x ^ (x >> 31);\n}\n\
    \ntemplate <typename Key, typename Hash>\nstd::size_t mixed_hash(const Key& key,\
    \ const Hash& hash) {\n    static const std::uint64_t fixed_random =\n       \
    \ std::chrono::steady_clock::now().time_since_epoch().count();\n    return static_cast<std::size_t>(splitmix64(static_cast<std::uint64_t>(hash(key))\
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
    }  // namespace data_structure\n}  // namespace m1une\n\n\n#line 5 \"data_structure/hash_set.hpp\"\
    \n\n#line 8 \"data_structure/hash_set.hpp\"\n#include <functional>\n#include <initializer_list>\n\
    #line 11 \"data_structure/hash_set.hpp\"\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace data_structure {\n\ntemplate <typename T, typename Hash = std::hash<T>,\
    \ typename KeyEqual = std::equal_to<T>>\nstruct HashSet {\n   private:\n    static\
    \ constexpr unsigned char EMPTY = 0;\n    static constexpr unsigned char DELETED\
    \ = 1;\n    static constexpr std::size_t npos = static_cast<std::size_t>(-1);\n\
    \n    std::vector<unsigned char> ctrl;\n    std::vector<detail::Slot<T>> data;\n\
    \    std::size_t _size = 0;\n    std::size_t _deleted = 0;\n    Hash hasher;\n\
    \    KeyEqual key_equal;\n\n    std::size_t mask() const {\n        return ctrl.size()\
    \ - 1;\n    }\n\n    std::size_t make_hash(const T& key) const {\n        return\
    \ detail::mixed_hash(key, hasher);\n    }\n\n    static unsigned char fingerprint(std::size_t\
    \ h) {\n        return static_cast<unsigned char>(2 + (h >> (sizeof(std::size_t)\
    \ * 8 - 7)));\n    }\n\n    static bool occupied(unsigned char c) {\n        return\
    \ c >= 2;\n    }\n\n    T* value_at(std::size_t i) {\n        return data[i].ptr();\n\
    \    }\n\n    const T* value_at(std::size_t i) const {\n        return data[i].ptr();\n\
    \    }\n\n    void destroy_all() {\n        for (std::size_t i = 0; i < ctrl.size();\
    \ i++) {\n            if (occupied(ctrl[i])) data[i].destroy();\n        }\n \
    \   }\n\n    void reset(std::size_t bucket_count) {\n        destroy_all();\n\
    \        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));\n\
    \        ctrl.assign(bucket_count, EMPTY);\n        data.clear();\n        data.resize(bucket_count);\n\
    \        _size = 0;\n        _deleted = 0;\n    }\n\n    std::size_t find_index_with_hash(const\
    \ T& key, std::size_t h) const {\n        const unsigned char fp = fingerprint(h);\n\
    \        std::size_t i = h & mask();\n        while (true) {\n            const\
    \ unsigned char c = ctrl[i];\n            if (c == EMPTY) return npos;\n     \
    \       if (c == fp && key_equal(*value_at(i), key)) return i;\n            i\
    \ = (i + 1) & mask();\n        }\n    }\n\n    std::size_t find_index(const T&\
    \ key) const {\n        return find_index_with_hash(key, make_hash(key));\n  \
    \  }\n\n    template <typename U>\n    void insert_existing(U&& key, std::size_t\
    \ h) {\n        std::size_t i = h & mask();\n        while (occupied(ctrl[i]))\
    \ i = (i + 1) & mask();\n        ctrl[i] = fingerprint(h);\n        data[i].construct(std::forward<U>(key));\n\
    \        _size++;\n    }\n\n    void rebuild(std::size_t bucket_count) {\n   \
    \     std::vector<unsigned char> old_ctrl = std::move(ctrl);\n        std::vector<detail::Slot<T>>\
    \ old_data = std::move(data);\n\n        ctrl.clear();\n        data.clear();\n\
    \        bucket_count = detail::bit_ceil(std::max<std::size_t>(16, bucket_count));\n\
    \        ctrl.assign(bucket_count, EMPTY);\n        data.resize(bucket_count);\n\
    \        _size = 0;\n        _deleted = 0;\n\n        for (std::size_t i = 0;\
    \ i < old_ctrl.size(); i++) {\n            if (occupied(old_ctrl[i])) {\n    \
    \            T* value = old_data[i].ptr();\n                insert_existing(std::move(*value),\
    \ make_hash(*value));\n                old_data[i].destroy();\n            }\n\
    \        }\n    }\n\n    void ensure_for_insert() {\n        const std::size_t\
    \ used = _size + _deleted;\n        if ((used + 1) * 10 >= ctrl.size() * 7) {\n\
    \            rebuild(ctrl.size() * 2);\n        } else if (_deleted > _size &&\
    \ (_size + 1) * 10 < ctrl.size() * 7) {\n            rebuild(ctrl.size());\n \
    \       }\n    }\n\n    template <typename U>\n    bool insert_impl(U&& key) {\n\
    \        ensure_for_insert();\n\n        const std::size_t h = make_hash(key);\n\
    \        const unsigned char fp = fingerprint(h);\n        std::size_t first_deleted\
    \ = npos;\n        std::size_t i = h & mask();\n        while (true) {\n     \
    \       const unsigned char c = ctrl[i];\n            if (occupied(c)) {\n   \
    \             if (c == fp && key_equal(*value_at(i), key)) return false;\n   \
    \         } else if (c == DELETED) {\n                if (first_deleted == npos)\
    \ first_deleted = i;\n            } else {\n                const std::size_t\
    \ pos = first_deleted == npos ? i : first_deleted;\n                if (first_deleted\
    \ != npos) _deleted--;\n                ctrl[pos] = fp;\n                data[pos].construct(std::forward<U>(key));\n\
    \                _size++;\n                return true;\n            }\n     \
    \       i = (i + 1) & mask();\n        }\n    }\n\n   public:\n    HashSet() :\
    \ hasher(Hash()), key_equal(KeyEqual()) {\n        reset(16);\n    }\n\n    explicit\
    \ HashSet(std::size_t reserve_count, Hash hash_fn = Hash(), KeyEqual equal_fn\
    \ = KeyEqual())\n        : hasher(std::move(hash_fn)), key_equal(std::move(equal_fn))\
    \ {\n        reset(detail::bucket_count_for(reserve_count));\n    }\n\n    HashSet(std::initializer_list<T>\
    \ init, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())\n        : HashSet(init.size(),\
    \ std::move(hash_fn), std::move(equal_fn)) {\n        for (const T& x : init)\
    \ insert(x);\n    }\n\n    template <typename Iterator>\n    HashSet(Iterator\
    \ first, Iterator last, Hash hash_fn = Hash(), KeyEqual equal_fn = KeyEqual())\n\
    \        : HashSet(0, std::move(hash_fn), std::move(equal_fn)) {\n        while\
    \ (first != last) {\n            insert(*first);\n            ++first;\n     \
    \   }\n    }\n\n    HashSet(const HashSet& other) : hasher(other.hasher), key_equal(other.key_equal)\
    \ {\n        ctrl.assign(other.ctrl.size(), EMPTY);\n        data.resize(other.data.size());\n\
    \        for (std::size_t i = 0; i < other.ctrl.size(); i++) {\n            ctrl[i]\
    \ = other.ctrl[i];\n            if (occupied(other.ctrl[i])) data[i].construct(*other.value_at(i));\n\
    \        }\n        _size = other._size;\n        _deleted = other._deleted;\n\
    \    }\n\n    HashSet(HashSet&& other) noexcept\n        : ctrl(std::move(other.ctrl)),\n\
    \          data(std::move(other.data)),\n          _size(other._size),\n     \
    \     _deleted(other._deleted),\n          hasher(std::move(other.hasher)),\n\
    \          key_equal(std::move(other.key_equal)) {\n        other.ctrl.clear();\n\
    \        other.data.clear();\n        other._size = 0;\n        other._deleted\
    \ = 0;\n    }\n\n    HashSet& operator=(const HashSet& other) {\n        if (this\
    \ == &other) return *this;\n        HashSet copy(other);\n        *this = std::move(copy);\n\
    \        return *this;\n    }\n\n    HashSet& operator=(HashSet&& other) noexcept\
    \ {\n        if (this == &other) return *this;\n        destroy_all();\n     \
    \   ctrl = std::move(other.ctrl);\n        data = std::move(other.data);\n   \
    \     _size = other._size;\n        _deleted = other._deleted;\n        hasher\
    \ = std::move(other.hasher);\n        key_equal = std::move(other.key_equal);\n\
    \        other.ctrl.clear();\n        other.data.clear();\n        other._size\
    \ = 0;\n        other._deleted = 0;\n        return *this;\n    }\n\n    ~HashSet()\
    \ {\n        destroy_all();\n    }\n\n    int size() const {\n        return static_cast<int>(_size);\n\
    \    }\n\n    bool empty() const {\n        return _size == 0;\n    }\n\n    std::size_t\
    \ bucket_count() const {\n        return ctrl.size();\n    }\n\n    double load_factor()\
    \ const {\n        return static_cast<double>(_size) / static_cast<double>(ctrl.size());\n\
    \    }\n\n    void clear() {\n        reset(ctrl.size());\n    }\n\n    void reserve(std::size_t\
    \ count) {\n        const std::size_t target = detail::bucket_count_for(count);\n\
    \        if (target > ctrl.size() || _deleted > 0) rebuild(std::max(target, ctrl.size()));\n\
    \    }\n\n    bool insert(const T& key) {\n        return insert_impl(key);\n\
    \    }\n\n    bool insert(T&& key) {\n        return insert_impl(std::move(key));\n\
    \    }\n\n    bool erase(const T& key) {\n        const std::size_t h = make_hash(key);\n\
    \        const std::size_t i = find_index_with_hash(key, h);\n        if (i ==\
    \ npos) return false;\n        data[i].destroy();\n        ctrl[i] = DELETED;\n\
    \        _size--;\n        _deleted++;\n        return true;\n    }\n\n    const\
    \ T* find(const T& key) const {\n        const std::size_t i = find_index(key);\n\
    \        return i == npos ? nullptr : value_at(i);\n    }\n\n    bool contains(const\
    \ T& key) const {\n        return find_index(key) != npos;\n    }\n\n    int count(const\
    \ T& key) const {\n        return contains(key) ? 1 : 0;\n    }\n\n    std::vector<T>\
    \ to_vector() const {\n        std::vector<T> result;\n        result.reserve(_size);\n\
    \        for (std::size_t i = 0; i < ctrl.size(); i++) {\n            if (occupied(ctrl[i]))\
    \ result.push_back(*value_at(i));\n        }\n        return result;\n    }\n\
    };\n\n}  // namespace data_structure\n}  // namespace m1une\n\n\n#line 4 \"verify/data_structure/hash_set.test.cpp\"\
    \n\n#include <cassert>\n#include <iostream>\n#include <unordered_set>\n#line 9\
    \ \"verify/data_structure/hash_set.test.cpp\"\n\nint main() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    m1une::data_structure::HashSet<long long> st;\n\
    \    assert(st.empty());\n    assert(st.insert(5));\n    assert(!st.insert(5));\n\
    \    assert(st.insert(1));\n    assert(st.contains(5));\n    assert(st.count(1)\
    \ == 1);\n    assert(st.erase(5));\n    assert(!st.contains(5));\n    assert(!st.erase(5));\n\
    \n    std::vector<long long> xs;\n    for (int i = 0; i < 1000; i++) xs.push_back(i\
    \ * 1000000007LL);\n    m1une::data_structure::HashSet<long long> large(xs.begin(),\
    \ xs.end());\n    for (long long x : xs) assert(large.contains(x));\n    for (int\
    \ i = 0; i < 500; i++) assert(large.erase(xs[i]));\n    for (int i = 0; i < 500;\
    \ i++) assert(!large.contains(xs[i]));\n    for (int i = 500; i < 1000; i++) assert(large.contains(xs[i]));\n\
    \    auto copied_large = large;\n    auto moved_large = std::move(copied_large);\n\
    \    for (int i = 500; i < 1000; i++) assert(moved_large.contains(xs[i]));\n\n\
    \    m1une::data_structure::HashSet<int> tested;\n    std::unordered_set<int>\
    \ expected;\n    unsigned long long seed = 123456789;\n    for (int q = 0; q <\
    \ 10000; q++) {\n        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n\
    \        int x = static_cast<int>((seed >> 32) % 400) - 200;\n        int type\
    \ = static_cast<int>(seed % 4);\n        if (type == 0) {\n            assert(tested.insert(x)\
    \ == (expected.insert(x).second));\n        } else if (type == 1) {\n        \
    \    assert(tested.erase(x) == (expected.erase(x) == 1));\n        } else {\n\
    \            assert(tested.contains(x) == (expected.find(x) != expected.end()));\n\
    \            assert(tested.count(x) == static_cast<int>(expected.count(x)));\n\
    \        }\n        assert(tested.size() == static_cast<int>(expected.size()));\n\
    \    }\n\n    long long A, B;\n    std::cin >> A >> B;\n    std::cout << A + B\
    \ << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    data_structure/hash_set.hpp\"\n\n#include <cassert>\n#include <iostream>\n#include\
    \ <unordered_set>\n#include <vector>\n\nint main() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n\n    m1une::data_structure::HashSet<long long> st;\n\
    \    assert(st.empty());\n    assert(st.insert(5));\n    assert(!st.insert(5));\n\
    \    assert(st.insert(1));\n    assert(st.contains(5));\n    assert(st.count(1)\
    \ == 1);\n    assert(st.erase(5));\n    assert(!st.contains(5));\n    assert(!st.erase(5));\n\
    \n    std::vector<long long> xs;\n    for (int i = 0; i < 1000; i++) xs.push_back(i\
    \ * 1000000007LL);\n    m1une::data_structure::HashSet<long long> large(xs.begin(),\
    \ xs.end());\n    for (long long x : xs) assert(large.contains(x));\n    for (int\
    \ i = 0; i < 500; i++) assert(large.erase(xs[i]));\n    for (int i = 0; i < 500;\
    \ i++) assert(!large.contains(xs[i]));\n    for (int i = 500; i < 1000; i++) assert(large.contains(xs[i]));\n\
    \    auto copied_large = large;\n    auto moved_large = std::move(copied_large);\n\
    \    for (int i = 500; i < 1000; i++) assert(moved_large.contains(xs[i]));\n\n\
    \    m1une::data_structure::HashSet<int> tested;\n    std::unordered_set<int>\
    \ expected;\n    unsigned long long seed = 123456789;\n    for (int q = 0; q <\
    \ 10000; q++) {\n        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;\n\
    \        int x = static_cast<int>((seed >> 32) % 400) - 200;\n        int type\
    \ = static_cast<int>(seed % 4);\n        if (type == 0) {\n            assert(tested.insert(x)\
    \ == (expected.insert(x).second));\n        } else if (type == 1) {\n        \
    \    assert(tested.erase(x) == (expected.erase(x) == 1));\n        } else {\n\
    \            assert(tested.contains(x) == (expected.find(x) != expected.end()));\n\
    \            assert(tested.count(x) == static_cast<int>(expected.count(x)));\n\
    \        }\n        assert(tested.size() == static_cast<int>(expected.size()));\n\
    \    }\n\n    long long A, B;\n    std::cin >> A >> B;\n    std::cout << A + B\
    \ << '\\n';\n}\n"
  dependsOn:
  - data_structure/hash_set.hpp
  - data_structure/hash_common.hpp
  isVerificationFile: true
  path: verify/data_structure/hash_set.test.cpp
  requiredBy: []
  timestamp: '2026-06-15 03:24:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/data_structure/hash_set.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/hash_set.test.cpp
- /verify/verify/data_structure/hash_set.test.cpp.html
title: verify/data_structure/hash_set.test.cpp
---
