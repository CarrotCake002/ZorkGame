#include "Armor.h"
#include "Constants.h"

Armor::Armor(std::string name, std::string description, int defense, ArmorPart part) : Entity(name, description, EntityType::ARMOR) {
	this->defense = defense;
	this->part = part;
}

void Armor::display() const {
	printDialogue("- " + TEXT_COLOR_BLUE + getName() + TEXT_COLOR_RESET + " which has " + TEXT_COLOR_BLUE + std::to_string(getDefense()) + TEXT_COLOR_RESET + " defense.\n");
}
