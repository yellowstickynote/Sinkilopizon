# Z-Array (Z-function)

**Type:** `ZArray` · **Complexity:** `O(n)`

## Overview

Compute the Z-array (Z-function) of a sequence: for each position `i`,
`z[i]` is the length of the longest substring starting at `i` that is also a
prefix of the sequence. Works on any indexable container with `size()`
(`vector<int>`, `string`, ...). Indices are 0-based.

## API

| Member | Effect |
|--------|--------|
| `ZArray(s)` | Build from a sequence (`vector<int>`, `string`, ...); precomputes `z` via `zarray(s)`. |
| `z` | The computed Z-array of the input (`vector<int>`). |
| `zarray(s)` | *(static)* Compute and return the Z-array for sequence `s`.

## Notes

- `z[0]` is typically `0` (or `|s|` depending on convention); this implementation
  sets it to `0`.
- Complexity is linear: `O(n)` time and `O(n)` memory.
