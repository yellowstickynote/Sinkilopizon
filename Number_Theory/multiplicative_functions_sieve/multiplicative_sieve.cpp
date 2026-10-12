struct MultiplicativeSieve {
    int n;
    vector<int> primes, mu, tau;
    vector<long long> phi, sigma;

    MultiplicativeSieve(int n) : n(n), mu(n + 1), tau(n + 1), phi(n + 1), sigma(n + 1) {
        vector<int> spf(n + 1), e(n + 1);
        vector<long long> pk(n + 1);
        if (n >= 1) mu[1] = tau[1] = phi[1] = sigma[1] = 1;
        for (int i = 2; i <= n; i++) {
            if (!spf[i]) {
                spf[i] = i, primes.push_back(i);
                mu[i] = -1, tau[i] = 2, phi[i] = i - 1, sigma[i] = pk[i] = i + 1, e[i] = 1;
            }
            for (int p : primes) {
                if (p > spf[i] || (long long)i * p > n) break;
                int m = i * p;
                spf[m] = p;
                if (p == spf[i]) {
                    mu[m] = 0, e[m] = e[i] + 1, tau[m] = tau[i] / (e[i] + 1) * (e[i] + 2);
                    phi[m] = phi[i] * p, pk[m] = pk[i] * p + 1, sigma[m] = sigma[i] / pk[i] * pk[m];
                } else {
                    mu[m] = -mu[i], e[m] = 1, tau[m] = tau[i] * 2;
                    phi[m] = phi[i] * (p - 1), pk[m] = p + 1, sigma[m] = sigma[i] * (p + 1);
                }
            }
        }
    }
};
