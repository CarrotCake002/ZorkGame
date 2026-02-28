 #pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>

void slowPrint(const std::string& text, int delayMs = 10);

std::string toLower(std::string str);