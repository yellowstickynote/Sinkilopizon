template <signed MOD> struct ModInt {
    int val;

    ModInt(long long v = 0) {
        v %= MOD;
        if (v < 0) v += MOD;
        val = (int)v;
    }
    explicit operator int() const { return val; }

    bool operator==(const ModInt& o) const { return val == o.val; }
    bool operator!=(const ModInt& o) const { return val != o.val; }

    ModInt& operator+=(const ModInt& o) { val += o.val; if (val >= MOD) val -= MOD; return *this; }
    ModInt& operator-=(const ModInt& o) { val -= o.val; if (val < 0) val += MOD; return *this; }
    ModInt& operator*=(const ModInt& o) { val = (int)((long long)val * o.val % MOD); return *this; }
    ModInt& operator/=(const ModInt& o) { return *this *= o.inv(); }

    friend ModInt operator+(ModInt a, const ModInt& b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b) { return a /= b; }
    ModInt operator-() const { return ModInt(-val); }

    ModInt& operator++() { return *this += 1; }
    ModInt& operator--() { return *this -= 1; }

    friend ostream& operator<<(ostream& os, const ModInt& m) { return os << m.val; }
    friend istream& operator>>(istream& is, ModInt& m) { long long v; is >> v; m = v; return is; }

    ModInt pow(long long b) const {
        ModInt a = *this, res = 1;
        if (b < 0) { a = a.inv(); b = -b; }
        while (b) { if (b & 1) res *= a; a *= a; b >>= 1; }
        return res;
    }
    friend ModInt power(ModInt a, long long b) { return a.pow(b); }
    ModInt inv() const { return pow(MOD - 2); }

    // Cached factorial tables, extended lazily.
    static void prepare(int n) {
        vector<ModInt>& f = fact_tbl();
        vector<ModInt>& g = inv_fact_tbl();
        int cur = f.size();
        if (n < cur) return;
        f.resize(n + 1);
        g.resize(n + 1);
        for (int i = cur; i <= n; i++) f[i] = f[i - 1] * i;
        g[n] = f[n].inv();
        for (int i = n; i > cur; i--) g[i - 1] = g[i] * i;
    }
    static vector<ModInt>& fact_tbl() { static vector<ModInt> f = {ModInt(1)}; return f; }
    static vector<ModInt>& inv_fact_tbl() { static vector<ModInt> g = {ModInt(1)}; return g; }

    static ModInt fact(int n) { prepare(n); return fact_tbl()[n]; }
    static ModInt inv_fact(int n) { prepare(n); return inv_fact_tbl()[n]; }

    static ModInt choose(int n, int k) {
        if (k < 0 || n < 0 || k > n) return ModInt(0);
        prepare(n);
        return fact_tbl()[n] * inv_fact_tbl()[k] * inv_fact_tbl()[n - k];
    }
    static ModInt perm(int n, int k) {
        if (k < 0 || n < 0 || k > n) return ModInt(0);
        prepare(n);
        return fact_tbl()[n] * inv_fact_tbl()[n - k];
    }
    static ModInt multichoose(int n, int k) {
        if (n == 0) return ModInt(k == 0);
        return choose(n + k - 1, k);
    }
    static ModInt catalan(int n) {
        if (n < 0) return ModInt(0);
        return choose(2 * n, n) - choose(2 * n, n + 1);
    }
};

using mint = ModInt<1000000007>;
