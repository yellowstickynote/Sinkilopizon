#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct MoQuery {
    int l, r, id;
};

struct MoSolver {
    int n;
    long long block_size;
    vector<MoQuery> queries;
    
    // DEFINE GLOBAL STATE HERE

    MoSolver(int _n, const vector<MoQuery>& _queries) : n(_n), queries(_queries) {
        block_size = max(1LL, (long long)(n / sqrt(queries.size())));
        // INITIALIZE STATE HERE
    }

    void add(int i) {
        
    }

    void remove(int i) {
        
    }

    void answer(int i) {
        
    }

    void solve() {
        sort(queries.begin(), queries.end(), [&](const MoQuery& a, const MoQuery& b) {
            long long block_a = a.l / block_size;
            long long block_b = b.l / block_size;
            if (block_a != block_b) return block_a < block_b;
            return (block_a % 2 == 1) ? (a.r < b.r) : (a.r > b.r);
        });

        int curr_l = 0;
        int curr_r = -1;

        for (const auto& q : queries) {
            while (curr_l > q.l) {
                curr_l--;
                add(curr_l);
            }
            while (curr_r < q.r) {
                curr_r++;
                add(curr_r);
            }
            while (curr_l < q.l) {
                remove(curr_l);
                curr_l++;
            }
            while (curr_r > q.r) {
                remove(curr_r);
                curr_r--;
            }
            answer(q.id);
        }
    }
};

/* DOCUMENTATION & USAGE
   ---------------------
   Structure: MoQuery { int l, int r, id; }
   
   1. Setup:
      - Define your state variables (e.g., frequency array, count) inside the struct.
      - Initialize them in the constructor.
      
   2. Implementation:
      - add(i): Update state when adding index `i` to the range.
      - remove(i): Update state when removing index `i` from the range.
      - answer(i): Store the current answer for query index `i`.
      
   3. Execution:
      MoSolver mo(n, queries);
      mo.solve();
      
   Notes:
   - Uses Serpentine Sorting for O(N * sqrt(Q)) optimization.
   - `i` refers to the index in the original array (0-based) for add/remove.
   - `i` refers to the query ID for answer.
*/
