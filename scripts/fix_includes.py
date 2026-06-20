#!/usr/bin/env python3
import os
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
pattern = re.compile(r'(#include\s*")([^"]+)(")')

exts = {'.hpp', '.h', '.cpp', '.cc', '.md'}

changed = []
for dirpath, dirnames, filenames in os.walk(root):
    for fname in filenames:
        if Path(fname).suffix.lower() not in exts:
            continue
        fpath = Path(dirpath) / fname
        relstart = fpath.parent
        text = fpath.read_text(encoding='utf-8')
        new_text = text
        def repl(m):
            full = m.group(2)
            if '/' not in full:
                return m.group(0)
            target = (root / full).resolve()
            if not target.exists():
                return m.group(0)
            rel = os.path.relpath(str(target), start=str(relstart))
            rel = rel.replace(os.path.sep, '/')
            return m.group(1) + rel + m.group(3)
        new_text = pattern.sub(repl, text)
        if new_text != text:
            fpath.write_text(new_text, encoding='utf-8')
            changed.append(str(fpath.relative_to(root)))

print('Updated files:', len(changed))
for c in changed:
    print(c)
