#include "Creature.h"

Creature::Creature(std::string name, std::string description, int health, int attackPower, EntityType type)
		: health(health), attackPower(attackPower) {
	this->name = name;
	this->description = description;
	this->type = type;
	this->armor = 0;
}

void Creature::printContains() const {
	slowPrint("\t");
	for (auto& elem : contains) {
		slowPrint(elem->getName() + "\t");
	}
}

void Creature::display() {
	if (type == EntityType::PLAYER)
		return;
	slowPrint(" - A creature that goes by the mighty name of " + name + ".\nIt is described as " + description + ".\n");
	if (contains.size() > 0) {
		slowPrint("It also has in its inventory:\n");
		printContains();
		std::cout << "\n";
	}
	std::cout << std::endl;
}

bool Creature::isAlive() const {
	return health > 0;
}

void Creature::takeDamage(int damage) {
	int totalDamage = damage - armor;

	if (totalDamage < 0) {
		printDialogue("The " + name + "'s armor is too sturdy and absorbs all the damage.\n");
		return;
	}
	health -= totalDamage;
	if (health < 0)
		health = 0;
	printDialogue(name + " takes " + std::to_string(totalDamage) + " damage and has " + std::to_string(health) + " health remaining.\n");
}

int Creature::calcAttackPower(Weapon *weapon) const {
	int totalAttackPower = attackPower;
	double totalCritChance = critChance;

	if (weapon != nullptr) {
		totalAttackPower += weapon->getDamage();
		totalCritChance += weapon->getCritChance();
	}
	if (rollCrit(totalCritChance)) {
		totalAttackPower *= 2;
		printDialogue("Critical hit! Your attack power is doubled to " + std::to_string(totalAttackPower) + "!\n");
	}
	else {
		printDialogue("You attack for a total of " + std::to_string(totalAttackPower) + " damage.\n");
	}
	return totalAttackPower;
}

int Creature::attack(Creature* defender, Weapon* weapon) {
	int damage = calcAttackPower(weapon);

	defender->takeDamage(damage);
	return damage;
}

bool Creature::dropItem(Room* currentRoom, Entity* item) {
	for (auto it = contains.begin(); it != contains.end(); ++it) {
		if (*it == item) {
			currentRoom->addItem(item);
			contains.erase(it);
			return true;
		}
	}
	return false;
}

void Creature::die(Room* currentRoom) {
	for (auto it = contains.begin(); it != contains.end();) {
		currentRoom->addItem(*it);
		it = contains.erase(it);
	}
	currentRoom->removeItem(name);
	printDialogue("The " + getName() + " has been defeated and dropped its items on the ground.\n");
}