---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: string/string_hash.hpp
    title: String Hash
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
  bundledCode: "#line 1 \"verify/string/string_hash.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"string/string_hash.hpp\"\
    \n\n\n\n#include <cstddef>\n#include <cstdint>\n#include <string>\n#include <string_view>\n\
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
    \    }\n};\n\n}  // namespace string\n}  // namespace m1une\n\n\n#line 4 \"verify/string/string_hash.test.cpp\"\
    \n\n#include <cassert>\n#line 7 \"verify/string/string_hash.test.cpp\"\n#include\
    \ <iostream>\n#line 10 \"verify/string/string_hash.test.cpp\"\n#include <unordered_set>\n\
    \nnamespace {\n\nvoid test_fixed() {\n    using m1une::string::concat_string_hash;\n\
    \    using m1une::string::hash_string;\n\n    constexpr auto empty = hash_string(\"\
    \");\n    constexpr auto first = hash_string(\"abc\");\n    constexpr auto second\
    \ = hash_string(\"def\");\n    constexpr auto combined = concat_string_hash(first,\
    \ second);\n    static_assert(combined == hash_string(\"abcdef\"));\n    static_assert(concat_string_hash(empty,\
    \ first) == first);\n    static_assert(concat_string_hash(first, empty) == first);\n\
    \    static_assert(hash_string(\"abc\") != hash_string(\"abd\"));\n    static_assert(\n\
    \        hash_string(\"a\")\n        != hash_string(std::string_view(\"a\\0\"\
    , 2))\n    );\n\n    std::string bytes;\n    bytes.push_back(char(0));\n    bytes.push_back(char(128));\n\
    \    bytes.push_back(char(255));\n    assert(\n        hash_string(bytes)\n  \
    \      == hash_string(std::string_view(bytes.data(), bytes.size()))\n    );\n\n\
    \    std::unordered_set<\n        std::string,\n        m1une::string::StringHasher,\n\
    \        std::equal_to<>\n    > words;\n    words.insert(\"alpha\");\n    words.insert(\"\
    beta\");\n    assert(words.contains(std::string_view(\"alpha\")));\n    assert(!words.contains(std::string_view(\"\
    gamma\")));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 1103;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 20000; ++trial) {\n        int first_length = int(random() % 40);\n      \
    \  int second_length = int(random() % 40);\n        std::string first(first_length,\
    \ '\\0');\n        std::string second(second_length, '\\0');\n        for (char&\
    \ character : first) character = char(random() & 255);\n        for (char& character\
    \ : second) character = char(random() & 255);\n\n        std::string joined =\
    \ first + second;\n        assert(\n            m1une::string::concat_string_hash(\n\
    \                m1une::string::hash_string(first),\n                m1une::string::hash_string(second)\n\
    \            ) == m1une::string::hash_string(joined)\n        );\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n\
    \    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../string/string_hash.hpp\"\n\n#include <cassert>\n#include <cstdint>\n#include\
    \ <iostream>\n#include <string>\n#include <string_view>\n#include <unordered_set>\n\
    \nnamespace {\n\nvoid test_fixed() {\n    using m1une::string::concat_string_hash;\n\
    \    using m1une::string::hash_string;\n\n    constexpr auto empty = hash_string(\"\
    \");\n    constexpr auto first = hash_string(\"abc\");\n    constexpr auto second\
    \ = hash_string(\"def\");\n    constexpr auto combined = concat_string_hash(first,\
    \ second);\n    static_assert(combined == hash_string(\"abcdef\"));\n    static_assert(concat_string_hash(empty,\
    \ first) == first);\n    static_assert(concat_string_hash(first, empty) == first);\n\
    \    static_assert(hash_string(\"abc\") != hash_string(\"abd\"));\n    static_assert(\n\
    \        hash_string(\"a\")\n        != hash_string(std::string_view(\"a\\0\"\
    , 2))\n    );\n\n    std::string bytes;\n    bytes.push_back(char(0));\n    bytes.push_back(char(128));\n\
    \    bytes.push_back(char(255));\n    assert(\n        hash_string(bytes)\n  \
    \      == hash_string(std::string_view(bytes.data(), bytes.size()))\n    );\n\n\
    \    std::unordered_set<\n        std::string,\n        m1une::string::StringHasher,\n\
    \        std::equal_to<>\n    > words;\n    words.insert(\"alpha\");\n    words.insert(\"\
    beta\");\n    assert(words.contains(std::string_view(\"alpha\")));\n    assert(!words.contains(std::string_view(\"\
    gamma\")));\n}\n\nvoid test_randomized() {\n    std::uint64_t state = 1103;\n\
    \    auto random = [&state]() {\n        state ^= state << 7;\n        state ^=\
    \ state >> 9;\n        return state;\n    };\n\n    for (int trial = 0; trial\
    \ < 20000; ++trial) {\n        int first_length = int(random() % 40);\n      \
    \  int second_length = int(random() % 40);\n        std::string first(first_length,\
    \ '\\0');\n        std::string second(second_length, '\\0');\n        for (char&\
    \ character : first) character = char(random() & 255);\n        for (char& character\
    \ : second) character = char(random() & 255);\n\n        std::string joined =\
    \ first + second;\n        assert(\n            m1une::string::concat_string_hash(\n\
    \                m1une::string::hash_string(first),\n                m1une::string::hash_string(second)\n\
    \            ) == m1une::string::hash_string(joined)\n        );\n    }\n}\n\n\
    }  // namespace\n\nint main() {\n    test_fixed();\n    test_randomized();\n\n\
    \    long long a, b;\n    std::cin >> a >> b;\n    std::cout << a + b << '\\n';\n\
    }\n"
  dependsOn:
  - string/string_hash.hpp
  isVerificationFile: true
  path: verify/string/string_hash.test.cpp
  requiredBy: []
  timestamp: '2026-06-23 02:51:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/string/string_hash.test.cpp
layout: document
redirect_from:
- /verify/verify/string/string_hash.test.cpp
- /verify/verify/string/string_hash.test.cpp.html
title: verify/string/string_hash.test.cpp
---
