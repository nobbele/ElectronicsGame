#include <iostream>
#include <sstream>
#include <map>
#include <functional>
#include <vector>
#include <thread>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "game_main.h"
#include "eg_events.h"
#include "eg_containers.h"
#include "main.h"
#include "GameObject.h"
#include "NativeComponent.h"
#include "ScriptComponent.h"

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

void nop(void*) {
	return;
}

bool running = false;
double delta_time = 0;
unsigned int fps = 0;
unsigned long int frame_count = 0;
bool vsync = false;

Vector2<int> window_size = { 640, 480 };

std::mt19937 mt((unsigned int)time(0));
std::uniform_int_distribution<int> dist(0);

int eg_prand() {
	return dist(mt);
}

lua_State* _L;

Uint32 fps_timer(Uint32 interval, void* param) {

	return interval;
}

#undef main
int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
		printf("Error Initializing SDL %s", SDL_GetError());
		getchar();
		return -1;
	}
	if (TTF_Init() < 0) {
		printf("Error Initializing TTF %s", SDL_GetError());
		getchar();
		return -1;
	}

	SDL_Window *window = SDL_CreateWindow("ElectronicsGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_size.x, window_size.y, SDL_WINDOW_RESIZABLE);
	if (!window) {
		printf("Error Initializing Window %s", SDL_GetError());
		getchar();
		return -1;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, (SDL_RENDERER_PRESENTVSYNC & (vsync << 2)) | SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Error Initializing Renderer %s", SDL_GetError());
		getchar();
		return -1;
	}
	TTF_Font *arial = TTF_OpenFont("C:/Windows/Fonts/arial.ttf", 32);
	if (!arial) {
		printf("Error Loading Arial Font %s", SDL_GetError());
		getchar();
		return -1;
	}

	SDL_AddTimer(1, fps_timer, nullptr);

	_L = luaL_newstate();

	luaopen_base(_L);
	luaopen_table(_L);
	luaopen_io(_L);
	luaopen_string(_L);
	luaopen_math(_L);

	for (unsigned int i = 0; i < sizeof_array(Lua_API); i++) {
		lua_register(_L, Lua_API[i].name, Lua_API[i].func);
	}

	game_start();

	Uint32 lastframe = SDL_GetTicks();
	double last_current_time = 0;

	running = true;
	while (running) {
		/*Events*/
		{
			SDL_Event event;
			while (SDL_PollEvent(&event)) {
				if (event.type == SDL_EventType::SDL_QUIT)
					running = false;
				for (eg_events::Subscription sub : eg_events::event_subscriptions) {
					if (sub.type == event.type) {
						sub.callback(event);
					}
				}
			}
		}

		/*Misc*/
		{
			Uint32 current_time = SDL_GetTicks();

			delta_time = (current_time - last_current_time) / 1000;
			fps = (unsigned int)(1.0 / delta_time);

			frame_count++;
			last_current_time = current_time;

			for (GameObject &obj : GameObject::GetAll()) {
				for (ScriptComponent &comp : obj.ScriptComponents) {
					comp.UpdateWatch();
					comp.Update();
				}
				for (NativeComponent &comp : obj.NativeComponents) {
					comp.Update();
				}
			}
		}

		/*Game logic*/
		{
			game_update();
		}

		/*Drawing*/
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);

			game_draw(renderer);

			SDL_RenderPresent(renderer);
		}
	}

	game_end();

	lua_close(_L);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	return 0;
}