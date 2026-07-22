#pragma once

#include "Player.h"
#include "Monster.h"

enum class EBattleResult
{
	Victory,
	Defeat,
};

int CalculateDamage(int AttackterAtk, int DamageDivisor, int TargerDef);
EBattleResult RunBattle(FPlayer& Player, FMonster& Monster);