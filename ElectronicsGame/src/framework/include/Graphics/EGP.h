#ifndef EGP_H
#define EGP_H

#include <eg_containers.h>
#include <globals.h>

template<typename T>
inline Vector2<float> egpToGL(Vector2<T> pos) {
    Vector2<float> glPos(0,0);
    glPos.x = pos.x *  2.0f / window_size.x - 1.0f;
    glPos.y = pos.y * -2.0f / window_size.y + 1.0f;
    return glPos;
}

#endif