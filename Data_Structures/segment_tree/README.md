# Segment Tree — Point Update, Range Query (Non-Commutative)

**Type:** `SegTree<T, Comb>` · **Complexity:** build `O(n)`, update/query `O(log n)`

## Overview

An iterative point-update / range-query segment tree designed to work with a
**non-commutative** `comb` (order matters). It maintains both a forward and a
reversed tree so you can query the aggregate in either direction. Ranges are
**closed `[l, r]`**, 0-based.

## Template parameters

- `T` — node / aggregate type.
- `Comb` — combining functor / lambda type (defaults to `MaxOp`).

## API

| Method | Effect |
|--------|--------|
| `SegTree(n, id, c)` | Empty tree over `n` elements with identity `id` and combiner `c`. |
| `SegTree(v, id, c)` | Build from a `vector<T>` with identity `id` and combiner `c`. |
| `upd(pos, val)` | Set the element at `pos` to `val`. |
| `query(l, r)` | Left-to-right aggregate over `[l, r]`. |
| `query_rev(l, r)` | Right-to-left aggregate over `[l, r]`. |

## Customization (Functors)

To change the combining operation (`comb`) with **0% runtime overhead**, pass a custom functor struct overloading `const operator()`. Avoid `std::function` as it adds indirect call overhead and heap allocations (TLE risk).

### 2-Line Usage Snippet
```cpp
struct GcdOp { long long operator()(long long a, long long b) const { return std::gcd(a, b); } };
SegTree<long long, GcdOp> gcd_tree(n, 0); // n elements, ID = 0, using GcdOp
```

### Common Operations
- **Range Max (Default):** `SegTree<long long> max_tree(n, -1e18);`
- **Range Sum:** `SegTree<long long, std::plus<long long>> sum_tree(n, 0);`
- **Range Min:** `struct MinOp { long long operator()(long long a, long long b) const { return min(a, b); } };`
- **Range XOR:** `SegTree<int, std::bit_xor<int>> xor_tree(n, 0);`

## Notes

- Ranges are closed `[l, r]`, 0-based.
- Use `query_rev` when the operation is non-commutative and you need the reversed fold.
- Both `comb` and `ID` can be customized via the constructor with zero runtime overhead due to compile-time type deduction.
