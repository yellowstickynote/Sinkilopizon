# Static-Sized Matrix

**Type:** `Matrix<T, N, M, Add, Mul>` · **Complexity:** multiplication `O(NMK)`, exponentiation `O(N^3 log k)`

## Overview

Matrix with dimensions known at compile time. Uses static arrays and supports customizable element type and operations.

```cpp
template<class T, int N, int M, class Add = plus<T>, class Mul = multiplies<T>>
struct Matrix
```

- `T` — element type.
- `N` — number of rows.
- `M` — number of columns.
- `Add` — operation used to combine products.
- `Mul` — operation used to multiply elements.

## Usage

Construct an empty matrix:

```cpp
Matrix<long long, 2, 3> a;
```

Construct from values:

```cpp
Matrix<long long, 2, 2> a{{1, 2}, {3, 4}};
```

Access elements normally:

```cpp
a[i][j]
```

Matrix multiplication checks dimensions at compile time:

```cpp
Matrix<int, 2, 3> a;
Matrix<int, 3, 4> b;
auto c = a * b; // Matrix<int, 2, 4>
```

Square matrices support identity and exponentiation:

```cpp
Matrix<long long, 2, 2> a{{1, 1}, {1, 0}};
auto b = a.pow(10);
```

## Custom operations

```cpp
struct Min {
    long long operator()(long long a, long long b) const {
        return min(a, b);
    }
};

struct Plus {
    long long operator()(long long a, long long b) const {
        return a + b;
    }
};

using mat = Matrix<long long, 2, 2, Min, Plus>;

mat a(INF, 0);
auto b = a.pow(k);
```

The constructor arguments after the matrix dimensions are:

```text
zero, one, add, mul
```

`zero` is the identity for `Add`, and `one` is the identity for `Mul`.

## Notes

- Dimensions are compile-time constants.
- Matrix data is stored in a static `T[N][M]` array.
- `A * B` requires `A.M == B.N`.
- `identity()` and `pow()` require a square matrix.
- `pow()` uses binary exponentiation.
- `Add` should be associative and `Mul` should distribute over `Add`.

## Complexity

For `N × M` multiplied by `M × K`:

`O(NMK)`

For exponentiating an `N × N` matrix:

`O(N^3 log k)`
