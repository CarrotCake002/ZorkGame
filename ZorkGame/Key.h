#pragma once

#include "Entity.h"

class Key : public Entity
{
public:
	Key(std::string name, std::string description, int exit_id);
	~Key() = default;

	int getId(void) const { return exit_id; };

private:
	int exit_id;
};

