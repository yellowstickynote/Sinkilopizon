/**
 * Lazy Segment Tree (Range Update, Range Query)
 * Interchangeable with standard SegTree. 
 * Default configured for Range Add / Range Sum.
 */
template <class T> struct LazySegTree {
    T ID = 0;
    T LAZY_ID = 0;
    int n;
    vector<T> tree, lazy;

    T comb(T a, T b) { return a + b; }

    LazySegTree(int _n) : n(_n), tree(4 * _n, ID), lazy(4 * _n, LAZY_ID) {}
    LazySegTree(const vector<T>& v) : n(v.size()), tree(4 * v.size(), ID), lazy(4 * v.size(), LAZY_ID) {
        build(v, 1, 0, n - 1);
    }

    void push(int node, int tl, int tr) {
        if (lazy[node] != LAZY_ID) {
            tree[node] += lazy[node] * (tr - tl + 1);
            if (tl != tr) {
                lazy[2 * node] += lazy[node];
                lazy[2 * node + 1] += lazy[node];
            }
            lazy[node] = LAZY_ID;
        }
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

    void upd(int l, int r, T val, int node, int tl, int tr) {
        push(node, tl, tr);
        if (l > tr || r < tl) return;
        if (l <= tl && tr <= r) {
            lazy[node] += val;
            push(node, tl, tr);
            return;
        }
        int tm = (tl + tr) / 2;
        upd(l, r, val, 2 * node, tl, tm);
        upd(l, r, val, 2 * node + 1, tm + 1, tr);
        tree[node] = comb(tree[2 * node], tree[2 * node + 1]);
    }
    void upd(int l, int r, T val) { upd(l, r, val, 1, 0, n - 1); }

    T query(int l, int r, int node, int tl, int tr) {
        push(node, tl, tr);
        if (l > tr || r < tl) return ID;
        if (l <= tl && tr <= r) return tree[node];
        int tm = (tl + tr) / 2;
        return comb(query(l, r, 2 * node, tl, tm), 
                    query(l, r, 2 * node + 1, tm + 1, tr));
    }
    T query(int l, int r) { return query(l, r, 1, 0, n - 1); }
};
