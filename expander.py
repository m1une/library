import sys
import os
import re

LIBRARY_ROOT = os.path.abspath(os.path.dirname(__file__))
INCLUDE_PATHS = ['.', LIBRARY_ROOT]
visited = set()

def resolve_include(header, current_file_dir):
    """
    Finds the absolute path for a given header file.
    It first checks relative to the current file's directory,
    then checks the global include paths.
    """
    relative_path = os.path.join(current_file_dir, header)
    if os.path.isfile(relative_path):
        return os.path.abspath(relative_path)
    
    for path in INCLUDE_PATHS:
        full_path = os.path.join(path, header)
        if os.path.isfile(full_path):
            return os.path.abspath(full_path)
    return None

def expand_file(path, display_name=None):
    """
    Recursively expands a C++ file by inlining its local #include directives.
    It removes include guards and skips #ifdef LOCAL blocks.
    """
    abs_path = os.path.abspath(path)
    if abs_path in visited:
        return
    visited.add(abs_path)

    if display_name is None:
        display_name = os.path.relpath(path, LIBRARY_ROOT)

    print(f'// BEGIN: {display_name}')

    with open(path) as f:
        lines = f.readlines()

    # --- Pre-processing Step: Identify lines to skip ---
    lines_to_skip = set()
    
    # Identify and mark include guards for removal
    if lines:
        # Method 1: #pragma once
        for i, line in enumerate(lines):
            if line.strip() == "#pragma once":
                lines_to_skip.add(i)
                break
        
        # Method 2: #ifndef/#define/#endif guards
        if not lines_to_skip and len(lines) >= 2:
            first_line_idx, first_line = -1, ""
            for i, line in enumerate(lines):
                if line.strip():
                    first_line_idx, first_line = i, line
                    break
            
            second_line_idx, second_line = -1, ""
            if first_line_idx != -1:
                for i in range(first_line_idx + 1, len(lines)):
                    if lines[i].strip():
                        second_line_idx, second_line = i, lines[i]
                        break
            
            last_endif_idx = -1
            for i in range(len(lines) - 1, -1, -1):
                if lines[i].strip().startswith('#endif'):
                    last_endif_idx = i
                    break

            if first_line_idx != -1 and second_line_idx != -1 and last_endif_idx != -1:
                ifndef_match = re.match(r'#\s*ifndef\s+([A-Z0-9_]+)\s*', first_line)
                if ifndef_match:
                    guard_macro = ifndef_match.group(1)
                    define_pattern = r'#\s*define\s+' + re.escape(guard_macro)
                    if re.match(define_pattern, second_line.strip()):
                        lines_to_skip.add(first_line_idx)
                        lines_to_skip.add(second_line_idx)
                        lines_to_skip.add(last_endif_idx)

    # --- Main Processing Loop ---
    first_line_emitted = False
    local_block_state = 0  # 0: normal, 1: skipping #ifdef LOCAL, 2: in #else of LOCAL
    current_file_dir = os.path.dirname(path)

    for i, line in enumerate(lines):
        stripped_line = line.strip()

        # Handle #ifdef LOCAL state machine
        if stripped_line.startswith('#ifdef LOCAL'):
            local_block_state = 1
            continue
        elif stripped_line.startswith('#else') and local_block_state == 1:
            local_block_state = 2
            continue
        elif stripped_line.startswith('#endif') and (local_block_state == 1 or local_block_state == 2):
            local_block_state = 0
            continue
        
        if local_block_state == 1: # Skip lines inside #ifdef LOCAL
            continue
            
        if i in lines_to_skip: # Skip include guard lines
            continue
        
        if not first_line_emitted:
            print(f'#line {i + 1} "{display_name}"')
            first_line_emitted = True
            
        m = re.match(r'#\s*include\s*"([^"]+)"', stripped_line)
        if m:
            header = m.group(1)
            resolved = resolve_include(header, current_file_dir)
            if resolved:
                expand_file(resolved, header)
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
