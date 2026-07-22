#pragma once

#include <string>
#include <vector>
#include <map>
#include "RecipeLoader.h"
#include "Item.h"

class FPotionShop
{
public:
	FPotionShop(std::vector<FRecipe> InRecipes);

	std::vector<FRecipe> SearchByName(std::string Name, const std::map<std::string, FItem>& Items) const;
	std::vector<FRecipe> SearchByIngredient(std::string IngredientId) const;
	void ShowAll(const std::map<std::string, FItem>& Items) const;

	bool DispensePotion(std::string RecipeId);
	bool ReturnPotion(std::string RecipeId);

private:
	std::vector<FRecipe> Recipes;
	std::map<std::string, int> Stock;
	std::map<std::string, int> MaxStockById;
};