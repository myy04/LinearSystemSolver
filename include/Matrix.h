//
// Created by Yerdaulet Mussabek on 11.06.2026.
//

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "Vector.h"

template<typename T>
class Matrix {
public:
    Matrix() = default;
    explicit Matrix(size_t n, size_t m, T init_val);

    static Matrix identity(size_t n);
    static Matrix hilbert(size_t n);

    size_t n() const;
    size_t m() const;

    T& operator[](size_t i, size_t j);
    const T& operator[](size_t i, size_t j) const;

    T& at(size_t i, size_t j);
    const T& at(size_t i, size_t j) const;

    Vector<T> row(size_t i) const;
    Vector<T> col(size_t j) const;

    void swap_rows(size_t r1, size_t r2);

    void print() const;

    Vector<T> operator*(const Vector<T>& v) const;
private:
    size_t n_ = 0;
    size_t m_ = 0;
    std::vector<T> data_;
};

#include "Matrix.ipp"
#endif //MATRIX_H
