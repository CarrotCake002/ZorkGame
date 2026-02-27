#include "Utils.h"

void slowPrint(const std::string& text, int delayMs)
{
    for (char c : text)
    {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << std::flush;
}