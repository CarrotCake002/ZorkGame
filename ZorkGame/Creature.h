#pragma once

#include "Entity.h"
#include "Weapon.h"
#include "Room.h"
#include "Armor.h"

struct Equipment {
	Armor* head;
	Armor* body;
	Armor* legs;
	Weapon* hands;
};

class Creature : public Entity
{
public:
	Creature(std::string name, std::string description, int health, int attackPower, bool useWeapons = true, EntityType type = EntityType::CREATURE);
	~Creature() = default;

	void display(void) const override;
	void displayStatus(void) const;
	std::string getPrintableName(void) const override;

	std::string getName(void) const override { return name; };
	int getHealth(void) const { return health; };
	int getMaxHealth(void) const { return maxHealth; };
	int getAttackPower(void) const { return attackPower; };
	bool isAlive(void) const { return health > 0; };
	bool isAggro(void) const { return aggro; };
	Weapon* getWeapon(void) const;

	void setAggro(bool aggro);
	void setHealth(int health) { this->health = health; };
	void setMaxHealth(int maxHealth) { this->maxHealth = maxHealth; };

	
	void takeDamage(int damage);
	int calcDefensePower(void) const;
	int calcAttackPower(Weapon* weapon) const;
	int attack(Creature* defender, Weapon* weapon) const;
	bool dropItem(Room* currentRoom, Entity *item);
	void die(Room* currentRoom);

protected:
	int health;
	int maxHealth;
	int attackPower;
	int baseArmor = 0;
	double critChance = 0.05;
	bool aggro = false;
	bool useWeapons;
	Equipment eq;
};

using Player = Creature;