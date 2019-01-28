#pragma once

#include "eg_containers.h"
#include <vector>
#include <functional>
extern "C" {
	#include "lua.h"
}
#undef main

struct GameObject;

struct Component {
	const std::string file;
	const std::string component_name;
	GameObject *parent = nullptr;

	Component(const std::string file, const std::string component_name, GameObject *parent);
	Component(const Component& copy);
	~Component();
	
	Component &operator=(const Component& move);

	void Start();
	void Update();
	void Delete();
private:
	void LoadScript();
	//Not yet implemented
	void UpdateWatch();

	static int copy_count;

	friend int main(int argc, char* argv[]);
	friend GameObject;
};

struct GameObject {
	Vector2<float> position;
	std::vector<Component> Components;

	GameObject();
	GameObject(const GameObject& copy);
	~GameObject();

	static GameObject *Create();
	static void Delete(GameObject**);
	static void Delete(GameObject*);
	static void Reserve_add(size_t n);
	static void Reserve_set(size_t n);

	static inline std::vector<GameObject> &GetAll() {
		return all;
	}

	friend Component;

private:
	static std::vector<GameObject> all;
	static int copy_count;

	friend int main(int argc, char* argv[]);
};

//Lua API
int GameObject_lua_Get_Position(lua_State *L);
