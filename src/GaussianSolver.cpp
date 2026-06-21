//
// Created by Yerdaulet Mussabek on 15.06.2026.
//

#pragma GCC optimize("O3")

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
}

template<typename T>
Vector<T> GaussianSolver<T>::solve(const Matrix<T>& A, const Vector<T>& b) {
    if (b.size() != A.n()) throw std::runtime_error("Size Mismatch");

    Matrix<T> Ab(A.n(), A.m() + 1, 0);
    
    auto Ab_iter = Ab.data().begin();
    auto A_iter = A.data().begin(); 
    auto b_iter = b.data().begin();

    for (size_t i = 0; i < Ab.n() * Ab.m(); i++) {
        if ((i + 1) % Ab.m() == 0) [[unlikely]] {
            *Ab_iter = *b_iter;
            b_iter++;
        } 
        else { 
            *Ab_iter = *A_iter;
            A_iter++;
        }

        Ab_iter++; 
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
