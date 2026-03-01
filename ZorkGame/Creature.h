#pragma once

#include "Entity.h"
#include "Weapon.h"
#include "Room.h"

class Creature : public Entity
{
public:
	Creature(std::string name, std::string description, int health, int attackPower, EntityType type = EntityType::CREATURE);
	~Creature() = default;

	void display(void) override;
	void printContains() const;

	std::string getName() const override { return name; };
	int getHealth() const { return health; };
	int getAttackPower() const { return attackPower; };

	void takeDamage(int damage);
	bool isAlive() const;
	int calcAttackPower(Weapon* weapon) const;
	int attack(Creature* defender, Weapon* weapon);
	bool dropItem(Room* currentRoom, Entity *item);
	void die(Room* currentRoom);

protected:
	int health;
	int attackPower;
	int armor;
	double critChance = 0.05;
};

using Player = Creature;