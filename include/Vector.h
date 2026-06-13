//
// Created by Yerdaulet Mussabek on 11.06.2026.
//

#ifndef VECTOR_H
#define VECTOR_H

#include <vector>


template<typename T>
class Vector {
public:
    explicit Vector(int size);
    Vector(std::initializer_list<T>);

    T& operator [](int ind);
    const T& operator[](int ind) const;

    [[nodiscard]] size_t size() const;

    Vector<T>& operator+(const Vector<T>&);
    Vector<T>& operator-(const Vector<T>&);
    Vector<T>& operator*(const Vector<T>&);
    Vector<T>& operator*(const T&);
    T dot(const Vector<T>&);
    const bool operator==(const Vector<T>&) const;

    void print() const;
private:
    std::vector<T> vector_;
};

#include "Vector.ipp"
#endif //VECTOR_H
