using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, bool invert) {
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
    
    // 2. Iterative Cooley-Tukey
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(angle), sin(angle));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j];
                cd v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }
    
    // 3. Scaling for inverse transform
    if (invert) {
        for (cd& x : a)
            x /= n;
    }
}

vector<long long> multiply(const vector<long long>& a, const vector<long long>& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    
    int n = 1;
    while (n < a.size() + b.size()) 
        n <<= 1;
    
    fa.resize(n);
    fb.resize(n);

    // 1. Forward FFT
    fft(fa, false);
    fft(fb, false);
    
    // 2. Pointwise complex multiplication
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
        
    // 3. Inverse FFT
    fft(fa, true);

    // 4. Round back to integer coefficients
    vector<long long> result(a.size() + b.size() - 1);
    for (int i = 0; i < result.size(); i++) {
        result[i] = llround(fa[i].real());
    }
    return result;
}
