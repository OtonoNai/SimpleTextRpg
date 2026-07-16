#include "Player.h"

std::map<std::string, std::string> FPlayer::GetAllStatus()
{
    return Status;
}

std::string FPlayer::GetStatusFromKey(std::string Key)
{
    return Status[Key];
}

void FPlayer::SetStatus(std::string Key, std::string Value)
{
    Status[Key] = Value;
}

bool FPlayer::GetIsValidStatus()
{
    return bIsValidStatus;
}

void FPlayer::SetIsValidStatus(bool bInValue)
{
    bIsValidStatus = bInValue;
}
