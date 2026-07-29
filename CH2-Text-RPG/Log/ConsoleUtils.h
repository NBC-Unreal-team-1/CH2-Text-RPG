#pragma once

#include <string>

void MoveCursor(int X, int Y);
std::string ClearLine();
void ClearConsole();
void FlushInput();
std::string ClearToEndOfLine(int X);