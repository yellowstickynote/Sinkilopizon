//TreeLCA T(n);
//for (int i = 1; i <= n; ++i) cin >> T.val[i];
//for (int i = 0; i < n-1; ++i) {
//    int u, v; cin >> u >> v;
//    T.add_edge(u, v);
//}
//T.build(1);
// then:
// T.lca(u, v);
// T.kth_parent(u, k);
// T.sum_on_path(u, v);
// T.min_on_path(u, v);
// T.max_on_path(u, v);
struct TreeLCA {
    struct Agg {
        long long sum;
        long long mn;
        long long mx;
    };

    int n, LOG;
    const long long INF = (long long)4e18;

    vector<vector<int>> g;
    vector<int> depth;
    vector<vector<int>> up;

    TreeLCA(int _n = 0) { if (_n) init(_n); }

    void init(int _n) {
        n = _n;
        LOG = 32 - __builtin_clz(n);
        g.assign(n + 1, {});
        depth.assign(n + 1, 0);

    }

    void add_edge(int u, int v) {
        g[u].push_back(v);
        g[v].push_back(u);
    }

    void dfs(int v, int p) {
        up[0][v] = p;
        if (p == 0) depth[v] = 0;
        else depth[v] = depth[p] + 1;

        for (int k = 1; k < LOG; ++k) {
            int mid = up[k - 1][v];
            up[k][v] = up[k - 1][mid];

        }

        for (int to : g[v]) if (to != p) dfs(to, v);
    }

    void build(int root = 1) {
        dfs(root, 0);
    }

    int kth_parent(int v, int k) {
        for (int i = 0; i < LOG && v; ++i)
            if (k & (1 << i))
                v = up[i][v];
        return v; // 0 if we go above root
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int i = 0; i < LOG; ++i)
            if (diff & (1 << i))
                a = up[i][a];
        if (a == b) return a;
        for (int i = LOG - 1; i >= 0; --i) {
            if (up[i][a] != up[i][b]) {
                a = up[i][a];
                b = up[i][b];
            }
        }
        return up[0][a];
    }

    Agg merge(const Agg &A, const Agg &B) {
        return {A.sum + B.sum,
                min(A.mn, B.mn),
                max(A.mx, B.mx)};
    }

    // path from v up by `steps` edges, including start and end
    Agg climb(int v, int steps) {
        Agg res{val[v], val[v], val[v]}; // start with node v
        for (int i = 0; i < LOG; ++i) {
            if (steps & (1 << i)) {
                res.sum += upSum[i][v];
                res.mn = min(res.mn, upMin[i][v]);
                res.mx = max(res.mx, upMax[i][v]);
                v = up[i][v];
            }
        }
        return res;
    }

    // aggregate over simple path a-b (all node values)
    Agg path_agg(int a, int b) {
        int c = lca(a, b);

        // a -> c (inclusive)
        Agg A = climb(a, depth[a] - depth[c]);
        if (b == c) return A;

        // b -> child of c (inclusive), exclude c to avoid double-count
        int steps = depth[b] - depth[c] - 1;
        Agg B = climb(b, steps);

        return merge(A, B);
    }

    long long sum_on_path(int a, int b) {
        return path_agg(a, b).sum;
    }

    long long min_on_path(int a, int b) {
        return path_agg(a, b).mn;
    }

    long long max_on_path(int a, int b) {
        return path_agg(a, b).mx;
    }
};
