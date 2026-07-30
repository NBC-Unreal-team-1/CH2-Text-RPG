#pragma once

#include <string>

void MoveCursor(int X, int Y);
void ClearLine(int x, int y);
void ClearConsole();
void FlushInput();
std::string ClearToEndOfLine(int X);