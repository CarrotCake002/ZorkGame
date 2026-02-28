 #pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

struct TextSegment
{
    std::string text;
    int delayMs = 10;      // typing speed for this segment
};

std::string toLower(std::string str);

void slowPrint(const std::string& text, int delayMs = 10);
void printDialogue(const std::vector<TextSegment>& segments);
void printDialogue(const std::string& text, int delayMs = 10);