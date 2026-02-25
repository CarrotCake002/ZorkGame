#include "Game.h"
#include "World.h"

int main() {
    int status = true;
    World world;

	world.addEntity(new Entity());

    while (status) {
        if (getInput() == 1) {
            break;
        }
		world.update();
    }
    return 0;
}