#pragma once

#include <string>
#include <vector>
#include <array>

enum EDataRow
{
    Line,
    RawText,
    IoType,
    VarNames,
    NumOfVars,
    VarType,
    VarRange,
    InteractType,
    InteractCategory,
    InteractWith,
    Trigger,
    RequiredItem,
    RequiredQty,
    ResultType,
    End,
};

struct FTextDataView
{
    std::string Data;
};

struct FTextDataIn
{
    int Column;
    int VarX;
    std::string VarName;
    std::string VarType;
    std::string VarRange;
};

struct FTextDataUpdate
{
    int Line;
};

struct FTextDataInteract
{
    int Index;
    std::string Text;
    int Trigger;
    std::string RequiredItem;
    int RequiredQty;
    std::string ResultType;
};

struct FTextData
{
public:
    static constexpr int NumOfRow = EDataRow::End;

    static const char BorderText = '=';
    static const int BorderLength = 40;

    std::string LastInteractMessage;
    bool bAdvancePhase = true;
    int ConsoleLine = -1;

    std::vector<std::array<std::string, NumOfRow>>& GetDataOrigin()
    {
        return TextDataOrigin;
    }

    void SetDataOrigin(std::vector<std::array<std::string, NumOfRow>> InData)
    {
        TextDataOrigin = InData;
    }

    void SetHasSelect(bool bInValue)
    {
        bHasSelect = bInValue;
    }

    bool CheckHasSelect()
    {
        return bHasSelect;
    }

    std::vector<std::array<std::string, NumOfRow>> TextDataOrigin;
    std::vector<FTextDataView> View;
    std::vector<FTextDataIn> In;
    std::vector<FTextDataUpdate> Update;
    std::vector<FTextDataInteract> Interacts;

private:
    bool bHasSelect = false;
};

struct FSeparatedData
{
    std::vector<FTextDataView> View;
    std::vector<FTextDataIn> Inputs;
    std::vector<FTextDataUpdate> Updates;
    std::vector<FTextDataInteract> Interacts;
    int ConsoleLine = -1;
};
