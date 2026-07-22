#pragma once

#include <string>
#include <map>
#include "Monster.h"

std::map<std::string, FMonster> LoadMonsters(const std::string& FilePath);