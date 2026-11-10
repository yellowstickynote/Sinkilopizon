using u64 = unsigned long long;
using u128 = __uint128_t;

struct Hash {
    u64 x;
    Hash(u64 x = 0) : x(x) {}

    Hash operator+(Hash o) const { return x + o.x + (x + o.x < x); }
    Hash operator-(Hash o) const { return *this + ~o.x; }
    Hash operator*(Hash o) const {
        u128 m = (u128)x * o.x;
        return Hash((u64)m) + (u64)(m >> 64);
    }

    u64 get() const { return x + !~x; }
    bool operator==(Hash o) const { return get() == o.get(); }
    bool operator!=(Hash o) const { return get() != o.get(); }
    bool operator<(Hash o) const { return get() < o.get(); }
};
