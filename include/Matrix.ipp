//
// Created by Yerdaulet Mussabek on 11.06.2026.
//

#ifndef MATRIX_IPP
#define MATRIX_IPP

#include <algorithm>
#include <iostream>

template<typename T>
Matrix<T>::Matrix(size_t n, size_t m, T init_val): n_(n), m_(m), data_(n * m, init_val) {}

template<typename T>
Matrix<T> Matrix<T>::identity(size_t n) {
    Matrix<T> ret(n, n, T{});
    for (size_t i = 1; i <= n; i++) {
        ret[i, i] = T{1};
    }
    return ret;
}

template<typename T>
Matrix<T> Matrix<T>::hilbert(size_t n) {
    Matrix<T> ret(n, n, 1.0);
    for (size_t i = 1; i <= n; i++) {
        for (size_t j = 1; j <= n; j++) {
            ret[i, j] /= (i + j - 1);
        }
    }
    return ret;
}

template<typename T>
size_t Matrix<T>::n() const {return n_;}

template<typename T>
size_t Matrix<T>::m() const {return m_;}

template<typename T>
T& Matrix<T>::operator[](size_t i, size_t j) {
    i--;
    j--;
    return data_[i * this->m() + j];
}

template<typename T>
const T& Matrix<T>::operator[](size_t i, size_t j) const {
    i--;
    j--;
    return data_[i * this->m() + j];
}

template<typename T>
T& Matrix<T>::at(size_t i, size_t j) {
    if (i < 1 || i > n_ || j < 1 || j > m_) {
        throw std::out_of_range("Matrix index out of range");
    }
    i--;
    j--;
    return data_[i * this->m() + j];
}

template<typename T>
const T& Matrix<T>::at(size_t i, size_t j) const {
    if (i < 1 || i > n_ || j < 1 || j > m_) {
        throw std::out_of_range("Matrix index out of range");
    }
    i--;
    j--;
    return data_[i * this->m() + j];
}

template<typename T>
Vector<T> Matrix<T>::row(size_t i) const {
    Vector<T> ret(this->m());
    for (size_t j = 1; j <= this->m(); j++) {
        ret[j] = (*this)[i, j];
    }
    return ret;
}

template<typename T>
Vector<T> Matrix<T>::col(size_t j) const {
    Vector<T> ret(this->n());
    for (size_t i = 1; i <= this->n(); i++) {
        ret[i] = (*this)[i, j];
    }
    return ret;
}

template<typename T>
void Matrix<T>::swap_rows(size_t r1, size_t r2) {
    for (size_t j = 1; j <= this->m(); j++) {
        std::swap((*this)[r1, j], (*this)[r2, j]);
    }
}

template<typename T>
Vector<T> Matrix<T>::operator*(const Vector<T> &v) const {
    if (v.size() != this->m()) throw std::runtime_error("Size Mismatch");
    Vector<T> ret(this->n(), 0);
    for (size_t i = 1; i <= this->n(); i++) {
        Vector<T> row = this->row(i);
        ret[i] = row.dot(v);
    }
    return ret;
}

template<typename T>
void Matrix<T>::print() const {
    for (int i = 1; i <= this->m() + 2; i++) {
        std::cout << '-';
    }
    std::cout << std::endl;

    for (int i = 1; i <= this->n(); i++) {
        for (int j = 1; j <= this->m(); j++) {
            std::cout << (*this)[i, j] << ' ';
        }
        std::cout << std::endl;
    }

    for (int i = 1; i <= this->m() + 2; i++) {
        std::cout << '-';
    }

    std::cout << std::endl;
}


#endif