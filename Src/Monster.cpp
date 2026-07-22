#include "Monster.h"

FMonster::FMonster(std::string InMonsterId, std::string InDisplayName, int InHp, int InAtk, int InDef, std::string InDropItemId, int InExpReward)
    : MonsterId(InMonsterId), DisplayName(InDisplayName), Hp(InHp), Atk(InAtk), Def(InDef), DropItemId(InDropItemId), ExpReward(InExpReward)
{
}

void FMonster::TakeDamage(int Amount)
{
    Hp -= Amount;

    if (Hp < 0)
    {
        Hp = 0;
    }
}

bool FMonster::IsAlive() const
{
    return Hp > 0;
}

const std::string& FMonster::GetMonsterId() const
{
    return MonsterId;
}

const std::string& FMonster::GetDisplayName() const
{
    return DisplayName;
}

int FMonster::GetHp() const
{
    return Hp;
}

int FMonster::GetAtk() const
{
    return Atk;
}

int FMonster::GetDef() const
{
    return Def;
}

const std::string& FMonster::GetDropItemId() const
{
    return DropItemId;
}

int FMonster::GetExpReward() const
{
    return ExpReward;
}
