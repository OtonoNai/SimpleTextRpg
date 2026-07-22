#include "RecipeLoader.h"
#include "CSVReader.h"

std::vector<FRecipe> LoadRecipes(const std::string& FilePath)
{
	CSVReader Reader;
	Reader.ReadFile(FilePath);

	std::vector<FRecipe> Result;

	for (size_t i = 1; i < Reader.GetRowCount(); ++i)
	{
		const auto& Row = Reader.GetRow(i);

		FRecipe NewRecipe;
		NewRecipe.RecipeId = Row[0];
		NewRecipe.ResultItemId = Row[1];
		NewRecipe.Ingredient1Id = Row[2];
		NewRecipe.Qty1 = Row[3].empty() ? 0 : stoi(Row[3]);
		NewRecipe.Ingredient2Id = Row[4];
		NewRecipe.Qty2 = Row[5].empty() ? 0 : stoi(Row[5]);
		NewRecipe.InitialStock = Row[6].empty() ? 0 : stoi(Row[6]);
		NewRecipe.MaxStock = Row[7].empty() ? 0 : stoi(Row[7]);

		Result.push_back(NewRecipe);
	}

	return Result;
}