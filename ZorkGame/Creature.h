#pragma once

#include "Entity.h"

class Creature : public Entity
{
public:
	Creature(std::string name, std::string description, int health, int attackPower, EntityType type = EntityType::Creature);
	~Creature();

	void update(void) override;

	std::string getName() const override { return name; };
	int GetHealth() const { return health; };
	int GetAttackPower() const { return attackPower; };

	void takeItem(Entity* item);

	void takeDamage(int damage);
	bool isAlive() const;

protected:
	int health;
	int attackPower;
};

using Player = Creature;