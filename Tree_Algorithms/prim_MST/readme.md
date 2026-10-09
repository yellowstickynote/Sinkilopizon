# Prim's Algorithm

**Type:** `Prim` · **Complexity:** `O(E log V)`

## Overview

Computes the **Minimum Spanning Tree (MST)** of a connected, weighted undirected graph by starting from a seed node and greedily adding the minimum-weight frontier edge using a Min-Heap priority queue.

## API

| Member | Effect |
|--------|--------|
| `Prim(n, adj, start)` | Builds MST from node count `n`, adjacency list `adj`, starting at node `start` (default `0`). |
| `mst_weight` | Total weight of the Minimum Spanning Tree (`long long`). |
| `mst_edges` | `vector<pair<int, int>>` storing added directed MST edges as `{from, to}` pairs. |
| `is_connected` | `bool` indicating whether all `n` vertices were reachable ($N-1$ edges added). |

## Notes

- Nodes are 0-based in range `[0, n-1]`.
- Adjacency list format expected: `adj[u]` stores `std::pair<int, long long>` as `{neighbor, weight}`.
- Works efficiently with multi-edges and dense graphs ($E \approx V^2$).
