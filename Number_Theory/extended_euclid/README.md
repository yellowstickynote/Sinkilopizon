# Extended Euclidean Algorithm

**Type:** `ExtendedEuclid` · **Complexity:** `O(log min(a, b))`

## Overview

Computes `g = gcd(a, b)` together with Bézout coefficients `x, y` satisfying
`a*x + b*y = g`. Useful for modular inverses (`a*x ≡ 1 (mod m)` when
`gcd(a, m) = 1`) and solving linear Diophantine equations. Uses `long long`
throughout to avoid the easy overflow of the `int` version.

## API

| Member | Effect |
|--------|--------|
| `ExtendedEuclid(a, b)` | Compute and store `g`, `x`, `y`. |
| `g` | `gcd(a, b)`. |
| `x`, `y` | Bézout coefficients with `a*x + b*y == g`. |
| `ext(a, b, x&, y&)` | Static helper if you prefer the raw call without an object. |

## Notes

- For a modular inverse of `a` mod `m`: `ExtendedEuclid e(a, m);` then the inverse
  is `((e.x % m) + m) % m` (requires `e.g == 1`).
