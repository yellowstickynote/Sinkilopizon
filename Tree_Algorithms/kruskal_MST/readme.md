# Kruskal's Algorithm

**Type:** `Kruskal` · **Complexity:** `O(E log E)`

## Overview

Computes the **Minimum Spanning Tree (MST)** of a weighted undirected graph using an edge-centric greedy strategy with Disjoint Set Union (DSU). Ideal for sparse graphs where $E \ll V^2$.

## API

| Member | Effect |
|--------|--------|
| `Kruskal(n, edges)` | Builds MST from vertex count `n` and edge list `vector<Edge>&`. |
| `mst_weight` | Total weight of the Minimum Spanning Tree (`long long`). |
| `mst_edges` | `vector<Edge>` containing the $N-1$ edges included in the MST. |
| `is_connected` | `bool` indicating whether the graph forms a single connected tree. |

## Notes

- Nodes are 0-based in range `[0, n-1]`.
- Modifies and sorts the input `edges` vector in-place inside constructor.
- Uses path compression and union-by-size DSU for near $O(1)$ amortized cycle checks.
