#pragma once

#include <string>
#include <vector>
#include "TextDataTypes.h"
#include "Player.h"

void InitRender(FTextData& Data);
bool CheckInputIsValid(std::string Value, std::vector<int> Range, int X, int Y);
void GetInput(FTextData& Data, FPlayer& Player, int Phase);
void Interact(FTextData& Data, FPlayer& Player);
void UpdateRender(FTextData& Data, FPlayer& Player);
void WaitLoading(std::string Text, FTextData& Data);
bool CheckExit();
void SetNext(FTextData& Data, int& Phase);
