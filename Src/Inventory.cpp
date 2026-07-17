#include "Inventory.h"

void FInventory::AddItem(std::string ItemId, int Quantity)
{
	Items[ItemId] += Quantity;
}

bool FInventory::HasItem(std::string ItemId, int Quantity) const
{
	auto It = Items.find(ItemId);

	if (It == Items.end())
	{
		return false;
	}

	return It->second >= Quantity;
}

void FInventory::RemoveItem(std::string ItemId, int Quantity)
{
	auto It = Items.find(ItemId);

	if (It == Items.end())
	{
		return;
	}

	It->second -= Quantity;

	if (It->second <= 0)
	{
		Items.erase(It);
	}
}

std::vector<std::pair<FItem, int>> FInventory::ToDisplayList(const std::map<std::string, FItem>& ItemDb) const
{
	std::vector<std::pair<FItem, int>> Result;

	for (const auto& Entry : Items)
	{
		auto It = ItemDb.find(Entry.first);

		if (It == ItemDb.end())
		{
			continue;
		}

		Result.push_back({ It->second, Entry.second });
	}

	return Result;
}