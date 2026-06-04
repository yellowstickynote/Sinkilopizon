/**
 * Implicit Treap (lazy propagation, dual-type config). Maintains a sequence by
 * position; supports insert/erase/index, range upd/query/reverse, all O(log n).
 *   T = node/aggregate type (sum, min/max, matrix...);  U = lazy-tag type.
 * T and U default to the same type; use Treap<T,U> to separate them. Indices are
 * 0-based. comb may be NON-commutative (a reverse aggregate is tracked so reverse
 * stays correct, e.g. for affine mx+b). Only edit the Customization Section:
 *   ID/LAZY_ID  identities for comb / lazy
 *   comb        merge two aggregates (left,right order preserved)
 *   apply_val   fold a lazy tag into an aggregate spanning node_sz elements
 *   combine_lazy compose tags (old then new); needs operator!= on U
 */
template <class T, class U = T> struct Treap {
    T ID = 0;
    U LAZY_ID = 0;
    T comb(T a, T b) {
        return a + b;
    }
    T apply_val(T node_agg, U lazy_val, int node_sz) {
        return node_agg + lazy_val * node_sz;
    }
    U combine_lazy(U old_lazy, U new_lazy) {
        return old_lazy + new_lazy;
    }
    struct Node {
        int l = 0, r = 0, sz = 1, pri;
        bool rev = false;
        T val, agg, ragg;
        U lazy;
    };
    vector<Node> t;
    int root = 0;
    mt19937 rng{random_device{}()};
    Treap() { t.push_back({0, 0, 0, 0, false, ID, ID, ID, LAZY_ID}); }
    Treap(const vector<T>& v) : Treap() { for (T x : v) push_back(x); }
    int sz(int x) { return t[x].sz; }
    int make(T v) { t.push_back({0, 0, 1, (int)rng(), false, v, v, v, LAZY_ID}); return t.size() - 1; }
    void apply(int x, U v) {
        if (!x) return;
        t[x].val = apply_val(t[x].val, v, 1);
        t[x].agg = apply_val(t[x].agg, v, t[x].sz);
        t[x].ragg = apply_val(t[x].ragg, v, t[x].sz);
        t[x].lazy = combine_lazy(t[x].lazy, v);
    }
    void flip(int x) { if (x) { swap(t[x].l, t[x].r); swap(t[x].agg, t[x].ragg); t[x].rev ^= 1; } }
    void push(int x) {
        if (t[x].lazy != LAZY_ID) { apply(t[x].l, t[x].lazy); apply(t[x].r, t[x].lazy); t[x].lazy = LAZY_ID; }
        if (t[x].rev) { flip(t[x].l); flip(t[x].r); t[x].rev = false; }
    }
    void calc(int x) {
        t[x].sz = 1 + sz(t[x].l) + sz(t[x].r);
        t[x].agg = comb(comb(t[t[x].l].agg, t[x].val), t[t[x].r].agg);
        t[x].ragg = comb(comb(t[t[x].r].ragg, t[x].val), t[t[x].l].ragg);
    }
    void split(int x, int k, int& a, int& b) {
        if (!x) { a = b = 0; return; }
        push(x);
        if (sz(t[x].l) < k) { a = x; split(t[x].r, k - sz(t[x].l) - 1, t[x].r, b); }
        else { b = x; split(t[x].l, k, a, t[x].l); }
        calc(x);
    }
    int merge(int a, int b) {
        if (!a || !b) return a | b;
        if (t[a].pri > t[b].pri) { push(a); t[a].r = merge(t[a].r, b); calc(a); return a; }
        push(b); t[b].l = merge(a, t[b].l); calc(b); return b;
    }
    void insert(int i, T v) { int a, b; split(root, i, a, b); root = merge(merge(a, make(v)), b); }
    void push_back(T v) { insert(sz(root), v); }
    void erase(int i) { int a, b, c; split(root, i, a, b); split(b, 1, b, c); root = merge(a, c); }
    void upd(int l, int r, U v) {
        int a, b, c; split(root, l, a, b); split(b, r - l + 1, b, c);
        apply(b, v); root = merge(merge(a, b), c);
    }
    T query(int l, int r) {
        int a, b, c; split(root, l, a, b); split(b, r - l + 1, b, c);
        T res = t[b].agg; root = merge(merge(a, b), c); return res;
    }
    void reverse(int l, int r) {
        int a, b, c; split(root, l, a, b); split(b, r - l + 1, b, c);
        flip(b); root = merge(merge(a, b), c);
    }
    T operator[](int i) { return query(i, i); }
};
