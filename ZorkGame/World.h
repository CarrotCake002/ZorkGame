#pragma once

#include "Entity.h"
#include <vector>
#include <iostream>

class World
{
public:
	World() = default;
	~World();

	void update(void);

	void addEntity(Entity* entity) { entities.push_back(entity); }

private:
	std::vector<Entity *> entities;
};

