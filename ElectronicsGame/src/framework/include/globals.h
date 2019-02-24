#pragma once

#include "eg_containers.h"
#include <SDL.h>

struct globals {
    static bool running;
    static double deltaTime;
    static unsigned int fps;
    static unsigned long int frameCount;
    static bool vsync;

    static Vector2<int> window_size;

    static SDL_Window *window;
    static SDL_GLContext context;
};