#pragma once

#include "eg_containers.h"
#include <random>
extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}
#include "GameObject.h"
#include "eg_events.h"
#include "Components.h"

void nop(void*);

extern bool running;
extern double delta_time;
extern unsigned int fps;
extern unsigned long int frame_count;
extern bool vsync;

extern Vector2<int> window_size;

int eg_prand();

extern lua_State *_L;

const luaL_Reg Lua_API[] = {
	{ "GameObjectGetPositon", lua_GameObject_GetPosition },
	{ "SubscribeEvent", lua_SubscribeEvent },
	{ "GetNativeComponent", lua_GetNativeComponent },
	{ "GetScriptComponent", lua_GetScriptComponent },
};

template<typename T, int sz>
constexpr size_t sizeof_array(const T(&)[sz])
{
	return sz;
}