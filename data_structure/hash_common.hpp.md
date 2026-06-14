---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: data_structure/hash_map.hpp
    title: Hash Map
  - icon: ':heavy_check_mark:'
    path: data_structure/hash_set.hpp
    title: Hash Set
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/hash_map.test.cpp
    title: verify/data_structure/hash_map.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/hash_map_associative_array.test.cpp
    title: verify/data_structure/hash_map_associative_array.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/data_structure/hash_set.test.cpp
    title: verify/data_structure/hash_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"data_structure/hash_common.hpp\"\n\n\n\n#include <algorithm>\n\
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
    }  // namespace data_structure\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_HASH_COMMON_HPP\n#define M1UNE_HASH_COMMON_HPP 1\n\n#include\
    \ <algorithm>\n#include <chrono>\n#include <cstddef>\n#include <cstdint>\n#include\
    \ <new>\n#include <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace\
    \ data_structure {\nnamespace detail {\n\ninline std::uint64_t splitmix64(std::uint64_t\
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
    }  // namespace data_structure\n}  // namespace m1une\n\n#endif  // M1UNE_HASH_COMMON_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/hash_common.hpp
  requiredBy:
  - data_structure/hash_map.hpp
  - data_structure/hash_set.hpp
  timestamp: '2026-06-15 03:24:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/data_structure/hash_map_associative_array.test.cpp
  - verify/data_structure/hash_set.test.cpp
  - verify/data_structure/hash_map.test.cpp
documentation_of: data_structure/hash_common.hpp
layout: document
redirect_from:
- /library/data_structure/hash_common.hpp
- /library/data_structure/hash_common.hpp.html
title: data_structure/hash_common.hpp
---
