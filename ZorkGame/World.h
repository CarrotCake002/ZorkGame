#pragma once

#include "Entity.h"
#include "Creature.h"
#include "Utils.h"

#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

enum class Action {
	QUIT,
	LOOK,
	TAKE,
	USE,
	INVALID
};

class World
{
public:
	World() = default;
	~World();

	void cmdLook(void);
	void cmdInventory(void);
	int cmdTake(std::string target);
	int cmdDrop(std::string target);
	int cmdPut(std::string target, std::string item);

	bool isRunning(void) const { return !quit; };

	int getInput(void);
	int splitCommands(std::string input);
	int parseCommands(void);
	int handleCommand(std::string command);

	int handleAction(std::string action, std::string target, std::string conjunction, std::string item);
	Entity *getTarget(std::string target) const;

	void addEntity(Entity* entity) { entities.push_back(entity); }

private:
	bool quit = false;
	std::vector<std::string> commands;
	std::vector<Entity *> entities;
};

