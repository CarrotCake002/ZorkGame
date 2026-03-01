#pragma once

#include "Entity.h"

class Room;

enum class Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	UP,
	DOWN,
	NONE = -1
};

class Exit : public Entity
{
public:
	Exit() = default;
	Exit(std::string name, Direction dir, Room* source, Room* destination);
	~Exit() = default;

	void display(void) override;

	Direction getDirection(void) const { return direction; };
	Room* getSource(void) const { return source; };
	Room* getDestination(void) const { return destination; };

	std::string getStrDirection(void) const;

	static Direction strToDirection(std::string str);
private:
	Direction direction;
	Room* source;
	Room* destination;
};

