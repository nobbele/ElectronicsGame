#pragma once

#include <unordered_map>
#include "internal_Component.h"
struct GameObject;
#include "GameObject.h"

typedef void(NativeComponentFunction)(GameObject*);
typedef std::unordered_map<std::string, NativeComponentFunction*> OtherFunctionCollection;

#define NULL_FUNCTION ((*NativeComponentFunction)0)

struct NativeComponentFunctions
{
	NativeComponentFunction *Start;
	NativeComponentFunction *Update;
	NativeComponentFunction *Delete;
	const OtherFunctionCollection Other;
	inline NativeComponentFunctions(NativeComponentFunction *Start,
									NativeComponentFunction *Update,
									NativeComponentFunction *Delete,
									const OtherFunctionCollection other) :
		Start(Start), Update(Update), Delete(Delete), Other(other)
	{}
};

struct NativeComponent
{
	COMPONENT_HEADER(NativeComponent);

	const NativeComponentFunctions functions;

	NativeComponent(const NativeComponentFunctions &funcs,
					const std::string &component_name,
					GameObject *parent);
	NativeComponent(NativeComponentFunction *Start, 
					NativeComponentFunction *Update, 
					NativeComponentFunction *Delete,
					const OtherFunctionCollection &other,
					const std::string &component_name,
					GameObject *parent);
	~NativeComponent();
};
