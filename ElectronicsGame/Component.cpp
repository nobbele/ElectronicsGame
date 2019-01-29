#include "Components.h"

NativeComponent *GetNativeComponent(GameObject &obj, const std::string &name)
{
	for (NativeComponent &comp : obj.NativeComponents) {
		if (comp.component_name == name) return &comp;
	}
	return nullptr;
}
int lua_GetNativeComponent(lua_State *L)
{
	GameObject *object = reinterpret_cast<GameObject*>(lua_touserdata(L, 1));
	const char *name = lua_tostring(L, 2);
	NativeComponent *comp = GetNativeComponent(object, name);
	lua_pushlightuserdata(L, static_cast<NativeComponent*>(comp));
	return 1;
}

ScriptComponent *GetScriptComponent(GameObject &obj, const std::string &name)
{
	for (ScriptComponent &comp : obj.ScriptComponents) {
		if (comp.component_name == name) return &comp;
	}
	return nullptr;
}
int lua_GetScriptComponent(lua_State *L)
{
	GameObject *object = reinterpret_cast<GameObject*>(lua_touserdata(L, 1));
	const char *name = lua_tostring(L, 2);
	ScriptComponent *comp = GetScriptComponent(object, name);
	lua_pushlightuserdata(L, static_cast<ScriptComponent*>(comp));
	return 1;
}