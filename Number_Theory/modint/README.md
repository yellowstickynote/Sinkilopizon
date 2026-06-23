# Modular Integer (ModInt)

**Type:** `ModInt<MOD>` (alias `mint = ModInt<1000000007>`) · **Complexity:** `+ - *` `O(1)`, `/` & `pow` & `inv` `O(log MOD)`

## Overview

Arithmetic in `Z/MOD` for a **fixed compile-time prime modulus**. Auto-reduces
on construction (handles negatives, no overflow). Division multiplies by the
modular inverse, valid because `MOD` is prime. Includes cached factorial tables
for combinatorics.

## Template parameters

- `MOD` — a compile-time prime modulus.

## API

| Member | Effect |
|--------|--------|
| `ModInt(v)` | Construct from any integer, reduced into `[0, MOD)`. |
| `+ - * /`, `+= -= *= /=`, unary `-`, `++ --` | Standard modular arithmetic. |
| `cin >>`, `cout <<` | Stream IO. |
| `pow(b)` / `power(a, b)` | Fast exponentiation `a^b` (`b` may be negative). |
| `inv()` | Modular inverse via Fermat, `a^(MOD-2)`. |
| `(int)x` | Explicit cast to the underlying value. |

### Static combinatorics helpers (call on the type, e.g. `mint::choose(n, k)`)

| Member | Effect |
|--------|--------|
| `fact(n)` | `n!`, cached and grown on demand. |
| `inv_fact(n)` | `(n!)^{-1}`, cached. |
| `choose(n, k)` | Binomial coefficient `C(n, k)`. |
| `perm(n, k)` | Falling factorial `n! / (n-k)!`. |
| `multichoose(n, k)` | Stars and bars `C(n+k-1, k)`. |
| `catalan(n)` | `n`-th Catalan number. |

## Customization

- Change the modulus via the template arg or the `mint` alias.

## Notes

- `MOD` **must be prime** for division / `inv` to be correct.
- Factorial tables are static per type and extend lazily as needed.
