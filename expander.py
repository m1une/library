import sys
import os
import re

INCLUDE_PATHS = ['.', os.path.expanduser('~/Desktop/atcoder/library')] # replace this with /path/to/library
visited = set()

def resolve_include(header):
    for path in INCLUDE_PATHS:
        full_path = os.path.join(path, header)
        if os.path.isfile(full_path):
            return os.path.abspath(full_path)
    return None

def expand_file(path, display_name=None, caller_file=None, caller_line=None):
    abs_path = os.path.abspath(path)
    if abs_path in visited:
        return
    visited.add(abs_path)

    if display_name is None:
        display_name = os.path.basename(path)

    print(f'// BEGIN: {display_name}')
    print(f'#line 1 "{display_name}"')  # add `#line` at the start of file

    with open(path) as f:
        for i, line in enumerate(f, start=1):
            if line.strip() == "#pragma once":
                continue

            m = re.match(r'#\s*include\s*"([^"]+)"', line)
            if m:
                header = m.group(1)
                resolved = resolve_include(header)
                if resolved:
                    if resolved not in visited:
                        expand_file(resolved, header, display_name, i + 1)
                    print(f'#line {i + 1} "{display_name}"')  # file ended and return to the previous file
                else:
                    print(f'// [warning] include not found: {header}')
            elif re.match(r'#\s*include\s*<[^>]+>', line):
                print(line, end='')
            else:
                print(line, end='')

    print(f'// END: {display_name}')

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python3 expander.py main.cpp > singlefile.cpp")
        sys.exit(1)

    expand_file(sys.argv[1])
