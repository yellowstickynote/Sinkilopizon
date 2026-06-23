# XOR Trie (Binary Trie)

**Type:** `Xortrie` · **Complexity:** insert/erase/query `O(B)` where `B = 31` bits

## Overview

A binary trie over the bits of non-negative integers, used to find the maximum
XOR of a query value against the inserted set. Each node tracks a `cnt` of how
many values pass through it, so values can be removed as well as added (supports
sliding-window / online use). Handles values up to 31 bits (`i = 30 … 0`).

## API

| Method | Effect |
|--------|--------|
| `Xortrie()` | Empty trie. |
| `Xortrie(a)` | Build from a `vector<int>` (inserts each element). |
| `update(x, val=1)` | Insert `x` (`val=1`) or remove it (`val=-1`); updates counts along the path. |
| `maxxor(x)` | Maximum value of `x XOR y` over all currently present `y` (returns 0 if empty). |

## Notes

- Bit width is hard-coded to 31 bits (loop from bit 30). Widen the loop bound for larger values.
- `maxxor` follows the opposite bit when a counted child exists, greedily maximizing high bits.
