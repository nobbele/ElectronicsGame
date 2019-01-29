#include "ScriptComponent.h"

#include "main.h"
#include <sstream>
#include <sys/stat.h>

int cfileexists(const char* filename) {
	struct stat buffer;
	int exist = stat(filename, &buffer);
	if (exist == 0)
		return 1;
	else // -1
		return 0;
}

int ScriptComponent::copy_count = 0;

ScriptComponent::ScriptComponent(const std::string file, const std::string component_name, GameObject *parent) :
	file(file), component_name(component_name), parent(parent)
{
	LoadScript();
	Start();
}

ScriptComponent::ScriptComponent(const ScriptComponent &copy) :
	file(copy.file), component_name(copy.component_name), parent(copy.parent)
{
	copy_count++;
	printf("ScriptComponent Copy %d\n", copy_count);
}

ScriptComponent::~ScriptComponent()
{
	Delete();
}

ScriptComponent & ScriptComponent::operator=(const ScriptComponent & move)
{
	return *this;
}

constexpr size_t cstrlen(const char *const str) {
	int i = 0;
	while (str[i]) i++;
	return i;
}

void ScriptComponent::Start()
{
	const std::string func = this->component_name + "_Start";

	if (!lua_getglobal(_L, func.c_str())) {
		printf("[SCRIPTCOMPONENT] Couldn't find function %s\n", func.c_str());
		return;
	}

	lua_pushlightuserdata(_L, static_cast<GameObject*>(this->parent));

	lua_call(_L, 1, 0);
}

void ScriptComponent::Update()
{
	const std::string func = this->component_name + "_Update";
	if (!lua_getglobal(_L, func.c_str())) {
		printf("[SCRIPTCOMPONENT] Couldn't find function %s\n", func.c_str());
		return;
	}

	lua_pushlightuserdata(_L, static_cast<GameObject*>(this->parent));

	lua_call(_L, 1, 0);
}

void ScriptComponent::Delete()
{
	const std::string func = this->component_name + "_Delete";
	printf("[SCRIPTCOMPONENT] Delete function is not working, todo");
	return;
	if (!lua_getglobal(_L, func.c_str())) {
		printf("[COMPONENT] Couldn't find function %s\n", func.c_str());
		return;
	}

	lua_pushlightuserdata(_L, static_cast<GameObject*>(this->parent));

	lua_call(_L, 1, 0);
}

void ScriptComponent::LoadScript()
{
	if (!cfileexists(file.c_str())) //File was not found
		printf("script %s was not found\n", file.c_str());

	luaL_dofile(_L, file.c_str());
}

void ScriptComponent::UpdateWatch()
{

}
