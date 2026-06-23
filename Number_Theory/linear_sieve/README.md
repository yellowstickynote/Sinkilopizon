# Linear Sieve

**Type:** `LinearSieve` · **Complexity:** build `O(n)`, `factorize`/`divisors` `O(log x + d(x))`

## Overview

Sieves `[0, n]` in linear time, recording the **smallest prime factor** of every
number. From the SPF table you get `O(1)` primality tests and `O(log x)` prime
factorizations.

## API

| Member | Effect |
|--------|--------|
| `LinearSieve(n)` | Sieve `[0, n]` in `O(n)`. |
| `spf[i]` | Smallest prime factor of `i` (`spf[i] == i` iff `i` is prime). |
| `primes` | All primes in `[2, n]`, ascending. |
| `is_prime(x)` | `true` iff `x ∈ [2, n]` is prime, `O(1)`. |
| `factorize(x)` | Prime factorization as `{prime, exponent}` pairs, `O(log x)`. |
| `divisors(x)` | All divisors of `x` (unsorted), `O(d(x) + log x)`. |

## Notes

- `factorize`/`divisors`/`is_prime` only work for `x ≤ n`.
