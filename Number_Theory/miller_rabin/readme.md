# Miller-Rabin Primality Test

**Type:** Number Theory / Primality Testing · **Complexity:** Time $O(k \log N)$ where $k$ is the number of bases

## Overview

A probabilistic primality test evaluated over a specific set of bases to make it fully deterministic for all 64-bit integers. It factors $n-1 = 2^r \cdot d$ and verifies the congruence properties of $a^d \pmod n$. 

## API

| Member / Function | Effect |
|--------|--------|
| `is_prime(n)` | Returns `true` if the 64-bit unsigned integer `n` is prime, otherwise `false`. |

## Customization

- For 32-bit integers, the base set can be safely reduced to just `{2, 7, 61}` to optimize speed.
- The `binpower` function can be integrated into Montgomery Multiplication if repeated queries dominate performance.

## Notes

- Uses GCC/Clang specific `__uint128_t` to prevent overflow during intermediate 64-bit multiplications.
- Extremely fast for competitive programming, avoiding the need for large prime sieves when testing sparse, large numbers.