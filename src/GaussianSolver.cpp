//
// Created by Yerdaulet Mussabek on 15.06.2026.
//

#include "../include/GaussianSolver.h"

#include "../include/Matrix.h"
#include "../include/Vector.h"
#include <stdexcept>
#include "../include/Config.h"
#include <vector>

template class GaussianSolver<Scalar_t>;
template class GaussianSolver<float>;
template class GaussianSolver<int>;

namespace {
    template<typename T>
    size_t find_partial_pivot(const Matrix<T>& A, size_t row_idx) {
        T max_abs_val{A[row_idx, row_idx]};
        size_t pivot = row_idx;
        for (size_t i = row_idx + 1; i <= A.n(); i++) {
            if (std::abs(A[i, row_idx]) > max_abs_val) {
                max_abs_val = abs(A[i, row_idx]);
                pivot = i;
            }
        }
        return pivot;
    }

    using T = Scalar_t;
}

template<typename T>
Vector<T> GaussianSolver<T>::solve(const Matrix<T> &A, const Vector<T> &b) {
    if (b.size() != A.n()) throw std::runtime_error("Size Mismatch");

    // Build a new matrix where the m+1'th columns is vector b
    Matrix<T> Ab(A.n(), A.m() + 1, 0);
    for (size_t i = 1; i <= A.n(); i++) {
        for (size_t j = 1; j <= A.m(); j++) {
            Ab[i, j] = A[i, j];
        }
        Ab[i, A.m() + 1] = b[i];
    }

    for (size_t i = 1; i < Ab.n(); i++) {
        size_t pivot = find_partial_pivot(Ab, i);
        Ab.swap_rows(i, pivot);

        for (size_t i2 = i + 1; i2 <= Ab.n(); i2++) {
            const T k = Ab[i2, i] / Ab[i, i];
            for (size_t j = 1; j <= Ab.m(); j++) {
                Ab[i2, j] -= Ab[i, j] * k;
            }
        }
    }

    Vector<T> x(b.size());
    for (size_t i = Ab.n(); i > 0; i--) {
        Accumulator_t<T> sum = Ab[i, Ab.m()];
        for (size_t j = i + 1; j <= Ab.n(); j++) {
            sum -= Ab[i, j] * x[j];
        }
        x[i] = sum / Ab[i, i];
    }

    return x;
}
