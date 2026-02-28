#include "Entity.h"

Entity::Entity(std::string name, std::string description, EntityType type) : name(name), description(description), type(type) {

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

bool Entity::hasItem(std::string name) const {
	name = toLower(name);
	for (auto& item : this->contains) {
		if (toLower(item->getName()) == name) {
			return true;
		}
	}
	return false;
}

Entity *Entity::removeItem(std::string target) {
	std::string itemName;
	Entity* item = nullptr;

	target = toLower(target);
	for (auto it = contains.begin(); it != contains.end(); ++it) {
		itemName = (*it)->getName();
		if (toLower(itemName) == target) {
			item = *it;
			contains.erase(it);
			return item;
		}
	}
	return nullptr;
}
