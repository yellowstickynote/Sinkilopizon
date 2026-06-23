# Iterative Lazy Segment Tree

**Type:** `LazySegTree<T>` or `LazySegTree<T, U>` · **Complexity:** build `O(n)`, update/query `O(log n)`

## Overview

An iterative (bottom-up) segment tree with lazy propagation supporting range
update and range query. Ranges are **closed `[l, r]`**, 0-based.

## Template parameters

- `T` — data type of the tree nodes (e.g. node sums, or a struct for a matrix).
- `U` — data type of the lazy tags (e.g. a struct for an affine transformation `mx + b`).

Defaults to `T == U`. To separate them, instantiate as `LazySegTree<T, U>`.

## API

| Method | Effect |
|--------|--------|
| `LazySegTree(n)` | Empty tree over `n` elements. |
| `LazySegTree(v)` | Build from a `vector<T>`. |
| `upd(l, r, val)` | Apply lazy tag `val` over `[l, r]`. |
| `query(l, r)` | Aggregate over `[l, r]`. |
| `query_rev(l, r)` | Alias of `query` (kept for API parity with other seg trees). |

## Customization

Only edit the Customization Section at the top:

- `ID` / `LAZY_ID` — identities for `comb` / the lazy tag.
- `comb(a, b)` — merge two node aggregates.
- `apply_val(node_val, lazy_val, node_sz)` — fold a lazy tag into a node spanning `node_sz` elements.
- `combine_lazy(old, new)` — compose tags (old then new).

## Notes

- Ranges are closed `[l, r]`, 0-based.
