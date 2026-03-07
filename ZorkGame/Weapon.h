#pragma once

#include "Entity.h"

class Weapon : public Entity
{
public:
	Weapon() = default;
	Weapon(std::string name, std::string description, int damage, double critChance = 0.05f);
	~Weapon() = default;

	void display(void) const override;

	int getDamage(void) const { return damage; };
	double getCritChance(void) const { return critChance; };

private:
	int damage;
	double critChance;
};

