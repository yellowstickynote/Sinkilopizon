# Lowest Common Ancestor (Binary Lifting)

**Type:** `TreeLCA` · **Complexity:** build `O(n log n)`, query `O(log n)`

## Overview

Lowest common ancestor via **binary lifting**. Precomputes a `2^i`-th ancestor
table so LCA, `k`-th ancestor, and tree distance all answer in `O(log n)`. The
tree is **1-indexed** (node `0` is the null/sentinel parent).

## API

| Member | Effect |
|--------|--------|
| `TreeLCA(n)` | Initialize a tree with `n` nodes (1-indexed). |
| `add_edge(u, v)` | Add an undirected edge. |
| `build(root = 1)` | Precompute depth and the binary-lifting table. |
| `lca(u, v)` | Lowest common ancestor of `u` and `v`. |
| `kth_parent(u, k)` | `k`-th ancestor of `u` (returns `0` if out of bounds). |
| `dist(u, v)` | Number of edges between `u` and `v`. |

## Notes

- Nodes are 1-indexed; `0` is reserved as the sentinel "no parent".
- Call `build` once after all edges are added.
