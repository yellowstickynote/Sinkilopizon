# Mo's Algorithm

**Type:** `MoSolver` · **Complexity:** `O((N + Q) · sqrt(Q))`

## Overview

Offline range-query technique. Sorts queries so that the `[curr_l, curr_r]`
window moves as little as possible, answering each query by incrementally adding
/ removing single elements. Uses **serpentine (snake) sorting** — alternating the
sort direction of `r` per block — for the `O((N+Q)·sqrt(Q))` bound.

`MoQuery` holds `{ int l, r, id; }`. Indices `l, r` are into the original array
(0-based); `id` is the query's position so answers can be written back in input
order.

## Usage

1. **Setup** — define your state variables (frequency array, current count, …)
   where it says `// DEFINE GLOBAL STATE HERE`, and initialize them in the
   constructor at `// INITIALIZE STATE HERE`.
2. **Implement the three hooks:**
   - `add(i)` — update state when index `i` enters the window.
   - `remove(i)` — update state when index `i` leaves the window.
   - `answer(i)` — record the current answer for query `id == i`.
3. **Run:**
   ```cpp
   MoSolver mo(n, queries);
   mo.solve();
   ```

## Notes

- In `add`/`remove`, `i` is an **array index** (0-based). In `answer`, `i` is the **query id**.
- Queries must be known up front (offline).
