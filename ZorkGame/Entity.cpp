#include "Entity.h"

Entity::Entity(std::string name, std::string description) : name(name), description(description) {
	this->type = EntityType::None;
}

void Entity::printContains() const {
	if (contains.size() > 0) {
		std::cout << "It also contains:\n\t";
		for (auto& elem : contains) {
			std::cout << elem->getName() << "\t";
		}
		std::cout << std::endl;
	}
}

void Entity::update() {
	std::cout << "Entity " << name << " updated." << "\n";
	std::cout << "Entity is described as " << description << "\n";
	printContains();
}

void Entity::addItem(Entity* item) {
	contains.push_back(item);
}
