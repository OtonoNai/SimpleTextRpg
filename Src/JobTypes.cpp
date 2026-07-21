#include "JobTypes.h"

FWarrior::FWarrior(const FJobData& JobData)
	: FPlayer(JobData.AttackMessage, JobData.HitCount, JobData.DamageDivisor, JobData.JobMessage)
{
	ModifyStat(JobData.BonusStat, "add", JobData.BonusValue);
}

std::string FWarrior::Attack() const
{
	return AttackMessage;
}

FMage::FMage(const FJobData& JobData)
	: FPlayer(JobData.AttackMessage, JobData.HitCount, JobData.DamageDivisor, JobData.JobMessage)
{
	ModifyStat(JobData.BonusStat, "add", JobData.BonusValue);
}

std::string FMage::Attack() const
{
	return AttackMessage;
}

FThief::FThief(const FJobData& JobData)
	: FPlayer(JobData.AttackMessage, JobData.HitCount, JobData.DamageDivisor, JobData.JobMessage)
{
	ModifyStat(JobData.BonusStat, "add", JobData.BonusValue);
}

std::string FThief::Attack() const
{
	return AttackMessage;
}

FArcher::FArcher(const FJobData& JobData)
	: FPlayer(JobData.AttackMessage, JobData.HitCount, JobData.DamageDivisor, JobData.JobMessage)
{
	ModifyStat(JobData.BonusStat, "add", JobData.BonusValue);
}

std::string FArcher::Attack() const
{
	return AttackMessage;
}
