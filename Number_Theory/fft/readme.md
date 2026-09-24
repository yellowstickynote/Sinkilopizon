# Fast Fourier Transform (FFT)

**Type:** Floating-Point / Complex Domain (`cd = std::complex<double>`) · **Complexity:** Transform $O(N \log N)$, Multiply $O(N \log N)$

## Overview

Polynomial multiplication over the complex field $\mathbb{C}$ using $N$-th complex roots of unity $e^{2\pi i / N}$. It evaluates polynomials into point-value form, performs pointwise complex multiplication, and interpolates back using the inverse FFT. Standard floating-point rounding (`llround`) recovers the original integer coefficients.

## API

| Member / Function | Effect |
|--------|--------|
| `fft(a, invert)` | In-place iterative Cooley-Tukey FFT on `vector<complex<double>>& a`. Set `invert = true` for IFFT. |
| `multiply_fft(a, b)` | Convolution of two integer sequences `vector<long long>`. Handles sizing, padding, and rounding. |

## Customization

- Switch `double` to `long double` for higher precision when dealing with large coefficients ($> 10^{14}$).

## Notes

- Vector lengths are automatically padded to the smallest power of 2 ($N = 2^k$) where $N \ge \text{a.size()} + \text{b.size()}$.
- Subject to floating-point precision constraints. Suitable when no exact modulo is specified or coefficients are small enough to prevent rounding errors.