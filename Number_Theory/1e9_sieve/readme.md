# Fast Segmented Wheel Sieve

**Type:** Number Theory / Prime Generation · **Complexity:** Time $O(N \log \log N)$, Space $O(\sqrt{N} + L)$

## Overview

Generates all prime numbers up to $N$ using a cache-friendly segmented sieve of Eratosthenes combined with a modulo-30 wheel. It inherently skips multiples of 2, 3, and 5 by tracking only the 8 coprime residues per block of 30. Bit-packing, fast bitwise extraction, and precomputed repeating patterns for small primes ensure extremely fast execution and low memory overhead.

## API

| Member / Function | Effect |
|--------|--------|
| `sieve(N, Q = 17, L = 1 << 15)` | Returns a `vector<int>` of all primes up to $N$. `Q` sets the threshold for pre-computed patterns, and `L` sets the block size. |

## Customization

- Modify `L` (default `1 << 15` or 32KB) to precisely match the target architecture's L1 data cache size for maximum performance.
- Adjust `Q` (default `17`) to change the threshold of small primes included in the pre-sieved block pattern. *Warning: Increasing `Q` significantly increases the precomputation array size.*

## Notes

- Vector capacity is pre-allocated by estimating the final prime count using the Prime Number Theorem ($N / (\ln(N) - 1.1)$) to prevent reallocation overhead.
- Relies on the compiler intrinsic `__builtin_ctz` for fast bitwise extraction, which requires GCC or Clang.
