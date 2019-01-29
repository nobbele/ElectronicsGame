#pragma once

#include "NativeComponent.h"
#include "ScriptComponent.h"

NativeComponent *GetNativeComponent(GameObject &obj, const std::string &name);
inline NativeComponent *GetNativeComponent(GameObject *obj, const std::string &name)
{
	return GetNativeComponent(*obj, name);
}
int lua_GetNativeComponent(lua_State *L);

ScriptComponent *GetScriptComponent(GameObject &obj, const std::string &name);
inline ScriptComponent *GetScriptComponent(GameObject *obj, const std::string &name)
{
	return GetScriptComponent(*obj, name);
}
int lua_GetScriptComponent(lua_State *L);