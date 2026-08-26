struct Matrix {
    int n, m;
    T zero, one;
    Add add;
    Mul mul;
    vector<vector<T>> a;

    Matrix(int n = 0, int m = 0, T zero = T(), T one = T(1),
           Add add = Add(), Mul mul = Mul())
        : n(n), m(m), zero(zero), one(one), add(add), mul(mul),
          a(n, vector<T>(m, zero)) {}

    Matrix(initializer_list<vector<T>> a, T zero = T(), T one = T(1),
           Add add = Add(), Mul mul = Mul())
        : n(a.size()), m(n ? a.begin()->size() : 0), zero(zero), one(one),
          add(add), mul(mul), a(a) {}
    Matrix(vector<vector<T>> a, T zero = T(), T one = T(1),
           Add add = Add(), Mul mul = Mul())
        : n(a.size()), m(n ? a.begin()->size() : 0), zero(zero), one(one),
          add(add), mul(mul), a(a) {}

    vector<T>& operator[](int i) { return a[i]; }
    const vector<T>& operator[](int i) const { return a[i]; }

    Matrix operator*(const Matrix& b) const {
        assert(m == b.n);
        Matrix c(n, b.m, zero, one, add, mul);
        for (int i = 0; i < n; i++)
            for (int k = 0; k < m; k++)
                for (int j = 0; j < b.m; j++)
                    c[i][j] = add(c[i][j], mul(a[i][k], b[k][j]));
        return c;
    }

    Matrix pow(long long b) const {
        assert(n == m && b >= 0);
        Matrix a = *this, r(n, n, zero, one, add, mul);
        for (int i = 0; i < n; i++) r[i][i] = one;
        for (; b; b >>= 1, a = a * a)
            if (b & 1) r = r * a;
        return r;
    }
};
