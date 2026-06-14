//
// Created by Yerdaulet Mussabek on 11.06.2026.
//

#ifndef VECTOR_IPP
#define VECTOR_IPP

#include <iostream>
#include <stdexcept>
#include <cmath>

template<typename T>
Vector<T>::Vector(size_t size): data_(size, T{}) {}

template<typename T>
Vector<T>::Vector(size_t size, T init_val): data_(size, init_val) {}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init): data_(init) {}

template<typename T>
T& Vector<T>::operator[](size_t ind) {
    ind--;
    return data_[ind];
}

template<typename T>
const T& Vector<T>::operator[](size_t ind) const {
    ind--;
    return data_[ind];
}

template<typename T>
T& Vector<T>::at(size_t ind) {
    ind--;
    return data_.at(ind);
}

template<typename T>
const T& Vector<T>::at(size_t ind) const {
    ind--;
    return data_.at(ind);
}


template<typename T>
size_t Vector<T>::size() const {
    return data_.size();
}

template<typename T>
Vector<T>& Vector<T>::operator+=(const Vector<T>& other) {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");
    for (size_t i = 1; i <= this->size(); i++) {
        (*this)[i] += other[i];
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator-=(const Vector<T>& other) {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");
    for (size_t i = 1; i <= this->size(); i++) {
        (*this)[i] -= other[i];
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator*=(const Vector<T>& other) {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");
    for (size_t i = 1; i <= this->size(); i++) {
        (*this)[i] *= other[i];
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator*=(const T& scalar) {
    for (size_t i = 1; i <= this->size(); i++) {
        (*this)[i] *= scalar;
    }
    return *this;
}

template<typename T>
Vector<T> Vector<T>::operator+(const Vector<T>& other) const {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");

    Vector<T> ret(this->size());
    for (size_t i = 1; i <= this->size(); i++) {
        ret[i] = (*this)[i] + other[i];
    }
    return ret;
}

template<typename T>
Vector<T> Vector<T>::operator-(const Vector<T>& other) const {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");

    Vector<T> ret(this->size());
    for (size_t i = 1; i <= this->size(); i++) {
        ret[i] = (*this)[i] - other[i];
    }
    return ret;
}

template<typename T>
Vector<T> Vector<T>::operator*(const Vector<T>& other) const {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");

    Vector<T> ret(this->size());
    for (size_t i = 1; i <= this->size(); i++) {
        ret[i] = (*this)[i] * other[i];
    }
    return ret;
}

template<typename T>
Vector<T> Vector<T>::operator*(const T& scalar) const {
    Vector<T> ret(this->size());
    for (size_t i = 1; i <= this->size(); i++) {
        ret[i] = (*this)[i] * scalar;
    }
    return ret;
}


template<typename T>
T Vector<T>::dot(const Vector<T>& other) const {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");

    T ret{};
    for (size_t i = 1; i <= this->size(); i++) {
        ret = ret + ((*this)[i] * other[i]);
    }

    return ret;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T>& other) const {
    if (other.size() != this->size()) return false;
    for (size_t i = 1; i <= this->size(); i++) {
        if ((*this)[i] != other[i]) return false;
    }
    return true;
}

template<typename T>
void Vector<T>::print() const {
    std::cout << "Vector: ";
    for (size_t i = 1; i <= this->size(); i++) {
        std::cout << (*this)[i] << ' ';
    }
    std::cout << std::endl;
}

template<typename T>
Vector<T> operator*(const T& scalar, const Vector<T>& v) {
    Vector<T> ret = v * scalar;
    return ret;
}

template<typename T>
T Vector<T>::norm() const {
    T ret{};
    for (size_t i = 1; i <= this->size(); i++) {
        ret += ((*this)[i] * (*this)[i]);
    }
    ret = std::sqrt(ret);
    return ret;
}

#endif