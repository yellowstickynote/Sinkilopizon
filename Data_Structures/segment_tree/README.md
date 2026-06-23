# Segment Tree — Point Update, Range Query (Non-Commutative)

**Type:** `SegTree<T>` · **Complexity:** build `O(n)`, update/query `O(log n)`

## Overview

An iterative point-update / range-query segment tree designed to work with a
**non-commutative** `comb` (order matters). It maintains both a forward and a
reversed tree so you can query the aggregate in either direction. Ranges are
**closed `[l, r]`**, 0-based.

## Template parameters

- `T` — node / aggregate type.

## API

| Method | Effect |
|--------|--------|
| `SegTree(n)` | Empty tree over `n` elements. |
| `SegTree(v)` | Build from a `vector<T>`. |
| `upd(pos, val)` | Set the element at `pos` to `val`. |
| `query(l, r)` | Left-to-right aggregate over `[l, r]`. |
| `query_rev(l, r)` | Right-to-left aggregate over `[l, r]`. |

## Customization

- `comb(a, b)` — the operation, where `a` is the left operand and `b` the right (order matters; currently `max`).
- `ID` — identity element of `comb`.

## Notes

- Ranges are closed `[l, r]`, 0-based.
- Use `query_rev` when the operation is non-commutative and you need the reversed fold.
