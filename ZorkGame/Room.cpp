#include "Room.h"

Room::Room(std::string name, std::string description) : Entity(name, description, EntityType::ROOM) {

}

Exit* Room::getExit(Direction dir) const {
	Exit* exit = nullptr;

	for (auto& entity : contains) {
		if (entity->getType() == EntityType::EXIT) {
			exit = static_cast<Exit*>(entity);
			if (exit->getDirection() == dir) {
				return exit;
			}
		}
	}
	return nullptr;
}

nlohmann::json Room::toJson(void) const {
	nlohmann::json j = Entity::toJson();

	for (auto& entity : contains) {
		if (entity->getType() != EntityType::CREATURE && entity->getType() != EntityType::EXIT && entity->getType() != EntityType::PLAYER && entity->getType() != EntityType::NONE) {
			j["items"][entity->getName()] = entity->toJson();
		}
	}

	for (auto& entity : contains) {
		if (entity->getType() == EntityType::CREATURE) {
			j["enemies"][entity->getName()] = entity->toJson();
		}
	}
	return j;
}