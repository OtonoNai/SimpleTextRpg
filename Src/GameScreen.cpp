#include "GameScreen.h"
#include "ConsoleUtils.h"
#include <Windows.h>
#include <sstream>
#include <iostream>
#include <cstdlib>

void InitRender(FTextData& Data)
{
    std::vector<FTextDataView> Temp = Data.View;
    for (int i = 1; i < Temp.size(); ++i)
    {
        std::cout << Temp[i].Data;

        for (auto& Input : Data.In)
        {
            if (Input.Column == i)
            {
                CONSOLE_SCREEN_BUFFER_INFO Csbi;
                GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Csbi);
                Input.VarX = Csbi.dwCursorPosition.X;
                break;
            }
        }
        std::cout << std::endl;
    }
}

bool CheckInputIsValid(std::string Value, std::vector<int> Range, int X, int Y)
{
    int ValueInt = stoi(Value);

    if (ValueInt >= Range[0] && ValueInt <= Range[1])
    {
        return true;
    }
    else
    {
        MoveCursor(X + 1, Y - 1);
        std::cout << "범위를 벗어났습니다. " << Range[0] << "부터 " << Range[1] << " 사이의 값을 입력해주세요.";
        Sleep(1000);
        MoveCursor(X + 1, Y - 1);
        std::cout << ClearLine();
        return false;
    }
}

void GetInput(FTextData& Data, FPlayer& Player, int Phase)
{
    std::vector<FTextDataView> TempView = Data.View;
    std::vector<FTextDataIn> TempIn = Data.In;
    std::string TempData;

    for (const auto& Input : TempIn)
    {
    RETRY_INPUT:
        std::stringstream Ss(Input.VarRange);
        std::string Token;
        std::string TempType;
        std::vector<int> TempRange;

        TempType = Input.VarType;

        int Y = Input.Column;
        int X = Input.VarX;

        MoveCursor(X + 1, Y - 1);

        std::string Value;
        std::getline(std::cin, Value);

        try
        {
            if (TempType == "int")
            {
                while (std::getline(Ss, Token, '-'))
                {
                    TempRange.push_back(stoi(Token));
                }

                if (!CheckInputIsValid(Value, TempRange, X, Y))
                {
                    goto RETRY_INPUT;
                }
            }
        }
        catch (const std::invalid_argument&)
        {
            MoveCursor(X + 1, Y - 1);
            std::cout << "숫자만 입력하세요.";
            Sleep(1000);
            MoveCursor(X + 1, Y - 1);
            std::cout << ClearLine();
            goto RETRY_INPUT;
        }

        if (Phase == 1)
        {
            Player.SetStatus(Input.VarName, Value);
        }
        else if (Phase == 2)
        {
        }
    }
}

void Interact(FTextData& Data, FPlayer& Player)
{
}

void UpdateRender(FTextData& Data, FPlayer& Player)
{
    std::vector<FTextDataView> TempView = Data.View;
    std::vector<FTextDataUpdate> TempUpdate = Data.Update;
    int FixYPos = 1;

    for (const auto& Args : TempUpdate)
    {
        std::string TextOrigin = Data.View[Args.Line].Data;
        size_t TStart = 0;
        while ((TStart = TextOrigin.find("{", TStart)) != std::string::npos)
        {
            size_t TEnd = TextOrigin.find("}", TStart);

            if (TEnd == std::string::npos)
            {
                break;
            }

            std::string Var = TextOrigin.substr(TStart + 1, TEnd - TStart - 1);
            std::string Value = Player.GetStatusFromKey(Var);
            TextOrigin.replace(TStart, TEnd - TStart + 1, Value);
            TStart += Value.length();
        }

        MoveCursor(0, Args.Line - FixYPos);
        std::cout << ClearLine();
        MoveCursor(0, Args.Line - FixYPos);
        std::cout << TextOrigin;
    }
}

void WaitLoading(std::string Text, FTextData& Data)
{
    std::string ExitText = "종료하려면 exit을 입력하세요.";
    std::string StepText = "계속하려면 아무 문자열이나 입력하세요.";
    int FixYPos = 2;
    MoveCursor(0, (unsigned int)Data.View.size() - FixYPos);
    std::cout << ClearLine();
    MoveCursor(0, (unsigned int)Data.View.size() - FixYPos);
    std::cout << "/" << Text;
    for (int i = 0; i < 3; ++i)
    {
        Sleep(500);
        std::cout << ". ";
    }
    std::cout << "/" << std::endl;
    Sleep(500);
    MoveCursor(0, (unsigned int)Data.View.size() - FixYPos);
    std::cout << ClearLine();
    MoveCursor(0, (unsigned int)Data.View.size() - FixYPos);
    std::cout << "Loaded!" << std::endl;
    MoveCursor(0, (unsigned int)Data.View.size() - FixYPos + 1);
    std::cout << ExitText << std::endl;
    std::cout << StepText << std::endl;
}

bool CheckExit()
{
    std::string Input;
    std::cin >> Input;

    if (Input == "exit")
    {
        return true;
    }
    else
    {
        return false;
    }
}

void SetNext(FTextData& Data, int& Phase)
{
    Data.GetDataOrigin().clear();
    MoveCursor(0, (unsigned int)Data.View.size() + 1);
    ++Phase;
    if (CheckExit())
    {
        exit(0);
    }
}
