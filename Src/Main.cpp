#include "TextDataTypes.h"
#include "TextDataLoader.h"
#include "GameScreen.h"
#include "Player.h"
#include "ConsoleUtils.h"
#include <Windows.h>

int main()
{
    FTextData TextData;
    FPlayer Player;
    int Phase = 1;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    while (true)
    {
        ClearConsole();
        LoadTextData(TextData, Phase);
        BuildData(TextData);
        InitRender(TextData);
        GetInput(TextData, Player, Phase);
        WaitLoading("Update", TextData);
        UpdateRender(TextData, Player);
        SetNext(TextData, Phase);
    }
}
