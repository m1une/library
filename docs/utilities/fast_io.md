---
title: Fast IO
documentation_of: ../../utilities/fast_io.hpp
---

## Overview

`FastInput` and `FastOutput` provide buffered C-style input and output for
large competitive-programming data. They are useful when standard iostreams are
too slow even with synchronization disabled.

Both classes default to `stdin` or `stdout`, and can also be constructed from a
custom `std::FILE*`.

In addition to scalar values, this library supports pre-sized nested ranges such
as `std::vector<T>`, `std::vector<std::vector<T>>`, and higher-dimensional
vectors. This makes it possible to read and write arrays, matrices, and tensors
without writing explicit loops.

## Classes

All names are in `m1une::utilities`.

| Class | Description |
| --- | --- |
| `FastInput` | Buffered scanner for whitespace-separated tokens. |
| `FastOutput` | Buffered writer. The destructor flushes pending output. |

## Supported Types

### Scalar types

`FastInput::read` supports the following scalar types.

| Type | Behavior |
| --- | --- |
| Integral types except `bool` and `char` | Reads a signed or unsigned integer token. |
| `bool` | Reads an integer token and stores whether it is nonzero. |
| `char` | Reads the next non-whitespace character. |
| `std::string` | Reads the next whitespace-separated token. |
| ModInt-like types | Reads a `long long` token and constructs `T(x)`. |

A ModInt-like type means a type that has a `val()` member function. For example,
`m1une::math::ModInt<998244353>` can be read directly as long as it can be
constructed from an integer.

`FastOutput::write` supports the following scalar types.

| Type | Behavior |
| --- | --- |
| Integral types except `bool` and `char` | Writes the decimal representation. |
| `bool` | Writes `1` or `0`. |
| `char` | Writes the character itself. |
| `const char*` | Writes the null-terminated string. |
| `std::string` | Writes the string. |
| ModInt-like types | Writes `value.val()`. |

`FastOutput` does not use `std::ostream`, so `operator<<` overloads are not used.
For ModInt-like types, output is handled through `val()`.

### Range types

A range type is a type for which `std::begin(x)` and `std::end(x)` are valid.
`std::string` and C strings are treated as scalar string types, not as ranges.

The main intended use is pre-sized vectors.

```cpp
std::vector<int> a(n);
input.read(a);

std::vector<std::vector<int>> b(h, std::vector<int>(w));
input.read(b);

std::vector<std::vector<std::vector<int>>> c(
    x, std::vector<std::vector<int>>(y, std::vector<int>(z))
);
input.read(c);
```

The size must already be determined before calling `read`. `read(range)` does
not resize the range.

Nested ranges are read recursively. Therefore, a `vector<vector<T>>` reads all
of its elements in row-major order, and a higher-dimensional vector reads all
leaf scalar values in the natural nested-loop order.

## FastInput Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `FastInput(std::FILE* stream = stdin)` | Constructs an input scanner. | $O(1)$ |
| `int read_char_raw()` | Reads one raw byte, including whitespace, or `EOF`. | Amortized $O(1)$ |
| `bool skip_spaces()` | Skips bytes `<= ' '` and leaves the first non-space byte unread. | Linear in skipped bytes |
| `bool read(T& value)` | Reads an integral value, `bool`, `char`, `std::string`, or ModInt-like value. | Linear in token length |
| `bool read(range)` | Reads all elements of a pre-sized range recursively. | Linear in total token length |
| `bool read(a, b, ...)` | Reads multiple values from left to right. | Linear in total token length |

## FastOutput Methods

| Method | Description | Complexity |
| --- | --- | --- |
| `FastOutput(std::FILE* stream = stdout)` | Constructs an output writer. | $O(1)$ |
| `void flush()` | Writes pending buffered bytes. | Linear in buffered bytes |
| `void write_char(char c)` | Writes one character. | Amortized $O(1)$ |
| `void write(value)` | Writes an integral value, `bool`, `char`, C-string, `std::string`, or ModInt-like value. | Linear in output length |
| `void write(range)` | Writes all elements of a range recursively. | Linear in output length |
| `void print(a, b, ...)` | Writes values separated by one space. | Linear in output length |
| `void println()` | Writes a newline. | Amortized $O(1)$ |
| `void println(a, b, ...)` | Writes values separated by one space, then a newline. | Linear in output length |

## Range Output Format

One-dimensional ranges are written with spaces between elements.

```cpp
std::vector<int> a = {1, 2, 3};
output.println(a);
```

```text
1 2 3
```

Nested ranges are written recursively. If the child element is itself a range,
children are separated by newlines instead of spaces.

```cpp
std::vector<std::vector<int>> b = {
    {1, 2, 3},
    {4, 5, 6},
};
output.println(b);
```

```text
1 2 3
4 5 6
```

For three or more dimensions, every innermost one-dimensional range is printed
as one line. No blank line is inserted between higher-dimensional blocks.

```cpp
std::vector<std::vector<std::vector<int>>> c(2);
c[0].push_back({1, 2});
c[0].push_back({3, 4});
c[1].push_back({5, 6});
c[1].push_back({7, 8});
output.println(c);
```

```text
1 2
3 4
5 6
7 8
```

For multidimensional output, calling `println(range)` on the range alone is
recommended. Combining a nested range with other arguments in the same `print` or
`println` call is supported by overload resolution, but the formatting can be
harder to read.

## Notes

Input parsing is whitespace-separated. `read(char&)` returns the next
non-whitespace character, while `read_char_raw()` can be used when whitespace is
significant.

`read(range)` requires the range to have its final size before reading. For
example, call `input.read(n)` first, then construct `std::vector<T> a(n)`, then
call `input.read(a)`.

`std::vector<bool>` is supported. It is read and written as `bool` values using
integer tokens and `1`/`0` output.

`FastOutput` flushes in its destructor, but calling `flush()` explicitly is
useful before reading back from a custom file handle.

## Example

```cpp
#include "utilities/fast_io.hpp"

using m1une::utilities::FastInput;
using m1une::utilities::FastOutput;

int main() {
    FastInput input;
    FastOutput output;

    int n;
    input.read(n);

    std::vector<long long> a(n);
    input.read(a);

    long long sum = 0;
    for (long long x : a) sum += x;

    output.println(sum);
    output.println(a);
}
```

## Multidimensional Vector Example

```cpp
#include "utilities/fast_io.hpp"

using m1une::utilities::FastInput;
using m1une::utilities::FastOutput;

int main() {
    FastInput input;
    FastOutput output;

    int h, w;
    input.read(h, w);

    std::vector<std::vector<int>> a(h, std::vector<int>(w));
    input.read(a);

    output.println(a);
}
```

Input:

```text
2 3
1 2 3
4 5 6
```

Output:

```text
1 2 3
4 5 6
```
