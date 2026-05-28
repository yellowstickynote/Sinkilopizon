// TreeLCA T(n); -> Initialize 1-indexed tree with n nodes
// T.add_edge(u, v); -> Add bidirectional/undirected edge between u and v
// T.build(root); -> Precompute depth and binary lifting table (default root = 1)
// T.lca(u, v); -> Find Lowest Common Ancestor of u and v in O(log n)
// T.kth_parent(u, k); -> Find k-th ancestor of u in O(log n), returns 0 if out of bounds
// T.dist(u, v); -> Find distance (number of edges) between u and v in O(log n)
struct TreeLCA {
    int n, lg;
    vector<vector<int>> g, up;
    vector<int> depth;

    TreeLCA(int n = 0) { if (n) init(n); }

    void init(int _n) {
        n = _n; 
        lg = 32 - __builtin_clz(n);
        g.assign(n + 1, {});
        depth.assign(n + 1, 0);
        up.assign(lg, vector<int>(n + 1, 0));
    }

    void add_edge(int u, int v) {
        g[u].push_back(v); g[v].push_back(u);
    }

    void dfs(int v, int p) {
        up[0][v] = p;
        depth[v] = (p ? depth[p] + 1 : 0);
        for (int i = 1; i < lg; ++i) up[i][v] = up[i - 1][up[i - 1][v]];
        for (int to : g[v]) if (to != p) dfs(to, v);
    }

    void build(int root = 1) { dfs(root, 0); }

    int kth_parent(int v, int k) {
        for (int i = 0; i < lg && v; ++i)
            if (k & (1 << i)) v = up[i][v];
        return v;
    }

    int lca(int a, int b) {
        if (depth[a] < depth[b]) swap(a, b);
        int diff = depth[a] - depth[b];
        for (int i = 0; i < lg; ++i)
            if (diff & (1 << i)) a = up[i][a];
        if (a == b) return a;
        for (int i = lg - 1; i >= 0; --i) {
            if (up[i][a] != up[i][b]) {
                a = up[i][a];
                b = up[i][b];
            }
        }
        return up[0][a];
    }

    int dist(int a, int b) { 
        return depth[a] + depth[b] - 2 * depth[lca(a, b)]; 
    }
};
