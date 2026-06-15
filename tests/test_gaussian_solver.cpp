#include <gtest/gtest.h>
#include "../include/GaussianSolver.h"
#include "../include/Matrix.h"
#include "../include/Vector.h"
#include <cmath>

template <typename T>
void ExpectVectorNear(const Vector<T>& actual,
                      const Vector<T>& expected,
                      T eps = T{1e-5}) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 1; i <= actual.size(); ++i) {
        EXPECT_NEAR(actual[i], expected[i], eps) << " at index " << i;
    }
}

// ==================== Basic 2x2 Systems ====================

TEST(GaussianSolverTest, Simple2x2System) {
    // 2x + y = 5
    // x + y = 3
    // Expected solution: x=2, y=1
    Matrix<double> A(2, 2, 0.0);
    A[1, 1] = 2.0; A[1, 2] = 1.0;
    A[2, 1] = 1.0; A[2, 2] = 1.0;

    Vector<double> b(2);
    b[1] = 5.0;
    b[2] = 3.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> expected(2);
    expected[1] = 2.0;
    expected[2] = 1.0;

    ExpectVectorNear(x, expected);
}

TEST(GaussianSolverTest, IdentityMatrix2x2) {
    // I * x = b
    // Expected solution: x = b
    Matrix<double> A = Matrix<double>::identity(2);
    Vector<double> b(2);
    b[1] = 3.0;
    b[2] = 7.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    ExpectVectorNear(x, b);
}

TEST(GaussianSolverTest, ZeroOffDiagonal) {
    // Diagonal matrix:
    // 2x = 4
    // 3y = 9
    // Expected: x=2, y=3
    Matrix<double> A(2, 2, 0.0);
    A[1, 1] = 2.0;
    A[2, 2] = 3.0;

    Vector<double> b(2);
    b[1] = 4.0;
    b[2] = 9.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> expected(2);
    expected[1] = 2.0;
    expected[2] = 3.0;

    ExpectVectorNear(x, expected);
}

// ==================== Basic 3x3 Systems ====================

TEST(GaussianSolverTest, Simple3x3System) {
    // x + y + z = 6
    // 2y + 5z = -4
    // 2x + 5y - z = 27
    // Expected: x=5, y=3, z=-2
    Matrix<double> A(3, 3, 0.0);
    A[1, 1] = 1.0; A[1, 2] = 1.0; A[1, 3] = 1.0;
    A[2, 1] = 0.0; A[2, 2] = 2.0; A[2, 3] = 5.0;
    A[3, 1] = 2.0; A[3, 2] = 5.0; A[3, 3] = -1.0;

    Vector<double> b(3);
    b[1] = 6.0;
    b[2] = -4.0;
    b[3] = 27.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> expected(3);
    expected[1] = 5.0;
    expected[2] = 3.0;
    expected[3] = -2.0;

    ExpectVectorNear(x, expected);
}

TEST(GaussianSolverTest, Identity3x3) {
    Matrix<double> A = Matrix<double>::identity(3);
    Vector<double> b(3);
    b[1] = 1.0;
    b[2] = 2.0;
    b[3] = 3.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    ExpectVectorNear(x, b);
}

// ==================== Larger Systems ====================

TEST(GaussianSolverTest, Size4System) {
    // Create a 4x4 identity system
    Matrix<double> A = Matrix<double>::identity(4);
    Vector<double> b(4);
    b[1] = 2.0;
    b[2] = 4.0;
    b[3] = 6.0;
    b[4] = 8.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    ExpectVectorNear(x, b);
}

TEST(GaussianSolverTest, Size5System) {
    Matrix<double> A = Matrix<double>::identity(5);
    Vector<double> b(5);
    for (size_t i = 1; i <= 5; ++i) {
        b[i] = static_cast<double>(i);
    }

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    ExpectVectorNear(x, b);
}

// ==================== Solution Verification ====================

TEST(GaussianSolverTest, SolutionSatisfiesSystem) {
    // Verify that A*x = b
    Matrix<double> A(3, 3, 0.0);
    A[1, 1] = 2.0; A[1, 2] = -1.0; A[1, 3] = 0.0;
    A[2, 1] = -1.0; A[2, 2] = 2.0; A[2, 3] = -1.0;
    A[3, 1] = 0.0; A[3, 2] = -1.0; A[3, 3] = 2.0;

    Vector<double> b(3);
    b[1] = 1.0;
    b[2] = 0.0;
    b[3] = 0.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> result = A * x;
    ExpectVectorNear(result, b);
}

TEST(GaussianSolverTest, SolutionVerification2x2) {
    Matrix<double> A(2, 2, 0.0);
    A[1, 1] = 3.0; A[1, 2] = 2.0;
    A[2, 1] = 1.0; A[2, 2] = 4.0;

    Vector<double> b(2);
    b[1] = 8.0;
    b[2] = 9.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> result = A * x;
    ExpectVectorNear(result, b);
}

// ==================== Pivot Testing (partial pivoting) ====================

TEST(GaussianSolverTest, RequiresPivoting) {
    // Small diagonal element requires pivoting
    Matrix<double> A(2, 2, 0.0);
    A[1, 1] = 0.0001; A[1, 2] = 1.0;
    A[2, 1] = 1.0; A[2, 2] = 1.0;

    Vector<double> b(2);
    b[1] = 1.0001;
    b[2] = 2.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> result = A * x;
    ExpectVectorNear(result, b, 1e-4);
}

// ==================== Error Handling ====================

TEST(GaussianSolverTest, SizeMismatchThrows) {
    Matrix<double> A(3, 3, 0.0);
    Vector<double> b(2);  // Wrong size

    GaussianSolver<double> solver;
    EXPECT_THROW(solver.solve(A, b), std::runtime_error);
}

TEST(GaussianSolverTest, MismatchLargeSizes) {
    Matrix<double> A(5, 5, 0.0);
    Vector<double> b(4);  // Wrong size

    GaussianSolver<double> solver;
    EXPECT_THROW(solver.solve(A, b), std::runtime_error);
}

// ==================== Different Data Types ====================

TEST(GaussianSolverTest, IntegerType) {
    // Use integers carefully - ensure exact arithmetic
    Matrix<int> A(2, 2, 0);
    A[1, 1] = 2; A[1, 2] = 0;
    A[2, 1] = 0; A[2, 2] = 3;

    Vector<int> b(2);
    b[1] = 6;
    b[2] = 9;

    GaussianSolver<int> solver;
    Vector<int> x = solver.solve(A, b);

    Vector<int> expected(2);
    expected[1] = 3;
    expected[2] = 3;

    for (size_t i = 1; i <= x.size(); ++i) {
        EXPECT_EQ(x[i], expected[i]);
    }
}

TEST(GaussianSolverTest, FloatType) {
    Matrix<float> A(2, 2, 0.0f);
    A[1, 1] = 2.0f; A[1, 2] = 1.0f;
    A[2, 1] = 1.0f; A[2, 2] = 1.0f;

    Vector<float> b(2);
    b[1] = 5.0f;
    b[2] = 3.0f;

    GaussianSolver<float> solver;
    Vector<float> x = solver.solve(A, b);

    Vector<float> expected(2);
    expected[1] = 2.0f;
    expected[2] = 1.0f;

    ExpectVectorNear(x, expected, 1e-5f);
}

// ==================== Negative Values ====================

TEST(GaussianSolverTest, NegativeCoefficients) {
    Matrix<double> A(2, 2, 0.0);
    A[1, 1] = -2.0; A[1, 2] = 3.0;
    A[2, 1] = 4.0; A[2, 2] = -5.0;

    Vector<double> b(2);
    b[1] = 1.0;
    b[2] = 2.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> result = A * x;
    ExpectVectorNear(result, b);
}

TEST(GaussianSolverTest, NegativeRightHandSide) {
    Matrix<double> A(2, 2, 0.0);
    A[1, 1] = 1.0; A[1, 2] = 2.0;
    A[2, 1] = 3.0; A[2, 2] = 4.0;

    Vector<double> b(2);
    b[1] = -5.0;
    b[2] = -6.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> result = A * x;
    ExpectVectorNear(result, b);
}

// ==================== Zero Solutions ====================

TEST(GaussianSolverTest, ZeroSolution) {
    Matrix<double> A = Matrix<double>::identity(3);
    Vector<double> b(3, 0.0);

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    ExpectVectorNear(x, b);
}

// ==================== Hilbert Matrix (ill-conditioned) ====================

TEST(GaussianSolverTest, HilbertMatrix3x3) {
    // Hilbert matrices are ill-conditioned but solvable
    Matrix<double> A = Matrix<double>::hilbert(3);
    Vector<double> b(3);
    b[1] = 1.0;
    b[2] = 1.0;
    b[3] = 1.0;

    GaussianSolver<double> solver;
    Vector<double> x = solver.solve(A, b);

    Vector<double> result = A * x;
    ExpectVectorNear(result, b, 1e-4);
}
