/**
 * Explicit (Key-Ordered) Treap — Lazy Propagation, Triple-Type Configuration
 *
 *   K : key type that orders the set (needs operator<). Keys are unique.
 *   T : value/aggregate type stored at each key (e.g. int sum, struct for min/max).
 *   U : lazy-tag type applied over key ranges (e.g. int range-add, affine struct).
 * Default: T and U coincide. Instantiate as Treap<K>, Treap<K,T>, or Treap<K,T,U>.
 *
 * Unlike the implicit treap (indexed by position), this is indexed by KEY VALUE,
 * so keys may be large/sparse and memory is O(#elements). Ranges in upd/query are
 * inclusive key intervals [lo, hi]. Order-statistics (kth, order_of_key) come free
 * from the size field.
 *
 * Supported: insert(key,val), erase(key), contains(key), upd(lo,hi,tag),
 *            query(lo,hi), kth(k), order_of_key(key), operator[](rank).
 * NOT supported: reverse — reversing a sub-range would violate the key-ordering
 *                invariant. Use the implicit treap if you need positional reversal.
 *
 * Only edit the Customization Section at the top; everything below is mechanical.
 * Invariant preserved by every internal function: push(x) before descending into
 * a child, calc(x) after a child changes.
 */
template <class K, class T = K, class U = T> struct Treap {
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
        K key;
        T val, agg;
        U lazy;
    };
    vector<Node> t;
    int root = 0;
    mt19937 rng{random_device{}()};
    Treap() { t.push_back({0, 0, 0, 0, K{}, ID, ID, LAZY_ID}); }
    int sz(int x) { return t[x].sz; }
    int make(K k, T v) { t.push_back({0, 0, 1, (int)rng(), k, v, v, LAZY_ID}); return t.size() - 1; }
    void apply(int x, U v) {
        if (!x) return;
        t[x].val = apply_val(t[x].val, v, 1);
        t[x].agg = apply_val(t[x].agg, v, t[x].sz);
        t[x].lazy = combine_lazy(t[x].lazy, v);
    }
    void push(int x) {
        if (t[x].lazy != LAZY_ID) { apply(t[x].l, t[x].lazy); apply(t[x].r, t[x].lazy); t[x].lazy = LAZY_ID; }
    }
    void calc(int x) {
        t[x].sz = 1 + sz(t[x].l) + sz(t[x].r);
        t[x].agg = comb(comb(t[t[x].l].agg, t[x].val), t[t[x].r].agg);
    }
    void split(int x, K k, int& a, int& b, bool eq) {
        if (!x) { a = b = 0; return; }
        push(x);
        if (eq ? !(k < t[x].key) : t[x].key < k) { a = x; split(t[x].r, k, t[x].r, b, eq); }
        else { b = x; split(t[x].l, k, a, t[x].l, eq); }
        calc(x);
    }
    int merge(int a, int b) {
        if (!a || !b) return a | b;
        if (t[a].pri > t[b].pri) { push(a); t[a].r = merge(t[a].r, b); calc(a); return a; }
        push(b); t[b].l = merge(a, t[b].l); calc(b); return b;
    }
    void insert(K k, T v) {
        int a, mid, b; split(root, k, a, b, false); split(b, k, mid, b, true);
        if (!mid) mid = make(k, v); root = merge(merge(a, mid), b);
    }
    void erase(K k) {
        int a, mid, b; split(root, k, a, b, false); split(b, k, mid, b, true);
        root = merge(a, b);
    }
    bool contains(K k) {
        int a, mid, b; split(root, k, a, b, false); split(b, k, mid, b, true);
        bool res = mid; root = merge(merge(a, mid), b); return res;
    }
    void upd(K lo, K hi, U v) {
        int a, b, c; split(root, lo, a, b, false); split(b, hi, b, c, true);
        apply(b, v); root = merge(merge(a, b), c);
    }
    T query(K lo, K hi) {
        int a, b, c; split(root, lo, a, b, false); split(b, hi, b, c, true);
        T res = t[b].agg; root = merge(merge(a, b), c); return res;
    }
    int order_of_key(K k) {
        int a, b; split(root, k, a, b, false); int res = sz(a); root = merge(a, b); return res;
    }
    K kth(int k) {
        int x = root;
        while (x) {
            if (sz(t[x].l) == k) return t[x].key;
            if (k < sz(t[x].l)) x = t[x].l; else { k -= sz(t[x].l) + 1; x = t[x].r; }
        }
        return K{};
    }
    K operator[](int rank) { return kth(rank); }
};
