#include <windows.h>
#include "World.h"

std::string getInput() {
    std::string input = "";

    std::cout << TEXT_COLOR_CYAN << " > " << TEXT_COLOR_RESET;
    std::getline(std::cin, input);
    return input;
}

bool resetOrQuit(std::string input) {
    input = toLower(input);

    if (input == "reset") {
        return true;
    }
    else if (input == "quit") {
        return false;
    }
    else {
        printDialogue("Invalid input. Please enter 'reset' or 'quit'.\n");
        return resetOrQuit(getInput());
    }
}

int runGame() {
    World world;
	Player* player = static_cast<Player*>(world.getTarget("Player"));

    while (world.isRunning()) {
        if (world.getInput() == 1) {
            break;
        }
        if (world.isRunning() && !player->isAlive()) {
			return resetOrQuit(getInput());
        }
    }
    return 0;
}

int main() {
    bool reset = false;

    SetConsoleOutputCP(CP_UTF8);

    printDialogue(ZORK_ASCII, 0);
    printDialogue(INTRO, 0);
    std::cout << std::endl;
    do {
        reset = runGame();
    } while (reset);
}