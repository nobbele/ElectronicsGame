#pragma once

#include "eg_containers.h"
#include "misc.h"
#include <vector>
#include <functional>
#include <utility>
#include <variant>
struct ScriptComponent;
#include "ScriptComponent.h"
struct NativeComponent;
#include "NativeComponent.h"
extern "C" {
	#include "lua.h"
}

template<
	typename T1, 
	typename T2,
	typename T1Store = std::vector<T1>&,
	typename T2Store = std::vector<T2>&
>
struct DoubleIterator {
	using FirstType = T1;
	using SecondType = T2;
	T1Store first;
	T2Store second;

	uint64_t offset = 0;

	DoubleIterator(T1Store first, T2Store second)
		: first(first), second(second)
	{

	}
	DoubleIterator(T1Store first, T2Store second, uint64_t offset) 
		: DoubleIterator(first, second) 
	{
		this->offset = offset;
	}

	DoubleIterator begin() {
		return DoubleIterator(first, second, 0);
	}
	DoubleIterator end() {
		return DoubleIterator(first, second, first.size() + second.size() - 1);
	}

	DoubleIterator& operator++() {
		this->offset++;
		return *this;
	}
	bool operator!=(DoubleIterator const& other) const {
		return offset != other.offset;
	}
	using VariantType = std::variant<FirstType*, SecondType*>;
	VariantType operator*() {
		if(offset < first.size())
			return &first.at(offset);
		else
			return &second.at(offset);
	}
};

using ComponentIterator = DoubleIterator<ScriptComponent, NativeComponent>;
using ComponentVariant = ComponentIterator::VariantType;

struct GameObject {
	Vector2<float> position;

	std::vector<ScriptComponent> ScriptComponents;
	std::vector<NativeComponent> NativeComponents;

	GameObject();
	GameObject(const GameObject& copy);
	~GameObject();

	ComponentIterator GetComponentIterator() {
		return ComponentIterator(ScriptComponents, NativeComponents);
	}

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

	friend ScriptComponent;
	friend NativeComponent;

	static std::vector<GameObject> all;

private:
	static int copy_count;
};

int lua_GameObject_GetPosition(lua_State *L);
