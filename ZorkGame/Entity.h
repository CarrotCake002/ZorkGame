#pragma once

#include <iostream>
#include <string>
#include <list>

enum class EntityType
{
	None = 0,
	Player = 1,
	Item = 2,
	Creature = 3,
	Room = 4,
	Exit = 5
};

class Entity
{
public:
	Entity() = default;
	virtual ~Entity() = default;

	virtual void update(void);

private:
	EntityType type;
	std::string name;
	std::string description;
	std::list<Entity *> contains;
};

