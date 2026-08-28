struct SumOp { template <class T> T operator()(T a, T b) const { return a + b; } };

template <class T, class Comb = SumOp> struct BIT {
    T ID;
    Comb comb;
    int n;
    vector<T> bit, arr;

    BIT(int _n = 0, T id = 0, Comb c = Comb()) : ID(id), comb(c) { init(_n); }
    BIT(const vector<T>& v, T id = 0, Comb c = Comb()) : ID(id), comb(c) {
        init(v.size());
        for (int i = 0; i < n; i++) add(i, v[i]);
    }

    void init(int _n) {
        n = _n;
        bit.assign(n + 1, ID);
        arr.assign(n, ID);
    }

    void set(int pos, T val) { add(pos, val - arr[pos]); }

    void add(int pos, T val) {
        arr[pos] += val;
        for (++pos; pos <= n; pos += pos & -pos)
            bit[pos] = comb(bit[pos], val);
    }

    T pref_sum(int pos) {
        T res = ID;
        for (++pos; pos; pos -= pos & -pos)
            res = comb(res, bit[pos]);
        return res;
    }
};
