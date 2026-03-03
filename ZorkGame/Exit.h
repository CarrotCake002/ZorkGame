#pragma once

#include "Entity.h"
#include "Key.h"

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
	Exit(std::string name, Direction dir, Room* source, Room* destination, bool open = true, int id = 0);
	~Exit() = default;

	void display(void) override;
	std::string getPrintableDirection(void) const;

	Direction getDirection(void) const { return direction; };
	Room* getSource(void) const { return source; };
	Room* getDestination(void) const { return destination; };
	bool isLocked(void) const { return !open; };

	std::string getStrDirection(void) const;
	static Direction strToDirection(std::string str);

	bool openDoor(std::list<Entity*> playerInventory);
private:
	Direction direction;
	Room* source;
	Room* destination;
	bool open;
	int id;
};

