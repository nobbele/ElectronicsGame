#include "GameObject.h"
#include "Component.h"

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
	: position(0, 0)
{
	
}

GameObject::GameObject(const GameObject &copy) :
	position(copy.position)
{
	ScriptComponents.reserve(copy.ScriptComponents.size());
	for (const ScriptComponent &comp : copy.ScriptComponents) {
		ScriptComponents.push_back(comp);
		ScriptComponent &new_comp = ScriptComponents.back();
		new_comp.parent = this;
		new_comp.Start();
	}
	NativeComponents.reserve(copy.NativeComponents.size());
	for (const NativeComponent &comp : copy.NativeComponents) {
		NativeComponents.push_back(comp);
		NativeComponent &new_comp = NativeComponents.back();
		new_comp.parent = this;
		new_comp.Start();
	}
	this->copy_count++;
	printf("GameObject Copy %d\n", this->copy_count);
}

GameObject::~GameObject()
{

}

NativeComponent &GameObject::AddNativeComponent(NativeComponent &comp)
{
	this->NativeComponents.push_back(comp);
	dispatch_after_frame([&]() { comp.Start(); });
	return comp;
}

ScriptComponent &GameObject::AddScriptComponent(ScriptComponent &comp)
{
	this->ScriptComponents.push_back(comp);
	dispatch_after_frame([&]() { comp.Start(); });
	return comp;
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
	FOREACH_COMPONENT(obj, {
		comp.Delete();
	});
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

int lua_GameObject_GetPosition(lua_State *L) {
	GameObject *object = reinterpret_cast<GameObject*>(lua_touserdata(L, 1));
	lua_pushnumber(L, object->position.x);
	lua_pushnumber(L, object->position.y);
	return 2;
}
