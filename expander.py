import sys
import os
import re

INCLUDE_PATHS = ['.']
# INCLUDE_PATHS = ['.', os.path.expanduser('/path/to/the/library')]
visited = set()

def resolve_include(header):
    """Finds the absolute path for a given header file."""
    for path in INCLUDE_PATHS:
        full_path = os.path.join(path, header)
        if os.path.isfile(full_path):
            return os.path.abspath(full_path)
    return None

def expand_file(path, display_name=None):
    """
    Recursively expands a C++ file by inlining its local #include directives,
    while removing include guards (#pragma once or #ifndef/#define/#endif).
    """
    abs_path = os.path.abspath(path)
    if abs_path in visited:
        return
    visited.add(abs_path)

    if display_name is None:
        display_name = os.path.basename(path)

    print(f'// BEGIN: {display_name}')

    with open(path) as f:
        lines = f.readlines()

    lines_to_skip = set()
    
    # Method 1: Find and mark '#pragma once' to be skipped
    for i, line in enumerate(lines):
        if line.strip() == "#pragma once":
            lines_to_skip.add(i)

    # Method 2: If no '#pragma once', find and mark traditional guards
    if not lines_to_skip and len(lines) >= 2:
        # Find first and second non-empty lines for #ifndef and #define
        first_line_idx, first_line = -1, None
        for i, line in enumerate(lines):
            if line.strip():
                first_line_idx, first_line = i, line
                break
        
        second_line_idx, second_line = -1, None
        if first_line_idx != -1:
            for i in range(first_line_idx + 1, len(lines)):
                if lines[i].strip():
                    second_line_idx, second_line = i, lines[i]
                    break
        
        # Find the last #endif line in the file
        last_endif_idx, last_endif_line = -1, None
        for i in range(len(lines) - 1, -1, -1):
            if lines[i].strip().startswith('#endif'):
                last_endif_idx, last_endif_line = i, lines[i]
                break

        if first_line and second_line and last_endif_line:
            ifndef_match = re.match(r'#\s*ifndef\s+([A-Z0-9_]+)\s*', first_line)
            if ifndef_match:
                guard_macro = ifndef_match.group(1)
                define_pattern = r'#\s*define\s+' + re.escape(guard_macro)
                # Check if the second line is the matching #define
                if re.match(define_pattern, second_line.strip()):
                    lines_to_skip.add(first_line_idx)
                    lines_to_skip.add(second_line_idx)
                    lines_to_skip.add(last_endif_idx)

    # Process and print the file content
    first_line_emitted = False
    for i, line in enumerate(lines):
        if i in lines_to_skip:
            continue
        
        # Emit the #line directive before the first line of actual code
        if not first_line_emitted:
            print(f'#line {i + 1} "{display_name}"')
            first_line_emitted = True
            
        m = re.match(r'#\s*include\s*"([^"]+)"', line)
        if m:
            header = m.group(1)
            resolved = resolve_include(header)
            if resolved:
                expand_file(resolved, header)
                # After inlining, reset the line number back to the current file
                print(f'#line {i + 2} "{display_name}"')
            else:
                print(f'// [warning] include not found: {header}')
                print(line, end='')
        else:
            print(line, end='')

    print(f'// END: {display_name}')

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print("Usage: python3 expander.py <main_file.cpp> > bundled_file.cpp", file=sys.stderr)
        sys.exit(1)

    expand_file(sys.argv[1])
