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

void Creature::takeDamage(int damage) {
	int totalDamage = damage - armor;

	if (totalDamage < 0) {
		printDialogue("The " + name + "'s armor is too sturdy and absorbs all the damage.\n");
		return;
	}
	health -= totalDamage;
	if (health < 0)
		health = 0;
    // Make the damage message clear whether the player or a creature is taking damage
    if (type == EntityType::PLAYER) {
        printDialogue("You take " + std::to_string(totalDamage) + " damage and have " + std::to_string(health) + " health remaining.\n");
    }
    else {
        printDialogue(name + " takes " + std::to_string(totalDamage) + " damage and has " + std::to_string(health) + " health remaining.\n");
    }
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

        std::string attackerName = (type == EntityType::PLAYER) ? "You" : getName();
        std::string possessive = (type == EntityType::PLAYER) ? "Your" : attackerName + "'s";
        printDialogue(attackerName + " lands a critical hit! " + possessive + " attack power is doubled to " + std::to_string(totalAttackPower) + "!\n");
    }
    else {
        std::string attackerName = (type == EntityType::PLAYER) ? "You" : getName();
        printDialogue(attackerName + " attacks for a total of " + std::to_string(totalAttackPower) + " damage.\n");
    }
	return totalAttackPower;
}

int Creature::attack(Creature* defender, Weapon* weapon) const {
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

void Creature::setAggro(bool aggro) {
	this->aggro = aggro;
	printDialogue("The " + getName() + " is now targetting you!");
}

Weapon* Creature::getWeapon() const {
	for (auto& item : contains) {
		if (item->getType() == EntityType::WEAPON)
			return static_cast<Weapon*>(item);
	}
	return nullptr;
}