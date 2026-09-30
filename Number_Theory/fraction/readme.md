# Fraction (Rational Number)

**Type:** `Fraction` · **Complexity:** creation/math `O(log(min(|N|, |D|)))`, compare `O(1)`

## Overview

A struct used to represent rational numbers exactly, entirely bypassing floating-point precision loss. It automatically reduces fractions and standardizes signs upon creation or during mathematical operations. It natively handles division by zero by treating it as infinity, providing absolute safety against the undefined behaviors and infinite loops commonly caused when `std::sort` encounters `NaN` or precision rounding errors.

## API

| Method | Effect |
| :--- | :--- |
| `Fraction()` | Empty fraction, defaults to `0/1`. |
| `Fraction(n, d)` | Builds fraction `n/d`, reduces via `std::gcd`, and standardizes signs. |
| `operator<(o)`, `>`, `<=`, `>=` | Safely compares using 128-bit cross-multiplication. |
| `operator==`, `!=` | Exact equality check (requires exactly matching `n` and `d`). |
| `operator+`, `-`, `*`, `/` | Performs mathematical operation and returns a new reduced `Fraction`. |

## Notes

* Internal cross-multiplication casts to `__int128_t` to completely prevent overflow for numerators and denominators up to `10^18`.
* Division by zero (`d = 0`) is natively normalized to represent `+INF` (`1/0`) or `-INF` (`-1/0`), allowing them to sort deterministically at the ends of an array.
* Bypasses the heavy I/O overhead of `std::cin` parsing string-to-float decimals.