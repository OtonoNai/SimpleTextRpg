#include "MonsterLoader.h"
#include "CSVReader.h"

std::map<std::string, FMonster> LoadMonsters(const std::string& FilePath)
{
	CSVReader Reader;
	Reader.ReadFile(FilePath);

	std::map<std::string, FMonster> Result;

	for (size_t i = 1; i < Reader.GetRowCount(); ++i)
	{
		const auto& Row = Reader.GetRow(i);

		std::string MonsterId = Row[0];
		std::string DisplayName = Row[1];
		int Hp = Row[2].empty() ? 0 : stoi(Row[2]);
		int Atk = Row[3].empty() ? 0 : stoi(Row[3]);
		int Def = Row[4].empty() ? 0 : stoi(Row[4]);
		std::string DropItemId = Row[5];
		int ExpReward = Row[6].empty() ? 0 : stoi(Row[6]);

		FMonster NewMonster(MonsterId, DisplayName, Hp, Atk, Def, DropItemId, ExpReward);
		Result.emplace(MonsterId, NewMonster);
	}

	return Result;
}