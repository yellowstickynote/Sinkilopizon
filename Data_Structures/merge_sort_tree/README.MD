# Merge Sort Tree

A merge sort tree stores a sorted vector at every segment tree node.

It can be used to answer range queries involving the number of elements
whose values lie inside a given range.

## Complexity

- Build: `O(n log n)`
- Query: `O(log^2 n)`
- Memory: `O(n log n)`

## Usage

```cpp
vector<int> a = {1, 5, 2, 4, 3};

MergeSortTree st(a);

// Number of elements in [1, 4] with value in [2, 4]
int ans = st.query(1, 4, 2, 4);
```

`query(l, r, vmin, vmax)` returns the number of elements `x` such that:

```text
l <= index <= r
vmin <= x <= vmax
```

## Requirements

`T` must support `operator<`.

No other comparison operator is required.

## Notes

The tree is static after construction.

The binary search calculation is separated into `bs_calc`, so it can
be reused or replaced in more complex problems without changing the
segment tree traversal.

The value range is inclusive on both ends.

`bs_calc(v, vmin, vmax)` is equivalent to:

```cpp
upper_bound(v.begin(), v.end(), vmax) -
lower_bound(v.begin(), v.end(), vmin)
```
