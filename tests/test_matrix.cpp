#include <gtest/gtest.h>
#include "../include/Matrix.h"
#include <cmath>

// Helper: compare matrix element via temp variable to avoid
// preprocessor comma conflicts in EXPECT_* macros with m[i, j].
template <typename T>
void ExpectElem(const Matrix<T>& m, size_t i, size_t j, T expected, T eps = T{1e-6}) {
    T actual = m[i, j];
    EXPECT_NEAR(actual, expected, eps);
}

// ==================== Construction ====================

TEST(MatrixTest, DefaultConstructor) {
    Matrix<double> m;
    EXPECT_EQ(m.n(), 0);
    EXPECT_EQ(m.m(), 0);
}

TEST(MatrixTest, SizedConstructor) {
    Matrix<double> m(3, 4, 1.5);
    EXPECT_EQ(m.n(), 3);
    EXPECT_EQ(m.m(), 4);
    for (size_t i = 1; i <= 3; i++) {
        for (size_t j = 1; j <= 4; j++) {
            ExpectElem(m, i, j, 1.5);
        }
    }
}

TEST(MatrixTest, SizedConstructorDefaultInit) {
    Matrix<int> m(2, 3, 0);
    for (size_t i = 1; i <= 2; i++) {
        for (size_t j = 1; j <= 3; j++) {
            int val = m[i, j];
            EXPECT_EQ(val, 0);
        }
    }
}

// ==================== Identity ====================

TEST(MatrixTest, IdentitySize) {
    Matrix<double> id = Matrix<double>::identity(4);
    EXPECT_EQ(id.n(), 4);
    EXPECT_EQ(id.m(), 4);
}

TEST(MatrixTest, IdentityOnDiagonal) {
    Matrix<double> id = Matrix<double>::identity(4);
    for (size_t i = 1; i <= 4; i++) {
        ExpectElem(id, i, i, 1.0);
    }
}

TEST(MatrixTest, IdentityOffDiagonal) {
    Matrix<double> id = Matrix<double>::identity(4);
    for (size_t i = 1; i <= 4; i++) {
        for (size_t j = 1; j <= 4; j++) {
            if (i != j) {
                ExpectElem(id, i, j, 0.0);
            }
        }
    }
}

// ==================== Hilbert ====================

TEST(MatrixTest, HilbertTopLeft) {
    Matrix<double> h = Matrix<double>::hilbert(3);
    ExpectElem(h, 1, 1, 1.0);
}

TEST(MatrixTest, HilbertKnownValues) {
    Matrix<double> h = Matrix<double>::hilbert(3);
    ExpectElem(h, 1, 2, 1.0 / 2.0);
    ExpectElem(h, 2, 1, 1.0 / 2.0);
    ExpectElem(h, 2, 2, 1.0 / 3.0);
    ExpectElem(h, 2, 3, 1.0 / 4.0);
    ExpectElem(h, 3, 3, 1.0 / 5.0);
}

TEST(MatrixTest, HilbertSymmetric) {
    Matrix<double> h = Matrix<double>::hilbert(5);
    for (size_t i = 1; i <= 5; i++) {
        for (size_t j = 1; j <= 5; j++) {
            double a = h[i, j];
            double b = h[j, i];
            EXPECT_DOUBLE_EQ(a, b);
        }
    }
}

// ==================== Indexing ====================

TEST(MatrixTest, IndexOperatorReadWrite) {
    Matrix<double> m(2, 3, 0.0);
    m[1, 1] = 1.0;
    m[1, 3] = 3.0;
    m[2, 2] = 5.0;
    ExpectElem(m, 1, 1, 1.0);
    ExpectElem(m, 1, 3, 3.0);
    ExpectElem(m, 2, 2, 5.0);
}

TEST(MatrixTest, ConstIndexOperator) {
    Matrix<double> m(2, 2, 7.0);
    m[1, 2] = 3.0;
    m[2, 1] = 4.0;
    const Matrix<double>& cm = m;
    double a = cm[1, 1];
    double b = cm[1, 2];
    double c = cm[2, 1];
    EXPECT_DOUBLE_EQ(a, 7.0);
    EXPECT_DOUBLE_EQ(b, 3.0);
    EXPECT_DOUBLE_EQ(c, 4.0);
}

// ==================== Bounds-checked Access (at) ====================

TEST(MatrixTest, AtMutable) {
    Matrix<double> m(2, 2, 0.0);
    m.at(1, 1) = 5.0;
    double val = m.at(1, 1);
    EXPECT_DOUBLE_EQ(val, 5.0);
}

TEST(MatrixTest, AtConst) {
    Matrix<double> m(2, 2, 1.0);
    m.at(2, 2) = 9.0;
    const Matrix<double>& cm = m;
    double a = cm.at(1, 1);
    double b = cm.at(2, 2);
    EXPECT_DOUBLE_EQ(a, 1.0);
    EXPECT_DOUBLE_EQ(b, 9.0);
}

TEST(MatrixTest, AtThrowsOnOutOfRange) {
    Matrix<double> m(2, 3, 0.0);
    EXPECT_THROW(m.at(0, 1), std::out_of_range);
    EXPECT_THROW(m.at(1, 0), std::out_of_range);
    EXPECT_THROW(m.at(3, 1), std::out_of_range);
    EXPECT_THROW(m.at(1, 4), std::out_of_range);
}

TEST(MatrixTest, ConstAtThrowsOnOutOfRange) {
    const Matrix<double> m(2, 2, 0.0);
    EXPECT_THROW(m.at(0, 1), std::out_of_range);
    EXPECT_THROW(m.at(3, 1), std::out_of_range);
}

// ==================== Row / Column Extraction ====================

TEST(MatrixTest, RowExtraction) {
    Matrix<double> m(3, 4, 0.0);
    for (size_t j = 1; j <= 4; j++) {
        m[2, j] = static_cast<double>(j * 10);
    }
    Vector<double> r = m.row(2);
    EXPECT_EQ(r.size(), 4);
    EXPECT_DOUBLE_EQ(r[1], 10.0);
    EXPECT_DOUBLE_EQ(r[2], 20.0);
    EXPECT_DOUBLE_EQ(r[3], 30.0);
    EXPECT_DOUBLE_EQ(r[4], 40.0);
}

TEST(MatrixTest, ColExtraction) {
    Matrix<double> m(3, 4, 0.0);
    for (size_t i = 1; i <= 3; i++) {
        m[i, 3] = static_cast<double>(i * 100);
    }
    Vector<double> c = m.col(3);
    EXPECT_EQ(c.size(), 3);
    EXPECT_DOUBLE_EQ(c[1], 100.0);
    EXPECT_DOUBLE_EQ(c[2], 200.0);
    EXPECT_DOUBLE_EQ(c[3], 300.0);
}

TEST(MatrixTest, RowConstCorrectness) {
    const Matrix<double> m(2, 2, 5.0);
    Vector<double> r = m.row(1);
    EXPECT_EQ(r.size(), 2);
    EXPECT_DOUBLE_EQ(r[1], 5.0);
    EXPECT_DOUBLE_EQ(r[2], 5.0);
}

// ==================== Swap Rows ====================

TEST(MatrixTest, SwapRows) {
    Matrix<double> m(3, 3, 0.0);
    m[1, 1] = 1.0; m[1, 2] = 2.0; m[1, 3] = 3.0;
    m[3, 1] = 7.0; m[3, 2] = 8.0; m[3, 3] = 9.0;
    m.swap_rows(1, 3);
    ExpectElem(m, 1, 1, 7.0);
    ExpectElem(m, 1, 2, 8.0);
    ExpectElem(m, 1, 3, 9.0);
    ExpectElem(m, 3, 1, 1.0);
    ExpectElem(m, 3, 2, 2.0);
    ExpectElem(m, 3, 3, 3.0);
}

TEST(MatrixTest, SwapRowsSameRow) {
    Matrix<double> m(2, 2, 0.0);
    m[1, 1] = 1.0; m[1, 2] = 2.0;
    m[2, 1] = 3.0; m[2, 2] = 4.0;
    m.swap_rows(1, 1);
    ExpectElem(m, 1, 1, 1.0);
    ExpectElem(m, 1, 2, 2.0);
    ExpectElem(m, 2, 1, 3.0);
    ExpectElem(m, 2, 2, 4.0);
}

// ==================== Matrix-Vector Multiplication ====================

TEST(MatrixTest, MultiplyByIdentity) {
    Matrix<double> id = Matrix<double>::identity(3);
    Vector<double> v{1.0, 2.0, 3.0};
    Vector<double> result = id * v;
    EXPECT_EQ(result.size(), 3);
    EXPECT_DOUBLE_EQ(result[1], 1.0);
    EXPECT_DOUBLE_EQ(result[2], 2.0);
    EXPECT_DOUBLE_EQ(result[3], 3.0);
}

TEST(MatrixTest, MultiplyNonSquare) {
    Matrix<double> m(2, 3, 0.0);
    m[1, 1] = 1.0; m[1, 2] = 2.0; m[1, 3] = 3.0;
    m[2, 1] = 4.0; m[2, 2] = 5.0; m[2, 3] = 6.0;
    Vector<double> v{2.0, 0.0, 1.0};
    Vector<double> result = m * v;
    EXPECT_EQ(result.size(), 2);
    EXPECT_DOUBLE_EQ(result[1], 1.0 * 2.0 + 2.0 * 0.0 + 3.0 * 1.0);
    EXPECT_DOUBLE_EQ(result[2], 4.0 * 2.0 + 5.0 * 0.0 + 6.0 * 1.0);
}

TEST(MatrixTest, MultiplySizeMismatchThrows) {
    Matrix<double> m(3, 3, 0.0);
    Vector<double> v{1.0, 2.0};
    EXPECT_THROW(m * v, std::runtime_error);
}
