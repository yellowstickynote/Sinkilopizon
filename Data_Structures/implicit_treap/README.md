# Implicit Treap — Lazy Propagation

**Type:** `Treap<T>` or `Treap<T, U>` · **Complexity:** all ops `O(log n)`

## Overview

A treap keyed **implicitly by position**, i.e. a dynamic array/sequence. Supports
insert/erase at an index, indexed access, and range update / query / **reverse**,
all in `O(log n)`. Indices are **0-based**.

`comb` may be **non-commutative**: a reverse aggregate (`ragg`) is tracked
alongside the forward one so `reverse` stays correct (e.g. for affine `mx + b`
composition).

## Template parameters

- `T` — node / aggregate type (sum, min/max, matrix, …).
- `U` — lazy-tag type. Defaults to `T`; use `Treap<T, U>` to separate them.

## API

| Method | Effect |
|--------|--------|
| `Treap(v)` | Build from a `vector<T>`. |
| `insert(i, v)` | Insert value `v` at index `i`. |
| `push_back(v)` | Append `v`. |
| `erase(i)` | Remove the element at index `i`. |
| `upd(l, r, v)` | Apply lazy tag `v` over `[l, r]`. |
| `query(l, r)` | Aggregate over `[l, r]`. |
| `reverse(l, r)` | Reverse the subarray `[l, r]`. |
| `operator[](i)` | Value at index `i`. |

## Customization

Only edit the Customization Section at the top:

- `ID` / `LAZY_ID` — identities for `comb` / the lazy tag.
- `comb(a, b)` — merge two aggregates (left, right order preserved).
- `apply_val(node_agg, lazy_val, node_sz)` — fold a lazy tag into an aggregate spanning `node_sz` elements.
- `combine_lazy(old, new)` — compose tags (old then new); needs `operator!=` on `U`.

## Notes

- Ranges are closed `[l, r]`, 0-based.
