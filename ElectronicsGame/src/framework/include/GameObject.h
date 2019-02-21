#pragma once

#include "eg_containers.h"
#include "misc.h"
#include <vector>
#include <functional>
struct ScriptComponent;
#include "ScriptComponent.h"
struct NativeComponent;
#include "NativeComponent.h"
extern "C" {
	#include "lua.h"
}

#undef main

struct GameObject {
	Vector2<float> position;
	std::vector<ScriptComponent> ScriptComponents;
	std::vector<NativeComponent> NativeComponents;

	GameObject();
	GameObject(const GameObject& copy);
	~GameObject();

	NativeComponent &AddNativeComponent(NativeComponent &comp);
	template <class... Args>
	inline NativeComponent &AddNewNativeComponent(Args&&... args)
	{
		this->NativeComponents.emplace_back(args...);
		NativeComponent &comp = this->NativeComponents.back();
		dispatch_after_frame([&]() { comp.Start(); });
		return comp;
	}
	ScriptComponent &AddScriptComponent(ScriptComponent &comp);
	template <class... Args>
	inline ScriptComponent &AddNewScriptComponent(Args&&... args)
	{
		this->ScriptComponents.emplace_back(args...);
		ScriptComponent &comp = this->ScriptComponents.back();
		dispatch_after_frame([&]() { comp.Start(); });
		return comp;
	}

	static GameObject *Create();
	static void Delete(GameObject**);
	static void Delete(GameObject*);
	static void Reserve_add(size_t n);
	static void Reserve_set(size_t n);

	static inline std::vector<GameObject> &GetAll() {
		return all;
	}

	friend ScriptComponent;
	friend NativeComponent;

private:
	static std::vector<GameObject> all;
	static int copy_count;

	friend int main(int argc, char* argv[]);
};

int lua_GameObject_GetPosition(lua_State *L);
