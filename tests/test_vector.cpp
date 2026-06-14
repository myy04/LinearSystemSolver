//
// Created by Yerdaulet Mussabek on 14.06.2026.
//
#include <gtest/gtest.h>
#include <vector>
#include "../include/Vector.h"

template <typename T>
void ExpectVectorsEqual(const Vector<T>& actual,
                        const std::vector<T>& expected,
                        T eps = T{1e-6}) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); ++i) {
        EXPECT_NEAR(actual[i], expected[i], eps) << " at index " << i;
    }
}

// ==================== Construction ====================

TEST(VectorTest, ConstructorWithSize) {
    Vector<double> v(5);
    EXPECT_EQ(v.size(), 5);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], 0.0);
    }
}

TEST(VectorTest, ConstructorWithSizeAndInitValue) {
    Vector<double> v(4, 3.14);
    EXPECT_EQ(v.size(), 4);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_DOUBLE_EQ(v[i], 3.14);
    }
}

TEST(VectorTest, InitializerListConstructor) {
    Vector<double> v{1.0, 2.0, 3.0};
    EXPECT_EQ(v.size(), 3);
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[1], 2.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

TEST(VectorTest, InitializerListConstructorEmpty) {
    Vector<int> v{};
    EXPECT_EQ(v.size(), 0);
}

TEST(VectorTest, ConstructorWithIntegerInitValue) {
    Vector<int> v(3, 5);
    EXPECT_EQ(v.size(), 3);
    for (size_t i = 0; i < v.size(); ++i) {
        EXPECT_EQ(v[i], 5);
    }
}

// ==================== Indexing ====================

TEST(VectorTest, IndexOperator) {
    Vector<double> v{10.0, 20.0, 30.0};
    EXPECT_DOUBLE_EQ(v[0], 10.0);
    EXPECT_DOUBLE_EQ(v[1], 20.0);
    EXPECT_DOUBLE_EQ(v[2], 30.0);
}

TEST(VectorTest, IndexOperatorMutable) {
    Vector<double> v{1.0, 2.0, 3.0};
    v[1] = 5.0;
    EXPECT_DOUBLE_EQ(v[1], 5.0);
}

TEST(VectorTest, ConstIndexOperator) {
    const Vector<double> v{1.0, 2.0, 3.0};
    EXPECT_DOUBLE_EQ(v[0], 1.0);
    EXPECT_DOUBLE_EQ(v[2], 3.0);
}

// ==================== Addition ====================

TEST(VectorTest, AdditionNonMutating) {
    Vector<double> a{1.0, 2.0, 3.0};
    Vector<double> b{4.0, 5.0, 6.0};
    Vector<double> c = a + b;
    
    ExpectVectorsEqual(c, {5.0, 7.0, 9.0});
    ExpectVectorsEqual(a, {1.0, 2.0, 3.0});  // a unchanged
    ExpectVectorsEqual(b, {4.0, 5.0, 6.0});  // b unchanged
}

TEST(VectorTest, AdditionMutatingOperator) {
    Vector<double> a{1.0, 2.0, 3.0};
    Vector<double> b{4.0, 5.0, 6.0};
    Vector<double>& ref = (a += b);
    
    EXPECT_EQ(&ref, &a);  // returns reference to a
    ExpectVectorsEqual(a, {5.0, 7.0, 9.0});
    ExpectVectorsEqual(b, {4.0, 5.0, 6.0});  // b unchanged
}

TEST(VectorTest, AdditionSizeMismatchThrows) {
    Vector<double> a{1.0, 2.0};
    Vector<double> b{1.0, 2.0, 3.0};
    
    EXPECT_THROW(a + b, std::runtime_error);
    EXPECT_THROW(a += b, std::runtime_error);
}

// ==================== Subtraction ====================

TEST(VectorTest, SubtractionNonMutating) {
    Vector<double> a{5.0, 7.0, 9.0};
    Vector<double> b{1.0, 2.0, 3.0};
    Vector<double> c = a - b;
    
    ExpectVectorsEqual(c, {4.0, 5.0, 6.0});
    ExpectVectorsEqual(a, {5.0, 7.0, 9.0});  // a unchanged
}

TEST(VectorTest, SubtractionMutatingOperator) {
    Vector<double> a{5.0, 7.0, 9.0};
    Vector<double> b{1.0, 2.0, 3.0};
    Vector<double>& ref = (a -= b);
    
    EXPECT_EQ(&ref, &a);
    ExpectVectorsEqual(a, {4.0, 5.0, 6.0});
}

TEST(VectorTest, SubtractionSizeMismatchThrows) {
    Vector<double> a{1.0, 2.0};
    Vector<double> b{1.0, 2.0, 3.0};
    
    EXPECT_THROW(a - b, std::runtime_error);
    EXPECT_THROW(a -= b, std::runtime_error);
}

// ==================== Element-wise Multiplication ====================

TEST(VectorTest, ElementwiseMultiplicationNonMutating) {
    Vector<double> a{2.0, 3.0, 4.0};
    Vector<double> b{5.0, 6.0, 7.0};
    Vector<double> c = a * b;
    
    ExpectVectorsEqual(c, {10.0, 18.0, 28.0});
    ExpectVectorsEqual(a, {2.0, 3.0, 4.0});  // a unchanged
}

TEST(VectorTest, ElementwiseMultiplicationMutatingOperator) {
    Vector<double> a{2.0, 3.0, 4.0};
    Vector<double> b{5.0, 6.0, 7.0};
    Vector<double>& ref = (a *= b);
    
    EXPECT_EQ(&ref, &a);
    ExpectVectorsEqual(a, {10.0, 18.0, 28.0});
}

TEST(VectorTest, ElementwiseMultiplicationSizeMismatchThrows) {
    Vector<double> a{1.0, 2.0};
    Vector<double> b{1.0, 2.0, 3.0};
    
    EXPECT_THROW(a * b, std::runtime_error);
    EXPECT_THROW(a *= b, std::runtime_error);
}

// ==================== Scalar Multiplication ====================

TEST(VectorTest, ScalarMultiplicationRight) {
    Vector<double> v{2.0, 3.0, 4.0};
    Vector<double> result = v * 5.0;
    
    ExpectVectorsEqual(result, {10.0, 15.0, 20.0});
    ExpectVectorsEqual(v, {2.0, 3.0, 4.0});  // v unchanged
}

TEST(VectorTest, ScalarMultiplicationMutating) {
    Vector<double> v{2.0, 3.0, 4.0};
    Vector<double>& ref = (v *= 5.0);
    
    EXPECT_EQ(&ref, &v);
    ExpectVectorsEqual(v, {10.0, 15.0, 20.0});
}

TEST(VectorTest, ScalarMultiplicationByZero) {
    Vector<double> v{2.0, 3.0, 4.0};
    Vector<double> result = v * 0.0;
    
    ExpectVectorsEqual(result, {0.0, 0.0, 0.0});
}

TEST(VectorTest, ScalarMultiplicationByOne) {
    Vector<double> v{2.0, 3.0, 4.0};
    Vector<double> result = v * 1.0;
    
    ExpectVectorsEqual(result, {2.0, 3.0, 4.0});
}

TEST(VectorTest, ScalarMultiplicationNegative) {
    Vector<double> v{2.0, 3.0, 4.0};
    Vector<double> result = v * -2.0;
    
    ExpectVectorsEqual(result, {-4.0, -6.0, -8.0});
}

// ==================== Dot Product ====================

TEST(VectorTest, DotProduct) {
    Vector<double> a{1.0, 2.0, 3.0};
    Vector<double> b{4.0, 5.0, 6.0};
    
    double result = a.dot(b);
    EXPECT_DOUBLE_EQ(result, 32.0);  // 1*4 + 2*5 + 3*6 = 32
}

TEST(VectorTest, DotProductZeroVectors) {
    Vector<double> a{0.0, 0.0, 0.0};
    Vector<double> b{1.0, 2.0, 3.0};
    
    EXPECT_DOUBLE_EQ(a.dot(b), 0.0);
}

TEST(VectorTest, DotProductSelfProduct) {
    Vector<double> v{3.0, 4.0};
    
    EXPECT_DOUBLE_EQ(v.dot(v), 25.0);  // 3*3 + 4*4 = 25
}

TEST(VectorTest, DotProductSizeMismatchThrows) {
    Vector<double> a{1.0, 2.0};
    Vector<double> b{1.0, 2.0, 3.0};
    
    EXPECT_THROW(a.dot(b), std::runtime_error);
}

TEST(VectorTest, DotProductWithIntegers) {
    Vector<int> a{2, 3, 4};
    Vector<int> b{5, 6, 7};
    
    EXPECT_EQ(a.dot(b), 56);  // 2*5 + 3*6 + 4*7 = 56
}

// ==================== Equality ====================

TEST(VectorTest, EqualityOperator) {
    Vector<double> a{1.0, 2.0, 3.0};
    Vector<double> b{1.0, 2.0, 3.0};
    
    EXPECT_TRUE(a == b);
}

TEST(VectorTest, InequalityDifferentValues) {
    Vector<double> a{1.0, 2.0, 3.0};
    Vector<double> b{1.0, 2.0, 4.0};
    
    EXPECT_FALSE(a == b);
}

TEST(VectorTest, InequalityDifferentSizes) {
    Vector<double> a{1.0, 2.0};
    Vector<double> b{1.0, 2.0, 3.0};
    
    EXPECT_FALSE(a == b);
}

TEST(VectorTest, EqualityWithZeroVectors) {
    Vector<double> a(5, 0.0);
    Vector<double> b(5, 0.0);
    
    EXPECT_TRUE(a == b);
}

TEST(VectorTest, EqualityWithIntegers) {
    Vector<int> a{1, 2, 3};
    Vector<int> b{1, 2, 3};
    
    EXPECT_TRUE(a == b);
}

// ==================== Integration Tests ====================

TEST(VectorTest, ChainedOperations) {
    Vector<double> a{1.0, 2.0, 3.0};
    Vector<double> b{2.0, 3.0, 4.0};
    Vector<double> c{1.0, 1.0, 1.0};
    
    // (a + b) * 2 - c
    Vector<double> result = (a + b) * 2.0;
    result = result - c;
    
    ExpectVectorsEqual(result, {5.0, 9.0, 13.0});  // (1+2)*2-1=5, (2+3)*2-1=9, (3+4)*2-1=13
}

TEST(VectorTest, ComplexDotProductCalculation) {
    Vector<double> a{1.0, 2.0, 3.0};
    Vector<double> b{4.0, 5.0, 6.0};
    Vector<double> c = a + b;
    // c = 5, 7, 9
    // a * c = 1*5 + 2*7 + 3*9 = 5 + 14 + 27 = 46

    double result = c.dot(a);
    EXPECT_DOUBLE_EQ(result, 46.0);  // (1+4)*1 + (2+5)*2 + (3+6)*3 = 5 + 14 + 27 = 46
}