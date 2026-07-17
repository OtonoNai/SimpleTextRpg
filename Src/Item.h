#pragma once

#include <string>

class FPlayer;

class FItem
{
public:
    FItem(std::string InItemId, std::string InDisplayName, std::string InItemType, std::string InOperation, std::string InTargetStat, int InValue, int InPrice);

    void ApplyTo(FPlayer& Fplayer) const;

    const std::string& GetItemId() const;
    const std::string& GetDisplayName() const;
    const std::string& GetItemType() const;
    int GetPrice() const;

private:
    std::string ItemId;
    std::string DisplayName;
    std::string ItemType;
    std::string Operation;
    std::string TargetStat;
    int Value;
    int Price;
};
