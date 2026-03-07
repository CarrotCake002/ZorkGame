#pragma once

#include "Entity.h"
#include "Constants.h"

class Note : public Entity
{
public:
	Note(std::string name, std::string description) : Entity(name, description, EntityType::NOTE) {};
	~Note() {};

	void display(void) const override {
		printDialogue(" - A " + TEXT_COLOR_YELLOW + "Note" + TEXT_COLOR_RESET + " that says:\n" + description + "\n");
	}

};

