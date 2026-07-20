#include "ItemLoader.h"
#include "CSVReader.h"
#include <iostream>
#include <cstdlib>

std::map<std::string, FItem> LoadItems(const std::string& FilePath) {
	CSVReader Reader;
	Reader.ReadFile(FilePath);

	std::map<std::string, FItem> Result;

	for (size_t i = 1; i < Reader.GetRowCount(); ++i)
	{
		const auto& Row = Reader.GetRow(i);

		std::string ItemId = Row[0];
		std::string DisplayName = Row[1];
		std::string ItemType = Row[2];
		std::string Operation = Row[3];
		std::string TargetStat = Row[4];
		int Value = Row[5].empty() ? 0 : stoi(Row[5]);
		int Price = Row[6].empty() ? 0 : stoi(Row[6]);

		FItem NewItem(ItemId, DisplayName, ItemType, Operation, TargetStat, Value, Price);
		Result.emplace(ItemId, NewItem);
	}

	return Result;
}

void LoadStartingInventory(FInventory& Inventory, const std::string& FilePath)
{
	CSVReader Reader;
	Reader.ReadFile(FilePath);

	for (size_t i = 1; i < Reader.GetRowCount(); ++i)
	{
		const auto& Row = Reader.GetRow(i);

		std::string ItemId = Row[0];
		int Quantity = Row[1].empty() ? 0 : stoi(Row[1]);

		Inventory.AddItem(ItemId, Quantity);
	}
}

void ValidateItemReferences(const FTextData& Data, const std::map<std::string, FItem>& Items)
{
	for (const auto& Interact : Data.Interacts)
	{
		if (Interact.RequiredItem.empty())
		{
			continue;
		}

		if (Items.find(Interact.RequiredItem) == Items.end())
		{
			std::cout << "잘못된 아이템 참조: \"" << Interact.RequiredItem << "\" (Text: " << Interact.Text << ")" << std::endl;
			exit(1);
		}
	}
}