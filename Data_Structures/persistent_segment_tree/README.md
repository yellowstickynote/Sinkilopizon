# Persistent Segment Tree — Point Update, Range Query (Versioned)

**Type:** `PersistentSegTree<T, Comb>` · **Complexity:** build `O(n)`, update/query `O(log n)` time and space

## Overview

A top-down, node-based persistent segment tree designed to preserve historical array states. Updates create new branches and return a new root index, allowing you to independently query any past or present version. Ranges are **closed `[l, r]`**, 0-based.

## Template parameters

- `T` — node / aggregate type.
- `Comb` — combining functor / lambda type (defaults to `std::plus<T>`).

## API

| Method | Effect |
|--------|--------|
| `PersistentSegTree(n, id, c)` | Empty tree over `n` elements with identity `id` and combiner `c`. |
| `build(v)` | Build from a `vector<T>` and return the initial root index. |
| `update(root, i, val)` | Set element at `i` to `val` branching from `root`, returning the new root index. |
| `query(root, l, r)` | Aggregate over `[l, r]` within the version pointed to by `root`. |

## Customization (Functors)

To change the combining operation (`comb`) with **0% runtime overhead**, pass a custom functor struct overloading `const operator()`. Avoid `std::function` as it adds indirect call overhead and heap allocations (TLE risk).

### 2-Line Usage Snippet
```cpp
struct GcdOp { long long operator()(long long a, long long b) const { return std::gcd(a, b); } };
PersistentSegTree<long long, GcdOp> gcd_tree(n, 0); // n elements, ID = 0, using GcdOp
```

### Common Operations
- **Range Sum (Default):** `PersistentSegTree<long long> sum_tree(n, 0);`
- **Range Min:** `struct MinOp { long long operator()(long long a, long long b) const { return min(a, b); } };`
- **Range XOR:** `PersistentSegTree<int, std::bit_xor<int>> xor_tree(n, 0);`

## Notes

- Ranges are closed `[l, r]`, 0-based.
- Updates are non-destructive; you must store the returned root integer from `update` or `build` to track different version states.
- Node index `0` is reserved as a null/default dummy node.
