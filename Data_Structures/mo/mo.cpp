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

