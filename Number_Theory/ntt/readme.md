# Number Theoretic Transform (NTT)

**Type:** Finite Field Domain (`Z/MOD`) · **Complexity:** Transform $O(N \log N)$, Multiply $O(N \log N)$

## Overview

Exact integer polynomial multiplication inside a finite field $\mathbb{Z}_{\text{MOD}}$ using primitive roots of unity $G$. By replacing complex arithmetic with modular arithmetic under an NTT-friendly prime modulus, it completely eliminates floating-point precision loss.

## Template / Configuration parameters

- `MOD` — Prime modulus of the form $c \cdot 2^k + 1$ (default: `998244353`).
- `G` — Primitive root modulo `MOD` (default: `3`).

## API

| Member / Function | Effect |
|--------|--------|
| `ntt(a, invert)` | In-place finite-field NTT on `vector<long long>& a`. Set `invert = true` for INTT. |
| `multiply_ntt(a, b)` | Exact modular polynomial convolution returning coefficients modulo `MOD`. |
| `power(base, exp)` | Modular exponentiation helper used to calculate roots and inverses. |
| `modInverse(n)` | Computes $n^{-1} \pmod{\text{MOD}}$ via Fermat's Little Theorem ($n^{\text{MOD}-2}$). |

## Customization

- To use alternative NTT-friendly primes (e.g., `1004535809` or `167772161`), update `MOD` and its corresponding primitive root `G`.

## Notes

- `MOD` **must be prime** and have a sufficiently large $2^k$ factor ($2^k \mid \text{MOD} - 1$) to support array sizes $N \le 2^k$.
- Guaranteed exact results modulo `MOD` without precision issues.