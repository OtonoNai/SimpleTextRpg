#pragma once

#include <map>
#include <string>

class FPlayer
{
public:
    FPlayer(std::string InAttackMessage, int InHitCount, int InDamageDivisor, std::string InJobMessage, std::string InBonusStat, int InBonusValue);
    virtual ~FPlayer() {}

    virtual std::string Attack() const = 0;

    std::map<std::string, std::string> GetAllStatus();
    std::string GetStatusFromKey(std::string Key);
    void SetStatus(std::string Key, std::string Value);
    void ModifyStat(std::string StatName, std::string Operation, int Value);
    void ApplyJobBonus();

    void TakeDamage(int Amount);
    bool IsAlive() const;

    bool GetIsValidStatus();
    void SetIsValidStatus(bool bInValue);

    const std::string& GetName() const;
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
    std::string JobMessage;
    std::string BonusStat;
    int BonusValue;
};
