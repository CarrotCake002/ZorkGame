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
	nlohmann::json j = nlohmann::json();

	for (Entity* entity : contains) {
		if (entity->isItem()) {
			j["items"][entity->getName()] = entity->toJson();
		}
		else if (entity->isCreature()) {
			j["enemies"][entity->getName()] = entity->toJson();
		}
	}
	return j;
}