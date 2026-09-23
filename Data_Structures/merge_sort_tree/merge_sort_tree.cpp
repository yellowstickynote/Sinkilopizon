template <class T> struct MergeSortTree {
    int n;
    vector<vector<T>> tree;

    MergeSortTree(int _n = 0) { init(_n); }

    MergeSortTree(const vector<T>& v) {
        init(v.size());
        for (int i = 0; i < v.size(); i++) tree[n + i] = {v[i]};
        for (int i = n - 1; i > 0; --i) {
            tree[i].resize(tree[2 * i].size() + tree[2 * i + 1].size());
            merge(tree[2 * i].begin(), tree[2 * i].end(),
                  tree[2 * i + 1].begin(), tree[2 * i + 1].end(),
                  tree[i].begin());
        }
    }

    void init(int _n) {
        for (n = 1; n < _n; n *= 2);
        tree.assign(2 * n, {});
    }

    int bs_calc(const vector<T>& v, const T& vmin, const T& vmax) {
        return upper_bound(v.begin(), v.end(), vmax) -
               lower_bound(v.begin(), v.end(), vmin);
    }

    int query(int l, int r, const T& vmin, const T& vmax) {
        int res = 0;
        for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res += bs_calc(tree[l++], vmin, vmax);
            if (r & 1) res += bs_calc(tree[--r], vmin, vmax);
        }
        return res;
    }
};
