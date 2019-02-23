#include "globals.h"

bool globals::running = false;
double globals::delta_time = 0;
unsigned int globals::fps = 0;
unsigned long int globals::frame_count = 0;
bool globals::vsync = false;

Vector2<int> globals::window_size = { 800, 600 };

SDL_Window *globals::window = nullptr;
SDL_GLContext globals::context = nullptr;