#include "Exit.h"
#include "Room.h"
#include "Constants.h"

Exit::Exit(std::string name, Direction dir, Room* source, Room* destination, bool open, int id)
	: Entity(name, "an exit to another room", EntityType::EXIT), direction(dir), source(source), destination(destination), open(open), id(id) {

}

void Exit::display() {
	slowPrint(" - An exit to the " + getPrintableDirection() + " which leads to " + TEXT_COLOR_CYAN + destination->getName() + TEXT_COLOR_RESET + ".\n");
	std::cout << std::endl;
}

std::string Exit::getPrintableDirection() const {
	return TEXT_COLOR_MAGENTA + getStrDirection() + TEXT_COLOR_RESET;
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

bool Exit::openDoor(std::list<Entity*> playerInventory) {
	Key* key = nullptr;

	for (auto& item : playerInventory) {
		if (item->getType() != EntityType::KEY)
			continue;
		key = static_cast<Key*>(item);
		if (key->getId() == id) {
			open = true;
			printDialogue("You open the door with " + TEXT_COLOR_MAGENTA + key->getDescription() + TEXT_COLOR_RESET + ".\n");
			return true;
		}
	}
	printDialogue("You don't have the key to open the door to the " + TEXT_COLOR_MAGENTA + getStrDirection() + TEXT_COLOR_RESET + ".\n");
	return false;
}