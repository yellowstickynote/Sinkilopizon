# Multiplicative Sieve

**Type:** `MultiplicativeSieve` · **Complexity:** build `O(n)`, memory about `40n` bytes while building

Linear sieve computing τ, σ, μ, φ and the primes for every value in `[1, n]`.

## API

| Member | Type / Parameters | Description | Constraints |
|--------|-------------------|-------------|-------------|
| `MultiplicativeSieve(n)` | `int n` | Build all tables. | `n ≥ 0`; practical `n ≲ 10^7` |
| `n` | `int` | Sieve limit. | Read-only |
| `primes` | `vector<int>` | Primes in `[2, n]`, ascending. | Empty if `n < 2` |
| `mu` | `vector<int>`, size `n + 1` | `mu[i] = μ(i)`. | Index `1..n`; `mu[0]` unused |
| `tau` | `vector<int>`, size `n + 1` | `tau[i] = τ(i)`. | Index `1..n`; `tau[0]` unused |
| `phi` | `vector<long long>`, size `n + 1` | `phi[i] = φ(i)`. | Index `1..n`; `phi[0]` unused |
| `sigma` | `vector<long long>`, size `n + 1` | `sigma[i] = σ(i)`. | Index `1..n`; `sigma[0]` unused |

## Example

```cpp
MultiplicativeSieve s(1000000);
s.mu[30];           // -1
s.phi[1000000];     // 400000

// coprime ordered pairs in [1, n]^2
long long ans = 0;
for (int d = 1; d <= n; d++) ans += s.mu[d] * 1LL * (n / d) * (n / d);
```

## Notes

- Out-of-range indices are out of bounds.
