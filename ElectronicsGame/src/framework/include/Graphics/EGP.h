#ifndef EGP_H
#define EGP_H

#include <eg_containers.h>
#include <globals.h>

template<typename T>
inline Vector2<float> egpToGL(Vector2<T> pos) {
    //return pos / globals::window_size * 2 - 1;
    return Vector2<float>(pos.x * 2.0f / globals::window_size.x - 1, pos.y * -2.0f / globals::window_size.y + 1);
}

#endif