// Segment Tree for Non-Commutative Operations
// - T comb(T a, T b): Order matters! Combines 'a' (left branch) and 'b' (right branch).
// - void upd(int pos, T val): Point update.
// - T query(int l, int r): Left-to-right range query (top-to-bottom on HLD).
// - T query_rev(int l, int r): Right-to-left range query (bottom-to-top on HLD).

template <class T> struct SegTree {
    T ID = 0; 
    int n;
    vector<T> tree;

    T comb(T a, T b) { return max(a, b); }

    SegTree(int _n = 0) {
        init(_n);
    }

    SegTree(const vector<T>& v) {
        init(v.size());
        for (int i = 0; i < n; i++) tree[n + i] = v[i];
        for (int i = n - 1; i > 0; --i) tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
    }

    void init(int _n) {
        n = _n;
        tree.assign(2 * n, ID);
    }

    void upd(int pos, T val) {
        for (tree[pos += n] = val; pos > 1; pos >>= 1) {
            tree[pos >> 1] = comb(tree[pos & ~1], tree[pos | 1]);
        }
    }

    T query(int l, int r) {
        T resL = ID, resR = ID;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = comb(resL, tree[l++]);
            if (r & 1) resR = comb(tree[--r], resR);
        }
        return comb(resL, resR);
    }

    T query_rev(int l, int r) {
        T resL = ID, resR = ID;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resL = comb(tree[l++], resL);
            if (r & 1) resR = comb(resR, tree[--r]);
        }
        return comb(resR, resL);
    }
};
