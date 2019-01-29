#pragma once

#include "internal_Component.h"
struct GameObject;
#include "GameObject.h"

typedef void(NativeComponentFunction)(GameObject*);

#define NULL_FUNCTION (std::function<NativeComponentFunction>((*NativeComponentFunction)0))

struct NativeComponentFunctions
{
	const std::function<NativeComponentFunction> Start;
	const std::function<NativeComponentFunction> Update;
	const std::function<NativeComponentFunction> Delete;
	inline NativeComponentFunctions(NativeComponentFunction *Start,
									NativeComponentFunction *Update,
									NativeComponentFunction *Delete) :
		Start(Start), Update(Update), Delete(Delete)
	{}
	inline NativeComponentFunctions(const std::function<NativeComponentFunction> &Start,
									const std::function<NativeComponentFunction> &Update,
									const std::function<NativeComponentFunction> &Delete) :
		Start(Start), Update(Update), Delete(Delete)
	{}
};

struct NativeComponent
{
	COMPONENT_HEADER(NativeComponent);

	const NativeComponentFunctions functions;

	NativeComponent(const NativeComponentFunctions funcs,
					const std::string &component_name,
					GameObject *parent);
	NativeComponent(NativeComponentFunction *Start, 
					NativeComponentFunction *Update, 
					NativeComponentFunction *Delete,
					const std::string &component_name,
					GameObject *parent);
	NativeComponent(const std::function<NativeComponentFunction> &Start,
					const std::function<NativeComponentFunction> &Update,
					const std::function<NativeComponentFunction> &Delete,
					const std::string &component_name,
					GameObject *parent);
	~NativeComponent();
};
