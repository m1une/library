---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../../data_structure/sparse_table.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"../../data_structure/sparse_table.hpp\"\n#include \"../../monoid/min.hpp\"\
    \n\n#include <iostream>\n#include <vector>\n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(NULL);\n}\n\nint main() {\n    fast_io();\n\n    int N, Q;\n\
    \    std::cin >> N >> Q;\n\n    std::vector<long long> A(N);\n    for (int i =\
    \ 0; i < N; ++i) {\n        std::cin >> A[i];\n    }\n\n    m1une::data_structure::SparseTable<m1une::monoid::Min<long\
    \ long>> st(A);\n\n    for (int q = 0; q < Q; ++q) {\n        int l, r;\n    \
    \    std::cin >> l >> r;\n        \n        std::cout << st.prod(l, r) << \"\\\
    n\";\n    }\n\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: verify/data_structure/sparce_table.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/data_structure/sparce_table.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/sparce_table.test.cpp
- /verify/verify/data_structure/sparce_table.test.cpp.html
title: verify/data_structure/sparce_table.test.cpp
---
