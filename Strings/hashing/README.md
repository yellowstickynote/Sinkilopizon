# String Hashing (Polynomial, Prefix Hashes, mod 2^64 - 1)

**Type:** `StringHash` · **Complexity:** build `O(n)`, substring hash `O(1)`

## Overview

Polynomial hashing over a string or any integer sequence. After an `O(n)` build,
the hash of any substring is available in `O(1)`, so two substrings can be
compared for equality without touching their characters. Ranges are **closed
`[l, r]`**, 0-based.

All arithmetic is modulo `2^64 - 1`, implemented inside the struct with an
end-around carry (`add`) and `__uint128_t` multiplication (`mul`). It is about 2x
slower than plain `unsigned long long` (mod `2^64`) but is not broken by
Thue-Morse style anti-hash tests. The base is random and generated **once per
run**, when the first `StringHash` is constructed; all instances share it, so a
fixed hack cannot target it and hashes of different strings are directly
comparable. The file is self-contained and the modulus is not customizable.

## API

| Member | Effect |
|--------|--------|
| `StringHash(s)` | Build from a `string` or `vector<int>` (any container of integers). |
| `query(l, r)` | Hash of `s[l..r]`, as a canonical `u64`. |
| `windows(len)` | Hashes of every substring of length `len`, in order of start position (empty if `len > n`). |
| `StringHash::base()` | The shared base (`u64`), generated on first use. |

Hashes are plain `u64` values already reduced to `[0, 2^64 - 2]`, so they can be
compared with `==` and `<` and used directly in `set`, `map`, `unordered_map`,
`sort` and `unique`.

## Usage

```cpp
StringHash h(s);
bool eq = h.query(l1, r1) == h.query(l2, r2);

vector<u64> w = h.windows(k);           // all length-k substring hashes
sort(w.begin(), w.end());               // e.g. count distinct substrings
```

Every instance uses the same base, so hashes from different strings can be
compared directly:

```cpp
StringHash a(s), b(t);
bool eq = a.query(l1, r1) == b.query(l2, r2);
```

- **Reproducible runs (debugging):** replace `random_device{}()` in `base()` with
  a constant seed, e.g. `mt19937_64 rng{12345};`.

## Notes

- Compare only hashes of **equal-length** substrings.
- Elements are added as `(u64)s[i]` with no offset, so with a `0` element the
  sequences `[0, 1]` and `[1]` hash the same. This is harmless when you compare
  equal-length substrings (the usual case); shift values to start at `1` if you
  ever compare different lengths.
- Internally `ha` and `pw` may hold `2^64 - 1`, which is the same number as `0`;
  `query` and `windows` always return the reduced value, so only compare those.
- Needs `<bits/stdc++.h>` (`vector`, `mt19937_64`, `random_device`), like the rest of the repo.
- The `u64` / `u128` aliases at the top are the same as in `miller_rabin.cpp`;
  repeating an identical alias is legal, so pasting both is fine.
- Memory is `O(n)`: two `vector<u64>` of size `n + 1`.
