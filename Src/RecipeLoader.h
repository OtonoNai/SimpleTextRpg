#pragma once

#include <string>
#include <vector>

struct FRecipe
{
    std::string RecipeId;
    std::string ResultItemId;
    std::string Ingredient1Id;
    int Qty1;
    std::string Ingredient2Id;
    int Qty2;
    int InitialStock;
    int MaxStock;
};

std::vector<FRecipe> LoadRecipes(const std::string& FilePath);