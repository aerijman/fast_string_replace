## fast_string_replace
### Efficient multi-location string replacement in Python using a C backend

## Overview
fast_string_replace is a Python module that wraps a C implementation to perform multiple string modifications efficiently. Unlike Python’s native str.replace() or re.sub(), this function allows for location-specific replacements in a single pass, minimizing memory allocations and improving performance.

## Features
* Replace multiple substrings at specific positions.
* Single-pass, memory-efficient implementation.
* Ideal for large-scale text processing (e.g., bioinformatics, log parsing).
* Easy-to-use Python interface.

## Installation
pip install fast_string_replace

## Example usage
```python
from fast_string_replace import replace_at_positions

s = "ACGTACGTACGT"
changes = [(0, "T"), (4, "G"), (8, "C")]
new_s = replace_at_positions(s, changes)
print(new_s)  # Output: TCGTGCGTACGT
```

## Performance
Benchmarks show up to 10x speed improvement over native Python methods for large strings with many replacements.

## Build & contribute
git clone https://github.com/aerijman/fast_string_replace.git
cd fast_string_replace
python setup.py install


