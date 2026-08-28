# Fenwick Tree (Binary Indexed Tree)

**Type:** `BIT<T, Comb, Neg>` · **Complexity:** update/query `O(log n)`

## Overview

Fenwick tree for point updates and prefix queries. Indices are 0-based.

## Template parameters

- `T` — element / aggregate type.
- `Comb` — combining functor (defaults to `SumOp`).
- `Neg` — inverse functor (defaults to `NegOp`).

## API

| Method | Effect |
|--------|--------|
| `BIT(n, id, c, ng)` | Empty tree over `n` elements. |
| `add(pos, val)` | Combines `val` into the element at `pos`. |
| `set(pos, val)` | Sets the element at `pos` to `val`. |
| `pref_sum(pos)` | Aggregate over `[0, pos]`. |

## Customization

The default operation is sum:

```cpp
BIT<long long> bit(n);
```

`Comb` and `Neg` can be replaced for other operations:

```cpp
struct GcdOp {
    long long operator()(long long a, long long b) const {
        return gcd(a, b);
    }
};
```

`set` requires `Neg` to provide the inverse of an element under `Comb`:

```cpp
add(pos, comb(neg(arr[pos]), val));
```

For sum, this is ordinary negation:

```cpp
struct NegOp {
    template <class T>
    T operator()(T a) const { return -a; }
};
```

## Notes

- Indices are 0-based.
- `pref_sum(pos)` aggregates `[0, pos]`.
- `ID` must be the identity of `Comb`.
- `Comb` must be associative.
- `Neg` must provide the inverse required by `set`.
