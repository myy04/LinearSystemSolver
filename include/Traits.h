//
// Created by Yerdaulet Mussabek on 15.06.2026.
//

#ifndef TRAITS_H
#define TRAITS_H

template<typename T>
struct Accumulator {
    using Type = T;
};

template<>
struct Accumulator<float> {
    using Type = double;
};

#endif //TRAITS_H
