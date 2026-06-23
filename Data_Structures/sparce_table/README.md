# Sparse Table

**Type:** `SparseTable<T>` · **Complexity:** build `O(n log n)`, query `O(1)`

## Overview

A static structure for **idempotent** range queries (min, max, gcd, …) on an
immutable array. Built once from a vector; answers any range query in `O(1)`.
Query range is **closed `[l, r]`**, 0-based.

## Template parameters

- `T` — element type.

## API

| Method | Effect |
|--------|--------|
| `SparseTable(v)` | Build from a `vector<T>`. |
| `query(l, r)` | Idempotent aggregate over `[l, r]` (currently min). |

## Customization

- `f(a, b)` (marked `// customize`) — the idempotent operation. Must be idempotent (`f(x, x) == x`) for the `O(1)` overlap trick to be valid; currently `min`.

## Notes

- The array is static — there is no update operation.
- Ranges are closed `[l, r]`, 0-based.
