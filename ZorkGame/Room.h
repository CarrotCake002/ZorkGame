#pragma once

#include "Entity.h"

#include <array>

enum class Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	UP,
	DOWN
};

class Exit;

class Room : public Entity
{
public:
	Room() = default;
	Room(std::string name, std::string description);
	~Room() = default;

	void addExit(Exit* exit) { exits.push_back(exit); };
private:
	std::vector<Exit*> exits;
};