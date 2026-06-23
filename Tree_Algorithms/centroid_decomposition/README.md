# Centroid Decomposition

**Type:** `CentroidDecomposition` · **Complexity:** build `O(n log n)`

## Overview

Builds the **centroid decomposition** of a tree: a recursive partition where each
level removes the centroid of every remaining component, producing a balanced
"centroid tree" of depth `O(log n)`. Commonly used for path/distance queries that
decompose over centroids. Nodes are 0-based.

## API

| Member | Effect |
|--------|--------|
| `CentroidDecomposition(tree)` | Build from an adjacency list `vector<set<int>>` (rooted internally at 0). |
| `dad[u]` | Parent of `u` in the centroid tree (root's parent is itself). |
| `operator[](u)` | Same as `dad[u]`. |

## Notes

- Takes the tree **by value** as `vector<set<int>>` and mutates its copy while peeling centroids; your original is untouched.
- `sub` holds subtree sizes computed during the build.
