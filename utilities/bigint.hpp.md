---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/basic_utilities.test.cpp
    title: verify/utilities/basic_utilities.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/bigint.hpp\"\n\n\n\n#include <algorithm>\n#include\
    \ <iomanip>\n#include <iostream>\n#include <stdexcept>\n#include <string>\n#include\
    \ <tuple>\n#include <vector>\n\nnamespace m1une {\nnamespace utilities {\n\nstruct\
    \ BigInt {\n    static constexpr int BASE = 1000000000;\n    static constexpr\
    \ int BASE_DIGITS = 9;\n\n    std::vector<int> a;\n    int sign;\n\n    BigInt()\
    \ : sign(1) {}\n\n    BigInt(long long v) {\n        *this = v;\n    }\n\n   \
    \ BigInt(const std::string& s) {\n        read(s);\n    }\n\n    BigInt& operator=(long\
    \ long v) {\n        sign = 1;\n        unsigned long long magnitude = static_cast<unsigned\
    \ long long>(v);\n        if (v < 0) {\n            sign = -1;\n            magnitude\
    \ = 0 - magnitude;\n        }\n        a.clear();\n        for (; magnitude >\
    \ 0; magnitude /= BASE) {\n            a.push_back(int(magnitude % BASE));\n \
    \       }\n        return *this;\n    }\n\n    BigInt& operator=(const std::string&\
    \ s) {\n        read(s);\n        return *this;\n    }\n\n    void trim() {\n\
    \        while (!a.empty() && a.back() == 0) {\n            a.pop_back();\n  \
    \      }\n        if (a.empty()) sign = 1;\n    }\n\n    void read(const std::string&\
    \ s) {\n        sign = 1;\n        a.clear();\n        int pos = 0;\n        while\
    \ (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {\n            if\
    \ (s[pos] == '-') sign = -1;\n            ++pos;\n        }\n        for (int\
    \ i = int(s.size()) - 1; i >= pos; i -= BASE_DIGITS) {\n            int x = 0;\n\
    \            for (int j = std::max(pos, i - BASE_DIGITS + 1); j <= i; ++j) {\n\
    \                x = x * 10 + (s[j] - '0');\n            }\n            a.push_back(x);\n\
    \        }\n        trim();\n    }\n\n    std::string to_string() const {\n  \
    \      if (a.empty()) return \"0\";\n        std::string res = \"\";\n       \
    \ if (sign == -1) res += '-';\n        res += std::to_string(a.back());\n    \
    \    for (int i = (int)a.size() - 2; i >= 0; --i) {\n            std::string block\
    \ = std::to_string(a[i]);\n            res += std::string(BASE_DIGITS - block.length(),\
    \ '0') + block;\n        }\n        return res;\n    }\n\n    bool is_zero() const\
    \ {\n        return a.empty() || (a.size() == 1 && a[0] == 0);\n    }\n\n    BigInt\
    \ operator-() const {\n        BigInt res = *this;\n        if (!is_zero()) res.sign\
    \ = -sign;\n        return res;\n    }\n\n    BigInt abs() const {\n        BigInt\
    \ res = *this;\n        res.sign = 1;\n        return res;\n    }\n\n    friend\
    \ bool operator<(const BigInt& x, const BigInt& y) {\n        if (x.sign != y.sign)\
    \ return x.sign < y.sign;\n        if (x.a.size() != y.a.size()) {\n         \
    \   return (x.sign == 1) ? (x.a.size() < y.a.size()) : (x.a.size() > y.a.size());\n\
    \        }\n        for (int i = (int)x.a.size() - 1; i >= 0; --i) {\n       \
    \     if (x.a[i] != y.a[i]) {\n                return (x.sign == 1) ? (x.a[i]\
    \ < y.a[i]) : (x.a[i] > y.a[i]);\n            }\n        }\n        return false;\n\
    \    }\n\n    friend bool operator>(const BigInt& x, const BigInt& y) {\n    \
    \    return y < x;\n    }\n    friend bool operator<=(const BigInt& x, const BigInt&\
    \ y) {\n        return !(y < x);\n    }\n    friend bool operator>=(const BigInt&\
    \ x, const BigInt& y) {\n        return !(x < y);\n    }\n    friend bool operator==(const\
    \ BigInt& x, const BigInt& y) {\n        return !(x < y) && !(y < x);\n    }\n\
    \    friend bool operator!=(const BigInt& x, const BigInt& y) {\n        return\
    \ x < y || y < x;\n    }\n\n    BigInt& operator+=(const BigInt& other) {\n  \
    \      if (sign != other.sign) return *this -= (-other);\n        for (int i =\
    \ 0, carry = 0; i < (int)std::max(a.size(), other.a.size()) || carry; ++i) {\n\
    \            if (i == (int)a.size()) a.push_back(0);\n            a[i] += carry\
    \ + (i < (int)other.a.size() ? other.a[i] : 0);\n            carry = a[i] >= BASE;\n\
    \            if (carry) a[i] -= BASE;\n        }\n        return *this;\n    }\n\
    \n    BigInt& operator-=(const BigInt& other) {\n        if (sign != other.sign)\
    \ return *this += (-other);\n        if (abs() < other.abs()) {\n            BigInt\
    \ tmp = other;\n            tmp -= *this;\n            *this = tmp;\n        \
    \    sign = -sign;\n            return *this;\n        }\n        for (int i =\
    \ 0, carry = 0; i < (int)other.a.size() || carry; ++i) {\n            a[i] -=\
    \ carry + (i < (int)other.a.size() ? other.a[i] : 0);\n            carry = a[i]\
    \ < 0;\n            if (carry) a[i] += BASE;\n        }\n        trim();\n   \
    \     return *this;\n    }\n\n    BigInt& operator*=(int v) {\n        long long\
    \ multiplier = v;\n        if (multiplier < 0) {\n            sign = -sign;\n\
    \            multiplier = -multiplier;\n        }\n        long long carry = 0;\n\
    \        for (int i = 0; i < (int)a.size() || carry; ++i) {\n            if (i\
    \ == (int)a.size()) a.push_back(0);\n            const long long cur = a[i] *\
    \ multiplier + carry;\n            carry = cur / BASE;\n            a[i] = (int)(cur\
    \ % BASE);\n        }\n        trim();\n        return *this;\n    }\n\n    BigInt&\
    \ operator*=(const BigInt& other) {\n        if (is_zero() || other.is_zero())\
    \ return *this = 0;\n        std::vector<int> res(a.size() + other.a.size());\n\
    \        for (int i = 0; i < (int)a.size(); ++i) {\n            for (int j = 0,\
    \ carry = 0; j < (int)other.a.size() || carry; ++j) {\n                long long\
    \ cur = res[i + j] + a[i] * (long long)(j < (int)other.a.size() ? other.a[j] :\
    \ 0) + carry;\n                carry = (int)(cur / BASE);\n                res[i\
    \ + j] = (int)(cur % BASE);\n            }\n        }\n        a = res;\n    \
    \    sign *= other.sign;\n        trim();\n        return *this;\n    }\n\n  \
    \  friend std::pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1)\
    \ {\n        if (b1.is_zero()) {\n            throw std::domain_error(\"BigInt\
    \ division by zero\");\n        }\n        BigInt a = a1.abs(), b = b1.abs(),\
    \ q, r;\n        q.a.resize(a.a.size());\n        for (int i = (int)a.a.size()\
    \ - 1; i >= 0; --i) {\n            r *= BASE;\n            r += a.a[i];\n    \
    \        int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];\n          \
    \  int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];\n        \
    \    int d = ((long long)BASE * s1 + s2) / b.a.back();\n            r -= b * d;\n\
    \            while (r < 0) {\n                r += b;\n                --d;\n\
    \            }\n            q.a[i] = d;\n        }\n        q.sign = a1.sign *\
    \ b1.sign;\n        r.sign = a1.sign;\n        q.trim();\n        r.trim();\n\
    \        return {q, r};\n    }\n\n    BigInt& operator/=(const BigInt& other)\
    \ {\n        return *this = divmod(*this, other).first;\n    }\n    BigInt& operator%=(const\
    \ BigInt& other) {\n        return *this = divmod(*this, other).second;\n    }\n\
    \n    friend BigInt operator+(BigInt x, const BigInt& y) {\n        return x +=\
    \ y;\n    }\n    friend BigInt operator-(BigInt x, const BigInt& y) {\n      \
    \  return x -= y;\n    }\n    friend BigInt operator*(BigInt x, const BigInt&\
    \ y) {\n        return x *= y;\n    }\n    friend BigInt operator/(BigInt x, const\
    \ BigInt& y) {\n        return x /= y;\n    }\n    friend BigInt operator%(BigInt\
    \ x, const BigInt& y) {\n        return x %= y;\n    }\n\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const BigInt& b) {\n        return os << b.to_string();\n\
    \    }\n\n    friend std::istream& operator>>(std::istream& is, BigInt& b) {\n\
    \        std::string s;\n        if (is >> s) b.read(s);\n        return is;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n\n"
  code: "#ifndef M1UNE_UTILITIES_BIGINT_HPP\n#define M1UNE_UTILITIES_BIGINT_HPP 1\n\
    \n#include <algorithm>\n#include <iomanip>\n#include <iostream>\n#include <stdexcept>\n\
    #include <string>\n#include <tuple>\n#include <vector>\n\nnamespace m1une {\n\
    namespace utilities {\n\nstruct BigInt {\n    static constexpr int BASE = 1000000000;\n\
    \    static constexpr int BASE_DIGITS = 9;\n\n    std::vector<int> a;\n    int\
    \ sign;\n\n    BigInt() : sign(1) {}\n\n    BigInt(long long v) {\n        *this\
    \ = v;\n    }\n\n    BigInt(const std::string& s) {\n        read(s);\n    }\n\
    \n    BigInt& operator=(long long v) {\n        sign = 1;\n        unsigned long\
    \ long magnitude = static_cast<unsigned long long>(v);\n        if (v < 0) {\n\
    \            sign = -1;\n            magnitude = 0 - magnitude;\n        }\n \
    \       a.clear();\n        for (; magnitude > 0; magnitude /= BASE) {\n     \
    \       a.push_back(int(magnitude % BASE));\n        }\n        return *this;\n\
    \    }\n\n    BigInt& operator=(const std::string& s) {\n        read(s);\n  \
    \      return *this;\n    }\n\n    void trim() {\n        while (!a.empty() &&\
    \ a.back() == 0) {\n            a.pop_back();\n        }\n        if (a.empty())\
    \ sign = 1;\n    }\n\n    void read(const std::string& s) {\n        sign = 1;\n\
    \        a.clear();\n        int pos = 0;\n        while (pos < (int)s.size()\
    \ && (s[pos] == '-' || s[pos] == '+')) {\n            if (s[pos] == '-') sign\
    \ = -1;\n            ++pos;\n        }\n        for (int i = int(s.size()) - 1;\
    \ i >= pos; i -= BASE_DIGITS) {\n            int x = 0;\n            for (int\
    \ j = std::max(pos, i - BASE_DIGITS + 1); j <= i; ++j) {\n                x =\
    \ x * 10 + (s[j] - '0');\n            }\n            a.push_back(x);\n       \
    \ }\n        trim();\n    }\n\n    std::string to_string() const {\n        if\
    \ (a.empty()) return \"0\";\n        std::string res = \"\";\n        if (sign\
    \ == -1) res += '-';\n        res += std::to_string(a.back());\n        for (int\
    \ i = (int)a.size() - 2; i >= 0; --i) {\n            std::string block = std::to_string(a[i]);\n\
    \            res += std::string(BASE_DIGITS - block.length(), '0') + block;\n\
    \        }\n        return res;\n    }\n\n    bool is_zero() const {\n       \
    \ return a.empty() || (a.size() == 1 && a[0] == 0);\n    }\n\n    BigInt operator-()\
    \ const {\n        BigInt res = *this;\n        if (!is_zero()) res.sign = -sign;\n\
    \        return res;\n    }\n\n    BigInt abs() const {\n        BigInt res =\
    \ *this;\n        res.sign = 1;\n        return res;\n    }\n\n    friend bool\
    \ operator<(const BigInt& x, const BigInt& y) {\n        if (x.sign != y.sign)\
    \ return x.sign < y.sign;\n        if (x.a.size() != y.a.size()) {\n         \
    \   return (x.sign == 1) ? (x.a.size() < y.a.size()) : (x.a.size() > y.a.size());\n\
    \        }\n        for (int i = (int)x.a.size() - 1; i >= 0; --i) {\n       \
    \     if (x.a[i] != y.a[i]) {\n                return (x.sign == 1) ? (x.a[i]\
    \ < y.a[i]) : (x.a[i] > y.a[i]);\n            }\n        }\n        return false;\n\
    \    }\n\n    friend bool operator>(const BigInt& x, const BigInt& y) {\n    \
    \    return y < x;\n    }\n    friend bool operator<=(const BigInt& x, const BigInt&\
    \ y) {\n        return !(y < x);\n    }\n    friend bool operator>=(const BigInt&\
    \ x, const BigInt& y) {\n        return !(x < y);\n    }\n    friend bool operator==(const\
    \ BigInt& x, const BigInt& y) {\n        return !(x < y) && !(y < x);\n    }\n\
    \    friend bool operator!=(const BigInt& x, const BigInt& y) {\n        return\
    \ x < y || y < x;\n    }\n\n    BigInt& operator+=(const BigInt& other) {\n  \
    \      if (sign != other.sign) return *this -= (-other);\n        for (int i =\
    \ 0, carry = 0; i < (int)std::max(a.size(), other.a.size()) || carry; ++i) {\n\
    \            if (i == (int)a.size()) a.push_back(0);\n            a[i] += carry\
    \ + (i < (int)other.a.size() ? other.a[i] : 0);\n            carry = a[i] >= BASE;\n\
    \            if (carry) a[i] -= BASE;\n        }\n        return *this;\n    }\n\
    \n    BigInt& operator-=(const BigInt& other) {\n        if (sign != other.sign)\
    \ return *this += (-other);\n        if (abs() < other.abs()) {\n            BigInt\
    \ tmp = other;\n            tmp -= *this;\n            *this = tmp;\n        \
    \    sign = -sign;\n            return *this;\n        }\n        for (int i =\
    \ 0, carry = 0; i < (int)other.a.size() || carry; ++i) {\n            a[i] -=\
    \ carry + (i < (int)other.a.size() ? other.a[i] : 0);\n            carry = a[i]\
    \ < 0;\n            if (carry) a[i] += BASE;\n        }\n        trim();\n   \
    \     return *this;\n    }\n\n    BigInt& operator*=(int v) {\n        long long\
    \ multiplier = v;\n        if (multiplier < 0) {\n            sign = -sign;\n\
    \            multiplier = -multiplier;\n        }\n        long long carry = 0;\n\
    \        for (int i = 0; i < (int)a.size() || carry; ++i) {\n            if (i\
    \ == (int)a.size()) a.push_back(0);\n            const long long cur = a[i] *\
    \ multiplier + carry;\n            carry = cur / BASE;\n            a[i] = (int)(cur\
    \ % BASE);\n        }\n        trim();\n        return *this;\n    }\n\n    BigInt&\
    \ operator*=(const BigInt& other) {\n        if (is_zero() || other.is_zero())\
    \ return *this = 0;\n        std::vector<int> res(a.size() + other.a.size());\n\
    \        for (int i = 0; i < (int)a.size(); ++i) {\n            for (int j = 0,\
    \ carry = 0; j < (int)other.a.size() || carry; ++j) {\n                long long\
    \ cur = res[i + j] + a[i] * (long long)(j < (int)other.a.size() ? other.a[j] :\
    \ 0) + carry;\n                carry = (int)(cur / BASE);\n                res[i\
    \ + j] = (int)(cur % BASE);\n            }\n        }\n        a = res;\n    \
    \    sign *= other.sign;\n        trim();\n        return *this;\n    }\n\n  \
    \  friend std::pair<BigInt, BigInt> divmod(const BigInt& a1, const BigInt& b1)\
    \ {\n        if (b1.is_zero()) {\n            throw std::domain_error(\"BigInt\
    \ division by zero\");\n        }\n        BigInt a = a1.abs(), b = b1.abs(),\
    \ q, r;\n        q.a.resize(a.a.size());\n        for (int i = (int)a.a.size()\
    \ - 1; i >= 0; --i) {\n            r *= BASE;\n            r += a.a[i];\n    \
    \        int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];\n          \
    \  int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];\n        \
    \    int d = ((long long)BASE * s1 + s2) / b.a.back();\n            r -= b * d;\n\
    \            while (r < 0) {\n                r += b;\n                --d;\n\
    \            }\n            q.a[i] = d;\n        }\n        q.sign = a1.sign *\
    \ b1.sign;\n        r.sign = a1.sign;\n        q.trim();\n        r.trim();\n\
    \        return {q, r};\n    }\n\n    BigInt& operator/=(const BigInt& other)\
    \ {\n        return *this = divmod(*this, other).first;\n    }\n    BigInt& operator%=(const\
    \ BigInt& other) {\n        return *this = divmod(*this, other).second;\n    }\n\
    \n    friend BigInt operator+(BigInt x, const BigInt& y) {\n        return x +=\
    \ y;\n    }\n    friend BigInt operator-(BigInt x, const BigInt& y) {\n      \
    \  return x -= y;\n    }\n    friend BigInt operator*(BigInt x, const BigInt&\
    \ y) {\n        return x *= y;\n    }\n    friend BigInt operator/(BigInt x, const\
    \ BigInt& y) {\n        return x /= y;\n    }\n    friend BigInt operator%(BigInt\
    \ x, const BigInt& y) {\n        return x %= y;\n    }\n\n    friend std::ostream&\
    \ operator<<(std::ostream& os, const BigInt& b) {\n        return os << b.to_string();\n\
    \    }\n\n    friend std::istream& operator>>(std::istream& is, BigInt& b) {\n\
    \        std::string s;\n        if (is >> s) b.read(s);\n        return is;\n\
    \    }\n};\n\n}  // namespace utilities\n}  // namespace m1une\n\n#endif  // M1UNE_UTILITIES_BIGINT_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/bigint.hpp
  requiredBy: []
  timestamp: '2026-06-20 02:38:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/basic_utilities.test.cpp
documentation_of: utilities/bigint.hpp
layout: document
title: BigInt
---

## Overview

An arbitrary-precision signed integer for competitive programming. Digits are
stored in base $10^9$ blocks.

It supports arithmetic, comparisons, and standard stream input and output.

## Methods

| Method / Operator | Description | Complexity |
| --- | --- | --- |
| `BigInt()` | Initializes the value to `0`. | $O(1)$ |
| `BigInt(long long v)` | Initializes the BigInt from a standard 64-bit integer. | $O(1)$ |
| `BigInt(const std::string& s)` | Parses a base-10 string (with optional `+`/`-` prefix). | $O(N)$ |
| `std::string to_string() const` | Converts the BigInt back to a base-10 string. | $O(N)$ |
| `BigInt abs() const` | Returns the absolute value of the BigInt. | $O(N)$ |
| `operator+`, `operator+=` | Adds two BigInts. | $O(N)$ |
| `operator-`, `operator-=` | Subtracts one BigInt from another. | $O(N)$ |
| `operator*`, `operator*=` | Multiplies two BigInts (Standard Long Multiplication). | $O(N \cdot M)$ |
| `operator/`, `operator/=` | Divides the BigInt by another (Integer division). | $O(N \cdot M)$ |
| `operator%`, `operator%=` | Calculates the remainder of division by another BigInt. | $O(N \cdot M)$ |
| `divmod(a, b)` | Returns `std::pair<BigInt, BigInt>` containing `{a / b, a % b}`. | $O(N \cdot M)$ |
| Relational Operators | `<, >, <=, >=, ==, !=` are all fully supported. | $O(N)$ |
| Stream Operators | `<<` (output) and `>>` (input) integration. | $O(N)$ |

Here, $N$ and $M$ denote the number of base-$10^9$ blocks in the operands.
Division by zero throws `std::domain_error`.

## Example

```cpp
#include "utilities/bigint.hpp"
#include <iostream>

using m1une::utilities::BigInt;

int main() {
    BigInt a("12345678901234567890");
    BigInt b = 987654321;

    BigInt sum = a + b;
    BigInt diff = a - b;
    BigInt prod = a * b;

    // std::pair<BigInt, BigInt>
    auto [quotient, remainder] = divmod(a, b);

    std::cout << "Sum: " << sum << "\n";
    std::cout << "Difference: " << diff << "\n";
    std::cout << "Product: " << prod << "\n";
    std::cout << "Quotient: " << quotient << " R: " << remainder << "\n";

    if (a > b) {
        std::cout << "A is larger!\n";
    }

    return 0;
}
```
