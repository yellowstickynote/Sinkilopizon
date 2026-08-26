# Matrix

Generic matrix with customizable element type and operations.

```cpp
template<class T, class Add = plus<T>, class Mul = multiplies<T>>
struct Matrix
```

- `T` — element type.
- `Add` — operation used to combine products.
- `Mul` — operation used to multiply elements.
- `zero` — identity of `Add`.
- `one` — identity of `Mul`.

## Usage

Construct from dimensions:

```cpp
Matrix<long long> a(n, m);
```

Construct from an initializer list:

```cpp
Matrix<long long> a{{1, 2}, {3, 4}};
```

Construct from a vector:

```cpp
vector<vector<long long>> a = {{1, 2}, {3, 4}};
Matrix<long long> b(a);
```

Custom identities and operations:

```cpp
struct Min {
    long long operator()(long long a, long long b) const { return min(a, b); }
};

struct Plus {
    long long operator()(long long a, long long b) const { return a + b; }
};

using mat = Matrix<long long, Min, Plus>;

mat a(n, n, INF, 0);
```

Matrix multiplication and exponentiation:

```cpp
auto b = a * a;
auto c = a.pow(k);
```

`a * b` requires `a.m == b.n`.

`pow(k)` requires a square matrix and uses binary exponentiation.

Complexity:
- multiplication: `O(nmk)`
- exponentiation: `O(n^3 log k)`
