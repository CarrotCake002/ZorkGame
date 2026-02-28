#include "Creature.h"

Creature::Creature(std::string name, std::string description, int health, int attackPower, EntityType type)
		: health(health), attackPower(attackPower) {
	this->name = name;
	this->description = description;
	this->type = type;
}

Creature::~Creature() {
	for (auto &elem : contains) {
		delete elem;
	}
}

void Creature::printContains() const {
	slowPrint("\t");
	for (auto& elem : contains) {
		slowPrint(elem->getName() + "\t");
	}
}

void Creature::display() {
	if (type == EntityType::Player)
		return;
	slowPrint(" - A creature that goes by the mighty name of " + name + ".\nIt is described as " + description + ".\n");
	if (contains.size() > 0) {
		slowPrint("It also has in its inventory:\n");
		printContains();
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void Creature::takeDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
	}
}

bool Creature::isAlive() const {
	return health > 0;
}
