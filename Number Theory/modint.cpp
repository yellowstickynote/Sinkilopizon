template <int MOD>
struct ModInt {
    int val;
    ModInt(int v = 0) {
        if (v < 0) v = v % MOD + MOD;
        if (v >= MOD) v %= MOD;
        val = v;
    }
    explicit operator int() const { return val; }
    bool operator==(const ModInt& o) const { return val == o.val; }
    bool operator!=(const ModInt& o) const { return val != o.val; }
    ModInt& operator+=(const ModInt& o) { val += o.val; if (val >= MOD) val -= MOD; return *this; }
    ModInt& operator-=(const ModInt& o) { val -= o.val; if (val < 0) val += MOD; return *this; }
    ModInt& operator*=(const ModInt& o) { val = (val * o.val) % MOD; return *this; }
    ModInt& operator/=(const ModInt& o) { return *this *= o.inv(); }
    friend ModInt operator+(ModInt a, const ModInt& b) { return a += b; }
    friend ModInt operator-(ModInt a, const ModInt& b) { return a -= b; }
    friend ModInt operator*(ModInt a, const ModInt& b) { return a *= b; }
    friend ModInt operator/(ModInt a, const ModInt& b) { return a /= b; }
    ModInt operator-() const { return ModInt(-val); }
    ModInt& operator++() { return *this += 1; }
    ModInt& operator--() { return *this -= 1; }
    friend ostream& operator<<(ostream& os, const ModInt& m) { return os << m.val; }
    friend istream& operator>>(istream& is, ModInt& m) { int v; is >> v; m = ModInt(v); return is; }
    
    ModInt inv() const { return power(*this, MOD - 2); }
    friend ModInt power(ModInt a, int b) {
        ModInt res = 1;
        while (b) { if (b & 1) res *= a; a *= a; b >>= 1; }
        return res;
    }
};
using mint = ModInt<1000000007>;
