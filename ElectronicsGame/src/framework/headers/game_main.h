#pragma once

#include <vector>
#include <SDL_render.h>

void game_start(void);
//Update is called in a seperate thread
void game_update(void);
void game_draw(SDL_GLContext context);
void game_end(void);