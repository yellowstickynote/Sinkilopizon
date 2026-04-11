//TreeLCA T(n);
//T.add_edge(u, v);
//T.build(1);
// T.lca(u, v);
// T.kth_parent(u, k);
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
        up.assign(LOG, vector<int>(n + 1, 0));
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
};
