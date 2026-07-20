#include "TextDataLoader.h"
#include "CSVReader.h"
#include <format>

std::vector<std::array<std::string, FTextData::NumOfRow>> ReadCSV(std::string FileName, std::vector<std::array<std::string, FTextData::NumOfRow>> List)
{
    CSVReader Reader;
    Reader.ReadFile(std::format("./Data/{}.csv", FileName));
    std::array<std::string, FTextData::NumOfRow> Temp;

    for (int i = 0; i < Reader.GetRowCount(); ++i)
    {
        auto& Row = Reader.GetRow(i);
        for (int j = 0; j < Row.size(); ++j)
        {
            Temp[j] = Row[j];
        }
        List.push_back(Temp);
    }

    return List;
}

std::string GetBorder()
{
    std::string Temp;
    for (int i = 0; i < FTextData::BorderLength; ++i)
    {
        Temp += FTextData::BorderText;
    }
    return Temp;
}

std::string GetEmpty()
{
    return " ";
}

FSeparatedData SeparateText(std::vector<std::array<std::string, FTextData::NumOfRow>> List)
{
    std::vector<FTextDataView> View;
    std::vector<FTextDataIn> Inputs;
    std::vector<FTextDataUpdate> Updates;
    std::vector<FTextDataInteract> Interacts;
    int ConsoleLine = -1;

    for (int i = 0; i < List.size(); ++i)
    {
        FTextDataView TempView;
        if (List[i][EDataRow::RawText] == "border")
        {
            TempView.Data = GetBorder();
            View.push_back(TempView);
            continue;
        }
        else if (List[i][EDataRow::RawText] == "empty")
        {
            TempView.Data = GetEmpty();
            View.push_back(TempView);
            continue;
        }
        else
        {
            int ScreenLine = static_cast<int>(View.size());

            if (List[i][EDataRow::IoType] == "console")
            {
                ConsoleLine = ScreenLine;
            }

            if (List[i][EDataRow::IoType] == "in")
            {
                FTextDataIn TempInput;

                TempInput.Column = ScreenLine;
                TempInput.VarName = List[i][EDataRow::VarNames];
                TempInput.VarType = List[i][EDataRow::VarType];
                TempInput.VarRange = List[i][EDataRow::VarRange];

                Inputs.push_back(TempInput);
            }
            else if (List[i][EDataRow::IoType] == "update")
            {
                FTextDataUpdate TempUpdate;

                TempUpdate.Line = stoi(List[i][EDataRow::Line]);

                Updates.push_back(TempUpdate);
            }
            else if (List[i][EDataRow::IoType] == "interact")
            {
                FTextDataInteract TempInteracts;

                TempInteracts.Index = stoi(List[i][EDataRow::Line]);
                TempInteracts.Text = List[i][EDataRow::RawText];
                TempInteracts.Trigger = stoi(List[i][EDataRow::Trigger]);
                TempInteracts.RequiredItem = List[i][EDataRow::RequiredItem];
                TempInteracts.RequireQty = List[i][EDataRow::RequiredQty].empty() ? 0 : stoi(List[i][EDataRow::RequiredQty]);
                TempInteracts.ResultType = List[i][EDataRow::ResultType];

                Interacts.push_back(TempInteracts);
                continue;
            }

            TempView.Data = List[i][EDataRow::RawText];
        }

        View.push_back(TempView);
    }

    FSeparatedData Result{
        View,
        Inputs,
        Updates,
        Interacts,
        ConsoleLine,
    };

    return Result;
}

void LoadTextData(FTextData& Data, int Phase)
{
    Data.SetDataOrigin(ReadCSV(std::format("TextData{}", Phase), Data.GetDataOrigin()));
}

void BuildData(FTextData& Data)
{
    FSeparatedData Temp = SeparateText(Data.GetDataOrigin());

    Data.View = Temp.View;
    Data.In = Temp.Inputs;
    Data.Update = Temp.Updates;
    Data.Interacts = Temp.Interacts;
    Data.ConsoleLine = Temp.ConsoleLine;
}
