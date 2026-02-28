#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include "Utils.h"

enum class EntityType
{
	None,
	Player,
	Item,
	Container,
	Creature,
	Room,
	Exit
};

class Entity
{
public:
	Entity() = default;
	Entity(std::string name, std::string description, EntityType type = EntityType::Item);
	virtual ~Entity() = default;

	virtual void display(void);
	virtual void printContains(void) const;

	virtual void addItem(Entity* item);
	virtual bool hasItem(std::string name) const;
	Entity* getItem(std::string name) const;
	Entity* removeItem(std::string name);

	virtual std::string getName() const { return name; };
	virtual std::string getDescription() const { return description; };
	virtual EntityType getType() const { return type; };
	std::list<Entity*> getContains() const { return contains; };

protected:
	EntityType type = EntityType::Item;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
};
