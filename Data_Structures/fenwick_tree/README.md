# Fenwick Tree (Binary Indexed Tree)

**Type:** `BIT<T, Comb>` · **Complexity:** build `O(n log n)`, update/query `O(log n)`

## Overview

A Fenwick tree for point updates and prefix queries. Indices are 0-based.

## Template parameters

- `T` — element / aggregate type.
- `Comb` — combining functor (defaults to `SumOp`).

## API

| Method | Effect |
|--------|--------|
| `BIT(n, id, c)` | Empty tree over `n` elements with identity `id` and combiner `c`. |
| `BIT(v, id, c)` | Build from a `vector<T>` with identity `id` and combiner `c`. |
| `set(pos, val)` | Set the element at `pos` to `val`. |
| `add(pos, val)` | Add `val` to the element at `pos`. |
| `pref_sum(pos)` | Aggregate over `[0, pos]`. |

## Customization

To change the combining operation, pass a custom functor.

```cpp
struct GcdOp { long long operator()(long long a, long long b) const { return std::gcd(a, b); } };
BIT<long long, GcdOp> bit(n, 0);
```

Common operations:

- **Sum (Default):** `BIT<long long> bit(n);`
- **GCD:** `BIT<long long, GcdOp> bit(n, 0);`
- **XOR:** `BIT<int, std::bit_xor<int>> bit(n, 0);`

## Notes

- Indices are 0-based.
- `pref_sum(pos)` aggregates `[0, pos]`.
- `set` uses `val - arr[pos]`, so it requires an appropriate subtraction operation on `T`.
- `ID` is the identity of `Comb`.
