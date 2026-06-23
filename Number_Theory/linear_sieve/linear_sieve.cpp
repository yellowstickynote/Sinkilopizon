struct LinearSieve {
    int n;
    vector<int> spf, primes;

    LinearSieve(int n) : n(n), spf(n + 1) {
        for (int i = 2; i <= n; i++) {
            if (!spf[i]) spf[i] = i, primes.push_back(i);
            for (int p : primes) {
                if (p > spf[i] || (long long)i * p > n) break;
                spf[i * p] = p;
            }
        }
    }

    bool is_prime(int x) { return x >= 2 && spf[x] == x; }

    vector<pair<int, int>> factorize(int x) {
        vector<pair<int, int>> res;
        while (x > 1) {
            int p = spf[x], e = 0;
            while (x % p == 0) x /= p, e++;
            res.push_back({p, e});
        }
        return res;
    }

    vector<int> divisors(int x) {
        vector<int> res = {1};
        for (auto [p, e] : factorize(x)) {
            int sz = res.size(), pk = 1;
            for (int i = 0; i < e; i++) {
                pk *= p;
                for (int j = 0; j < sz; j++) res.push_back(res[j] * pk);
            }
        }
        return res;
    }
};
