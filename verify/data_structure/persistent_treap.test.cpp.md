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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: ../../data_structure/persistent_treap.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\n\
    #include \"../../data_structure/persistent_treap.hpp\"\n\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\n\n// Fast I/O\nvoid fast_io() {\n    std::ios_base::sync_with_stdio(false);\n\
    \    std::cin.tie(NULL);\n}\n\nint main() {\n    fast_io();\n    int N, Q;\n \
    \   std::cin >> N >> Q;\n    std::vector<int> a(N);\n    std::vector<int> distinct_elements;\n\
    \n    for (int i = 0; i < N; ++i) {\n        std::cin >> a[i];\n        distinct_elements.push_back(a[i]);\n\
    \    }\n\n    // Coordinate Compression\n    std::sort(distinct_elements.begin(),\
    \ distinct_elements.end());\n    distinct_elements.erase(std::unique(distinct_elements.begin(),\
    \ distinct_elements.end()), distinct_elements.end());\n\n    auto get_compressed_rank\
    \ = [&](int val) {\n        return std::lower_bound(distinct_elements.begin(),\
    \ distinct_elements.end(), val) - distinct_elements.begin();\n    };\n\n    //\
    \ Build a persistent treap for each prefix of the array\n    std::vector<m1une::persistent_treap<int>>\
    \ versions(N + 1);\n    for (int i = 0; i < N; ++i) {\n        versions[i + 1]\
    \ = versions[i].insert(get_compressed_rank(a[i]));\n    }\n\n    for (int q =\
    \ 0; q < Q; ++q) {\n        int l, r, k;\n        std::cin >> l >> r >> k;\n\n\
    \        // Meguru-style Binary Search\n        // We are looking for the smallest\
    \ rank 'ok' such that the number of elements\n        // in a[l..r-1] with rank\
    \ <= 'ok' is strictly greater than k.\n        int ng = -1;                  \
    \          // 'ng' is a rank that is always \"not good enough\"\n        int ok\
    \ = distinct_elements.size() - 1;  // 'ok' is a rank that is \"good enough\"\n\
    \n        while (std::abs(ok - ng) > 1) {\n            int mid = ng + (ok - ng)\
    \ / 2;\n\n            // Count elements in the range a[l..r-1] with a compressed\
    \ rank <= mid\n            int count_le = versions[r].order_of_key(mid + 1) -\
    \ versions[l].order_of_key(mid + 1);\n\n            if (count_le > k) {\n    \
    \            // mid is a possible answer, try for a smaller one\n            \
    \    ok = mid;\n            } else {\n                // mid is not the answer,\
    \ we need a larger rank\n                ng = mid;\n            }\n        }\n\
    \n        // The answer is the original value corresponding to the 'ok' rank\n\
    \        std::cout << distinct_elements[ok] << \"\\n\";\n    }\n\n    return 0;\n\
    }\n"
  dependsOn: []
  isVerificationFile: true
  path: verify/data_structure/persistent_treap.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: verify/data_structure/persistent_treap.test.cpp
layout: document
redirect_from:
- /verify/verify/data_structure/persistent_treap.test.cpp
- /verify/verify/data_structure/persistent_treap.test.cpp.html
title: verify/data_structure/persistent_treap.test.cpp
---
