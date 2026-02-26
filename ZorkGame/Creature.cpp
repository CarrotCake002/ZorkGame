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

void Creature::update() {
	std::cout << "Creature " << name << " updated." << std::endl;
	std::cout << "This creature is described as " << description << std::endl;
	printContains();
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
