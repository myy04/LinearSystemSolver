//
// Created by Yerdaulet Mussabek on 11.06.2026.
//

#ifndef VECTOR_IPP
#define VECTOR_IPP

#include <iostream>

template<typename T>
Vector<T>::Vector(int size): vector_(size) {}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> init): vector_(init) {}

template<typename T>
T &Vector<T>::operator[](int ind) {
    return vector_[ind];
}

template<typename T>
const T &Vector<T>::operator[](int ind) const {
    return vector_[ind];
}

template<typename T>
size_t Vector<T>::size() const {
    return vector_.size();
}

template<typename T>
Vector<T> &Vector<T>::operator+(const Vector<T> &other) {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");
    for (int i = 0; i < this->size(); i++) {
        this[i] += other[i];
    }
    return this;
}

template<typename T>
Vector<T> &Vector<T>::operator-(const Vector<T> &other) {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");
    for (int i = 0; i < this->size(); i++) {
        this[i] -= other[i];
    }
    return this;
}

template<typename T>
Vector<T> &Vector<T>::operator*(const Vector<T> &other) {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");
    for (int i = 0; i < this->size(); i++) {
        this[i] *= other[i];
    }
    return this;
}

template<typename T>
Vector<T> &Vector<T>::operator*(const T &scalar) {
    for (int i = 0; i < this->size(); i++) {
        this[i] *= scalar;
    }
    return this;
}

template<typename T>
T Vector<T>::dot(const Vector<T> &other) {
    if (other.size() != this->size()) throw std::runtime_error("Size Mismatch");

    T ret{};
    for (int i = 0; i < this->size(); i++) {
        ret = ret + (this[i] * other[i]);
    }

    return ret;
}

template<typename T>
bool Vector<T>::operator==(const Vector<T> &other) const {
    if (other.size() != this->size()) return false;
    for (int i = 0; i < this->size(); i++) {
        if (this[i] != other[i]) return false;
    }
    return true;
}

template<typename T>
void Vector<T>::print() const {
    std::cout << "Vector: ";
    for (int i = 0; i < this->size(); i++) {
        std::cout << this[i] << ' ';
    }
    std::cout << std::endl;
}

#endif VECTOR_IPP