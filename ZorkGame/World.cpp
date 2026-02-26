#include "World.h"

World::~World() {
	for (auto entity : entities) {
		delete entity;
	}
}

void World::update(void) {
	for (auto entity : entities) {
		entity->update();
	}
}