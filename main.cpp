#include <iostream>

#include "include/Matrix.h"
#include "include/GaussianSolver.h"
#include <iostream>

int main() {
    Matrix<double> A(4, 4, 0);
    for (int i = 1; i <= 4; i++) {
        for (int j = 1; j <= 4; j++) {
            std::cin >> A[i, j];
        }
    }

    Vector<double> b(4);

    for (int i = 1; i <= 4; i++) {
        std::cin >> b[i];
    }

    Vector<double> res = GaussianSolver<double>().solve(A, b);
    res.print();

    return 0;
}