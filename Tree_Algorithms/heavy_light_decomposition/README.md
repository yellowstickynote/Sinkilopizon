# Heavy-Light Decomposition

**Type:** `TreeHLD<ST, T, U>` · **Complexity:** `O(log^2 n)` per path op, `O(log n)` per subtree op

## Overview

Heavy-light decomposition over a tree, backed by a user-supplied segment tree, to
support path and subtree updates/queries. **Non-commutative compatible**: path
queries respect endpoint order (forward vs. reversed segments are combined
correctly), so it works with operations like affine composition. The tree is
1-indexed.

## Template parameters

- `ST` — a (lazy) segment tree type exposing `ID`, `comb`, `query`, `query_rev`, `upd` (e.g. the repo's `LazySegTree`).
- `T` — node / aggregate type.
- `U` — lazy-tag type (defaults to `T`).

## API

| Member | Effect |
|--------|--------|
| `TreeHLD(n)` | Create over `n` nodes (1-indexed). |
| `add_edge(u, v)` | Add an undirected edge. |
| `build(root = 1)` | Build the decomposition. |
| `build(vals, root = 1)` | Build and seed initial node values. |
| `upd_node(u, val)` | Point update at `u`. |
| `upd_path(u, v, val)` | Range update along the path `u … v`. |
| `upd_subtree(u, val)` | Range update over the subtree of `u`. |
| `query_path(u, v)` | Ordered aggregate along the path `u → v`. |
| `query_subtree(u)` | Aggregate over the subtree of `u`. |
| `lca(u, v)` | Lowest common ancestor. |

## Notes

- The backing `ST` must provide both `query` and `query_rev`; `comb`/lazy must compose order-correctly for non-commutative use.
- Nodes are 1-indexed.
