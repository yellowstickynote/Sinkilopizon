template <class ST, class T, class U = T> struct TreeHLD {
    int n, cur_pos;
    vector<vector<int>> g;
    vector<int> parent, depth, heavy, head, pos, sz;
    ST tree;

    TreeHLD(int _n = 0) : tree(_n) { if (_n) init(_n); }

    void init(int _n) {
        n = _n;
        cur_pos = 0;
        g.assign(n + 1, {});
        parent.assign(n + 1, 0);
        depth.assign(n + 1, 0);
        heavy.assign(n + 1, -1);
        head.assign(n + 1, 0);
        pos.assign(n + 1, 0);
        sz.assign(n + 1, 0);
        tree = ST(n);
    }

    void add_edge(int u, int v) {
        g[u].push_back(v); g[v].push_back(u);
    }

    int dfs_sz(int v, int p) {
        sz[v] = 1;
        int max_c_size = 0;
        parent[v] = p;
        depth[v] = (p ? depth[p] + 1 : 0);
        for (int to : g[v]) {
            if (to != p) {
                dfs_sz(to, v);
                sz[v] += sz[to];
                if (sz[to] > max_c_size) {
                    max_c_size = sz[to];
                    heavy[v] = to;
                }
            }
        }
        return sz[v];
    }

    void dfs_hld(int v, int h) {
        head[v] = h;
        pos[v] = cur_pos++;
        if (heavy[v] != -1) dfs_hld(heavy[v], h);
        for (int to : g[v]) {
            if (to != parent[v] && to != heavy[v]) dfs_hld(to, to);
        }
    }

    void dfs_hld(int v, int h, const vector<T>& vals, vector<T>& linear_vals) {
        head[v] = h;
        pos[v] = cur_pos++;
        linear_vals[pos[v]] = vals[v];
        if (heavy[v] != -1) dfs_hld(heavy[v], h, vals, linear_vals);
        for (int to : g[v]) {
            if (to != parent[v] && to != heavy[v]) dfs_hld(to, to, vals, linear_vals);
        }
    }

    void build(int root = 1) {
        dfs_sz(root, 0);
        dfs_hld(root, root);
        tree = ST(n);
    }

    void build(const vector<T>& vals, int root = 1) {
        dfs_sz(root, 0);
        vector<T> linear_vals(n);
        dfs_hld(root, root, vals, linear_vals);
        tree = ST(linear_vals);
    }

    int lca(int u, int v) {
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) u = parent[head[u]];
            else v = parent[head[v]];
        }
        return (depth[u] < depth[v] ? u : v);
    }

    void upd_node(int u, U val) {
        tree.upd(pos[u], val);
    }

    void upd_path(int u, int v, U val) {
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                tree.upd(pos[head[u]], pos[u], val);
                u = parent[head[u]];
            } else {
                tree.upd(pos[head[v]], pos[v], val);
                v = parent[head[v]];
            }
        }
        if (pos[u] <= pos[v]) tree.upd(pos[u], pos[v], val);
        else                  tree.upd(pos[v], pos[u], val);
    }

    void upd_subtree(int u, U val) {
        tree.upd(pos[u], pos[u] + sz[u] - 1, val);
    }

    T query_path(int u, int v) {
        T res_u = tree.ID, res_v = tree.ID;
        while (head[u] != head[v]) {
            if (depth[head[u]] > depth[head[v]]) {
                res_u = tree.comb(res_u, tree.query_rev(pos[head[u]], pos[u]));
                u = parent[head[u]];
            } else {
                res_v = tree.comb(tree.query(pos[head[v]], pos[v]), res_v);
                v = parent[head[v]];
            }
        }
        if (depth[u] >= depth[v]) {
            res_u = tree.comb(res_u, tree.query_rev(pos[v], pos[u]));
        } else {
            res_v = tree.comb(tree.query(pos[u], pos[v]), res_v);
        }
        return tree.comb(res_u, res_v);
    }

    T query_subtree(int u) {
        return tree.query(pos[u], pos[u] + sz[u] - 1);
    }
};
