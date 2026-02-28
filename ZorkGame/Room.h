#pragma once

#include "Entity.h"
#include "Exit.h"

#include <array>

class Room : public Entity
{
public:
	Room() = default;
	Room(std::string name, std::string description);
	~Room() = default;

	void addExit(Exit* exit) { exits.push_back(exit); };
	Exit* getExit(Direction dir) const;

private:
	std::vector<Exit*> exits;
};