#pragma once

#include "GameObject.h"
#include "eg_events.h"
#include "Component.h"

extern "C" {
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

template<typename T>
T *clua_getptr(lua_State *L, int index)
{
	return reinterpret_cast<T*>(lua_touserdata(L, index));
}

extern lua_State *_L;

const luaL_Reg Lua_API[] = {
	{ "GameObjectGetPositon", lua_GameObject_GetPosition },
	{ "SubscribeEvent", lua_SubscribeEvent },
	{ "GetNativeComponent", lua_GetNativeComponent },
	{ "GetScriptComponent", lua_GetScriptComponent },
	{ "CallNativeComponent", lua_CallNativeComponentFunction },
	{ "CallScriptComponent", lua_CallScriptComponentFunction }
};