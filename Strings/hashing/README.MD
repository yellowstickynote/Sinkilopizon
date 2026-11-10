# Hash (Arithmetic Modulo 2^64 - 1)

**Type:** `Hash` · **Complexity:** `O(1)` per operation

## Overview

A value type for polynomial hashing that does arithmetic modulo `2^64 - 1`.
It is about 2x slower than plain `unsigned long long` (mod `2^64`) but is not
broken by Thue-Morse style anti-hash tests, which make mod `2^64` hashes
collide on strings of length around `2^10` and up. Addition and subtraction
use an end-around carry; multiplication uses `__uint128_t`.

## API

| Member | Effect |
|--------|--------|
| `Hash(x)` | Wrap a `u64` (default `0`). |
| `a + b`, `a - b`, `a * b` | Arithmetic mod `2^64 - 1`. |
| `get()` | Canonical value in `[0, 2^64 - 2]` as a `u64`. |
| `==`, `!=`, `<` | Compare by canonical value, so `Hash` works in `set`, `map` and `sort`. |

## Usage

```cpp
Hash base = 1000000007ULL * 100 + 3;    // pick any base, ideally random
Hash h = Hash(3) * base + Hash(5);      // 3 * base + 5
bool same = (h == Hash(3) * base + Hash(5));
u64 key = h.get();                      // for printing or unordered_map keys
```

## Notes

- The internal value `x` can be `2^64 - 1`, which is the same number as `0`.
  Always compare through `==` / `get()`, never through `x` directly.
- `Hash(x)` takes a `u64`; a negative `int` is converted by wrap-around.
- Needs no headers, only the built-in types and the `u64` / `u128` aliases
  declared at the top of the file. Repeating those aliases is legal, so pasting
  it together with `miller_rabin.cpp` is fine.
