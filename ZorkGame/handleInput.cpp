#include "handleInput.h"

int parseInput(std::string input) {
    // parsing here
    return 0;
}

int getInput(void) {
    std::string input;

    std::cout << " > ";
    std::getline(std::cin, input);
    if (input == "exit")
        return 1;
    if (parseInput(input) == 1)
        return 0;
    return 0;
}