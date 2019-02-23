#pragma once

#define COMPONENT_HEADER(name) \
	const std::string component_name;\
	GameObject *parent = nullptr;\
	void Start() const;\
	void Update() const;\
	void Delete() const;\
	name(const name &copy);\
	name &operator=(const name &move);\
	void Call(const std::string &name) const;