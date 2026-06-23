template <class T> struct SegTree {
    T ID = 0; 
    int n;
    vector<T> tree, tree_rev;

    T comb(T a, T b) { return max(a, b); }

    SegTree(int _n = 0) { init(_n); }

    SegTree(const vector<T>& v) {
        init(v.size());
        for (int i = 0; i < n; i++) {
			if(i<v.size())
            {
				tree[n + i] = v[i];
				tree_rev[n + i] = v[i]; 
			}
        }
        for (int i = n - 1; i > 0; --i) {
            tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
            tree_rev[i] = comb(tree_rev[2 * i + 1], tree_rev[2 * i]);
        }
    }

    void init(int _n) {
		int k = 1;
		while(k<_n) k*=2;
		n = k;
        tree.assign(2 * n, ID);
        tree_rev.assign(2 * n, ID);
    }

    void upd(int pos, T val) {
        int p = pos + n;
        tree[p] = val;
        tree_rev[p] = val;
        for (p >>= 1; p > 0; p >>= 1) {
            tree[p] = comb(tree[p << 1], tree[p << 1 | 1]);
            tree_rev[p] = comb(tree_rev[p << 1 | 1], tree_rev[p << 1]);
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
            if (l & 1) resL = comb(tree_rev[l++], resL);
            if (r & 1) resR = comb(resR, tree_rev[--r]);
        }
        return comb(resR, resL);
    }
};
