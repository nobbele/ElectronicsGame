#pragma once

struct GameObject;
#include "GameObject.h"
#include "internal_Component.h"

struct ScriptComponent {
	COMPONENT_HEADER(ScriptComponent);

	const std::string file;

	ScriptComponent(const std::string file, const std::string component_name, GameObject *parent);
	~ScriptComponent();

	//Not yet implemented
	void UpdateWatch();
private:
	void LoadScript();

	static int copy_count;

	friend int main(int argc, char* argv[]);
	friend GameObject;
};