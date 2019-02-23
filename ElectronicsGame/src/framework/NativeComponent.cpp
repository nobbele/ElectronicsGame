#include "NativeComponent.h"

void NativeComponent::Start() const
{
	if(this->functions.Start)
		this->functions.Start(parent);
}
void NativeComponent::Update() const
{
	if (this->functions.Update)
		this->functions.Update(parent);
}
void NativeComponent::Delete() const
{
	if (this->functions.Delete)
		this->functions.Delete(parent);
}

void NativeComponent::Call(const std::string &name) const
{
	NativeComponentFunction *const func = this->functions.Other.at(name);
	func(this->parent);
}

NativeComponent::NativeComponent(const NativeComponent &copy) :
	functions(copy.functions), component_name(copy.component_name), parent(copy.parent)
{

}
NativeComponent &NativeComponent::operator=(const NativeComponent &move) 
{
	return *this;
}

NativeComponent::NativeComponent(const NativeComponentFunctions &funcs,
								 const std::string &component_name,
								 GameObject *parent) :
	functions(funcs), component_name(component_name), parent(parent)
{}

NativeComponent::NativeComponent(NativeComponentFunction *Start,
								 NativeComponentFunction *Update,
								 NativeComponentFunction *Delete,
								 const OtherFunctionCollection &other,
								 const std::string &component_name,
								 GameObject *parent) :
	functions(Start, Update, Delete, other), component_name(component_name), parent(parent)
{}

NativeComponent::~NativeComponent()
{}
