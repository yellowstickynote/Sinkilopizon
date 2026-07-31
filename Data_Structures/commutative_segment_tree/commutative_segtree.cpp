#include <vector>
using namespace std;

struct MaxOp { template <class T> T operator()(T a, T b) const { return max(a, b); } };

template <class T, class Comb = MaxOp> struct SegTree {
    T ID;
    Comb comb;
    int n;
    vector<T> tree;

    SegTree(int _n = 0, T id = 0, Comb c = Comb()) : ID(id), comb(c) { init(_n); }
    SegTree(const vector<T>& v, T id = 0, Comb c = Comb()) : ID(id), comb(c) {
        init(v.size());
        for (int i = 0; i < v.size(); i++) tree[n + i] = v[i];
        for (int i = n - 1; i > 0; --i) {
            tree[i] = comb(tree[2 * i], tree[2 * i + 1]);
        }
    }

    void init(int _n) {
        for (n = 1; n < _n; n *= 2);
        tree.assign(2 * n, ID);
    }

    void upd(int pos, T val) {
        int p = pos + n;
        tree[p] = val;
        for (p >>= 1; p > 0; p >>= 1) {
            tree[p] = comb(tree[p << 1], tree[p << 1 | 1]);
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
};
