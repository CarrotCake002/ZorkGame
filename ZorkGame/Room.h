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

class Room : public Entity
{
public:
	Room() = default;
	Room(std::string name, std::string description);
	~Room() = default;

private:
};

struct Exit {
	Direction dir;
	Room* source;
	Room* destination;
};
