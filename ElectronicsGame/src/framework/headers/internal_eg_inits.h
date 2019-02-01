#pragma once

#include <SDL.h>
extern "C" {
#include <lua.h>
}

inline void initLua()
{
	_L = luaL_newstate();

	luaopen_base(_L);
	luaopen_table(_L);
	luaopen_io(_L);
	luaopen_string(_L);
	luaopen_math(_L);

	for (unsigned int i = 0; i < sizeof_array(Lua_API); i++) {
		lua_register(_L, Lua_API[i].name, Lua_API[i].func);
	}
}
inline void initSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0) {
		fprintf(stderr, "Error Initializing SDL %s\n", SDL_GetError());
		getchar();
		exit(-1);
	}
}
inline void initGl3w()
{
	int err;
	if ((err = gl3wInit()) != GL3W_OK) {
		fprintf(stderr, "Error Initializing gl3w %d\n", err);
		getchar();
		exit(-1);
	}
}