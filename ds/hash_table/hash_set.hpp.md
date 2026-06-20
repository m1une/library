---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: ds/hash_table/hash_common.hpp
    title: ds/hash_table/hash_common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/ds/hash_table/hash_set.test.cpp
    title: verify/ds/hash_table/hash_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"ds/hash_table/hash_set.hpp\"\n\n\n\n#line 1 \"ds/hash_table/hash_common.hpp\"\
    \n\n\n\n#include <algorithm>\n#include <chrono>\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <new>\n#include <type_traits>\n#include <utility>\n\nnamespace\
    \ m1une {\nnamespace ds {\nnamespace detail {\n\ninline std::uint64_t splitmix64(std::uint64_t\
    \ x) {\n    x += 0x9e3779b97f4a7c15;\n    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;\n\
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
    }  // namespace ds\n}  // namespace m1une\n\n\n#line 5 \"ds/hash_table/hash_set.hpp\"\
    \n\n#line 8 \"ds/hash_table/hash_set.hpp\"\n#include <functional>\n#include <initializer_list>\n\
    #line 11 \"ds/hash_table/hash_set.hpp\"\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <typename T, typename Hash = std::hash<T>, typename\
    \ KeyEqual = std::equal_to<T>>\nstruct HashSet {\n   private:\n    static constexpr\
    \ unsigned char EMPTY = 0;\n    static constexpr unsigned char DELETED = 1;\n\
    \    static constexpr std::size_t npos = static_cast<std::size_t>(-1);\n\n   \
    \ std::vector<unsigned char> ctrl;\n    std::vector<detail::Slot<T>> data;\n \
    \   std::size_t _size = 0;\n    std::size_t _deleted = 0;\n    Hash hasher;\n\
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
    };\n\n}  // namespace ds\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_HASH_SET_HPP\n#define M1UNE_HASH_SET_HPP 1\n\n#include \"ds/hash_table/hash_common.hpp\"\
    \n\n#include <algorithm>\n#include <cstddef>\n#include <functional>\n#include\
    \ <initializer_list>\n#include <utility>\n#include <vector>\n\nnamespace m1une\
    \ {\nnamespace ds {\n\ntemplate <typename T, typename Hash = std::hash<T>, typename\
    \ KeyEqual = std::equal_to<T>>\nstruct HashSet {\n   private:\n    static constexpr\
    \ unsigned char EMPTY = 0;\n    static constexpr unsigned char DELETED = 1;\n\
    \    static constexpr std::size_t npos = static_cast<std::size_t>(-1);\n\n   \
    \ std::vector<unsigned char> ctrl;\n    std::vector<detail::Slot<T>> data;\n \
    \   std::size_t _size = 0;\n    std::size_t _deleted = 0;\n    Hash hasher;\n\
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
    };\n\n}  // namespace ds\n}  // namespace m1une\n\n#endif  // M1UNE_HASH_SET_HPP\n"
  dependsOn:
  - ds/hash_table/hash_common.hpp
  isVerificationFile: false
  path: ds/hash_table/hash_set.hpp
  requiredBy: []
  timestamp: '2026-06-20 20:05:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/ds/hash_table/hash_set.test.cpp
documentation_of: ds/hash_table/hash_set.hpp
layout: document
title: Hash Set
---

## Overview

`HashSet` is a flat open-addressing hash set. It is intended as a faster and more hack-resistant replacement for `std::unordered_set` in competitive programming.

Hashes are passed through a salted splitmix64 mixer, which helps avoid adversarial collisions for common integral keys. The table uses linear probing and rebuilds before the load factor reaches about 70%.

Pointers returned by `find` remain valid until the set is modified.

## Template Parameters

* `T`: The key type.
* `Hash`: Hash function. Defaults to `std::hash<T>`.
* `KeyEqual`: Equality predicate. Defaults to `std::equal_to<T>`.

## Constructors

* `HashSet()`
  Constructs an empty set. ($O(1)$)

* `HashSet(std::size_t reserve_count)`
  Constructs an empty set with enough buckets for about `reserve_count` keys. ($O(1)$)

* `HashSet(std::initializer_list<T> init)`
  Constructs a set from an initializer list. Duplicate keys are ignored. Expected $O(N)$

* `HashSet(Iterator first, Iterator last)`
  Constructs a set from a range. Duplicate keys are ignored. Expected $O(N)$

## Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `int size() const` | Returns the number of keys. | $O(1)$ |
| `bool empty() const` | Returns whether the set is empty. | $O(1)$ |
| `std::size_t bucket_count() const` | Returns the number of buckets. | $O(1)$ |
| `double load_factor() const` | Returns `size() / bucket_count()`. | $O(1)$ |
| `void clear()` | Removes all keys. | $O(B)$ |
| `void reserve(std::size_t count)` | Reserves enough buckets for about `count` keys. | Expected $O(N)$ |
| `bool insert(const T& key)`, `bool insert(T&& key)` | Inserts `key`; returns whether a new key was inserted. | Expected $O(1)$ |
| `bool erase(const T& key)` | Removes `key`; returns whether a key was removed. | Expected $O(1)$ |
| `const T* find(const T& key) const` | Returns a pointer to `key`, or `nullptr` if it does not exist. | Expected $O(1)$ |
| `bool contains(const T& key) const` | Returns whether `key` exists. | Expected $O(1)$ |
| `int count(const T& key) const` | Returns `1` if `key` exists, otherwise `0`. | Expected $O(1)$ |
| `std::vector<T> to_vector() const` | Returns all keys in bucket order. | $O(B)$ |

## Example

```cpp
#include "ds/hash_table/hash_set.hpp"

#include <iostream>

int main() {
    m1une::ds::HashSet<long long> st = {3, 1, 3, 5};

    st.insert(2);
    st.erase(3);

    std::cout << st.contains(5) << "\n";  // 1
    std::cout << st.count(3) << "\n";     // 0
}
```
