# Fenwick Tree (Binary Indexed Tree)

**Type:** `BIT<T>` · **Complexity:** build `O(n)`, update/prefix-sum `O(log n)`

## Overview

A Fenwick tree (BIT) for point updates and prefix-sum queries over an array of
`n` elements. Indices are **0-based** in the public API. It also keeps the raw
`arr` so `set` can compute the delta against the current value.

## Template parameters

- `T` — element / sum type (e.g. `int`, `long long`).

## API

| Method | Effect |
|--------|--------|
| `BIT(n)` | Empty tree over `n` elements. |
| `set(ind, val)` | Set the value at index `ind` to `val`. |
| `add(ind, val)` | Add `val` to the element at index `ind`. |
| `pref_sum(ind)` | Sum of all values in `[0, ind]`. |

## Notes

- For a range sum `[l, r]`, compute `pref_sum(r) - pref_sum(l - 1)`.
- Indices are 0-based.
