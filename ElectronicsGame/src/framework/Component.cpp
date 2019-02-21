#include "Component.h"
#include "eg_lua.h"

NativeComponent *GetNativeComponent(GameObject &obj, const std::string &name)
{
	for (NativeComponent &comp : obj.NativeComponents) {
		if (comp.component_name == name) return &comp;
	}
	return nullptr;
}
int lua_GetNativeComponent(lua_State *L)
{
	GameObject *object = clua_getptr<GameObject>(L, 1);
	const char *name = lua_tostring(L, 2);
	NativeComponent *comp = GetNativeComponent(object, name);
	lua_pushlightuserdata(L, static_cast<NativeComponent*>(comp));
	return 1;
}

int lua_CallNativeComponentFunction(lua_State * L)
{
	NativeComponent *comp = clua_getptr<NativeComponent>(L, 1);
	const char *func = lua_tostring(L, 2);
	comp->Call(func);
	return 0;
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
	GameObject *object = clua_getptr<GameObject>(L, 1);
	const char *name = lua_tostring(L, 2);
	ScriptComponent *comp = GetScriptComponent(object, name);
	lua_pushlightuserdata(L, static_cast<ScriptComponent*>(comp));
	return 1;
}

int lua_CallScriptComponentFunction(lua_State * L)
{
	ScriptComponent *comp = clua_getptr<ScriptComponent>(L, 1);
	const char *func = lua_tostring(L, 2);
	comp->Call(func);
	return 0;
}
