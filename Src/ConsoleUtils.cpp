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
