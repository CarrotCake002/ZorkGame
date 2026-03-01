#include "Weapon.h"

Weapon::Weapon(std::string name, std::string description, int damage, double critChance) : Entity(name, description, EntityType::WEAPON), damage(damage), critChance(critChance) {

}
