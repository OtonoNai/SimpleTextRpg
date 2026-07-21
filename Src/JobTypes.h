#pragma once

#include <string>
#include "Player.h"

struct FJobData
{
	std::string JobId;
	std::string DisplayName;
	std::string BonusStat;
	int BonusValue;
	std::string AttackMessage;
	int HitCount;
	int DamageDivisor;
	std::string JobMessage;
};

class FWarrior : public FPlayer
{
public:
	FWarrior(const FJobData& JobData);

	virtual std::string Attack() const override;
};

class FMage : public FPlayer
{
public:
	FMage(const FJobData& JobData);

	virtual std::string Attack() const override;
};

class FThief : public FPlayer
{
public:
	FThief(const FJobData& JobData);

	virtual std::string Attack() const override;
};

class FArcher : public FPlayer
{
public:
	FArcher(const FJobData& JobData);

	virtual std::string Attack() const override;
};
