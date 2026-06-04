/**
 * Explicit (Key-Ordered) Treap Forest — Lazy Propagation.
 *
 *   K : key type ordering the set (needs operator<); keys unique within a tree.
 *   T : value/aggregate type (e.g. int sum, struct for min/max).
 *   U : lazy-tag type over key ranges (e.g. int range-add, affine struct).
 * Instantiate ONCE as Treap<K>, Treap<K,T>, or Treap<K,T,U>; it owns all trees of
 * that type. A tree is a root index you track yourself; init() hands you an empty one.
 *
 * Mutators take the root by reference and are void, so a root that shifts is written
 * back automatically. Pure reads return their result. Ranges are CLOSED [lo,hi].
 *
 *   init()              : return a fresh empty tree (== 0).
 *   split(x,k,a,b,eq)   : cut x by key; a,b get the two sides. eq=false -> {<k}|{>=k},
 *                         eq=true -> {<=k}|{>k}.
 *   merge(a,b,c)        : CONCATENATE ordered disjoint subtrees (all keys in a < all
 *                         keys in b); result -> c. Use for split-then-rejoin.
 *   unite(a,b,c)        : key-set UNION of two arbitrary trees, O(M log(N/M)); result
 *                         -> c. On a shared key keeps a's node. Inputs are consumed.
 *   intersect(a,b,c)    : key-set INTERSECTION (keys in both), O(M log(N/M)); result
 *                         -> c, nodes taken from a. Inputs are consumed.
 *   insert(r,k,v)       : add key k (no-op if present).   erase(r,k) : remove key k.
 *   upd(r,lo,hi,tag)    : apply tag over [lo,hi].
 *   query(r,lo,hi)      : aggregate over [lo,hi].          contains(r,k) : membership.
 *   order_of_key(r,k)   : number of keys < k.              kth(r,i) : key at rank i.
 *
 * Internals keep the invariant push(x) before descent, calc(x) after a child changes.
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
    mt19937 rng{random_device{}()};
    Treap() { t.push_back({0, 0, 0, 0, K{}, ID, ID, LAZY_ID}); }
    int init() { return 0; }
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
    void merge(int a, int b, int& c) {
        if (!a || !b) { c = a | b; return; }
        if (t[a].pri > t[b].pri) { push(a); merge(t[a].r, b, t[a].r); calc(a); c = a; }
        else { push(b); merge(a, t[b].l, t[b].l); calc(b); c = b; }
    }
    void unite(int a, int b, int& c) {
        if (!a || !b) { c = a | b; return; }
        if (t[a].pri < t[b].pri) swap(a, b);
        push(a);
        int l, r, dup; split(b, t[a].key, l, b, false); split(b, t[a].key, dup, r, true);
        unite(t[a].l, l, t[a].l); unite(t[a].r, r, t[a].r);
        calc(a); c = a;
    }
    void intersect(int a, int b, int& c) {
        if (!a || !b) { c = 0; return; }
        if (t[a].pri < t[b].pri) swap(a, b);
        push(a);
        int l, r, dup; split(b, t[a].key, l, b, false); split(b, t[a].key, dup, r, true);
        int lc, rc; intersect(t[a].l, l, lc); intersect(t[a].r, r, rc);
        if (dup) { t[a].l = lc; t[a].r = rc; calc(a); c = a; }
        else merge(lc, rc, c);
    }
    void insert(int& r, K k, T v) {
        int a, mid, b; split(r, k, a, b, false); split(b, k, mid, b, true);
        if (!mid) mid = make(k, v);
        merge(mid, b, mid); merge(a, mid, r);
    }
    void erase(int& r, K k) {
        int a, mid, b; split(r, k, a, b, false); split(b, k, mid, b, true);
        merge(a, b, r);
    }
    bool contains(int& r, K k) {
        int a, mid, b; split(r, k, a, b, false); split(b, k, mid, b, true);
        bool res = mid; merge(mid, b, mid); merge(a, mid, r); return res;
    }
    void upd(int& r, K lo, K hi, U v) {
        int a, b, c; split(r, lo, a, b, false); split(b, hi, b, c, true);
        apply(b, v); merge(b, c, b); merge(a, b, r);
    }
    T query(int& r, K lo, K hi) {
        int a, b, c; split(r, lo, a, b, false); split(b, hi, b, c, true);
        T res = t[b].agg; merge(b, c, b); merge(a, b, r); return res;
    }
    int order_of_key(int& r, K k) {
        int a, b; split(r, k, a, b, false); int res = sz(a); merge(a, b, r); return res;
    }
    K kth(int& r, int i) {
        int x = r;
        while (x) {
            if (sz(t[x].l) == i) return t[x].key;
            if (i < sz(t[x].l)) x = t[x].l; else { i -= sz(t[x].l) + 1; x = t[x].r; }
        }
        return K{};
    }
};
