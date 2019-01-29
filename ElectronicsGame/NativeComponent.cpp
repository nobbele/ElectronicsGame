#include "NativeComponent.h"

void NativeComponent::Start() 
{
	if(this->functions.Start)
		this->functions.Start(parent);
}
void NativeComponent::Update() 
{
	if (this->functions.Update)
		this->functions.Update(parent);
}
void NativeComponent::Delete() 
{
	if (this->functions.Delete)
		this->functions.Delete(parent);
}

NativeComponent::NativeComponent(const NativeComponent &copy) :
	functions(copy.functions), component_name(copy.component_name), parent(copy.parent)
{

}
NativeComponent &NativeComponent::operator=(const NativeComponent &move) 
{
	return *this;
}

NativeComponent::NativeComponent(const NativeComponentFunctions funcs,
								 const std::string &component_name,
								 GameObject *parent) :
	functions(funcs), component_name(component_name), parent(parent)
{
	this->Start();
}

NativeComponent::NativeComponent(NativeComponentFunction *Start,
								 NativeComponentFunction *Update,
								 NativeComponentFunction *Delete,
								 const std::string &component_name,
								 GameObject *parent) :
	functions(Start, Update, Delete), component_name(component_name), parent(parent)
{
	this->Start();
}

NativeComponent::NativeComponent(const std::function<NativeComponentFunction> &Start, 
								 const std::function<NativeComponentFunction> &Update, 
								 const std::function<NativeComponentFunction> &Delete,
								 const std::string &component_name,
								 GameObject *parent) :
	functions(Start, Update, Delete), component_name(component_name), parent(parent)
{
	this->Start();
}

NativeComponent::~NativeComponent()
{
	this->Delete();
}
