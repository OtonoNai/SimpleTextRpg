#include "TextDataTypes.h"
#include "TextDataLoader.h"
#include "GameScreen.h"
#include "Player.h"
#include "Item.h"
#include "Inventory.h"
#include "ItemLoader.h"
#include "ConsoleUtils.h"
#include <Windows.h>

int main()
{
    FTextData TextData;
    FPlayer Player;
    FInventory Inventory;
    int Phase = 1;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::map<std::string, FItem> Items = LoadItems("./Data/Items.csv");
    LoadStartingInventory(Inventory, "./Data/StartingInventory.csv");

    while (true)
    {
        ClearConsole();
        LoadTextData(TextData, Phase);
        BuildData(TextData);
        TextData.bAdvancePhase = true;
        ValidateItemReferences(TextData, Items);
        InitRender(TextData);
        GetInput(TextData, Player, Inventory, Items, Phase);
        if (!TextData.LastInteractMessage.empty())
        {
            WaitLoading(TextData.LastInteractMessage, TextData);
        }
        else
        {
            WaitLoading("Update", TextData);
        }
        UpdateRender(TextData, Player);
        SetNext(TextData, Phase);
    }
}
