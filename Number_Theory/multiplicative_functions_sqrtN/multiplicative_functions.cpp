struct MultiplicativeFunctions {
    static vector<pair<long long, int>> factorize(long long n) {
        vector<pair<long long, int>> res;
        for (long long p = 2; p * p <= n; p++) {
            if (n % p) continue;
            int e = 0;
            while (n % p == 0) n /= p, e++;
            res.push_back({p, e});
        }
        if (n > 1) res.push_back({n, 1});
        return res;
    }

    static long long tau(long long n) {
        long long res = 1;
        for (auto [p, e] : factorize(n)) res *= e + 1;
        return res;
    }

    static long long sigma(long long n) {
        long long res = 1;
        for (auto [p, e] : factorize(n)) {
            long long s = 1, pk = 1;
            while (e--) s += pk *= p;
            res *= s;
        }
        return res;
    }

    static int mu(long long n) {
        int res = 1;
        for (auto [p, e] : factorize(n)) {
            if (e > 1) return 0;
            res = -res;
        }
        return res;
    }

    static long long phi(long long n) {
        for (auto [p, e] : factorize(n)) n = n / p * (p - 1);
        return n;
    }
};
