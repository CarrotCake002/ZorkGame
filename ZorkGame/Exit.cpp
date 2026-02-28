#include "Exit.h"

Exit::Exit(std::string name, Direction dir, Room* source, Room* destination)
	: Entity(name, "an exit to another room", EntityType::Exit), direction(dir), source(source), destination(destination) {

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