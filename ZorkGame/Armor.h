#pragma once

#include "Entity.h"

enum class ArmorPart {
	HEAD,
	BODY,
	LEGS
};

class Armor : public Entity
{
public:
	Armor(std::string name, std::string description, int defense, ArmorPart type);
	~Armor() = default;

	void display(void) const;

	int getDefense(void) const { return defense; };
	ArmorPart getPart(void) const { return part; };

	void setDefense(int defense) { this->defense = defense; };

private:
	int defense;
	ArmorPart part;
};

