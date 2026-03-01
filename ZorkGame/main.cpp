#include <windows.h>
#include "World.h"

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int status = true;
    World world;

    while (world.isRunning()) {
        if (world.getInput() == 1) {
            break;
        }
    }
    return 0;
}