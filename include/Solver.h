//
// Created by Yerdaulet Mussabek on 14.06.2026.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "Matrix.h"
#include "Vector.h"
#include "Traits.h"

template<typename T>
struct SolverResult {
    Vector<T>       x;
    bool            converged = true;
    int             iterations = 0;
    Accumulator_t<T>  residual = 0.0;
};

template<typename T>
class Solver {
public:
    virtual ~Solver() = default;
    virtual Vector<T> solve(const Matrix<T>& A, const Vector<T>& b) = 0;
protected:
    T residual_norm(const Matrix<T>& A, const Vector<T>& x, const Vector<T>& b) const {
        return (b - A * x).norm();
    }
};

#endif //SOLVER_H
