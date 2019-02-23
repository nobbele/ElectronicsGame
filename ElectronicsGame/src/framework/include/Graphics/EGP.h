#ifndef EGP_H
#define EGP_H

#include <eg_containers.h>
#include <globals.h>

template<typename T>
inline Vector2<float> egpToGL(Vector2<T> pos) {
    return pos / globals::window_size * 2 - 1;
}

#endif