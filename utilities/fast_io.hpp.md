---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/fast_io.test.cpp
    title: verify/utilities/fast_io.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/fast_io.hpp\"\n\n\n\n#include <cstdio>\n#include\
    \ <string>\n#include <type_traits>\n\nnamespace m1une {\nnamespace utilities {\n\
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
    \   }\n        return true;\n    }\n\n    template <class First, class Second,\
    \ class... Rest>\n    bool read(First& first, Second& second, Rest&... rest) {\n\
    \        if (!read(first)) return false;\n        return read(second, rest...);\n\
    \    }\n};\n\nstruct FastOutput {\n    static constexpr int buffer_size = 1 <<\
    \ 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n\n   public:\n    explicit FastOutput(std::FILE* stream =\
    \ stdout)\n        : _stream(stream), _position(0) {}\n\n    FastOutput(const\
    \ FastOutput&) = delete;\n    FastOutput& operator=(const FastOutput&) = delete;\n\
    \n    ~FastOutput() {\n        flush();\n    }\n\n    void flush() {\n       \
    \ if (_position == 0) return;\n        std::fwrite(_buffer, 1, _position, _stream);\n\
    \        _position = 0;\n    }\n\n    void write_char(char c) {\n        if (_position\
    \ == buffer_size) flush();\n        _buffer[_position++] = c;\n    }\n\n    void\
    \ write(const char* s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\
    \n    void write(const std::string& s) {\n        for (char c : s) write_char(c);\n\
    \    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\n    void\
    \ write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<\n        std::is_integral_v<T>\n          \
    \  && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n\
    \        if constexpr (std::is_signed_v<Raw>) {\n            if (value < 0) {\n\
    \                write_char('-');\n                magnitude = Unsigned(0) - Unsigned(value);\n\
    \            } else {\n                magnitude = Unsigned(value);\n        \
    \    }\n        } else {\n            magnitude = value;\n        }\n\n      \
    \  if (magnitude == 0) {\n            write_char('0');\n            return;\n\
    \        }\n\n        char digits[64];\n        int count = 0;\n        while\
    \ (magnitude > 0) {\n            digits[count++] = char('0' + magnitude % 10);\n\
    \            magnitude /= 10;\n        }\n        while (count--) write_char(digits[count]);\n\
    \    }\n\n    template <class First, class... Rest>\n    void print(const First&\
    \ first, const Rest&... rest) {\n        write(first);\n        ((write_char('\
    \ '), write(rest)), ...);\n    }\n\n    void println() {\n        write_char('\\\
    n');\n    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_FAST_IO_HPP\n#define M1UNE_FAST_IO_HPP 1\n\n#include <cstdio>\n\
    #include <string>\n#include <type_traits>\n\nnamespace m1une {\nnamespace utilities\
    \ {\n\nstruct FastInput {\n    static constexpr int buffer_size = 1 << 20;\n\n\
    \   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n    int\
    \ _position;\n    int _length;\n\n   public:\n    explicit FastInput(std::FILE*\
    \ stream = stdin)\n        : _stream(stream), _position(0), _length(0) {}\n\n\
    \    FastInput(const FastInput&) = delete;\n    FastInput& operator=(const FastInput&)\
    \ = delete;\n\n    int read_char_raw() {\n        if (_position == _length) {\n\
    \            _length = int(std::fread(_buffer, 1, buffer_size, _stream));\n  \
    \          _position = 0;\n            if (_length == 0) return EOF;\n       \
    \ }\n        return _buffer[_position++];\n    }\n\n    bool skip_spaces() {\n\
    \        int c = read_char_raw();\n        while (c != EOF && c <= ' ') c = read_char_raw();\n\
    \        if (c == EOF) return false;\n        --_position;\n        return true;\n\
    \    }\n\n    bool read(char& value) {\n        if (!skip_spaces()) return false;\n\
    \        value = char(read_char_raw());\n        return true;\n    }\n\n    bool\
    \ read(std::string& value) {\n        if (!skip_spaces()) return false;\n    \
    \    value.clear();\n        int c = read_char_raw();\n        while (c != EOF\
    \ && c > ' ') {\n            value.push_back(char(c));\n            c = read_char_raw();\n\
    \        }\n        return true;\n    }\n\n    bool read(bool& value) {\n    \
    \    int x;\n        if (!read(x)) return false;\n        value = x != 0;\n  \
    \      return true;\n    }\n\n    template <class T>\n    std::enable_if_t<\n\
    \        std::is_integral_v<T>\n            && !std::is_same_v<std::remove_cv_t<T>,\
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
    \   }\n        return true;\n    }\n\n    template <class First, class Second,\
    \ class... Rest>\n    bool read(First& first, Second& second, Rest&... rest) {\n\
    \        if (!read(first)) return false;\n        return read(second, rest...);\n\
    \    }\n};\n\nstruct FastOutput {\n    static constexpr int buffer_size = 1 <<\
    \ 20;\n\n   private:\n    std::FILE* _stream;\n    char _buffer[buffer_size];\n\
    \    int _position;\n\n   public:\n    explicit FastOutput(std::FILE* stream =\
    \ stdout)\n        : _stream(stream), _position(0) {}\n\n    FastOutput(const\
    \ FastOutput&) = delete;\n    FastOutput& operator=(const FastOutput&) = delete;\n\
    \n    ~FastOutput() {\n        flush();\n    }\n\n    void flush() {\n       \
    \ if (_position == 0) return;\n        std::fwrite(_buffer, 1, _position, _stream);\n\
    \        _position = 0;\n    }\n\n    void write_char(char c) {\n        if (_position\
    \ == buffer_size) flush();\n        _buffer[_position++] = c;\n    }\n\n    void\
    \ write(const char* s) {\n        while (*s != '\\0') write_char(*s++);\n    }\n\
    \n    void write(const std::string& s) {\n        for (char c : s) write_char(c);\n\
    \    }\n\n    void write(char c) {\n        write_char(c);\n    }\n\n    void\
    \ write(bool value) {\n        write_char(value ? '1' : '0');\n    }\n\n    template\
    \ <class T>\n    std::enable_if_t<\n        std::is_integral_v<T>\n          \
    \  && !std::is_same_v<std::remove_cv_t<T>, bool>\n            && !std::is_same_v<std::remove_cv_t<T>,\
    \ char>\n    >\n    write(T value) {\n        using Raw = std::remove_cv_t<T>;\n\
    \        using Unsigned = std::make_unsigned_t<Raw>;\n\n        Unsigned magnitude;\n\
    \        if constexpr (std::is_signed_v<Raw>) {\n            if (value < 0) {\n\
    \                write_char('-');\n                magnitude = Unsigned(0) - Unsigned(value);\n\
    \            } else {\n                magnitude = Unsigned(value);\n        \
    \    }\n        } else {\n            magnitude = value;\n        }\n\n      \
    \  if (magnitude == 0) {\n            write_char('0');\n            return;\n\
    \        }\n\n        char digits[64];\n        int count = 0;\n        while\
    \ (magnitude > 0) {\n            digits[count++] = char('0' + magnitude % 10);\n\
    \            magnitude /= 10;\n        }\n        while (count--) write_char(digits[count]);\n\
    \    }\n\n    template <class First, class... Rest>\n    void print(const First&\
    \ first, const Rest&... rest) {\n        write(first);\n        ((write_char('\
    \ '), write(rest)), ...);\n    }\n\n    void println() {\n        write_char('\\\
    n');\n    }\n\n    template <class... Args>\n    void println(const Args&... args)\
    \ {\n        print(args...);\n        write_char('\\n');\n    }\n};\n\n}  // namespace\
    \ utilities\n}  // namespace m1une\n\n#endif  // M1UNE_FAST_IO_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/fast_io.hpp
  requiredBy: []
  timestamp: '2026-06-27 04:09:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/fast_io.test.cpp
documentation_of: utilities/fast_io.hpp
layout: document
title: Fast IO
---

## Overview

`FastInput` and `FastOutput` provide buffered C-style input and output for
large competitive-programming data. They are useful when standard iostreams are
too slow even with synchronization disabled.

Both classes default to `stdin` or `stdout`, and can also be constructed from a
custom `std::FILE*`.

## Classes

All names are in `m1une::utilities`.

| Class | Description |
| --- | --- |
| `FastInput` | Buffered scanner for whitespace-separated tokens. |
| `FastOutput` | Buffered writer. The destructor flushes pending output. |

## FastInput Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `FastInput(std::FILE* stream = stdin)` | Constructs an input scanner. | $O(1)$ |
| `int read_char_raw()` | Reads one raw byte, including whitespace, or `EOF`. | Amortized $O(1)$ |
| `bool skip_spaces()` | Skips bytes `<= ' '` and leaves the first non-space byte unread. | Linear in skipped bytes |
| `bool read(T& value)` | Reads an integral value, `bool`, `char`, or `std::string`. | Linear in token length |
| `bool read(a, b, ...)` | Reads multiple values from left to right. | Linear in total token length |

## FastOutput Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `FastOutput(std::FILE* stream = stdout)` | Constructs an output writer. | $O(1)$ |
| `void flush()` | Writes pending buffered bytes. | Linear in buffered bytes |
| `void write_char(char c)` | Writes one character. | Amortized $O(1)$ |
| `void write(value)` | Writes an integral value, `bool`, `char`, C-string, or `std::string`. | Linear in output length |
| `void print(a, b, ...)` | Writes values separated by one space. | Linear in output length |
| `void println()` | Writes a newline. | Amortized $O(1)$ |
| `void println(a, b, ...)` | Writes values separated by one space, then a newline. | Linear in output length |

## Notes

Input parsing is whitespace-separated. `read(char&)` returns the next
non-whitespace character, while `read_char_raw()` can be used when whitespace is
significant.

`FastOutput` flushes in its destructor, but calling `flush()` explicitly is
useful before reading back from a custom file handle.

## Example

```cpp
#include "utilities/fast_io.hpp"

int main() {
    m1une::utilities::FastInput input;
    m1une::utilities::FastOutput output;

    int n, q;
    input.read(n, q);

    long long sum = 0;
    for (int i = 0; i < n; ++i) {
        long long x;
        input.read(x);
        sum += x;
    }

    output.println(sum, q);
}
```
