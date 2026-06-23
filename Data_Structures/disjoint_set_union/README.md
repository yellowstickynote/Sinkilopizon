# Disjoint Set Union (Union-Find)

**Type:** `DSU` · **Complexity:** near `O(α(n))` amortized per op (path compression + union by size)

## Overview

A union-find structure over `n` elements `0 … n-1` with path compression and
union by size. Tracks component sizes.

## API

| Method | Effect |
|--------|--------|
| `DSU(n)` | Create `n` singleton sets. |
| `find(x)` | Representative (root) of `x`'s set, with path compression. |
| `unite(a, b)` | Merge the sets of `a` and `b`; returns `false` if already in the same set. |
| `size(x)` | Size of the component containing `x`. |

## Notes

- Requires `<numeric>` (`iota`) and `<vector>` when used standalone.
- Elements are 0-based.
