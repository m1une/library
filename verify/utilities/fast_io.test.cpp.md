---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: utilities/fast_io.hpp
    title: Fast IO
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
  bundledCode: "#line 1 \"verify/utilities/fast_io.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/aplusb\"\n\n#line 1 \"utilities/fast_io.hpp\"\n\
    \n\n\n#include <cstddef>\n#include <cstdio>\n#include <iterator>\n#include <string>\n\
    #include <type_traits>\n#include <utility>\n\nnamespace m1une {\nnamespace utilities\
    \ {\nnamespace internal {\n\n// Detect std::begin(x), std::end(x).\ntemplate <class\
    \ T, class = void>\nstruct is_range : std::false_type {};\n\ntemplate <class T>\n\
    struct is_range<T, std::void_t<\n    decltype(std::begin(std::declval<T&>())),\n\
    \    decltype(std::end(std::declval<T&>()))\n>> : std::true_type {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_range_v = is_range<T>::value;\n\ntemplate\
    \ <class T>\nusing range_reference_t = decltype(*std::begin(std::declval<T&>()));\n\
    \ntemplate <class T>\nusing range_value_t = std::remove_cv_t<std::remove_reference_t<range_reference_t<T>>>;\n\
    \ntemplate <class T, class = void>\nstruct range_stored_value {\n    using type\
    \ = range_value_t<T>;\n};\n\ntemplate <class T>\nstruct range_stored_value<T,\
    \ std::void_t<typename std::remove_cv_t<std::remove_reference_t<T>>::value_type>>\
    \ {\n    using type = typename std::remove_cv_t<std::remove_reference_t<T>>::value_type;\n\
    };\n\ntemplate <class T>\nusing range_stored_value_t = typename range_stored_value<T>::type;\n\
    \n// Treat strings and C strings as scalar output objects, not as ranges.\ntemplate\
    \ <class T>\nstruct is_char_array : std::false_type {};\n\ntemplate <class T,\
    \ std::size_t N>\nstruct is_char_array<T[N]>\n    : std::bool_constant<std::is_same_v<std::remove_cv_t<T>,\
    \ char>> {};\n\ntemplate <class T>\nstruct is_string_like\n    : std::bool_constant<\n\
    \          std::is_same_v<std::decay_t<T>, std::string>\n          || std::is_same_v<std::decay_t<T>,\
    \ const char*>\n          || std::is_same_v<std::decay_t<T>, char*>\n        \
    \  || is_char_array<std::remove_reference_t<T>>::value\n      > {};\n\ntemplate\
    \ <class T>\ninline constexpr bool is_string_like_v = is_string_like<T>::value;\n\
    \n// ModInt-like type: x.val() is printable, and x can be assigned from long long.\n\
    template <class T, class = void>\nstruct has_val_method : std::false_type {};\n\
    \ntemplate <class T>\nstruct has_val_method<T, std::void_t<decltype(std::declval<const\
    \ T&>().val())>>\n    : std::true_type {};\n\ntemplate <class T>\ninline constexpr\
    \ bool has_val_method_v = has_val_method<T>::value;\n\n}  // namespace internal\n\
    \nstruct FastInput {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n\
    \    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int _position;\n\
    \    int _length;\n\n   public:\n    explicit FastInput(std::FILE* stream = stdin)\n\
    \        : _stream(stream), _position(0), _length(0) {}\n\n    FastInput(const\
    \ FastInput&) = delete;\n    FastInput& operator=(const FastInput&) = delete;\n\
    \n    int read_char_raw() {\n        if (_position == _length) {\n           \
    \ _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n            _position\
    \ = 0;\n            if (_length == 0) return EOF;\n        }\n        return _buffer[_position++];\n\
    \    }\n\n    bool skip_spaces() {\n        int c = read_char_raw();\n       \
    \ while (c != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return\
    \ false;\n        --_position;\n        return true;\n    }\n\n    bool read(char&\
    \ value) {\n        if (!skip_spaces()) return false;\n        value = char(read_char_raw());\n\
    \        return true;\n    }\n\n    bool read(std::string& value) {\n        if\
    \ (!skip_spaces()) return false;\n        value.clear();\n        int c = read_char_raw();\n\
    \        while (c != EOF && c > ' ') {\n            value.push_back(char(c));\n\
    \            c = read_char_raw();\n        }\n        return true;\n    }\n\n\
    \    bool read(bool& value) {\n        int x;\n        if (!read(x)) return false;\n\
    \        value = x != 0;\n        return true;\n    }\n\n    template <class T>\n\
    \    std::enable_if_t<\n        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>,\n        bool\n\
    \    >\n    read(T& value) {\n        int c = read_char_raw();\n        while\
    \ (c != EOF && c <= ' ') c = read_char_raw();\n        if (c == EOF) return false;\n\
    \n        bool negative = false;\n        if (c == '-') {\n            negative\
    \ = true;\n            c = read_char_raw();\n        }\n\n        if constexpr\
    \ (std::is_signed_v<T>) {\n            T result = 0;\n            while ('0' <=\
    \ c && c <= '9') {\n                int digit = c - '0';\n                result\
    \ = negative ? result * 10 - digit : result * 10 + digit;\n                c =\
    \ read_char_raw();\n            }\n            value = result;\n        } else\
    \ {\n            T result = 0;\n            while ('0' <= c && c <= '9') {\n \
    \               result = result * 10 + T(c - '0');\n                c = read_char_raw();\n\
    \            }\n            value = negative ? T(0) - result : result;\n     \
    \   }\n        return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        internal::has_val_method_v<T>\n            && !std::is_integral_v<T>\n\
    \            && !internal::is_range_v<T>,\n        bool\n    >\n    read(T& value)\
    \ {\n        long long x;\n        if (!read(x)) return false;\n        value\
    \ = T(x);\n        return true;\n    }\n\n    template <class Range>\n    std::enable_if_t<\n\
    \        internal::is_range_v<Range>\n            && !internal::is_string_like_v<Range>,\n\
    \        bool\n    >\n    read(Range& range) {\n        using StoredValue = internal::range_stored_value_t<Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   for (auto&& value : range) {\n            if constexpr (std::is_same_v<StoredValue,\
    \ bool> && !nested) {\n                bool x;\n                if (!read(x))\
    \ return false;\n                value = x;\n            } else {\n          \
    \      if (!read(value)) return false;\n            }\n        }\n        return\
    \ true;\n    }\n\n    template <class First, class Second, class... Rest>\n  \
    \  bool read(First& first, Second& second, Rest&... rest) {\n        if (!read(first))\
    \ return false;\n        return read(second, rest...);\n    }\n};\n\nstruct FastOutput\
    \ {\n    static constexpr int buffer_size = 1 << 20;\n\n   private:\n    std::FILE*\
    \ _stream;\n    char _buffer[buffer_size];\n    int _position;\n\n   public:\n\
    \    explicit FastOutput(std::FILE* stream = stdout)\n        : _stream(stream),\
    \ _position(0) {}\n\n    FastOutput(const FastOutput&) = delete;\n    FastOutput&\
    \ operator=(const FastOutput&) = delete;\n\n    ~FastOutput() {\n        flush();\n\
    \    }\n\n    void flush() {\n        if (_position == 0) return;\n        std::fwrite(_buffer,\
    \ 1, _position, _stream);\n        _position = 0;\n    }\n\n    void write_char(char\
    \ c) {\n        if (_position == buffer_size) flush();\n        _buffer[_position++]\
    \ = c;\n    }\n\n    void write(const char* s) {\n        while (*s != '\\0')\
    \ write_char(*s++);\n    }\n\n    void write(const std::string& s) {\n       \
    \ for (char c : s) write_char(c);\n    }\n\n    void write(char c) {\n       \
    \ write_char(c);\n    }\n\n    void write(bool value) {\n        write_char(value\
    \ ? '1' : '0');\n    }\n\n    template <class T>\n    std::enable_if_t<\n    \
    \    std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ bool>\n            && !std::is_same_v<std::remove_cv_t<T>, char>\n    >\n  \
    \  write(T value) {\n        using Raw = std::remove_cv_t<T>;\n        using Unsigned\
    \ = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n        if constexpr\
    \ (std::is_signed_v<Raw>) {\n            if (value < 0) {\n                write_char('-');\n\
    \                magnitude = Unsigned(0) - Unsigned(value);\n            } else\
    \ {\n                magnitude = Unsigned(value);\n            }\n        } else\
    \ {\n            magnitude = value;\n        }\n\n        if (magnitude == 0)\
    \ {\n            write_char('0');\n            return;\n        }\n\n        char\
    \ digits[64];\n        int count = 0;\n        while (magnitude > 0) {\n     \
    \       digits[count++] = char('0' + magnitude % 10);\n            magnitude /=\
    \ 10;\n        }\n        while (count--) write_char(digits[count]);\n    }\n\n\
    \    template <class T>\n    std::enable_if_t<\n        internal::has_val_method_v<T>\n\
    \            && !std::is_integral_v<T>\n            && !internal::is_range_v<T>\n\
    \    >\n    write(const T& value) {\n        write(value.val());\n    }\n\n  \
    \  template <class Range>\n    std::enable_if_t<\n        internal::is_range_v<Range>\n\
    \            && !internal::is_string_like_v<Range>\n    >\n    write(const Range&\
    \ range) {\n        using StoredValue = internal::range_stored_value_t<const Range>;\n\
    \        constexpr bool nested = internal::is_range_v<StoredValue>\n         \
    \                       && !internal::is_string_like_v<StoredValue>;\n\n     \
    \   bool first = true;\n        for (const auto& value : range) {\n          \
    \  if (!first) write_char(nested ? '\\n' : ' ');\n            first = false;\n\
    \            if constexpr (std::is_same_v<StoredValue, bool> && !nested) {\n \
    \               write(static_cast<bool>(value));\n            } else {\n     \
    \           write(value);\n            }\n        }\n    }\n\n    template <class\
    \ First, class... Rest>\n    void print(const First& first, const Rest&... rest)\
    \ {\n        write(first);\n        ((write_char(' '), write(rest)), ...);\n \
    \   }\n\n    void println() {\n        write_char('\\n');\n    }\n\n    template\
    \ <class... Args>\n    void println(const Args&... args) {\n        print(args...);\n\
    \        write_char('\\n');\n    }\n};\n\n}  // namespace utilities\n}  // namespace\
    \ m1une\n\n\n#line 4 \"verify/utilities/fast_io.test.cpp\"\n\n#include <cassert>\n\
    #line 8 \"verify/utilities/fast_io.test.cpp\"\n\nvoid test_fast_input() {\n  \
    \  std::FILE* file = std::tmpfile();\n    assert(file != nullptr);\n    std::fputs(\"\
    \ -123 456 token Z 1\\n\", file);\n    std::rewind(file);\n\n    m1une::utilities::FastInput\
    \ input(file);\n    int a;\n    unsigned int b;\n    std::string s;\n    char\
    \ c;\n    bool flag;\n    assert(input.read(a, b, s, c, flag));\n    assert(a\
    \ == -123);\n    assert(b == 456);\n    assert(s == \"token\");\n    assert(c\
    \ == 'Z');\n    assert(flag);\n    std::fclose(file);\n}\n\nvoid test_fast_output()\
    \ {\n    std::FILE* file = std::tmpfile();\n    assert(file != nullptr);\n\n \
    \   {\n        m1une::utilities::FastOutput output(file);\n        output.println(\"\
    answer\", -42, 17u);\n        output.println(false);\n        output.flush();\n\
    \    }\n\n    std::rewind(file);\n    char buffer[64];\n    std::size_t length\
    \ = std::fread(buffer, 1, sizeof(buffer), file);\n    std::string result(buffer,\
    \ buffer + length);\n    assert(result == \"answer -42 17\\n0\\n\");\n    std::fclose(file);\n\
    }\n\nint main() {\n    test_fast_input();\n    test_fast_output();\n\n    m1une::utilities::FastInput\
    \ input;\n    m1une::utilities::FastOutput output;\n\n    long long a, b;\n  \
    \  input.read(a, b);\n    output.println(a + b);\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ../../utilities/fast_io.hpp\"\n\n#include <cassert>\n#include <cstdio>\n#include\
    \ <string>\n\nvoid test_fast_input() {\n    std::FILE* file = std::tmpfile();\n\
    \    assert(file != nullptr);\n    std::fputs(\" -123 456 token Z 1\\n\", file);\n\
    \    std::rewind(file);\n\n    m1une::utilities::FastInput input(file);\n    int\
    \ a;\n    unsigned int b;\n    std::string s;\n    char c;\n    bool flag;\n \
    \   assert(input.read(a, b, s, c, flag));\n    assert(a == -123);\n    assert(b\
    \ == 456);\n    assert(s == \"token\");\n    assert(c == 'Z');\n    assert(flag);\n\
    \    std::fclose(file);\n}\n\nvoid test_fast_output() {\n    std::FILE* file =\
    \ std::tmpfile();\n    assert(file != nullptr);\n\n    {\n        m1une::utilities::FastOutput\
    \ output(file);\n        output.println(\"answer\", -42, 17u);\n        output.println(false);\n\
    \        output.flush();\n    }\n\n    std::rewind(file);\n    char buffer[64];\n\
    \    std::size_t length = std::fread(buffer, 1, sizeof(buffer), file);\n    std::string\
    \ result(buffer, buffer + length);\n    assert(result == \"answer -42 17\\n0\\\
    n\");\n    std::fclose(file);\n}\n\nint main() {\n    test_fast_input();\n   \
    \ test_fast_output();\n\n    m1une::utilities::FastInput input;\n    m1une::utilities::FastOutput\
    \ output;\n\n    long long a, b;\n    input.read(a, b);\n    output.println(a\
    \ + b);\n}\n"
  dependsOn:
  - utilities/fast_io.hpp
  isVerificationFile: true
  path: verify/utilities/fast_io.test.cpp
  requiredBy: []
  timestamp: '2026-06-27 04:39:45+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/utilities/fast_io.test.cpp
layout: document
redirect_from:
- /verify/verify/utilities/fast_io.test.cpp
- /verify/verify/utilities/fast_io.test.cpp.html
title: verify/utilities/fast_io.test.cpp
---
