#include "World.h"

int main() {
    int status = true;
    World world;

    while (world.isRunning()) {
        if (world.getInput() == 1) {
            break;
        }
    }
    return 0;
}