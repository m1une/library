---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/opt/hostedtoolcache/Python/3.13.7/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../../data_structure/treap.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/ordered_set\"\n\n#include\
    \ <iostream>\n#include <vector>\n\n#include \"../../data_structure/treap.hpp\"\
    \n\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n    std::cin.tie(NULL);\n\
    }\n\nint main() {\n    fast_io();\n    int N, Q;\n    std::cin >> N >> Q;\n\n\
    \    m1une::treap<int> tr;\n    for (int i = 0; i < N; ++i) {\n        int a;\n\
    \        std::cin >> a;\n        tr.insert(a);\n    }\n\n    for (int q = 0; q\
    \ < Q; ++q) {\n        int type, k;\n        std::cin >> type >> k;\n        if\
    \ (type == 0) {\n            if (!tr.contains(k)) {\n                tr.insert(k);\n\
    \            }\n        } else if (type == 1) {\n            if (tr.contains(k))\
    \ {\n                tr.erase(k);\n            }\n        } else if (type == 2)\
    \ {\n            // Find k-th smallest (0-indexed)\n            if (tr.size()\
    \ < k) {\n                std::cout << -1 << \"\\n\";\n            } else {\n\
    \                std::cout << tr.find_by_order(k - 1) << \"\\n\";\n          \
    \  }\n        } else if (type == 3) {\n            // Find number of elements\
    \ <= k\n            // This is the same as the rank of k+1\n            std::cout\
    \ << tr.order_of_key(k + 1) << \"\\n\";\n        } else if (type == 4) {\n   \
    \         // Find largest element <= k (predecessor)\n            int order =\
    \ tr.order_of_key(k + 1);\n            if (order == 0) {\n                std::cout\
    \ << -1 << \"\\n\";\n            } else {\n                std::cout << tr.find_by_order(order\
    \ - 1) << \"\\n\";\n            }\n        } else if (type == 5) {\n         \
    \   // Find smallest element >= k (successor)\n            auto res = tr.lower_bound(k);\n\
    \            if (res) {\n                std::cout << *res << \"\\n\";\n     \
    \       } else {\n                std::cout << -1 << \"\\n\";\n            }\n\
    \        }\n    }\n\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: verify/data_structure/treap.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/data_structure/treap.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/treap.test.cpp
- /verify/verify/data_structure/treap.test.cpp.html
title: verify/data_structure/treap.test.cpp
---
