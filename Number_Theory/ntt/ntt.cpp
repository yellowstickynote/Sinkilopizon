const int MOD = 998244353;
const int G = 3; // Primitive root for 998244353

// Helper: Fast modular exponentiation
long long power(long long base, long long exp) {
    long long res = 1;
    base %= MOD;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % MOD;
        base = (base * base) % MOD;
        exp /= 2;
    }
    return res;
}

// Helper: Modular inverse using Fermat's Little Theorem
long long modInverse(long long n) {
    return power(n, MOD - 2);
}

void ntt(vector<long long>& a, bool invert) {
    int n = a.size();
    
    // 1. Bit-reversal permutation
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1)
            j ^= bit;
        j ^= bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    
    // 2. Iterative Cooley-Tukey over Finite Field
    for (int len = 2; len <= n; len <<= 1) {
        long long wlen = power(G, (MOD - 1) / len);
        if (invert)
            wlen = modInverse(wlen);
        
        for (int i = 0; i < n; i += len) {
            long long w = 1;
            for (int j = 0; j < len / 2; j++) {
                long long u = a[i + j];
                long long v = (a[i + j + len / 2] * w) % MOD;
                
                // Optimized modulo addition/subtraction
                a[i + j] = (u + v < MOD ? u + v : u + v - MOD);
                a[i + j + len / 2] = (u - v >= 0 ? u - v : u - v + MOD);
                w = (w * wlen) % MOD;
            }
        }
    }
    
    // 3. Scaling for inverse transform
    if (invert) {
        long long n_inv = modInverse(n);
        for (long long& x : a)
            x = (x * n_inv) % MOD;
    }
}

vector<long long> multiply(const vector<long long>& a, const vector<long long>& b) {
    vector<long long> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    
    fa.resize(n);
    fb.resize(n);

    // 1. Forward NTT
    ntt(fa, false);
    ntt(fb, false);
    
    // 2. Pointwise modular multiplication
    for (int i = 0; i < n; i++)
        fa[i] = (fa[i] * fb[i]) % MOD;
        
    // 3. Inverse NTT
    ntt(fa, true);

    // 4. Shrink to degree without rounding
    fa.resize(a.size() + b.size() - 1);
    return fa;
}
