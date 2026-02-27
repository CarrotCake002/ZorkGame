#include "Entity.h"

Entity::Entity(std::string name, std::string description) : name(name), description(description) {
	this->type = EntityType::None;
}

void Entity::printContains() const {
	slowPrint("\t");
	for (auto& elem : contains) {
		slowPrint(elem->getName() + "\t");
	}
}

void Entity::display() {
	slowPrint(" - A " + name + " which is described as " + description + ".\n");
	if (contains.size() > 0) {
		slowPrint("It also contains:\n");
		printContains();
		slowPrint("\n");
	}
	std::cout << std::endl;
}

void Entity::addItem(Entity* item) {
	contains.push_back(item);
}

Entity *Entity::removeItem(std::string target) {
	std::string itemName;
	Entity* item = nullptr;

	std::transform(target.begin(), target.end(), target.begin(), ::tolower);
	for (auto it = contains.begin(); it != contains.end(); ++it) {
		itemName = (*it)->getName();
		std::transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
		if (itemName == target) {
			item = *it;
			contains.erase(it);
			return item;
		}
	}
	return nullptr;
}
