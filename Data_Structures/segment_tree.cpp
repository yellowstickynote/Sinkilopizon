template <class T> struct SegTree {
    T ID = 0; 
    int n;
    vector<T> tree;

    T comb(T a, T b) { return a + b; }

    SegTree(int _n) : n(_n), tree(4 * _n, ID) {}
    SegTree(const vector<T>& v) : n(v.size()), tree(4 * v.size(), ID) {
        build(v, 1, 0, n - 1);
    }

    void build(const vector<T>& v, int node, int tl, int tr) {
        if (tl == tr) {
            tree[node] = v[tl];
            return;
        }
        int tm = (tl + tr) / 2;
        build(v, 2 * node, tl, tm);
        build(v, 2 * node + 1, tm + 1, tr);
        tree[node] = comb(tree[2 * node], tree[2 * node + 1]);
    }

    void upd(int pos, T val, int node, int tl, int tr) {
        if (tl == tr) {
            tree[node] = val;
            return;
        }
        int tm = (tl + tr) / 2;
        if (pos <= tm) upd(pos, val, 2 * node, tl, tm);
        else upd(pos, val, 2 * node + 1, tm + 1, tr);
        tree[node] = comb(tree[2 * node], tree[2 * node + 1]);
    }
    void upd(int pos, T val) { upd(pos, val, 1, 0, n - 1); }

    T query(int l, int r, int node, int tl, int tr) {
        if (l > tr || r < tl) return ID;
        if (l <= tl && tr <= r) return tree[node];
        int tm = (tl + tr) / 2;
        return comb(query(l, r, 2 * node, tl, tm), 
                    query(l, r, 2 * node + 1, tm + 1, tr));
    }
    T query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};
