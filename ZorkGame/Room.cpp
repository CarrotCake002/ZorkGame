#include "Room.h"

Room::Room(std::string name, std::string description) : Entity(name, description, EntityType::Room) {

}

Exit* Room::getExit(Direction dir) const {
	Exit* exit = nullptr;

	for (auto& entity : contains) {
		if (entity->getType() == EntityType::Exit) {
			exit = static_cast<Exit*>(entity);
			if (exit->getDirection() == dir) {
				return exit;
			}
		}
	}
	return nullptr;
}