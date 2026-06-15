//
// Created by Yerdaulet Mussabek on 15.06.2026.
//

#ifndef GAUSSIANSOLVER_H
#define GAUSSIANSOLVER_H

#include "Solver.h"
#include "Config.h"

template<typename T>
class GaussianSolver : public Solver<T> {
public:
    GaussianSolver() = default;

    Vector<T> solve(const Matrix<T>& A, const Vector<T>& b) override;
};

#endif //GAUSSIANSOLVER_H
