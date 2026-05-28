struct Line {
 
    mutable ll m, c, p;
 
    bool operator < (const Line &o) const { 
        return m < o.m; 
    }
 
    bool operator < (ll x) const { 
        return p < x; 
    }
 
    ll val(ll x) const { 
        return m * x + c; 
    }
};
 
template < typename T = int, T Mode = -1 > class CHT : multiset < Line, less < > > {
private:
    
    static constexpr T LLimit = numeric_limits < T > :: min(), RLimit = numeric_limits < T > :: max();
 
    T div(T a, T b) { // floored division
        return a / b - ((a ^ b) < 0 && a % b);
    }
 
    bool is_intersect(iterator x, iterator y) {
        if (y == end()) return x -> p = RLimit, 0;
        if (x -> m == y -> m) x -> p = (x -> c > y -> c ? RLimit : LLimit);
        else x -> p = div(y -> c - x -> c, x -> m - y -> m);
        return x -> p >= y -> p;
    }
 
public:
    
    void add(T m, T c) {
        m *= Mode, c *= Mode;
        auto z = insert({m, c, 0}), y = z++, x = y;
        while (is_intersect(y, z)) z = erase(z);
        if (x != begin() && is_intersect(--x, y)) is_intersect(x, y = erase(y));
        while ((y = x) != begin() && (--x) -> p >= y -> p) is_intersect(x, erase(y));
    }
 
    T query(T x) {
        assert(!empty());
        auto l = *lower_bound(x);
        return Mode * l.val(x);
    }
 
};
