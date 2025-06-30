#!/usr/bin/env python3
"""
Check C source and header files for coding norm violations:
 - Max 5 functions per file
 - Max 25 lines per function
Usage: python3 scripts/check_norm.py
"""
import os
import re
import sys

MAX_FUNCS_PER_FILE = 5
MAX_LINES_PER_FUNCTION = 25

# Pattern to detect function definitions (simple heuristic)
func_def_pattern = re.compile(r'^[a-zA-Z_][a-zA-Z0-9_ \t\*]*\([^;]*\)\s*\{')

def check_file(path):
    violations = []
    with open(path, 'r') as f:
        lines = f.readlines()
    funcs = []
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        if func_def_pattern.match(line) and not line.strip().startswith('//') and not line.strip().startswith('*'):
            # Found a function definition
            start = i
            nesting = line.count('{') - line.count('}')
            j = i + 1
            # Find matching closing brace
            while j < n and nesting > 0:
                nesting += lines[j].count('{') - lines[j].count('}')
                j += 1
            end = j
            length = end - start
            # Extract function name
            name_match = re.match(r'^[a-zA-Z_][a-zA-Z0-9_ \t\*]*\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*\(', line)
            name = name_match.group(1) if name_match else '<unknown>'
            funcs.append((name, start+1, end, length))
            i = j
        else:
            i += 1
    # Check count
    if len(funcs) > MAX_FUNCS_PER_FILE:
        violations.append(f"{path}: {len(funcs)} functions (max {MAX_FUNCS_PER_FILE})")
    # Check each function length
    for name, start, end, length in funcs:
        if length > MAX_LINES_PER_FUNCTION:
            violations.append(
                f"{path}:{start}-{end} function '{name}' is {length} lines (max {MAX_LINES_PER_FUNCTION})"
            )
    return violations

def main():
    has_violation = False
    for root, dirs, files in os.walk('.'):
        # Skip hidden directories
        dirs[:] = [d for d in dirs if not d.startswith('.')]
        for fname in files:
            if fname.endswith(('.c', '.h')):
                path = os.path.join(root, fname)
                v = check_file(path)
                if v:
                    has_violation = True
                    for msg in v:
                        print(msg)
    if has_violation:
        sys.exit(1)

if __name__ == '__main__':
    main()
