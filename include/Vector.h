//
// Created by Yerdaulet Mussabek on 11.06.2026.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <vector>

template<typename T>
class Vector {
public:
    explicit Vector(size_t size);
    explicit Vector(size_t size, T init_val);

    Vector(std::initializer_list<T>);

    T& operator [](size_t ind);
    const T& operator[](size_t ind) const;

    T& at(size_t ind);
    const T& at(size_t ind) const;

    [[nodiscard]] size_t size() const;

    Vector<T>& operator+=(const Vector<T>&);
    Vector<T>& operator-=(const Vector<T>&);
    Vector<T>& operator*=(const Vector<T>&);
    Vector<T>& operator*=(const T&);

    Vector<T> operator+(const Vector<T>&) const;
    Vector<T> operator-(const Vector<T>&) const;
    Vector<T> operator*(const Vector<T>&) const;
    Vector<T> operator*(const T&) const;

    T dot(const Vector<T>&) const;
    bool operator==(const Vector<T>&) const;

    void print() const;
private:
    std::vector<T> data_;
};

template<typename T>
Vector<T> operator*(double scalar, const Vector<T>& v);

#include "Vector.ipp"
#endif
