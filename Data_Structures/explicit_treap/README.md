# Explicit (Key-Ordered) Treap Forest — Lazy Propagation

**Type:** `Treap<K>`, `Treap<K,T>`, or `Treap<K,T,U>` · **Complexity:** all ops `O(log n)`; `unite`/`intersect` `O(M log(N/M))`

## Overview

A key-ordered balanced BST (treap) that maintains an ordered set with aggregate
queries and lazy range updates over key ranges. A single `Treap<...>` instance
owns **all trees of that type**: a tree is just a root index that *you* track.
`init()` hands you a fresh empty one, so you can keep several disjoint trees
alive at once and split/merge between them.

Mutators take the root **by reference** and return `void`, so a root that shifts
is written back for you. Pure reads return their result. Ranges are **closed
`[lo, hi]`**.

## Template parameters

- `K` — key type that orders the set (needs `operator<`); keys are unique within a tree.
- `T` — value/aggregate type (e.g. `int` sum, or a struct for min/max). Defaults to `K`.
- `U` — lazy-tag type applied over key ranges (e.g. `int` range-add, an affine struct). Defaults to `T`.

## API

| Method | Effect |
|--------|--------|
| `init()` | Return a fresh empty tree (`== 0`). |
| `split(x, k, a, b, eq)` | Cut `x` by key into `a, b`. `eq=false` → `{<k} \| {>=k}`; `eq=true` → `{<=k} \| {>k}`. |
| `merge(a, b, c)` | **Concatenate** ordered disjoint subtrees (all keys in `a` < all keys in `b`) → `c`. Use to rejoin after a split. |
| `unite(a, b, c)` | Key-set **union** of two arbitrary trees → `c`. On a shared key keeps `a`'s node. Inputs are consumed. |
| `intersect(a, b, c)` | Key-set **intersection** (keys in both) → `c`, nodes taken from `a`. Inputs are consumed. |
| `insert(r, k, v)` | Add key `k` with value `v` (no-op if already present). |
| `erase(r, k)` | Remove key `k`. |
| `upd(r, lo, hi, tag)` | Apply lazy `tag` over key range `[lo, hi]`. |
| `query(r, lo, hi)` | Aggregate over key range `[lo, hi]`. |
| `contains(r, k)` | Membership test. |
| `order_of_key(r, k)` | Number of keys `< k`. |
| `kth(r, i)` | Key at rank `i` (0-based). |

## Customization

Edit the functions at the top of the struct:

- `ID` / `LAZY_ID` — identities for `comb` / the lazy tag.
- `comb(a, b)` — merge two aggregates.
- `apply_val(node_agg, lazy_val, node_sz)` — fold a lazy tag into an aggregate spanning `node_sz` elements.
- `combine_lazy(old, new)` — compose tags (old then new); needs `operator!=` on `U`.

## Notes

- Internals keep the invariant: `push(x)` before descending, `calc(x)` after a child changes.
- `unite`/`intersect` consume their inputs — don't reuse `a`/`b` afterward.
