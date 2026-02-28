#pragma once

#include "Entity.h"
#include "Room.h"

class Exit : public Entity
{
public:
	Exit() = default;
	Exit(std::string name, Direction dir, Room* source, Room* destination);

	void display(void) override;

	Direction getDirection(void) const { return direction; };
	Room* getSource(void) const { return source; };
	Room* getDestination(void) const { return destination; };

	std::string getStrDirection(void) const;
private:
	Direction direction;
	Room* source;
	Room* destination;
};

