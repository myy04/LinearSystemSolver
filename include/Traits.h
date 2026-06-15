//
// Created by Yerdaulet Mussabek on 15.06.2026.
//

#ifndef TRAITS_H
#define TRAITS_H

template<typename T>
struct Accumulator {
    using type = T;
};

template<>
struct Accumulator<float> {
    using type = double;
};

template<typename T>
using Accumulator_t = typename Accumulator<T>::type;

#endif //TRAITS_H
