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
            tree[pos >> 1] = comb(tree[pos], tree[pos ^ 1]);
        }
    }

    T query(int l, int r) {
        T res = ID;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = comb(res, tree[l++]);
            if (r & 1) res = comb(res, tree[--r]);
        }
        return res;
    }
};
