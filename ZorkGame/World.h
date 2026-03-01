#pragma once

#include "Entity.h"
#include "Creature.h"
#include "Utils.h"
#include "Room.h"
#include "Exit.h"
#include "Weapon.h"

#include "Constants.h"

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
	World();
	~World();

	// DISPLAY COMMANDS
	void cmdLook(void) const;
	void cmdInventory(void) const;
	void cmdHelp(void) const;

	// ACTION COMMANDS ERROR HANDLERS
	int handleCmdDropErrors(std::string target, Entity* eTarget) const;
	int handleCmdTakeErrors(std::string target, Entity* eTarget) const;
	int handleCmdTakeFromContainerErrors(std::string target, Entity* eTarget, std::string container, Entity* eContainer) const;
	int handleCmdPutErrors(std::string target, Entity* eTarget, std::string container, Entity* eContainer) const;
	int handleCmdWalkErrors(Exit* exit) const;
	int handleAttack(Entity* target, Entity* eWeapon, std::string weapon) const;

	// ACTION COMMANDS
	int cmdDrop(std::string target);
	int cmdTake(std::string target);
	int cmdTakeFromContainer(std::string target, std::string container);
	int cmdPut(std::string target, std::string item);
	int cmdWalk(std::string target);
	int cmdAttack(std::string target, std::string weapon);

	// MOVEMENT FUNCTIONS
	int moveToRoom(Entity* room);


	bool isRunning(void) const { return !quit; };

	int getInput(void);
	int splitCommands(std::string input);
	int parseCommands(void);
	int handleCommand(std::string command);

	int handleAction(std::string action, std::string target, std::string conjunction, std::string item);
	Entity* getTarget(std::string target) const;

	void ennemyAttack(void);

	void addEntity(Entity* entity) { entities.push_back(entity); };

private:
	bool quit = false;
	std::vector<std::string> commands;
	std::vector<Entity*> entities;
	Room* currentRoom = nullptr;
};

