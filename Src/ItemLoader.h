#pragma once

#include <string>
#include <map>
#include "Item.h"
#include "Inventory.h"
#include "TextDataTypes.h"

std::map<std::string, FItem> LoadItems(const std::string& FilePath);
void LoadStartingInventory(FInventory& Inventory, const std::string& FilePath);
void ValidateItemReferences(const FTextData& Data, const std::map<std::string, FItem>& Items);