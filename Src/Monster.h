#pragma once

#include <string>

class FMonster
{
public:
	FMonster(std::string InMonsterId, std::string InDisplayName, int InHp, int InAtk, int InDef, std::string InDropItemId, int InExpReward);
	
	void TakeDamage(int Amount);
	bool IsAlive() const;

	const std::string& GetMonsterId() const;
	const std::string& GetDisplayName() const;
	int GetHp() const;
	int GetAtk() const;
	int GetDef() const;
	const std::string& GetDropItemId() const;
	int GetExpReward() const;

private:
	std::string MonsterId;
	std::string DisplayName;
	int Hp;
	int Atk;
	int Def;
	std::string DropItemId;
	int ExpReward;
};