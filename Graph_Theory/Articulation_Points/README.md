# Articulation Points (Cut Vertices)

**Type:** `ArticulationPoints` · **Complexity:** `O(n + m)`

## Overview

Finds all **articulation points** (cut vertices) of an undirected graph via a
single DFS using discovery times (`tin`) and low-links (`low`). A vertex is an
articulation point if removing it increases the number of connected components.
Handles disconnected graphs (runs the DFS from every unvisited vertex). Nodes are
0-based.

## API

| Member | Effect |
|--------|--------|
| `ArticulationPoints(n)` | Create a graph on `n` nodes. |
| `add_edge(u, v)` | Add an undirected edge. |
| `find_cutpoints()` | Run the algorithm; fills `articulations`. |
| `articulations` | `set<int>` of articulation-point vertices. |

## Notes

- The root of a DFS tree is an articulation point iff it has more than one DFS child.
- Multi-edges are fine; the `to == p` check skips the edge back to the parent.
