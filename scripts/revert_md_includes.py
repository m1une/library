#!/usr/bin/env python3
import os
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
pattern = re.compile(r'(#include\s*")([^"]+)(")')

changed = []
for md in root.rglob('*.md'):
    text = md.read_text(encoding='utf-8')
    new_text = text
    def repl(m):
        path_str = m.group(2)
        # Only touch includes that contain path separators or parent refs
        if '/' not in path_str and '..' not in path_str:
            return m.group(0)
        # Resolve the include relative to the markdown file
        target = (md.parent / path_str).resolve()
        if not target.exists():
            return m.group(0)
        # Compute path relative to repo root
        rel = os.path.relpath(str(target), start=str(root)).replace(os.path.sep, '/')
        return m.group(1) + rel + m.group(3)
    new_text = pattern.sub(repl, text)
    if new_text != text:
        md.write_text(new_text, encoding='utf-8')
        changed.append(str(md.relative_to(root)))

print('Reverted includes in', len(changed), 'markdown files')
for c in changed:
    print(c)
