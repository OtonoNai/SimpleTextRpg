#include "JobLoader.h"
#include "CSVReader.h"

std::map<std::string, FJobData> LoadJobs(const std::string& FilePath)
{
	CSVReader Reader;
	Reader.ReadFile(FilePath);

	std::map<std::string, FJobData> Result;

	for (size_t i = 1; i < Reader.GetRowCount(); ++i)
	{
		const auto& Row = Reader.GetRow(i);

		FJobData NewJob;
		NewJob.JobId = Row[0];
		NewJob.DisplayName = Row[1];
		NewJob.BonusStat = Row[2];
		NewJob.BonusValue = Row[3].empty() ? 0 : stoi(Row[3]);
		NewJob.AttackMessage = Row[4];
		NewJob.HitCount = Row[5].empty() ? 1 : stoi(Row[5]);
		NewJob.DamageDivisor = Row[6].empty() ? 1 : stoi(Row[6]);

		Result.emplace(NewJob.JobId, NewJob);
	}

	return Result;
}