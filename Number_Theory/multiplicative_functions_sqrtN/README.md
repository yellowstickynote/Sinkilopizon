# Multiplicative Functions (single value)

**Type:** `MultiplicativeFunctions` · **Complexity:** `O(√n)` per call

τ (divisor count), σ (divisor sum), μ (Möbius), φ (Euler totient) for one `n`. All members are `static`.

## API

`ll` = `long long`.

| Member | Parameters | Returns | Constraints |
|--------|------------|---------|-------------|
| `factorize(n)` | `ll n` | `vector<pair<ll, int>>`, `{prime, exponent}` with primes ascending; empty for `n = 1` | `n ≥ 1`; practical `n ≲ 10^12` |
| `tau(n)` | `ll n` | `ll`, number of divisors | `n ≥ 1`; practical `n ≲ 10^12` |
| `sigma(n)` | `ll n` | `ll`, sum of divisors | `n ≥ 1`; no overflow for `n ≤ 10^12` |
| `mu(n)` | `ll n` | `int` in `{-1, 0, 1}` | `n ≥ 1`; practical `n ≲ 10^12` |
| `phi(n)` | `ll n` | `ll`, count of `i ∈ [1, n]` with `gcd(i, n) = 1` | `n ≥ 1`; practical `n ≲ 10^12` |

## Example

```cpp
MultiplicativeFunctions::phi(36);    // 12
MultiplicativeFunctions::sigma(36);  // 91
```

## Notes

- `n ≤ 0` is undefined behavior.
- For all values up to `n` use `MultiplicativeSieve`.
