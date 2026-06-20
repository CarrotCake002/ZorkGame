#pragma once

#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include <nlohmann/json.hpp>

#include "Utils.h"

enum class EntityType
{
	NONE = 0,
	PLAYER = 1,
	ITEM = 2,
	WEAPON = 3,
	ARMOR = 4,
	CONTAINER = 5,
	CREATURE = 6,
	ROOM = 7,
	KEY = 8,
	NOTE = 9,
	EXIT = 10
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

	bool isItem(void) const;
	bool isCreature(void) const;

	virtual nlohmann::json toJson(void) const;

protected:
	EntityType type = EntityType::ITEM;
	std::string name;
	std::string description;
	std::list<Entity*> contains;
};
