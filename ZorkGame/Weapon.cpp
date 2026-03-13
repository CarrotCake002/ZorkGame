#include "Weapon.h"
#include "Constants.h"

Weapon::Weapon(std::string name, std::string description, int damage, double critChance) : Entity(name, description, EntityType::WEAPON), damage(damage), critChance(critChance) {

}

void Weapon::display() const {
	printDialogue(" - " + TEXT_COLOR_RED + getName() + TEXT_COLOR_RESET + " described as " + getDescription() + ".\n");
}