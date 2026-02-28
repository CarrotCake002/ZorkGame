#include "Utils.h"


// FUNCTIONS FOR STRING MANIPULATION
std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
    return str;
}


// FUNCTIONS FOR PRINTING
void slowPrint(const std::string& text, int delayMs)
{
    if (text.empty()) {
		if (delayMs > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
        return;
    }
    for (char c : text)
    {
        std::cout << c << std::flush;
		if (delayMs > 0)
            std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
    }
    std::cout << std::flush;
}

void printDialogue(const std::vector<TextSegment>& segments)
{
    for (const auto& segment : segments)
    {
        slowPrint(segment.text, segment.delayMs);
    }
    std::cout << std::endl;
}

void printDialogue(const std::string& text, int delayMs)
{
    slowPrint(text, delayMs);
    std::cout << std::endl;
}