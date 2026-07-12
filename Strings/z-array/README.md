# Z-Array (Z-function)

**Type:** `ZArray` · **Complexity:** `O(n)`

## Overview

Compute the Z-array (Z-function) of a sequence: for each position `i`,
`z[i]` is the length of the longest substring starting at `i` that is also a
prefix of the sequence. This implementation works on integer sequences
(`vector<int>`); use `to_vec` to convert a `string` to `vector<int>` when
operating on characters. Indices are 0-based.

## API

| Member | Effect |
|--------|--------|
| `to_vec(s, norm = 0)` | *(free function)* Convert a `string` to a `vector<int>` via `v[i] = s[i] - norm`. |
| `ZArray(p)` | Build from a pattern `vector<int>`; precomputes `z` via `zarray(p)`. |
| `z` | The computed Z-array of the input (`vector<int>`). |
| `zarray(s)` | *(static)* Compute and return the Z-array for sequence `s`.

## Notes

- `z[0]` is typically `0` (or `|s|` depending on convention); this implementation
  sets it to `0`.
- Use `to_vec` with `norm = 'a'` (or appropriate char) to map characters to a
  small 0-based alphabet.
- Complexity is linear: `O(n)` time and `O(n)` memory.
