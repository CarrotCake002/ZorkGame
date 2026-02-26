#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

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
	Entity(std::string name, std::string description);
	virtual ~Entity() = default;

	virtual void display(void);
	virtual void printContains(void) const;

	virtual void addItem(Entity* item);
	Entity *removeItem(std::string name);

	virtual std::string getName() const { return name; };
	virtual std::string getDescription() const { return description; };
	virtual EntityType getType() const { return type; };

protected:
	EntityType type;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
	// add room for location
};
