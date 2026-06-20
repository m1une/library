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
    s*\")([^\"]+)(\")')\n\nchanged = []\nfor md in root.rglob('*.md'):\n    text =\
    \ md.read_text(encoding='utf-8')\n    new_text = text\n    def repl(m):\n    \
    \    path_str = m.group(2)\n        # Only touch includes that contain path separators\
    \ or parent refs\n        if '/' not in path_str and '..' not in path_str:\n \
    \           return m.group(0)\n        # Resolve the include relative to the markdown\
    \ file\n        target = (md.parent / path_str).resolve()\n        if not target.exists():\n\
    \            return m.group(0)\n        # Compute path relative to repo root\n\
    \        rel = os.path.relpath(str(target), start=str(root)).replace(os.path.sep,\
    \ '/')\n        return m.group(1) + rel + m.group(3)\n    new_text = pattern.sub(repl,\
    \ text)\n    if new_text != text:\n        md.write_text(new_text, encoding='utf-8')\n\
    \        changed.append(str(md.relative_to(root)))\n\nprint('Reverted includes\
    \ in', len(changed), 'markdown files')\nfor c in changed:\n    print(c)\n"
  dependsOn: []
  isVerificationFile: false
  path: scripts/revert_md_includes.py
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: scripts/revert_md_includes.py
layout: document
redirect_from:
- /library/scripts/revert_md_includes.py
- /library/scripts/revert_md_includes.py.html
title: scripts/revert_md_includes.py
---
