struct MoQuery {
    int l, r, id;
};

struct MoSolver {
    int n;
    int block_size;
    vector<MoQuery> queries;
    
    function<void(int,bool)> add;
    function<void(int,bool)> remove;
    function<void(int)> answer;

    MoSolver(int _n, const vector<MoQuery>& _queries,
             function<void(int,bool)> _add,
             function<void(int,bool)> _remove,
             function<void(int)> _answer)
        : n(_n), queries(_queries), add(_add), remove(_remove), answer(_answer) 
    {
        block_size = max(1LL, (int)(n / sqrt(queries.size())));
    }

    void solve() {
        sort(queries.begin(), queries.end(), [&](const MoQuery& a, const MoQuery& b) {
            int block_a = a.l / block_size;
            int block_b = b.l / block_size;
            if (block_a != block_b) return block_a < block_b;
            return (block_a % 2 == 1) ? (a.r < b.r) : (a.r > b.r);
        });

        int curr_l = 0;
        int curr_r = -1;

        for (const auto& q : queries) {
            while (curr_l > q.l) add(--curr_l,false);
            while (curr_r < q.r) add(++curr_r,true);
            while (curr_l < q.l) remove(curr_l++,false);
            while (curr_r > q.r) remove(curr_r--,true);
            answer(q.id);
        }
    }
};

/* DOCUMENTATION & USAGE
   ---------------------
   Structure: MoQuery { int l, int r, id; }
   
   Constructor Parameters:
   1. n: Size of the array (used to calculate block size).
   2. queries: Vector of MoQuery objects.
   3. add(index): Adds the element at `index` (in original array) to current state.
   4. remove(index): Removes the element at `index` from current state.
   5. answer(query_id): Saves the current state as the answer for query `query_id`.

   Performance Note:
   This template uses the "Serpentine Sorting" optimization (alternating R direction),
   which reduces movement of the R pointer significantly compared to standard block sorting.

   Example: Count Distinct Elements in Range
   -----------------------------------------
   int current_distinct = 0;
   vector<int> cnt(MAX_VAL, 0);
   vector<int> answers(queries.size());

   MoSolver mo(
       n, queries,
       // Add: if count becomes 1, it's a new distinct element
       [&](int idx) { 
           if (++cnt[arr[idx]] == 1) current_distinct++; 
       },
       // Remove: if count drops to 0, we lost a distinct element
       [&](int idx) { 
           if (--cnt[arr[idx]] == 0) current_distinct--; 
       },
       // Answer: store current state
       [&](int id) { 
           answers[id] = current_distinct; 
       }
   );
   
   mo.solve();
*/
