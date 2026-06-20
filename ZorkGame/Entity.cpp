#include "Entity.h"
#include "Constants.h"

Entity::Entity(std::string name, std::string description, EntityType type) : name(name), description(description), type(type) {

}

void Entity::printContains() const {
	for (auto& elem : contains) {
		slowPrint("\t");
		elem->display();
	}
}

void Entity::display() const {
	std::string text_color = (type == EntityType::CONTAINER) ? TEXT_COLOR_BRIGHT_YELLOW : TEXT_COLOR_YELLOW;

	slowPrint(" - " + text_color + name + TEXT_COLOR_RESET + " which is described as " + description + ".\n");
	if (contains.size() > 0) {
		slowPrint("It contains:\n");
		printContains();
	}
	else if (contains.size() == 0 && type == EntityType::CONTAINER) {
		slowPrint("It is empty.\n");
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

bool Entity::isItem(void) const {
	EntityType type = getType();

	if (type == EntityType::ITEM || type == EntityType::WEAPON || type == EntityType::ARMOR
		|| type == EntityType::CONTAINER || type == EntityType::NOTE || type == EntityType::KEY)
		return true;
	return false;
}

bool Entity::isCreature(void) const {
	EntityType type = getType();

	if (type == EntityType::CREATURE)
		return true;
	return false;
}

nlohmann::json Entity::toJson(void) const {
	nlohmann::json entityJson;

	entityJson["description"] = description;
	entityJson["type"] = static_cast<int>(type);
	if (contains.size() > 0) {
		for (auto& item : contains) {
			entityJson["items"][item->getName()] = item->toJson();
		}
	}
	return entityJson;
}