#include "ConsoleUtils.h"
#include <Windows.h>
#include <cstdlib>

void MoveCursor(int X, int Y)
{
    COORD Pos = { X, Y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        Pos
    );
}

std::string ClearLine()
{
    std::string Temp;
    for (int i = 0; i < 80; ++i)
    {
        Temp += ' ';
    }
    return Temp;
}

void ClearConsole()
{
    system("cls");
    MoveCursor(0, 0);
}

void FlushInput()
{
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

std::string ClearToEndOfLine(int X)
{
    CONSOLE_SCREEN_BUFFER_INFO Csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Csbi);
    int Width = Csbi.dwSize.X;
    int Count = Width - X;

    if (Count < 0)
    {
        Count = 0;
    }

    std::string Temp;
    for (int i = 0; i < Count; ++i)
    {
        Temp += ' ';
    }
    return Temp;
}