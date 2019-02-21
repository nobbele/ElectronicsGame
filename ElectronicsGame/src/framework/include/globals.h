#pragma once

#include "eg_containers.h"
#include <SDL.h>

extern bool running;
extern double delta_time;
extern unsigned int fps;
extern unsigned long int frame_count;
extern bool vsync;

extern Vector2<int> window_size;

extern SDL_Window *window;
extern SDL_GLContext context;