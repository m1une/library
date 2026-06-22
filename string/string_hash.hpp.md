---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/all.hpp
    title: String Algorithms Bundle
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/string/string_algorithms.test.cpp
    title: verify/string/string_algorithms.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string/string_hash.test.cpp
    title: verify/string/string_hash.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/string_hash.hpp\"\n\n\n\n#include <cstddef>\n#include\
    \ <cstdint>\n#include <string>\n#include <string_view>\n\nnamespace m1une {\n\
    namespace string {\n\nstruct StringHash {\n    std::uint32_t first;\n    std::uint32_t\
    \ second;\n    std::uint32_t first_power;\n    std::uint32_t second_power;\n \
    \   std::size_t length;\n\n    friend constexpr bool operator==(const StringHash&\
    \ left, const StringHash& right) {\n        return left.length == right.length\
    \ && left.first == right.first && left.second == right.second;\n    }\n};\n\n\
    namespace string_hash_detail {\n\ninline constexpr std::uint64_t first_mod = 1'000'000'007;\n\
    inline constexpr std::uint64_t second_mod = 1'000'000'009;\ninline constexpr std::uint64_t\
    \ base = 911'382'323;\n\n}  // namespace string_hash_detail\n\n// Computes a double\
    \ polynomial hash. Bytes are interpreted as unsigned.\nconstexpr StringHash hash_string(std::string_view\
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
    \    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_STRING_STRING_HASH_HPP\n#define M1UNE_STRING_STRING_HASH_HPP\
    \ 1\n\n#include <cstddef>\n#include <cstdint>\n#include <string>\n#include <string_view>\n\
    \nnamespace m1une {\nnamespace string {\n\nstruct StringHash {\n    std::uint32_t\
    \ first;\n    std::uint32_t second;\n    std::uint32_t first_power;\n    std::uint32_t\
    \ second_power;\n    std::size_t length;\n\n    friend constexpr bool operator==(const\
    \ StringHash& left, const StringHash& right) {\n        return left.length ==\
    \ right.length && left.first == right.first && left.second == right.second;\n\
    \    }\n};\n\nnamespace string_hash_detail {\n\ninline constexpr std::uint64_t\
    \ first_mod = 1'000'000'007;\ninline constexpr std::uint64_t second_mod = 1'000'000'009;\n\
    inline constexpr std::uint64_t base = 911'382'323;\n\n}  // namespace string_hash_detail\n\
    \n// Computes a double polynomial hash. Bytes are interpreted as unsigned.\nconstexpr\
    \ StringHash hash_string(std::string_view value) {\n    using namespace string_hash_detail;\n\
    \    std::uint64_t first = 0;\n    std::uint64_t second = 0;\n    std::uint64_t\
    \ first_power = 1;\n    std::uint64_t second_power = 1;\n    for (char character\
    \ : value) {\n        std::uint64_t symbol = static_cast<unsigned char>(character)\
    \ + std::uint64_t(1);\n        first = (first * base + symbol) % first_mod;\n\
    \        second = (second * base + symbol) % second_mod;\n        first_power\
    \ = first_power * base % first_mod;\n        second_power = second_power * base\
    \ % second_mod;\n    }\n    return StringHash{\n        static_cast<std::uint32_t>(first),\n\
    \        static_cast<std::uint32_t>(second),\n        static_cast<std::uint32_t>(first_power),\n\
    \        static_cast<std::uint32_t>(second_power),\n        value.size(),\n  \
    \  };\n}\n\nconstexpr StringHash hash_string(const std::string& value) {\n   \
    \ return hash_string(std::string_view(value));\n}\n\nconstexpr StringHash hash_string(const\
    \ char* value) {\n    return hash_string(std::string_view(value));\n}\n\n// Returns\
    \ the hash of the concatenation represented by `left` and `right`.\nconstexpr\
    \ StringHash concat_string_hash(const StringHash& left, const StringHash& right)\
    \ {\n    using namespace string_hash_detail;\n    return StringHash{\n       \
    \ static_cast<std::uint32_t>((std::uint64_t(left.first) * right.first_power +\
    \ right.first) % first_mod),\n        static_cast<std::uint32_t>((std::uint64_t(left.second)\
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
    \    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\n#endif  // M1UNE_STRING_STRING_HASH_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: string/string_hash.hpp
  requiredBy:
  - string/all.hpp
  timestamp: '2026-06-23 02:51:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/string/string_hash.test.cpp
  - verify/string/string_algorithms.test.cpp
documentation_of: string/string_hash.hpp
layout: document
title: String Hash
---

## Overview

This header computes a compact whole-string hash using two polynomial hashes.
It is useful when strings are treated as indivisible values rather than when
arbitrary substring queries are required.

For substring hashing, longest-common-prefix queries, and comparisons, use
`RollingHash` instead.

## Hash Value

```cpp
struct StringHash {
    uint32_t first;
    uint32_t second;
    uint32_t first_power;
    uint32_t second_power;
    size_t length;
};
```

`first` and `second` are hashes modulo two different primes. The power fields
allow two known hashes to be concatenated in constant time. Equality compares
both hashes and the string length.

As with every non-cryptographic hash, equality of hashes is not a mathematical
proof that strings are equal. Using two independent moduli makes accidental
collisions unlikely in competitive-programming applications.

## Functions

| Function | Description | Complexity |
| --- | --- | --- |
| `hash_string(value)` | Returns the double hash of a string or string view. | $O(N)$ |
| `concat_string_hash(left, right)` | Returns the hash of the represented concatenation. | $O(1)$ |

Characters are interpreted as unsigned bytes and shifted by one, so embedded
null bytes and bytes with values from 128 through 255 are handled consistently.

The implementation is `constexpr`, permitting hashes of compile-time string
literals.

## Unordered Containers

`StringHasher` can hash `std::string`, `std::string_view`, C strings, and
`StringHash` values:

```cpp
std::unordered_set<std::string, m1une::string::StringHasher> words;
```

For standard strings this provides a deterministic double-polynomial hash.
It is intended for convenience and collision resistance, not cryptographic or
adversarial security.

## Example

```cpp
#include "string/string_hash.hpp"

#include <iostream>

int main() {
    constexpr auto hello = m1une::string::hash_string("hello");
    constexpr auto space = m1une::string::hash_string(" ");
    constexpr auto world = m1une::string::hash_string("world");

    constexpr auto left =
        m1une::string::concat_string_hash(hello, space);
    constexpr auto sentence =
        m1une::string::concat_string_hash(left, world);

    std::cout << (sentence == m1une::string::hash_string("hello world"))
              << "\n";
}
```
