#pragma once

#include <string>
#include <vector>
#include <array>
#include "TextDataTypes.h"

std::vector<std::array<std::string, FTextData::NumOfRow>> ReadCSV(std::string FileName, std::vector<std::array<std::string, FTextData::NumOfRow>> List);
std::string GetBorder();
std::string GetEmpty();
FSeparatedData SeparateText(std::vector<std::array<std::string, FTextData::NumOfRow>> List);
void LoadTextData(FTextData& Data, int Phase);
void BuildData(FTextData& Data);
