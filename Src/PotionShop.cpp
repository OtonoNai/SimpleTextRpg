#include "PotionShop.h"
#include <iostream>

FPotionShop::FPotionShop(std::vector<FRecipe> InRecipes)
	: Recipes(InRecipes)
{
	for (const auto& Recipe : Recipes)
	{
		Stock[Recipe.RecipeId] = Recipe.InitialStock;
		MaxStockById[Recipe.RecipeId] = Recipe.MaxStock;
	}
}

std::vector<FRecipe> FPotionShop::SearchByName(std::string Name, const std::map<std::string, FItem>& Items) const
{
	std::vector<FRecipe> Result;

	for (const auto& Recipe : Recipes)
	{
		auto ItemIt = Items.find(Recipe.ResultItemId);

		if (ItemIt != Items.end() && ItemIt->second.GetDisplayName() == Name)
		{
			Result.push_back(Recipe);
		}
	}

	return Result;
}

std::vector<FRecipe> FPotionShop::SearchByIngredient(std::string IngredientId) const
{
	std::vector<FRecipe> Result;

	for (const auto& Recipe : Recipes)
	{
		if (Recipe.Ingredient1Id == IngredientId || Recipe.Ingredient2Id == IngredientId)
		{
			Result.push_back(Recipe);
		}
	}

	return Result;
}

void FPotionShop::ShowAll(const std::map<std::string, FItem>& Items) const
{
	for (const auto& Recipe : Recipes)
	{
		auto ItemIt = Items.find(Recipe.ResultItemId);
		std::string ResultName = (ItemIt != Items.end()) ? ItemIt->second.GetDisplayName() : Recipe.ResultItemId;
		std::cout << "-> " << ResultName << " (" << Recipe.Ingredient1Id << " x" << Recipe.Qty1
			<< ", " << Recipe.Ingredient2Id << " x" << Recipe.Qty2 << ")" << std::endl;
	}
}

bool FPotionShop::DispensePotion(std::string RecipeId)
{
	if (Stock[RecipeId] <= 0)
	{
		return false;
	}

	Stock[RecipeId] -= 1;
	return true;
}

bool FPotionShop::ReturnPotion(std::string RecipeId)
{
	if (Stock[RecipeId] >= MaxStockById[RecipeId])
	{
		return false;
	}

	Stock[RecipeId] += 1;
	return true;
}
