# LinearSystemSolver

A C++23 library for solving systems of linear equations.

### Available Solvers
- GaussianSolver - Gaussian Elimination with partial pivoting

### Future Solvers
- LU Solver
- Gauss Seidel Solver
- Conjugate Gradient Solver

### Build

```bash
cd LinearSystemSolver
mkdir -p build && cd build
cmake .. && cmake --build .
```

### Example Usage

```cpp
#include "include/GaussianSolver.h"

int main() {
    // Solve: 2x + y = 5
    //        x + y = 3
    
    Matrix<double> A = {{2.0, 1.0}, {1.0, 1.0}};
    Vector<double> b{5.0, 3.0};
    
    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);  // x = {2, 1}
}
```

## Requirements

- C++23 compiler (GCC 13+, Clang 15+, Apple Clang 15+)
- CMake 3.31+
- Google Test (brew install googletest on macOS)

## Project Structure

```
LinearSystemSolver/
├── include/          # Vector.h, Matrix.h, GaussianSolver.h
├── src/              # GaussianSolver.cpp
├── tests/            # 96 test cases
└── README.md
```

## API

**Vector:**
- Construction: `Vector<T> v(size)` or `v{1, 2, 3}`
- Operations: `v + v2`, `v - v2`, `v * scalar`, `v.dot(v2)`, `v.norm()`

**Matrix:**
- Construction: `Matrix<T> m(rows, cols, val)` or `m{{1,2},{3,4}}`
- Factories: `Matrix<T>::identity(n)`, `Matrix<T>::hilbert(n)`
- Operations: `m[i,j]`, `m.row(i)`, `m.col(j)`, `m.swap_rows(i,j)`, `m * v`

**Solvers:**
- Solve: `solver.solve(A, b)` → returns Vector x

## License

MIT
