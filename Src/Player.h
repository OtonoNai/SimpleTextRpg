#pragma once

#include <map>
#include <string>

class FPlayer
{
public:
    FPlayer();
    FPlayer(std::string InName, int InHp, int InMp, int InAtk, int InDef);

    std::map<std::string, std::string> GetAllStatus();
    std::string GetStatusFromKey(std::string Key);
    void SetStatus(std::string Key, std::string Value);
    void ModifyStat(std::string StatName, std::string Operation, int Value);

    bool GetIsValidStatus();
    void SetIsValidStatus(bool bInValue);

    int GetHp() const;
    int GetMp() const;
    int GetAtk() const;
    int GetDef() const;

private:
    std::string Name;
    int Hp;
    int Mp;
    int Atk;
    int Def;
    bool bIsValidStatus = false;
};
