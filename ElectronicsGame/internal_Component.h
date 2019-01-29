#pragma once

#define COMPONENT_HEADER(name) \
	const std::string component_name;\
	GameObject *parent = nullptr;\
	void Start();\
	void Update();\
	void Delete();\
	name(const name &copy);\
	name &operator=(const name &move);