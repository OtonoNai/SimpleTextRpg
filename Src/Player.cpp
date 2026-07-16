#include "Player.h"

FPlayer::FPlayer()
    : Name(""), Hp(0), Mp(0), Atk(0), Def(0)
{
}

FPlayer::FPlayer(std::string InName, int InHp, int InMp, int InAtk, int InDef)
	: Name(InName), Hp(InHp), Mp(InMp), Atk(InAtk), Def(InDef)
{
}

std::map<std::string, std::string> FPlayer::GetAllStatus()
{
	std::map<std::string, std::string> Result;
	Result["name"] = Name;
	Result["hp"] = std::to_string(Hp);
	Result["mp"] = std::to_string(Mp);
	Result["atk"] = std::to_string(Atk);
	Result["def"] = std::to_string(Def);
	return Result;
}

std::string FPlayer::GetStatusFromKey(std::string Key)
{
    if (Key == "name")
    {
        return Name;
    }
    else if (Key == "hp")
    {
        return std::to_string(Hp);
    }
    else if (Key == "mp")
    {
        return std::to_string(Mp);
    }
    else if (Key == "atk")
    {
        return std::to_string(Atk);
    }
    else if (Key == "def")
    {
        return std::to_string(Def);
    }

    return "";
}

void FPlayer::SetStatus(std::string Key, std::string Value)
{
    if (Key == "name")
    {
        Name = Value;
    }
    else if (Key == "hp")
    {
        Hp = stoi(Value);
    }
    else if (Key == "mp")
    {
        Mp = stoi(Value);
    }
    else if (Key == "atk")
    {
        Atk = stoi(Value);
    }
    else if (Key == "def")
    {
        Def = stoi(Value);
    }
}

void FPlayer::ModifyStat(std::string StatName, std::string Operation, int Value)
{
    int* Target = nullptr;

    if (StatName == "hp")
    {
        Target = &Hp;
    }
    else if (StatName == "mp")
    {
        Target = &Mp;
    }
    else if (StatName == "atk")
    {
        Target = &Atk;
    }
    else if (StatName == "def")
    {
        Target = &Def;
    }

    if (Target == nullptr)
    {
        return;
    }

    if (Operation == "add")
    {
        *Target += Value;
    }
    else if (Operation == "multiply")
    {
        *Target *= Value;
    }
}

bool FPlayer::GetIsValidStatus()
{
	return bIsValidStatus;
}

void FPlayer::SetIsValidStatus(bool bInValue)
{
	bIsValidStatus = bInValue;
}

int FPlayer::GetHp() const
{
    return Hp;
}

int FPlayer::GetMp() const
{
    return Mp;
}

int FPlayer::GetAtk() const
{
    return Atk;
}

int FPlayer::GetDef() const
{
    return Def;
}
