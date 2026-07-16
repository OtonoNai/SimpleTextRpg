#pragma once

#include <map>
#include <string>

class FPlayer
{
public:
    std::map<std::string, std::string> GetAllStatus();
    std::string GetStatusFromKey(std::string Key);
    void SetStatus(std::string Key, std::string Value);
    bool GetIsValidStatus();
    void SetIsValidStatus(bool bInValue);

private:
    std::map<std::string, std::string> Status;
    bool bIsValidStatus = false;
};
