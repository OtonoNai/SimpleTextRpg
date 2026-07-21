#pragma once

#include <map>
#include <string>

class FPlayer
{
public:
    FPlayer(std::string InAttackMessage, int InHitCount, int InDamageDivisor);
    virtual ~FPlayer() {}

    virtual std::string Attack() const = 0;

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
    int GetHitCount() const;
    int GetDamageDivisor() const;

protected:
    std::string AttackMessage;

private:
    std::string Name;
    int Hp;
    int Mp;
    int Atk;
    int Def;
    bool bIsValidStatus = false;
    int HitCount;
    int DamageDivisor;
};
