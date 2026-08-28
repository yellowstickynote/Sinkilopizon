struct SumOp {
    template <class T>
    T operator()(T a, T b) const { return a + b; }
};

struct NegOp {
    template <class T>
    T operator()(T a) const { return -a; }
};

template <class T, class Comb = SumOp, class Neg = NegOp> struct BIT {
    int n;
    T ID;
    Comb comb;
    Neg neg;
    vector<T> bit, arr;

    BIT(int n = 0, T id = 0, Comb c = Comb(), Neg ng = Neg())
        : n(n), ID(id), comb(c), neg(ng), bit(n + 1, ID), arr(n, ID) {}

    void add(int pos, T val) {
        arr[pos] = comb(arr[pos], val);
        for (++pos; pos <= n; pos += pos & -pos)
            bit[pos] = comb(bit[pos], val);
    }

    void set(int pos, T val) {
        add(pos, comb(neg(arr[pos]), val));
    }

    T pref_sum(int pos) {
        T res = ID;
        for (++pos; pos; pos -= pos & -pos)
            res = comb(res, bit[pos]);
        return res;
    }
};
