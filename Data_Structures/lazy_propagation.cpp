/**
 * Iterative Lazy Segment Tree (Range Update, Range Query)
 * Default: Range Add / Range Sum. 
 * Customize ID, LAZY_ID, comb(), and apply() for other operations.
 */
template <class T> struct LazySegTree {
    T ID = 0;
    T LAZY_ID = 0;

    T comb(T a, T b) { return a + b; }

    void apply(int i, T val) {
        tree[i] += val * sz[i];
        if (i < n) lazy[i] += val;
    }

    int n, h;
    vector<T> tree, lazy;
    vector<int> sz;

    LazySegTree(int _n = 0) {
        if (_n) init(_n);
    }

    LazySegTree(const vector<T>& v) {
        init(v.size());
        for (int i = 0; i < n; i++) tree[n + i] = v[i];
        for (int i = n - 1; i > 0; --i) tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
    }

    void init(int _n) {
        n = _n;
        h = 32 - __builtin_clz(n);
        tree.assign(2 * n, ID);
        lazy.assign(n, LAZY_ID);
        sz.assign(2 * n, 0);
        for (int i = 0; i < n; i++) sz[n + i] = 1;
        for (int i = n - 1; i > 0; --i) sz[i] = sz[2 * i] + sz[2 * i + 1];
    }

    void push(int i) {
        if (lazy[i] != LAZY_ID) {
            apply(2 * i, lazy[i]);
            apply(2 * i + 1, lazy[i]);
            lazy[i] = LAZY_ID;
        }
    }

    void upd(int l, int r, T val) {
        l += n; r += n + 1;
        int l0 = l, r0 = r - 1;

        for (int s = h; s > 0; --s) {
            int i1 = l0 >> s, i2 = r0 >> s;
            if (i1 > 0 && i1 < n) push(i1);
            if (i2 > 0 && i2 < n) push(i2);
        }

        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) apply(l++, val);
            if (r & 1) apply(--r, val);
        }

        for (l0 >>= 1; l0 > 0; l0 >>= 1) tree[l0] = comb(tree[2 * l0], tree[2 * l0 + 1]);
        for (r0 >>= 1; r0 > 0; r0 >>= 1) tree[r0] = comb(tree[2 * r0], tree[2 * r0 + 1]);
    }

    T query(int l, int r) {
        l += n; r += n + 1;
        int l0 = l, r0 = r - 1;

        for (int s = h; s > 0; --s) {
            int i1 = l0 >> s, i2 = r0 >> s;
            if (i1 > 0 && i1 < n) push(i1);
            if (i2 > 0 && i2 < n) push(i2);
        }

        T res = ID;
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = comb(res, tree[l++]);
            if (r & 1) res = comb(res, tree[--r]);
        }
        return res;
    }
};
