template<class T, int N, int M, class Add = plus<T>, class Mul = multiplies<T>>
struct Matrix {
    T a[N][M], zero, one;
    Add add;
    Mul mul;

    Matrix(T zero = T(), T one = T(1), Add add = Add(), Mul mul = Mul())
        : zero(zero), one(one), add(add), mul(mul) {
        for (auto& r : a)
            for (auto& x : r)
                x = zero;
    }

    Matrix(initializer_list<initializer_list<T>> x, T zero = T(), T one = T(1),
           Add add = Add(), Mul mul = Mul())
        : zero(zero), one(one), add(add), mul(mul) {
        int i = 0;
        for (auto& r : x) {
            int j = 0;
            for (auto& v : r) a[i][j++] = v;
            assert(j == M);
            i++;
        }
        assert(i == N);
    }

    T* operator[](int i) { return a[i]; }
    const T* operator[](int i) const { return a[i]; }

    template<int K>
    Matrix<T, N, K, Add, Mul> operator*(const Matrix<T, M, K, Add, Mul>& b) const {
        Matrix<T, N, K, Add, Mul> c(zero, one, add, mul);
        for (int i = 0; i < N; i++)
            for (int k = 0; k < M; k++)
                for (int j = 0; j < K; j++)
                    c[i][j] = add(c[i][j], mul(a[i][k], b[k][j]));
        return c;
    }

    static Matrix identity(T zero = T(), T one = T(1),
                           Add add = Add(), Mul mul = Mul()) {
        static_assert(N == M);
        Matrix res(zero, one, add, mul);
        for (int i = 0; i < N; i++) res[i][i] = one;
        return res;
    }

    Matrix pow(long long b) const {
        static_assert(N == M);
        assert(b >= 0);
        Matrix a = *this, r = identity(zero, one, add, mul);
        for (; b; b >>= 1, a = a * a)
            if (b & 1) r = r * a;
        return r;
    }
};
