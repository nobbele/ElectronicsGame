#include "GameObject.h"

static void stackDump(lua_State *L) {
	int i;
	int top = lua_gettop(L);
	for (i = 1; i <= top; i++) {  /* repeat for each level */
		int t = lua_type(L, i);
		switch (t) {

		case LUA_TSTRING:  /* strings */
			printf("`%s'", lua_tostring(L, i));
			break;

		case LUA_TBOOLEAN:  /* booleans */
			printf(lua_toboolean(L, i) ? "true" : "false");
			break;

		case LUA_TNUMBER:  /* numbers */
			printf("%g", lua_tonumber(L, i));
			break;

		default:  /* other values */
			printf("%s", lua_typename(L, t));
			break;

		}
		printf("  ");  /* put a separator */
	}
	printf("\n");  /* end the listing */
}

std::vector<GameObject> GameObject::all;
int GameObject::copy_count = 0;

GameObject::GameObject()
{
	position.x = 0;
	position.y = 0;
}

GameObject::GameObject(const GameObject &copy) :
	position(copy.position)
{
	Components.reserve(copy.Components.size());
	for (const Component &comp : copy.Components) {
		Components.push_back(comp);
		Component &new_comp = Components.back();
		new_comp.parent = this;
		new_comp.Start();
	}
	this->copy_count++;
	printf("GameObject Copy %d\n", this->copy_count);
}

GameObject::~GameObject()
{

}

GameObject *GameObject::Create()
{
	GameObject::all.emplace_back();
	return &GameObject::all.back();
}

void GameObject::Delete(GameObject **_obj)
{
	GameObject *obj = *_obj;
	GameObject::Delete(obj);
	*_obj = nullptr;
}

void GameObject::Delete(GameObject *obj)
{
	obj->~GameObject();
	ptrdiff_t index = std::distance(&GameObject::all.front(), obj);
	auto it = GameObject::all.begin() + index;
	GameObject::all.erase(it);
}

void GameObject::Reserve_add(size_t n)
{
	GameObject::Reserve_set(GameObject::all.capacity() + n);
}

void GameObject::Reserve_set(size_t n)
{
	GameObject::all.reserve(n);
}

int GameObject_lua_Get_Position(lua_State *L) {
	GameObject *object = reinterpret_cast<GameObject*>(lua_touserdata(L, 1));
	lua_pushnumber(L, object->position.x);
	lua_pushnumber(L, object->position.y);
	return 2;
}

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

int Component::copy_count = 0;

Component::Component(const std::string file, const std::string component_name, GameObject *parent) :
	file(file), component_name(component_name), parent(parent)
{
	LoadScript();
	Start();
}

Component::Component(const Component &copy) :
	file(copy.file), component_name(copy.component_name), parent(copy.parent)
{
	copy_count++;
	printf("Component Copy %d\n", copy_count);
}

Component::~Component()
{
	Delete();
}

Component & Component::operator=(const Component & move)
{
	return *this;
}

constexpr size_t cstrlen(const char *const str) {
	int i = 0;
	while (str[i]) i++;
	return i;
}

void Component::Start()
{
	const std::string func = component_name + "_Start";

	if (!lua_getglobal(_L, func.c_str())) {
		printf("[COMPONENT] Couldn't find function %s\n", func.c_str());
		return;
	}

	lua_pushlightuserdata(_L, static_cast<GameObject*>(parent));

	lua_call(_L, 1, 0);
}

void Component::Update()
{
	const std::string func = component_name + "_Update";
	if (!lua_getglobal(_L, func.c_str())) {
		printf("[COMPONENT] Couldn't find function %s\n", func.c_str());
		return;
	}

	lua_pushlightuserdata(_L, static_cast<GameObject*>(parent));

	lua_call(_L, 1, 0);
}

void Component::Delete()
{
	const std::string func = component_name + "_Delete";
	if (!lua_getglobal(_L, func.c_str())) {
		printf("[COMPONENT] Couldn't find function %s\n", func.c_str());
		return;
	}

	lua_pushlightuserdata(_L, static_cast<GameObject*>(parent));

	lua_call(_L, 1, 0);
}

void Component::LoadScript()
{
	if (!cfileexists(file.c_str())) //File was not found
		printf("script %s was not found\n", file.c_str());

	luaL_dofile(_L, file.c_str());
}

void Component::UpdateWatch()
{

}
