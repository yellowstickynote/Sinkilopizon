# Convex Hull Trick (LineContainer)

**Type:** `CHT<T, Mode>` · **Complexity:** amortized `O(log n)` per `add` / `query`

## Overview

A fully dynamic convex hull trick (Li Chao / kinetic-style line container built on
`multiset`) for DP transitions of the form `dp[i] = min/max over j of (m_j · x + c_j)`.
Lines may be added in **any order** and queries may use **any `x`**. Requires a
`using ll = long long;` typedef in scope (repo convention).

## Template parameters

- `T` — coordinate / value type (defaults to `int`; use `long long` in practice).
- `Mode` — `-1` for a **minimum** hull (default), `+1` for a **maximum** hull. The
  sign trick lets one implementation serve both.

## API

| Member | Effect |
|--------|--------|
| `add(m, c)` | Insert the line `y = m·x + c`. |
| `query(x)` | Best (min or max, per `Mode`) value of any inserted line at `x`. |

## Notes

- `query` asserts the container is non-empty — add at least one line first.
- Internally stores lines negated when `Mode == -1` so the same `max`-style hull logic works.
