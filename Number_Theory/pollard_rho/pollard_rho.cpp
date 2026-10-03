// Miller-Rabin primality test
using u64 = unsigned long long;
using u128 = __uint128_t;

u64 binpower(u64 base, u64 e, u64 mod) {
    u64 result = 1;
    base %= mod;
    while (e) {
        if (e & 1) result = (u128)result * base % mod;
        base = (u128)base * base % mod;
        e >>= 1;
    }
    return result;
}

bool check_composite(u64 n, u64 a, u64 d, int s) {
    u64 x = binpower(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; r++) {
        x = (u128)x * x % n;
        if (x == n - 1)
            return false;
    }
    return true;
}

bool is_prime(u64 n) {
    if (n < 2) return false;
    int r = 0;
    u64 d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    // Deterministic bases for 64-bit integers
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n == a) return true;
        if (check_composite(n, a, d, r)) return false;
    }
    return true;
}

u64 pollard_rho(u64 n) {
    if (n % 2 == 0) return 2;
    if (is_prime(n)) return n;
    
    auto f = [n](u64 x, u64 c) {
        return (u64)(((u128)x * x % n + c) % n);
    };
    
    u64 x = 0, y = 0, p = 2, q, t = 0, c = rand() % (n - 1) + 1;
    for (int step = 2;; step *= 2) {
        y = x;
        for (int i = 0; i < step; ++i) x = f(x, c);
        for (int i = 0; i < step; i += 128) {
            u64 next_x = x;
            q = 1;
            for (int j = 0; j < std::min(128, step - i); ++j) {
                next_x = f(next_x, c);
                u64 diff = (next_x > y) ? (next_x - y) : (y - next_x);
                q = (u128)q * diff % n;
            }
            x = next_x;
            p = std::gcd(q, n);
            if (p > 1) break;
        }
        if (p > 1) break;
    }
    if (p == n) return pollard_rho(n); // Retry with new random state on failure
    return p;
}

void factorize(u64 n, std::map<u64, int>& factors) {
    if (n == 1) return;
    if (is_prime(n)) {
        factors[n]++;
        return;
    }
    u64 divisor = pollard_rho(n);
    factorize(divisor, factors);
    factorize(n / divisor, factors);
}
