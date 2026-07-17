#include "Item.h"
#include "Player.h"

FItem::FItem(std::string InItemId, std::string InDisplayName, std::string InItemType, std::string InOperation, std::string InTargetStat, int InValue, int InPrice)
	: ItemId(InItemId), DisplayName(InDisplayName), ItemType(InItemType), Operation(InOperation), TargetStat(InTargetStat), Value(InValue), Price(InPrice)
{}

void FItem::ApplyTo(FPlayer& Player) const
{
	Player.ModifyStat(TargetStat, Operation, Value);
}

const std::string& FItem::GetItemId() const
{
	return ItemId;
}

const std::string& FItem::GetDisplayName() const
{
	return DisplayName;
}

const std::string& FItem::GetItemType() const
{
	return ItemType;
}

int FItem::GetPrice() const
{
	return Price;
}