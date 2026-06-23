# Persistent Segment Tree

**Type:** `SegTree` · **Complexity:** build `O(n)`, update/query `O(log n)`; each update creates `O(log n)` new nodes

## Overview

A node-pool persistent segment tree: every `update` returns a **new root** while
sharing untouched subtrees with the previous version, so all historical versions
remain queryable. Roots are `int` indices into the shared node pool that you
track yourself. Query ranges are **closed `[l, r]`**.

## API

| Method | Effect |
|--------|--------|
| `SegTree(n)` | Create a pool over `n` leaves (also seeds the null node). |
| `build(arr)` | Build a tree from `arr`; returns its root. |
| `update(root, i, val)` | Set index `i` to `val` on version `root`; returns the **new root**. |
| `query(root, l, r)` | Aggregate over `[l, r]` on version `root`. |

## Customization

Edit the two members marked `// customize`:

- `merge(a, b)` — the combine operation (currently `+`).
- `DEFAULT` — identity element returned for empty / out-of-range nodes.

## Notes

- Keep the root returned by each `update` to query that version later; the old root still works.
