#pragma once

#include <string>
#include <map>
#include <vector>
#include <utility>
#include "Item.h"

class FInventory
{
public:
    void AddItem(std::string ItemId, int Quantity);
    bool HasItem(std::string ItemId, int Quantity) const;
    void RemoveItem(std::string ItemId, int Quantity);

    std::vector<std::pair<FItem, int>> ToDisplayList(const std::map<std::string, FItem>& ItemDb) const;

private:
    std::map<std::string, int> Items;
};