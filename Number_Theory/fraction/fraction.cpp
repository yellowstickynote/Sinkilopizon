struct Fraction {
    long long n, d;
    Fraction(long long _n = 0, long long _d = 1) {
        long long g = std::gcd(std::abs(_n), std::abs(_d));
        if (g) { _n /= g; _d /= g; }
        if (_d < 0) { _n = -_n; _d = -_d; }
        else if (_d == 0) { _n = (_n > 0 ? 1 : (_n < 0 ? -1 : 0)); }
        n = _n; d = _d;
    }
    bool operator<(const Fraction& o) const {
        if (d == 0 || o.d == 0) {
            if (d == o.d) return n < o.n;
            return d == 0 ? n < 0 : o.n > 0;
        }
        return (__int128_t)n * o.d < (__int128_t)o.n * d;
    }
    bool operator>(const Fraction& o) const { return o < *this; }
    bool operator<=(const Fraction& o) const { return !(*this > o); }
    bool operator>=(const Fraction& o) const { return !(*this < o); }
    bool operator==(const Fraction& o) const { return n == o.n && d == o.d; }
    bool operator!=(const Fraction& o) const { return !(*this == o); }
    
    Fraction operator+(const Fraction& o) const { return Fraction(n * o.d + o.n * d, d * o.d); }
    Fraction operator-(const Fraction& o) const { return Fraction(n * o.d - o.n * d, d * o.d); }
    Fraction operator*(const Fraction& o) const { return Fraction(n * o.n, d * o.d); }
    Fraction operator/(const Fraction& o) const { return Fraction(n * o.d, d * o.n); }
    
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        if (f.d == 0) return os << (f.n > 0 ? "INF" : (f.n < 0 ? "-INF" : "NaN"));
        return os << f.n << "/" << f.d;
    }
};
