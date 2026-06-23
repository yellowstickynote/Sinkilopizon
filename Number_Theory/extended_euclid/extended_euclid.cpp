struct ExtendedEuclid {
    long long g, x, y; // g = gcd(a, b); a*x + b*y = g

    ExtendedEuclid(long long a, long long b) { g = ext(a, b, x, y); }

    static long long ext(long long a, long long b, long long &x, long long &y) {
        if (b == 0) {
            x = 1;
            y = 0;
            return a;
        }
        long long x1, y1;
        long long d = ext(b, a % b, x1, y1);
        x = y1;
        y = x1 - y1 * (a / b);
        return d;
    }
};
