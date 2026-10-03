# Pollard's Rho Algorithm

**Type:** Number Theory / Integer Factorization · **Complexity:** Expected Time $O(N^{1/4})$, Space $O(1)$

## Overview

A fast, randomized algorithm for integer factorization. This specific implementation utilizes Brent's cycle-finding variation combined with polynomial block accumulation (batching GCD calculations) to significantly reduce the overhead of modulo operations.

## API

| Member / Function | Effect |
|--------|--------|
| `pollard_rho(n)` | Returns a non-trivial divisor of `n`. Re-runs recursively if it happens to hit `n`. |
| `factorize(n, factors)` | Recursively populates `map<u64, int> factors` with the prime factorization of `n`. |

## Customization

- The accumulation block size (currently `128`) can be tuned based on the average size of $N$ and architecture caching.

## Notes

- **Dependency:** Strongly depends on an efficient `is_prime` function (like Miller-Rabin) to identify prime factors and terminate the recursion early.
- Handles up to 64-bit integers effortlessly thanks to `__uint128_t` for intermediate steps.