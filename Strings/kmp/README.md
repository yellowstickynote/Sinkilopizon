# Knuth–Morris–Pratt (KMP)

**Type:** `KMP` · **Complexity:** build `O(m)`, search `O(n + m)` (`m = |pattern|`, `n = |text|`)

## Overview

Sequence matching via the **prefix function** (failure function). Constructed from a
pattern (a `vector<int>`), it finds all occurrences in a text in linear time, and
exposes the prefix-function machinery plus a DP-friendly automaton for the matching
problems that show up in competitive programming. Works on any integer alphabet
(use `to_vec` to run it on strings by mapping characters to ints). All indices are
0-based.

## API

| Member | Effect |
|--------|--------|
| `to_vec(s, norm = 0)` | *(free function)* Convert a `string` to a `vector<int>` via `v[i] = s[i] - norm`, so KMP can run on text. Pass `norm` (e.g. `'a'`) to map to a small `0`-based alphabet for `automaton`. |
| `KMP(pat)` | Build from a pattern `vector<int>`; precomputes its prefix function `pi`. |
| `prefix(s)` | *(static)* Prefix function of any sequence `s`: `pi[i]` = longest proper prefix of `s[0..i]` that is also a suffix. |
| `pi` | Prefix function of the pattern. |
| `find_all(text)` | Start indices of every occurrence of `pat` in `text`. |
| `count(text)` | Number of occurrences of `pat` in `text`. |
| `automaton(sigma)` | KMP automaton: `aut[state][c]` = next state after reading symbol `c` (`0 ≤ c < sigma`). |

## Automaton

`automaton(sigma)` returns a table with `|pat| + 1` states over an alphabet of
`sigma` symbols `0 .. sigma - 1` (the pattern values must lie in this range). From
state `i`, reading a symbol moves to the next prefix-function state; reaching state
`|pat|` means a full match just ended. Use it to run matching as a DP/transition
(e.g. "count sequences of length `L` avoiding / containing the pattern").

## Notes

- `find_all` returns empty for an empty pattern.
- For multiple texts against the same pattern, build `KMP` once and reuse it.
- The prefix function alone (`KMP::prefix(s)`) is the building block for string
  periodicity, counting distinct substrings with hashing, and more.
