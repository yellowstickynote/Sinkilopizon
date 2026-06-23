# Knuth–Morris–Pratt (KMP)

**Type:** `KMP` · **Complexity:** build `O(m)`, search `O(n + m)` (`m = |pattern|`, `n = |text|`)

## Overview

String matching via the **prefix function** (failure function). Constructed from a
pattern, it finds all occurrences in a text in linear time, and exposes the
prefix-function machinery plus a DP-friendly automaton for the string problems
that show up in competitive programming. All indices are 0-based.

## API

| Member | Effect |
|--------|--------|
| `KMP(pat)` | Build from a pattern; precomputes its prefix function `pi`. |
| `prefix(s)` | *(static)* Prefix function of any string `s`: `pi[i]` = longest proper prefix of `s[0..i]` that is also a suffix. |
| `pi` | Prefix function of the pattern. |
| `find_all(text)` | Start indices of every occurrence of `pat` in `text`. |
| `count(text)` | Number of occurrences of `pat` in `text`. |
| `automaton(sigma, base)` | KMP automaton: `aut[state][c]` = next state after reading `base + c`. |

## Automaton

`automaton(sigma = 26, base = 'a')` returns a table with `|pat| + 1` states over
an alphabet of `sigma` consecutive characters starting at `base`. From state `i`,
reading a character moves to the next prefix-function state; reaching state
`|pat|` means a full match just ended. Use it to run matching as a DP/transition
(e.g. "count strings of length `L` avoiding / containing the pattern").

## Notes

- `find_all` returns empty for an empty pattern.
- For multiple texts against the same pattern, build `KMP` once and reuse it.
- The prefix function alone (`KMP::prefix(s)`) is the building block for string
  periodicity, counting distinct substrings with hashing, and more.
