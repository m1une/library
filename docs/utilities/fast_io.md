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
