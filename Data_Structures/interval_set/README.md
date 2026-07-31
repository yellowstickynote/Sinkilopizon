# Interval Set — Disjoint Range Manager (Size-Tracked)
**Type:** `IntervalSet` · **Complexity:** amortized `O(log n)` per operation

## Overview
A dynamically maintained set of disjoint integer intervals that automatically merges overlapping segments upon insertion and splits them upon deletion. It strictly maintains a secondary binary search tree (`sz_st`) to track active intervals sorted by their size, breaking ties with the left boundary.

## Template parameters
- None. Operates directly on `int` coordinates to minimize template bloat.

## API
| Method | Effect |
|--------|--------|
| `ins(l, r)` | Inserts the closed range `[l, r]` into the set, merging overlapping intervals and updating `sz_st`. |
| `del(l, r)` | Removes the closed range `[l, r]` from the set, splitting intervals and updating `sz_st`. |
| `intersect(l, r)` | Returns the sum of lengths of intersections between `[l, r]` and current ranges without modifying the set. |
| `surrounding_range(pos)` | Returns a `pair<int,int>` `{l, r}` containing `pos`, or `{-1, -1}` if `pos` is unassigned. |

## Customization (Functors)
There is no combining functor. The `IntervalSet` internally manages sync logic between `st` and `sz_st` using private-like helper methods `add` and `rem`.

### 2-Line Usage Snippet
```cpp
IntervalSet iset; 
iset.ins(1, 10); 
```

### Common Operations:
- **Insert Range:** `iset.ins(l, r);`
- **Remove Range:** `iset.del(l, r);`
- **Intersection Length:** `int overlap = iset.intersect(3, 15);`
- **Point Query:** `pair<int, int> bounds = iset.surrounding_range(5);`
- **Largest Range Query:** `auto [size, l] = *iset.sz_st.rbegin();`

## Notes
- Ranges are strictly closed `[l, r]`.
- The `sz_st` set elements are pairs formatted as `{size, leftmost_point}`.
- Internally uses `upper_bound` with `2e9` for rapid point queries. For coordinates exceeding `2e9`, switch `int` to `long long` and update the literal accordingly.
