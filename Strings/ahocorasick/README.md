# Aho–Corasick

**Type:** `AhoCorasick` · **Complexity:** build `O(Σ·(L + 1))`, `find` / `per_pattern` `O(|t| + L)` (`L` = total pattern length, `Σ` = alphabet size, `t` = text)

## Overview

Multi-pattern matching automaton over any indexable container with `size()`: patterns are
a `vector` of `string`s or of `vector<int>`s, and the text is a `string` or a `vector<int>`.
Symbols are mapped to `0 .. sigma - 1` by subtracting `norm`. Patterns are inserted into a
trie, then suffix links (`back`) are added and every missing transition is filled in, so
reading the text is a plain walk with one table lookup per symbol. Duplicate patterns are
allowed, empty patterns are not (asserted). Node `0` is the root.

Most per-pattern statistics (occurrence count, first / last occurrence, ...) reduce to the
same idea: pattern `j` ends at text position `i` exactly when the state reached after
`t[i]` lies in the subtree of `endNode[j]` in the **suffix-link tree**. So record a value
at each visited state, fold it up the tree once, and read it off at each pattern's end
node. `per_pattern` does this for any `O(1)` merge, in linear time.

## API

| Member | Effect |
|--------|--------|
| `AhoCorasick(pat, sigma, norm = 0)` | Build from patterns (`vector<string>`, `vector<vector<int>>`, ...) whose symbols lie in `[norm, norm + sigma)`. For lowercase strings use `AhoCorasick(pat, 26, 'a')`. |
| `go(v, c)` | Transition from state `v` on the raw symbol `c` (`norm` is subtracted internally; complete automaton, never `-1`). |
| `find(t)` | For each position `i`, the index of the longest pattern ending at `i`, or `-1`. Among identical patterns, the last inserted. |
| `find_all(t)` | For each position `s`, the indices of all patterns **starting** at `s`, shortest first. Output-sensitive: `O(\|t\| + #occurrences)`. |
| `per_pattern<T>(t, id, visit, merge)` | For each pattern, the `merge` of everything `visit` recorded in the subtree of its end node. See below. |
| `push_up(val, merge)` | `val[v]` becomes the `merge` over the subtree of `v` in the suffix-link tree. |
| `push_down(val, merge)` | `val[v]` becomes the `merge` over `v` and all its suffix-link ancestors. |
| `N[v].nmatches` | Number of patterns (duplicates counted) that are a suffix of state `v`'s string. |
| `N[v].end` | Longest pattern that is a suffix of state `v`'s string, or `-1`. |
| `N[v].back` | Suffix link of `v`. |
| `endNode[j]`, `len[j]` | End state and length of pattern `j`. |
| `order` | States in BFS order (root first); parents in the suffix-link tree come before children. |
| `N.size()` | Number of states **plus one**: the last index is an internal sentinel and is not a real state. |

## Customization

`per_pattern<T>(t, id, visit, merge)`:

- `T` — value stored per state (give it explicitly).
- `id` — identity of `merge`, the starting value of every state.
- `visit(cell, i)` — called on the state reached after `t[i]`; update `cell` in place.
- `merge(into, from)` — fold `from` into `into`. Must be associative and commutative.

```cpp
vector<string> pat = {"he", "she", "his", "hers"};
string t = "ushers";
AhoCorasick ac(pat, 26, 'a');            // lowercase letters; for vector<int> data use norm = 0
const int INF = 1e9;
auto add = [](int &a, int b) { a += b; };
auto mn  = [](int &a, int b) { a = min(a, b); };
auto mx  = [](int &a, int b) { a = max(a, b); };

// number of occurrences of each pattern
auto cnt = ac.per_pattern<int>(t, 0, [](int &c, int) { c++; }, add);

// end index of the first / last occurrence (INF / -1 if the pattern never occurs)
auto first_end = ac.per_pattern<int>(t, INF, [](int &c, int i) { c = min(c, i); }, mn);
auto last_end  = ac.per_pattern<int>(t, -1,  [](int &c, int i) { c = max(c, i); }, mx);
// start of the first occurrence: first_end[j] - ac.len[j] + 1
```

Identical patterns share an end node, so they get identical answers.

Other queries of the same shape:

- **Total matches ending at each position** — sum of `nmatches` along the walk (`n = ac.go(n, c)`).
- **Weight of all patterns that are suffixes of each state** — put weights on `endNode[j]` (use `+=` for duplicates), then `push_down(val, add)`; read `val[state]`.
- **Which pattern is the shortest / longest suffix of a state** — `push_down` with `min` / `max` on lengths.

Use `push_up` when many states feed one pattern's answer; use `push_down` when many patterns feed one state's answer.

## Notes

- All indices are 0-based. Symbols outside `[norm, norm + sigma)` are undefined behavior.
- Patterns and text only need to agree on symbol values: e.g. `vector<int>` patterns holding `'a'..'z'` can be matched against a `string` text with `norm = 'a'`.
- `find_all` can return `O(|t| · √L)` entries with distinct patterns; if you only need counts, use `per_pattern` and never enumerate occurrences.
- Transition table is `Σ · (states + 1)` ints (≈ 104 MB for `Σ = 26`, `L = 10^6` with 32-bit `int`; double that under `#define int long long`).
- `merge` must also be correct when `from` is the identity, since untouched states are merged up as well.
- The two loops over `order` are iterative, so deep suffix-link trees (long patterns) cannot overflow the stack.
