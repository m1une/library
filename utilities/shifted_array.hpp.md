---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/utilities/shifted_array.test.cpp
    title: verify/utilities/shifted_array.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"utilities/shifted_array.hpp\"\n\n\n\n#include <stdexcept>\n\
    #include <vector>\n\nnamespace m1une {\n// bool is not allowed\n// if you want\
    \ to use bool, use char instead\ntemplate <typename T>\nstruct shifted_array {\n\
    \   private:\n    long long _offset;\n    long long _step;\n    int _size;\n \
    \   std::vector<T> _data;\n\n   public:\n    // make an array with indices from\
    \ L to R (including both L and R)\n    // [L, R] (closed interval)\n    shifted_array(long\
    \ long L, long long R, T init_value = T(), long long step = 1)\n        : _offset(L),\
    \ _step(step), _size((R - L) / step + 1), _data(_size, init_value) {\n       \
    \ if (step <= 0) {\n            throw std::invalid_argument(\"Step must be positive\"\
    );\n        }\n        if (L > R) {\n            throw std::invalid_argument(\"\
    Left bound must be less than or equal to right bound\");\n        }\n    }\n \
    \   T &operator[](long long i) {\n        int index = (i - _offset) / _step;\n\
    \        if (index < 0 || index >= _size) {\n            throw std::out_of_range(\"\
    Index out of range\");\n        }\n        return _data[index];\n    };\n    const\
    \ T &operator[](long long i) const {\n        int index = (i - _offset) / _step;\n\
    \        if (index < 0 || index >= _size) {\n            throw std::out_of_range(\"\
    Index out of range\");\n        }\n        return _data[index];\n    };\n    long\
    \ long index(long long i) const {\n        int index = (i - _offset) / _step;\n\
    \        if (index < 0 || index >= _size) {\n            throw std::out_of_range(\"\
    Index out of range\");\n        }\n        return index;\n    }\n};\n\n}  // namespace\
    \ m1une\n\n\n"
  code: "#ifndef M1UNE_SHIFTED_ARRAY_HPP\n#define M1UNE_SHIFTED_ARRAY_HPP 1\n\n#include\
    \ <stdexcept>\n#include <vector>\n\nnamespace m1une {\n// bool is not allowed\n\
    // if you want to use bool, use char instead\ntemplate <typename T>\nstruct shifted_array\
    \ {\n   private:\n    long long _offset;\n    long long _step;\n    int _size;\n\
    \    std::vector<T> _data;\n\n   public:\n    // make an array with indices from\
    \ L to R (including both L and R)\n    // [L, R] (closed interval)\n    shifted_array(long\
    \ long L, long long R, T init_value = T(), long long step = 1)\n        : _offset(L),\
    \ _step(step), _size((R - L) / step + 1), _data(_size, init_value) {\n       \
    \ if (step <= 0) {\n            throw std::invalid_argument(\"Step must be positive\"\
    );\n        }\n        if (L > R) {\n            throw std::invalid_argument(\"\
    Left bound must be less than or equal to right bound\");\n        }\n    }\n \
    \   T &operator[](long long i) {\n        int index = (i - _offset) / _step;\n\
    \        if (index < 0 || index >= _size) {\n            throw std::out_of_range(\"\
    Index out of range\");\n        }\n        return _data[index];\n    };\n    const\
    \ T &operator[](long long i) const {\n        int index = (i - _offset) / _step;\n\
    \        if (index < 0 || index >= _size) {\n            throw std::out_of_range(\"\
    Index out of range\");\n        }\n        return _data[index];\n    };\n    long\
    \ long index(long long i) const {\n        int index = (i - _offset) / _step;\n\
    \        if (index < 0 || index >= _size) {\n            throw std::out_of_range(\"\
    Index out of range\");\n        }\n        return index;\n    }\n};\n\n}  // namespace\
    \ m1une\n\n#endif  // M1UNE_SHIFTED_ARRAY_HPP\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/shifted_array.hpp
  requiredBy: []
  timestamp: '2025-09-29 00:53:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/utilities/shifted_array.test.cpp
documentation_of: utilities/shifted_array.hpp
layout: document
redirect_from:
- /library/utilities/shifted_array.hpp
- /library/utilities/shifted_array.hpp.html
title: utilities/shifted_array.hpp
---
