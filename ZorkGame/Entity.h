#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

#include "Utils.h"

enum class EntityType
{
	NONE,
	PLAYER,
	ITEM,
	WEAPON,
	ARMOR,
	CONTAINER,
	CREATURE,
	ROOM,
	KEY,
	NOTE,
	EXIT
};

class Entity
{
public:
	Entity() = default;
	Entity(std::string name, std::string description, EntityType type = EntityType::ITEM);
	virtual ~Entity() = default;

	virtual void display(void) const;
	virtual void printContains(void) const;
	virtual std::string getPrintableName(void) const;

	virtual void addItem(Entity* item);
	virtual bool hasItem(std::string name) const;
	Entity* removeItem(std::string name);

	Entity* getItem(std::string name) const;
	virtual std::string getName(void) const { return name; };
	virtual std::string getDescription(void) const { return description; };
	virtual EntityType getType(void) const { return type; };
	std::list<Entity*> getContains(void) const { return contains; };

protected:
	EntityType type = EntityType::ITEM;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
};
