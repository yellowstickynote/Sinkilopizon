# Strongly Connected Components (Tarjan)

**Type:** `SCC` · **Complexity:** `O(n + m)`

## Overview

Computes the strongly connected components of a **directed** graph in a single
DFS (Tarjan's algorithm) and builds the **condensation** graph. Nodes are
0-based. Each component is identified by the vertex at which it was closed
(`root[v]`), so component ids are vertex indices rather than `0…k-1`.

## API

| Member | Effect |
|--------|--------|
| `SCC(n)` | Create a directed graph on `n` nodes. |
| `add_edge(u, v)` | Add a directed edge `u → v`. |
| `run()` | Compute components and the condensation. |
| `comp` | List of components, each a `vector<int>` of member vertices. |
| `root[v]` | Component representative (id) of vertex `v`. |
| `cond[r]` | Condensation: out-edges from component `r` (may contain duplicates). |

## Notes

- `cond` is indexed by component representative, not by a compact `0…k-1` id.
- Edges within the same component are skipped when building `cond`.
