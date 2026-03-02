#include "Entity.h"
#include "Constants.h"

Entity::Entity(std::string name, std::string description, EntityType type) : name(name), description(description), type(type) {

}

void Entity::printContains() const {
	slowPrint("\t");
	for (auto& elem : contains) {
		slowPrint(elem->getPrintableName() + "\t");
	}
}

void Entity::display() {
	std::string text_color = (type == EntityType::CONTAINER) ? TEXT_COLOR_BRIGHT_YELLOW : TEXT_COLOR_YELLOW;

	slowPrint(" - A " + text_color + name + TEXT_COLOR_RESET + " which is described as " + description + ".\n");
	if (contains.size() > 0) {
		slowPrint("It also contains:\n");
		printContains();
		slowPrint("\n");
	}
	std::cout << std::endl;
}

std::string Entity::getPrintableName(void) const {
	return TEXT_COLOR_YELLOW + getName() + TEXT_COLOR_RESET;
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

Entity* Entity::getItem(std::string target) const {
	std::string itemName;
	target = toLower(target);
	for (auto& item : this->contains) {
		itemName = toLower(item->getName());
		if (itemName == target) {
			return item;
		}
	}
	return nullptr;
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
