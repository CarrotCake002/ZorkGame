#include "Creature.h"
#include "Constants.h"

Creature::Creature(std::string name, std::string description, int health, int attackPower, bool useWeapons, EntityType type)
		: Entity(name, description, type), maxHealth(health), attackPower(attackPower), useWeapons(useWeapons) {
	this->health = maxHealth;
	this->armor = 0;
}

void Creature::printContains() const {
	slowPrint("\t");
	for (auto& elem : contains) {
		slowPrint(elem->getPrintableName() + "\t");
	}
}

std::string Creature::getPrintableName(void) const {
	if (this->type == EntityType::PLAYER)
		return TEXT_COLOR_GREEN + getName() + TEXT_COLOR_RESET;
	return TEXT_COLOR_RED + getName() + TEXT_COLOR_RESET;
}

void Creature::display() {
	if (type == EntityType::PLAYER)
		return;
	printDialogue(" - A dangerous " + getPrintableName() + ".\nIt is described as " + description + ".\n");
	std::cout << std::endl;
}

void Creature::displayStatus() {
	std::string text_color = getType() == EntityType::PLAYER ? TEXT_COLOR_GREEN : TEXT_COLOR_RED;

	printDialogue(" - " + text_color + getName() + TEXT_COLOR_RESET + " has " + TEXT_COLOR_GREEN + std::to_string(getHealth()) + TEXT_COLOR_RESET
		+ " of his " + TEXT_COLOR_GREEN + std::to_string(getMaxHealth()) + TEXT_COLOR_RESET + " maximum health.\n");
}

void Creature::takeDamage(int damage) {
	int totalDamage = damage - armor;

    if (totalDamage < 0) {
        printDialogue("The " + getPrintableName() + "'s armor is too sturdy and absorbs all the damage.\n");
        return;
    }
	health -= totalDamage;
	if (health < 0)
		health = 0;
    printDialogue(getPrintableName() + " takes " + TEXT_COLOR_RED + std::to_string(totalDamage) + TEXT_COLOR_RESET + " damage and has " + TEXT_COLOR_GREEN + std::to_string(health) + TEXT_COLOR_RESET + " health remaining.\n");
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

        printDialogue(getPrintableName() + " lands a " + TEXT_COLOR_RED + "critical hit!" + TEXT_COLOR_RESET + " His attack power is doubled to " + TEXT_COLOR_RED + std::to_string(totalAttackPower) + TEXT_COLOR_RESET + "!\n");
    }
    else {
        printDialogue(getPrintableName() + " attacks for a total of " + TEXT_COLOR_RED + std::to_string(totalAttackPower) + TEXT_COLOR_RESET + " damage.\n");
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
	printDialogue("The " + getPrintableName() + " has been defeated and dropped its items on the ground.\n");
}

void Creature::setAggro(bool aggro) {
	this->aggro = aggro;
	printDialogue("The " + getPrintableName() + " is now targetting you!");
}

Weapon* Creature::getWeapon() const {
	if (useWeapons) {
		for (auto& item : contains) {
			if (item->getType() == EntityType::WEAPON)
				return static_cast<Weapon*>(item);
		}
	}
	return nullptr;
}