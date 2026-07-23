#include "GameScreen.h"
#include "ConsoleUtils.h"
#include <Windows.h>
#include <sstream>
#include <iostream>
#include <cstdlib>

std::string ReadValidatedInput(const FTextDataIn& Input)
{
RETRY_INPUT:
	std::stringstream Ss(Input.VarRange);
	std::string Token;
	std::vector<int> TempRange;

	int Y = Input.Column;
	int X = Input.VarX;

	MoveCursor(X + 1, Y - 1);

	std::string Value;
	std::getline(std::cin, Value);

	try
	{
		if (Input.VarType == "int")
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
		FlushInput();
		goto RETRY_INPUT;
	}

	return Value;
}

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
		FlushInput();
		return false;
	}
}

FPlayer* CreatePlayerFromJobSelection(const std::string& Value, const std::map<std::string, FJobData>& Jobs)
{
	std::string JobId;

	if (Value == "1")
	{
		JobId = "warrior";
	}
	else if (Value == "2")
	{
		JobId = "mage";
	}
	else if (Value == "3")
	{
		JobId = "thief";
	}
	else if (Value == "4")
	{
		JobId = "archer";
	}

	const FJobData& SelectedJob = Jobs.at(JobId);

	if (JobId == "warrior")
	{
		return new FWarrior(SelectedJob);
	}
	else if (JobId == "mage")
	{
		return new FMage(SelectedJob);
	}
	else if (JobId == "thief")
	{
		return new FThief(SelectedJob);
	}

	return new FArcher(SelectedJob);
}

FPlayer* HandleJobSelection(FTextData& Data, const std::map<std::string, FJobData>& Jobs)
{
	std::string Value = ReadValidatedInput(Data.In[0]);
	return CreatePlayerFromJobSelection(Value, Jobs);
}

void HandleMainMenu(FTextData& Data, FPlayer& Player, FInventory& Inventory, const std::map<std::string, FItem>& Items, const std::vector<FMonster>& MonsterPool, FPotionShop& Shop)
{
	std::string Value = ReadValidatedInput(Data.In[0]);

	if (Value == "1")
	{
		FMonster Monster = MonsterPool[rand() & MonsterPool.size()];

		if (RunBattle(Player, Monster) == EBattleResult::Victory)
		{
			if (Monster.GetDropItemId() != "none")
			{
				Inventory.AddItem(Monster.GetDropItemId(), 1);
			}

			Data.LastInteractMessage = Monster.GetDisplayName() + " 처치! 아이템을 획득했습니다.";
		}
		else
		{
			Data.LastInteractMessage = "패배했습니다...";
		}
		
		Data.bAdvancePhase = false;
	}
	else if (Value == "2")
	{
		std::cout << std::endl << "[ 인벤토리 ]" << std::endl;

		for (const auto& Entry : Inventory.ToDisplayList(Items))
		{
			std::cout << Entry.first.GetDisplayName() << " x" << Entry.second << std::endl;
		}

		std::cout << std::endl << "계속하려면 Enter..." << std::endl;
		std::cin.get();

		Data.LastInteractMessage = "인벤토리를 확인했습니다.";
		Data.bAdvancePhase = false;
	}
	else if (Value == "3")
	{
		std::cout << std::endl << "1.전체보기 2.이름검색 3.재료검색 : ";
		std::string Choice;
		std::getline(std::cin, Choice);

		if (Choice == "1")
		{
			Shop.ShowAll(Items);
		}
		else if (Choice == "2")
		{
			std::cout << "검색할 이름 : ";
			std::string Name;
			std::getline(std::cin, Name);

			for (const auto& Recipe : Shop.SearchByName(Name, Items))
			{
				std::cout << "-> " << Recipe.RecipeId << std::endl;
			}
		}
		else if (Choice == "3")
		{
			std::cout << "검색할 재료 : ";
			std::string Ingredient;
			std::getline(std::cin, Ingredient);

			for (const auto& Recipe : Shop.SearchByIngredient(Ingredient))
			{
				std::cout << "-> " << Recipe.RecipeId << std::endl;
			}
		}

		std::cout << std::endl << "계속하려면 Enter..." << std::endl;
		std::cin.get();

		Data.LastInteractMessage = "포션 제작소를 이용했습니다.";
		Data.bAdvancePhase = false;
	}
	else if (Value == "0")
	{
		Data.LastInteractMessage = "게임을 종료합니다.";
		Data.bAdvancePhase = true;
	}
}


void GetInput(FTextData& Data, FPlayer& Player, FInventory& Inventory, const std::map<std::string, FItem>& Items, int Phase)
{
	std::vector<FTextDataView> TempView = Data.View;
	std::vector<FTextDataIn> TempIn = Data.In;
	std::string TempData;

	for (const auto& Input : TempIn)
	{
		std::string Value = ReadValidatedInput(Input);

		if (Phase == 2)
		{
			Player.SetStatus(Input.VarName, Value);
		}
		else if (Phase == 3)
		{
			Interact(Data, Player, Inventory, Items, stoi(Value));
		}
	}

	if (Phase == 2)
	{
		Player.ApplyJobBonus();
	}
}

std::string SubstituteVars(std::string Text, FPlayer& Player)
{
	size_t TStart = 0;
	while ((TStart = Text.find("{", TStart)) != std::string::npos)
	{
		size_t TEnd = Text.find("}", TStart);

		if (TEnd == std::string::npos)
		{
			break;
		}

		std::string Var = Text.substr(TStart + 1, TEnd - TStart - 1);
		std::string Value = Player.GetStatusFromKey(Var);
		Text.replace(TStart, TEnd - TStart + 1, Value);
		TStart += Value.length();
	}

	return Text;
}

void Interact(FTextData& Data, FPlayer& Player, FInventory& Inventory, const std::map<std::string, FItem>& Items, int SelectedValue)
{
	Data.LastInteractMessage.clear();

	for (const auto& Candidate : Data.Interacts)
	{
		if (Candidate.Trigger != SelectedValue)
		{
			continue;
		}

		bool bConditionMet = true;

		if (!Candidate.RequiredItem.empty())
		{
			bConditionMet = Inventory.HasItem(Candidate.RequiredItem, Candidate.RequiredQty);
		}

		std::string ExpectedResult = bConditionMet ? "success" : "fail";

		if (Candidate.ResultType != ExpectedResult)
		{
			continue;
		}

		if (bConditionMet && !Candidate.RequiredItem.empty())
		{
			auto ItemIt = Items.find(Candidate.RequiredItem);

			if (ItemIt != Items.end())
			{
				ItemIt->second.ApplyTo(Player);
				Inventory.RemoveItem(Candidate.RequiredItem, Candidate.RequiredQty);
			}
		}

		Data.LastInteractMessage = SubstituteVars(Candidate.Text, Player);
		break;
	}

	Data.bAdvancePhase = (SelectedValue == 0);
}

void UpdateRender(FTextData& Data, FPlayer& Player)
{
	std::vector<FTextDataView> TempView = Data.View;
	std::vector<FTextDataUpdate> TempUpdate = Data.Update;
	int FixYPos = 1;

	for (const auto& Args : TempUpdate)
	{
		std::string TextOrigin = SubstituteVars(Data.View[Args.Line].Data, Player);
		size_t TStart = 0;

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
	int LoadingLineY = Data.ConsoleLine - 1;

	MoveCursor(0, LoadingLineY);
	std::cout << ClearLine();
	MoveCursor(0, LoadingLineY);
	std::cout << "/" << Text;
	for (int i = 0; i < 3; ++i)
	{
		Sleep(500);
		std::cout << ". ";
	}
	std::cout << "/" << std::endl;
	Sleep(500);
	MoveCursor(0, LoadingLineY);
	std::cout << ClearLine();
	MoveCursor(0, LoadingLineY);
	std::cout << "Loaded!" << std::endl;

	if (Data.bAdvancePhase)
	{
		MoveCursor(0, LoadingLineY + 1);
		std::cout << ExitText << std::endl;
		std::cout << StepText << std::endl;
	}

	FlushInput();
}

bool CheckExit()
{
	std::string Input;
	std::getline(std::cin, Input);

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

	if (Data.bAdvancePhase)
	{
		++Phase;
	}
}
