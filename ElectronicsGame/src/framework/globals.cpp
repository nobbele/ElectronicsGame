#include "globals.h"

bool running = false;
double delta_time = 0;
unsigned int fps = 0;
unsigned long int frame_count = 0;
bool vsync = false;

Vector2<int> window_size = { 800, 600 };

SDL_Window *window = nullptr;
SDL_GLContext context = nullptr;