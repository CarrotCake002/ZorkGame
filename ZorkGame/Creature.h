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
	void printContains(void) const;

	std::string getName(void) const override { return name; };
	int getHealth(void) const { return health; };
	int getAttackPower(void) const { return attackPower; };
	Weapon* getWeapon(void) const;
	bool isAlive(void) const { return health > 0; };
	bool isAggro(void) const { return aggro; };

	void setAggro(bool aggro);

	
	void takeDamage(int damage);
	int calcAttackPower(Weapon* weapon) const;
	int attack(Creature* defender, Weapon* weapon) const;
	bool dropItem(Room* currentRoom, Entity *item);
	void die(Room* currentRoom);


protected:
	int health;
	int attackPower;
	int armor;
	double critChance = 0.05;
	bool aggro = false;
};

using Player = Creature;