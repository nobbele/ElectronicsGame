#pragma once

#include "eg_containers.h"
#include <SDL.h>

struct globals {
    static bool running;
    static double delta_time;
    static unsigned int fps;
    static unsigned long int frame_count;
    static bool vsync;

    static Vector2<int> window_size;

    static SDL_Window *window;
    static SDL_GLContext context;
};