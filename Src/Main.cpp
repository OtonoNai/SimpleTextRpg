#include "TextDataTypes.h"
#include "TextDataLoader.h"
#include "GameScreen.h"
#include "Player.h"
#include "Item.h"
#include "Inventory.h"
#include "ItemLoader.h"
#include "JobTypes.h"
#include "JobLoader.h"
#include "ConsoleUtils.h"
#include "Monster.h"
#include "MonsterLoader.h"
#include "Battle.h"
#include "RecipeLoader.h"
#include "PotionShop.h"
#include <Windows.h>
#include <iostream>

int main()
{
    FTextData TextData;
    FPlayer* Player = nullptr;
    FInventory Inventory;
    int Phase = 1;

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::map<std::string, FItem> Items = LoadItems("./Data/Items.csv");
    std::map<std::string, FJobData> Jobs = LoadJobs("./Data/Jobs.csv");
    LoadStartingInventory(Inventory, "./Data/StartingInventory.csv");

    while (true)
    {
        ClearConsole();
        LoadTextData(TextData, Phase);
        BuildData(TextData);
        TextData.bAdvancePhase = true;
        ValidateItemReferences(TextData, Items);
        InitRender(TextData);
        
        if (Phase == 1)
        {
            Player = HandleJobSelection(TextData, Jobs);
        }
        else
        {
            GetInput(TextData, *Player, Inventory, Items, Phase);
        }

        if (!TextData.LastInteractMessage.empty())
        {
            WaitLoading(TextData.LastInteractMessage, TextData);
        }
        else
        {
            WaitLoading("Update", TextData);
        }

        UpdateRender(TextData, *Player);
        SetNext(TextData, Phase);

        if (Phase == 4)
        {
            ClearConsole();
            std::map<std::string, FMonster> Monsters = LoadMonsters("./Data/Monsters.csv");
            FMonster Slime = Monsters.at("slime");

            if (RunBattle(*Player, Slime) == EBattleResult::Victory)
            {
                if (Slime.GetDropItemId() != "none")
                {
                    Inventory.AddItem(Slime.GetDropItemId(), 1);
                }
            }

            std::vector<FRecipe> Recipes = LoadRecipes("./Data/Recipes.csv");
            FPotionShop Shop(Recipes);

            std::cout << std::endl << "[테스트] 전체 레시피:" << std::endl;
            Shop.ShowAll(Items);

            std::cout << std::endl << "[테스트] herb 재료로 검색:" << std::endl;
            for (const auto& R : Shop.SearchByIngredient("herb"))
            {
                std::cout << "-> " << R.RecipeId << std::endl;
            }

            std::cin.get();
            break;
        }

        if (TextData.bAdvancePhase && CheckExit())
        {
            break;
        }
    }

    delete Player;
    
    return 0;
}
