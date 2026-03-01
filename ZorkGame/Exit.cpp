#include "Exit.h"
#include "Room.h"

Exit::Exit(std::string name, Direction dir, Room* source, Room* destination)
	: Entity(name, "an exit to another room", EntityType::EXIT), direction(dir), source(source), destination(destination) {

}

void Exit::display() {
	slowPrint(" - An exit to the " + getStrDirection() + " which leads to " + destination->getName() + ".\n");
	std::cout << std::endl;
}

std::string Exit::getStrDirection() const {
	switch (direction) {
	case Direction::NORTH:
		return "North";
	case Direction::SOUTH:
		return "South";
	case Direction::EAST:
		return "East";
	case Direction::WEST:
		return "West";
	case Direction::UP:
		return "Up";
	case Direction::DOWN:
		return "Down";
	default:
		return "";
	}
}

Direction Exit::strToDirection(std::string str) {
	str = toLower(str);
	if (str == "north") {
		return Direction::NORTH;
	}
	else if (str == "south") {
		return Direction::SOUTH;
	}
	else if (str == "east") {
		return Direction::EAST;
	}
	else if (str == "west") {
		return Direction::WEST;
	}
	else if (str == "up") {
		return Direction::UP;
	}
	else if (str == "down") {
		return Direction::DOWN;
	}
	else {
		return Direction::NONE;
	}
}