#pragma once

#include "World.h"

class System {
public:
	static std::string getSaveFilePath(void);
	static void saveGame(World* world);
};