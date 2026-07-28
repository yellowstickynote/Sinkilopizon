struct MaxOp { template <class T> T operator()(T a, T b) const { return max(a, b); } };
template <class T, class Comb = MaxOp> struct PersistentSegTree {
    struct Node {
        int l, r;
        T val;
    };
    vector<Node> tree;
    int sz;
    T ID;
    Comb comb;

    PersistentSegTree(int n, T id = 0, Comb c = Comb()) : sz(n), ID(id), comb(c) {
        tree.push_back({0, 0, ID});
    }

    int createNode(T val, int l = 0, int r = 0) {
        tree.push_back({l, r, val});
        return (int)tree.size() - 1;
    }

    int build(const vector<T>& arr) { return build(arr, 0, sz); }
    int build(const vector<T>& arr, int lx, int rx) {
        if (rx - lx == 1) return createNode(lx < arr.size() ? arr[lx] : ID);
        int m = lx + (rx - lx) / 2;
        int l = build(arr, lx, m), r = build(arr, m, rx);
        return createNode(comb(tree[l].val, tree[r].val), l, r);
    }

    int update(int root, int i, T val) { return update(root, i, val, 0, sz); }
    int update(int cur, int i, T val, int lx, int rx) {
        if (rx - lx == 1) return createNode(val);
        int m = (rx + lx) / 2, cl = cur ? tree[cur].l : 0, cr = cur ? tree[cur].r : 0;
        if (i < m) {
            int nl = update(cl, i, val, lx, m);
            return createNode(comb(tree[nl].val, tree[cr].val), nl, cr);
        }
        int nr = update(cr, i, val, m, rx);
        return createNode(comb(tree[cl].val, tree[nr].val), cl, nr);
    }

    T query(int root, int l, int r) { return query(root, l, r + 1, 0, sz); }
    T query(int cur, int l, int r, int lx, int rx) {
        if (rx <= l || lx >= r || cur == 0) return ID;
        if (rx <= r && lx >= l) return tree[cur].val;
        int m = lx + (rx - lx) / 2;
        return comb(query(tree[cur].l, l, r, lx, m), query(tree[cur].r, l, r, m, rx));
    }
};
