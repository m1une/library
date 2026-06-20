---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: py
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/home/runner/.local/lib/python3.12/site-packages/onlinejudge_verify/languages/python.py\"\
    , line 96, in bundle\n    raise NotImplementedError\nNotImplementedError\n"
  code: "#!/usr/bin/env python3\nimport os\nimport re\nfrom pathlib import Path\n\n\
    root = Path(__file__).resolve().parents[1]\npattern = re.compile(r'(#include\\\
    s*\")([^\"]+)(\")')\n\nexts = {'.hpp', '.h', '.cpp', '.cc', '.md'}\n\nchanged\
    \ = []\nfor dirpath, dirnames, filenames in os.walk(root):\n    for fname in filenames:\n\
    \        if Path(fname).suffix.lower() not in exts:\n            continue\n  \
    \      fpath = Path(dirpath) / fname\n        relstart = fpath.parent\n      \
    \  text = fpath.read_text(encoding='utf-8')\n        new_text = text\n       \
    \ def repl(m):\n            full = m.group(2)\n            if '/' not in full:\n\
    \                return m.group(0)\n            target = (root / full).resolve()\n\
    \            if not target.exists():\n                return m.group(0)\n    \
    \        rel = os.path.relpath(str(target), start=str(relstart))\n           \
    \ rel = rel.replace(os.path.sep, '/')\n            return m.group(1) + rel + m.group(3)\n\
    \        new_text = pattern.sub(repl, text)\n        if new_text != text:\n  \
    \          fpath.write_text(new_text, encoding='utf-8')\n            changed.append(str(fpath.relative_to(root)))\n\
    \nprint('Updated files:', len(changed))\nfor c in changed:\n    print(c)\n"
  dependsOn: []
  isVerificationFile: false
  path: scripts/fix_includes.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: scripts/fix_includes.py
layout: document
redirect_from:
- /library/scripts/fix_includes.py
- /library/scripts/fix_includes.py.html
title: scripts/fix_includes.py
---
