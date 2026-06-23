# Dijkstra (with path counting)

**Type:** `Dijkstra` · **Complexity:** `O((n + m) log n)`

## Overview

Single-source shortest paths on a graph with **non-negative** edge weights, using
a binary-heap priority queue. Alongside distances it tracks one parent per node
(for path reconstruction) and the **number of shortest paths** to each node,
counted modulo `MOD`. Nodes are 0-based; distances use `long long`.

## API

| Member | Effect |
|--------|--------|
| `Dijkstra(n)` | Create a graph on `n` nodes. |
| `add_edge(u, v, w)` | Add a directed edge `u → v` of weight `w` (call twice for undirected). |
| `run(s)` | Compute shortest paths from source `s`. |
| `dist[i]` | Shortest distance `s → i` (`INF` if unreachable). |
| `par[i]` | Predecessor of `i` on a shortest path (`-1` if unreachable or `i == s`). |
| `cnt[i]` | Number of shortest paths `s → i`, modulo `MOD`. |

## Customization

- `MOD` (member, default `1e9 + 7`) — modulus for the shortest-path count.

## Notes

- Edge weights must be non-negative.
- `INF = 1e18` fits in `long long`; keep edge weights well below it to avoid overflow.
