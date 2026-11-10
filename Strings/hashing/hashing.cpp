using u64 = unsigned long long;
using u128 = __uint128_t;

struct StringHash {
    int n;
    vector<u64> ha, pw;

    static u64 add(u64 a, u64 b) { return a + b + (a + b < a); }
    static u64 sub(u64 a, u64 b) { return add(a, ~b); }
    static u64 mul(u64 a, u64 b) {
        u128 m = (u128)a * b;
        return add((u64)m, (u64)(m >> 64));
    }
    static u64 canon(u64 a) { return a + !~a; }

    static u64 base() {
        static const u64 b = [] {
            mt19937_64 rng{random_device{}()};
            return (rng() >> 2) | (1ULL << 32) | 1;
        }();
        return b;
    }

    template <class C>
    StringHash(const C& s) : n(s.size()), ha(n + 1), pw(n + 1) {
        u64 b = base();
        pw[0] = 1;
        for (int i = 0; i < n; i++) {
            ha[i + 1] = add(mul(ha[i], b), (u64)s[i]);
            pw[i + 1] = mul(pw[i], b);
        }
    }

    u64 query(int l, int r) const {
        return canon(sub(ha[r + 1], mul(ha[l], pw[r - l + 1])));
    }

    vector<u64> windows(int len) const {
        vector<u64> res;
        for (int i = 0; i + len <= n; i++) res.push_back(query(i, i + len - 1));
        return res;
    }
};
